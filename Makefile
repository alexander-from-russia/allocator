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
TEST_BIN := $(TEST)/bin
INCLUDE_DIRS := $(SRC)
SRCS := $(wildcard $(SRC)/*.c)
ifeq (, $(filter test,$(MAKECMDGOALS)))
SRCS += $(PROJECT_ROOT)main.c
endif
OBJS := $(patsubst $(PROJECT_ROOT)%.c, $(OBJ)/%.o, $(SRCS))
TESTS := $(wildcard $(TEST)/*.c)
TESTBINS := $(patsubst $(TEST)/%.c, $(TEST_BIN)/%, $(TESTS))
bin := $(BIN)/yandex

CFLAGS := -Wall -Werror -pedantic -O2 -MMD $(addprefix -I,$(INCLUDE_DIRS))
LDFLAGS := -Wall -Werror -pedantic $(addprefix -I,$(INCLUDE_DIRS))

.PHONY: clean

all: $(bin)

$(bin): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ)/%.o: $(PROJECT_ROOT)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTBINS)
	for test in $(TESTBINS) ; do $$test ; done

$(TEST_BIN)/%: $(TEST)/%.c $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

-include $(OBJS:.o=.d)

clean:
	$(RM) -r $(BIN) $(OBJ) $(TEST_BIN)
