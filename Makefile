.PHONY: phony_explicit

phony_explicit:

%.o: %.cc
	@g++ -c -Wall -Wno-sign-compare -std=c++17 -O3 -Ilibs $< -o $@

%.run: %.o phony_explicit
	@g++ $< libs/game_of_life/game_of_life.a -o $@
	@./$@

all: *.o

test_all: $(patsubst %.cc,%.run,$(wildcard *_test.cc))

clean:
	@rm -f *.o
	@rm -f *.run
