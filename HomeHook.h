/**************************************************
***	Project Title: Super Start (sstart)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
*** Platforms:	TI-89, TI-92p, V200				***
*** Supported Hardware Revisions: 1, 2			***
***	Description: An Application designed to		***
*** 			 Simplify the launching of ppg	***
***				 programs as well as normal		***
***				 asm programs					***
***************************************************/
/*
    This file is part of Super Start.

    Super Start is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    
    You may use portions of this source code for your own projects
    if you give me credit and a link to my website: http://calc.gregd.org/
    
*/

#ifndef _HOME_HOOK_H_
#define _HOME_HOOK_H_ 

	BOOL InstallHook(void);
	BOOL RemoveHook(void);
	void HomeHook(pFrame self, PEvent e);
	
	BOOL CanDelete(AppID self);		//this should probabbly be called from a CanDelete function in sstart.c if there are more hooking options added
#endif
