# Makefile for busybox binary in WslInstall repository

DIR = busybox-1.30.1
FILE = busybox-1.30.1.tar.bz2
LINK = https://busybox.net/downloads/$(FILE)

bin:
	wget $(LINK)
	tar -xf $(FILE)
	cp .config $(DIR)
	cd $(DIR); $(MAKE)
