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
 *  enum Flow { LeftToRight, TopToBottom }
 *  enum LayoutMode { SinglePass, Batched }
 *  enum Movement { Static, Free, Snap }
 *  enum ResizeMode { Fixed, Adjust }
 *  enum ViewMode { ListMode, IconMode }
 */

/*
 *  Constructed[ 29/29 [ 100.00% ] ]
 *
 */

#include <QtCore/QPointer>

#include <QtGui/QListView>


/*
 * QListView ( QWidget * parent = 0 )
 * ~QListView ()
 */

typedef struct
{
   QPointer< QListView > ph;
   bool bNew;
   PHBQT_GC_FUNC func;
   int type;
} HBQT_GC_T_QListView;

HBQT_GC_FUNC( hbqt_gcRelease_QListView )
{
   QListView  * ph = NULL;
   HBQT_GC_T_QListView * p = ( HBQT_GC_T_QListView * ) Cargo;

   if( p && p->bNew && p->ph )
   {
      ph = p->ph;
      if( ph )
      {
         const QMetaObject * m = ( ph )->metaObject();
         if( ( QString ) m->className() != ( QString ) "QObject" )
         {
            delete ( p->ph );
            p->ph = NULL;
         }
         else
            p->ph = NULL;
      }
      else
         p->ph = NULL;
   }
   else
      p->ph = NULL;
}

void * hbqt_gcAllocate_QListView( void * pObj, bool bNew )
{
   HBQT_GC_T_QListView * p = ( HBQT_GC_T_QListView * ) hb_gcAllocate( sizeof( HBQT_GC_T_QListView ), hbqt_gcFuncs() );

   new( & p->ph ) QPointer< QListView >( ( QListView * ) pObj );
   p->bNew = bNew;
   p->func = hbqt_gcRelease_QListView;
   p->type = HBQT_TYPE_QListView;

   return p;
}

HB_FUNC( QT_QLISTVIEW )
{
   QListView * pObj = NULL;

   pObj = new QListView( hbqt_par_QWidget( 1 ) ) ;

   hb_retptrGC( hbqt_gcAllocate_QListView( ( void * ) pObj, true ) );
}

/* int batchSize () const */
HB_FUNC( QT_QLISTVIEW_BATCHSIZE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( p )->batchSize() );
}

/* void clearPropertyFlags () */
HB_FUNC( QT_QLISTVIEW_CLEARPROPERTYFLAGS )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->clearPropertyFlags();
}

/* Flow flow () const */
HB_FUNC( QT_QLISTVIEW_FLOW )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( QListView::Flow ) ( p )->flow() );
}

/* QSize gridSize () const */
HB_FUNC( QT_QLISTVIEW_GRIDSIZE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retptrGC( hbqt_gcAllocate_QSize( new QSize( ( p )->gridSize() ), true ) );
}

/* bool isRowHidden ( int row ) const */
HB_FUNC( QT_QLISTVIEW_ISROWHIDDEN )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retl( ( p )->isRowHidden( hb_parni( 2 ) ) );
}

/* bool isSelectionRectVisible () const */
HB_FUNC( QT_QLISTVIEW_ISSELECTIONRECTVISIBLE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retl( ( p )->isSelectionRectVisible() );
}

/* bool isWrapping () const */
HB_FUNC( QT_QLISTVIEW_ISWRAPPING )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retl( ( p )->isWrapping() );
}

/* LayoutMode layoutMode () const */
HB_FUNC( QT_QLISTVIEW_LAYOUTMODE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( QListView::LayoutMode ) ( p )->layoutMode() );
}

/* int modelColumn () const */
HB_FUNC( QT_QLISTVIEW_MODELCOLUMN )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( p )->modelColumn() );
}

/* Movement movement () const */
HB_FUNC( QT_QLISTVIEW_MOVEMENT )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( QListView::Movement ) ( p )->movement() );
}

/* ResizeMode resizeMode () const */
HB_FUNC( QT_QLISTVIEW_RESIZEMODE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( QListView::ResizeMode ) ( p )->resizeMode() );
}

/* void setBatchSize ( int batchSize ) */
HB_FUNC( QT_QLISTVIEW_SETBATCHSIZE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setBatchSize( hb_parni( 2 ) );
}

/* void setFlow ( Flow flow ) */
HB_FUNC( QT_QLISTVIEW_SETFLOW )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setFlow( ( QListView::Flow ) hb_parni( 2 ) );
}

/* void setGridSize ( const QSize & size ) */
HB_FUNC( QT_QLISTVIEW_SETGRIDSIZE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setGridSize( *hbqt_par_QSize( 2 ) );
}

/* void setLayoutMode ( LayoutMode mode ) */
HB_FUNC( QT_QLISTVIEW_SETLAYOUTMODE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setLayoutMode( ( QListView::LayoutMode ) hb_parni( 2 ) );
}

/* void setModelColumn ( int column ) */
HB_FUNC( QT_QLISTVIEW_SETMODELCOLUMN )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setModelColumn( hb_parni( 2 ) );
}

/* void setMovement ( Movement movement ) */
HB_FUNC( QT_QLISTVIEW_SETMOVEMENT )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setMovement( ( QListView::Movement ) hb_parni( 2 ) );
}

/* void setResizeMode ( ResizeMode mode ) */
HB_FUNC( QT_QLISTVIEW_SETRESIZEMODE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setResizeMode( ( QListView::ResizeMode ) hb_parni( 2 ) );
}

/* void setRowHidden ( int row, bool hide ) */
HB_FUNC( QT_QLISTVIEW_SETROWHIDDEN )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setRowHidden( hb_parni( 2 ), hb_parl( 3 ) );
}

/* void setSelectionRectVisible ( bool show ) */
HB_FUNC( QT_QLISTVIEW_SETSELECTIONRECTVISIBLE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setSelectionRectVisible( hb_parl( 2 ) );
}

/* void setSpacing ( int space ) */
HB_FUNC( QT_QLISTVIEW_SETSPACING )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setSpacing( hb_parni( 2 ) );
}

/* void setUniformItemSizes ( bool enable ) */
HB_FUNC( QT_QLISTVIEW_SETUNIFORMITEMSIZES )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setUniformItemSizes( hb_parl( 2 ) );
}

/* void setViewMode ( ViewMode mode ) */
HB_FUNC( QT_QLISTVIEW_SETVIEWMODE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setViewMode( ( QListView::ViewMode ) hb_parni( 2 ) );
}

/* void setWordWrap ( bool on ) */
HB_FUNC( QT_QLISTVIEW_SETWORDWRAP )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setWordWrap( hb_parl( 2 ) );
}

/* void setWrapping ( bool enable ) */
HB_FUNC( QT_QLISTVIEW_SETWRAPPING )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      ( p )->setWrapping( hb_parl( 2 ) );
}

/* int spacing () const */
HB_FUNC( QT_QLISTVIEW_SPACING )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( p )->spacing() );
}

/* bool uniformItemSizes () const */
HB_FUNC( QT_QLISTVIEW_UNIFORMITEMSIZES )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retl( ( p )->uniformItemSizes() );
}

/* ViewMode viewMode () const */
HB_FUNC( QT_QLISTVIEW_VIEWMODE )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retni( ( QListView::ViewMode ) ( p )->viewMode() );
}

/* bool wordWrap () const */
HB_FUNC( QT_QLISTVIEW_WORDWRAP )
{
   QListView * p = hbqt_par_QListView( 1 );
   if( p )
      hb_retl( ( p )->wordWrap() );
}


#endif /* #if QT_VERSION >= 0x040500 */
