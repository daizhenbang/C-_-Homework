
exe: test.x
	chmod +x test.x

test.x: scratch.o
	g++ scratch.o -o test.x
	mkdir -p obj
	mv *.o obj

scratch.o: scratch.cpp
	g++ -c scratch.cpp 

clean:
	rm -rf obj test.x
