INCLUDE = -I../include -I../
FLAGS = -Wall -Wextra -g
LIB = -Llib ../lib/libglfw3.a ../lib/libglfw3dll.a -lgdi32

all:
	gcc $(FLAGS) $(INCLUDE) main.c glad.c -O1 -o run $(LIB) 
	./run
rectangle:
	gcc $(FLAGS) $(INCLUDE) rectangle.c glad.c -O1 -o run $(LIB) 
	./run
text:
	gcc $(FLAGS) $(INCLUDE) text.c glad.c -O1 -o run $(LIB) 
	./run
font-creator:
	gcc $(FLAGS) $(INCLUDE) font-creator.c glad.c -O1 -o run $(LIB) 
	./run
pong:
	gcc $(FLAGS) $(INCLUDE) pong.c glad.c -O1 -o run $(LIB) 
	./run
space-shooter:
	gcc $(FLAGS) $(INCLUDE) space-shooter.c glad.c -O1 -o run $(LIB) 
	./run
farm-poc:
	gcc $(FLAGS) $(INCLUDE) farm-poc.c glad.c -O1 -o run $(LIB) 
	./run
light:
	gcc $(FLAGS) $(INCLUDE) light.c glad.c -O1 -o run $(LIB) 
	./run
model:
	gcc $(FLAGS) $(INCLUDE) model.c glad.c -O1 -o run $(LIB) 
	./run
# Needs a different exe to run concurently
model-creator:
	gcc $(FLAGS) $(INCLUDE) model-creator.c glad.c -O1 -o run-model-creator $(LIB) 
	./run-model-creator
bun2d-mark:
	gcc $(FLAGS) $(INCLUDE) bun2d-mark.c glad.c -O1 -o run $(LIB) 
	./run
animation:
	gcc $(FLAGS) $(INCLUDE) animation.c glad.c -O1 -o run $(LIB) 
	./run
bunny-hop:
	gcc $(FLAGS) $(INCLUDE) bunny-hop.c glad.c -O1 -o run $(LIB) 
	./run
bun2d-benchmark:
	gcc $(FLAGS) $(INCLUDE) bun2d-benchmark.c glad.c -O1 -o run $(LIB) 
	./run
camera:
	gcc $(FLAGS) $(INCLUDE) camera.c glad.c -O1 -o run $(LIB) 
	./run
raycaster:
	gcc $(FLAGS) $(INCLUDE) raycaster.c glad.c -O1 -o run $(LIB) 
	./run
raycaster-voxel:
	gcc $(FLAGS) $(INCLUDE) raycaster-voxel.c glad.c -O1 -o run $(LIB) 
	./run
