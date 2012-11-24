XKMENU
=========

In my last year in college, I was hired as a freelancer to develop an alternative start menu for KDE 3. It was a laptop manufacturer who wished to offer GNU/Linux notebook (to cut of license fees) to its customers while trying to keep the Windows look and feel.

This code is pushed here for historic and educational reasons.

![screenshot](http://ea.tl/images/xkmenu.png "Screenshot")

Here's a text I wrote about this package back then:

> I'm proud of being the father of the xk-menu -- an alternative to k-menu, obviously. I was asked to mimic winxp's menu, and that was exactly what I've did.

> Well, technically, it's a kicker applet. It's component based. It reads .desktop files from $KDEDIR/share/xkmenu/ and generates the menu items. It reads KDE's own panel configuration, such as maximum number of recent menu entries, or the recent menu entries themselves, which means it blends into KDE quite well. It even honors your option on whether it should display recently used items or frequently used items! wow!