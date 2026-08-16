CC ?= cc
CPPFLAGS ?= -I.
CFLAGS ?= -std=c11 -Wall -Wextra -Wconversion -Werror -pedantic
LDLIBS ?= -lm

CORE_SOURCES = backpack.c command.c container.c game.c item.c parser.c room.c world.c
SOURCES = main.c $(CORE_SOURCES)
OBJECTS = $(SOURCES:.c=.o)
TARGET = adventure
TEST_TARGET = tests/test_core

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): tests/test_core.c $(CORE_SOURCES)
	$(CC) $(CPPFLAGS) $(CFLAGS) tests/test_core.c $(CORE_SOURCES) -o $@ $(LDLIBS)

.PHONY: all clean test scenario sanitize

test: $(TARGET) $(TEST_TARGET)
	@./$(TEST_TARGET) >/dev/null
	@sh tests/test_cli.sh
	@printf 'All tests passed.\n'

scenario: $(TARGET)
	./$(TARGET) < scenario.txt

sanitize:
	$(MAKE) clean
	ASAN_OPTIONS=detect_leaks=0 UBSAN_OPTIONS=halt_on_error=1 \
		$(MAKE) CFLAGS="$(CFLAGS) -g3 -fsanitize=address,undefined -fno-omit-frame-pointer" test

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_TARGET)
