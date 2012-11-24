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

#ifndef _XK_MENUBUTTOMTITLE_H_
#define _XK_MENUBUTTOMTITLE_H_

#include "menutitle.h"

class QHBoxLayout;
class MenuItem;

class MenuBottomTitle : public MenuTitle
{
Q_OBJECT
public:
	MenuBottomTitle( const QPixmap& bg = QPixmap(),
					 QWidget* parent = 0,
					 const char* name = 0 );
protected slots:
	void
	requestShutdown();
	
	void
	requestLock();
protected:
	virtual QSize
	minimumSizeHint() const;
private:
	QHBoxLayout* m_mainLay;
	MenuItem* m_shutDownButton;
	MenuItem* m_lockButton;
};

#endif
