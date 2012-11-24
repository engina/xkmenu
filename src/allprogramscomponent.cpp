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
#include <klocale.h>

#include "menuitem.h"
#include "servicemenu.h"
#include "allprogramscomponent.h"

AllProgramsComponent::AllProgramsComponent( QWidget* p,
								 			const QColor& bg,
								 			const QColor& hl )
 : MenuComponent( QString::null, p, bg, hl )
{
	ServiceMenu* sm = new ServiceMenu();
	sm->setPaletteBackgroundColor( bg );
	sm->setBackgroundMode( Qt::PaletteBackground );
	connect( sm, SIGNAL( itemExecuted() ), this, SLOT( hideTopWidget() ) );
	MenuItem* item = new MenuItem( this,
						   i18n( "All Programs" ),
						   i18n( "Full list of registered programs" ),
						   QString::null,
						   highlightColor(),
						   sm );
	// disable icon
	item->setPixmap( QPixmap() );
	addItem( item );
}

void
AllProgramsComponent::hideTopWidget()
{
	kdDebug() << "activated" << endl;
	topLevelWidget()->hide();
}

void
AllProgramsComponent::paintEvent( QPaintEvent* e )
{
	kdDebug() << "ALL PAINT EVENT" << endl;
	MenuComponent::paintEvent( e );	
}
