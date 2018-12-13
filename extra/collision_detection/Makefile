CC = g++
CFLAGS = -Wall
PROG = collisions

SRCS = main.cpp imageloader.cpp vec3f.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU -lGL -lm
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG).exe $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
