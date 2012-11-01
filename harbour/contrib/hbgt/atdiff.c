/*
 * $Id$
 */

/*
 * GT CLIPPER STANDARD HEADER
 *
 * File......: atdiff.c
 * Author....: Andy M Leighton
 * BBS.......: The Dark Knight Returns
 * Net/Node..: 050/069
 * User Name.: Andy Leighton
 * Date......: 23/05/93
 * Revision..: 1.00
 *
 * This is an original work by Andy Leighton and is placed in the
 * public domain.
 */

#include "hbapi.h"

HB_FUNC( GT_ATDIFF )
{
   const char * s1, * s2;
   HB_ISIZ      pos, len;

   if( HB_ISCHAR( 1 ) && HB_ISCHAR( 2 ) )
   {
      s1  = hb_parc( 1 );
      s2  = hb_parc( 2 );
      len = hb_parclen( 2 );

      /*
         loop through comparing both strings

         NOTE: pos starts at 1, so as to return a string index
               for CLIPPER
       */

      for( pos = 1; ( pos <= len ) && ( *s1 == *s2 ); s2++, s1++ )
         pos++;

      if( pos > len )               /* strings match exactly!!! */
         hb_retns( 0 );
      else
         hb_retns( pos );
   }
   else
   {
      hb_retns( -1 );                 /* parameter mismatch - error -1 */
   }
}
