/*
 * $Id$
 */

/*
 * Harbour Project source code:
 * Compiler PCode generation functions
 *
 * Copyright 1999 {list of individual authors and e-mail addresses}
 * www - http://www.harbour-project.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version, with one exception:
 *
 * The exception is that if you link the Harbour Runtime Library (HRL)
 * and/or the Harbour Virtual Machine (HVM) with other files to produce
 * an executable, this does not by itself cause the resulting executable
 * to be covered by the GNU General Public License. Your use of that
 * executable is in no way restricted on account of linking the HRL
 * and/or HVM code into it.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA (or visit
 * their web site at http://www.gnu.org/).
 *
 */

/*
 * The following parts are Copyright of the individual authors.
 * www - http://www.harbour-project.org
 *
 * Copyright 2000 RonPinkas <Ron@Profit-Master.com>
 *    hb_compStrongType()
 *
 * See doc/license.txt for licensing terms.
 *
 */

#include <assert.h>

#include "hbcomp.h"

static BYTE s_pcode_len[] = {
   1,        /* HB_P_AND,                  */
   1,        /* HB_P_ARRAYPUSH,            */
   1,        /* HB_P_ARRAYPOP,             */
   3,        /* HB_P_ARRAYDIM,             */
   3,        /* HB_P_ARRAYGEN,             */
   1,        /* HB_P_EQUAL,                */
   1,        /* HB_P_ENDBLOCK,             */
   1,        /* HB_P_ENDPROC,              */
   1,        /* HB_P_EXACTLYEQUAL,         */
   1,        /* HB_P_FALSE,                */
   1,        /* HB_P_FORTEST,              */
   3,        /* HB_P_FUNCTION,             */
   2,        /* HB_P_FUNCTIONSHORT,        */
   3,        /* HB_P_FRAME,                */
   1,        /* HB_P_FUNCPTR,              */
   1,        /* HB_P_GREATER,              */
   1,        /* HB_P_GREATEREQUAL,         */
   1,        /* HB_P_DEC,                  */
   1,        /* HB_P_DIVIDE,               */
   3,        /* HB_P_DO,                   */
   2,        /* HB_P_DOSHORT,              */
   1,        /* HB_P_DUPLICATE,            */
   1,        /* HB_P_DUPLTWO,              */
   1,        /* HB_P_INC,                  */
   1,        /* HB_P_INSTRING,             */
   2,        /* HB_P_JUMPNEAR,             */
   3,        /* HB_P_JUMP,                 */
   4,        /* HB_P_JUMPFAR,              */
   2,        /* HB_P_JUMPFALSENEAR,        */
   3,        /* HB_P_JUMPFALSE,            */
   4,        /* HB_P_JUMPFALSEFAR,         */
   2,        /* HB_P_JUMPTRUENEAR,         */
   3,        /* HB_P_JUMPTRUE,             */
   4,        /* HB_P_JUMPTRUEFAR,          */
   1,        /* HB_P_LESSEQUAL,            */
   1,        /* HB_P_LESS,                 */
   3,        /* HB_P_LINE,                 */
   0,        /* HB_P_LOCALNAME,            */
   1,        /* HB_P_MACROPOP,             */
   1,        /* HB_P_MACROPOPALIASED,      */
   1,        /* HB_P_MACROPUSH,            */
   1,        /* HB_P_MACROPUSHALIASED,     */
   1,        /* HB_P_MACROSYMBOL,          */
   1,        /* HB_P_MACROTEXT,            */
   3,        /* HB_P_MESSAGE,              */
   1,        /* HB_P_MINUS,                */
   1,        /* HB_P_MODULUS,              */
   0,        /* HB_P_MODULENAME,           */
             /* start: pcodes generated by macro compiler */
   3,        /* HB_P_MMESSAGE,             */
   3,        /* HB_P_MPOPALIASEDFIELD,     */
   3,        /* HB_P_MPOPALIASEDVAR,       */
   3,        /* HB_P_MPOPFIELD,            */
   3,        /* HB_P_MPOPMEMVAR,           */
   3,        /* HB_P_MPUSHALIASEDFIELD,    */
   3,        /* HB_P_MPUSHALIASEDVAR,      */
   0,        /* HB_P_MPUSHBLOCK,           */
   3,        /* HB_P_MPUSHFIELD,           */
   3,        /* HB_P_MPUSHMEMVAR,          */
   3,        /* HB_P_MPUSHMEMVARREF,       */
   3,        /* HB_P_MPUSHSYM,             */
   3,        /* HB_P_MPUSHVARIABLE,        */
             /* end: */
   1,        /* HB_P_MULT,                 */
   1,        /* HB_P_NEGATE,               */
   1,        /* HB_P_NOOP,                 */
   1,        /* HB_P_NOT,                  */
   1,        /* HB_P_NOTEQUAL,             */
   1,        /* HB_P_OR,                   */
   4,        /* HB_P_PARAMETER,            */
   1,        /* HB_P_PLUS,                 */
   1,        /* HB_P_POP,                  */
   1,        /* HB_P_POPALIAS,             */
   3,        /* HB_P_POPALIASEDFIELD,      */
   2,        /* HB_P_POPALIASEDFIELDNEAR,  */
   3,        /* HB_P_POPALIASEDVAR,        */
   3,        /* HB_P_POPFIELD,             */
   3,        /* HB_P_POPLOCAL,             */
   2,        /* HB_P_POPLOCALNEAR,         */
   3,        /* HB_P_POPMEMVAR,            */
   3,        /* HB_P_POPSTATIC,            */
   3,        /* HB_P_POPVARIABLE,          */
   1,        /* HB_P_POWER,                */
   1,        /* HB_P_PUSHALIAS,            */
   3,        /* HB_P_PUSHALIASEDFIELD,     */
   2,        /* HB_P_PUSHALIASEDFIELDNEAR, */
   3,        /* HB_P_PUSHALIASEDVAR,       */
   0,        /* HB_P_PUSHBLOCK,            */
   0,        /* HB_P_PUSHBLOCKSHORT,       */
   3,        /* HB_P_PUSHFIELD,            */
   2,        /* HB_P_PUSHBYTE,             */
   3,        /* HB_P_PUSHINT,              */
   3,        /* HB_P_PUSHLOCAL,            */
   2,        /* HB_P_PUSHLOCALNEAR,        */
   3,        /* HB_P_PUSHLOCALREF,         */
   1 + sizeof( long ),        /* HB_P_PUSHLONG,             */
   3,        /* HB_P_PUSHMEMVAR,           */
   3,        /* HB_P_PUSHMEMVARREF,        */
   1,        /* HB_P_PUSHNIL,              */
   1 + sizeof( double ) + sizeof( BYTE ) + sizeof( BYTE ),        /* HB_P_PUSHDOUBLE,           */
   1,        /* HB_P_PUSHSELF,             */
   3,        /* HB_P_PUSHSTATIC,           */
   3,        /* HB_P_PUSHSTATICREF,        */
   0,        /* HB_P_PUSHSTR,              */
   0,        /* HB_P_PUSHSTRSHORT,         */
   3,        /* HB_P_PUSHSYM,              */
   2,        /* HB_P_PUSHSYMNEAR,          */
   3,        /* HB_P_PUSHVARIABLE,         */
   1,        /* HB_P_RETVALUE,             */
   3,        /* HB_P_SEND,                 */
   2,        /* HB_P_SENDSHORT,            */
   4,        /* HB_P_SEQBEGIN,             */
   4,        /* HB_P_SEQEND,               */
   1,        /* HB_P_SEQRECOVER,           */
   3,        /* HB_P_SFRAME,               */
   5,        /* HB_P_STATICS,              */
   1,        /* HB_P_SWAPALIAS,            */
   1,        /* HB_P_TRUE,                 */
   1,        /* HB_P_ZERO,                 */
   1         /* HB_P_ONE,                  */
};

