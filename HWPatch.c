/**************************************************
***	Project Title: Super Start (sstart)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
*** Platforms:	TI-89, TI89T, TI-92p, V200		***
*** Supported Hardware Revisions: 1, 2, 3		***
***	Description: An Application designed to		***
*** 			 Simplify the launching of ppg	***
***				 programs as well as normal		***
***				 asm and TI-BASIC programs		***
***************************************************/
/*
    This file is part of Super Start.

    Super Start is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	You may use portions of the Super Start source code for your own projects
	if you give me credit and a link to my website: http://calc.gregd.org/ 
	in the project source code and documentation.
    
*/

#include <tiams.h>
#include "HWPatch.h"

//#define addr_EX_stoBCD ((char *)AMS_Global_Variables[0xC0])

/*
BOOL h220xtsrInstalled(void)
{		
	switch(*(unsigned long*)(*(unsigned long*)0xAC-8))
	{
		case 0x32547372:	//#'2Tsr' (new signature)
		case 0x32545352:	//#'2TSR' (old signature)
			return TRUE;
		break;
		
		default:
			return FALSE;		
	}
}

BOOL HW2PatchInstalled(void)
{
Access_AMS_Global_Variables;

  register unsigned long *ptr;
  
  if (*(unsigned long *)0xAC == 0x100) return HW2_Patch_RAM;
  
  ptr = (unsigned long *)((addr_EX_stoBCD)+0x52);
  
  //if (ptr[0]!=0x700000) return HW2_Patch_ROM;
  if (ptr[1]!=0x36BCFFDF) return HW2_Patch_ROM;
  
  return HW2_Patch_None;
}

*/

//thanks to ExtendeD for this ;)
void enter_ghost_space(void * address) {
asm(
	" movem.l  a3/d3/d7,-(sp)\n" // 4
	" movea.l  16(sp),a3\n" // 4
	" move.l   (0xC8).w,-(a7)\n"	// 4
	" lea      -0x10(a7),a7\n" // 4
	" moveq    #0xF,d3\n" // 2
	" trap     #11\n" // 2
	" lea      0x14(a7),a7\n" // 4
	" movem.l  (sp)+,a3/d3/d7\n", // 4
	28); //it doesn't really matter if we get the exact length of the asm
		//instruction correct - but make sure the given length is >= the actual length
}
