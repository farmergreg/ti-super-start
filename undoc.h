#ifndef _NOT_DOCUMENTED_H_
#define _NOT_DOCUMENTED_H_
//these are functions that are either NOT documented by TI,
//or are poorly documented.
//i also have a few defines that could be useful if found in tiams.h
//I do not consider this to be part of the Super Start project.
//I use it in several other projects, and keep a copy that is up-to-date
//elsewhere on my computer.

#ifndef _TIAMS_H
	#error Please include tiams.h before this header file
#endif

#define FirstWindow (*(WINDOW **)AMS_Global_Variables[0])

#define PortRestore tiamsapi_419
void tiamsapi_419(void);

#define FreeHandles tiamsapi_571
short tiamsapi_571(void);

#define CU_start tiamsapi_196
CU_STATE tiamsapi_196(void);

#define CU_stop tiamsapi_197
CU_STATE tiamsapi_197(void);

#define CU_restore tiamsapi_195
void tiamsapi_195(CU_STATE);

#define AtLeastAMS(major,minor)((long const *)AMS_Global_Variables)[-1] < 1499 || ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number < (((major) << 8) + (minor))

#endif
 