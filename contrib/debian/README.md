
Debian
====================
This directory contains files used to package dngrcoind/dngrcoin-qt
for Debian-based Linux systems. If you compile dngrcoind/dngrcoin-qt yourself, there are some useful files here.

## dngrcoin: URI support ##


dngrcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dngrcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dngrcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/dngrcoin128.png` to `/usr/share/pixmaps`

dngrcoin-qt.protocol (KDE)

