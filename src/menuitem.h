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

#ifndef XK_MENUITEM_H_
#define XK_MENUITEM_H_

#include <kicontheme.h>

#include <qbutton.h>
#include <qpixmap.h>

class KDesktopFile;
class QFrame;

class MenuItem : public QButton
{
Q_OBJECT
public:
	MenuItem( QWidget* parent,
			  KDesktopFile* desktop,
			  const QColor& hl = QColor(),
			  QFrame* sub = 0,
			  bool updateRecent = false );

	MenuItem( QWidget* parent,
			  const QString& title,
			  const QString& comment = QString::null,
			  const QString& icon = QString::null,
			  const QColor& hl = QColor(),
			  QFrame* sub = 0,
			  bool updateRecent = false );
			  
	~MenuItem();
	
	void
	setHighlightColor( const QColor& );
	
	QColor
	highlightColor() const;

	void
	setPrimaryOffset( int );
	
	int
	primaryOffset() const;
	
	void
	setSecondaryOffset( int );
	
	int
	secondaryOffset() const;

	void
	setTitle( const QString& );
	
	QString
	title() const;
	
	void
	setDescription( const QString& );
	
	QString
	description() const;
	
	void
	setDescFontOffset( int );
	
	int
	descFontOffset() const;
	
	void
	setDescLines( int );
	
	int
	descLines() const;

	QSize
	minimumSizeHint() const;
	
	void
	setIcon( const QString& name,
			 KIcon::Group group = KIcon::Desktop,
			 int size = 0,
			 bool def = false );

public slots:
	void
	showMenu();
	
	void
	hideMenu();

	void
	hideInactiveMenu();

signals:
	void menuPopped();

protected:
	virtual void
	drawButton( QPainter* );
	
	virtual void
	drawLabel( QPainter* );

	virtual void
	enterEvent( QEvent* );
	
	virtual void
	leaveEvent( QEvent* );
	
	virtual void
	mouseReleaseEvent( QMouseEvent* );

	virtual bool
	eventFilter( QObject*, QEvent* );

private:
	KDesktopFile* m_desktop;
	bool m_mouseOver, m_subActive;
	int m_offset, m_secOffset;
	QFrame* m_sub;
	QColor m_bgColor, m_hlColor;
	QString	m_title;
	QString	m_desc;
	bool m_updateRecent;
	QPainter* m_painter;
	int m_descFontOffset;
	int m_descLines;
	QString m_arrowIcon;
};

#endif