static BYTE * hb_comp_cParamTypes = NULL;
static int    hb_comp_iParamCount = -1;

void hb_compPCodeEval( PFUNCTION pFunc, HB_PCODE_FUNC_PTR * pFunctions, void * cargo )
{
   ULONG ulPos = 0;
   USHORT usSkip;
   BYTE opcode;
   HB_PCODE_FUNC_PTR pCall;

   /* Make sure that table is correct */
   assert( sizeof( s_pcode_len ) == HB_P_LAST_PCODE );

   while( ulPos < pFunc->lPCodePos )
   {
      opcode = pFunc->pCode[ ulPos ];
      if( opcode < HB_P_LAST_PCODE )
      {
         usSkip = s_pcode_len[ opcode ];
         pCall = pFunctions[ opcode ];
         if( pCall )
         {
            if( usSkip )
               pCall( pFunc, ulPos, cargo );
            else
               usSkip = pCall( pFunc, ulPos, cargo );
         }
         ulPos += usSkip;
      }
      else
      {
         printf( "--- Invalid opcode %i in hb_compPCodeEval() ---\n", opcode );
         ++ulPos;
      }
   }

}

void hb_compStrongType( int iSize )
{
   PFUNCTION pFunc = hb_comp_functions.pLast, pTmp;
   PVAR pVar;
   PCOMSYMBOL pSym;
   PCOMDECLARED pDeclared = NULL;
   ULONG ulPos = pFunc->lPCodePos - iSize;
   SHORT wVar;
   int iVar;
   char szType1[32], szType2[32];
   BYTE bLast1, bLast2;

   /* Make sure we have enough stack space. */
   if ( pFunc->pStack == NULL )
      pFunc->pStack = ( BYTE * ) hb_xgrab( pFunc->iStackSize += 16 );
   else if ( pFunc->iStackSize - pFunc->iStackIndex < 4 )
      pFunc->pStack = ( BYTE * ) hb_xrealloc( pFunc->pStack, pFunc->iStackSize += 16 );

   /* TODO Split under conitions for the different matching possible iSize. */

   /* TODO Subject to Operator Overloading! */

   switch ( pFunc->pCode[ ulPos ] )
   {
     /*-----------------4/26/00 0:16AM-------------------
      * Push values on stack.
      * --------------------------------------------------*/

     case HB_P_SWAPALIAS :
     case HB_P_RETVALUE :
       pFunc->iStackIndex--;

       pSym = hb_compSymbolFind( pFunc->szName, NULL );

       if ( pSym && pSym->szName )
          pDeclared = hb_compDeclaredFind( pSym->szName );

       /* The function was declared, but return value doesn't match the declaration */
       if ( pDeclared && pDeclared->cType != ' ' && pDeclared->cType != pFunc->pStack[ pFunc->iStackIndex ] )
       {
          sprintf( szType1, "%c", pDeclared->cType );
          sprintf( szType2, "%c", pFunc->pStack[ pFunc->iStackIndex ] );

          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_RETURN_TYPE, szType2, szType1 );
       }
       break;

     case HB_P_DOSHORT :
     case HB_P_FUNCTIONSHORT :
       wVar = pFunc->pCode[ ulPos + 1 ];

       if ( hb_comp_iParamCount > -1 )
       {
         if( hb_comp_iParamCount == wVar )
         {
            BYTE iOffset = 0;

            while ( hb_comp_iParamCount-- > 0 )
            {
               iOffset++;
               if ( pFunc->iStackIndex - iOffset && hb_comp_cParamTypes[ hb_comp_iParamCount ] != pFunc->pStack[ pFunc->iStackIndex - iOffset ] )
               {
                  sprintf( szType1, "%i", hb_comp_iParamCount + 1 );
                  sprintf( szType2, "%c", hb_comp_cParamTypes[ hb_comp_iParamCount ] );
                  hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_PARAM_TYPE, szType1, szType2 );
               }
            }
         }
         else
         {
            sprintf( szType1, "%i", wVar );
            sprintf( szType2, "%i", hb_comp_iParamCount );
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_PARAM_COUNT, szType1, szType2 );
         }
       }

       /* Removing all the optional parameters. Rteurn type already pushed just prior to parameters */
       pFunc->iStackIndex -= wVar;

       /* Removing the NIL */
       pFunc->iStackIndex--;

       /* Resetting */
       hb_comp_cParamTypes = NULL;
       hb_comp_iParamCount = -1;

       break;

     case HB_P_DO :
     case HB_P_FUNCTION :
       wVar = pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256;

       if ( hb_comp_iParamCount > -1 )
       {
         if( hb_comp_iParamCount == wVar )
         {
            BYTE iOffset = 0;

            while ( hb_comp_iParamCount-- > 0 )
            {
               iOffset++;
               if ( pFunc->iStackIndex - iOffset && hb_comp_cParamTypes[ hb_comp_iParamCount ] != pFunc->pStack[ pFunc->iStackIndex - iOffset ] )
               {
                  sprintf( szType1, "%i", hb_comp_iParamCount + 1 );
                  sprintf( szType2, "%c", hb_comp_cParamTypes[ hb_comp_iParamCount ] );
                  hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_PARAM_TYPE, szType1, szType2 );
               }
            }
         }
         else
         {
            sprintf( szType1, "%i", wVar );
            sprintf( szType2, "%i", hb_comp_iParamCount );
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_PARAM_COUNT, szType1, szType2 );
         }
       }

       /* Removing all the optional parameters. Rteurn type already pushed just prior to parameters */
       pFunc->iStackIndex -= wVar;

       /* Removing the NIL */
       pFunc->iStackIndex--;

       /* Resetting */
       hb_comp_cParamTypes = NULL;
       hb_comp_iParamCount = -1;
       break;

     case HB_P_DEC :
     case HB_P_INC :
       sprintf( szType1, "%c", pFunc->pStack[ pFunc->iStackIndex ] );

       if ( pFunc->pStack[ pFunc->iStackIndex ] == 'N' )
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, "N", NULL );
       else
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_TYPE, szType1, "N" );

       break;

     case HB_P_JUMPFALSENEAR :
     case HB_P_JUMPFALSE :
     case HB_P_JUMPFALSEFAR :
     case HB_P_JUMPTRUENEAR :
     case HB_P_JUMPTRUE :
     case HB_P_JUMPTRUEFAR :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       sprintf( szType1, "%c", pFunc->pStack[ pFunc->iStackIndex ] );

       if ( pFunc->pStack[ pFunc->iStackIndex ] == 'L' )
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, "L", NULL );
       else
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_TYPE, szType1, "L" );

       break;

     case HB_P_INSTRING :

       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 1 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       sprintf( szType1, "%c", pFunc->pStack[ pFunc->iStackIndex - 1 ] );
       sprintf( szType2, "%c", pFunc->pStack[ pFunc->iStackIndex ] );

       if ( ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' &&  pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' ) ||
            ( pFunc->pStack[ pFunc->iStackIndex ] == 'C' &&  pFunc->pStack[ pFunc->iStackIndex - 1 ] == 'C' ) )
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, "C", NULL  );
       else if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] != 'C' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_TYPE, szType1, "C" );
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, "C", NULL );
       else if ( pFunc->pStack[ pFunc->iStackIndex ] != 'C' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_TYPE, szType2, "C" );

       /* Override the last item with the new result type */
       pFunc->pStack[ pFunc->iStackIndex - 1 ] = 'L';
       break;

     /* May be subject to Operator Overloading - don't restrict to Numeric! */
     case HB_P_DIVIDE :
     case HB_P_PLUS :
     case HB_P_NEGATE :
     case HB_P_MULT :
     case HB_P_POWER :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 1 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       sprintf( szType1, "%c", pFunc->pStack[ pFunc->iStackIndex - 1 ] );
       sprintf( szType2, "%c", pFunc->pStack[ pFunc->iStackIndex ] );

       if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' &&  pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' )
          /* Override the last item with the new result type which is already there */
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == 'N' && pFunc->pStack[ pFunc->iStackIndex - 1 ] == 'N' )
          /* Override the last item with the new result type wich is already there */
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' )
       {
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, szType2, NULL );

          /* Override the last item with the new result type */
          pFunc->pStack[ pFunc->iStackIndex - 1 ] = ' ';
       }
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
       {
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, szType1, NULL );

          /* Override the last item with the new result type wich is already there */
       }
       else
       {
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERANDS_INCOMPATBLE, szType1, szType2 );

          /* Override the last item with the new result type */
          pFunc->pStack[ pFunc->iStackIndex - 1 ] = 'U';
       }

       break;

     case HB_P_EQUAL :
     case HB_P_EXACTLYEQUAL :
     case HB_P_NOTEQUAL :
     case HB_P_GREATER :
     case HB_P_GREATEREQUAL :
     case HB_P_LESSEQUAL :
     case HB_P_LESS :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 1 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       sprintf( szType1, "%c", pFunc->pStack[ pFunc->iStackIndex - 1 ] );
       sprintf( szType2, "%c", pFunc->pStack[ pFunc->iStackIndex ] );

       if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' &&  pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' )
          /* Override the last item with the new result type which is already there */
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == pFunc->pStack[ pFunc->iStackIndex - 1 ] )
          /* Override the last item with the new result type wich is already there */
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' )
       {
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, szType2, NULL );

          /* Override the last item with the new result type */
          pFunc->pStack[ pFunc->iStackIndex - 1 ] = ' ';
       }
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
       {
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, szType1, NULL );

          /* Override the last item with the new result type wich is already there */
       }
       else
       {
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERANDS_INCOMPATBLE, szType1, szType2 );

          /* Override the last item with the new result type */
          pFunc->pStack[ pFunc->iStackIndex - 1 ] = 'U';
       }

       break;

     /* Should we allow Operator Overloading here too? */
     case HB_P_AND :
     case HB_P_NOT :
     case HB_P_OR :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 1 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       sprintf( szType1, "%c", pFunc->pStack[ pFunc->iStackIndex - 1 ] );
       sprintf( szType2, "%c", pFunc->pStack[ pFunc->iStackIndex ] );

       if ( ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' &&  pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' ) ||
            ( pFunc->pStack[ pFunc->iStackIndex ] == 'L' &&  pFunc->pStack[ pFunc->iStackIndex - 1 ] == 'L' ) )
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, "L", NULL  );
       else if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] != 'L' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_TYPE, szType1, "L" );
       else if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_SUSPECT, "L", NULL );
       else if ( pFunc->pStack[ pFunc->iStackIndex ] != 'L' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_OPERAND_TYPE, szType2, "L" );

       /* Override the last item with the new result type */
       pFunc->pStack[ pFunc->iStackIndex - 1 ] = 'L';
       break;

     case HB_P_DUPLICATE :
       if ( pFunc->iStackIndex < 1 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       bLast1 = pFunc->pStack[ pFunc->iStackIndex - 1 ];
       pFunc->pStack[ pFunc->iStackIndex++ ] = bLast1;
       break;

     case HB_P_DUPLTWO :
       if ( pFunc->iStackIndex < 2 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       bLast1 = pFunc->pStack[ pFunc->iStackIndex - 2 ];
       bLast2 = pFunc->pStack[ pFunc->iStackIndex - 1 ];
       pFunc->pStack[ pFunc->iStackIndex++ ] = bLast1;
       pFunc->pStack[ pFunc->iStackIndex++ ] = bLast2;
       break;
     /* Explicit Types. */

     /* Objects */
     case HB_P_PUSHSELF :
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'O';
       break;

     /* Blcoks */
     /* Nothing to do, handled by HB_P_ENDBLOCK.
     case HB_P_PUSHBLOCK :
     case HB_P_PUSHBLOCKSHORT :
     */

     case HB_P_ENDBLOCK :
       /* Override the last value of the block left on the stack. */
       pFunc->pStack[ pFunc->iStackIndex ] = 'B';
       break;

     /* Undefined */
     case HB_P_PUSHNIL :
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'U';
       break;

     /* Logicals */
     case HB_P_TRUE :
     case HB_P_FALSE :
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'L';
       break;

     /* Numerics */
     case HB_P_PUSHDOUBLE :
     case HB_P_PUSHLONG :
     case HB_P_PUSHINT :
     case HB_P_PUSHBYTE :
     case HB_P_ZERO :
     case HB_P_ONE :
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'N';
       break;

     /* Charcters */
     case HB_P_PUSHSTRSHORT :
     case HB_P_PUSHSTR :
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'C';
       break;

     case HB_P_PUSHSYM :
     case HB_P_MPUSHSYM :
       pSym = hb_compSymbolGetPos( pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256 );

       if ( pSym && pSym->szName )
          pDeclared = hb_compDeclaredFind( pSym->szName );

       if ( pDeclared )
       {
          pFunc->pStack[ pFunc->iStackIndex++ ] = pDeclared->cType;

          /* Storing, will be checked by FUNCTION* */
          hb_comp_cParamTypes = pDeclared->cParamTypes;
          hb_comp_iParamCount = pDeclared->iParamCount;
       }
       else
         pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';

       break;

     case HB_P_PUSHSYMNEAR :
       pSym = hb_compSymbolGetPos( pFunc->pCode[ ulPos + 1 ] );

       if ( pSym && pSym->szName )
          pDeclared = hb_compDeclaredFind( pSym->szName );

       if ( pDeclared )
       {
          pFunc->pStack[ pFunc->iStackIndex++ ] = pDeclared->cType;

          /* Storing, will be checked by FUNCTION* */
          hb_comp_cParamTypes = pDeclared->cParamTypes;
          hb_comp_iParamCount = pDeclared->iParamCount;
       }
       else
          pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';

       break;

     /* Local Variables */

     case HB_P_PUSHLOCAL :
       wVar = * ( ( SHORT * ) &( pFunc->pCode )[ ulPos + 1 ] );

       /* we are accesing variables within a codeblock */
       if( wVar < 0 )
       {
          /* Finding the Function owning the block. */
          pTmp = pFunc->pOwner;

          /* Might be a nested block. */
          while ( pTmp->pOwner )
            pTmp = pTmp->pOwner;

          pVar = hb_compVariableFind( pTmp->pLocals, -wVar );
       }
       else
          pVar = hb_compVariableFind( pFunc->pLocals, wVar );

       if ( pVar )
       {
          /* Review with Ryszard. */
          if ( pVar->cType == 'U' )
             pVar->cType = ' ';

          pFunc->pStack[ pFunc->iStackIndex++ ] = pVar->cType;
       }
       else
          pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';

       break;

     case HB_P_PUSHLOCALREF :
       /* QUESTION: Fall from above, or use a "REFERENCED" type. */
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'R';
       break;

     case HB_P_PUSHLOCALNEAR :
       iVar = pFunc->pCode[ ulPos + 1 ];

       /* we are accesing variables within a codeblock */
       if( iVar < 0 )
       {
          /* Finding the Function owning the block. */
          pTmp = pFunc->pOwner;

          /* Might be a nested block. */
          while ( pTmp->pOwner )
             pTmp = pTmp->pOwner;

          pVar = hb_compVariableFind( pTmp->pLocals, -iVar );
       }
       else
          pVar = hb_compVariableFind( pFunc->pLocals, iVar );

       if ( pVar )
       {
          /* Review with Ryszard. */
          if ( pVar->cType == 'U' )
             pVar->cType = ' ';

          pFunc->pStack[ pFunc->iStackIndex++ ] = pVar->cType;
       }
       else
          pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';

       break;

     /* Static Variables */

     case HB_P_PUSHSTATIC :
       pTmp = hb_comp_functions.pFirst;
       wVar = pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256;

       while( pTmp->pNext && pTmp->pNext->iStaticsBase < wVar )
          pTmp = pTmp->pNext;

       pVar = hb_compVariableFind( pTmp->pStatics, wVar - pTmp->iStaticsBase );

       if ( pVar )
       {
          /* Review with Ryszard. */
          if ( pVar->cType == 'U' )
             pVar->cType = ' ';

         pFunc->pStack[ pFunc->iStackIndex++ ] = pVar->cType;
       }
       else
         pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';

       break;

     case HB_P_PUSHSTATICREF :
       /* Question use type "REFERENCE" or the base type of the var */
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'R';

     case HB_P_PUSHALIASEDFIELDNEAR :
       pSym = hb_compSymbolGetPos( pFunc->pCode[ ulPos + 1 ] );

       if ( pSym )
         pFunc->pStack[ pFunc->iStackIndex++ ] = pSym->cType;
       else
         pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';

       break;

     case HB_P_PUSHFIELD :
     case HB_P_PUSHALIASEDFIELD :
     case HB_P_PUSHALIASEDVAR :
     case HB_P_PUSHVARIABLE :
     case HB_P_PUSHMEMVAR :
       pSym = hb_compSymbolGetPos( pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256 );

       if ( pSym )
         pFunc->pStack[ pFunc->iStackIndex++ ] = pSym->cType;
       else
         pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';

       break;

     case HB_P_PUSHMEMVARREF :
       /* Question use type "REFERENCE" or the base type of the var */
       pFunc->pStack[ pFunc->iStackIndex++ ] = 'R';
       break;

     /* Arrays. */

     case HB_P_ARRAYDIM :
       wVar = pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256;

       if ( pFunc->iStackIndex < wVar )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       pFunc->iStackIndex -= wVar;

       pFunc->pStack[ pFunc->iStackIndex++ ] = 'A';

       break;

     case HB_P_ARRAYGEN :
       wVar = pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256;

       if ( pFunc->iStackIndex < wVar )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       pFunc->iStackIndex -= wVar;

       pFunc->pStack[ pFunc->iStackIndex++ ] = 'A';

       break;

     case HB_P_ARRAYPUSH :
       /* TODO: Deal with Array Elements. */
       pFunc->pStack[ pFunc->iStackIndex++ ] = ' ';
       break;

     /* Macros type unknown */
     case HB_P_MPUSHALIASEDFIELD :
     case HB_P_MPUSHALIASEDVAR :
     case HB_P_MPUSHFIELD :
     case HB_P_MPUSHMEMVAR :
     case HB_P_MPUSHMEMVARREF :
     case HB_P_MPUSHVARIABLE :
     case HB_P_MACROPUSHALIASED :
     case HB_P_MACROPUSH :
       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       /* Replace the value of the macro expression with unknown result of expanded macro. */
       pFunc->pStack[ pFunc->iStackIndex - 1 ] = ' ';
       break;

     case HB_P_MACROSYMBOL :
       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       /* Replace Macro Variable Symbol Name type with unknown type of expanded macro Function Call */
       pFunc->pStack[ pFunc->iStackIndex - 1 ] = ' ';
       break;

     case HB_P_MACROTEXT :
       /* Stack already has type C. */
       /*pFunc->pStack[ pFunc->iStackIndex ] = 'C';*/
       break;

     /*-----------------4/26/00 0:15AM-------------------
      *  Begin POP Check and Remove from Stack.
      * --------------------------------------------------*/

     case HB_P_POP :
     case HB_P_POPALIAS :
       pFunc->iStackIndex--;
       break;

     case HB_P_POPALIASEDFIELDNEAR :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       pSym = hb_compSymbolGetPos( pFunc->pCode[ ulPos + 1 ] );

       if ( pSym && pSym->cType != ' ' )
       {
         char szType[2];
         sprintf( szType, "%c", pSym->cType );

         if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_SUSPECT, pSym->szName, szType );
         else if ( pSym->cType != pFunc->pStack[ pFunc->iStackIndex ] )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_TYPE, pSym->szName, szType );
       }

       break;

     case HB_P_POPFIELD :
     case HB_P_POPALIASEDFIELD :
       /* TODO: Add support for FIELD declarations. */
     case HB_P_POPMEMVAR :
     case HB_P_POPVARIABLE :
     case HB_P_POPALIASEDVAR :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       pSym = hb_compSymbolGetPos( pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256 );

       if ( pSym && pSym->cType != ' ' )
       {
         char szType[2];
         sprintf( szType, "%c", pSym->cType );

         if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_SUSPECT, pSym->szName, szType );
         else if ( pSym->cType != pFunc->pStack[ pFunc->iStackIndex ] )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_TYPE, pSym->szName, szType );
       }

       break;

     case HB_P_POPLOCAL :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       wVar = * ( ( SHORT * ) &( pFunc->pCode )[ ulPos + 1 ] );

       /* we are accesing variables within a codeblock */
       if( wVar < 0 )
       {
         /* Finding the Function owning the block. */
         pTmp = pFunc->pOwner;

         /* Might be a nested block. */
         while ( pTmp->pOwner )
            pTmp = pTmp->pOwner;

         pVar = hb_compVariableFind( pTmp->pLocals, -wVar );
       }
       else
         pVar = hb_compVariableFind( pFunc->pLocals, wVar );

       if ( pVar && pVar->cType != ' ' )
       {
         char szType[2];
         sprintf( szType, "%c", pVar->cType );

         if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_SUSPECT, pVar->szName, szType );
         else if ( pVar->cType != pFunc->pStack[ pFunc->iStackIndex ] )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_TYPE, pVar->szName, szType );
       }

       break;

     case HB_P_POPLOCALNEAR :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       iVar = ( char ) pFunc->pCode[ ulPos + 1 ];

       /* we are accesing local variable refernced within a codeblock */
       if( iVar < 0 )
       {
         /* Finding the Function owning the block. */
         pTmp = pFunc->pOwner;

         /* Might be a nested block. */
         while ( pTmp->pOwner )
            pTmp = pTmp->pOwner;

         pVar = hb_compVariableFind( pTmp->pLocals, -iVar );
       }
       else
         pVar = hb_compVariableFind( pFunc->pLocals, iVar );

       if ( pVar && pVar->cType != ' ' )
       {
         char szType[2];
         sprintf( szType, "%c", pVar->cType );

         if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_SUSPECT, pVar->szName, szType );
         else if ( pVar->cType != pFunc->pStack[ pFunc->iStackIndex ] )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_TYPE, pVar->szName, szType );
       }

       break;

     case HB_P_POPSTATIC :
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       pTmp = hb_comp_functions.pFirst;
       wVar = pFunc->pCode[ ulPos + 1 ] + pFunc->pCode[ ulPos + 2 ] * 256;

       while( pTmp->pNext && pTmp->pNext->iStaticsBase < wVar )
          pTmp = pTmp->pNext;

       pVar = hb_compVariableFind( pTmp->pStatics, wVar - pTmp->iStaticsBase );

       if ( pVar && pVar->cType != ' '  )
       {
         char szType[2];
         sprintf( szType, "%c", pVar->cType );

         if ( pFunc->pStack[ pFunc->iStackIndex ] == ' ' )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_SUSPECT, pVar->szName, szType );
         else if ( pVar->cType != pFunc->pStack[ pFunc->iStackIndex ] )
            hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_ASSIGN_TYPE, pVar->szName, szType );
       }

       break;

     /* Macros Undefined Types */

     case HB_P_MPOPALIASEDFIELD :
     case HB_P_MPOPALIASEDVAR :
     case HB_P_MPOPFIELD :
     case HB_P_MPOPMEMVAR :
     case HB_P_MACROPOP :
     case HB_P_MACROPOPALIASED :
        pFunc->iStackIndex--;
        break;

     case HB_P_ARRAYPOP :
       /* Poping the Array Index. */
       pFunc->iStackIndex--;

       if ( pFunc->iStackIndex < 0 )
          /* TODO Error Message after finalizing all possible pcodes. */
          break;

       /* TODO: Deal with Array Elements. */
       if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] == ' ' )
          ;
       else if ( pFunc->pStack[ pFunc->iStackIndex - 1 ] != 'A' )
          hb_compGenWarning( hb_comp_szWarnings, 'W', HB_COMP_WARN_NOT_ARRAY, NULL, NULL );

       /* Poping the Assigned Value. */
       pFunc->iStackIndex--;

       break;
   }

   /* TODO Error or trace messages when completed. */
   if ( pFunc->iStackIndex < 0 )
      pFunc->iStackIndex = 0;
   else if ( pFunc->iStackIndex > 255 )
      pFunc->iStackIndex = 255;
}

