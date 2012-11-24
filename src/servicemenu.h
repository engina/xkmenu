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

#ifndef XK_SERVICEMENU_H_
#define XK_SERVICEMENU_H_

#include <kservicegroup.h>
#include <kpopupmenu.h>

#include <qvaluevector.h>


typedef QMap<int, KSycocaEntry::Ptr> EntryMap;
typedef QValueVector<QPopupMenu*> PopupMenuList;

class ServiceMenu : public KPopupMenu
{
Q_OBJECT
public:
	ServiceMenu( const QString & label = QString::null,
				 const QString & relPath = QString::null,
				 QWidget* parent  = 0, const char* name = 0,
				 bool addmenumode = false,
				 const QString &insertInlineHeader = QString::null );
	void
	setIconSize( int );

	int
	iconSize() const { return m_iconSize; }
protected:
	void
	initialize();
	
	void
	fillMenu( KServiceGroup::Ptr&, KServiceGroup::List&,
			  const QString &_relPath, int & id );
	void
	insertMenuItem( KService::Ptr & s, int nId, int nIndex = -1,
				 	const QStringList *suppressGenericNames=0,
				 	const QString &aliasname = QString::null);
    QIconSet
    getIconSet(const QString& icon);

	virtual ServiceMenu *
	newSubMenu( const QString & label, const QString & relPath,
				QWidget * parent, const char * name,
				const QString & _inlineHeader = QString::null);

protected slots:
	void
	slotExec( int );

	void
	updateRecentlyUsedApps(KService::Ptr &service);
signals:
	void itemExecuted();

private:
	QString m_relPath;
	int m_iconSize;
	EntryMap m_entryMap;
	PopupMenuList m_popupList;
};

#endif
