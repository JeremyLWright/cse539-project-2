OBJS=BigInt.o RSA.o #task1.o #blindsig.o
CXX=g++
CXX_FLAGS=-std=gnu++11 -Wall -O3

all: task1 blindsig


%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

task1: $(OBJS) task1.o
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS) task1.o -static

blindsig: $(OBJS) blindsig.o
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS) blindsig.o -static


clean:
	rm -rf $(OBJS) dependencies task1 blindsig

