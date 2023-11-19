all:
	gcc -Wall -Wextra -g -Iinclude main.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run