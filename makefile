CXX=g++
RM=rm -f
CPPFLAGS=-Wall -std=c++14 -I/usr/local/boost_1_65_1
LIBLOC=/usr/local/boost_1_65_1/stage/lib
LDLIBS=-L$(LIBLOC) -lboost_iostreams -lboost_system
LDFLAGS=-DBOOST_SYSTEM_NO_DEPRECATED -Wl,-rpath=$(LIBLOC)
SRCS=NES.cpp Events.cpp ListManager.cpp Stat.cpp rngs.cpp rvgs.cpp RNG.cpp Station.cpp System.cpp Subject.cpp Observer.cpp StatNotifier.cpp WalkStat.cpp Estimator.cpp
MVASRCS:=$(filter-out NES.cpp,$(SRCS))
MVASRCS+=testMVA.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
MVAOBJS=$(subst .cpp,.o,$(MVASRCS))

all: NES

NES: $(OBJS)
	$(CXX) $(LDFLAGS) -o out $(OBJS) $(LDLIBS)

NES.o: $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRCS)

testMVA: $(MVAOBJS)
	$(CXX) $(LDFLAGS) -o testMVA $(MVAOBJS) $(LDLIBS)

testMVA.o: $(MVASRCS)
	$(CXX) $(CPPFLAGS) -c $(MVASRCS)

clean:
	$(RM) $(OBJS)\
	$(RM) $(MVAOBJS)

	
