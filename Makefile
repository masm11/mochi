mochi: mochi.c
	cc `pkg-config --cflags --libs glut gl` -o mochi mochi.c
