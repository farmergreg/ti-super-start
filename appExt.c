/**************************************************
***	Project Title: Super Start (sstart)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
*** Platforms:	TI-89, TI-89T, TI-92p, V200		***
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

#include <tiams.h>
#include "sstart.h"
#include "ttunpack.h"
#include "appExt.h"
#include "oo.h"
#include "HWPatch.h"
#include "Resources.h"
#include "CommandPostExport.h"

#ifndef EX_patch
	#define EX_patch tiamsapi_346
	void tiamsapi_346(char *base_addr, char *tag_ptr);
#endif

//This is a highly optimized version of ttunpack; unfortunately, 
//the source code used to generate this array was lost.
const unsigned short gTT_UNPACK[392] = { 
0x206f,0x0004,0x226f,0x0008,0x48e7,0x010c,0x303c,0x0200,0x4e41,0x3f00,
0x6100,0x0010,0x3200,0x301f,0x4e41,0x3001,0x4cdf,0x3080,0x4e75,0x4e56,
0xfff4,0x48e7,0x1e30,0x2a09,0x0c28,0x0054,0x0002,0x6708,0x303c,0x00fc,
0x6000,0x021e,0x0c28,0x0050,0x0003,0x66f0,0x0c28,0x0008,0x000a,0x6708,
0x303c,0x00fa,0x6000,0x0206,0x0c28,0xff80,0x000b,0x66f0,0x4240,0x1028,
0x0009,0x3d40,0xfff8,0x303c,0x00f9,0x0c6e,0x0008,0xfff8,0x6200,0x01e6,
0x4240,0x1028,0x000c,0x3d40,0xfff6,0x303c,0x00fb,0x0c6e,0x0004,0xfff6,
0x6200,0x01ce,0x4240,0x1028,0x0006,0x3640,0x7008,0x906e,0xfff8,0x3d40,
0xfffa,0x43e8,0x000f,0x2d49,0xfffc,0x4fef,0xfefc,0x2a4f,0x327c,0x0001,
0x4217,0x4202,0x1002,0x4880,0x7201,0xe169,0x6f0c,0x3001,0x1b82,0x9000,
0x5249,0x5340,0x66f6,0x5202,0x0c02,0x0007,0x6fe2,0x7000,0x1028,0x000f,
0x49f0,0x0810,0x3e3c,0x0080,0x4a6e,0xfff8,0x6600,0x0162,0x380b,0xb84b,
0x6718,0x302e,0xfffa,0xe16c,0x2445,0x5285,0x3200,0x41fa,0x01c6,0x4e90,
0x8800,0x1484,0x60da,0x426e,0xfff4,0x45fa,0x016a,0x4e92,0x3c00,0x0c40,
0x0001,0x6600,0x00e2,0x4240,0x1014,0xc047,0x6700,0x00a4,0xe21f,0x6402,
0x528c,0x4240,0x1014,0xc047,0x676a,0xe21f,0x6402,0x528c,0x4e92,0x3800,
0x0c40,0x007f,0x6240,0x4e92,0x0c40,0x001f,0x6224,0x0280,0x0000,0xffff,
0x206e,0xfffc,0x1030,0x0800,0x0240,0x00ff,0x4242,0x2245,0x5285,0x12c0,
0x5242,0xb842,0x64f4,0x6000,0xff74,0x3600,0x0643,0xffe0,0xe74b,0x7203,
0x41fa,0x0148,0x4e90,0x8043,0x60da,0x0644,0xff80,0xe34c,0x7201,0x41fa,
0x0136,0x4e90,0x8840,0x4e92,0x5340,0xe148,0x8840,0x60a6,0xe21f,0x6402,
0x528c,0x47fa,0x011e,0x322e,0xfff8,0x4e93,0x3600,0x302e,0xfffa,0xe16c,
0x2445,0x5285,0x3200,0x4e93,0x8800,0x1484,0x3643,0x6000,0xff1c,0xe21f,
0x6402,0x528c,0x41fa,0x0094,0x4e90,0x3200,0x0a41,0x00ff,0x4242,0x7000,
0x3001,0x2045,0x91c0,0x102e,0xfff5,0xd028,0xffff,0x2245,0x5285,0x12c0,
0x5242,0xbc42,0x64e4,0x6000,0xfee8,0x4e92,0x3600,0x5343,0x0c43,0x00fe,
0x672a,0x4a6e,0xfff6,0x6612,0x41fa,0x0054,0x4e90,0x3200,0x0a41,0x00ff,
0xe14b,0x8243,0x60ba,0x302e,0xfff6,0xe16b,0x3200,0x41fa,0x009a,0x4e90,
0x8640,0x60dc,0x0c46,0x0003,0x630e,0x45fa,0x002a,0x4e92,0x3d40,0xfff4,
0x4e92,0x608e,0x4240,0x6010,0x322e,0xfff8,0x41fa,0x0074,0x4e90,0x3800,
0x6000,0xfe94,0x4cee,0x0c78,0xffdc,0x4e5e,0x4e75,0x101c,0xe148,0x1014,
0x1235,0x7000,0x5201,0xe268,0x0240,0x00ff,0x4e75,0x3407,0x1014,0xc400,
0x673c,0xd402,0x5302,0x1235,0x7000,0xc002,0xb102,0x6608,0x142c,0x0001,
0x4602,0x5001,0x9235,0x2000,0x1401,0x5202,0x0c01,0x0007,0x6504,0x7207,
0x7407,0x3007,0xe43f,0xbe00,0x6502,0x528c,0x6100,0x0010,0x5201,0x03c0,
0x4e75,0x7001,0xe21f,0x6526,0x4e75,0x7000,0x5301,0x6520,0x6732,0x3007,
0xe23f,0xbe00,0x6518,0xd040,0x5340,0xc01c,0xe148,0x1014,0x1435,0x7800,
0xe468,0xe21f,0x6402,0x528c,0x4e75,0xd040,0x5340,0xc014,0x1435,0x7800,
0xe428,0xe21f,0x65ec,0x4e75,0x1014,0xc007,0x56c0,0x0200,0x0001,0xe21f,
0x65dc,0x4e75};

void ext_SSTART(void)
{
	Access_AMS_Global_Variables;
	char *src, *dest;	//these play a dual role (get program name, and pointers to program data later on)
	BYTE tokbuf[MAX_SYM_LEN];
	SYM_ENTRY *symptr;
	USHORT len;
	volatile HANDLE h;					//handle to the program's data
	volatile HANDLE h_alloc=H_NULL;		//handle allocated by this program
	EStackIndex tmp_index;
	CONTROL_BITS savedctrl;
	HANDLE cmd_post;
	ULONG hardwareRevision = FL_getHardwareParmBlock()->hardwareRevision;
	
	if(JT_VERSION_CHECK())	return;	//don't run if the JT_VERSION flag is set... this should be done for all TI-BASIC Extensions!
	
	if(UseLeakWatch() && (cmd_post=EV_getAppID(cmd_post_app_id)))
	{
		LeakWatch_begin(cmd_post);
	}
	
	savedctrl=NG_control;
	SET_SIDE_EFFECTS_PERMITTED;
	
	if(!remaining_element_count(top_estack))	ER_throwFrame(ER_TOO_FEW_ARGS, pAppObj);		//ER_throw(TOO_FEW_ARGS_ERROR);

//the TIOS does not simplify input for us... so we do it by replacing the top value with the simplified version of it.
//this will allow people to use sstart in the exact same way as ttstart.
//For Example, Basic programmers will be able to write "tetris"->x:sstart(x) 	
	push_simplify(top_estack);
		
	if(ESTACK(top_estack)!=STR_DATA_TAG)		ER_throwFrame(ER_EXPECTED_STRING_ARG, pAppObj);	//ER_throw(ER_ARG_MUST_BE_STRING);
	
	tmp_index=next_expression_index(top_estack);
	src=(char*)tmp_index+2;	//pointer to the variable name of the program to be launched
//we only want the program NAME - so ignore parenthesis, and anything that follows them
	if((dest=strchr(src, '(')))*dest=0;
	if(TokenizeName(src, tokbuf)==FS_BAD_NAME)				ER_throw(ER_RESERVED);
	
	
//this is important because the TIOS expects any return values to be at the original top_estack.
	top_estack=tmp_index;
	tmp_index=next_expression_index(tmp_index);
	PUSH_QUANTUM_NOCHECK(END_TAG);	//TIGCC programs _should_ destroy the estack up to the first END_TAG that it encounters if they returns a value.
//copy any passed arguments over for the launched program to use
	while(remaining_element_count(tmp_index))	//copy each argument (if any)
	{
		push_simplify(tmp_index);					//for whatever reason, TI-BASIC FLASH extensions don't get the simplified expression so we simplify it here...
		tmp_index=next_expression_index(tmp_index);
	}

	tmp_index=top_estack;
	
//try to find the variable in question
	if(!(symptr=DerefSym(SymFind(TokNameRight(tokbuf)))))	ER_throw(ER_UNDEFINED_VAR);
	
	h=symptr->hVal;
    dest=(char*)HToESI(h);
    
	if(HeapGetLock(h))
	{
		src=HeapDeref(h);
		h=H_NULL;
	}
	else
		src=HLock(h);

	len=*(USHORT*)src;
	src+=2;
		
	TRY	
		if(*(UCHAR*)dest==ASM_PRGM_TAG && hardwareRevision < 2)
		{
			if(symptr->Flags&SF_EXTMEM)
			{//located in the archive; a copy is necessary
				h_alloc=HeapAllocHighThrow(len);
				dest=((char*)HeapDeref(h_alloc)) + ((hardwareRevision == 2) ? 0 : 0x40000);
				memcpy(dest,src,len);
			}
			else
			{
				src = src + ((hardwareRevision == 2) ? 0 : 0x40000);
				dest = src;
			}
		}
		else
		{//not an asm tag, so what is it?
			len=ttunpack_size(src);
			h_alloc=HeapAllocHighThrow(len);
			
			if(*(UCHAR*)dest==GEN_DATA_TAG && *(dest-4)=='p' && *(dest-3)=='p' && *(dest-2)=='g')
			{
				dest=(char *)HeapDeref(h_alloc);

				ST_helpMsg(OO_AbsoluteGet(OO_FIRST_APP_STRING+XR_Decompressing));
				
				if(((unsigned short(*const)(char*,char*))gTT_UNPACK)(src,dest))			ER_throw(ER_INVALID_VAR_REF);
					
				ST_eraseHelp();
				
				if(h) {HeapUnlock(h);h=H_NULL;}	//unlock the ppg mem ASAP
				
				len-=2;
				dest+= (hardwareRevision == 2) ? 2 : 0x40002;
			}
			else//wasnt a ppg either.. therefore we do not know how to handle it.
				ER_throw(ER_INVALID_VAR_REF);
		}


	//unprotect the area where we want to execute the program...
		enter_ghost_space(((hardwareRevision == 2) ? dest : (void*)0x3E000));
		
		// "APD crash" fix.
		/* If we are on AMS 2, we have to set the "last executed program" to somewhere
		in the last 4 KB of RAM, or else APD may crash under certain circumstances.
		The code below looks for the "last executed program" variable. That variable
		is cleared during initialization, immediately after the stack fence is set up.
		So we look for the value of the stack fence (0xDEADDEAD) in the initialization
		code and add 8 (12 if long reference) to get the wanted short pointer, which must
		then be sign-extended to an actual pointer. (The sign extension is implicit in the
		generated code, as it should be.) */
		// sstart vs. ttstart: sstart does not run on AMS 1.xx or PedroM so the checking for that is not necessary.
		{
			char *rb=(char*)(((unsigned long)*(void**)0xC8)&0xE00000);

			char *p=rb+0x12000;
			char *q=rb+0x18000;
        
        	while (p<q && *(unsigned long*)p!=0xDEADDEAD) p+=2;
			p+=2[(short *)p]?8:12;
			*(void **)(long)*(short *)p=(hardwareRevision == 2) ? dest : (void*)0x3f000;
		}
				
		EX_patch(dest,dest+len-1);
		asm("movem.l d0-d7/a0-a6,-(sp)\n", 4);	//this avoids bugs caused by programs not saving/restoring the registers properly
		((void(*const)(void))dest)();				//launch!
		asm(" nop\n nop\n nop\n nop\n nop\n",10);	//a way to ignore/fool the TIGCC return value hack
		asm(" movem.l (sp)+,d0-d7/a0-a6\n",4);  //this avoids bugs caused by programs not saving/restoring the registers properly

			#ifdef DEBUG
			{
				char buff[100];
				sprintf(buff,"0x%lx 0x%lx",top_estack,tmp_index);
				ST_helpMsg(buff);
				ngetchx();
			}
			#endif
			
			//slighly more forgiving than remaining_element_count
			//this allows programs to destroy more of the estack than they should without causing
			//problems for Super Start.
			if(top_estack<=tmp_index)	//if(!remaining_element_count(top_estack))
			{
				top_estack=tmp_index;
				push_zstr(XR_stringPtr(XR_Done));
			}
			
	FINALLY
		if(h)HeapUnlock(h);
		HeapFreeIndir((HANDLE *)&h_alloc);

		NG_control=savedctrl;
		
		if(UseLeakWatch() && (cmd_post=EV_getAppID(cmd_post_app_id)))
		{
			LeakWatch_end(cmd_post, OO_AbsoluteGet(OO_FIRST_APP_STRING+XR_LeakWatchTitle));
		}			
	ENDFINAL		
}

