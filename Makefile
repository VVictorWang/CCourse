CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-2.0)
CFLAGS += -std=c11
LIBS = $(shell $(PKGCONFIG) --libs gtk+-2.0)
RM = rm

DIR_GUI = ./src/view
DIR_MODEL = ./src/model
DIR_SRC = ./src
DIR_BIN = ./bin
SRC = $(wildcard ${DIR_SRC}/*.c)
SRC += $(wildcard ${DIR_GUI}/*.c)
SRC += $(wildcard ${DIR_MODEL}/*.c)
OBJ = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${SRC}))

TARGET = infoManagementSystem
BIN_TARGET = ${DIR_BIN}/${TARGET}

.PHONY:all clean

all: ${BIN_TARGET}

${BIN_TARGET}:${OBJ}
	$(CC) $^ -o $@  $(LIBS)
	find ${DIR_BIN} . -name '*.o' -exec $(RM) '{}' \;

${DIR_BIN}/%.o:$(DIR_GUI)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

${DIR_BIN}/%.o:$(DIR_MODEL)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

${DIR_BIN}/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) ${BIN_TARGET}

