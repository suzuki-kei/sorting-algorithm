SRC = main.cpp sorting-algorithm.hpp sorting-algorithm-test.hpp sorting-algorithm-test.cpp
OUT = a.out

$(OUT): $(SRC)
	g++ -Ofast -Wall -Werror -o $(OUT) $^

run: $(OUT)
	@./$(OUT)

clean:
	rm -f $(OUT)

