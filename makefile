CXX=g++
RM=rm -f
CPPFLAGS=-Wall -std=c++14
SRCS=NES.cpp Events.cpp ListManager.cpp Stat.cpp rngs.cpp rvgs.cpp rvms.cpp RNG.cpp Station.cpp System.cpp Subject.cpp Observer.cpp StatNotifier.cpp WalkStat.cpp Estimator.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: NES

NES: $(OBJS)
	$(CXX) -o out $(OBJS)

NES.o: $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRCS)

clean:
	$(RM) $(OBJS)
