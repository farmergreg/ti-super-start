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

#include <tiams.h>
#include "sstart.h"
#include "Resources.h"
#include "oo.h"
#include "HomeHook.h"
#include "appExt.h"
 
////////////////////////////////////////////////////
//static function prototypes                    ///
//////////////////////////////////////////////////
static void appExtHelp(AppID self, USHORT strnum);
static void Event_Handler(pFrame self, PEvent e);
static void DoFormatsDialog(void);

///////////////////////////////////////
//////////////////////////////////////

#define FRAME_SIZE (11 + NUM_OO_ATTRIBS)
    
APP_EXTENSION const appExtensions[NUM_EXTENSIONS]={
//		func name #, 						help string # 						func index
	{OO_FIRST_APP_STRING + XR_About,	OO_FIRST_APP_STRING + XR_st_About,		EXT_ABOUT},
	{OO_FIRST_APP_STRING + XR_sstart,	OO_FIRST_APP_STRING + XR_st_sstart,		EXT_SSTART},
};

//APP_EXT_PROGRAM
//APP_EXT_FUNCTION
APP_EXT_ENTRY const appExtEntries[NUM_EXTENSIONS]={
//		&Function(),		type

	{ext_ABOUT,		APP_EXT_PROGRAM},
	{ext_SSTART,	APP_EXT_FUNCTION},
};

FRAME(appObj2, OO_SYSTEM_FRAME, 0, OO_APP_FLAGS, FRAME_SIZE)
	ATTR(OO_APP_FLAGS, 					APP_INTERACTIVE) 				//0x0001
	ATTR(OO_APP_NAME, 					"Super Start")                  //0x0002
	ATTR(OO_APP_TOK_NAME, 				"sstart")						//0x0003
	ATTR(OO_APP_PROCESS_EVENT, 			&Event_Handler)                 //0x0004
	ATTR(OO_APP_EXT_COUNT, 				NUM_EXTENSIONS)					//0x0007
	ATTR(OO_APP_EXTENSIONS, 			appExtensions)					//0x0008
	ATTR(OO_APP_EXT_ENTRIES, 			appExtEntries)					//0x0009
	ATTR(OO_APP_CAN_DELETE,				CanDelete)						//0x000C
	ATTR(OO_APP_ICON,					&AppIcon)						//0c000F
	ATTR(OO_APP_EXT_HELP,				appExtHelp)						//0x0010
	ATTR(OO_APP_ABOUT,					About)							//0x0012
		
//App Data Interface      
	ATTR(OO_TTUNPACK,					gTT_UNPACK)						//0x10000
    
ENDFRAME
 
