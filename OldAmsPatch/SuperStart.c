// $Id$
// C Source File
// Created 7/21/2003; 1:16:55 AM
//Super Start Patch Program by Greg Dietsche
//Running this program on a calculator running AMS 2.00 - 2.03
//will bypass Super Start's error checking and allow Super Start
//to function normally. Prior to running this program, you MUST
//have Super Start installed and you MUST install a line 1111
//emulator such as the ones found in KerNO and PreOS.
//
//Modified by Lionel Debroux: changed the code to prevent the
//crash if Super Start is not installed (!); added
//NO_CALC_DETECT; added a simple check for a custom F-Line
//handler such as the one in KerNO or PreOS.

#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

#define NO_EXIT_SUPPORT       // This program never uses exit() to terminate
#define NO_CALC_DETECT        // Detecting the calc is useless
#define ENABLE_ERROR_RETURN   // Enable Returning Errors to AMS
#define OPTIMIZE_ROM_CALLS    // Use ROM Call Optimization
#define MIN_AMS 200           // Compile for AMS 2.00 or higher
#include <tigcclib.h>         // Include All TIGCC Header Files

#ifndef MAX_APPLET_NAME_SIZE
	#define MAX_APPLET_NAME_SIZE (8)
#endif
#ifndef AppID
	typedef HANDLE AppID;
#endif
#ifndef AppHdr
	#ifndef SAppHdr
		typedef struct SAppHdr
		{
		   ULONG magic;
		   UCHAR name[MAX_APPLET_NAME_SIZE];
		   BYTE  zeros[24];
		   USHORT flags;
		   ULONG dataLen;
		   ULONG codeOffset;
		   ULONG initDataOffset;
		   ULONG initDataLen;
		   ULONG optlen;
		} AppHdr;
	#endif
#endif
#ifndef ACB_Flags
	typedef enum
	{
	   ACB_BUILTIN   =0x0001,
	   ACB_INSTALLED =0x0002,
	   ACB_LOCALIZER =0x0004,
	   ACB_LOCK      =0x0008,
	   ACB_JT_VERSION=0x0010,
	   ACB_SELECTED  =0x0020,
	   ACB_COLLAPSE  =0x0800,
	   ACB_BG        =0x1000,
	   ACB_COMPRESS  =0x4000,
	   ACB_DELETE    =0x8000
	} ACB_Flags;
#endif
#ifndef SACB
	#ifndef ACB
		typedef struct SACB
		{
		   USHORT flags;
		   AppID myID;
		   AppID next;
		   AppID prev;
		   ULONG publicstorage;
		   AppHdr const *appHeader;
		   BYTE const *certhdr;
		   pFrame appData;
		} ACB;
		
	#endif
#endif


#define AMS2_EV_getAppID _rom_call(short,(unsigned char const*),454)
#define OO_GetFirstFlashAppSectorAddress _rom_call(unsigned char *,(CFILE *),4F3)

#define OO_AMS_OK_FRAME_ENTRY (0x10001)

// Main Function
void _main(void)
{
	// Are we running on AMS 2.03- ? This patch is useless on AMS 2.04+.
	if(TIOS_entries<=0x5B7)
	{
		HANDLE appid=AMS2_EV_getAppID("sstart");
		ACB *acb;
		void *F_LINE_HANDLER_ADDRESS;
		CFILE file;

		if(appid)
		{
			// Is a custom F-Line handler installed ?
			F_LINE_HANDLER_ADDRESS=*(void **)INT_VEC_LINE_1111;

			if(F_LINE_HANDLER_ADDRESS < (void*)CertificateMemory || 
			   F_LINE_HANDLER_ADDRESS >= (void*)OO_GetFirstFlashAppSectorAddress(&file))
			{
				if(OO_SetAppAttr(appid, OO_AMS_OK_FRAME_ENTRY, (void*)TRUE))
				{
					acb=HeapDeref(appid);
					acb->flags&= ~ACB_JT_VERSION;

					ST_helpMsg("Patch applied");
					return;
				}
			}
		}
	}
	ST_helpMsg("Patch NOT applied");
}