void hb_compGenPCode1( BYTE byte )
{
   PFUNCTION pFunc = hb_comp_functions.pLast;   /* get the currently defined Clipper function */

   if( ! pFunc->pCode )   /* has been created the memory block to hold the pcode ? */
   {
      pFunc->pCode      = ( BYTE * ) hb_xgrab( HB_PCODE_CHUNK );
      pFunc->lPCodeSize = HB_PCODE_CHUNK;
      pFunc->lPCodePos  = 0;
   }
   else if( ( pFunc->lPCodeSize - pFunc->lPCodePos ) < 1 )
      pFunc->pCode = ( BYTE * ) hb_xrealloc( pFunc->pCode, pFunc->lPCodeSize += HB_PCODE_CHUNK );

   pFunc->pCode[ pFunc->lPCodePos++ ] = byte;

   if ( hb_comp_iWarnings >= 3 )
      hb_compStrongType( 1 );
}

void hb_compGenPCode2( BYTE byte1, BYTE byte2, BOOL bStackAffected )
{
   PFUNCTION pFunc = hb_comp_functions.pLast;   /* get the currently defined Clipper function */

   if( ! pFunc->pCode )   /* has been created the memory block to hold the pcode ? */
   {
      pFunc->pCode      = ( BYTE * ) hb_xgrab( HB_PCODE_CHUNK );
      pFunc->lPCodeSize = HB_PCODE_CHUNK;
      pFunc->lPCodePos  = 0;
   }
   else if( ( pFunc->lPCodeSize - pFunc->lPCodePos ) < 2 )
      pFunc->pCode = ( BYTE * ) hb_xrealloc( pFunc->pCode, pFunc->lPCodeSize += HB_PCODE_CHUNK );

   pFunc->pCode[ pFunc->lPCodePos++ ] = byte1;
   pFunc->pCode[ pFunc->lPCodePos++ ] = byte2;

   if ( hb_comp_iWarnings >= 3 && bStackAffected )
      hb_compStrongType( 2 );
}

