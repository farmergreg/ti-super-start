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
#include "sstart.h"
#include "oo.h"


//used when this application is not active to retrieve attributes
AppID GetMyAppID(void)
{
	return EV_getAppID((const UCHAR*)APP_INTERNAL);
}

//retrieves an attribute from this applications frame under nearly any circumstance
void *OO_AbsoluteGet(ULONG selector)
{
	return OO_GetAppAttr(GetMyAppID(), selector);
}

/*
BOOL OO_AbsoluteSet(ULONG selector, void *value)
{
	return OO_SetAppAttr(GetMyAppID(), selector, value);
}
*/
