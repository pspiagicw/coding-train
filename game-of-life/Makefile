CFLAGS=-Wall -Wextra -g
LIBS=-lraylib -lm -lgoreland -Ldeps/goreland
INCLUDE=-Ideps/goreland 
run: build
	./golf

build: game.c render.c state.c build-deps render.c
	gcc -c $(CFLAGS) game.c $(LIBS) $(INCLUDE)
	gcc -c $(CFLAGS) render.c $(LIBS) $(INCLUDE)
	gcc -c $(CFLAGS) state.c $(LIBS) $(INCLUDE)
	gcc -o golf $(CFLAGS) *.o $(LIBS) $(INCLUDE)
	make clean
build-deps: 
	cd deps/goreland && make
clean:
	rm *.o
.PHONY: build run build-deps
