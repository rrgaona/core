/*
 * $Id$
 */

/* -------------------------------------------------------------------- */
/* WARNING: Automatically generated source file. DO NOT EDIT!           */
/*          Instead, edit corresponding .qth file,                      */
/*          or the generator tool itself, and run regenarate.           */
/* -------------------------------------------------------------------- */

/*
 * Harbour Project QT wrapper
 *
 * Copyright 2009-2010 Pritpal Bedi <bedipritpal@hotmail.com>
 * www - http://harbour-project.org
 *
 * For full copyright message and credits, see: CREDITS.txt
 *
 */

#include "hbqtcore.h"
#include "hbqtgui.h"

#if QT_VERSION >= 0x040500

/*
 *  enum ColorSpec { NormalColor, CustomColor, ManyColor }
 *  enum Type { Tty, GuiClient, GuiServer }
 */

/*
 *  Constructed[ 74/74 [ 100.00% ] ]
 *
 *
 *  *** Commented out protostypes ***
 *
 *  // QInputContext * inputContext () const
 *  // virtual bool macEventFilter ( EventHandlerCallRef, EventRef )
 *  // virtual bool qwsEventFilter ( QWSEvent * )
 *  // int qwsProcessEvent ( QWSEvent * )
 *  // void qwsSetCustomColors ( QRgb * colortable, int start, int numColors )
 *  // void setInputContext ( QInputContext * inputContext )
 *  // QWidgetList allWidgets ()
 *  //bool keypadNavigationEnabled ()
 *  //QDecoration & qwsDecoration ()
 *  //void qwsSetDecoration ( QDecoration * )
 *  //QDecoration * qwsSetDecoration ( const QString & decoration )
 *  //void setKeypadNavigationEnabled ( bool enable )
 *  // QWidgetList topLevelWidgets ()
 *  //int autoMaximizeThreshold () const
 *  //bool autoSipEnabled () const
 *  //void setAutoMaximizeThreshold ( const int threshold )
 *  //void setAutoSipEnabled ( const bool enabled )
 */

#include <QtCore/QPointer>

#include "hbapi.h"

#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QImage>
#include <QtGui/QPalette>
#include <QtGui/QApplication>
#include <QtCore/QLocale>
#include <QtGui/QIcon>

HB_EXTERN_BEGIN
extern HB_EXPORT QApplication * __hbqtgui_app( void );
HB_EXTERN_END

/*
 * QApplication ( int & argc, char ** argv )
 * QApplication ( int & argc, char ** argv, bool GUIenabled )
 * QApplication ( int & argc, char ** argv, Type type )
 * QApplication ( Display * display, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0 )
 * QApplication ( Display * display, int & argc, char ** argv, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0 )
 * virtual ~QApplication ()
*/


HB_FUNC( QT_QAPPLICATION_EXECUTE )
{
   hb_retni( __hbqtgui_app()->exec() );
}

HB_FUNC( QT_QAPPLICATION_QUIT )
{
   __hbqtgui_app()->quit();
}

typedef struct
{
   QPointer< QApplication > ph;
   bool bNew;
   PHBQT_GC_FUNC func;
   int type;
} HBQT_GC_T_QApplication;

HBQT_GC_FUNC( hbqt_gcRelease_QApplication )
{
   HB_SYMBOL_UNUSED( Cargo );
   HBQT_GC_T * p = ( HBQT_GC_T * ) Cargo;

   if( p && p->bNew )
      p->ph = NULL;
}

void * hbqt_gcAllocate_QApplication( void * pObj, bool bNew )
{
   HBQT_GC_T_QApplication * p = ( HBQT_GC_T_QApplication * ) hb_gcAllocate( sizeof( HBQT_GC_T_QApplication ), hbqt_gcFuncs() );

   new( & p->ph ) QPointer< QApplication >( ( QApplication * ) pObj );
   p->bNew = bNew;
   p->func = hbqt_gcRelease_QApplication;
   p->type = HBQT_TYPE_QApplication;

   return p;
}

