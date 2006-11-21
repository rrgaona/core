#include "hbpp.h"
#include "hbcomp.h"
#include "hbdate.h"
#include "harboury.h"

/*
   keywords:
      ANNO[UNCE]        -> ANNOUNCE
      BEGI[N] SEQU[ENCE]-> BEGINSEQ
      BREA[K]           -> BREAK
      CASE              -> CASE
      _PROCREQ_(        -> PROCREQ
      DECL[ARE]         -> DECLARE, PRIVATE, IDENTIFIER
      OPTI[ONAL]        -> OPTIONAL
      DO                -> DO
      DO CASE           -> DOCASE
      DO WHILE          -> WHILE
      DESCEND           -> DESCEND
      ELSE              -> ELSE
      ELSEI[F]          -> ELSEIF
      END SEQU[ENCE]    -> END
      ENDI[F]           -> ENDIF
      ENDC[ASE]         -> ENDCASE
      ENDD[O]           -> ENDDO
      END               -> END
      EXIT              -> EXIT
      EXTE[RNAL]        -> EXTERN
      _FIE[LD]          -> FIELD
      FIEL[D]           -> FIELD
      FOR               -> FOR
      FOR EACH          -> FOREACH
      FUNC[TION]        -> FUNCTION
      HB_INLINE         -> ???
      IIF               -> IIF
      IF                -> IF, IIF
      IN                -> IN
      INIT              -> INIT
      LOOP              -> LOOP
      MEMV[AR]          -> MEMVAR
      NEXT              -> NEXT
      NIL               -> NIL
      OTHE[RWISE]       -> OTHERWISE
      PARA[METERS]      -> PARAMETERS
      PRIV[ATE]         -> PRIVATE
      PROC[EDURE]       -> PROCEDURE
      PUBL[IC]          -> PUBLIC
      QSELF()           -> SELF
      RECO[VER]         -> RECOVER
      RECO[VER] USIN[G] -> RECOVERUSING
      RETU[RN]          -> RETURN
      STAT[IC]          -> STATIC
      STEP              -> STEP
      SWITCH            -> DOSWITCH
      TO                -> TO
      WHILE             -> WHILE
      WITH              -> WITH
      WITH OBJECT       -> WITHOBJECT
      AS ARRA[Y]        -> AS_ARRAY
      AS CODE[BLOCK]    -> AS_BLOCK
      AS STRI[NG]       -> AS_CHARACTER
      AS CHAR[ACTER]    -> AS_CHARACTER
      AS CLAS[S]        -> AS_CLASS
      AS DATE           -> AS_DATE
      AS LOGI[CAL]      -> AS_LOGICAL
      AS NUME[RIC]      -> AS_NUMERIC
      AS OBJE[CT]       -> AS_OBJECT
      AS USUA[L]        -> AS_VARIANT
      AS ANYT[YPE]      -> AS_VARIANT
      AS ARRA[Y] OF USUA[L]         -> AS_ARRAY
      AS ARRA[Y] OF ANYT[YPE]       -> AS_ARRAY
      AS ARRA[Y] OF ARRA[Y]         -> AS_ARRAY_ARRAY
      AS ARRA[Y] OF CODE[BLOCK]     -> AS_BLOCK_ARRAY
      AS ARRA[Y] OF STRI[NG]        -> AS_CHARACTER_ARRAY
      AS ARRA[Y] OF CHAR[ACTER]     -> AS_CHARACTER_ARRAY
      AS ARRA[Y] OF CLAS[S]         -> AS_CLASS_ARRAY
      AS ARRA[Y] OF DATE            -> AS_DATE_ARRAY
      AS ARRA[Y] OF LOGI[CAL]       -> AS_LOGICAL_ARRAY
      AS ARRA[Y] OF NUME[RIC]       -> AS_NUMERIC_ARRAY
      AS ARRA[Y] OF OBJE[CT]        -> AS_OBJECT_ARRAY
      _HB_CLASS         -> DECLARE_CLASS
      _HB_MEMBER        -> DECLARE_MEMBER


   iState usage:
      '[':        OPERATOR, LSEPARATOR, LARRAY, IF, ELSEIF, CASE, BREAK,
                  RETURN, WITH, WHILE
      break:      LOOKUP
      case:       LOOKUP
      declare:    DO
      do:         LOOKUP
      end:        LOOKUP
      field:      LOOKUP
      for:        LOOKUP
      iif:        FUNCTION, PROCEDURE
      if:         FUNCTION, PROCEDURE, LOOKUP
      init:       LOOKUP
      next:       LOOKUP
      otherwise:  LOOKUP
      recover:    LOOKUP
      return:     LOOKUP
      switch:     LOOKUP
      while:      DO, LOOKUP
      whith:      LOOKUP, DO, WHILE, MACROVAR, MACROTEXT, IDENTIFIER,
                  RSEPARATOR

*/

