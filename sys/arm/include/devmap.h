/*-
 * Copyright (c) 2013 Ian Lepore <ian@freebsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef	_MACHINE_DEVMAP_H_
#define	_MACHINE_DEVMAP_H_

/*
 * Routines to translate between virtual and physical addresses within a region
 * that is static-mapped by the devmap code.  If the given address range isn't
 * static-mapped, then ptov returns NULL and vtop returns DEVMAP_PADDR_NOTFOUND.
 * The latter implies that you can't vtop just the last byte of physical address
 * space.  This is not as limiting as it might sound, because even if a device
 * occupies the end of the physical address space, you're only prevented from
 * doing vtop for that single byte.  If you vtop a size bigger than 1 it works.
 */
#define	DEVMAP_PADDR_NOTFOUND	((vm_paddr_t)(-1))

void *     arm_devmap_ptov(vm_paddr_t _pa, vm_size_t _sz);
vm_paddr_t arm_devmap_vtop(void * _va, vm_size_t _sz);

#endif
