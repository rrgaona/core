/*
 * $Id$
 */

#ifndef HBSETUP_H_
#define HBSETUP_H_

/*
 * Harbour compiler and runtime configuration file
 */

/* The name of starting procedure
 * Note: You have to define it in case when Harbour cannot find the proper
 * starting procedure (due to incorrect order of static data initialization)
 *
 * The list of compilers that require it:
 * - Watcom C/C++ 10.0
 * - GCC on Linux
 *
 * By default we are using automatic lookup (symbol not defined)
*/
#if defined(__WATCOMC__) || defined(__GNUC__)
  #if !defined(__DJGPP__)
    #define HARBOUR_START_PROCEDURE "MAIN"
  #endif
#endif

/* This symbol defines if we want an ability to create and link OBJ files
 * generated by Harbour compiler
 *
 * By default it is disabled (symbol is not defined)
*/
/*#define HARBOUR_OBJ_GENERATION*/

/* This symbol defines if we want to use strict Clipper compatibility
 *
 * By default it is disabled (symbol is not defined)
*/
/*#define HB_STRICT_CLIPPER_COMPATIBILITY*/

/* This symbol defines if you want to have hb_stricmp() use stricmp()
 *
 * By default it is disabled (symbol is not defined)
*/
/*#define HB_USE_STRICMP*/

/* This symbol defines if you want to have hb_stricmp() use strcasecmp()
 *
 * By default it is disabled (symbol is not defined)
 *
 * If you define both HB_USE_STRICMP and HB_USE_STRCASECMP, HB_USE_STRICMP
 * will take precedence over HB_USE_STRCASECMP
*/
/*#define HB_USE_STRCASECMP*/

/* This symbol defines if we want to use the GT API
 *
 * By default it is disabled (symbol is not defined)
*/
/*#define USE_GTAPI*/

/* Operating system specific definitions
 */
#ifdef __GNUC__
  /* The GNU C compiler is used */
  #ifdef __DJGPP__
    /* The DJGPP port of GNU C is used - for DOS platform */
    #define OS_PATH_LIST_SEPARATOR   ';'
    #define OS_PATH_DELIMITER '\\'
    #define OS_DOS_COMPATIBLE
  #else
    #define OS_PATH_LIST_SEPARATOR   ':'
    #define OS_PATH_DELIMITER '/'
    #define OS_UNIX_COMPATIBLE
  #endif
#else
  /* we are assuming here the DOS compatible OS */
  #define OS_PATH_LIST_SEPARATOR    ';'
  #define OS_PATH_DELIMITER '\\'
  #define OS_DOS_COMPATIBLE
#endif

#endif  /* HBSETUP_H_ */
