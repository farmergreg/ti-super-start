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

#ifndef _XR_H_
#define _XR_H_

//Application XR strings
enum XR_STRINGS {
                  XR_About=OO_FIRST_APP_STRING,
				  XR_st_About,
				  XR_msg_About,
				  
				  XR_sstart,
				  XR_st_sstart,
				  XR_msg_sstart,
				  
				  XR_LongAppName,
				  XR_About_Me,
				  XR_Fail_HS_Active,
				  XR_SSTART_EXT,
				  XR_SSTART_MINIMAL,
				  XR_SSTART_TOK,
				  XR_Decompressing,
				  XR_AutoComplete,
				  XR_LeakWatch,
				  XR_LeakWatchTitle,
				  
				  ER_TOO_FEW_ARGS,
				  ER_EXPECTED_STRING_ARG,
				  				  
				  LAST_XR_STRING
				  };                          	
#define NUM_XR_STRINGS (LAST_XR_STRING-OO_FIRST_APP_STRING)


//if you are using a resource file, then you cannot use an enum
//to declare the application XR_strings
//this is due to limitations of the TIFS resource compiler
//this information is current as of TIFS Version 1.1 Build 41
//rather, you must #define each string used in the resource like this:

//this is rather high maintence...
#define XR_LONG_APP_NAME	(OO_FIRST_APP_STRING + 6)
#define XR_AUTO_COMPLETE	(OO_FIRST_APP_STRING + 13)
#define XR_LEAK_WATCH		(OO_FIRST_APP_STRING + 14)



#define LANGUAGE_OFFSET (250)
#define LANG_German		(OO_FIRST_APP_STRING + LANGUAGE_OFFSET + 0)
#define LANG_English	(OO_FIRST_APP_STRING + LANGUAGE_OFFSET + 1)
#define LANG_Spanish	(OO_FIRST_APP_STRING + LANGUAGE_OFFSET + 2)
#define LANG_French		(OO_FIRST_APP_STRING + LANGUAGE_OFFSET + 3)
#define LANG_Italian	(OO_FIRST_APP_STRING + LANGUAGE_OFFSET + 4)
#define LANG_Dutch		(OO_FIRST_APP_STRING + LANGUAGE_OFFSET + 5)
#define LANG_Swedish	(OO_FIRST_APP_STRING + LANGUAGE_OFFSET + 6)


//Application Defined TI-Basic Extensions
//Keep in ABC order (keep in mind the difference between 'A' and 'a' too)
// or there will be problems.	
enum
{
    EXT_ABOUT,
    EXT_SSTART,
	NUM_EXTENSIONS
};

#endif
 