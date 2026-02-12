JUNIT_JAR=junit-platform-console-standalone-1.9.3.jar
SRC_DIR=Poligono
JAVA_FILES=$(SRC_DIR)/*.java

.PHONY: build test clean


build:
	javac -cp .:$(JUNIT_JAR) $(JAVA_FILES)

test: build
	java -jar $(JUNIT_JAR) --class-path .:Poligono --scan-class-path


clean:
	rm -f $(SRC_DIR)/*.class
