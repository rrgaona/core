/*
 * $Id$
 */

/*
 * Harbour Project source code:
 * SPACE() function
 *
 * Copyright 1999 Antonio Linares <alinares@fivetech.com>
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

#include "hbapi.h"
#include "hbapiitm.h"
#include "hbapierr.h"

/* returns n copies of a single space */
/* TEST: QOUT( "space( 5 ) = '" + space( 5 ) + "'" ) */
HB_FUNC( SPACE )
{
   if( ISNUM( 1 ) )
   {
      long lLen = hb_parnl( 1 );

      if( lLen > 0 )
      {
         char * szResult = ( char * ) hb_xgrab( lLen + 1 );

         /* NOTE: String overflow could never occure since a string can
                  be as large as ULONG_MAX, and the maximum length that
                  can be specified is LONG_MAX here. [vszakats] */
         /* hb_errRT_BASE( EG_STROVERFLOW, 1233, NULL, "SPACE" ); */

         hb_xmemset( szResult, ' ', lLen );
         hb_retclen( szResult, lLen );
         hb_xfree( szResult );
      }
      else
         hb_retc( "" );
   }
   else
   {
      PHB_ITEM pResult = hb_errRT_BASE_Subst( EG_ARG, 1105, NULL, "SPACE" );

      if( pResult )
      {
         hb_itemReturn( pResult );
         hb_itemRelease( pResult );
      }
   }
}
