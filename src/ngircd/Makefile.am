#
# ngIRCd -- The Next Generation IRC Daemon
# Copyright (c)2001,2002 by Alexander Barton (alex@barton.de)
#
# Dieses Programm ist freie Software. Sie koennen es unter den Bedingungen
# der GNU General Public License (GPL), wie von der Free Software Foundation
# herausgegeben, weitergeben und/oder modifizieren, entweder unter Version 2
# der Lizenz oder (wenn Sie es wuenschen) jeder spaeteren Version.
# Naehere Informationen entnehmen Sie bitter der Datei COPYING. Eine Liste
# der an ngIRCd beteiligten Autoren finden Sie in der Datei AUTHORS.
#
# $Id: Makefile.am,v 1.19 2002/03/29 22:52:12 alex Exp $
#

AM_CFLAGS = -I$(srcdir)/../portab

LINTARGS = -weak -warnunixlib +unixlib -booltype BOOLEAN

sbin_PROGRAMS = ngircd

ngircd_SOURCES = ngircd.c channel.c client.c conf.c conn.c hash.c irc.c \
	irc-channel.c irc-login.c irc-mode.c irc-oper.c irc-server.c \
	irc-write.c log.c parse.c tool.c

noinst_HEADERS = ngircd.h channel.h client.h conf.h conn.h hash.h irc.h \
	irc-channel.h irc-login.h irc-mode.h irc-oper.h irc-server.h \
	irc-write.h log.h parse.h tool.h \
	messages.h defines.h

clean-local:
	rm -f check-version check-help lint.out

maintainer-clean-local:
	rm -f Makefile Makefile.in

check-version: Makefile
	echo "#!/bin/sh" > check-version
	echo "./ngircd --version | grep version > /dev/null 2>&1" >> check-version
	chmod 755 check-version

check-help: Makefile
	echo "#!/bin/sh" > check-help
	echo "./ngircd --help | grep help > /dev/null 2>&1" >> check-help
	chmod 755 check-help

lint:
	rm -f lint.out
	for f in *.c; do \
	 echo "checking $$f ..."; \
	 splint $$f $(LINTARGS) -I./.. $(AM_CFLAGS) > lint.out 2>&1; \
	 grep "no warnings" lint.out > /dev/null 2>&1; \
	 if [ $$? -ne 0 ]; then \
	  echo; cat lint.out; echo; \
	 fi; \
	done;

TESTS = check-version check-help

# -eof-
