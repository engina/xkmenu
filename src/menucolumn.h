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

#ifndef XK_MENUCOLUMN_H_
#define XK_MENUCOLUMN_H_

#include <qframe.h>

class QVBoxLayout;
class MenuComponent;

class MenuColumn : protected QFrame
{
Q_OBJECT
public:
	MenuColumn( QWidget* parent = 0,
				const QString& name = QString::null,
				const QColor& bg = QColor(),
				const QColor& hl = QColor() );
	
	void
	setBackgroundColor( const QColor& );
	
	QColor
	backgroundColor() const;
	
	void
	setHighlightColor( const QColor& );
	
	QColor
	highlightColor() const;

public slots:
	void
	addSpacer();

	void
	addComponent( MenuComponent* );
	
	void
	loadItems();

private:
	QVBoxLayout* m_mainLay;
	QVBoxLayout* m_compLay;
	QColor m_bgColor;
	QColor m_hlColor;
	QString m_name;
};

#endif
