cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g

# Agregamos -I. para asegurar que busque headers locales y generales
includes = -I. -I../src/captura -I../src/Estructuras

# Librerías existentes (Hash y Cola)
libs_path = -L../../lib
libs = -lHashTable -lCola

# ARCHIVOS FUENTE
# 1. main.c y Libro.c están en la carpeta actual
# 2. arbol.c debe buscarse en su carpeta (ajusta si la ruta es diferente)
# 3. nodoarbol.c debe buscarse en su carpeta (ajusta si la ruta es diferente)
# IMPORTANTE: Si nodoarbol.c está en "nodos", usa ../Estructuras/nodos/nodoarbol.c
source = main.c Libro.c ../Estructuras/arbol/arbol.c ../Estructuras/nodos/nodoarbol.c

output = ../../bin/practica10

build:
	gcc $(cflags) $(source) -o $(output) $(includes) $(libs_path) $(libs)
	@echo "Compilo Exitosamente!!!"

rebuild:
	make -C ../captura
	make -C ../Estructuras/hash
	make -C ../Estructuras/cola 
	gcc $(cflags) $(source) -o $(output) $(includes) $(libs_path) $(libs)
	@echo "Compilo Exitosamente!!!"

run:
	../../bin/practica10.exe