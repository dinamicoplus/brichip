mkdir bin
gcc -c src/SDLm.c
gcc -c src/chip8.c
gcc -c src/SDL_win32_main.c
gcc -o bin/brichip-1.1.exe SDLm.o chip8.o SDL_win32_main.o -lSDL
pause