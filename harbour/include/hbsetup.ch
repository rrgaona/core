/*
 * $Id$
 */

/*
 * Harbour Project source code:
 * Header file for runtime configuration, common for Harbour and C level.
 *
 * Copyright 1999 Victor Szakats <info@szelvesz.hu>
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

/* NOTE: This file is also used by C code. */

#ifndef HB_SETUP_CH_
#define HB_SETUP_CH_

/* NOTE: You can select here, which features you want to include of the 
         different Clipper implementations. */

#define HB_EXTENSION              /* Enable Harbour extensions */

#define HB_C52_UNDOC              /* Enable CA-Cl*pper 5.2e undocumented features */
/* #define HB_C52_STRICT */       /* Enable CA-Cl*pper 5.2e strict compatibility */

#define HB_COMPAT_C53             /* Enable CA-Cl*pper 5.3x extensions */
#define HB_COMPAT_XPP             /* Enable Alaska Xbase++ extensions */
/* #define HB_COMPAT_VO */        /* Enable CA-VO extensions */
/* #define HB_COMPAT_FLAGSHIP */  /* Enable Flagship extensions */
/* #define HB_COMPAT_FOXPRO */    /* Enable FoxPro extensions */
/* #define HB_COMPAT_DBASE */     /* Enable dBase extensions */

/* NOTE: HB_SHORTNAMES must be defined manually if the symbol name length is 
         set to 10 explicitly and not through the HB_C52_STRICT option 
         [vszakats] */

/* Turn on short names support for the class engine */
#ifdef HB_C52_STRICT
   #define HB_SHORTNAMES
#endif

#define HB_CLS_MASKHIDDEN         /* Disallow heritence of hidden variables */

#endif /* HB_SETUP_CH_ */

