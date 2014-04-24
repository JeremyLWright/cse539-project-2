EXECUTABLE=task1
OBJS=BigInt.o RSA.o task1.o
CXX=g++
CXX_FLAGS=-std=gnu++11 -Wall -O3 -Idependencies/include -Ldependencies/lib

%.o: %.cpp dependencies/include/primesieve.hpp
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

$(EXECUTABLE): $(OBJS) 
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS) -static -lprimesieve

clean:
	rm -rf $(OBJS) dependencies task1
	cd primesieve-5.2 && make clean

dependencies/include/primesieve.hpp:
	cd primesieve-5.2 && ./configure --prefix=$(PWD)/dependencies && make install && cd ..

