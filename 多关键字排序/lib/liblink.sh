gcc ../*.c -fPIC -c -I
gcc -shared *.o -o libsort.so