void ext_ABOUT(void)
{
	Access_AMS_Global_Variables;
	const WIN_RECT wRegion={C(10, 30), C(4, 6), C(MAX_X-10, 215), C(85, 113)};
	WINDOW win;
	WIN_POINT ds_pt={4,1};
	WIN_POINT post_pt;
	
	#ifndef NO_EASTER_EGGS
		short leet_user=FALSE;
		short key_code='x';//initialize it with something other than a valid key...
	#endif
	
	if(JT_VERSION_CHECK())	return;	//don't run if the JT_VERSION flag is set... this should be done for all TI-BASIC Extensions!
	
	if(remaining_element_count(top_estack)) ER_throw(TOO_MANY_ARGS_ERROR);
	
	if(!WinOpen(&win, &wRegion, WF_SAVE_SCR|WF_TTY|WF_TITLE|WF_ROUNDEDBORDER, XR_stringPtr(XR_ABOUT)))
		ER_throw(ER_MEMORY);
	
	WinBeginPaint(&win);
	
	#ifdef _89
		WinFont(&win, F_4x6);
	#endif
	
	post_pt.x0=WinWidth(&win)-4-((BITMAP*)AppIcon)->NumCols;
	post_pt.y0=1;
	
	WinClr(&win);
	WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)GForceIcon, A_XOR);
	WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
	
	WinMoveTo(&win,33,7);
	WinStr(&win, (char*)OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_About_Me));//About());
	DrawStaticButton(&win, PDB_OK, 5);
	
	#ifdef NO_EASTER_EGGS
		while(KeyYesOrNo(GKeyIn(NULL, GKF_MODAL | GKF_SYS))==-1);
	#else
		while(KeyYesOrNo(key_code)==-1)
		{
			key_code=GKeyIn(NULL, GKF_MODAL | GKF_SYS);
			if(key_code==(0x31337-(0x12F0|0x30000)) && !leet_user)	//$r3 j00 1 31337 H4X0R G
			{
				short dx=1, dy=1, steps;
				
				leet_user=TRUE;
				
				for(steps=0;steps<C(105,210);steps++)
				{
				#ifdef _92
					if(steps<155)
					{
				#endif
						WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
						post_pt.x0--;
						WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
				#ifdef _92
					}
					else
					{
						short delay;
						for(delay=0;delay<5000;delay++);
					}
				#endif
					
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)GForceIcon, A_XOR);
					if(ds_pt.x0>WinWidth(&win)-16  || ds_pt.x0<0)dx=-dx;
					if(ds_pt.y0>WinHeight(&win)-16 || ds_pt.y0<0)dy=-dy;
					ds_pt.x0+=dx;	ds_pt.y0+=dy;
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)GForceIcon, A_XOR);
				}
			}
		}
		#endif
	

	WinEndPaint(&win);
	WinClose(&win);
}

