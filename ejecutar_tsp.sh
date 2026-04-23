#!/bin/bash

# 1. Crear carpeta para imágenes en la raíz si no existe
mkdir -p imagenes

# 2. Configuración de rutas
SRC_DIR="./src"
DATA_DIR="./data"
SUPPORT_FILES="$SRC_DIR/data_loader.cpp $SRC_DIR/plot_tour.cpp"

echo "--- Compilando algoritmos ---"

# Compilar Nearest Neighbor
g++ $SRC_DIR/nearest_neighbor.cpp $SUPPORT_FILES -o nearest_neighbor.bin -O3 -I$SRC_DIR
if [ $? -ne 0 ]; then echo "✘ Error compilando NN"; exit 1; fi

# Compilar Nearest Insertion
g++ $SRC_DIR/nearest_insertion.cpp $SUPPORT_FILES -o nearest_insertion.bin -O3 -I$SRC_DIR
if [ $? -ne 0 ]; then echo "✘ Error compilando NI"; exit 1; fi

echo "✔ Compilación exitosa."

# 3. Bucle para procesar cada archivo .tsp en la carpeta data
for file in "$DATA_DIR"/*.tsp; do
    # Extraer el nombre del archivo para mostrar en consola
    filename=$(basename "$file")
    
    echo -e "\n========================================"
    echo "Procesando instancia: $filename"
    echo "========================================"

    # Ejecutar Nearest Neighbor
    echo "[Ejecutando NN...]"
    ./nearest_neighbor.bin "$file"

    # Ejecutar Nearest Insertion
    echo "[Ejecutando NI...]"
    ./nearest_insertion.bin "$file"

    # Mover imágenes generadas para esta instancia a la carpeta imagenes
    # El código usa el nombre de la instancia para el prefijo de la imagen
    mv *.png imagenes/ 2>/dev/null
done

echo -e "\n--- Proceso finalizado ---"
echo "Todas las imágenes se encuentran en la carpeta: $(pwd)/imagenes"
