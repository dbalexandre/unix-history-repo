/*
 *  Interpress utilities
 *
 * Copyright (c) 1984, 1985 Xerox Corp.
 *
 *  Written for Xerox Corporation by William LeFebvre
 *  31-May-1984
 *
 * History:
 *	26-apr-85  ed flint	add macros to set standard imager variables
 */

/*
 *  Subroutines to help build interpress files:
 *
 *  operator interface level - these routines call routines at the literal
 *			       interface level to provide an easy way to
 *			       write operators along with their parameters.
 */

/*
 *  These routines are all deined with macros that call low level routines
 *  found in operator.c.
 */

# define    Abs(n)		op_n(OP_abs, n)
# define    Add(n1,n2)		op_nn(OP_add, n1, n2)
# define    And(i1,i2)		op_ii(OP_and, (long) i1, (long) i2)
# define    Ceiling(n)		op_n(OP_ceiling, n)
# define    Copy(i)		op_i(OP_copy, (long) i)
# define    CorrectSpace(n1,n2)	op_nn(OP_correctspace, n1, n2)
# define    Div(n1,n2)		op_nn(OP_div, n1, n2)
# ifdef anyop
# define    Dup(a)		op_a(OP_dup, a)
# define    Eq(a1,a2)		op_aa(OP_eq, a1, a2)
# define    Exch(a1,a2)		op_aa(OP_exch, a1, a2)
# endif
# define    Fget(i)		op_i(OP_fget, (long) i)
# define    Floor(n)		op_n(OP_floor, n)
# ifdef anyop
# define    Fset(a,i)		op_ai(OP_fset, a, (long) i)
# endif
# define    Ge(n1,n2)		op_nn(OP_ge, n1, n2)
# define    Get(n)		op_n(OP_get, n)
# define    Gt(n1,n2)		op_nn(OP_gt, n1, n2)
# define    Iget(i)		op_i(OP_iget, (long) i)
# ifdef anyop
# define    Iset(a,i)		op_ai(OP_iset, a, (long) i)
# endif
# define    Lineto(n1,n2)	op_nn(OP_lineto, n1, n2)
# define    Linetox(n)		op_n(OP_linetox, n)
# define    Linetoy(n)		op_n(OP_linetoy, n)
# define    Makegray(n)		op_n(OP_makegray, n)
# define    Makeoutline(i)	op_i(OP_makeoutline, (long) i)
# define    Makesampledblack(i)	op_i(OP_makesampledblack, (long) i)
# define    Makevec(i)		op_i(OP_makevec, (long) i)
# define    Makeveclu(i1,i2)	op_ii(OP_makeveclu, (long) i1, (long) i2)
# define    Mark(i)		op_i(OP_mark, (long) i)
# define    Maskrectangle(n1,n2,n3,n4)	op_nnnn(OP_maskrectangle,n1,n2,n3,n4)
# define    Masktrapezoidx(n1,n2,n3,n4,n5,n6)	\
		op_nnnnnn(OP_masktrapezoidx,n1,n2,n3,n4,n5,n6)
# define    Masktrapezoidy(n1,n2,n3,n4,n5,n6) \
		op_nnnnnn(OP_masktrapezoidy,n1,n2,n3,n4,n5,n6)
# define    Maskunderline(n1,n2)	op_nn(OP_maskunderline, n1, n2)
# define    Maskvector(n1,n2,n3,n4)	op_nnnn(OP_maskvector,n1,n2,n3,n4)
# define    Mod(n1,n2)		op_nn(OP_mod, n1, n2)
# define    Moveto(n1,n2)	op_nn(OP_moveto, n1, n2)
# define    Mul(n1,n2)		op_nn(OP_mul, n1, n2)
# define    Neg(n)		op_n(OP_neg, n)
# define    Not(i)		op_i(OP_not, (long) i)
# define    Or(i1,i2)		op_ii(OP_or, (long) i1, (long) i2)
# ifdef anyop
# define    Pop(a)		op_a(OP_pop, a)
# endif
# define    Rem(n1,n2)		op_nn(OP_rem, n1, n2)
# define    Roll(i1,i2)		op_ii(OP_roll, (long) i1, (long) i2)
# define    Rotate(n)		op_n(OP_rotate, n)
# define    Round(n)		op_n(OP_round, n)
# define    Scale(n)		op_n(OP_scale, n)
# define    Scale2(n1,n2)	op_nn(OP_scale2, n1, n2)
# define    Setamplifyspace(n)	op_ni(OP_iset, n, (long) I_amplifySpace)
# define    Setcorrectmeasure(n1,n2)	op_nn(OP_setcorrectmeasure, n1, n2)
# define    Setcorrectpass(i)	op_ii(OP_iset, (long) i, (long) I_correctPass)
# define    Setcorrectshrink(n)	op_ni(OP_iset, n, (long) I_correctShrink)
# define    Setcorrecttolerance(n1,n2)	op_nn(OP_setcorrecttolerance, n1, n2)
# define    Setfont(i)		op_i(OP_setfont, (long) i)
# define    Setgray(n)		op_n(OP_setgray, n)
# define    Setnoimage(i)	op_ii(OP_iset, (long) i, (long) I_noImage)
# define    Setpriorityimportant(i)	op_ii(OP_iset, (long) i, (long) I_priorityImportant)
# define    Setstrokeend(i)	op_ii(OP_iset, (long) i, (long) I_strokeEnd)
# define    Setstrokewidth(n)	op_ni(OP_iset, n, (long) I_strokeWidth)
# define    Setunderlinestart(n)	op_ni(OP_iset, n, (long) I_underlineStart)
# define    Setxrel(n)		op_n(OP_setxrel, n)
# define    Setxy(n1,n2)	op_nn(OP_setxy, n1, n2)
# define    Setxyrel(n1,n2)	op_nn(OP_setxyrel, n1, n2)
# define    Setyrel(n)		op_n(OP_setyrel, n)
# define    Space(n)		op_n(OP_space, n)
# define    Sub(n1,n2)		op_nn(OP_sub, n1, n2)
# define    Translate(n1,n2)	op_nn(OP_translate, n1, n2)
# define    Trunc(n)		op_n(OP_trunc, n)
# ifdef anyop
# define    Type(a)		op_a(OP_type, a)
# endif
# define    Unmark(i)		op_i(OP_unmark, (long) i)
