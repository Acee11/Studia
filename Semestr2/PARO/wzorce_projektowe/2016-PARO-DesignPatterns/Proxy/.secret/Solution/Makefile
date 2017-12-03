PROGNAME=Proxy
CXXFLAGS=-std=c++11 -Wall -MMD
SRCS=main.cpp
DEPENDS=$(PROGNAME).d

all: $(PROGNAME)

$(PROGNAME): $(SRCS)
	g++ $(CXXFLAGS) -I. -o $(PROGNAME) $(SRCS) 

.PHONY: clean
clean:
	rm -rf *.o $(PROGNAME) ${DEPENDS}

-include ${DEPENDS}
