EXECS = TrafficSim
OBJS = TrafficSim.o Animator.o Intersection.o TrafficLight.o VehicleBase.o Lane.o

#### use next two lines for Mac
CC = clang++
CCFLAGS = -std=c++11 -stdlib=libc++

#### use next two lines for mathcs* machines:
#CC = g++
#CCFLAGS = -std=c++11

all: $(EXECS)

testAnimator: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)
