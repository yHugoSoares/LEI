# JFLAGS = -g -cp
# JC = javac
# SRC = src
# .SUFFIXES: .java .class
# .java.class:
# 	$(JC) $(JFLAGS) $(SRC) $*.java

# CLASSES = \
# 	Circulo.java \
# 	Ficha1.java \
# 	Ficha2.java \
# 	Ficha3.java \
# 	HelloWrld.java

# default: classes

# classes: $(CLASSES:%.java=$(SRC)/%.class)

# clean:
# 	rm $(SRC)/*.class

JFLAGS = -g
JC = javac
SRC = src
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	Circulo.java \
	Sensor.java \
	Musica.java \
	LinhaEncomenda.java \
	Encomenda.java \
	Ficha1.java \
	Ficha2.java \
	Ficha3.java \
	HelloWrld.java
	

default: classes

classes: $(CLASSES:%.java=%.class)

clean:
	rm *.class