STRING_FRAME(appObj, OO_SYSTEM_FRAME, &appObj2, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
//App ext extension help strings
	"about",														//XR_About
	"Shows the Super Start About Screen",							//XR_st_About
	"About()\nShows the Super Start About Screen",					//XR_msg_About
	
	"sstart",														//XR_sstart
	"launch a ppg or ASM program",									//XR_st_sstart
	"sstart(\"prgm\",[arg1],...)\n\nThis command launches a ppg or ASM program.\nThe first argument 'prgm' must be supplied and be a valid variable which has the type 'ASM' or 'ppg' as shown in the Var-Link.",		//XR_msg_sstart
	
//Application Strings   
	"Super Start",					//XR_ShortAppName
	"Super Start v" APP_VERSION,	//XR_LongAppName
	"Super Start v" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nBy: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\nhttp://calc.gregd.org",	//XR_About_Me
	"You cannot delete Super Start while the Home Screen is active! Please switch to another application such as the Y= Editor before removing Super Start.",					//XR_Fail_HS_Active
	"sstart.",						//XR_SSTART_EXT			this string must be consistent with the OO_APP_TOK_NAME frame entry
	"sstart(\"",					//XR_SSTART_MINIMAL		this string must be consistent with the OO_APP_TOK_NAME frame entry
	"\0sstart",						//XR_SSTART_TOK			this string must be consistent with the OO_APP_TOK_NAME frame entry
	"decompressing...",				//XR_Decompressing
	"Auto Start",
	"Leak Watch",
	"Leak Watch Report",			//XR_LeakWatchTitle
	
//Application Error Strings
	"As a minimum, you must specify the ASM or ppg program that you wish to launch. Example: sstart(\"tetris\")",				//ER_TOO_FEW_ARGS
	"You must place quotation marks around the name of the program that you wish to launch. Example: sstart(\"tetris\")",		//ER_EXPECTED_STRING_ARG	
ENDFRAME

//////////////////////////////////////////////////
//Application Data Section					  ///
////////////////////////////////////////////////

/* Pointer to the Frame object */
	pFrame pAppObj = (pFrame)&appObj;  /* Must be the first global variable declared! */

//This is a bitmap structure, NOT an icon as suggested by the FRAME entry
const short AppIcon[]={
	0x0013,	//Num Rows	/\
	0x0010,	//Num Cols	<->
	//icon data
	0xF01F, 0x683F, 0x681F, 0x701F, 0x600F, 0x6782, 0xF340, 0x0340, 0x0380,
	0x0300, 0x0300, 0x0780, 0x003A, 0x4066, 0xF060, 0xF860, 0xF86F, 0xFC66,
	0xF83C
};


//16x16 Detached Solutions BITMAP
const short GForceIcon[]={
	0x000e,
	0x0010,
	0x1F30, 0x37E0, 0x68E0, 0x50C0, 0xD800,
	0xD800, 0xDFF0, 0xDFE0, 0xD0E0, 0x70E0,
	0x70E0, 0x38E0, 0x1FF0, 0x3FF8,
};

const UCHAR cmd_post_app_id[]="CMDPOST";

ULONG gSettings;

//yes, this is THE primary event loop!
//not much to it eh? :)
static void Event_Handler(pFrame self, PEvent e)
{
	Access_AMS_Global_Variables;
	
	CheckAMS(pAppObj, 2, 4);
	
	switch (e->command)
	{
		case CM_INSTALL:
			gSettings=0x00020001UL;			
		case CM_UNPACK:
			if(!gSettings)gSettings=OO_appGetPublicStorage();
			
			if(AutoStartInstalled())
				InstallHook();

			break;
			
		case CM_ACTIVATE:
			DoFormatsDialog();
			EV_quit();	//quit now - there is no interactive interface beyond the settings dialog
			break;
			
		case CM_PACK:
		case CM_UNINSTALL:
			if(AutoStartInstalled())
				RemoveHook();
			
		//because of the double usage of the public storage space, we need to make sure we
		//do this step last so the RemoveHook function can do its job properly.
			OO_appSetPublicStorage(gSettings);
			break;
		
		default:
  			EV_defaultHandler(e);
  			break;
  	};
}

static void DoFormatsDialog(void)
{
	ULONG oldsettings=gSettings;
		
	switch(Dialog(&dlgFormats, -1, -1, NULL, (WORD*)&gSettings))
	{	
	//if enter is pressed, then accept the user's input
		case KB_ENTER:
			if(AutoStartInstalled() && AutoStartMask(oldsettings)==PUP_OFF)
				InstallHook();
				
			if(!AutoStartInstalled() && AutoStartMask(oldsettings)==PUP_ON)
				RemoveHook();
		
			break;
	//otherwise, restore the previous values
		//case DB_MEMFULL:
			//EV_errorCode=ER_MEMORY;	//because the dialog is a resource, and stored in the flash, this error should never happen.
		default:
			gSettings=oldsettings;
			break;
	};
}

BOOL cbFormatsDialog(WORD dlgId, DWORD dValue)
{
	if(dlgId==DB_QACTIVE && dValue==1)	return EV_getAppID(cmd_post_app_id);	//disable the option if Command Post is not installed
	
	return TRUE;
}


//Implements the About Screen and About Frame Attribute about string
char* About(void)
{//This app may not be active when this function is called, so use
//a lookup method that will not fail
	Access_AMS_Global_Variables;
	EStackIndex top=top_estack;	
	push_quantum(END_TAG);	//ext_ABOUTRC is fussy if it precieves any arguments
	ext_ABOUT();
	top_estack=top;

	return OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_About_Me);
}

static void appExtHelp(AppID self, USHORT strnum)
{
	DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName), 
				OO_AbsoluteGet((OO_FIRST_APP_STRING + OO_FIRST_APP_STRING+2) + strnum*3));
}