#define HB_PP_LEX_SELF(t)     ( HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_SEND && \
                                (t)->pNext && t->pNext->spaces == 0 && \
                                HB_PP_TOKEN_TYPE((t)->pNext->type) == HB_PP_TOKEN_SEND )

#define HB_PP_LEX_NEEDLEFT(t) ( HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_ASSIGN || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_PLUSEQ || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_MINUSEQ || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_MULTEQ || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_DIVEQ || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_MODEQ || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_EXPEQ || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_EQUAL || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_EQ || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_ALIAS || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_MULT || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_DIV || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_MOD || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_POWER || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_IN || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_AND || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_OR || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_PIPE || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_RIGHT_PB || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_RIGHT_SB || \
                                HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_RIGHT_CB || \
                                ( HB_PP_TOKEN_TYPE((t)->type) == HB_PP_TOKEN_SEND && \
                                  !HB_PP_LEX_SELF(t) ) )

#define LOOKUP           0
#define OPERATOR        -2
#define LSEPARATOR      -3
#define RSEPARATOR      -4
#define LINDEX          -5
#define RINDEX          -6
#define LARRAY          -7
#define RARRAY          -8
#define AS_TYPE         -9


typedef struct
{
   char *   value;      /* keyword name */
   int      minlen;     /* minimal length */
   int      maxlen;     /* maximal length */
   int      type;       /* terminal symbol code */
}
HB_LEX_KEY, * PHB_LEX_KEY;

static const HB_LEX_KEY s_keytable[] = 
{
   { "ANNOUNCE",    4,  8, ANNOUNCE       },
   { "BEGIN",       4,  5, BEGINSEQ       },
   { "BREAK",       4,  5, BREAK          },
   { "CASE",        4,  4, CASE           },
   { "DECLARE",     4,  7, DECLARE        },
   { "OPTIONAL",    4,  8, OPTIONAL       },
   { "DO",          2,  2, DO             },
   { "DESCEND",     7,  7, DESCEND        },
   { "ELSE",        4,  4, ELSE           },
   { "ELSEIF",      5,  6, ELSEIF         },
   { "END",         3,  3, END            },
   { "ENDIF",       4,  5, ENDIF          },
   { "ENDCASE",     4,  7, ENDCASE        },
   { "ENDDO",       4,  5, ENDDO          },
   { "EXIT",        4,  4, EXIT           },
   { "EXTERNAL",    4,  8, EXTERN         },
   { "_FIELD",      4,  6, FIELD          },
   { "FIELD",       4,  5, FIELD          },
   { "FOR",         3,  3, FOR            },
   { "FUNCTION",    4,  8, FUNCTION       },
   { "IIF",         3,  3, IIF            },
   { "IF",          2,  2, IF             },
   { "IN",          2,  2, IN             },
   { "INIT",        4,  4, INIT           },
   { "LOCAL",       4,  5, LOCAL          },
   { "LOOP",        4,  4, LOOP           },
   { "MEMVAR",      4,  6, MEMVAR         },
   { "NEXT",        4,  4, NEXT           },
   { "NIL",         3,  3, NIL            },
   { "OTHERWISE",   4,  9, OTHERWISE      },
   { "PARAMETERS",  4, 10, PARAMETERS     },
   { "PRIVATE",     4,  7, PRIVATE        },
   { "PROCEDURE",   4,  9, PROCEDURE      },
   { "PUBLIC",      4,  6, PUBLIC         },
   { "QSELF",       4,  5, SELF           },
   { "_PROCREQ_",   4,  9, PROCREQ        },
   { "RECOVER",     4,  7, RECOVER        },
   { "RETURN",      4,  6, RETURN         },
   { "STATIC",      4,  6, STATIC         },
   { "STEP",        4,  4, STEP           },
   { "SWITCH",      4,  6, DOSWITCH       },
   { "TO",          2,  2, TO             },
   { "WHILE",       4,  5, WHILE          },
   { "WITH",        4,  4, WITH           },
   { "AS",          2,  2, AS_TYPE        },
   { "_HB_CLASS",   9,  9, DECLARE_CLASS  },
   { "_HB_MEMBER", 10, 10, DECLARE_MEMBER }
};

#define _AS_ARRAY       1
#define _AS_BLOCK       2
#define _AS_CHARACTER   3
#define _AS_CLASS       4
#define _AS_DATE        5
#define _AS_LOGICAL     6
#define _AS_NUMERIC     7
#define _AS_OBJECT      8
#define _AS_VARIANT     9

