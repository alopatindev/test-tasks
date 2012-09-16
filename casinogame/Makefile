all: build run

build:
	gcc -c src/thirdparty/tgaload.c -std=c99 -o tgaload.o
	g++ tgaload.o src/*.cpp -o casinogame -lglut -lGLU
	strip casinogame

run:
	./casinogame

clean:
	rm -f casinogame tgaload.o