HB_FUNC( QT_QAPPLICATION )
{
   //__HB_RETPTRGC__( ( QApplication * ) __hbqtgui_app() );
   hb_retptr( __hbqtgui_app() );
}

/* virtual void commitData ( QSessionManager & manager ) */
HB_FUNC( QT_QAPPLICATION_COMMITDATA )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->commitData( *hbqt_par_QSessionManager( 2 ) );
}

/* bool isSessionRestored () const */
HB_FUNC( QT_QAPPLICATION_ISSESSIONRESTORED )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retl( ( p )->isSessionRestored() );
}

/* virtual void saveState ( QSessionManager & manager ) */
HB_FUNC( QT_QAPPLICATION_SAVESTATE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->saveState( *hbqt_par_QSessionManager( 2 ) );
}

/* QString sessionId () const */
HB_FUNC( QT_QAPPLICATION_SESSIONID )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retstr_utf8( ( p )->sessionId().toUtf8().data() );
}

/* QString sessionKey () const */
HB_FUNC( QT_QAPPLICATION_SESSIONKEY )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retstr_utf8( ( p )->sessionKey().toUtf8().data() );
}

/* QString styleSheet () const */
HB_FUNC( QT_QAPPLICATION_STYLESHEET )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retstr_utf8( ( p )->styleSheet().toUtf8().data() );
}

/* QWidget * activeModalWidget () */
HB_FUNC( QT_QAPPLICATION_ACTIVEMODALWIDGET )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->activeModalWidget(), false ) );
}

/* QWidget * activePopupWidget () */
HB_FUNC( QT_QAPPLICATION_ACTIVEPOPUPWIDGET )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->activePopupWidget(), false ) );
}

/* QWidget * activeWindow () */
HB_FUNC( QT_QAPPLICATION_ACTIVEWINDOW )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->activeWindow(), false ) );
}

/* void alert ( QWidget * widget, int msec = 0 ) */
HB_FUNC( QT_QAPPLICATION_ALERT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->alert( hbqt_par_QWidget( 2 ), hb_parni( 3 ) );
}

/* void beep () */
HB_FUNC( QT_QAPPLICATION_BEEP )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->beep();
}

/* void changeOverrideCursor ( const QCursor & cursor ) */
HB_FUNC( QT_QAPPLICATION_CHANGEOVERRIDECURSOR )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->changeOverrideCursor( *hbqt_par_QCursor( 2 ) );
}

/* QClipboard * clipboard () */
HB_FUNC( QT_QAPPLICATION_CLIPBOARD )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QClipboard( ( p )->clipboard(), false ) );
}

/* int colorSpec () */
HB_FUNC( QT_QAPPLICATION_COLORSPEC )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->colorSpec() );
}

/* int cursorFlashTime () */
HB_FUNC( QT_QAPPLICATION_CURSORFLASHTIME )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->cursorFlashTime() );
}

/* QDesktopWidget * desktop () */
HB_FUNC( QT_QAPPLICATION_DESKTOP )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QDesktopWidget( ( p )->desktop(), false ) );
}

/* bool desktopSettingsAware () */
HB_FUNC( QT_QAPPLICATION_DESKTOPSETTINGSAWARE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retl( ( p )->desktopSettingsAware() );
}

/* int doubleClickInterval () */
HB_FUNC( QT_QAPPLICATION_DOUBLECLICKINTERVAL )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->doubleClickInterval() );
}

/* int exec () */
HB_FUNC( QT_QAPPLICATION_EXEC )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->exec() );
}

/* QWidget * focusWidget () */
HB_FUNC( QT_QAPPLICATION_FOCUSWIDGET )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->focusWidget(), false ) );
}

/* QFont font () */
HB_FUNC( QT_QAPPLICATION_FONT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QFont( new QFont( ( p )->font() ), true ) );
}

