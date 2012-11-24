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

#ifndef XK_POPUPMANAGER_H_
#define XK_POPUPMANAGER_H_

#include <kdebug.h>

#include <qwidget.h>
#include <qvaluelist.h>

static QValueList< QWidget* > m_list;
static bool m_active;

class PopupManager
{
public:
	static void add( QWidget* w )
	{
		m_list.push_back( w );
	}
	
	static void show( QWidget* w, int x, int y )
	{
		hide();
		w->move( x, y );
		w->show();
	}

	static void hide( QWidget* w = 0 )
	{
		// if user is interacting with the shown popup, abort
		if( m_active ) return;
		QValueListIterator<QWidget*> it;
		for( it = m_list.begin(); it != m_list.end(); ++it )
		{
			if( dynamic_cast<QWidget*>(*it) ) // just precaution
			{
				if( w )
				{
					if( (*it) == w )
					{
						(*it)->hide();
						break;
					}
				}
				else
				{
					(*it)->hide();
				}
			}
			else
			{
				kdWarning() << k_funcinfo << "Dead popup reference." << endl;
			}
		}
	}
	
	// user is interacting the with the current shown popup
	static void active()
	{
		m_active = true;
	}
	
	// user is not interacting with any popups
	static void deactive()
	{
		m_active = false;
	}
};

#endif
