.DEFAULT_GOAL := game_of_life.a
.PHONY: clean

%.o: %.cc
	g++ -c -Wall -std=c++17 -O3 $< -o $@

game_of_life.a: common.o field2d.o
	ar crf game_of_life.a $^

clean:
	rm *.o
	rm *.a
