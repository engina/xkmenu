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
#include <kconfig.h>
#include <kpanelmenu.h>
#include <kdebug.h>

#include "menuitem.h"
#include "menuinfo.h"
#include "menuextensionscomponent.h"

MenuExtensionsComponent::MenuExtensionsComponent( QWidget* parent, const QColor& bg, const QColor& hl )
 :  MenuComponent( QString::null, parent, bg, hl, "MenuExtensionsComponent" )
{
	kdDebug() << "MENU EXTENSIONS" << endl;
	KGlobal::config()->setGroup( "menus" );
	QStringList extensions = KGlobal::config()->readListEntry( "Extensions" );

	for( QStringList::Iterator it = extensions.begin(); it != extensions.end(); ++it )
	{
		MenuInfo info( *it );
		if( !info.isValid() ) continue;
		
		KPanelMenu* menu = info.load();
		if( menu )
		{
			kdDebug() << "LOADING EXTENSION: " << info.name() << endl;
			addItem( new MenuItem( this, info.name(), info.comment(), "document", hl, menu ) );
		}
	}
}