void hb_compGenPCode3( BYTE byte1, BYTE byte2, BYTE byte3, BOOL bStackAffected )
{
   PFUNCTION pFunc = hb_comp_functions.pLast;   /* get the currently defined Clipper function */

   if( ! pFunc->pCode )   /* has been created the memory block to hold the pcode ? */
   {
      pFunc->pCode      = ( BYTE * ) hb_xgrab( HB_PCODE_CHUNK );
      pFunc->lPCodeSize = HB_PCODE_CHUNK;
      pFunc->lPCodePos  = 0;
   }
   else if( ( pFunc->lPCodeSize - pFunc->lPCodePos ) < 3 )
      pFunc->pCode = ( BYTE * ) hb_xrealloc( pFunc->pCode, pFunc->lPCodeSize += HB_PCODE_CHUNK );

   pFunc->pCode[ pFunc->lPCodePos++ ] = byte1;
   pFunc->pCode[ pFunc->lPCodePos++ ] = byte2;
   pFunc->pCode[ pFunc->lPCodePos++ ] = byte3;

   if ( hb_comp_iWarnings >= 3 && bStackAffected  )
      hb_compStrongType( 3 );
}

void hb_compGenPCode4( BYTE byte1, BYTE byte2, BYTE byte3, BYTE byte4, BOOL bStackAffected )
{
   PFUNCTION pFunc = hb_comp_functions.pLast;   /* get the currently defined Clipper function */

   if( ! pFunc->pCode )   /* has been created the memory block to hold the pcode ? */
   {
      pFunc->pCode      = ( BYTE * ) hb_xgrab( HB_PCODE_CHUNK );
      pFunc->lPCodeSize = HB_PCODE_CHUNK;
      pFunc->lPCodePos  = 0;
   }
   else if( ( pFunc->lPCodeSize - pFunc->lPCodePos ) < 4 )
      pFunc->pCode = ( BYTE * ) hb_xrealloc( pFunc->pCode, pFunc->lPCodeSize += HB_PCODE_CHUNK );

   pFunc->pCode[ pFunc->lPCodePos++ ] = byte1;
   pFunc->pCode[ pFunc->lPCodePos++ ] = byte2;
   pFunc->pCode[ pFunc->lPCodePos++ ] = byte3;
   pFunc->pCode[ pFunc->lPCodePos++ ] = byte4;

   if ( hb_comp_iWarnings >= 3 && bStackAffected  )
      hb_compStrongType( 4 );
}

