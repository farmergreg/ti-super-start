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

#include "tiams.h"
#include "sstart.h"

DIALOG dlgFormats, 0, 0, cbFormatsDialog
{
	POPUP,		{DF_TAB_ELLIPSES,   	12, 14+(0*12)},		XR_AUTO_COMPLETE,	pupOnOff,			0	//last num is index in the array
	POPUP,		{DF_TAB_ELLIPSES,		12,	14+(1*12)},		XR_LEAK_WATCH,		pupOnOff,			1	//last num is index in the array
	HEADER,		{0, 					0,	0}, 			XR_LONG_APP_NAME, 	PDB_OK, PDB_CANCEL
}

POPUP pupOnOff, 0, 0
{
	XR_ON,		PUP_ON=2	//subtract one, or let be to get true
	XR_OFF,		PUP_OFF=1	//subtract one to get false
}
