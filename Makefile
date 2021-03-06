include config.mk

.SUFFIXES:
.SUFFIXES: .o .c

INC= inc

HDR=\
	inc/arg.h\
	inc/compat.h\
	inc/util.h

# SOURCE
BIN=\
	src/primegen

# LIB SOURCE
LIBUTILSRC=\
	lib/util/strtobase.c

# LIB PATH
LIBUTIL= lib/libutil.a

# LIB OBJS
LIBUTILOBJ= $(LIBUTILSRC:.c=.o)

# ALL
LIB= $(LIBUTIL)
OBJ= $(BIN:=.o) $(LIBUTILOBJ)
SRC= $(BIN:=.c)

# VAR RULES
all: $(BIN)

$(BIN): $(LIB) $(@:=.o)
$(OBJ): $(HDR) config.mk

# SUFFIX RULES
.o:
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(INC) -o $@ -c $<

# LIBRARIES RULES
$(LIBUTIL): $(LIBUTILOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

# USER ACTIONS
clean:
	rm -f $(BIN) $(OBJ) $(LIB)

.PHONY:
	all clean

