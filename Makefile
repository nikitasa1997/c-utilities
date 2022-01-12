CC=gcc
RM=rm -frd
CFLAGS=-Wall -Walloc-zero -Walloca -Wanalyzer-too-complex -Warith-conversion \
    -Warray-bounds=2 -Wbad-function-cast -Wc++-compat -Wcast-align=strict \
    -Wcast-qual -Wconversion -Wdate-time -Wdisabled-optimization \
    -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond -Werror -Wextra \
    -Wfatal-errors -Wfloat-equal -Wformat=2 -Wformat-overflow=2 \
    -Wformat-signedness -Wformat-truncation=2 -Wimplicit-fallthrough=5 \
    -Winit-self -Winline -Wlogical-op -Wmissing-declarations \
    -Wmissing-include-dirs -Wmissing-noreturn -Wmissing-prototypes \
    -Wnested-externs -Wnull-dereference -Wold-style-definition -Wpacked \
    -Wpadded -Wpedantic -Wredundant-decls -Wshadow=global -Wshift-overflow=2 \
    -Wstrict-overflow=5 -Wstrict-prototypes -Wstringop-overflow=4 \
    -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code \
    -Wunused-const-variable=2 -Wunused-macros -Wvector-operation-performance \
    -Wvla -Wwrite-strings -fanalyzer -pedantic-errors -std=c18 -Iinclude/
# -Wattribute-alias=2 -Wsync-nand -Wunused
LDFLAGS=
LDLIBS=-lm
SOURCES=src/main1.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main1

all: $(SOURCES) $(EXECUTABLE)

debug: CFLAGS+=-Og -g
debug: all
release: CFLAGS+=-DNDEBUG -O3 -flto -march=native -mtune=native -s
release: LDFLAGS+=-O3 -flto -march=native -mtune=native -s
release: all

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
