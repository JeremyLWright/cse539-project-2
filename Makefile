OBJS=BigInt.o RSA.o #task1.o #blindsig.o
CXX=g++
CXX_FLAGS=-std=gnu++0x -O3

all: task1 blindsig challenge_response
	@echo "====================================="
	@echo "Running Task 1"
	./task1
	./challenge_response
	@echo "========= Blind Signature ==========="
	./blindsig
	@echo "====================================="
	@echo "Jeremy Wright - Spring 2014 - 1000738685"
	@echo "====================================="


%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

task1: $(OBJS) task1.o
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS) task1.o 

blindsig: $(OBJS) blindsig.o
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS) blindsig.o 

challenge_response: $(OBJS) challenge_response.o
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJS) challenge_response.o 


clean:
	rm -rf *.o task1 blindsig challenge_response

