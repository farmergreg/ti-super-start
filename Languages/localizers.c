// $Id$
// C Source File
// Created 7/21/2003; 1:16:55 AM
//Super Start Patch Program by Greg Dietsche
//warning, this program is not complete, and will not work on your calculator!

#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

#define NO_EXIT_SUPPORT
#define ENABLE_ERROR_RETURN   // Enable Returning Errors to AMS
#define OPTIMIZE_ROM_CALLS    // Use ROM Call Optimization
#define MIN_AMS 200           // Compile for AMS 2.00 or higher
#include <tigcclib.h>         // Include All Header Files

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
typedef enum {OO_RW=0,  OO_RO=1, OO_SEQ=0, OO_KEYED=2} OO_Flags;
              
typedef struct SFrameHdr
{
   pFrame parent;
   pFrame prototype;
   OO_Flags flags;
   ULONG first;
   ULONG count;
} OO_Hdr;

#define STRING_FRAME(name, parent, proto, first, count) \
const OO_Hdr name =   \
{                     \
   (pFrame)parent,    \
   (pFrame)proto,     \
   OO_RO | OO_SEQ,    \
   first,             \
   count              \
};                    \
static const char * const name##Attr[count] = \
{

#define ATTR(selector, val) {selector, (void *)(val)},
#define STRING_ATTR(sel, s) {OO_FIRST_STRING+(sel), s},
#define ENDFRAME };

#define OO_HANDLE (0xFF000000u)
#define OO_SYSTEM_FRAME OO_HANDLE

#define OO_FIRST_STRING             2048
#define OO_FIRST_APP_STRING         2048
#define OO_APPSTRING (OO_FIRST_STRING+OO_FIRST_APP_STRING)
#define RF_COPYRIGHT "\xA9"


#define SPANISH
#define APP_VERSION "1.20L"

#define NUM_XR_STRINGS (18)

asm("begin_frame:");


#ifdef SPANISH
//"Espa" RF_N_TILDE "ol" - Spanish

STRING_FRAME(appLangLoc, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
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

#endif

#ifdef DUTCH
//"Nederlands" - Dutch
STRING_FRAME(appLangLoc, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS) 
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
#endif

#ifdef SWEDISH
//"Svenska" - Swedish
STRING_FRAME(appLangLoc, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
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
#endif

#ifdef GERMAN
begin:
//"Deutsch" - German
STRING_FRAME(appLangLoc, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
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
#endif

#ifdef FRENCH
//"Fran" RF_C_CEDILLA "ais" -  French
STRING_FRAME(appLangLoc, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
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
#endif

#ifdef ITALIAN
//"Italiano" - Italian
STRING_FRAME(appLangLoc, OO_SYSTEM_FRAME, 0, OO_FIRST_STRING + OO_FIRST_APP_STRING, NUM_XR_STRINGS)
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
#endif

asm("end_frame:");

#define OO_AMS_OK (0x10001)

static pFrame hook=0;
extern char begin_frame;
extern char end_frame;

// Main Function
void _main(void)
{
		HANDLE appid=EV_getAppID("sstart");
		
		if(appid)
		{
			void *ptr;
				#define FRAME_SIZE (&end_frame-&begin_frame)
				ptr=HeapAllocPtr(FRAME_SIZE);
				
				memcpy(ptr, &appLangLoc, FRAME_SIZE);
				
				OO_InstallAppHook(appid, (pFrame)&ptr, &hook);
				
		}
}
