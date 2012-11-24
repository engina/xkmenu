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

#include <kdebug.h>

#include <qpainter.h>

#include "menutitle.h"

MenuTitle::MenuTitle( QWidget* p, const char* n )
 : QWidget( p, n )
{
}

void
MenuTitle::setTiledBackgroundPixmap( const QPixmap& bg )
{
	m_bg = bg;
	setMinimumHeight( m_bg.height() );
}

QPixmap
MenuTitle::tiledBackgroundPixmap() const
{
	return m_bg;
}

void
MenuTitle::setBackgroundPixmapWithMask( const QPixmap& bg )
{
	m_maskedBg = bg;
	setMinimumSize( m_maskedBg.size() );
	setMask( *m_maskedBg.mask() );
}

QPixmap
MenuTitle::backgroundPixmapWithMask() const
{
	return m_maskedBg;
}

void
MenuTitle::paintEvent( QPaintEvent* e )
{
	QPainter p( this );
	if( !m_bg.isNull() )
	{
		p.drawTiledPixmap( 0, 0, geometry().width(), geometry().width(), m_bg );
	}
	if( !m_maskedBg.isNull() )
	{
		p.drawPixmap( 0, 0, m_maskedBg );
	}
	QWidget::paintEvent( e );
}
