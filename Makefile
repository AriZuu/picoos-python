#
# Copyright (c) 2015, Ari Suutari <ari@stonepile.fi>.
# All rights reserved. 
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote
#     products derived from this software without specific prior written
#     permission. 
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
# INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.

#
# This is a little bit complicated, as both MicroPython and Pico]OS have
# their own Makefile framework, which conflict at least on "BUILD"
# Makefile variable usage. Work around it by executing the 
# build in separate steps which use only one framework at time.
#

#
# Step 1 of MicroPython build:  Figure out settings for other build steps and
#                               execute them in sub-make.
#
RELROOT = ../picoos/

PORT ?= unix
CPU ?= 32
BUILD = DEBUG

#
# Export parameters needed at Makefile.pos
#
POS_PORT=$(PORT)
POS_CPU=$(CPU)
POS_CORTEX=$(CORTEX)
POS_BUILD=$(BUILD)
POS_RELROOT=$(RELROOT)

export POS_PORT POS_CPU POS_CORTEX POS_BUILD POS_RELROOT

include $(RELROOT)make/common.mak

ifeq '$(strip $(DIR_OUTPUT))' ''
DIR_OUTPUT = $(CURRENTDIR)/bin
endif

MP_BUILD= $(DIR_OUTPUT)/$(PORT)-$(MODEEXT)/mp
INC =  -I.
INC += -I../micropython
INC += -I$(MP_BUILD)
CFLAGS += $(INC)
CFLAGS += -std=gnu99 -Wno-cast-align

ifeq ($(BUILD), 'RELEASE')
CFLAGS += -DNDEBUG
endif

all:
	$(MAKE) -f Makefile.mp "BUILD=$(MP_BUILD)" all V=$(V) CC=$(CC) "CFLAGS=$(CFLAGS)"
	$(MAKE) -f Makefile.pos 

clean:
	$(MAKE) -f Makefile.mp "BUILD=$(MP_BUILD)" clean
	$(MAKE) -f Makefile.pos clean
