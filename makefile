CXX=g++
RM=rm -f
CPPFLAGS=-Wall -std=c++11
SRCS=NES.cpp Events.cpp ListManager.cpp Stat.cpp rngs.cpp rvgs.cpp RNG.cpp Station.cpp System.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: NES

NES: $(OBJS)
	$(CXX) -o out $(OBJS)

NES.o: $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRCS)

clean:
	$(RM) $(OBJS)

	