static const int s_asTypes[] =
{ 
   0,
   AS_ARRAY,
   AS_BLOCK,
   AS_CHARACTER,
   AS_CLASS,
   AS_DATE,
   AS_LOGICAL,
   AS_NUMERIC,
   AS_OBJECT,
   AS_VARIANT
};

static const int s_asArrayTypes[] =
{ 
   0,
   AS_ARRAY_ARRAY,
   AS_BLOCK_ARRAY,
   AS_CHARACTER_ARRAY,
   AS_CLASS_ARRAY,
   AS_DATE_ARRAY,
   AS_LOGICAL_ARRAY,
   AS_NUMERIC_ARRAY,
   AS_OBJECT_ARRAY,
   AS_ARRAY
};

static const HB_LEX_KEY s_typetable[] = 
{
   { "ARRAY",       4,  5, _AS_ARRAY      },
   { "CODEBLOCK",   4,  9, _AS_BLOCK      },
   { "STRING",      4,  6, _AS_CHARACTER  },
   { "CHARACTER",   4,  9, _AS_CHARACTER  },
   { "CLASS",       4,  5, _AS_CLASS      },
   { "DATE",        4,  4, _AS_DATE       },
   { "LOGICAL",     4,  7, _AS_LOGICAL    },
   { "NUMERIC",     4,  7, _AS_NUMERIC    },
   { "OBJECT",      4,  6, _AS_OBJECT     },
   { "USUAL",       4,  5, _AS_VARIANT    },
   { "ANYTYPE",     4,  7, _AS_VARIANT    }
};

static int hb_comp_asType( PHB_PP_TOKEN pToken, BOOL fArray )
{
   if( pToken && HB_PP_TOKEN_TYPE( pToken->type ) == HB_PP_TOKEN_KEYWORD )
   {
      PHB_LEX_KEY pKey = ( PHB_LEX_KEY ) s_typetable;
      int i = sizeof( s_typetable ) / sizeof( HB_LEX_KEY );

      hb_pp_tokenUpper( pToken );
      do
      {
         if( pKey->minlen <= pToken->len && pToken->len <= pKey->maxlen &&
             memcmp( pKey->value, pToken->value, pToken->len ) == 0 )
            return ( fArray ? s_asArrayTypes : s_asTypes ) [ pKey->type ];
         ++pKey;
      }
      while( --i );
   }
   return 0;
}

static int hb_comp_keywordType( PHB_PP_TOKEN pToken )
{
   PHB_LEX_KEY pKey = ( PHB_LEX_KEY ) s_keytable;
   int i = sizeof( s_keytable ) / sizeof( HB_LEX_KEY );

   do
   {
      if( pKey->minlen <= pToken->len && pToken->len <= pKey->maxlen &&
          memcmp( pKey->value, pToken->value, pToken->len ) == 0 )
      {
         if( HB_PP_TOKEN_ALLOC( pToken->type ) && pToken->len == pKey->maxlen )
         {
            hb_xfree( pToken->value );
            pToken->value = pKey->value;
            pToken->type |= HB_PP_TOKEN_STATIC;
         }
         return pKey->type;
      }
      ++pKey;
   }
   while( --i );
   return IDENTIFIER;
}

static char * hb_comp_tokenIdentifer( PHB_PP_TOKEN pToken )
{
   if( HB_PP_TOKEN_ALLOC( pToken->type ) )
   {
      pToken->value = hb_compIdentifierNew( pToken->value, FALSE );
      pToken->type |= HB_PP_TOKEN_STATIC;
   }

   return pToken->value;
}

