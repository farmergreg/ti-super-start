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

#ifndef _SUPER_START_H_
#define _SUPER_START_H_

#ifndef _TIAMS_H
	#error Please include tiams.h before this header file
#endif

#define TT_UNPACK(obj, src, dest) \
((unsigned short(*const)(char*,char*))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 0))(src,dest)
               
/*
	See the documentation for the FDL compiler (ghost ware) to learn how to use these functions in a project

  casting a pointer to a function is simple:
  ((return_type (* const)(parameter_1_type, parameter_2_type, ...))
*/

/*
//to make TT_UNPACK work in a tigcc project, use this:
//This requires a current version of TIGCC such as Version 0.94 Beta 19
#undef OO_GetAppAttr
#define OO_GetAppAttr _rom_call(void*,(short,unsigned long),3FC)
#undef OO_FIRST_APP_ATTR
#define OO_FIRST_APP_ATTR 0x10000


HANDLE sstart_appid=TIOS_EV_getAppID("sstart");
if(sstart_appid)
{
	TT_UNPACK(sstart_appid, src, dest);
}
else
{
 //sstart flash app not installed
}


MIN_AMS should be set to at least 205
*/

#endif
