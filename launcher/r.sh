cd ..
cd src
cd server

clang http_server.c -o ../../build/http -Wall -Wextra -pedantic

cd ..
cd ..
cd build 

./http


