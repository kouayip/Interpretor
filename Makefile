CC = g++ # compilateur
CFLAGS = -c -std=gnu++17 -g #options de compilation (debug par exemple)
LDFLAGS = -g #options de link (librairies)
SRC = ${wildcard src/*.cpp} # création automatique de la liste des sources
HDR = ${wildcard include/*.hpp} # création automatique de la liste des sources
OBJ = ${SRC:.cpp=.o}
EXEC = trader
 
all: ${SRC} ${OBJ} ${EXEC}
 
${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.cpp ${HDR}
	${CC} ${CFLAGS} $< -o $@
 
.PHONY: clean mrproper
 
clean:
	rm -rf src/*.o
 
mrproper: clean
	rm -rf ${EXEC}