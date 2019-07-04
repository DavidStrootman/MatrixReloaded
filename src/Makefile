#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

RELOADED := ../lib/Reloaded
# source files in this project (main.cpp is automatically assumed)
SOURCES := $(RELOADED)/Reloaded.cpp $(RELOADED)/graphics_drawer.cpp

# header files in this project
HEADERS := $(RELOADED)/Reloaded.h $(RELOADED)/graphics_drawer.h $(RELOADED)/updating_drawable.h

# other places to look for files for this project
SEARCH  :=

# set RELATIVE to the next higher directory
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
