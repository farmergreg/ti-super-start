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

#ifndef _SUPERSTART_H_
#define _SUPERSTART_H_

//Version Control and Internal/External App Name
#define APP_VERSION "1.30"
#define APP_INTERNAL "sstart"

//#define DEBUG			//enable extra debugging code

#ifndef _89
#ifndef _92
	#error Please '#define _89' or '#define _92'
#endif
#endif

#ifdef _89
#ifdef _92
	#error '#define _89' and '#define _92' are mutually exclusive
#endif
#endif

#ifdef _89
	#define C(x,y)(x)
#endif
#ifdef _92
	#define C(x,y)(y)
#endif

/*
//My own debuged replacment for TI's OS_NeedMinimumVersion macro
//This Macro will mark the application for immediate removal if
//the AMS version is too low.
#define CheckAMS(frame, major, minor)								\
{																	\
   static BOOL _OSVersionOK_ = FALSE;								\
   if (! _OSVersionOK_)												\
   {																\
      if (((long const *)AMS_Global_Variables)[-1] < 1499 ||		\
          ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number	\
            < (((major) << 8) + (minor)))							\
         {															\
            MY_ACB(frame)->flags |= (ACB_JT_VERSION|ACB_DELETE);	\
            return;													\
         }															\
      else															\
         _OSVersionOK_ = TRUE;										\
   }																\
}
*/
      
//This header requires certain other header files
#include "xr.h"		//technically part of this header file; isolated for ease of editing

BOOL cbFormatsDialog(WORD dlgId, DWORD dValue);
char* About(void);

extern pFrame pAppObj;
extern const short AppIcon[];
extern const short GForceIcon[];
extern const UCHAR cmd_post_app_id[];
extern const UCHAR ti_home[];


typedef struct SSETTINGS{
	WORD AutoStart;
	WORD LeakWatch;
}SETTINGS;

extern SETTINGS gSettings;

//#define AutoStartMask(val) ((val&0xFFFF0000)>>16)
//#define LeakWatchMask(val) (val&0x0000FFFF)

//#define AutoStartInstalled() (AutoStartMask(gSettings)==PUP_ON)
#define AutoStartInstalled() (gSettings.AutoStart==PUP_ON)
//#define UseLeakWatch()	(LeakWatchMask(gSettings)==PUP_ON)
#define UseLeakWatch() (gSettings.LeakWatch==PUP_ON)

#endif
