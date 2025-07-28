# Makefile

# Compilador y flags
CC       := gcc
CFLAGS   := -Wall -Wextra -I./src -I./src/DList -std=c99 -g

# Directorios
SRCDIR   := src
DLISTDIR := $(SRCDIR)/DList
TESTDIR  := Tests

# Objetos de la librería (src)
LIB_SRCS  := \
    $(SRCDIR)/defl.c         \
    $(SRCDIR)/deff.c         \
    $(SRCDIR)/search.c       \
    $(SRCDIR)/apply.c        \
    $(SRCDIR)/operaciones.c  \
    $(SRCDIR)/variables.c    \
    $(SRCDIR)/parser.c       \
    $(DLISTDIR)/dlist.c

LIB_OBJS  := $(LIB_SRCS:.c=.o)

# Objeto de main
MAIN_SRC  := $(SRCDIR)/main.c
MAIN_OBJ  := $(MAIN_SRC:.c=.o)

# Tests: detecta todos los test_*.c en test/
TEST_SRCS := $(wildcard $(TESTDIR)/test_*.c)
TEST_BINS := $(patsubst $(TESTDIR)/%.c, % , $(TEST_SRCS))

# Target por defecto
.PHONY: all
all: main $(TEST_BINS)

# Link final del ejecutable principal
main: $(MAIN_OBJ) $(LIB_OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# Regla genérica para compilar objetos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Genera cada test vinculándolo con la librería
# e.g. test_cola: test/test_cola.c $(LIB_OBJS)
$(TEST_BINS): %: $(TESTDIR)/%.c $(LIB_OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# Limpieza de binarios y objetos
.PHONY: clean
clean:
	rm -f main $(TEST_BINS) \
	      $(LIB_OBJS) $(MAIN_OBJ)

