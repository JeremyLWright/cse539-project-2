EXECUTABLE=task1
OBJS=BigInt.o RSA.o task1.o
CXX=g++
CXX_FLAGS=-std=gnu++11 -Wall -O3

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(OBJS)

