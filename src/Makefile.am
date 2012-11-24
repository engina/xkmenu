INCLUDES= $(all_includes)
METASOURCES = AUTO

lib_LTLIBRARIES = xkmenu_panelapplet.la

xkmenu_panelapplet_la_SOURCES = xkmenu.cpp button.cpp menu.cpp \
	menucomponent.cpp servicemenu.cpp allprogramscomponent.cpp menucolumn.cpp menuitem.cpp \
	genericcomponent.cpp recentapplicationscomponent.cpp recentapps.cpp separatorcomponent.cpp \
	menuextensionscomponent.cpp menuinfo.cpp menutitle.cpp menutoptitle.cpp menubottomtitle.cpp
xkmenu_panelapplet_la_LDFLAGS = -module -avoid-version $(all_libraries)
xkmenu_panelapplet_la_LIBADD = $(LIB_KDEUI) 

xkmenu_DATA = xkmenu.desktop
xkmenudir = $(kde_datadir)/kicker/applets

messages: rc.cpp
	$(EXTRACTRC) `find . -name \*.ui -o -name \*.rc` > rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/xkmenu.pot
noinst_HEADERS = button.h menu.h menucomponent.h servicemenu.h \
			allprogramscomponent.h menucolumn.h menuitem.h genericcomponent.h popupmanager.h \
			recentapplicationscomponent.h recentapps.h separatorcomponent.h menuextensionscomponent.h menuinfo.h \
		menutitle.h menubottomtitle.h menutoptitle.h
SUBDIRS = menus
