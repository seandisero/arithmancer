gcc -g -c src\token.c -o build\token.o
gcc -g -c src\stack.c -o build\stack.o
gcc -g -c src\queue.c -o build\queue.o
gcc -g -c src\arithmancer.c -o build\arithmancer.o
gcc -g -c main.c -o build\main.o
gcc -g -o arithmancer build\token.o build\stack.o build\queue.o build\arithmancer.o build\main.o -lm
.\arithmancer.exe
