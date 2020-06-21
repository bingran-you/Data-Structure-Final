gcc ../*.c -fPIC -c -I
gcc -shared *.o -o libtraffic.so
