/*
 * $Id$
 */

/*
 * Harbour Project source code:
 * Networking API
 *
 * Copyright 2009 Viktor Szakats (harbour.01 syenar.hu)
 * www - http://www.harbour-project.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA (or visit the web site http://www.gnu.org/).
 *
 * As a special exception, the Harbour Project gives permission for
 * additional uses of the text contained in its release of Harbour.
 *
 * The exception is that, if you link the Harbour libraries with other
 * files to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the Harbour library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * This exception applies only to the code released by the Harbour
 * Project under the name Harbour.  If you copy code from other
 * Harbour Project or Free Software Foundation releases into a copy of
 * Harbour, as the General Public License permits, the exception does
 * not apply to the code that you add in this way.  To avoid misleading
 * anyone as to the status of such modified files, you must delete
 * this exception notice from them.
 *
 * If you write modifications of your own for Harbour, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.
 *
 */

#ifndef HB_APINET_H_
#define HB_APINET_H_

#include "hbapi.h"
#include "hbapiitm.h"

#if ! defined( HB_OS_DOS )

#define HB_API_NET

HB_EXTERN_BEGIN

#if defined( HB_OS_WIN )
   #define HB_SOCKET_T SOCKET

   #define _WINSOCKAPI_  /* Prevents inclusion of winsock.h in windows.h */
   #include <winsock2.h>
   #include <windows.h>
#else
   #define HB_SOCKET_T int

   #include <errno.h>
   #if defined( HB_OS_OS2 )
      #if defined( __WATCOMC__ )
         #include <types.h>
         #include <nerrno.h>
      #endif
      #include <sys/types.h>
      #include <sys/socket.h>
      #include <sys/select.h>
      #include <sys/ioctl.h>
   #else
      #include <sys/types.h>
      #include <sys/socket.h>
   #endif
   #include <netdb.h>
   #include <netinet/in.h>
   #include <arpa/inet.h>
   #include <unistd.h>
#endif

typedef struct _HB_SOCKET
{
   HB_SOCKET_T        com;
   struct sockaddr_in remote;
   char               szErrorText[ 128 ];
   const char *       pszErrorText;
   int                iErrorCode;
   int                iCount;
   int                iTimeout;
   int                iTimeLimit;
   PHB_ITEM           pPeriodicBlock;
} HB_SOCKET, * PHB_SOCKET;

extern int hb_selectReadFD( HB_SOCKET_T fd, int iTimeout );
extern int hb_selectWriteFD( HB_SOCKET_T fd, int iTimeout );
extern int hb_selectReadSocket( PHB_SOCKET pSocket );
extern int hb_selectWriteSocket( PHB_SOCKET pSocket );

HB_EXTERN_END

#endif

#endif /* HB_APINET_H_ */
