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

#include <kdesktopfile.h>
#include <kdebug.h>

#include <qlayout.h>
#include <qobjectlist.h>
#include <qdir.h>

#include "menuitem.h"
#include "menucomponent.h"

MenuComponent::MenuComponent( const QString& path,
							  QWidget* p,
							  const QColor& bg,
							  const QColor& hl,
							  const char* name )
 : QWidget( p, name ? name : "MenuComponentBase" ), m_path( path )
{
	// Read components config file
	m_cfg = new KDesktopFile( m_path + "/spec.desktop", true, "data" );

	// Set colors
	setBackgroundColor( m_cfg->readColorEntry( "BackgroundColor" ) );
	setHighlightColor( m_cfg->readColorEntry( "HighlightColor" ) );

	// Create basic layout
	initLayout();
	
	// override background and highlight colors if provided
	if( bg.isValid() )
		setBackgroundColor( bg );
	if( hl.isValid() )
		setHighlightColor( hl );
}

MenuComponent::~MenuComponent()
{
	delete m_cfg;
}

void
MenuComponent::initLayout()
{
	m_mainLay = new QVBoxLayout( this );
}

void
MenuComponent::deleteLayout()
{
	kdDebug() << k_funcinfo << "FIXME" << endl;
}

void
MenuComponent::reload()
{
	reloadInternal();
}

void
MenuComponent::clear()
{
	QObjectList* c = (QObjectList*)children();
	if( c )
	{
		QObject* obj = c->first();
		int count = c->count();
		for( int i = 0; i < count; i++ )
		{
			QObject* tmp = obj;
			obj = c->next();
			if( tmp )
			{
				if( tmp->isA( "MenuItem" ) )
				{
					delete tmp;
				}
			}
		}
	}
}

void
MenuComponent::setBackgroundColor( const QColor& c )
{
	kdDebug() << k_funcinfo << c << endl;
	m_bgColor = c;
}

QColor
MenuComponent::backgroundColor() const
{
	return m_bgColor;
}
	
void
MenuComponent::setHighlightColor( const QColor& c )
{
	kdDebug() << k_funcinfo << c << endl;
	m_hlColor = c;
}
	
QColor
MenuComponent::highlightColor() const
{
	return m_hlColor;
}

void
MenuComponent::enterEvent( QEvent* e )
{
	QWidget::enterEvent( e );
}

void
MenuComponent::leaveEvent( QEvent* e )
{
	QWidget::leaveEvent( e );
}

void
MenuComponent::addItem( MenuItem* i )
{
	kdDebug() << "Adding MenuItem " << (i->name()?i->name():"") << endl;
	m_mainLay->addWidget( i );
}
