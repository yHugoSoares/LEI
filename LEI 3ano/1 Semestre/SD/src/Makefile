# Makefile to compile all Java files

JAVAC=javac
SRC=$(wildcard *.java)
CLASSES=$(SRC:.java=.class)

all:
	$(JAVAC) -d . $(SRC)

run: all
	java BankTest

clean:
	rm -r src/*.class *.class
