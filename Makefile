all: mochi

mochi: mochi.c
ifdef APPLE
	cc -framework OpenGL -framework GLUT -o mochi mochi.c
else
	cc `pkg-config --cflags --libs gl glut` -o mochi mochi.c
endif

clean:
	rm -f mochi
