/*
 * $Id$
 */

/*
 * xHarbour Project source code:
 * 
 *
 * Copyright 2003 Przemyslaw Czerpak <druzus@acn.waw.pl>
 * www - http://www.xharbour.org
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

#include "hbapi.h"
#include "hbapicdp.h"

#define NUMBER_OF_CHARS    256

static USHORT uniCodes[NUMBER_OF_CHARS] = {
   0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
   0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
   0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
   0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
   0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
   0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
   0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
   0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
   0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
   0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
   0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
   0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
   0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
   0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
   0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
   0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
   0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,
   0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F,
   0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,
   0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F,
   0x00A0, 0x0104, 0x02D8, 0x0141, 0x00A4, 0x013D, 0x015A, 0x00A7,
   0x00A8, 0x0160, 0x015E, 0x0164, 0x0179, 0x00AD, 0x017D, 0x017B,
   0x00B0, 0x0105, 0x02DB, 0x0142, 0x00B4, 0x013E, 0x015B, 0x02C7,
   0x00B8, 0x0161, 0x015F, 0x0165, 0x017A, 0x02DD, 0x017E, 0x017C,
   0x0154, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0139, 0x0106, 0x00C7,
   0x010C, 0x00C9, 0x0118, 0x00CB, 0x011A, 0x00CD, 0x00CE, 0x010E,
   0x0110, 0x0143, 0x0147, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x00D7,
   0x0158, 0x016E, 0x00DA, 0x0170, 0x00DC, 0x00DD, 0x0162, 0x00DF,
   0x0155, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x013A, 0x0107, 0x00E7,
   0x010D, 0x00E9, 0x0119, 0x00EB, 0x011B, 0x00ED, 0x00EE, 0x010F,
   0x0111, 0x0144, 0x0148, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x00F7,
   0x0159, 0x016F, 0x00FA, 0x0171, 0x00FC, 0x00FD, 0x0163, 0x02D9,
};

HB_UNITABLE hb_uniTbl_8859_2 = { CPID_8859_2, NUMBER_OF_CHARS, FALSE, uniCodes };
