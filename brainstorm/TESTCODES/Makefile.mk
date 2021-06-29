CC=gcc

game: main.o essentials.o
	$(CC) main.o essentials.o -o ./game.exe 

main.o:main.c utils.h raylib.h 
	$(CC) main.c -o ../object/main.o -Wall -std=c99 -Wno-missing-braces -I ..\include\ -L ..\lib\ -lraylib -lopengl32 -lgdi32 -lwinmm 

essentials.o:essentials.c raylib.h utils.h
	$(CC) essentials.c -o ../object/essentials.o -Wall -std=c99 -Wno-missing-braces -I ..\include\ -L ..\lib\ -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	del game.exe
	