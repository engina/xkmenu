/***************************************************************************
 *   Copyright (C) 2005 by Engin AYDOGAN   *
 *   Copyright (c) 1996-2000 the kicker authors. *
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

#include <kdesktopfile.h>
#include <kservice.h>
#include <kdebug.h>

#include "menuitem.h"
#include "recentapps.h"
#include "recentapplicationscomponent.h"

RecentApplicationsComponent::RecentApplicationsComponent( QWidget *p,
								 						  const QColor& bg,
								 						  const QColor& hl )
 : MenuComponent( QString::null, p, bg, hl )
{
	init();
	startTimer( 500 );
}

void
RecentApplicationsComponent::reload()
{
	kdDebug() << k_funcinfo << "####### RELOAD" << endl;
	setUpdatesEnabled( FALSE );
	clear();
	init();
	setUpdatesEnabled( TRUE );
	repaint();
}

void
RecentApplicationsComponent::timerEvent( QTimerEvent* )
{
    if( RecentlyLaunchedApps::the().m_bNeedToUpdate )
    {
		reload();
    	RecentlyLaunchedApps::the().m_bNeedToUpdate = false;
	}
}

void
RecentApplicationsComponent::init()
{
	/* Copied from kicker/ui/k_mnu.cpp */
    RecentlyLaunchedApps::the().init();
    RecentlyLaunchedApps::the().m_nNumMenuItems = 0;

    QStringList RecentApps;
    RecentlyLaunchedApps::the().getRecentApps(RecentApps);

    if (RecentApps.count() > 0)
    {

        for (QValueList<QString>::ConstIterator it =
             RecentApps.begin(); it != RecentApps.end(); ++it)
        {
            KService::Ptr s = KService::serviceByDesktopPath(*it);
            if (!s)
            {
                RecentlyLaunchedApps::the().removeItem(*it);
            }
            else
            {
				addItem( new MenuItem( this, new KDesktopFile(*it ),
				 						 highlightColor(), 0, true ) );
                RecentlyLaunchedApps::the().m_nNumMenuItems++;
            }

        }
    }
}
