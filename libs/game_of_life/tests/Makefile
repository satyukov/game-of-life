.PHONY: phony_explicit

phony_explicit:

%.o: %.cc
	@g++ -c -Wall -Wno-sign-compare -std=c++17 -O3 -I../../ $< -o $@

%.run: %.o phony_explicit
	@g++ $< ../game_of_life.a -o $@
	@./$@

all: common_test.run

clean:
	@rm -f *.o
	@rm -f *.run
