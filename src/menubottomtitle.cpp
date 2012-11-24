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

#include <kglobal.h>
#include <kiconloader.h>
#include <klocale.h>
#include <kapplication.h>
#include <dcopclient.h>
#include <kdebug.h>

#include <qlayout.h>

#include "menuitem.h"
#include "menubottomtitle.h"

MenuBottomTitle::MenuBottomTitle( const QPixmap& bg, QWidget* p, const char* n )
 : MenuTitle( p, (n?n:"MenuBottomTitle") )
{
	setTiledBackgroundPixmap( bg );
	m_mainLay = new QHBoxLayout( this );
	m_mainLay->addStretch( 100 );
	
	m_shutDownButton = new MenuItem( this, i18n( "Logout" ) );
	m_shutDownButton->setPixmap( KGlobal::iconLoader()->loadIcon( "exit", KIcon::Toolbar ) );
	m_shutDownButton->setBackgroundOrigin( AncestorOrigin );
	m_shutDownButton->setPaletteBackgroundPixmap(  bg );
	m_shutDownButton->setHighlightColor( Qt::gray );
	
	m_shutDownButton->setMinimumWidth( 100 );
	m_lockButton = new MenuItem( this, i18n( "Lock" ) );
	m_lockButton->setBackgroundOrigin( AncestorOrigin );
	m_lockButton->setPaletteBackgroundPixmap(  bg );
	m_lockButton->setPixmap( KGlobal::iconLoader()->loadIcon( "lock", KIcon::Toolbar ) );
	m_lockButton->setMinimumWidth( 100 );
	m_lockButton->setHighlightColor( Qt::gray );
	connect( m_shutDownButton, SIGNAL( clicked() ), this, SLOT( requestShutdown() ) );
	connect( m_lockButton, SIGNAL( clicked() ), this, SLOT( requestLock() ) );
	
	m_mainLay->addWidget( m_lockButton );
	m_mainLay->addStretch( 10 );
	m_mainLay->addWidget( m_shutDownButton );
	m_mainLay->addStretch( 10 );
}

QSize
MenuBottomTitle::minimumSizeHint() const
{
	kdDebug() << "BUTTOM TITLE SIZEHINT: " << m_mainLay->sizeHint() << endl;
	return m_mainLay->sizeHint();
}

void
MenuBottomTitle::requestShutdown()
{
	kapp->requestShutDown();
}

extern int kicker_screen_number;

void
MenuBottomTitle::requestLock()
{
    QCString appname( "kdesktop" );
    if ( kicker_screen_number )
        appname.sprintf("kdesktop-screen-%d", kicker_screen_number);
    kapp->dcopClient()->send(appname, "KScreensaverIface", "lock()", "");
    topLevelWidget()->hide();
}
