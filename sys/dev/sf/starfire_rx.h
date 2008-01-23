/* $FreeBSD$ */
/*
 *   MODULE: GFP_RX.H
 *
 *   (c)2001 Adaptec, Inc. By using this software you agree that it is
 *   licensed to you "AS IS" and that Adaptec makes no warranties,
 *   express or implied, regarding the Software.
 *   Any redistribution of this Software must include this disclaimer and
 *   copyright notice.
 */

static unsigned char rxfwdata[624] =
{
	0x00,0x00,0x01,0x00,0x03,0xdc,
	0x00,0x86,0x04,0x00,0x04,0x21,
	0x18,0x0e,0x80,0x00,0x00,0x15,
	0x66,0x64,0x81,0x00,0x00,0x15,
	0x0b,0x06,0x1a,0x00,0x40,0xab,
	0x00,0x00,0x14,0x20,0x00,0x11,
	0xaa,0xaa,0x14,0x20,0x40,0x22,
	0x03,0x00,0x14,0x20,0x40,0x22,
	0x00,0x00,0x14,0x20,0x40,0x22,
	0x0b,0x14,0x1a,0x00,0x40,0xab,
	0x00,0x00,0x14,0x20,0x00,0x11,
	0x00,0x02,0x83,0x00,0x00,0x15,
	0x00,0x00,0x04,0x00,0x00,0x21,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x87,0x04,0x00,0x04,0x21,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x00,0x00,0x00,0x80,0x15,
	0x00,0x00,0x00,0x00,0x00,0x3e,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x40,0x00,0x82,0x00,0x00,0x15,
	0x00,0x00,0x00,0x9e,0x80,0x50,
	0x00,0x00,0x03,0x00,0x80,0x15,
	0x00,0x00,0x86,0x00,0x80,0x15,
	0x80,0x00,0x82,0x00,0x00,0x15,
	0x00,0x00,0x01,0x00,0x00,0x1c,
	0x01,0x0c,0x00,0x00,0x50,0xa0,
	0x60,0x08,0x4e,0x20,0xd0,0x11,
	0x40,0x08,0x14,0x20,0xd0,0x12,
	0x70,0x00,0x00,0x00,0xf0,0x90,
	0x30,0x00,0x00,0x00,0xc8,0xb0,
	0x00,0x00,0x00,0x00,0x40,0x40,
	0x00,0x00,0x00,0x10,0x80,0x15,
	0x40,0x00,0x00,0xa2,0xc1,0x50,
	0x00,0x14,0x00,0xa4,0x00,0xb0,
	0x00,0x00,0x00,0x00,0x00,0x20,
	0x25,0x25,0x25,0x00,0x40,0x0d,
	0x31,0x00,0x00,0x04,0x72,0x20,
	0x00,0x00,0x00,0x93,0x40,0x70,
	0x00,0x00,0x00,0x00,0x00,0x20,
	0x01,0x84,0x00,0x92,0x44,0x60,
	0x00,0x00,0x2b,0x20,0xc0,0x11,
	0x05,0x40,0x00,0x00,0xc4,0x20,
	0x42,0x2d,0x36,0x01,0x40,0x18,
	0x00,0x00,0x14,0x20,0x00,0x11,
	0x01,0x83,0x00,0x92,0x44,0x60,
	0x00,0x34,0x32,0x00,0x00,0x1f,
	0x00,0x02,0x02,0xac,0x00,0x15,
	0x00,0x08,0x00,0xa6,0x01,0x10,
	0x00,0x00,0x42,0x20,0x00,0x11,
	0x01,0x03,0x00,0x92,0x40,0x60,
	0x00,0x00,0x00,0x00,0x00,0x1e,
	0x01,0x00,0x00,0x00,0x00,0x20,
	0x00,0x00,0x00,0x00,0x00,0x1e,
	0x00,0x86,0x00,0x92,0x44,0x60,
	0x00,0x00,0x00,0x00,0x40,0x80,
	0x00,0x00,0x00,0x92,0xc0,0x70,
	0x01,0x00,0x00,0x92,0x40,0x60,
	0x50,0x00,0x00,0x00,0xc8,0x90,
	0x00,0x00,0x00,0xa6,0xc1,0x10,
	0x00,0x12,0x00,0xb0,0xc0,0x90,
	0x00,0x00,0x02,0x1c,0x00,0x15,
	0x00,0x34,0x32,0x00,0x00,0x1f,
	0x05,0x10,0x00,0x92,0x44,0x60,
	0x00,0x00,0x44,0x21,0x00,0x11,
	0x00,0x00,0x42,0x00,0x00,0x11,
	0x00,0x40,0x83,0x00,0x00,0x15,
	0x05,0x08,0x00,0x92,0x44,0x60,
	0x45,0x45,0x45,0x01,0x40,0x18,
	0x00,0x00,0x00,0x80,0x80,0x50,
	0x00,0x40,0x83,0x00,0x00,0x15,
	0x00,0x00,0x62,0x20,0x80,0x12,
	0x08,0x00,0x82,0x00,0x00,0x15,
	0x00,0x00,0x15,0x20,0x00,0x11,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0xee,0xa4,0x80,0x00,0x00,0x15,
	0x00,0x5f,0x81,0x00,0x00,0x15,
	0x00,0x00,0x00,0x00,0x00,0x60,
	0x00,0x00,0x00,0x00,0x41,0x20,
	0x40,0x00,0x00,0x00,0x4a,0x00,
	0x01,0x90,0x00,0x92,0x44,0x60,
	0x59,0x56,0x56,0x01,0x40,0x1a,
	0x00,0x00,0x14,0x00,0x00,0x11,
	0x00,0x18,0x00,0x93,0x40,0x50,
	0x00,0x18,0x00,0x93,0x00,0x50,
	0x00,0x2d,0x36,0x01,0x40,0x3a,
	0x00,0x00,0x00,0x06,0x43,0xa9,
	0x01,0x40,0x00,0x00,0xc4,0x20,
	0x59,0x56,0x56,0x01,0x40,0x1a,
	0x00,0x00,0x14,0x00,0x00,0x11,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x00,0x00,0x00,0x00,0x10,
	0x00,0x00,0x00,0x06,0x42,0xa9,
	0x01,0x83,0x00,0x02,0x44,0x20,
	0x59,0x56,0x56,0x01,0x40,0x1a,
	0x20,0x00,0x82,0x00,0x00,0x15,
	0x00,0x00,0x15,0x20,0x00,0x11,
	0x00,0x10,0x82,0x00,0x00,0x15,
	0x00,0x00,0x15,0x20,0x00,0x11,
	0x00,0x10,0x82,0x00,0x00,0x15,
	0x00,0x00,0x15,0x20,0x00,0x11
};
