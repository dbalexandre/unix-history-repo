/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)subr_prof.c	7.5 (Berkeley) %G%
 */

#ifdef GPROF
#include "gprof.h"
#include "param.h"
#include "systm.h"
#include "malloc.h"

/*
 * Froms is actually a bunch of unsigned shorts indexing tos
 */
int	profiling = 3;
u_short	*froms;
struct	tostruct *tos = 0;
long	tolimit = 0;
#if defined(vax)
char	*s_lowpc = (char *)0x80000000;
#endif
#if defined(tahoe)
char	*s_lowpc = (char *)0xc0000000;
#endif
extern	char etext;
char	*s_highpc = &etext;
u_long	s_textsize = 0;
int	ssiz;
u_short	*sbuf;
u_short	*kcount;

kmstartup()
{
	u_long fromssize, tossize;

	/*
	 * Round lowpc and highpc to multiples of the density we're using
	 * so the rest of the scaling (here and in gprof) stays in ints.
	 */
	s_lowpc = (char *)
	    ROUNDDOWN((unsigned)s_lowpc, HISTFRACTION*sizeof (HISTCOUNTER));
	s_highpc = (char *)
	    ROUNDUP((unsigned)s_highpc, HISTFRACTION*sizeof (HISTCOUNTER));
	s_textsize = s_highpc - s_lowpc;
	printf("Profiling kernel, s_textsize=%d [%x..%x]\n",
		s_textsize, s_lowpc, s_highpc);
	ssiz = (s_textsize / HISTFRACTION) + sizeof (struct phdr);
	sbuf = (u_short *)malloc(ssiz, M_GPROF, M_WAITOK);
	if (sbuf == 0) {
		printf("No space for monitor buffer(s)\n");
		return;
	}
	bzero(sbuf, ssiz);
	fromssize = s_textsize / HASHFRACTION;
	froms = (u_short *)malloc(fromssize, M_GPROF, M_WAITOK);
	if (froms == 0) {
		printf("No space for monitor buffer(s)\n");
		free(sbuf, M_GPROF);
		sbuf = 0;
		return;
	}
	bzero(froms, fromsize);
	tolimit = s_textsize * ARCDENSITY / 100;
	if (tolimit < MINARCS)
		tolimit = MINARCS;
	else if (tolimit > (0xffff - 1))
		tolimit = 0xffff - 1;
	tossize = tolimit * sizeof (struct tostruct);
	tos = (struct tostruct *)malloc(tossize, M_GPROF, M_WAITOK);
	if (tos == 0) {
		printf("No space for monitor buffer(s)\n");
		free(sbuf, M_GPROF), sbuf = 0;
		free(froms, M_GPROF), froms = 0;
		return;
	}
	bzero(tos, tossize);
	tos[0].link = 0;
	((struct phdr *)sbuf)->lpc = s_lowpc;
	((struct phdr *)sbuf)->hpc = s_highpc;
	((struct phdr *)sbuf)->ncnt = ssiz;
	kcount = (u_short *)(((int)sbuf) + sizeof (struct phdr));
#ifdef notdef
	/*
	 * Profiling is what mcount checks to see if
	 * all the data structures are ready!!!
	 */
	profiling = 0;		/* patch by hand when you're ready */
#endif
}

/*
 * This routine is massaged so that it may be jsb'ed to on vax.
 */
asm(".text");
asm("#the beginning of mcount()");
asm(".data");
mcount()
{
	register char *selfpc;			/* r11 => r5 */
	register u_short *frompcindex;		/* r10 => r4 */
	register struct tostruct *top;		/* r9  => r3 */
	register struct tostruct *prevtop;	/* r8  => r2 */
	register long toindex;			/* r7  => r1 */
	static int s;

	asm("	.text");		/* make sure we're in text space */
	/*
	 * Check that we are profiling.
	 */
	if (profiling)
		goto out;
	/*
	 * Find the return address for mcount,
	 * and the return address for mcount's caller.
	 */
#ifdef lint
	selfpc = (char *)0;
	frompcindex = 0;
#else
	;				/* avoid label botch */
#if defined(vax)
	asm("	movl (sp), r11");	/* selfpc = ... (jsb frame) */
	asm("	movl 16(fp), r10");	/* frompcindex =     (calls frame) */
#endif
#if defined(tahoe)
	asm("	movl -8(fp),r12");	/* selfpc = callf frame */
	asm("	movl (fp),r11");
	asm("	movl -8(r11),r11");	/* frompcindex = 1 callf frame back */
#endif
#endif
	/*
	 * Insure that we cannot be recursively invoked.
	 * this requires that splhigh() and splx() below
	 * do NOT call mcount!
	 */
	s = splhigh();
	/*
	 * Check that frompcindex is a reasonable pc value.
	 * For example:	signal catchers get called from the stack,
	 *	not from text space.  too bad.
	 */
	frompcindex = (u_short *)((long)frompcindex - (long)s_lowpc);
	if ((u_long)frompcindex > s_textsize)
		goto done;
	frompcindex =
	    &froms[((long)frompcindex) / (HASHFRACTION * sizeof (*froms))];
	toindex = *frompcindex;
	if (toindex == 0) {
		/*
		 * First time traversing this arc
		 */
		toindex = ++tos[0].link;
		if (toindex >= tolimit)
			goto overflow;
		*frompcindex = toindex;
		top = &tos[toindex];
		top->selfpc = selfpc;
		top->count = 1;
		top->link = 0;
		goto done;
	}
	top = &tos[toindex];
	if (top->selfpc == selfpc) {
		/*
		 * Arc at front of chain; usual case.
		 */
		top->count++;
		goto done;
	}
	/*
	 * Have to go looking down chain for it.
	 * Top points to what we are looking at,
	 * prevtop points to previous top.
	 * We know it is not at the head of the chain.
	 */
	for (; /* goto done */; ) {
		if (top->link == 0) {
			/*
			 * Top is end of the chain and none of the chain
			 * had top->selfpc == selfpc.
			 * So we allocate a new tostruct
			 * and link it to the head of the chain.
			 */
			toindex = ++tos[0].link;
			if (toindex >= tolimit)
				goto overflow;
			top = &tos[toindex];
			top->selfpc = selfpc;
			top->count = 1;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		/*
		 * Otherwise, check the next arc on the chain.
		 */
		prevtop = top;
		top = &tos[top->link];
		if (top->selfpc == selfpc) {
			/*
			 * There it is, increment its count and
			 * move it to the head of the chain.
			 */
			top->count++;
			toindex = prevtop->link;
			prevtop->link = top->link;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}

	}
done:
	splx(s);
	/* and fall through */
out:
#if defined(vax)
	asm("	rsb");
#endif
	return;
overflow:
	profiling = 3;
	printf("mcount: tos overflow\n");
	goto out;
}
asm(".text");
asm("#the end of mcount()");
asm(".data");
#endif
