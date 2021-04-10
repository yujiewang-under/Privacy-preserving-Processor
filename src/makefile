LDFLAGS=-ltfhe-spqlios-avx
CCFLAGS=--std=c++11 -fopenmp
all:
	g++ $(CCFLAGS) main.cpp -o cpu -g  $(LDFLAGS)
	./cpu
demo:
	g++ $(CCFLAGS) main.cpp -o cpu -g -D DEMO $(LDFLAGS)
	./cpu
clean:
	rm -rf cpu
