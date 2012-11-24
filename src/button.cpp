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

#include <kstandarddirs.h>
#include <klocale.h>
#include <kdebug.h>

#include <qimage.h>
#include <qpainter.h>

#include "button.h"

Button::Button( QWidget* parent, const QString& pixmap )
 : KPushButton( parent, "xkbutton" )
{
	changePixmap( pixmap == QString::null ? "default.png" : pixmap );
}

void
Button::changePixmap( const QString& name )
{
	QString path = locate( "data", "xkmenu/" + name );
	if( path.isNull() )
	{
		kdWarning() << k_funcinfo << "Pixmap could not be found [ "
				  << name << " ]" << endl;
		return;
	}
	loadPixmap( path  );
}

void
Button::loadPixmap( const QString& path )
{
	m_pixmapPath = path;

	QPixmap m_pixmap;
	
	if( !m_pixmap.load( path ) )
	{
		kdWarning() << k_funcinfo << "Could not convert image to pixmap" << endl;
		return;
	}
	
	setMinimumSize( m_pixmap.size() );
	
	// Paint the text on the button

	kdDebug() << "Pixmap : " << m_pixmap.size() << endl;
	QPainter p( &m_pixmap );
	// First make the pen white and thick
	QPen pen = p.pen();
	kdDebug() << "Painter's pen width: " << p.pen().width() << endl;
	kdDebug() << "New width: " << pen.width() << endl;
	p.setPen( QPen( white, 4 ) );
	kdDebug() << "Painter's pen width: " << p.pen().width() << endl;
	// Then make the font bold and italic
	QFont f = p.font();
	kdDebug() << "Default weight: " << p.font().weight() << endl;
	f.setWeight( 99 );
	kdDebug() << "New weight: " << f.weight() << endl;
	f.setBold( true );
	f.setItalic( true );
	p.setFont( f );
	kdDebug() << "Default weight: " << p.font().weight() << endl;
	// Finally draw the text
	int offset = (geometry().height() - p.fontMetrics().height()) / 2 + p.fontMetrics().height() - 2;
	p.drawText( 30, offset, i18n( "XK-Menu" ) );
	kdDebug() << "ABOUT TO setPixmap" << endl;

	setPixmap( m_pixmap );
	kdDebug() << "ABOUT TO setMask" << endl;
	setMask( *m_pixmap.mask() );
}

