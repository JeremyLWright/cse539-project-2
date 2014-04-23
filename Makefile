EXECUTABLE=task1
OBJS=BigInt.o RSA.o task1.o
CXX=g++
CXX_FLAGS=-std=gnu++11 -Wall -O3 -Idependencies/include -Ldependencies/lib

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

$(EXECUTABLE): $(OBJS) dependencies/lib/libprimesieve.a
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS) -static -lprimesieve

clean:
	rm -rf $(OBJS) dependencies task1
	cd primesieve-5.2 && make clean

dependencies/lib/libprimesieve.a:
	cd primesieve-5.2 && ./configure --prefix=$(PWD)/dependencies && make install && cd ..

