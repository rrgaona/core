/*
 * $Id$
 */

/*
 * Harbour Project source code:
 * Mouse low-level module includer for GNU compilers
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

/* NOTE: This is only a container source file, don't put real program
         code here. */

#include "hbsetup.h"

#if   defined(HARBOUR_USE_STD_GTAPI)
   #include "mouse/mousestd.c"
#elif defined(HARBOUR_USE_DOS_GTAPI)
   #include "mouse/mousedos.c"
#elif defined(HARBOUR_USE_OS2_GTAPI)
   #include "mouse/mouseos2.c"
#elif defined(HARBOUR_USE_WIN_GTAPI)
   #include "mouse/mousewin.c"
/*
#elif defined(HARBOUR_USE_CRS_GTAPI)
   #include "mouse/mousecrs.c"
#elif defined(HARBOUR_USE_SLN_GTAPI)
   #include "mouse/mousesln.c"
*/
#else
   #include "mouse/mousestd.c"
#endif
