/**************************************************************************
**
**  $Id: pcivar.h,v 1.3 1995/03/17 04:27:21 davidg Exp $
**
**  Declarations for pci device drivers.
**
**  FreeBSD
**
**-------------------------------------------------------------------------
**
** Copyright (c) 1994 Wolfgang Stanglmeier.  All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
***************************************************************************
*/

#ifndef __PCI_VAR_H__
#define __PCI_VAR_H__ "pl2 95/03/21"

/*-----------------------------------------------------------------
**
**	main pci initialization function.
**	called at boot time from autoconf.c
**
**-----------------------------------------------------------------
*/

void pci_configure (void);

/*-----------------------------------------------------------------
**
**	The pci configuration id describes a pci device on the bus.
**	It is constructed from: bus, device & function numbers.
**
**-----------------------------------------------------------------
*/

typedef union {
	u_long	 cfg1;
	struct {
		 u_char   enable;
		 u_char   forward;
		 u_short  port;
	       } cfg2;
	unsigned tag;
	} pcici_t;

#define sametag(x,y)  ((x).tag == (y).tag)

/*-----------------------------------------------------------------
**
**	Each pci device has an unique device id.
**	It is used to find a matching driver.
**
**-----------------------------------------------------------------
*/

typedef u_long pcidi_t;

/*-----------------------------------------------------------------
**
**	The following functions are provided for the device driver
**	to read/write the configuration space.
**
**	pci_conf_read():
**		Read a long word from the pci configuration space.
**		Requires a tag (from pcitag) and the register
**		number (should be a long word alligned one).
**
**	pci_conf_write():
**		Writes a long word to the pci configuration space.
**		Requires a tag (from pcitag), the register number
**		(should be a long word alligned one), and a value.
**
**-----------------------------------------------------------------
*/

u_long pci_conf_read  (pcici_t tag, u_long reg		   );

void   pci_conf_write (pcici_t tag, u_long reg, u_long data);

/*-----------------------------------------------------------------
**
**	The pci driver structure.
**
**	name:	The short device name.
**
**	probe:	Checks if the driver can support a device
**		with this type. The tag may be used to get
**		more info with pci_read_conf(). See below.
**		It returns a string with the devices name,
**		or a NULL pointer, if the driver cannot
**		support this device.
**
**	attach:	Allocate a control structure and prepare
**		it. This function may use the pci mapping
**		functions. See below.
**		(configuration id) or type.
**
**	count:	A pointer to a unit counter.
**		It's used by the pci configurator to
**		allocate unit numbers.
**
**-----------------------------------------------------------------
*/

struct pci_device {
    char*    pd_name;
    char*  (*pd_probe ) (pcici_t tag, pcidi_t type);
    void   (*pd_attach) (pcici_t tag, int     unit);
    u_long  *pd_count;
    int    (*pd_shutdown) (struct kern_devconf *, int);
};

/*-----------------------------------------------------------------
**
**	This table includes pointers to all pci device drivers.
**	It should be generated by the linker.
**
**-----------------------------------------------------------------
*/

extern struct linker_set pcidevice_set;

extern unsigned pci_max_burst_len;  /* log2 of safe burst transfer length */
extern unsigned pci_mechanism;
extern unsigned pci_maxdevice;

/*-----------------------------------------------------------------
**
**	The pci-devconf interface.
**
**-----------------------------------------------------------------
*/

struct pci_info {
	u_short pi_bus;
	u_short pi_device;
};  
   
#define PCI_EXT_CONF_LEN (16)
#define PCI_EXTERNAL_LEN (sizeof(struct pci_externalize_buffer))

struct pci_externalize_buffer {
	struct pci_info	peb_pci_info;
	u_long		peb_config[PCI_EXT_CONF_LEN];
};

/*-----------------------------------------------------------------
**
**	Map a pci device to physical and virtual memory.
**
**      Entry selects the register in the pci configuration
**	space, which supplies the size of the region, and
**	receives the physical address.
**
**	In case of success the function sets the addresses
**	in *va and *pa, and returns 1.
**	In case of errors a message is written,
**	and the function returns 0.
**
**-----------------------------------------------------------------
*/

int pci_map_mem (pcici_t tag, u_long entry, u_long  * va, u_long * pa);

/*-----------------------------------------------------------------
**
**	Map a pci device to an io port area.
**
**	Entry selects the register in the pci configuration
**	space, which supplies the size of the region, and
**	receives the port number.
**
**	In case of success the function sets the port number in pa,
**	and returns 1.
**	In case of errors a message is written,
**	and the function returns 0.
**
**-----------------------------------------------------------------
*/

int pci_map_port (pcici_t tag, u_long entry, u_short * pa);

/*-----------------------------------------------------------------
**
**	Map a pci interrupt to an isa irq line, and enable the interrupt.
**
**      -----------------
**
**      func is the interrupt handler, arg is the argument
**      to the handler (usually a pointer to a softc).
**
**      The maskptr argument should be  &bio_imask,
**      &net_imask etc. or NULL.
**
**      If there is any error, a message is written, and
**      the function returns with zero.
**      Else it returns with a value different to zero.
**
**      -----------------
**
**	The irq number is read from the configuration space.
**	(Should have been set by the bios).
**
**	Supports multiple handlers per irq (shared interrupts).
**
**	-----------------
**
**	There is code to support shared edge triggered ints.
**	This relies on the cooperation of the interrupt handlers:
**	they have to return a value <>0 if and only if something
**	was done. Beware of the performance penalty.
**
**-----------------------------------------------------------------
*/

struct pci_int_desc {
	struct pci_int_desc * pcid_next;
	pcici_t 	      pcid_tag;
	int		    (*pcid_handler)();
	void*		      pcid_argument;
	unsigned *	      pcid_maskptr;
	unsigned	      pcid_tally;
	unsigned	      pcid_mask;
};

int pci_map_int (pcici_t tag, int (*func)(), void* arg, unsigned * maskptr);

int pci_unmap_int (pcici_t tag);

#endif
