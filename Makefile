mochi: mochi.c
	cc `pkg-config --cflags --libs gl glut` -o mochi mochi.c
	# cc -framework OpenGL -framework GLUT -o mochi mochi.c
