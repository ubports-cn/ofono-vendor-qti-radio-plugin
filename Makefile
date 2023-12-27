# -*- Mode: makefile-gmake -*-

.PHONY: clean all debug release

#
# Required packages
#
# ofono.pc adds -export-symbols-regex linker option which doesn't  work
# on all platforms.
#

LDPKGS = libofonobinderpluginext libgbinder-radio libgbinder libglibutil gobject-2.0 glib-2.0
PKGS = ofono $(LDPKGS)

#
# Default target
#

all: debug release

#
# Library name
#

NAME = vendorqtiradioplugin
LIB_NAME = $(NAME)
LIB_SONAME = $(LIB_NAME).so
LIB = $(LIB_SONAME)
STATIC_LIB = $(NAME).a

#
# Sources
#

SRC = \
  sample_ext.c \
  sample_ims.c \
  vendor_qti_plugin.c \
  sample_slot.c

#
# Directories
#

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
DEBUG_BUILD_DIR = $(BUILD_DIR)/debug
RELEASE_BUILD_DIR = $(BUILD_DIR)/release

#
# Tools and flags
#

CC = $(CROSS_COMPILE)gcc
LD = $(CC)
WARNINGS = -Wall
INCLUDES = -I$(INCLUDE_DIR)
BASE_FLAGS = -fPIC -fvisibility=hidden
FULL_CFLAGS = $(BASE_FLAGS) $(CFLAGS) $(DEFINES) $(WARNINGS) $(INCLUDES) \
  -MMD -MP $(shell pkg-config --cflags $(PKGS))
FULL_LDFLAGS = $(BASE_FLAGS) $(LDFLAGS) -shared \
  $(shell pkg-config --libs $(LDPKGS))
DEBUG_FLAGS = -g
RELEASE_FLAGS =

KEEP_SYMBOLS ?= 0
ifneq ($(KEEP_SYMBOLS),0)
RELEASE_FLAGS += -g
endif

DEBUG_LDFLAGS = $(FULL_LDFLAGS) $(DEBUG_FLAGS)
RELEASE_LDFLAGS = $(FULL_LDFLAGS) $(RELEASE_FLAGS)
DEBUG_CFLAGS = $(FULL_CFLAGS) $(DEBUG_FLAGS) -DDEBUG
RELEASE_CFLAGS = $(FULL_CFLAGS) $(RELEASE_FLAGS) -O2

#
# Files
#

DEBUG_OBJS = $(SRC:%.c=$(DEBUG_BUILD_DIR)/%.o)
RELEASE_OBJS = $(SRC:%.c=$(RELEASE_BUILD_DIR)/%.o)

DEBUG_SO = $(DEBUG_BUILD_DIR)/$(LIB)
RELEASE_SO = $(RELEASE_BUILD_DIR)/$(LIB)

#
# Dependencies
#

DEPS = $(DEBUG_OBJS:%.o=%.d) $(RELEASE_OBJS:%.o=%.d)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

$(DEBUG_OBJS) $(DEBUG_SO): | $(DEBUG_BUILD_DIR)
$(RELEASE_OBJS) $(RELEASE_SO): | $(RELEASE_BUILD_DIR)

#
# Rules
#

debug: $(DEBUG_SO)

release: $(RELEASE_SO)

clean:
	rm -f $(SRC_DIR)/*~ rpm/*~ *~
	rm -fr $(BUILD_DIR)

$(DEBUG_BUILD_DIR):
	mkdir -p $@

$(RELEASE_BUILD_DIR):
	mkdir -p $@

$(DEBUG_BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(DEBUG_CFLAGS) -MT"$@" -MF"$(@:%.o=%.d)" $< -o $@

$(RELEASE_BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(RELEASE_CFLAGS) -MT"$@" -MF"$(@:%.o=%.d)" $< -o $@

$(DEBUG_SO): $(DEBUG_OBJS)
	$(LD) $(DEBUG_OBJS) $(DEBUG_LDFLAGS) $(DEBUG_LIBS) -o $@

$(RELEASE_SO): $(RELEASE_OBJS)
	$(LD) $(RELEASE_OBJS) $(RELEASE_LDFLAGS) $(RELEASE_LIBS) -o $@
ifeq ($(KEEP_SYMBOLS),0)
	$(STRIP) $@
endif

#
# Install
#

PLUGINDIR ?= $$(pkg-config ofono --variable=plugindir)
ABS_PLUGINDIR := $(shell echo /$(PLUGINDIR) | sed -r 's|/+|/|g')

INSTALL = install
INSTALL_PLUGIN_DIR = $(DESTDIR)$(ABS_PLUGINDIR)

install: $(INSTALL_PLUGIN_DIR)
	$(INSTALL) -m 755 $(RELEASE_SO) $(INSTALL_PLUGIN_DIR)

$(INSTALL_PLUGIN_DIR):
	$(INSTALL) -d $@