/* QFont font ( const QWidget * widget ) */
HB_FUNC( QT_QAPPLICATION_FONT_1 )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QFont( new QFont( ( p )->font( hbqt_par_QWidget( 2 ) ) ), true ) );
}

/* QFont font ( const char * className ) */
HB_FUNC( QT_QAPPLICATION_FONT_2 )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QFont( new QFont( ( p )->font( ( const char * ) hb_parc( 2 ) ) ), true ) );
}

/* QFontMetrics fontMetrics () */
HB_FUNC( QT_QAPPLICATION_FONTMETRICS )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QFontMetrics( new QFontMetrics( ( p )->fontMetrics() ), true ) );
}

/* QSize globalStrut () */
HB_FUNC( QT_QAPPLICATION_GLOBALSTRUT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QSize( new QSize( ( p )->globalStrut() ), true ) );
}

/* bool isEffectEnabled ( Qt::UIEffect effect ) */
HB_FUNC( QT_QAPPLICATION_ISEFFECTENABLED )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retl( ( p )->isEffectEnabled( ( Qt::UIEffect ) hb_parni( 2 ) ) );
}

/* bool isLeftToRight () */
HB_FUNC( QT_QAPPLICATION_ISLEFTTORIGHT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retl( ( p )->isLeftToRight() );
}

/* bool isRightToLeft () */
HB_FUNC( QT_QAPPLICATION_ISRIGHTTOLEFT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retl( ( p )->isRightToLeft() );
}

/* Qt::LayoutDirection keyboardInputDirection () */
HB_FUNC( QT_QAPPLICATION_KEYBOARDINPUTDIRECTION )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( Qt::LayoutDirection ) ( p )->keyboardInputDirection() );
}

/* int keyboardInputInterval () */
HB_FUNC( QT_QAPPLICATION_KEYBOARDINPUTINTERVAL )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->keyboardInputInterval() );
}

/* QLocale keyboardInputLocale () */
HB_FUNC( QT_QAPPLICATION_KEYBOARDINPUTLOCALE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QLocale( new QLocale( ( p )->keyboardInputLocale() ), true ) );
}

/* Qt::KeyboardModifiers keyboardModifiers () */
HB_FUNC( QT_QAPPLICATION_KEYBOARDMODIFIERS )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( Qt::KeyboardModifiers ) ( p )->keyboardModifiers() );
}

/* Qt::LayoutDirection layoutDirection () */
HB_FUNC( QT_QAPPLICATION_LAYOUTDIRECTION )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( Qt::LayoutDirection ) ( p )->layoutDirection() );
}

/* Qt::MouseButtons mouseButtons () */
HB_FUNC( QT_QAPPLICATION_MOUSEBUTTONS )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( Qt::MouseButtons ) ( p )->mouseButtons() );
}

/* QCursor * overrideCursor () */
HB_FUNC( QT_QAPPLICATION_OVERRIDECURSOR )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QCursor( ( p )->overrideCursor(), false ) );
}

/* QPalette palette () */
HB_FUNC( QT_QAPPLICATION_PALETTE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QPalette( new QPalette( ( p )->palette() ), true ) );
}

/* QPalette palette ( const QWidget * widget ) */
HB_FUNC( QT_QAPPLICATION_PALETTE_1 )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QPalette( new QPalette( ( p )->palette( hbqt_par_QWidget( 2 ) ) ), true ) );
}

/* QPalette palette ( const char * className ) */
HB_FUNC( QT_QAPPLICATION_PALETTE_2 )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QPalette( new QPalette( ( p )->palette( ( const char * ) hb_parc( 2 ) ) ), true ) );
}

/* bool quitOnLastWindowClosed () */
HB_FUNC( QT_QAPPLICATION_QUITONLASTWINDOWCLOSED )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retl( ( p )->quitOnLastWindowClosed() );
}

