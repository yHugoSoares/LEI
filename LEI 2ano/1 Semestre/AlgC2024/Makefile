CC=gcc
CI=ghci
FLAGS=-Wall -Wextra -Werror -lm -pedantic


# %: src/%.hs
# 	$(C) $^ -o bin/$@ $(FLAGS)
# 	@rm -rf ./src/$@*.o 
# 	@rm -rf ./src/$@*.hi

%: src/%.c
	$(CC) $^ -o bin/$@

clean:
	@rm -rf ./bin/*
	@rm -rf ./src/*.o
	@rm -rf ./src/*.hi