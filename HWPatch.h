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
// $Id$
/*
    This file is part of Super Start.

    Super Start is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	You may use portions of the Super Start source code for your own projects
	if you give me credit and a link to my website: http://calc.gregd.org/ 
	in the project source code and documentation.
    
*/

#ifndef __HWPatch_H__
#define __HWPatch_H__
/*
	BOOL HW2PatchInstalled(void);
	BOOL h220xtsrInstalled(void);
*/
	void enter_ghost_space(void *);
	
/*
	#define HW2_Patch_ROM  2
	#define HW2_Patch_RAM  1
	#define HW2_Patch_None 0

	#define CHECK_HW_PATCHED() (FL_getHardwareParmBlock()->hardwareRevision!=0 && !h220xtsrInstalled() && !HW2PatchInstalled())
*/	
#endif
