include config.mk


# defaults for options
PREFIX ?= /usr/local
CFLAGS ?= -W -Wall -Wextra -pedantic -Wwrite-strings -g
LDFLAGS ?= -g

# enable c99 features
CFLAGS += -std=c99

# link to sdl2
LDLIBS += -lSDL2 -lSDL2_image

EXE = fps-tester
SRC = fps-tester.c clock.c entity.c gui.c scene.c
OBJ = $(SRC:.c=.o)

IMG = images/smiley.png images/smiley-small.png images/smiley-big.png

.PHONY:
all: $(IMG) $(EXE)

$(EXE): $(OBJ)

images/smiley.png: images/smiley.svg
	convert $^ -scale 50x50 $@

images/smiley-small.png: images/smiley.svg
	convert $^ -scale 30x30 $@

images/smiley-big.png: images/smiley.svg
	convert $^ -scale 150x150 $@

.PHONY:
clean:
	rm -vf $(OBJ)
