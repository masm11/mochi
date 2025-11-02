puni: puni.c
	# cc `pkg-config --cflags --libs gtk4 glut gl` -o puni puni.c
	cc `pkg-config --cflags --libs glut gl` -o puni puni.c
