# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ej4.cpp MaestroPokemon.cpp trie.cpp SetTabu.cpp

# Objetos que serán generados
OBJECTS=ej4.o MaestroPokemon.o SetTabu.o

# Nombre del ejecutable a generar
EXECUTABLE=ej4

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
