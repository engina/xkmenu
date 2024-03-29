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

#include "separatorcomponent.h"

SeparatorComponent::SeparatorComponent( QWidget* p,
										const QColor& bg,
										const QColor& hl )
 : MenuComponent( QString::null, p, bg, hl )
{
	kdDebug() << "SEPERATOR" << endl;
	setMinimumHeight( 3 );
}

void
SeparatorComponent::paintEvent( QPaintEvent* )
{
	kdDebug() << "PAINT EVENT" << endl;
	QPainter p;
	p.begin( this );
	p.setPen( Qt::NoPen );
	p.setBrush( backgroundColor() );
	p.drawRect( rect() );
	p.setBrush( highlightColor() );
	p.drawRect( 10, 1, width()-20, 1 );
	p.end();
}
