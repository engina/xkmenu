/***************************************************************************
 *   Copyright (C) 2005 by Engin AYDOGAN   *
 *   engin@bzzzt.biz   *
 *	 Copyright (c) 1996-2000 the kicker authors. See file AUTHORS.	*
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

#include <kglobal.h>
#include <kiconloader.h>
#include <kapplication.h>
#include <kdebug.h>

#include <qimage.h>
#include <qbitmap.h>

#include "recentapps.h"
#include "servicemenu.h"

ServiceMenu::ServiceMenu( const QString &, const QString & relPath,
						  QWidget* parent, const char*,
						  bool, const QString & )
 : KPopupMenu( parent, relPath.data() ), m_relPath( relPath ), m_iconSize( 20 )
{
	connect( this, SIGNAL( activated( int ) ), SLOT( slotExec( int ) ) );
	initialize();
}

void
ServiceMenu::initialize()
{
	KServiceGroup::Ptr root = KServiceGroup::group( m_relPath );
	if( !root )
	{
		kdWarning() << k_funcinfo << "No such service group [ " << m_relPath << " ]" << endl;
		return;
	}
	KServiceGroup::List list = root->entries(true, true, true, true );
    if (list.isEmpty()) {
        kdWarning() << k_funcinfo << "No items [ " << m_relPath << " ]" << endl;
        return;
    }
    int id = 1983;
    fillMenu( root, list, m_relPath, id );
}

void
ServiceMenu::fillMenu( KServiceGroup::Ptr& root, KServiceGroup::List& list,
							const QString&, int & id )
{
	QStringList suppressGenericNames = root->suppressGenericNames();
	KServiceGroup::List::ConstIterator it = list.begin();

	for (; it != list.end(); ++it)
	{
		KSycocaEntry * e = *it;
		if (e->isType(KST_KServiceGroup))
		{
			KServiceGroup::Ptr g(static_cast<KServiceGroup *>(e));
			QString groupCaption = g->caption();

			KServiceGroup::Ptr subMenuRoot = KServiceGroup::group(g->relPath());

			int nbChildCount = subMenuRoot->childCount();
			if (nbChildCount == 0 && !g->showEmptyMenu())
			{
				continue;
			}

			QString inlineHeaderName = g->showInlineHeader() ? groupCaption : "";
			// Item names may contain ampersands. To avoid them being converted
			// to accelerators, replace them with two ampersands.
			groupCaption.replace("&", "&&");

			if ( nbChildCount == 1 && g->allowInline() && g->inlineAlias())
			{
				KServiceGroup::Ptr element = KServiceGroup::group(g->relPath());
				if ( element )
				{
					//just one element
					KServiceGroup::List listElement = element->entries(true, true, true, true);
					KSycocaEntry * e1 = *( listElement.begin() );
					if ( e1->isType( KST_KService ) )
					{
						KService::Ptr s(static_cast<KService *>(e1));
						insertMenuItem(s, id++, -1, &suppressGenericNames);
						continue;
                    }
                }
            }

			if (g->allowInline() && ((nbChildCount <= g->inlineValue() ) ||   (g->inlineValue() == 0)))
			{
				//inline all entries
				KServiceGroup::Ptr rootElement = KServiceGroup::group(g->relPath());

				if (!rootElement || !rootElement->isValid())
				{
					break;
				}

				KServiceGroup::List listElement = rootElement->entries(true, true, true, true);

				if ( !g->inlineAlias() && !inlineHeaderName.isEmpty() )
				{
					int mid = insertItem( QString( inlineHeaderName ), id + 1, id++);
					setItemEnabled( mid, false );
				}

				fillMenu( rootElement, listElement,  g->relPath(), id );
				continue;
			}

			// Ignore dotfiles.
			if ((g->name().at(0) == '.'))
			{
				continue;
			}

			ServiceMenu* m = newSubMenu(g->name(), g->relPath(), this, 
											  g->name().utf8(), inlineHeaderName);
			m->setCaption(groupCaption);

			QIconSet iconset = getIconSet(g->icon());

            int newId = insertItem(iconset, groupCaption, m, id++);
            m_entryMap.insert(newId, static_cast<KSycocaEntry*>(g));
            // We have to delete the sub menu our selves! (See Qt docs.)
            m_popupList.append(m);
		}
		else if (e->isType(KST_KService))
		{
            KService::Ptr s(static_cast<KService *>(e));
            insertMenuItem(s, id++, -1, &suppressGenericNames);
        }
        else if (e->isType(KST_KServiceSeparator))
        {
                insertSeparator();
        }
	}
}

void
ServiceMenu::insertMenuItem( KService::Ptr & s, int nId, int nIndex,
						 		  const QStringList *suppressGenericNames,
						 		  const QString &aliasname )
{
    QString serviceName = aliasname.isEmpty() ? s->name():aliasname;
    // add comment
    QString comment = s->genericName();
    if (!comment.isEmpty())
    {
            if (!suppressGenericNames ||
                !suppressGenericNames->contains(s->untranslatedGenericName()))
            {
                serviceName = QString("%1 (%2)").arg(serviceName).arg(comment);
            }
    }

    // restrict menu entries to a sane length
    if ( serviceName.length() > 60 ) {
      serviceName.truncate( 57 );
      serviceName += "...";
    }

    // check for NoDisplay
    if (s->noDisplay())
        return;

    // ignore dotfiles.
    if ((serviceName.at(0) == '.'))
        return;

    // item names may contain ampersands. To avoid them being converted
    // to accelerators, replace them with two ampersands.
    serviceName.replace("&", "&&");

    int newId = insertItem(getIconSet(s->icon()), serviceName, nId, nIndex);
    m_entryMap.insert(newId, static_cast<KSycocaEntry*>(s));
}

void
ServiceMenu::setIconSize( int s )
{
	m_iconSize = s;
}

QIconSet
ServiceMenu::getIconSet(const QString& icon)
{
	QIconSet iconset;
	if( icon != "unknown" )
	{
		if( m_iconSize > 0)
		{
			iconset = KGlobal::iconLoader()->loadIconSet(icon,
														 KIcon::NoGroup,
														 m_iconSize, true);
		}
		else if( m_iconSize == 0 )
		{
			QPixmap normal = KGlobal::iconLoader()->loadIcon(icon,
															 KIcon::Small, 0,
															 KIcon::DefaultState, 0,
															 true);

			QPixmap active = KGlobal::iconLoader()->loadIcon(icon,
															 KIcon::Small, 0,
															 KIcon::ActiveState, 0,
															true);

			// make sure they are not larger than 20x20
			if (normal.width() > 20 || normal.height() > 20)
			{
				normal.convertFromImage(normal.convertToImage().smoothScale(20,20));
			}

			if (active.width() > 20 || active.height() > 20)
			{
				active.convertFromImage(active.convertToImage().smoothScale(20,20));
			}

			iconset.setPixmap(normal, QIconSet::Small, QIconSet::Normal);
			iconset.setPixmap(active, QIconSet::Small, QIconSet::Active);
		}
	}

	if( iconset.isNull() )
	{
		QPixmap pix( m_iconSize, m_iconSize );
		QBitmap map( m_iconSize, m_iconSize, true );
		pix.setMask( map );
		iconset = QIconSet( pix, pix );
	}

	return iconset;
}

ServiceMenu*
ServiceMenu::newSubMenu(const QString & label, const QString & relPath,
							QWidget * parent, const char * name, const QString& _inlineHeader)
{
    ServiceMenu* sm = new ServiceMenu(label, relPath, parent, name, false,_inlineHeader);
    // pass the item executed event to the top most parent
    connect( sm, SIGNAL(itemExecuted()), this, SIGNAL(itemExecuted()) );
    return sm;
}

void
ServiceMenu::slotExec(int id)
{
    if (!m_entryMap.contains(id)) return;

    KSycocaEntry * e = m_entryMap[id];

    kapp->propagateSessionManager();

    KService::Ptr service = static_cast<KService *>(e);
    KApplication::startServiceByDesktopPath( service->desktopEntryPath(),
											 QStringList(), 0, 0, 0, "", true );
	kdDebug() << "exec" << endl;
	emit itemExecuted();

    updateRecentlyUsedApps(service);
//    startPos_ = QPoint(-1,-1);
}

void
ServiceMenu::updateRecentlyUsedApps(KService::Ptr &service)
{
    QString strItem(service->desktopEntryPath());

    // don't add an item from root kmenu level
    if (!strItem.contains('/'))
    {
        return;
    }

    // add it into recent apps list
    RecentlyLaunchedApps::the().appLaunched(strItem);
    RecentlyLaunchedApps::the().save();
    RecentlyLaunchedApps::the().m_bNeedToUpdate = true;
}