/* void restoreOverrideCursor () */
HB_FUNC( QT_QAPPLICATION_RESTOREOVERRIDECURSOR )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->restoreOverrideCursor();
}

/* void setActiveWindow ( QWidget * active ) */
HB_FUNC( QT_QAPPLICATION_SETACTIVEWINDOW )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setActiveWindow( hbqt_par_QWidget( 2 ) );
}

/* void setColorSpec ( int spec ) */
HB_FUNC( QT_QAPPLICATION_SETCOLORSPEC )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setColorSpec( hb_parni( 2 ) );
}

/* void setCursorFlashTime ( int ) */
HB_FUNC( QT_QAPPLICATION_SETCURSORFLASHTIME )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setCursorFlashTime( hb_parni( 2 ) );
}

/* void setDesktopSettingsAware ( bool on ) */
HB_FUNC( QT_QAPPLICATION_SETDESKTOPSETTINGSAWARE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setDesktopSettingsAware( hb_parl( 2 ) );
}

/* void setDoubleClickInterval ( int ) */
HB_FUNC( QT_QAPPLICATION_SETDOUBLECLICKINTERVAL )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setDoubleClickInterval( hb_parni( 2 ) );
}

/* void setEffectEnabled ( Qt::UIEffect effect, bool enable = true ) */
HB_FUNC( QT_QAPPLICATION_SETEFFECTENABLED )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setEffectEnabled( ( Qt::UIEffect ) hb_parni( 2 ), hb_parl( 3 ) );
}

/* void setFont ( const QFont & font, const char * className = 0 ) */
HB_FUNC( QT_QAPPLICATION_SETFONT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setFont( *hbqt_par_QFont( 2 ), ( const char * ) hb_parc( 3 ) );
}

/* void setGlobalStrut ( const QSize & ) */
HB_FUNC( QT_QAPPLICATION_SETGLOBALSTRUT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setGlobalStrut( *hbqt_par_QSize( 2 ) );
}

/* void setGraphicsSystem ( const QString & system ) */
HB_FUNC( QT_QAPPLICATION_SETGRAPHICSSYSTEM )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
   {
      void * pText;
      ( p )->setGraphicsSystem( hb_parstr_utf8( 2, &pText, NULL ) );
      hb_strfree( pText );
   }
}

/* void setKeyboardInputInterval ( int ) */
HB_FUNC( QT_QAPPLICATION_SETKEYBOARDINPUTINTERVAL )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setKeyboardInputInterval( hb_parni( 2 ) );
}

/* void setLayoutDirection ( Qt::LayoutDirection direction ) */
HB_FUNC( QT_QAPPLICATION_SETLAYOUTDIRECTION )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setLayoutDirection( ( Qt::LayoutDirection ) hb_parni( 2 ) );
}

/* void setOverrideCursor ( const QCursor & cursor ) */
HB_FUNC( QT_QAPPLICATION_SETOVERRIDECURSOR )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setOverrideCursor( *hbqt_par_QCursor( 2 ) );
}

/* void setPalette ( const QPalette & palette, const char * className = 0 ) */
HB_FUNC( QT_QAPPLICATION_SETPALETTE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setPalette( *hbqt_par_QPalette( 2 ), ( const char * ) hb_parc( 3 ) );
}

/* void setQuitOnLastWindowClosed ( bool quit ) */
HB_FUNC( QT_QAPPLICATION_SETQUITONLASTWINDOWCLOSED )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setQuitOnLastWindowClosed( hb_parl( 2 ) );
}

/* void setStartDragDistance ( int l ) */
HB_FUNC( QT_QAPPLICATION_SETSTARTDRAGDISTANCE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setStartDragDistance( hb_parni( 2 ) );
}

/* void setStartDragTime ( int ms ) */
HB_FUNC( QT_QAPPLICATION_SETSTARTDRAGTIME )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setStartDragTime( hb_parni( 2 ) );
}

