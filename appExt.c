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
#include "sstart_export.h"

#ifndef EX_patch
	#define EX_patch tiamsapi_346
	void tiamsapi_346(char *base_addr, char *tag_ptr);
#endif

//This is a highly optimized version of ttunpack
//It is taken from ttunpack.h in the zip file unpack_distro.zip
const unsigned short gTT_UNPACK[291] = {
0x48e7,0x1f3e,0x2c6f,0x002c,0x2a6f,0x0030,0x47ee,0x000f,0x7a00,0x1a2e,
0x0006,0x7e08,0x7004,0x0c2e,0x0054,0x0002,0x667c,0x0c2e,0x0050,0x0003,
0x6674,0x7006,0x0c2e,0x0008,0x000a,0x666a,0x0c2e,0x0080,0x000b,0x6662,
0x7007,0x7200,0x122e,0x0009,0x2801,0x5141,0x6254,0x7005,0x7200,0x122e,
0x000c,0x2241,0x5b41,0x6e46,0x7400,0x09c2,0x5342,0xe83a,0xe83d,0x7000,
0x1013,0x4df6,0x0010,0x49fa,0x003c,0x4a04,0x6604,0x49fa,0x0052,0x4fef,
0xfefc,0x244f,0x421a,0x7000,0x7207,0x7600,0x01c3,0x14c0,0x5343,0x66fa,
0x5240,0x51c9,0xfff2,0x244f,0x1c1e,0x4ed4,0x7000,0x4fef,0x0104,0x4400,
0x4cdf,0x7cf8,0x4e75,0x1ac0,0x1f06,0x301f,0x1c1e,0x1006,0xee68,0x1202,
0xc200,0xb205,0x66ec,0x558e,0x1c1e,0x9e44,0x6204,0x1c1e,0x5047,0x6100,
0x0110,0x3600,0x5340,0x6778,0x6100,0x0106,0x5200,0x662c,0x5943,0x65bc,
0x5843,0x1206,0x4841,0x1f1e,0x321f,0x121e,0x1c01,0xeea9,0x70ff,0x1001,
0x3f01,0x121f,0x41f5,0x0000,0x1018,0xd001,0x1ac0,0x51cb,0xfff8,0x4ed4,
0x5500,0x3209,0x671c,0xe368,0x7200,0x0fc1,0x5341,0xc206,0x9e49,0x620a,
0x1c1e,0x1f01,0x321f,0x1206,0x5047,0xee69,0x8041,0x7200,0x1f00,0x321f,
0x1f06,0x301f,0x1c1e,0x1006,0xee68,0x1200,0x4601,0x4681,0x41f5,0x1800,
0x1ad8,0x51cb,0xfffc,0x4ed4,0x5307,0x0f06,0x676a,0x4a07,0x6604,0x7e08,
0x1c1e,0x5307,0x0f06,0x6700,0x00c6,0x4a07,0x6604,0x7e08,0x1c1e,0x6170,
0x1600,0x6a1c,0xd603,0x5307,0x0f06,0x56c0,0x9600,0x4a07,0x6604,0x7e08,
0x1c1e,0x6158,0x5300,0x3f03,0x1e80,0x361f,0x614e,0x0c00,0x0020,0x6406,
0x1033,0x0000,0x601a,0xe708,0x1206,0x5747,0x620a,0x1c1e,0x1f01,0x321f,
0x1206,0x5047,0xee69,0x0201,0x0007,0x8001,0x1ac0,0x51cb,0xfffc,0x4ed4,
0x4a07,0x6604,0x7e08,0x1c1e,0x1f06,0x321f,0x1c1e,0x1206,0xee69,0x76ff,
0x1601,0x41f5,0x3800,0x1ad8,0x1ad8,0x4ed4,0x7000,0x3207,0x0fc0,0x5340,
0xcc00,0xbd00,0x6606,0x1016,0x4600,0x5041,0x9232,0x0000,0x0c01,0x0008,
0x6504,0x7208,0x5247,0x9e41,0x6204,0x5047,0x1c1e,0x7000,0x5301,0x6716,
0x0fc0,0x5340,0xc006,0x9e41,0x620a,0x1c1e,0x1f00,0x301f,0x1006,0x5047,
0xee68,0x03c0,0x4e75,0x4a07,0x6604,0x7e08,0x1c1e,0x1f06,0x301f,0x101e,
0x1c00,0xee68,0x1205,0x1a02,0xca00,0x4602,0xc002,0x4602,0x8001,0x1ac0,
0x4ed4};

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
	BOOL isHW3 = (FL_getHardwareParmBlock()->hardwareRevision == 2);
	
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
	if((dest=strchr(src, '(')))					*dest=0;
	if(TokenizeName(src, tokbuf)==FS_BAD_NAME)	ER_throw(ER_RESERVED);
	
	
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
		if(*(UCHAR*)dest==ASM_PRGM_TAG)
		{
			if(symptr->Flags&SF_EXTMEM)
			{//located in the archive; a copy is necessary
				h_alloc=HeapAllocHighThrow(len);
				dest=((char*)HeapDeref(h_alloc)) + (isHW3 ? 0 : 0x40000);
				memcpy(dest,src,len);
			}
			else
			{
				src += (isHW3 ? 0 : 0x40000);
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
				
				if(TT_UNPACK(MY_APP_ID(pAppObj), src, dest))	ER_throw(ER_INVALID_VAR_REF);
					
				ST_eraseHelp();
				
				if(h) {HeapUnlock(h);h=H_NULL;}	//unlock the ppg mem ASAP
				
				len-=2;
				dest+= isHW3 ? 2 : 0x40002;
			}
			else//wasnt a ppg either.. therefore we do not know how to handle it.
				ER_throw(ER_INVALID_VAR_REF);
		}
		
	// "APD crash" fix.
	/* If we are on AMS 2, we have to set the "last executed program" to somewhere
	in the last 4 KB of RAM, or else APD may crash under certain circumstances.
	The code below looks for the "last executed program" variable. That variable
	is cleared during initialization, immediately after the stack fence is set up.
	So we look for the value of the stack fence (0xDEADDEAD) in the initialization
	code and add 8 (12 if long reference) to get the wanted short pointer, which must
	then be sign-extended to an actual pointer. (The sign extension is implicit in the
	generated code, as it should be.) */
	// sstart vs. ttstart: sstart does not run on AMS 1.xx or PedroM so the extra checks are not necessary.
		{
			char *rb=(char*)(((unsigned long)*(void**)0xC8)&0xE00000);

			char *p=rb+0x12000;
			char *q=rb+0x18000;
        
        	while (p<q && *(unsigned long*)p!=0xDEADDEAD) p+=2;
			p+=2[(short *)p]?8:12;
			*(void **)(long)*(short *)p=isHW3 ? dest : (void*)0x3F000;
		}

	//unprotect the area where we want to execute the program...
		enter_ghost_space(isHW3 ? dest : (void*)0x3E000);
				
		EX_patch(dest,dest+len-1);
		asm("movem.l d0-d7/a0-a6,-(sp)\n", 4);		//this avoids bugs caused by programs not saving/restoring the registers properly
		((void(*const)(void))dest)();				//launch!
		asm(" nop\n nop\n nop\n nop\n nop\n",10);	//a way to ignore/fool the TIGCC return value hack
		asm(" movem.l (sp)+,d0-d7/a0-a6\n",4);  	//this avoids bugs caused by programs not saving/restoring the registers properly

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
	WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
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
					
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
					if(ds_pt.x0>WinWidth(&win)-16  || ds_pt.x0<0)dx=-dx;
					if(ds_pt.y0>WinHeight(&win)-16 || ds_pt.y0<0)dy=-dy;
					ds_pt.x0+=dx;	ds_pt.y0+=dy;
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
				}
			}
		}
		#endif
	

	WinEndPaint(&win);
	WinClose(&win);
}