//int hb_complex( YYSTYPE *yylval_ptr, HB_COMP_PTR pComp )
int yylex( YYSTYPE *yylval_ptr, HB_COMP_PTR pComp )
{
   PHB_COMP_LEX pLex = ( PHB_COMP_LEX ) pComp->pLex;
   PHB_PP_TOKEN pToken = hb_pp_tokenGet( pLex->pPP );

   if( !pToken )
      return 0;

   pLex->lasttok = pToken->value;

   switch( HB_PP_TOKEN_TYPE( pToken->type ) )
   {
      case HB_PP_TOKEN_NUMBER:
      {
         HB_LONG lNumber;
         double dNumber;
         int iDec, iWidth;

         pLex->iState = LITERAL;
         if( hb_compStrToNum( pToken->value, pToken->len, &lNumber, &dNumber, &iDec, &iWidth ) )
         {
            yylval_ptr->valDouble.dNumber = dNumber;
            yylval_ptr->valDouble.bDec    = ( UCHAR ) iDec;
            yylval_ptr->valDouble.bWidth  = ( UCHAR ) iWidth;
            return NUM_DOUBLE;
         }
         else
         {
            yylval_ptr->valLong.lNumber = lNumber;
            yylval_ptr->valLong.bWidth  = ( UCHAR ) iWidth;
            return NUM_LONG;
         }
      }
      case HB_PP_TOKEN_DATE:
         pLex->iState = LITERAL;
         if( pToken->len == 10 )
         {
            int year, month, day;
            hb_dateStrGet( pToken->value + 2, &year, &month, &day );
            yylval_ptr->valLong.lNumber = hb_dateEncode( year, month, day );
         }
         else
            yylval_ptr->valLong.lNumber = 0;
         return NUM_DATE;

      case HB_PP_TOKEN_STRING:
         pLex->iState = LITERAL;
         pLex->lasttok = yylval_ptr->string = hb_comp_tokenIdentifer( pToken );
         return LITERAL;

      case HB_PP_TOKEN_LOGICAL:
         pLex->iState = LITERAL;
         return pToken->value[ 1 ] == 'T' ? TRUEVALUE : FALSEVALUE;

      case HB_PP_TOKEN_MACROVAR:
         pLex->iState = MACROVAR;
         hb_pp_tokenUpper( pToken );
         pLex->lasttok = yylval_ptr->string = hb_comp_tokenIdentifer( pToken );
         return MACROVAR;

      case HB_PP_TOKEN_MACROTEXT:
         pLex->iState = MACROTEXT;
         hb_pp_tokenUpper( pToken );
         pLex->lasttok = yylval_ptr->string = hb_comp_tokenIdentifer( pToken );
         return MACROTEXT;

      case HB_PP_TOKEN_LEFT_SB:
         switch( pLex->iState )
         {
            case OPERATOR:
            case LSEPARATOR:
            case LARRAY:
            case IF:
            case ELSEIF:
            case CASE:
            case BREAK:
            case RETURN:
            case WITH:
            case WHILE:
               pLex->iState = LITERAL;
               hb_pp_tokenToString( pLex->pPP, pToken );
               pLex->lasttok = yylval_ptr->string = hb_comp_tokenIdentifer( pToken );
               return LITERAL;

            default:
               pLex->iState = LINDEX;
               return '[';
         }

      case HB_PP_TOKEN_RIGHT_SB:
         pLex->iState = RINDEX;
         return ']';

      case HB_PP_TOKEN_LEFT_CB:
         if( pToken->pNext &&
             HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_PIPE )
         {
            int iType = 0;
            yylval_ptr->asCodeblock.string =
               hb_strdup( hb_pp_tokenBlockString( pLex->pPP, pToken, &iType ) );
            yylval_ptr->asCodeblock.length =
               strlen( yylval_ptr->asCodeblock.string );
		yylval_ptr->asCodeblock.isMacro = iType > 0;
		yylval_ptr->asCodeblock.lateEval = iType > 1;
            hb_pp_tokenGet( pLex->pPP );
            return CBSTART;
         }
         pLex->iState = LARRAY;
         return '{';

      case HB_PP_TOKEN_RIGHT_CB:
         pLex->iState = RARRAY;
         return '}';

      case HB_PP_TOKEN_LEFT_PB:
         pLex->iState = LSEPARATOR;
         return '(';

      case HB_PP_TOKEN_RIGHT_PB:
         pLex->iState = RSEPARATOR;
         return ')';

      case HB_PP_TOKEN_EPSILON:
         pLex->iState = OPERATOR;
         return EPSILON;

      case HB_PP_TOKEN_HASH:
      case HB_PP_TOKEN_DIRECTIVE:
         if( pLex->iState == LOOKUP && pToken->pNext &&
             HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
             hb_stricmp( "LINE", pToken->pNext->value ) == 0 )
         {
            hb_pp_tokenGet( pLex->pPP );
            return LINE;
         }
         pLex->iState = OPERATOR;
         return NE1;

      case HB_PP_TOKEN_NE:
         pLex->iState = OPERATOR;
         return NE2;

      case HB_PP_TOKEN_ASSIGN:
         pLex->iState = OPERATOR;
         return INASSIGN;

      case HB_PP_TOKEN_EQUAL:
         pLex->iState = OPERATOR;
         return EQ;

      case HB_PP_TOKEN_INC:
         pLex->iState = OPERATOR;
         return INC;

      case HB_PP_TOKEN_DEC:
         pLex->iState = OPERATOR;
         return DEC;

      case HB_PP_TOKEN_ALIAS:
         pLex->iState = OPERATOR;
         return ALIASOP;

      case HB_PP_TOKEN_LE:
         pLex->iState = OPERATOR;
         return LE;

      case HB_PP_TOKEN_GE:
         pLex->iState = OPERATOR;
         return GE;

      case HB_PP_TOKEN_PLUSEQ:
         pLex->iState = OPERATOR;
         return PLUSEQ;

      case HB_PP_TOKEN_MINUSEQ:
         pLex->iState = OPERATOR;
         return MINUSEQ;

      case HB_PP_TOKEN_MULTEQ:
         pLex->iState = OPERATOR;
         return MULTEQ;

      case HB_PP_TOKEN_DIVEQ:
         pLex->iState = OPERATOR;
         return DIVEQ;

      case HB_PP_TOKEN_MODEQ:
         pLex->iState = OPERATOR;
         return MODEQ;

      case HB_PP_TOKEN_EXPEQ:
         pLex->iState = OPERATOR;
         return EXPEQ;

      case HB_PP_TOKEN_POWER:
         pLex->iState = OPERATOR;
         return POWER;

      case HB_PP_TOKEN_AND:
         pLex->iState = OPERATOR;
         return AND;

      case HB_PP_TOKEN_OR:
         pLex->iState = OPERATOR;
         return OR;

      case HB_PP_TOKEN_NOT:
         pLex->iState = OPERATOR;
         return NOT;

      case HB_PP_TOKEN_SEND:
         if( HB_PP_LEX_SELF( pToken ) )
         {
            pLex->lasttok = yylval_ptr->string = "SELF";
            return IDENTIFIER;
         }
         /* no break */
      case HB_PP_TOKEN_EQ:
      case HB_PP_TOKEN_PLUS:
      case HB_PP_TOKEN_MINUS:
      case HB_PP_TOKEN_MULT:
      case HB_PP_TOKEN_DIV:
      case HB_PP_TOKEN_MOD:
      case HB_PP_TOKEN_IN:
      case HB_PP_TOKEN_COMMA:
      case HB_PP_TOKEN_PIPE:
      case HB_PP_TOKEN_AMPERSAND:
      case HB_PP_TOKEN_DOT:
      case HB_PP_TOKEN_LT:
      case HB_PP_TOKEN_GT:
      case HB_PP_TOKEN_REFERENCE:
         pLex->iState = OPERATOR;
         return pToken->value[ 0 ];

      case HB_PP_TOKEN_EOL:
      case HB_PP_TOKEN_EOC:
         pLex->iState = LOOKUP;
         return pToken->value[ 0 ];

      case HB_PP_TOKEN_KEYWORD:
      {
         int iType;
         hb_pp_tokenUpper( pToken );
         iType = hb_comp_keywordType( pToken );
         pLex->lasttok = yylval_ptr->string = hb_comp_tokenIdentifer( pToken );
         switch( iType )
         {
            case FUNCTION:
            case PROCEDURE:
               /* Clipper needs PROCEDURE in one context only */
               if( !pToken->pNext ||
                   HB_PP_TOKEN_TYPE( pToken->pNext->type ) != HB_PP_TOKEN_KEYWORD )
                  hb_compGenError( hb_comp_szErrors, 'E', HB_COMP_ERR_SYNTAX,
                                   pToken->value, NULL );
               pLex->iState = iType;
               return pLex->iState;

            case BEGINSEQ:
               if( pLex->iState == LOOKUP && pToken->pNext &&
                   HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                   pToken->pNext->len >= 4 && pToken->pNext->len <= 8 &&
                   hb_strnicmp( "SEQUENCE", pToken->pNext->value, pToken->pNext->len ) == 0 )
               {
                  hb_pp_tokenGet( pLex->pPP );
                  break;
               }
               iType = IDENTIFIER;
               break;

            case RECOVER:
               if( pLex->iState == LOOKUP )
               {
                  if( HB_PP_TOKEN_ISEOC( pToken->pNext ) )
                  {
                     pLex->iState = RECOVER;
                     return RECOVER;
                  }
                  else if( pToken->pNext &&
                           HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                           pToken->pNext->len >= 4 && pToken->pNext->len <= 5 &&
                           hb_strnicmp( "USING", pToken->pNext->value, pToken->pNext->len ) == 0 )
                  {
                     hb_pp_tokenGet( pLex->pPP );
                     pLex->iState = RECOVERUSING;
                     return RECOVERUSING;
                  }
               }
               iType = IDENTIFIER;
               break;

            case END:
               if( pLex->iState == LOOKUP )
               {
                  if( pToken->pNext &&
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                      pToken->pNext->len >= 4 && pToken->pNext->len <= 8 &&
                      hb_strnicmp( "SEQUENCE", pToken->pNext->value, pToken->pNext->len ) == 0 )
                  {
                     if( hb_comp_wSeqCounter == 0 )
                        hb_compGenError( hb_comp_szErrors, 'E',
                                         HB_COMP_ERR_ENDIF, NULL, NULL );
                     hb_pp_tokenGet( pLex->pPP );
                     pLex->iState = END;
                     return END;
                  }
                  else if( HB_PP_TOKEN_ISEOC( pToken->pNext ) ||
                           HB_PP_TOKEN_TYPE( pToken->pNext->type ) ==
                                                         HB_PP_TOKEN_KEYWORD )
                  {
                     pLex->iState = END;
                     return END;
                  }
                  /* Clipper does not like end[], end(), end->, end-- & end++ at
                     the begining of line */
                  if( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_PB ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_SB ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_INC ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_DEC ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_ALIAS )
                     hb_compGenError( hb_comp_szErrors, 'E',
                                      HB_COMP_ERR_ENDIF, NULL, NULL );
               }
               iType = IDENTIFIER;
               break;

            case ELSE:
               /* ELSE can be used in one context only */
               if( hb_comp_wIfCounter == 0 )
                  hb_compGenError( hb_comp_szErrors, 'E',
                                   HB_COMP_ERR_UNMATCHED_ELSE, NULL, NULL );
               pLex->iState = ELSE;
               return ELSE;

            case ELSEIF:
               /* ELSEIF can be used in one context only */
               if( hb_comp_wIfCounter == 0 )
                  hb_compGenError( hb_comp_szErrors, 'E',
                                   HB_COMP_ERR_UNMATCHED_ELSEIF, NULL, NULL );
               pLex->iState = ELSEIF;
               return ELSEIF;

            case ENDIF:
               /* ENDIF can be used in one context only */
               if( hb_comp_wIfCounter == 0 )
                  hb_compGenError( hb_comp_szErrors, 'E',
                                   HB_COMP_ERR_ENDIF, NULL, NULL );
               break;

            case ENDCASE:
               /* ENDCASE can be used in one context only */
               if( hb_comp_wCaseCounter == 0 )
                  hb_compGenError( hb_comp_szErrors, 'E',
                                   HB_COMP_ERR_ENDCASE, NULL, NULL );
               break;

            case ENDDO:
               /* ENDDO can be used in one context only */
               if( hb_comp_wWhileCounter == 0 )
                  hb_compGenError( hb_comp_szErrors, 'E',
                                   HB_COMP_ERR_ENDDO, NULL, NULL );
               break;

            case INIT:
               if( pLex->iState == LOOKUP && pToken->pNext &&
                   HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                   pToken->pNext->len >= 4 &&
                   ( hb_strnicmp( "FUNCTION", pToken->pNext->value,
                                  pToken->pNext->len ) == 0 ||
                     hb_strnicmp( "PROCEDURE", pToken->pNext->value,
                                  pToken->pNext->len ) == 0 ) )
               {
                  pLex->iState = INIT;
                  return INIT;
               }
               iType = IDENTIFIER;
               break;

            case FIELD:
               if( pToken->pNext && 
                   ( ( pLex->iState == LOOKUP &&
                       HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD ) ||
                     HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_ALIAS ) )
               {
                  pLex->iState = FIELD;
                  return FIELD;
               }
               iType = IDENTIFIER;
               break;

            case BREAK:
               /* NOTE: Clipper does not like break[] in any context
                *       There are no resons to limit this use in Harbour.
                */
               if( pLex->iState == LOOKUP &&
                   ( HB_PP_TOKEN_ISEOC( pToken->pNext ) ||
                     !( HB_PP_LEX_NEEDLEFT( pToken->pNext ) ||
                        HB_PP_TOKEN_TYPE( pToken->pNext->type ) ==
                                                      HB_PP_TOKEN_LEFT_PB ) ) )
               {
                  pLex->iState = BREAK;
                  return BREAK;
               }
               iType = IDENTIFIER;
               break;

            case CASE:
            case OTHERWISE:
               if( pLex->iState == LOOKUP &&
                   ( HB_PP_TOKEN_ISEOC( pToken->pNext ) ||
                     ( iType == CASE && !HB_PP_LEX_NEEDLEFT( pToken->pNext ) ) ) )
               {
                  if( hb_comp_wCaseCounter == 0 && hb_comp_wSwitchCounter == 0 )
                     hb_compGenError( hb_comp_szErrors, 'E',
                                      HB_COMP_ERR_CASE, NULL, NULL );
                  pLex->iState = iType;
                  return iType;
               }
               iType = IDENTIFIER;
               break;

            case FOR:
               if( pLex->iState == LOOKUP &&
                   !HB_PP_TOKEN_ISEOC( pToken->pNext ) &&
                   ( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD ||
                     /* Clipper always assume FOR (somevar):=1 TO ... here */
                     HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_PB ) )
               {
                  if( pToken->pNext->pNext &&
                      HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) != HB_PP_TOKEN_ASSIGN &&
                      HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) != HB_PP_TOKEN_EQ &&
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                      hb_stricmp( "EACH", pToken->pNext->value ) == 0 )
                  {
                     hb_pp_tokenGet( pLex->pPP );
                     pLex->iState = FOREACH;
                     return FOREACH;
                  }
                  pLex->iState = FOR;
                  return FOR;
               }
               iType = IDENTIFIER;
               break;

            case NEXT:
               if( pLex->iState == LOOKUP )
               {
                  if( HB_PP_TOKEN_ISEOC( pToken->pNext ) ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD )
                  {
                     if( hb_comp_wForCounter == 0 )
                        hb_compGenError( hb_comp_szErrors, 'E',
                        HB_COMP_ERR_NEXTFOR, NULL, NULL );
                     pLex->iState = iType;
                     return iType;
                  }
                  /* Clipper does not like NEXT[], NEXT(), NEXT->,
                     NEXT++ & NEXT-- at the begining of line */
                  if( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_PB ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_SB ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_INC ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_DEC ||
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_ALIAS )
                     hb_compGenError( hb_comp_szErrors, 'E',
                                      HB_COMP_ERR_NEXTFOR, NULL, NULL );
               }
               iType = IDENTIFIER;
               break;

            case RETURN:
            case DOSWITCH:
               if( pLex->iState == LOOKUP &&
                   ( HB_PP_TOKEN_ISEOC( pToken->pNext ) ||
                     !HB_PP_LEX_NEEDLEFT( pToken->pNext ) ) )
               {
                  pLex->iState = iType;
                  return iType;
               }
               iType = IDENTIFIER;
               break;

            case DECLARE:
               if( pLex->iState == LOOKUP )
               {
                  if( !HB_PP_TOKEN_ISEOC( pToken->pNext ) &&
                      ( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_MACROVAR ||
                        HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_MACROTEXT ||
                        ( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                          ( HB_PP_TOKEN_ISEOC( pToken->pNext->pNext ) ||
                            HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) == HB_PP_TOKEN_LEFT_SB ||
                            HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) == HB_PP_TOKEN_COMMA ||
                            HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) == HB_PP_TOKEN_SEND ||
                            ( HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                              hb_stricmp( "AS", pToken->pNext->pNext->value ) == 0 ) ) ) ) )
                  {
                     pLex->iState = PRIVATE;
                     return PRIVATE;
                  }
                  pLex->iState = DECLARE;
                  return DECLARE;
               }
               iType = IDENTIFIER;
               break;

            case DO:
               if( pLex->iState == LOOKUP && !HB_PP_TOKEN_ISEOC( pToken->pNext ) )
               {
                  if( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD )
                  {
                     if( pToken->pNext->len == 4 &&
                         hb_stricmp( "CASE", pToken->pNext->value ) == 0 )
                     {
                        if( HB_PP_TOKEN_ISEOC( pToken->pNext->pNext ) )
                        {
                           hb_pp_tokenGet( pLex->pPP );
                           pLex->iState = DOCASE;
                           return DOCASE;
                        }
                     }
                     else if( pToken->pNext->len >= 4 &&
                              pToken->pNext->len <= 5 &&
                              hb_strnicmp( "WHILE", pToken->pNext->value,
                                           pToken->pNext->len ) == 0 &&
                        /* check if it's not DO while [WITH <args>] */
                        !HB_PP_TOKEN_ISEOC( pToken->pNext->pNext ) &&
                        ( HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) != HB_PP_TOKEN_KEYWORD ||
                          pToken->pNext->pNext->len != 4 ||
                          hb_stricmp( "WITH", pToken->pNext->pNext->value ) != 0 ) )
                     {
                        /* DO WHILE <exp> */
                        hb_pp_tokenGet( pLex->pPP );
                        pLex->iState = WHILE;
                        return WHILE;
                     }
                     /* DO identifier [WITH <args>] */
                     pToken = hb_pp_tokenGet( pLex->pPP );
                     /* do not upper next token for case sensitive file systems */
                     /* hb_pp_tokenUpper( pToken ); */
                     pLex->lasttok = yylval_ptr->string = hb_comp_tokenIdentifer( pToken );
                     pLex->iState = IDENTIFIER;
                     return DOIDENT;
                  }
                  else if( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_MACROVAR ||
                           HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_MACROTEXT )
                  {
                     /* DO &id WITH */
                     pLex->iState = DO;
                     return DO;
                  }
               }
               iType = IDENTIFIER;
               break;

            case WHILE:
               if( pLex->iState == LOOKUP &&
                   !HB_PP_TOKEN_ISEOC( pToken->pNext ) &&
                   !HB_PP_LEX_NEEDLEFT( pToken->pNext ) )
               {
                  pLex->iState = WHILE;
                  return WHILE;
               }
               iType = IDENTIFIER;
               break;

            case WITH:
               if( !HB_PP_TOKEN_ISEOC( pToken->pNext ) )
               {
                  if( pLex->iState == LOOKUP &&
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                      ( pToken->pNext->pNext->len >= 4 ||
                        hb_strnicmp( "OBJECT", pToken->pNext->value,
                                     pToken->pNext->len ) != 0 ) )
                  {
                     pLex->iState = WITHOBJECT;
                     return WITHOBJECT;
                  }
                  else if( pLex->iState == MACROVAR ||
                           pLex->iState == MACROTEXT ||
                           pLex->iState == IDENTIFIER )
                  {
                     pLex->iState = WITH;
                     return WITH;
                  }
               }
               iType = IDENTIFIER;
               break;

            case IIF:
               if( pLex->iState == FUNCTION || pLex->iState == PROCEDURE ||
                   HB_PP_TOKEN_ISEOC( pToken->pNext ) )
                  hb_compGenError( hb_comp_szErrors, 'E',
                                   HB_COMP_ERR_SYNTAX, "IIF", NULL );
               else if( HB_PP_TOKEN_TYPE( pToken->pNext->type ) != HB_PP_TOKEN_LEFT_PB )
                  hb_compGenError( hb_comp_szErrors, 'E', HB_COMP_ERR_SYNTAX,
                                   pToken->pNext->value, NULL );
               else
               {
                  pLex->iState = IIF;
                  return IIF;
               }
               iType = IDENTIFIER;
               break;

            case IF:
               if( pLex->iState == FUNCTION || pLex->iState == PROCEDURE ||
                   HB_PP_TOKEN_ISEOC( pToken->pNext ) )
                  hb_compGenError( hb_comp_szErrors, 'E',
                                   HB_COMP_ERR_SYNTAX, "IF", NULL );
               else if( HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_PB )
               {
                  pLex->iState = pLex->iState == LOOKUP ? IF : IIF;
                  return pLex->iState;
               }
               else if( HB_PP_LEX_NEEDLEFT( pToken->pNext ) )
                  hb_compGenError( hb_comp_szErrors, 'E', HB_COMP_ERR_SYNTAX2,
                                   pToken->pNext->value, "IF" );
               else
               {
                  pLex->iState = IF;
                  return IF;
               }
               iType = IDENTIFIER;
               break;

            case PROCREQ:
               if( pToken->pNext &&
                   HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_PB )
               {
                  hb_pp_tokenGet( pLex->pPP );
                  pLex->iState = LSEPARATOR;
                  return PROCREQ;
               }
               iType = IDENTIFIER;
               break;

            case SELF:
               if( pToken->pNext && pToken->pNext->pNext &&
                   HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_LEFT_PB &&
                   HB_PP_TOKEN_TYPE( pToken->pNext->pNext->type ) == HB_PP_TOKEN_RIGHT_PB )
               {
                  hb_pp_tokenGet( pLex->pPP );
                  hb_pp_tokenGet( pLex->pPP );
                  pLex->iState = RSEPARATOR;
                  return SELF;
               }
               iType = IDENTIFIER;
               break;

            case AS_TYPE:
            {
               int iAs = hb_comp_asType( pToken->pNext, FALSE );
               if( iAs )
               {
                  pToken = hb_pp_tokenGet( pLex->pPP );
                  if( iAs == AS_ARRAY && pToken->pNext &&
                      HB_PP_TOKEN_TYPE( pToken->pNext->type ) == HB_PP_TOKEN_KEYWORD &&
                      hb_stricmp( "OF", pToken->pNext->value ) == 0 )
                  {
                     int iAsArray = hb_comp_asType( pToken->pNext->pNext, TRUE );
                     if( iAsArray )
                     {
                        hb_pp_tokenGet( pLex->pPP );
                        hb_pp_tokenGet( pLex->pPP );
                        return iAsArray;
                     }
                  }
                  return iAs;
               }
               iType = IDENTIFIER;
               break;
            }
            case DECLARE_CLASS:
            case DECLARE_MEMBER:
               pLex->iState = OPERATOR;
               return iType;

            case EXIT:
            case IN:
            case LOOP:
            case NIL:
            case STEP:
            case TO:
            case ANNOUNCE:
            case OPTIONAL:
            case DESCEND:
            case EXTERN:
            case LOCAL:
            case MEMVAR:
            case PARAMETERS:
            case PRIVATE:
            case PUBLIC:
            case STATIC:
               break;
         }
         pLex->iState = IDENTIFIER;
         return iType;
      }
      default:
         return pToken->value[ 0 ];
   }
}

void hb_compParserStop( HB_COMP_PTR pComp )
{
   HB_SYMBOL_UNUSED( pComp );
}