void hb_compGenPCodeN( BYTE * pBuffer, ULONG ulSize, BOOL bStackAffected )
{
   PFUNCTION pFunc = hb_comp_functions.pLast;   /* get the currently defined Clipper function */

   if( ! pFunc->pCode )   /* has been created the memory block to hold the pcode ? */
   {
      pFunc->lPCodeSize = ( ( ulSize / HB_PCODE_CHUNK ) + 1 ) * HB_PCODE_CHUNK;
      pFunc->pCode      = ( BYTE * ) hb_xgrab( pFunc->lPCodeSize );
      pFunc->lPCodePos  = 0;
   }
   else if( pFunc->lPCodePos + ulSize > pFunc->lPCodeSize )
   {
      /* not enough free space in pcode buffer - increase it */
      pFunc->lPCodeSize += ( ( ( ulSize / HB_PCODE_CHUNK ) + 1 ) * HB_PCODE_CHUNK );
      pFunc->pCode = ( BYTE * ) hb_xrealloc( pFunc->pCode, pFunc->lPCodeSize );
   }

   memcpy( pFunc->pCode + pFunc->lPCodePos, pBuffer, ulSize );
   pFunc->lPCodePos += ulSize;

   if ( hb_comp_iWarnings >= 3 && bStackAffected  )
      hb_compStrongType( ulSize );
}
