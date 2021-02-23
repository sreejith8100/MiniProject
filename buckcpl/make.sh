gcc -c pbPlots.c -std=c99 -O3 -march=native
gcc -c supportLib.c -std=c99 -O3 -march=native
gcc -c example1.c -std=c99 -O3 -march=native
gcc example1.o pbPlots.o supportLib.o -lm -o example1
strip example1
