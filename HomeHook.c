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
#include "HomeHook.h"
#include "HWPatch.h"
#include "oo.h"



#define addr_HomeExecute ((char *)AMS_Global_Variables[0x10E])
#define addr_TE_select ((char *)AMS_Global_Variables[0xB1])

#define SymFindPtr tiamsapi_643
SYM_ENTRY * tiamsapi_643(char* ptr, short flags);

static void AutoStart(BOOL IgnoreAsmPrgmSize);
static TERecord *TE_findHomeScreen(void);


//the target app id
static const UCHAR ti_home[]="TIHOME";

FRAME(HookFrame, OO_SYSTEM_FRAME, 0, OO_APP_PROCESS_EVENT, 1)
	ATTR(OO_APP_PROCESS_EVENT, 		&HomeHook)					//0x0004
ENDFRAME

BOOL InstallHook(void)
{
	pFrame RetFrame;
	OO_InstallAppHook(EV_getAppID(ti_home), (pFrame)&HookFrame, &RetFrame);
	OO_appSetPublicStorage(RetFrame);
}

BOOL RemoveHook(void)
{
	OO_UninstallAppHook(EV_getAppID(ti_home), OO_appGetPublicStorage());
}

BOOL CanDelete(AppID self)
{
	Access_AMS_Global_Variables;
	
	if(EV_runningApp==EV_getAppID(ti_home) && AutoStartInstalled())
	{
		DlgNotice(OO_AbsoluteGet(XR_LongAppName + OO_FIRST_APP_STRING), OO_AbsoluteGet(XR_Fail_HS_Active + OO_FIRST_APP_STRING));
		return FALSE;
	}

	return TRUE;
}


void HomeHook(pFrame self, PEvent e)
{
	Access_AMS_Global_Variables;
	pFrame super=OO_SuperFrame;
	
	if(e->command==CM_KEY_PRESS)
	{	
		if(e->info.keyInfo.keyCode==KB_ENTER || e->info.keyInfo.keyCode==KB_ENTER+KB_OPTION)
		{
			AutoStart(UseLeakWatch() && EV_getAppID(cmd_post_app_id));
			
			#ifdef DEBUG
				ST_helpMsg("Enter Pressed");
				ngetchx();
			#endif
		}
	}
	
	if(super) AppProcessEvent(super, e);
}

//Credits to Samuel Stearley for this hack.
//I have converted his ASM code into a C function.
//Finds the Home Screen Text Editor / Entry Line in an AMS independant manner.
static TERecord *TE_findHomeScreen(void)
{
	Access_AMS_Global_Variables;
	register char *a=addr_HomeExecute;

	while(*(unsigned long*)a!=(unsigned long)addr_TE_select)
		a+=2;

	return (TERecord*)(unsigned long)(*(unsigned short*)(a-4));
}

static void AutoStart(BOOL IgnoreAsmPrgmSize)
{
	TERecord *hste=TE_findHomeScreen();
	char tmp[30];		//1 8 1 8 1 ()
	char *ptr;
	char *ptr2;
	SYM_ENTRY *sym;
	const char PackagedTag[]={'p','p','g',0,0xF8};
	const char * const text[]={"()","\")" };
	char *HomeText=HeapDeref(hste->b.hBuf);
	int i;
	unsigned char ParenCount=1;
	
	//////////////////////////////////////////
	//begin check for function, prgm, asm, ppg programs
		//Check if the home screen text edit line isn't active so don't peform the Auto Start		
		//check the max length of an program with a path associated with it
		if(!(hste->flags&TE_FOCUSED) || hste->datlen>19 ) return;
	
	//just converting it to a TIOS style file name...
		tmp[0]=0;
		i=hste->datlen;
		
		ptr=strcpy(ptr2=(tmp+1),HomeText)+i;

	//count parenthesis and prepare ptr2 for SymFindPtr
		if((ptr2=strchr(ptr2,'(')))
		{
			if(strlen(ptr2)==1 || *(ptr2+1)==')')
			{
				if(*(ptr2+1)==')')
					ParenCount=2;

				*ptr2=0;
				ptr=ptr2;
			}
		}
		else
			ParenCount=0;
			
		if((sym=SymFindPtr(ptr,0)))
		{
			unsigned short varsize=*(unsigned short*)HeapDeref(sym->hVal);
			ptr=(char*)HToESI(sym->hVal);
			
			
			if(!memcmp(PackagedTag,ptr-4,5) || (*(unsigned char*)ptr==ASM_PRGM_TAG && (varsize>(24*1024) || IgnoreAsmPrgmSize) ))
			{						
				TE_select(hste,0,0);
	
				if(SymFind((BYTE*)OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_SSTART_TOK)+strlen(((char*)OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_SSTART_TOK))+1)+1))	//use the full app extension if there is a variable by the same name
					TE_pasteText(hste,(UCHAR*)OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_SSTART_EXT),strlen(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_SSTART_EXT)));
				
				//Paste the sstart(" text
					TE_pasteText(hste,(UCHAR*)OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_SSTART_MINIMAL),strlen(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_SSTART_MINIMAL)));
				
				TE_select(hste,hste->datlen,hste->datlen);
				TE_pasteText(hste,(UCHAR*)text[1], 2);	//paste the terminating ")
			}
			else if(*(unsigned char*)ptr==USER_DEF_TAG || (*(unsigned char*)ptr==ASM_PRGM_TAG))	//&& varsize<=(24*1024)
			{
				TE_select(hste,hste->datlen,hste->datlen-ParenCount);
				TE_pasteText(hste,(UCHAR*)text[0], 2);
			}
		}
}
