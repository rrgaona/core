/*
 * $Id$
 */

/*
 * Harbour Project source code:
 * MemoEdit() function
 *
 * Copyright 2000 Maurilio Longo <maurilio.longo@libero.it>
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

/* TODO: MemoEdit() is not compatible with clipper one.
         Needs a lot more work to become */

#include "common.ch"
#include "inkey.ch"

FUNCTION MemoEdit(cString,;
                  nTop, nLeft,;
                  nBottom, nRight,;
                  lEditMode,;
                  cUserFunction,;
                  nLineLength,;
                  nTabSize,;
                  nTextBuffRow,;
                  nTextBuffColumn,;
                  nWindowRow,;
                  nWindowColumn)

   LOCAL oEd

   DEFAULT nTop            TO 0
   DEFAULT nLeft           TO 0
   DEFAULT nBottom         TO MaxRow()
   DEFAULT nRight          TO MaxCol()
   DEFAULT lEditMode       TO .T.
   DEFAULT nLineLength     TO nRight - nLeft
   DEFAULT nTabSize        TO 4
   DEFAULT nTextBuffRow    TO 1
   DEFAULT nTextBuffColumn TO 0
   DEFAULT nWindowRow      TO 0
   DEFAULT nWindowColumn   TO nTextBuffColumn

   // Original MemoEdit() converts Tabs into spaces
   oEd := TEditor():New(StrTran(cString, Chr(K_TAB), Space(1)), nTop, nLeft, nBottom, nRight, lEditMode, nil, nLineLength, nTabSize)
   oEd:RefreshWindow()

   if ! ISLOGICAL(cUserFunction) .OR. cUserFunction == .T.
      oEd:Edit()
      if oEd:lSaved
         cString := oEd:GetText()
         // dbu tests for LastKey() == K_CTRL_END, so I try to make it happy
         KEYBOARD K_CTRL_END
         Inkey()
      endif
   endif

   RETURN cString

