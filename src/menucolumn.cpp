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

#include <qlabel.h> // remove later8
#include <qlayout.h>
#include <qdir.h>

#include <kglobal.h>
#include <kstandarddirs.h>
#include <kdesktopfile.h>
#include <kdebug.h>

#include "genericcomponent.h"
#include "separatorcomponent.h"
#include "allprogramscomponent.h"
#include "recentapplicationscomponent.h"
#include "menuextensionscomponent.h"
#include "menucolumn.h"

MenuColumn::MenuColumn( QWidget* parent,
						const QString& name,
						const QColor& bg,
						const QColor& hl )
 : QFrame( parent, name ? name : "GenericMenuColumn" ), m_name( name )
{
	setFrameStyle( QFrame::Plain | QFrame::MenuBarPanel );
	m_mainLay = new QVBoxLayout( this );
	m_compLay = new QVBoxLayout();
	m_mainLay->addLayout( m_compLay );
	
	if( !m_name.isNull() )
		loadItems();

	// override color
	if( bg.isValid() )
		setBackgroundColor( bg );
	if( hl.isValid() )
		setHighlightColor( hl );


	setPaletteBackgroundColor( backgroundColor() );
}

void
MenuColumn::loadItems()
{
	// Open column's config file
	KDesktopFile cfg( "xkmenu/" + m_name + "/spec.desktop", true ,"data" );
	
	// Set column specific colors if defined in the file
	setBackgroundColor( cfg.readColorEntry( "BackgroundColor" ) );
	setHighlightColor( cfg.readColorEntry( "HighlightColor" ) );

	// Read directories in the column directory. These are components.
	QStringList compDirs = KGlobal::dirs()->findDirs( "data", "xkmenu/" + m_name  );
	QStringList::ConstIterator it;
	for( it = compDirs.begin(); it != compDirs.end(); ++it )
	{
		QDir d( *it );
		QStringList comps = d.entryList( "*", QDir::Dirs);
		// Now iterate through components
		for( QStringList::ConstIterator comp = comps.begin(); comp != comps.end(); ++comp )
		{
			if( *comp == "." || *comp == ".." ) continue;
			
			// Read components config file.
			KDesktopFile compCfg( *it + "/" + *comp + "/spec.desktop" );
			QString type = compCfg.readType();
			
			if( type.lower() == "static" )
			{
				addComponent( new GenericComponent( *it + "/" + *comp,
												 this,
												 backgroundColor(),
												 highlightColor()  )
							);
			}
			else if( type.lower() == "built-in" || type.lower() == "builtin" )
			{
				QString factory = compCfg.readEntry( "Factory" );
				if( factory.lower() == "all programs" )
				{
					addComponent( new AllProgramsComponent( this, backgroundColor(), highlightColor() ) );
				}
				else if( factory.lower() == "recent programs" )
				{
					addComponent( new RecentApplicationsComponent( this, backgroundColor(), highlightColor() ) );
				}
				else if( factory.lower() == "menu extensions" )
				{
					addComponent( new MenuExtensionsComponent( this, backgroundColor(), highlightColor() ) );
				}
				else if( factory.lower() == "separator" )
				{
					//! FIXME: make separator read it's own config file
					addComponent( new SeparatorComponent( this, backgroundColor(),
															compCfg.readColorEntry( "HighlightColor" ) ) );
				}
			}
			else if( type.lower() == "plugin" || type.lower() == "plug-in" )
			{
				//! TODO: implement dynamic loading... later
			}
		}
		addSpacer();
	}
}

void
MenuColumn::setBackgroundColor( const QColor& c )
{
	kdDebug() << k_funcinfo << c << endl;
	m_bgColor = c;
}

QColor
MenuColumn::backgroundColor() const
{
	return m_bgColor;
}
	
void
MenuColumn::setHighlightColor( const QColor& c )
{
	kdDebug() << k_funcinfo << c << endl;
	m_hlColor = c;
}

QColor
MenuColumn::highlightColor() const
{
	return m_hlColor;
}

void
MenuColumn::addComponent( MenuComponent* c )
{
	m_compLay->addWidget( c );
}

void
MenuColumn::addSpacer()
{
	m_compLay->addStretch();
}
