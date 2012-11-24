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
#include <klocale.h>
#include <kconfig.h>
#include <kapplication.h>
#include <kmessagebox.h>
#include <kglobalaccel.h>
#include <kdebug.h>

#include <qlayout.h>

#include "xkmenu.h"
#include "button.h"
#include "menu.h"

xkmenu::xkmenu(const QString& configFile, Type type, int actions, QWidget *parent, const char *name)
    : KPanelApplet(configFile, type, actions, parent, name)
{
kdDebug() << k_funcinfo << "APPLET STARTED" << endl;
    // Get the current application configuration handle
    ksConfig = config();
//     m_mainLay = new QVBoxLayout( this );
	Button* w = new Button( this );
// 	m_mainLay->addWidget( w );
	
	connect( w, SIGNAL( clicked() ), SLOT( buttonClicked() ) );

	/* apparently since win key is just a modifier on most systems this won't work */
	m_gAccel = new KGlobalAccel( this );
	m_gAccel->insert( "Popup", i18n( "Popup XK-Menu" ), 
					  i18n( "Pops up the XK-Menu upon Win key press" ),
					  Qt::Key_Meta, KKey::WIN, this, SLOT( buttonClicked() ) );
    m_button = w;
    m_button->show();

    m_menu = new Menu();
}


xkmenu::~xkmenu()
{
}


void xkmenu::about()
{
    KMessageBox::information(0, i18n("This is an about box"));
}


void xkmenu::help()
{
    KMessageBox::information(0, i18n("This is a help box"));
}


void xkmenu::preferences()
{
    KMessageBox::information(0, i18n("This is a preferences box"));
}

int xkmenu::widthForHeight(int) const
{
    return m_button->width();
}

int xkmenu::heightForWidth(int) const
{
    return m_button->height();
}

void xkmenu::resizeEvent(QResizeEvent *)
{
}

void xkmenu::positionChange( Position )
{
}

void xkmenu::buttonClicked()
{
	int x = mapToGlobal(QPoint(0,0)).x();
	int y = mapToGlobal(QPoint(0,0)).y();

	kdDebug() << k_funcinfo << "applet pos: " << mapToGlobal( QPoint() ) << endl;
	switch( popupDirection() )
	{
	case Up:
		y -= m_menu->frameGeometry().height();
	break;
	case Down:
		y += height();
	break;
	case Left:
		x -= m_menu->frameGeometry().width();
	break;
	case Right:
		x += width();
	}
	kdDebug() << k_funcinfo << "menu geo: " << m_menu->frameGeometry() << endl;
	kdDebug() << k_funcinfo << "dst point: " << QPoint( x, y ) << endl;
	
	// Snap to screen edge if we're closer than 20 pixel
	// (applet handlers can cause ugly spaces)
	x = x < 20 ? 0 : x;
	
	// If right edge is out of desktop put the menu back in desktop ?
	if( ( x + m_menu->frameGeometry().width() ) > QApplication::desktop()->width() )
	{
		x = QApplication::desktop()->width() - m_menu->frameGeometry().width();
	}
	m_menu->move( x, y );
	m_menu->show();
}

extern "C"
{
    KPanelApplet* init( QWidget *parent, const QString& configFile)
    {
        KGlobal::locale()->insertCatalogue("xkmenu");
        return new xkmenu(configFile, KPanelApplet::Normal,
                             KPanelApplet::About | KPanelApplet::Help | KPanelApplet::Preferences,
                             parent, "xkmenu");
    }
}
