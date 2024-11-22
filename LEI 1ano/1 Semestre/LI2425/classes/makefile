C=ghc
CI=ghci
#FLAGS=-Wall -Wextra -Werror -lm -pedantic


# %: src/%.hs
# 	$(C) $^ -o bin/$@ $(FLAGS)
# 	@rm -rf ./src/$@*.o 
# 	@rm -rf ./src/$@*.hi

%: src/%.hs
	$(C) $^ -o bin/$@
	@rm -rf ./src/$@*.o
	@rm -rf ./src/$@*.hi

clean:
	@rm -rf ./bin/*
	@rm -rf ./src/*.o
	@rm -rf ./src/*.hi