/* void setStyle ( QStyle * style ) */
HB_FUNC( QT_QAPPLICATION_SETSTYLE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setStyle( hbqt_par_QStyle( 2 ) );
}

/* QStyle * setStyle ( const QString & style ) */
HB_FUNC( QT_QAPPLICATION_SETSTYLE_1 )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
   {
      void * pText;
      hb_retptrGC( hbqt_gcAllocate_QStyle( ( p )->setStyle( hb_parstr_utf8( 2, &pText, NULL ) ), false ) );
      hb_strfree( pText );
   }
}

/* void setWheelScrollLines ( int ) */
HB_FUNC( QT_QAPPLICATION_SETWHEELSCROLLLINES )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setWheelScrollLines( hb_parni( 2 ) );
}

/* void setWindowIcon ( const QIcon & icon ) */
HB_FUNC( QT_QAPPLICATION_SETWINDOWICON )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->setWindowIcon( ( HB_ISCHAR( 2 ) ? QIcon( hbqt_par_QString( 2 ) ) : *hbqt_par_QIcon( 2 )) );
}

/* int startDragDistance () */
HB_FUNC( QT_QAPPLICATION_STARTDRAGDISTANCE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->startDragDistance() );
}

/* int startDragTime () */
HB_FUNC( QT_QAPPLICATION_STARTDRAGTIME )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->startDragTime() );
}

/* QStyle * style () */
HB_FUNC( QT_QAPPLICATION_STYLE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QStyle( ( p )->style(), false ) );
}

/* void syncX () */
HB_FUNC( QT_QAPPLICATION_SYNCX )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->syncX();
}

/* QWidget * topLevelAt ( const QPoint & point ) */
HB_FUNC( QT_QAPPLICATION_TOPLEVELAT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->topLevelAt( *hbqt_par_QPoint( 2 ) ), false ) );
}

/* QWidget * topLevelAt ( int x, int y ) */
HB_FUNC( QT_QAPPLICATION_TOPLEVELAT_1 )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->topLevelAt( hb_parni( 2 ), hb_parni( 3 ) ), false ) );
}

/* Type type () */
HB_FUNC( QT_QAPPLICATION_TYPE )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( QApplication::Type ) ( p )->type() );
}

/* int wheelScrollLines () */
HB_FUNC( QT_QAPPLICATION_WHEELSCROLLLINES )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retni( ( p )->wheelScrollLines() );
}

/* QWidget * widgetAt ( const QPoint & point ) */
HB_FUNC( QT_QAPPLICATION_WIDGETAT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->widgetAt( *hbqt_par_QPoint( 2 ) ), false ) );
}

/* QWidget * widgetAt ( int x, int y ) */
HB_FUNC( QT_QAPPLICATION_WIDGETAT_1 )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QWidget( ( p )->widgetAt( hb_parni( 2 ), hb_parni( 3 ) ), false ) );
}

/* QIcon windowIcon () */
HB_FUNC( QT_QAPPLICATION_WINDOWICON )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QIcon( new QIcon( ( p )->windowIcon() ), true ) );
}

/* void aboutQt () */
HB_FUNC( QT_QAPPLICATION_ABOUTQT )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->aboutQt();
}

/* void closeAllWindows () */
HB_FUNC( QT_QAPPLICATION_CLOSEALLWINDOWS )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
      ( p )->closeAllWindows();
}

/* void setStyleSheet ( const QString & sheet ) */
HB_FUNC( QT_QAPPLICATION_SETSTYLESHEET )
{
   QApplication * p = hbqt_par_QApplication( 1 );
   if( p )
   {
      void * pText;
      ( p )->setStyleSheet( hb_parstr_utf8( 2, &pText, NULL ) );
      hb_strfree( pText );
   }
}


#endif /* #if QT_VERSION >= 0x040500 */
