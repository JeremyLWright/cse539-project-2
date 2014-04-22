EXECUTABLE=prog
OBJS=BigInt.o RSA.o rsaDriver.o rsatry1.o
CXX=g++

%.o: %.cpp
	$(CXX) -o $@ -c $<

$(EXECUTABLE): $(OBJS)
	$(CXX) -o $@ $(OBJS)

clean:
	rm -rf $(OBJS)

