CC=gcc
SHELL:=$(shell which bash) -e -o pipefail
UNAME_S:=$(shell uname -s)
_CFLAGS=-Wall -Wextra -Werror -Wshadow -Winline -D_GNU_SOURCE -std=c99 -g

BIN_DIR=$(CURDIR)/bin
SRC_DIR=$(CURDIR)/src
DATA_DIR=$(CURDIR)/etc/data
SCRIPT_DIR=$(CURDIR)/scripts
SLAVE_DIR=$(SRC_DIR)/slave
MASTER_DIR=$(SRC_DIR)/master
LIB_DIR=$(SRC_DIR)/lib

# All header files in libraries
INCLUDES_SLAVE=-I$(SRC_DIR) -I$(CURDIR) \
	        -I$(CURDIR)/deps/uthash \
	        -I$(SLAVE_DIR) \
	        -I$(LIB_DIR) \
	        -lpthread \
                -lpcap \

INCLUDES_MASTER=-I$(SRC_DIR) -I$(CURDIR) \
	        -I$(CURDIR)/deps/uthash \
	        -I$(MASTER_DIR) \
	        -I$(LIB_DIR) \
	        -lpthread \
                -lpcap \

# All .c files in src folder
_SOURCES=$(shell find $(SRC_DIR) -type f -iname '*.[c]')
_SOURCES_SLAVE=$(shell find $(SLAVE_DIR) -type f -iname '*.[c]')
_SOURCES_MASTER=$(shell find $(MASTER_DIR) -type f -iname '*.[c]')
_SOURCES_LIB=$(shell find $(LIB_DIR) -type f -iname '*.[c]')

# Create 1GB file
create:
	@echo "Run some script :"
	$(SCRIPT_DIR)/test.sh

# Build
build_slave:
	    -mkdir -p $(BIN_DIR)
	    $(CC) -o $(BIN_DIR)/slave $(_SOURCES_LIB) $(_SOURCES_SLAVE) $(INCLUDES_SLAVE)

build_master:
	    -mkdir -p $(BIN_DIR)
	    $(CC) -o $(BIN_DIR)/master $(_SOURCES_LIB) $(_SOURCES_MASTER) $(INCLUDES_MASTER)

clean:
	@echo "Deleting bin folder"
	rm -rf $(BIN_DIR)/*
