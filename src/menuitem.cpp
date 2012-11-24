/***************************************************************************
 *   Copyright (C) 2005 by Engin AYDOGAN   *
 *   engin@bzzzt.biz   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <qlabel.h>
#include <qlayout.h>
#include <qpainter.h>
#include <qtimer.h>


#include <kapplication.h>
#include <kstringhandler.h>
#include <kdesktopfile.h>
#include <kiconloader.h>
#include <kglobal.h>
#include <kdebug.h>

#include <limits>

#include "recentapps.h"
#include "popupmanager.h"
#include "menuitem.h"

MenuItem::MenuItem( QWidget* p,
					KDesktopFile* desktop,
					const QColor& hl,
					QFrame* sub,
					bool updateRecent )
 : QButton( p, desktop->readName()  ), m_desktop( desktop ),
   m_mouseOver( false ), m_offset( 5 ), m_secOffset( 2 ), m_sub( sub ), m_updateRecent( updateRecent ),
   m_descFontOffset(2), m_descLines(2), m_arrowIcon( "1rightarrow" )
{
	setTitle( m_desktop->readName() );
	kdDebug() << k_funcinfo << "C-TOR" << m_desktop->readName() << endl; // DEBUG
	if( m_desktop->readComment() != QString::null )
	{
		setDescription( m_desktop->readComment() );
	}
	else
	{
		setDescription( m_desktop->readGenericName() );
	}

	setIcon( m_desktop->readIcon() );

	QColor bg = m_desktop->readColorEntry( "background" );
	if( bg.isValid() )
		setPaletteBackgroundColor( bg );

	setHighlightColor( m_desktop->readColorEntry( "highlight" ) );

	if( hl.isValid() )
		setHighlightColor( hl );
	if( m_sub )
	{
		m_sub->installEventFilter( this );
		PopupManager::add( m_sub );
	}
}

MenuItem::MenuItem( QWidget* p,
					const QString& title,
					const QString& comment,
					const QString& icon,
					const QColor& hl,
					QFrame* sub,
					bool updateRecent )
 : QButton( p, title  ), m_desktop( 0 ),
   m_mouseOver( false ), m_offset( 5 ), m_secOffset( 2 ), m_sub( sub ),
   m_updateRecent( updateRecent ), m_descFontOffset(2),
   m_descLines(2), m_arrowIcon( "1rightarrow" )
{
	kdDebug() << k_funcinfo << endl;

	setIcon( icon );
	setTitle( title );
	setDescription( comment );

	if( hl.isValid() )
		setHighlightColor( hl );
	if( m_sub )
	{
		m_sub->installEventFilter( this );
		PopupManager::add( m_sub );
	}
}

MenuItem::~MenuItem()
{
	kdDebug() << k_funcinfo << "D-TOR " << title() << endl;
	if( m_desktop ) delete m_desktop;
}

void
MenuItem::setHighlightColor( const QColor& c )
{
	m_hlColor = c;
}

QColor
MenuItem::highlightColor() const
{
	return ( m_hlColor.isValid() ? m_hlColor : colorGroup().highlight() );
}

void
MenuItem::setPrimaryOffset( int o )
{
	m_offset = o;
}

int
MenuItem::primaryOffset() const
{
	return m_offset;
}

void
MenuItem::setSecondaryOffset( int o )
{
	m_secOffset = o;
}

int
MenuItem::secondaryOffset() const
{
	return m_secOffset;
}

void
MenuItem::setDescFontOffset( int o )
{
	m_descFontOffset = o;
}

int
MenuItem::descFontOffset() const
{
	return m_descFontOffset;
}

void
MenuItem::setDescLines( int l )
{
	m_descLines = l;
}

int
MenuItem::descLines() const
{
	return m_descLines;
}

void
MenuItem::setTitle( const QString& name )
{
	m_title = name;
	repaint();
}

QString
MenuItem::title() const
{
	return m_title;
}

void
MenuItem::setDescription( const QString& desc )
{
	m_desc = desc;
	repaint();
}

QString
MenuItem::description() const
{
	return m_desc;
}

void
MenuItem::setIcon( const QString& n, KIcon::Group g, int s, bool def )
{
	setPixmap( KGlobal::iconLoader()->loadIcon( n, g, s, KIcon::DefaultState, 0, def ) );
}

void
MenuItem::enterEvent( QEvent* e )
{
	m_mouseOver = true;
	QButton::enterEvent( e );
	repaint();
	
	QTimer::singleShot( 200, this, SLOT( showMenu() ) );
}

void
MenuItem::leaveEvent( QEvent* e )
{
	m_mouseOver = false;
	QButton::leaveEvent( e );
	repaint();
	
	if( m_sub )
		QTimer::singleShot( 400, this, SLOT( hideMenu() ) );
}

void
MenuItem::mouseReleaseEvent( QMouseEvent* e )
{
	// If use clicked on the xk-menu and released outside ignore that
	if( !m_mouseOver ) return;	

	// If this item has a sub menu, don't do anything on clicks
	if( m_sub )
	{
		QButton::mouseReleaseEvent( e );
		return;
	}

	// Hide xk-menu
	topLevelWidget()->hide();
	
	// If this is a real item created from .desktop execute it
	if( m_desktop )
	{
		KApplication::startServiceByDesktopPath( m_desktop->fileName() );
		if( m_updateRecent )
		{
    		QString strItem(m_desktop->fileName());

    		// don't add an item from root kmenu level
    		if (!strItem.contains('/'))
    		{
	        	return;
	    	}

	    	// add it into recent apps list
	    	RecentlyLaunchedApps::the().appLaunched(strItem);
	    	RecentlyLaunchedApps::the().save();
	    	RecentlyLaunchedApps::the().m_bNeedToUpdate = true;
    	}
	}
	
	// Pass the event back to QButton
	QButton::mouseReleaseEvent( e );
}

void
MenuItem::showMenu()
{
	PopupManager::hide();
	if( !m_sub ) return;
	if( !m_mouseOver ) return;
	// Ensure the popup will in the screen
	int screenW = QApplication::desktop()->width();
	int screenH = QApplication::desktop()->height();
	int x = mapToGlobal( QPoint( 0, 0 ) ).x();
	int y = mapToGlobal( QPoint( 0, 0 ) ).y();
	int endX = x + m_sub->frameGeometry().width();
	int endY = y + m_sub->frameGeometry().height();
	int tmpX = screenW - endX;
	int tmpY = screenH - endY;
	if( tmpX < 0 ) x += tmpX;
	if( tmpY < 0 ) y += tmpY;
	PopupManager::show( m_sub, x + frameGeometry().width(), y );
	emit menuPopped();
}

void
MenuItem::hideMenu()
{
	PopupManager::hide( this );
}

void
MenuItem::hideInactiveMenu()
{
}

bool
MenuItem::eventFilter( QObject* o, QEvent* e )
{
	if( o == m_sub )
	{
		if( e->type() == QEvent::Enter )
		{
			m_subActive = true;
			// User is interacting with the popup, so we should ignore hide attempts.
			PopupManager::active();
		}
		else if( e->type() == QEvent::Leave )
		{
			m_subActive = false;
			// User left the popup menu, so we can issue any hide attempts.
			PopupManager::deactive();
		}
	}
	return false;
}

QSize
MenuItem::minimumSizeHint() const
{
	// Make the cell at least as high the pixmap or two lines of text one 
	// is being the smaller description + the 2 pixel offsets at top and bottom
	int pixmapHeight = pixmap()->height() + 2 * m_secOffset;

	// title itself
	int textHeight = QApplication::fontMetrics().height();

	// prepare description font
	QFont f = QApplication::font();
	f.setPointSize( f.pointSize() - m_descFontOffset ); // maybe this can be handled better ?
	textHeight += QFontMetrics( f ).height() * m_descLines;
	// Now use whichever is bigger, because we want it to fit always
	int height = QMAX( pixmapHeight, textHeight );
	// Add offsets
	height += 2 * m_offset;

	kdDebug() << k_funcinfo << "FIXME: really calculate min width" << endl;
	return QSize( 150, height );
}

void
MenuItem::drawButton( QPainter* p )
{
	QPen origPen = p->pen();
	p->setPen( Qt::NoPen );
	RasterOp origRasterOp = p->rasterOp();
// 	p->setRasterOp( OrROP );
	if( isDown() && m_mouseOver )
	{
 		p->fillRect( m_offset,
 					 m_offset,
					 geometry().width() - 2 * m_offset,
					 geometry().height() - 2 * m_offset,
					 QBrush( highlightColor().light() ) );
	}
	else if( m_mouseOver )
	{
		// if mouse is over the button, paint the highlight area with highlight color
 		p->fillRect( m_offset,
 					 m_offset,
					 geometry().width() - 2 * m_offset,
					 geometry().height() - 2 * m_offset,
					 QBrush( highlightColor() ) );
	}

	// Check if there's a sub menu, if so draw an arrow-like thing
	if( m_sub )
	{
		QPixmap arrow = KGlobal::iconLoader()->loadIcon( m_arrowIcon, KIcon::Toolbar );
		p->drawPixmap( geometry().width() - arrow.width() - m_offset - m_secOffset,
						( geometry().height() - arrow.height() ) / 2,
						arrow );
	}
	// Restore the settings
	p->setPen( origPen );
	p->setRasterOp( origRasterOp );
	// Draw the pixmap AND the labels
	drawLabel( p );
}

void
MenuItem::drawLabel( QPainter* p )
{
	RasterOp origRasterOp = p->rasterOp();
	if( m_mouseOver )
	{
// 		p->setRasterOp( OrROP );
	}
	// Prepare the title and desc
	
	// This is the available width that we can print text. This is the place just next to the pixmap
	uint availableWidth = geometry().width() - ( 2 * m_offset ) - pixmap()->width() - ( 4 * m_secOffset );
	
	// If there's a sub menu we'll draw an arrow in this button, so texts area gets smaller
	if( m_sub )
		availableWidth -= KGlobal::iconLoader()->loadIcon( m_arrowIcon, KIcon::Toolbar ).width() - m_secOffset;
	
	// Titles will be printed in one line definetely, so squeze it to fit
	QString s_title = KStringHandler::rPixelSqueeze( title(), p->fontMetrics(), availableWidth );

	// Draw the icon
	p->drawPixmap( m_offset + m_secOffset,
				   m_offset + m_secOffset,
				   *pixmap() );

	if( !description().isNull() )
	{
		// Write the description with smaller font
		QFont smallerFont = p->font();
	
		// Make the font smaller by m_descFontOffset points
		smallerFont.setPointSize( smallerFont.pointSize() - m_descFontOffset );

		////// MOVE LINE SPLICING CODE TO ABOVE
		// Let's see if we can use more than one line, because descriptions
		// are more likely to be longer
		
		// Active area height = total widget height - 2 * primary offset
		int activeAreaHeight = geometry().height() - 2 * m_offset;
		// Available desc height = Active area height - title height
		int availableDescHeight = activeAreaHeight - p->fontMetrics().height();
		// One desc line height
		int descLineHeight = QFontMetrics( smallerFont ).height();
		// Let's see how many desc lines are available
		int lineCount =  availableDescHeight / descLineHeight;

		// Prepare each line of text
		QString desc = description().stripWhiteSpace();
		QString line = desc;
		QStringList lines;

		if( lineCount > 1 )
		{
			for( int j = 0; j < lineCount; j++ )
			{
				uint size = QFontMetrics( smallerFont ).width( desc );
	
				if( ( j + 1 ) != lineCount )
				{
					while( size > availableWidth )
					{
							// Remove the last word untill it fits in one line
						line = line.section( " ", 0, -2 );
						size = QFontMetrics( smallerFont ).width( line );
					}
				}
				else
				{
					// This is the last available line, so squeze the rest
					line = KStringHandler::rPixelSqueeze( desc,
														  p->fontMetrics(),
														  availableWidth
														);
				}
				lines.push_back( line );
				desc = desc.mid( line.length() ).stripWhiteSpace();
				line = desc;
				if( line.isEmpty() ) break;
			}
		}
		else
		{
			lines.push_back( KStringHandler::rPixelSqueeze( desc,
															p->fontMetrics(),
															availableWidth ) );
		}
	
		uint totalTextHeight = p->fontMetrics().height() + 
							   lines.count() * descLineHeight;
		int offset = ( geometry().height() - totalTextHeight ) / 2;
	
		// Write the title of the cell 
		p->drawText( QRect( m_offset + pixmap()->width() + 2 * m_secOffset,
							offset,
							availableWidth,
							p->fontMetrics().height()
					  	),
					 		Qt::AlignLeft, s_title );
	
		// Print each line of the comment
		QFont origFont = p->font();
		QPen origPen = p->pen();
		p->setFont( smallerFont );
		p->setPen( highlightColor().light( 300 ) );
		int i = 0;
		int titleHeight = QFontMetrics( origFont ).height();
		QStringList::Iterator it;
		for( it = lines.begin(); it != lines.end(); ++it, i++ )
		{
			int lineOffset = i * p->fontMetrics().height();
			p->drawText( m_offset + pixmap()->width() + 2 * m_secOffset,
					 	offset + titleHeight + lineOffset,
					 	availableWidth,
					 	p->fontMetrics().height(),
					 	Qt::AlignLeft,
					 	*it );
		}
		
		// Restore to original font and pen
		p->setFont( origFont );
		p->setPen( origPen );
	}
	else
	{
		int offset = ( geometry().height() - p->fontMetrics().height() ) / 2;

		// Write the title of the cell 
		p->drawText( QRect( m_offset + pixmap()->width() + 2 * m_secOffset,
							offset,
							availableWidth,
							p->fontMetrics().height()
						  ),
				 			Qt::AlignLeft, s_title );
	}

	if( m_mouseOver )
	{
		p->setRasterOp( origRasterOp );
	}
}
