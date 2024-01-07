all:
	gcc -Wall -Wextra -g -Iinclude main.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run
rectangle:
	gcc -Wall -Wextra -g -Iinclude rectangle.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run
text:
	gcc -Wall -Wextra -g -Iinclude text.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run
font-creator:
	gcc -Wall -Wextra -g -Iinclude font-creator.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run
pong:
	gcc -Wall -Wextra -g -Iinclude pong.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run
space-shooter:
	gcc -Wall -Wextra -g -Iinclude space-shooter.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run
farm-poc:
	gcc -Wall -Wextra -g -Iinclude farm-poc.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run
light:
	gcc -Wall -Wextra -g -Iinclude light.c glad.c -o run -Llib lib/libglfw3.a lib/libglfw3dll.a -lgdi32
	./run