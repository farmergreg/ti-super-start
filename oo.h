/**************************************************
***	Project Title: Super Start (sstart)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
*** Platforms:	TI-89, TI-92p, V200				***
*** Supported Hardware Revisions: 1, 2			***
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

#ifndef __OO_H__
#define __OO_H__

//Application Frame Object Attribute Data Slots
enum OO_FRAME_SLOTS {
	OO_TTUNPACK=OO_FIRST_APP_ATTR,
	OO_AMS_OK,	//This is a special hook which allows Super Start to run on AMS 2.00 - 2.04 if this attribute has a value
	LAST_OO_ATTR
	};

#define FIRST_OO_ATTR	(OO_TTUNPACK)
#define NUM_OO_ATTRIBS (LAST_OO_ATTR-FIRST_OO_ATTR)


//Public Function Prototypes
AppID GetMyAppID(void);
void *OO_AbsoluteGet(ULONG selector);
BOOL OO_AbsoluteSet(ULONG selector, void *value);

#endif
