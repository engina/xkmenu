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

#include <kapplication.h>
#include <kdebug.h>

#include <qlayout.h>
#include <qbitmap.h>
#include <qpainter.h>
#include <kglobal.h>
#include <kstandarddirs.h>
#include <kconfig.h>

#include "menutoptitle.h"
#include "menubottomtitle.h"
#include "menucolumn.h"

#include "menu.h"

Menu::Menu()
 : QFrame( 0, "xkmenu", WType_Popup  | WNoAutoErase )
{
	kdDebug() << k_funcinfo << endl;
	setFrameStyle( QFrame::ToolBarPanel | QFrame::Plain );
	setLineWidth( 2 );
	
	m_layout = new QVBoxLayout( this);
	
	QVBoxLayout* menu = new QVBoxLayout();

	// Top of the menu ** fix this crap
	KConfig cfg( "xkmenu" );
	cfg.setGroup( "General" );
	QString t_topPixmap = cfg.readPathEntry( "TopPixmap", "top.png" );
	QString t_bottomPixmap = cfg.readPathEntry( "BottomPixmap", "bottom.png" );
	
	
	QString t_topPixmapFile = KGlobal::dirs()->findResource( "data", "xkmenu/" + t_topPixmap );
	QString t_bottomPixmapFile = KGlobal::dirs()->findResource( "data", "xkmenu/" + t_bottomPixmap );

	if( t_topPixmapFile.isNull() )
	{
		kdDebug() << "Couldn't find: " << t_topPixmap << endl;
		// fall back to safe defaults
		t_topPixmapFile = KGlobal::dirs()->findResource( "data", "xkmenu/top.png");
	}
	if( t_bottomPixmapFile.isNull() )
	{
		kdDebug() << "Couldn't find: " << t_bottomPixmap << endl;
		// fall back to safe defaults
		t_bottomPixmapFile = KGlobal::dirs()->findResource( "data", "xkmenu/bottom.png" );
	}

	m_topPixmap = QPixmap( t_topPixmapFile );
	menu->addWidget( new MenuTopTitle( m_topPixmap, this ) ); 
	setAutoMask( true );
	// Middle
	QBoxLayout* t = new QHBoxLayout();

 	m_left = new MenuColumn( this, "left" );
 	m_right = new MenuColumn( this, "right" );
	t->addWidget( m_left, 50 );
	t->addWidget( m_right, 50 );
	
	menu->addLayout( t );

	// Bottom of the menu
	menu->addWidget( new MenuBottomTitle( QPixmap( t_bottomPixmapFile ), this ) );

	m_layout->addLayout( menu );
	
    resize( QSize(1, 1).expandedTo( minimumSizeHint() ) );
	clearWState( WState_Polished );
	move( KApplication::desktop()->width(), KApplication::desktop()->height() );
}

void
Menu::updateMask()
{	QBitmap topMask = *m_topPixmap.mask();
	QBitmap mask(geometry().width(), geometry().height(), true );
	QPainter maskPainter( &mask );
	maskPainter.drawPixmap( 0, 0, topMask );
	maskPainter.fillRect( 0, topMask.height(),
						  geometry().width(),
						  geometry().height() - topMask.height(),
						  Qt::color1 );
	setMask( mask );
}
