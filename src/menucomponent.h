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

#ifndef XK_MENUCOMPONENT_H_
#define XK_MENUCOMPONENT_H_

#include <qwidget.h>

class QVBoxLayout;
class KDesktopFile;
class MenuItem;

class MenuComponent : public QWidget
{
Q_OBJECT
public:
	MenuComponent( const QString& path = QString::null,
				   QWidget* parent = 0,
				   const QColor& bg = QColor(),
				   const QColor& hl = QColor(),
				   const char* name = 0 );
	
	~MenuComponent();

	void
	setBackgroundColor( const QColor& );
	
	QColor
	backgroundColor() const;
	
	void
	setHighlightColor( const QColor& );
	
	QColor
	highlightColor() const;

	virtual void
	reloadInternal(){};
public slots:
	void
	addItem( MenuItem* );
	
	void
	reload();
	
	void
	clear();

protected:
	virtual void
	enterEvent( QEvent* );
	
	virtual void
	leaveEvent( QEvent* );
	
	virtual void
	initLayout();
	
	virtual void
	deleteLayout();
protected:
	KDesktopFile* m_cfg;
	QString m_path;
private:
	QVBoxLayout* m_mainLay;
	QVBoxLayout* m_itemLay;
	QColor m_bgColor;
	QColor m_hlColor;
};

#endif
