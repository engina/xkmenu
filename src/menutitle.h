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

#ifndef _XK_MENUTITLE_H_
#define _XK_MENUTITLE_H_

#include <qwidget.h>
#include <qpixmap.h>

class MenuTitle : public QWidget
{
Q_OBJECT
public:
	MenuTitle( QWidget* parent = 0,
			   const char* name = 0 );
	void
	setTiledBackgroundPixmap( const QPixmap& bg );

	QPixmap
	tiledBackgroundPixmap() const;
	
	void
	setBackgroundPixmapWithMask( const QPixmap& bg );
	
	QPixmap
	backgroundPixmapWithMask() const;
protected:
	virtual void
	paintEvent( QPaintEvent* );
private:
	QPixmap m_bg;
	QPixmap m_maskedBg;
};

#endif
