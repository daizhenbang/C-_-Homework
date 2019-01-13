CC = g++-8

exe: test.x
	chmod +x test.x

test.x: main.o
	$(CC) main.o -o test.x

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -rf *.o test.x

