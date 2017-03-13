all: itbmapview

myPlane: cannon.c game.c keypress.c main.c stack.c color.c graphics.c line.c rotate.c physics.c grafika.h
	gcc -o myPlane cannon.c game.c keypress.c main.c stack.c color.c graphics.c line.c rotate.c physics.c -lpthread -lm -std=gnu99

myPlane-fast: cannon.c game.c keypress.c main.c stack.c color.c graphics.c line.c rotate.c physics.c grafika.h
	gcc -o myPlane-fast cannon.c game.c keypress.c main.c stack.c color.c graphics.c line.c rotate.c physics.c -O2 -lpthread -lm -std=gnu99

itbmapview: keypress.c itbmapview.c stack.c color.c graphics.c line.c rotate.c physics.c grafika.h
	gcc -o itbmapview itbmapview.c keypress.c stack.c color.c graphics.c line.c rotate.c physics.c -lpthread -O2 -lm -std=gnu99

clean:
	$(RM) myPlane
	$(RM) myPlane-fast
	$(RM) itbmapview
