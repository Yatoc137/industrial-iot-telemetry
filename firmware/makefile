#=== Variables ==========================================================================#

CC := gcc # IMPORTANT! change to esp32 cross compiler before flashing or linking
INCLUDE := -Iinclude

DEPFLAGS := -MMD -MP

DEBUGFLAGS := -Og -g3 -fno-omit-frame-pointer -fno-inline \
			  -Wall -Wextra -Wshadow -Wformat=2

RELEASEFLAGS := -O2 -DNDEBUG -Wall -Wextra

CIFLAGS := -Werror -fno-common -Wundef -Wdouble-promotion

CFLAGS :=

#=== Source & Objects ===================================================================#

SRC := $(shell find src -name "*.c")

OBJ_DEBUG   := $(patsubst src/%.c,build/debug/%.o,$(SRC))
OBJ_RELEASE := $(patsubst src/%.c,build/release/%.o,$(SRC))

#=== PHONY Rules ========================================================================#

.PHONY: all release clean ci

#=== High-Level Rules ===================================================================#

all: CFLAGS = $(DEBUGFLAGS)
all: $(OBJ_DEBUG)

release: CFLAGS = $(RELEASEFLAGS)
release: $(OBJ_RELEASE)

ci:
	$(MAKE) clean || true
	$(MAKE) all CFLAGS="$(DEBUGFLAGS) $(CIFLAGS)"

#=== Generic Rules ======================================================================#

build/debug/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

build/release/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

#=== Dependencies =======================================================================#

-include $(OBJ_DEBUG:.o=.d)
-include $(OBJ_RELEASE:.o=.d)

#=== Other Rules ========================================================================#

clean:
	rm -rf build

#========================================================================================#