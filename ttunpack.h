/******************************************************************************
*
* project name:    TIGCC Tools Suite
* file name:       ttunpack.h
* initial date:    01/02/2001
* author:          thomas.nussbaumer@gmx.net
*
* description:     defines for exepack functionalities including unpack routine
*                  (complete rewrite of TIGCC Tools Suite header file)
*
* $Id: ttunpack.h,v 1.4 2002/03/28 21:17:28 tnussb Exp $
*
******************************************************************************/
#ifndef __TTUNPACK_H__
#define __TTUNPACK_H__

typedef struct {
    unsigned char  osize_lo;   // original size lowbyte
    unsigned char  osize_hi;   // original size highbyte
    unsigned char  magic1;     // must be equal to TTUNPACK_MAGIC1
    unsigned char  magic2;     // must be equal to TTUNPACK_MAGIC2
    unsigned char  csize_lo;   // compressed size lowbyte
    unsigned char  csize_hi;   // compressed size lowbyte
    unsigned char  esc1;       // escape >> (8-escBits)
    unsigned char  notused3;
    unsigned char  notused4;
    unsigned char  esc2;       // escBits
    unsigned char  gamma1;     // maxGamma + 1
    unsigned char  gamma2;     // (1<<maxGamma)
    unsigned char  extralz;    // extraLZPosBits
    unsigned char  notused1;
    unsigned char  notused2;
    unsigned char  rleentries; // rleUsed
} TTUNPACK_HEADER;

#define TTUNPACK_MAGIC1 0x54
#define TTUNPACK_MAGIC2 0x50

#define ttunpack_size(_p_)  ((unsigned short)(((TTUNPACK_HEADER*)(_p_))->osize_lo | (((TTUNPACK_HEADER*)(_p_))->osize_hi << 8)))
#define ttunpack_valid(_p_) (((TTUNPACK_HEADER*)(_p_))->magic1 == TTUNPACK_MAGIC1 && ((TTUNPACK_HEADER*)(_p_))->magic2 == TTUNPACK_MAGIC2)

#define TTUNPACK_OKAY             0
#define TTUNPACK_NOESCFOUND     248
#define TTUNPACK_ESCBITS        249
#define TTUNPACK_MAXGAMMA       250
#define TTUNPACK_EXTRALZP       251
#define TTUNPACK_NOMAGIC        252
#define TTUNPACK_OUTBUFOVERRUN  253
#define TTUNPACK_LZPOSUNDERRUN  254


#endif

//=============================================================================
// Revision History
//=============================================================================
//
// $Log: ttunpack.h,v $
// Revision 1.4  2002/03/28 21:17:28  tnussb
// project name in header changed to TIGCC Tools Suite
//
// Revision 1.3  2002/03/13 15:09:58  tnussb
// new exepack decompression function generated from old/unpack.c added
// (its a little bit smaller now). The new function should work as the old one,
// but if there are problems I will leave the old hexcode array here, too
//
// Revision 1.2  2001/02/05 20:33:01  Thomas Nussbaumer
// (1) magic of ttunpack header splitted again into 2 bytes to prevent address errors
// (2) new (stable?) pc-relative version of unpacking routine
//
//


 