
cd src
cd server 

clang http_server.c -o http -Wall -Wextra -pedantic

mv http ../../build/http

cd .. 
cd .. 

./build/http
