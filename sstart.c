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

//A piece of the FRAME...
FRAME(appObjMain, OO_SYSTEM_FRAME, 0, OO_APP_FLAGS, FRAME_SIZE)
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
//	ATTR(OO_AMS_OK,						FALSE)							//0x10001		This is a special hook which allows Super Start to run on AMS 2.00 - 2.04 if this attribute has a value
    
ENDFRAME

/*
STRING_FRAME(appLanguages, OO_SYSTEM_FRAME, &appObjMain, OO_FIRST_STRING + OO_FIRST_APP_STRING + LANGUAGE_OFFSET, 7)
//Supported Languages... Should be in ABC order!	
	"Deutsch",						//German
	"English",						//English
	"Espa" RF_N_TILDE "ol",			//Spanish
	"Fran" RF_C_CEDILLA "ais",		//French
	"Italiano",						//Italian
	"Nederlands",					//Dutch
	"Svenska"						//Swedish
ENDFRAME
*/

//If anyone wants Super Start in a different language, just translate these strings and
//send them to me.
//"English" - English 

STRING_FRAME(appObj, OO_SYSTEM_FRAME, &appObjMain, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
//App ext extension help strings
	"about",														//XR_About
	"Shows the Super Start About Screen",							//XR_st_About
	"About()\nShows the Super Start About Screen",					//XR_msg_About
	
	"sstart",														//XR_sstart
	"launch a ppg or ASM program",									//XR_st_sstart
	"sstart(\"prgm\",[arg1],...)\n\nThis command launches a ppg or ASM program.\nThe first argument 'prgm' must be supplied and be a valid variable which has the type 'ASM' or 'ppg' as shown in the Var-Link.",		//XR_msg_sstart
	
//Application Strings   
	"Super Start v" APP_VERSION,	//XR_LongAppName
	"Super Start v" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nBy: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\nhttp://calc.gregd.org",	//XR_About_Me
	"You cannot delete Super Start while the Auto Start feature is turned on and the Home Screen is active! Either turn off Auto Start, or switch to another application such as Y=",					//XR_Fail_HS_Active
	"sstart.",						//XR_SSTART_EXT			this string must be consistent with the OO_APP_TOK_NAME frame entry
	"sstart(\"",					//XR_SSTART_MINIMAL		this string must be consistent with the OO_APP_TOK_NAME frame entry
	"\0sstart",						//XR_SSTART_TOK			this string must be consistent with the OO_APP_TOK_NAME frame entry
	"decompressing...",				//XR_Decompressing
	"Auto Start",
	"Leak Watch",
	"Leak Watch Report",			//XR_LeakWatchTitle
	
//Application Error Strings
	"You must specify the ASM or ppg program. Example: sstart(\"tetris\")",				//ER_TOO_FEW_ARGS
	"You must place quotation marks around the name of the program. Example: sstart(\"tetris\")",		//ER_EXPECTED_STRING_ARG
ENDFRAME

/*
//"Espa" RF_N_TILDE "ol" - Spanish
STRING_FRAME(appSpanish, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
//App ext extension help strings
 "about",															//XR_About
 "Presentar la pantalla 'Acerca de..' de Super Start",				//XR_st_About
 "AcercaDe()\nPresenta la pantalla 'Acerca de' de Super Start",		//XR_msg_About
 "sstart",															//XR_sstart
 "Ejecutar un programa ppg o ASM",									//XR_st_sstart
 "sstart(\"prgm\",[arg1],...)\n\nEste comando ejecuta un programa ppg o ASM.\nEl primer argumento 'prgm' debe existir y ser una variable válida de tipo 'ASM' o 'ppg' como se muestra en el Var-Link.",  //XR_msg_sstart
 
//Application Strings   
 "Super Start v" APP_VERSION,										//XR_LongAppName
 "Super Start v" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nPor: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\nhttp://calc.gregd.org", //XR_About_Me  it is almost the same line
 "No puede borrar a Super Start mientras la opción de Auto Arranque esta activada 'ON' y se esta en la pantalla Home! Para hacerlo, desactive el Auto Arranque 'OFF', o Cambie a otra aplicacion tal como Y=",     //XR_Fail_HS_Active
 "sstart.",															//XR_SSTART_EXT   this string must be consistent with the OO_APP_TOK_NAME frame entry
 "sstart(\"",														//XR_SSTART_MINIMAL  this string must be consistent with the OO_APP_TOK_NAME frame entry
 "\0sstart",														//XR_SSTART_TOK   this string must be consistent with the OO_APP_TOK_NAME frame entry
 "descomprimiendo...",												//XR_Decompressing
 "Auto Arranque",
 "Vigilante de Fallas",
 "Informe del Vigilante de Fallas",									//XR_LeakWatchTitle
 
//Application Error Strings
 "Debe especificar el programa ASM o ppg. Ejemplo: sstart(\"tetris\")",						//ER_TOO_FEW_ARGS
 "Debe colocar comillas alrededor del nombre del programa. Ejemplo: sstart(\"tetris\")",	//ER_EXPECTED_STRING_ARG	
ENDFRAME

//"Nederlands" - Dutch
STRING_FRAME(appDutch, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS) 
//App ext extension help strings 
   "about",                                          //XR_About 
   "Toont het Over Super Start Scherm",                     //XR_st_About 
   "About()\nToont het Over Super Start Scherm",               //XR_msg_About 
    
   "sstart",                                          //XR_sstart DNT 
   "voer een ppg of ASM programma uit",                           //XR_st_sstart 
   "sstart(\"prgm\",[arg1],...)\n\nDit commando voert een ppg of ASM programma uit.\nHet eerste argument 'prgm' moet gegeven worden en een geldige variabele van het type 'ASM' of 'ppg' zijn, zoals getoond in de Var-Link.",      //XR_msg_sstart 
    
//Application Strings    
   "Super Start v" APP_VERSION,   //XR_LongAppName DNT 
   "Super Start v" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nDoor: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\nhttp://calc.gregd.org",   //XR_About_Me 
   "Je kunt Super Start niet verwijderen zolang de Auto Start functie aan staat en het Home Screen actief is! Schakel Auto Start uit, of ga naar een andere applicatie, zoals Y=",               //XR_Fail_HS_Active 
   "sstart.",                  //XR_SSTART_EXT         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "sstart(\"",               //XR_SSTART_MINIMAL      this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "\0sstart",                  //XR_SSTART_TOK         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "uitpakken...",            //XR_Decompressing 
   "Auto Start", 
   "Leak Watch", 
   "Leak Watch Report",         //XR_LeakWatchTitle 
    
//Application Error Strings 
   "Je moet het ASM of ppg programma aangeven. Voorbeeld: sstart(\"tetris\")",            //ER_TOO_FEW_ARGS 
   "Je moet aanhalingstekens plaatsen rond de naam van het programma. Voorbeeld: sstart(\"tetris\")",      //ER_EXPECTED_STRING_ARG    
ENDFRAME

//"Svenska" - Swedish
STRING_FRAME(appSwedish, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
//App ext extension help strings 
"about", //XR_About 
"Visar information om Super start", //XR_st_About 
"About()\nVisar information om Super start ", //XR_msg_About 

"sstart", //XR_sstart DNT 
"Kör ett ASM eller ppg program", //XR_st_sstart 
"sstart(\"prgm\",[arg1],...)\n\nDetta kommando kör ett ASM eller ppg program.\nDet första argumentet 'prgm' måste ges och vara en giltig variabel av typen ASM eller ppg som visas i Var-linkmenyn.", //XR_msg_sstart 

//Application Strings  
"Super Start v" APP_VERSION, //XR_LongAppName DNT 
"Super Start v" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nAv: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\nhttp://calc.gregd.org", //XR_About_Me 
"Du kan inte radera Super Start medan Auto Start är på och du har grundfönstret framme! Stäng antingen av Auto Start eller byt till ett annat fönster som Y= editorn", //XR_Fail_HS_Active 
"sstart.", //XR_SSTART_EXT this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
"sstart(\"", //XR_SSTART_MINIMAL this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
"\0sstart", //XR_SSTART_TOK this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
"packar upp...", //XR_Decompressing 
"Auto Start", 
"kontroll för minnesläckor", 
"minnesläckage", //XR_LeakWatchTitle 

//Application Error Strings 
"Du måste ge ett namn på ett ppg- eller ASM-program. Exempel: sstart(\"tetris\")", //ER_TOO_FEW_ARGS 
"Du måste sätta citationstecken runt namnet. exempel: sstart(\"tetris\")", //ER_EXPECTED_STRING_ARG 
ENDFRAME


//"Deutsch" - German
STRING_FRAME(appGerman, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
//App ext extension help strings 
   "about",                                          //XR_About 
   "Zeigt den \"Über Super Start\"-Bildschirm",                     //XR_st_About 
   "About()\nZeigt den \"Über Super Start\"-Bildschirm",               //XR_msg_About 
    
   "sstart",                                          //XR_sstart DNT 
   "Ausführen eines ppg- oder ASM-Programms",                           //XR_st_sstart 
   "sstart(\"prgm\",[arg1],...)\n\nDieser Befehl führt ein ppg oder ASM program aus.\nDas erste Argument 'prgm' muß angegeben werden und eine gültige Variable sein, deren Typ laut Var-Link 'ASM' oder 'ppg' ist.",      //XR_msg_sstart 
    
//Application Strings    
   "Super Start V" APP_VERSION,   //XR_LongAppName DNT 
   "Super Start V" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nVon: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\nhttp://calc.gregd.org",   //XR_About_Me 
   "Sie können Super Start nicht löschen, solange die Auto-Start-Funktion eingeschalten und der Home Screen aktiv ist! Deaktivieren Sie Auto Start, oder schalten Sie zu einer anderen Applikation, wie etwa Y=, um.",               //XR_Fail_HS_Active 
   "sstart.",                  //XR_SSTART_EXT         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "sstart(\"",               //XR_SSTART_MINIMAL      this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "\0sstart",                  //XR_SSTART_TOK         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "dekomprimiere...",            //XR_Decompressing 
   "Auto Start", 
   "Speicherverlustüberwachung", 
   "Speicherverlustüberwachungsergebnis",         //XR_LeakWatchTitle 
    
//Application Error Strings 
   "Sie müssen das ASM- oder ppg-Programm angeben. Z.B.: sstart(\"tetris\")",            //ER_TOO_FEW_ARGS 
   "Sie müssen Anführungszeichen um den Programmnamen herum setzen. Z.B.: sstart(\"tetris\")",      //ER_EXPECTED_STRING_ARG    
ENDFRAME 


//"Fran" RF_C_CEDILLA "ais" -  French
STRING_FRAME(appFrench, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
//App ext extension help strings 
   "about",                                          //XR_About 
   "Affiche l'écran À propos de Super Start",                     //XR_st_About 
   "About()\nAffiche l'écran À propos de Super Start",               //XR_msg_About 
    
   "sstart",                                          //XR_sstart DNT 
   "lance un programme ppg ou ASM",                           //XR_st_sstart 
   "sstart(\"prgm\",[arg1],...)\n\nCette commande lance un programme ppg ou ASM.\nLe premier argument 'prgm' doit être spécifié et représenter une variable valide dont le type qui apparaît dans le Var-Link est 'ASM' ou 'ppg'.",      //XR_msg_sstart 
    
//Application Strings 
   "Super Start v" APP_VERSION,   //XR_LongAppName DNT 
   "Super Start v" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nPar: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\nhttp://calc.gregd.org",   //XR_About_Me 
   "Vous ne pouvez pas effacer Super Start tant que la fonction Démarrage Automatique est activée et l'écran Home est actif! Désactivez le Démarrage Automatique ou passez à une autre application, comme par exemple Y=.",
   "sstart.",                  //XR_SSTART_EXT         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT
   "sstart(\"",               //XR_SSTART_MINIMAL      this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "\0sstart",                  //XR_SSTART_TOK         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "décompression en cours...",            //XR_Decompressing 
   "Démarrage Automatique", 
   "Détection des pertes de mémoire", 
   "Résultat de la détection des pertes de mémoire",         //XR_LeakWatchTitle 
    
//Application Error Strings 
   "Vous devez spécifier le programme ASM ou ppg. Exemple: sstart(\"tetris\")",            //ER_TOO_FEW_ARGS 
   "Vous devez placer des guillemets autour du nom du programme. Exemple: sstart(\"tetris\")",      //ER_EXPECTED_STRING_ARG    
ENDFRAME 


//"Italiano" - Italian
STRING_FRAME(appItalian, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
//App ext extension help strings 
   "about",                                          //XR_About 
   "Mostra lo schermo Informazioni su Super Start",                     //XR_st_About 
   "About()\nMostra lo schermo Informazioni su Super Start",               //XR_msg_About 
    
   "sstart",                                          //XR_sstart DNT 
   "esegue un programma ppg o ASM",                           //XR_st_sstart 
   "sstart(\"prgm\",[arg1],...)\n\nQuesto commando esegue un programma ppg o ASM.\nDeve essere fornito il primo argomento 'prgm' ed essere una variabile valida di tipo 'ASM' o 'ppg', come mostrato dal Var-Link.",      //XR_msg_sstart 
    
//Application Strings     
   "Super Start v" APP_VERSION,   //XR_LongAppName DNT 
   "Super Start v" APP_VERSION "\n\nCopyright " RF_COPYRIGHT " 2003\nDi: Gregory L. Dietsche\nEmail: calc@gregd.org\n\nGForce Programming:\n calc.gregd.org",    //XR_About_Me 
   "Super Start non può essere cancellata mentre la funzione Esecuzione Automatica è abilitata e lo schermo Home è attivo! Devi disabilitare l'Esecuzione Automatica, oppure passare ad un'altra applicazione, per esempio Y=.",
   "sstart.",                  //XR_SSTART_EXT         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "sstart(\"",               //XR_SSTART_MINIMAL      this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "\0sstart",                  //XR_SSTART_TOK         this string must be consistent with the OO_APP_TOK_NAME frame entry DNT 
   "decompressione in corso...",            //XR_Decompressing 
   "Esecuzione Automatica", 
   "Rilevamento perdite di memoria", 
   "Risultato del rilevamento delle perdite di memoria",         //XR_LeakWatchTitle 
    
//Application Error Strings 
   "Specificare il programma ASM o ppg. Esempio: sstart(\"tetris\")",            //ER_TOO_FEW_ARGS 
   "Devi mettere il nome del programma tra virgolette. Esempio: sstart(\"tetris\")",      //ER_EXPECTED_STRING_ARG    
ENDFRAME
*/

//////////////////////////////////////////////////
//Application Data Section					  ///
////////////////////////////////////////////////

/* Pointer to the Frame object */
	pFrame pAppObj = (pFrame)&appObj;	/* Must be the first global variable declared! */
	pFrame AppLanguage=0;			/* Which Language Should This App Use */

//This is a bitmap structure, NOT an icon as suggested by the FRAME entry
const short AppIcon[]={
	0x0013,	//Num Rows	/\
	0x0010,	//Num Cols	<->
	//icon data
	0xF01F, 0x683F, 0x681F, 0x701F, 0x600F, 0x6782, 0xF340, 0x0340, 0x0380,
	0x0300, 0x0300, 0x0780, 0x003A, 0x4066, 0xF060, 0xF860, 0xF86F, 0xFC66,
	0xF83C
};


//16x16 GForce Programming BITMAP
const short GForceIcon[]={
	0x000e,
	0x0010,
	0x1F30, 0x37E0, 0x68E0, 0x50C0, 0xD800,
	0xD800, 0xDFF0, 0xDFE0, 0xD0E0, 0x70E0,
	0x70E0, 0x38E0, 0x1FF0, 0x3FF8,
};

const UCHAR cmd_post_app_id[]="CMDPOST";
const UCHAR ti_home[]="TIHOME";

//The dialog options...
SETTINGS gSettings;

//typedef struct{unsigned short Field;unsigned short HdrLen;unsigned long Len;void*Data;}CERT_FIELD;
typedef struct{void*Start,*Pos,*End;short EOFVal;}CFILE;

//yes, this is THE primary event loop! (finally :)
//not much to it eh? :)
//Cannot use F-Line ROM_CALLs in most parts of it due to AMS 2.03- support.
static void Event_Handler(pFrame self, PEvent e)
{
	Access_AMS_Global_Variables;
	SETTINGS *g=&gSettings;
	ULONG tmp_val;
	BOOL _OSVersionOK_;
	void * F_LINE_HANDLER_ADDRESS;
	CFILE file;

	
	//instead of using the CheckAMS macro, i've implemented a different method which allows people to hook Super Start and force it to
	//run on ams 2.00 through 2.03
	#define AMSMajorRevisionRequired (2)
	#define AMSMinorRevisionRequired (4)
	#define AMSMajorRevisionMax      (3)
	#define AMSMinorRevisionMax      (0)

	
	
	
	// From _OSVersionOK_=(BOOL)OO_GetAttr(self, OO_AMS_OK);
	// Nasty eh ?
	//_OSVersionOK_=(BOOL)(((void *(*)(pFrame,unsigned long))AMS_Global_Variables[0x3FD])(self, OO_AMS_OK));
	
	//if(!_OSVersionOK_)
	//{

	// Address of F-Line instructions handler.
	F_LINE_HANDLER_ADDRESS = *(void **)0x2C;

	// Cannot work on AMS 2.03- if there is no custom F-Line handler (which we always check here).
	// Tests:
	// * number of ROM_CALLs high enough to use EX_getBasecodeParmBlock;
	// * AMS version < 2.04 (using EX_getBasecodeParmBlock).
	// * F-Line instructions handler being located in AMS itself.
	if (   (   ((long const *)AMS_Global_Variables)[-1] < 1499 
	        || ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number < (((AMSMajorRevisionRequired) << 8) + (AMSMinorRevisionRequired))) // EX_getBasecodeParmBlock.
		&& (   (F_LINE_HANDLER_ADDRESS >= (void*)CertificateMemory) 
		    && (F_LINE_HANDLER_ADDRESS < ((void *(*)(CFILE*))AMS_Global_Variables[0x4F3])(&file)))) // 'OO_GetFirstFlashAppSectorAddress'.
	{
		MY_ACB(pAppObj)->flags|=(ACB_JT_VERSION);
		return;
	}
	// Cannot work for sure on AMS 3.01+ because of an unsafe hack to get the home screen TERecord in
	// HomeHook.c (we cannot do without this hack, since what we want is not exported in the jump table).
	// Therefore, self-delete !
	if (((long const *)AMS_Global_Variables)[-1] >= 0x608 || ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number > (((AMSMajorRevisionMax) << 8) + (AMSMinorRevisionMax)))  // EX_getBasecodeParmBlock.
	{
		MY_ACB(pAppObj)->flags|=(ACB_JT_VERSION|ACB_DELETE);
		return;
	}
	// If we come here, we have an AMS between 2.04 and 3.00: we can therefore use F-Line ROM_CALLs.
	//else
	//{
		//OO_SetAttr(self, OO_AMS_OK, (void*)TRUE);
		//(((short(*)(pFrame,unsigned long,void*))AMS_Global_Variables[0x401])(self, OO_AMS_OK, (void*)TRUE));
	//}
	//}
   
	switch (e->command)
	{
		case CM_INSTALL:
			g->AutoStart=2;
			g->LeakWatch=1;
			
		case CM_UNPACK:
			
			if(!g->AutoStart)	//the autostart option should never be set to zero because zero is invalid
			{
				tmp_val=OO_appGetPublicStorage();
				g->AutoStart=(tmp_val&0x0000f000)>>12;
				g->LeakWatch=(tmp_val&0x00000f00)>>8;
			}
			
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
			
			tmp_val=(g->AutoStart<<12) | (g->LeakWatch<<8);
			OO_appSetPublicStorage(tmp_val);
				
			break;
		
		default:
  			EV_defaultHandler(e);
  			break;
  	};
}

static void DoFormatsDialog(void)
{
	SETTINGS oldsettings=gSettings;
		
	switch(Dialog(&dlgFormats, -1, -1, NULL, (WORD*)&gSettings))
	{	
	//if enter is pressed, then accept the user's input
		case KB_ENTER:
			if(AutoStartInstalled() && oldsettings.AutoStart==PUP_OFF)
				InstallHook();
				
			if(!AutoStartInstalled() && oldsettings.AutoStart==PUP_ON)
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
	if(dlgId==DB_QACTIVE && dValue==1)
		return EV_getAppID(cmd_post_app_id);	//disable the option if Command Post is not installed

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

