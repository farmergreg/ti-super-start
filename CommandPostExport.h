/**************************************************
***	Project Title: Command Post (KFLASH)		***
***	Author: Greg Dietsche						***
***	Date:	07/23/2002							***
***	Description: An application designed for	***
*** use with the TI-89 and TI-92 Plus Graphing	***
*** calculators during the testing and			***
*** debugging phases of FLASH APPS and RAM      ***
*** programs									***
***************************************************/

#ifndef _COMMAND_POST_H_
#define _COMMAND_POST_H_

#ifndef _TIAMS_H
	#error Please include tiams.h before this header file
#endif

/*
//Application Frame Object Attribute Data Slots
#define OO_PROTECTION_ACTIVE	(OO_FIRST_APP_ATTR + 0)		//pointer to BOOL AntiCrashInstalled (READ ONLY/cannot/must not be overridden)
#define OO_REDIRECTED_VECT		(OO_FIRST_APP_ATTR + 1)		//pointer to long gRedirect[NUM_VECT_REDIR]
#define OO_VECTORS				(OO_FIRST_APP_ATTR + 2)		//pointer to short gVectors[NUM_VECT_SAVED]
#define OO_OLD_VECTORS			(OO_FIRST_APP_ATTR + 3)		//poitner to long old_vectors[NUM_VECT_SAVED]
#define OO_VECT_REDIR			(OO_FIRST_APP_ATTR + 4)		//(short) NUM_VECT_REDIR
#define OO_VECT_SAVED			(OO_FIRST_APP_ATTR + 5)		//(short) NUM_VECT_SAVED			
#define OO_BACKUP_VECTORS		(OO_FIRST_APP_ATTR + 6)		//void MakeExceptionVectorBackup(void);
#define OO_INSTALL_VECTORS		(OO_FIRST_APP_ATTR + 7)		//void EnableCrashProtection(void);
#define OO_UNINSTALL_VECTORS	(OO_FIRST_APP_ATTR + 8)		//void DisableCrashProtection(void);
#define OO_KERNELS				(OO_FIRST_APP_ATTR + 9)		//pointer to char * gKernels[NUM_KERNELS];
#define OO_KERNELIDS			(OO_FIRST_APP_ATTR + 10)	//pointer to USHORT *gKernelID[NUM_KERNELS]
#define OO_NUM_KERNELS			(OO_FIRST_APP_ATTR + 11)	//(USHORT)Number of Known Kernels
#define OO_LEAK_WATCH_BEGIN		(OO_FIRST_APP_ATTR + 12)	//void export_LeakWatchBegin(void);
#define OO_LEAK_WATCH_END		(OO_FIRST_APP_ATTR + 13)	//DWORD export_LeakWatchEnd(char *);
*/

/*
	See the documentation for the FDL compiler (ghost ware) to learn how to use these functions in a project

  casting a pointer to a function is simple:
  ((return_type (* const)(parameter_1_type, parameter_2_type, ...))
*/

#define LeakWatch_begin(obj) \
((void (* const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 12))()

#define LeakWatch_end(obj,a) \
((DWORD (* const)(char *))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 13))(a)

/*
//to make LeakWatch work in a tigcc project, use this:
//This requires a current version of TIGCC such as Version 0.94 Beta 19
#undef OO_GetAppAttr
#define OO_GetAppAttr _rom_call(void*,(short,unsigned long),3FC)
#undef OO_FIRST_APP_ATTR
#define OO_FIRST_APP_ATTR 0x10000

#define LeakWatch_begin(obj) \
((void (* __ATTR_TIOS__ const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 12))()

#define LeakWatch_end(obj,a) \
((DWORD (* __ATTR_TIOS__ const)(const char *))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 13))(a)

HANDLE cmdpost_appid=TIOS_EV_getAppID("CMDPOST");
if(cmdpost_appid)LeakWatch_begin(cmdpost_appid);
...Program Code Goes Here...
if(cmdpost_appid)LeakWatch_end(cmdpost_appid,"Your Program's Name");

MIN_AMS should be set to at least 205
*/

#endif
