# Makefile
#
#  Created on: Apr 11, 2023
#      Author: alexander
#

PROJECT_ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRC := $(PROJECT_ROOT)allocator
TEST := $(PROJECT_ROOT)tests
OBJ := $(PROJECT_ROOT)obj
BIN := $(PROJECT_ROOT)bin
INCLUDE_DIRS := $(SRC)
SRCS := $(wildcard $(SRC)/*.c)
ifeq (, $(filter test,$(MAKECMDGOALS)))
SRCS += $(PROJECT_ROOT)main.c
endif
OBJS := $(patsubst $(PROJECT_ROOT)%.c, $(OBJ)/%.o, $(SRCS))
TESTS := $(wildcard $(TEST)/*.c)
TESTBINS := $(patsubst $(TEST)/%.c, $(TEST)/bins/%, $(TESTS))
BINS := $(BIN)/yandex

CFLAGS := -Wall -Werror -pedantic -O2 $(addprefix -I,$(INCLUDE_DIRS))
LDFLAGS := -Wall -Werror -pedantic $(addprefix -I,$(INCLUDE_DIRS))

$(info srcs $(OBJS))

.PHONY: clean

all: $(BINS)

$(BINS): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJS): $(SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

#test: $(TEST)/bin $(TESTBINS)
#	for test in $(TESTBINS) ; do $$test ; done

clean: $(RM) -r $(BIN) $(OBJ) 











