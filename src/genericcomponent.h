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

#ifndef XK_GENERICOMPONENT_H_
#define XK_GENERICOMPONENT_H_

#include "menucomponent.h"

class GenericComponent : public MenuComponent
{
Q_OBJECT
public:
	GenericComponent( const QString& path = QString::null,
					  QWidget* parent = 0,
					  const QColor& bg = QColor(),
					  const QColor& hl = QColor(),
					  const char* name = 0 )
		: MenuComponent( path, parent, bg, hl, name ){init();}
	void init();
	void reloadInternal();
};

#endif
