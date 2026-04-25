# PRACTICA 3: ALGORITMOS VORACES Y HEURISTICAS

Este repositorio contiene el codigo fuente, los datos de prueba y el material asociado a la Practica 3. El objetivo de la practica es resolver dos tipos de problemas: por un lado, un problema de asignacion mediante un algoritmo voraz (greedy), y por otro, el problema del Viajante de Comercio (TSP) aplicando heuristicas constructivas como Vecino Mas Cercano e Insercion Mas Cercana sobre instancias reales que nos dan como ejemplo.


/// ESTRUCTURA DEL PROYECTO ///

El directorio esta organizado de la siguiente manera para separar el codigo fuente, los ejecutables, los datos de entrada y la documentacion:

* CARPETA SRC (el codigo fuente): Contiene las implementaciones en C++ de los ejercicios propuestos.
  - tasks_servers.cpp: Es la solucion voraz al problema de asignacion de tareas a servidores, maximizando el numero de tareas asignadas.Usa el MergeSort para ordenar requerimientos y capacidades, y aplica un emparejamiento entre ambos vectores ya ordenados.
  - nearest_neighbor.cpp / nearest_neighbor.h: Heuristica del Vecino Mas Cercano para el TSP. Partiendo de la ciudad inicial, en cada paso se visita la ciudad no visitada mas proxima hasta cerrar el tour.
  - nearest_insertion.cpp / nearest_insertion.h: Heuristica de Insercion Mas Cercana para el TSP. Construye el tour de forma incremental insertando en cada iteracion la ciudad mas cercana al recorrido parcial en la posicion que minimiza el incremento de coste.
  - data_loader.cpp / data_loader.h: Modulo encargado de parsear los ficheros en formato tsp, construir la matriz de distancias entre nodos y calcular el coste de un tour dado.
  - plot_tour.cpp / plot_tour.h: Modulo de visualizacion. Exporta el tour resultante a una imagen PNG mediante Gnuplot, permitiendo comparar visualmente la solucion heuristica con el tour optimo.

* CARPETA BIN (los ejecutables): Contiene los archivos ejecutables generados tras compilar las fuentes.
  - tasks_servers: Ejecutable correspondiente al problema voraz de asignacion de tareas/servidores.

* CARPETA DATA (los datos): Almacena las instancias de entrada del problema TSP en formato TSPLIB. Cada fichero .tsp contiene las coordenadas de las ciudades y, en algunos casos,el tour optimo de referencia.
  - berlin52.tsp: Instancia con 52 ciudades.
  - st70.tsp: Instancia con 70 ciudades.
  - kroA100.tsp: Instancia con 100 ciudades.
  - ch150.tsp: Instancia con 150 ciudades.
  - a280.tsp: Instancia con 280 ciudades.

* CARPETA DOC: Contiene el guion y el enunciado oficial de la practica en formato PDF.


/// EJECUCION DEL PROGRAMA ///

Para compilar manualmente cada uno de los programas se puede usar g++ enlazando los modulos correspondientes. Algunos ejemplos:

    g++ src/tasks_servers.cpp -o bin/tasks_servers

    g++ src/nearest_neighbor.cpp src/data_loader.cpp src/plot_tour.cpp -o bin/nearest_neighbor

    g++ src/nearest_insertion.cpp src/data_loader.cpp src/plot_tour.cpp -o bin/nearest_insertion

Una vez generados los ejecutables, se ejecutan de la siguiente manera:

* Asignacion de tareas y servidores:

    ./bin/tasks_servers

  El programa pedira el numero N de tareas/servidores, despues los N requerimientos de las tareas y por ultimo las N capacidades de los servidores. Devuelve el numero maximo de tareas que se pueden asignar.

* Heuristicas para el TSP:

    ./bin/nearest_neighbor ./data/berlin52.tsp

    ./bin/nearest_insertion ./data/kroA100.tsp

  Estos programas cargan la instancia, calculan el tour mediante la heuristica correspondiente, muestran por pantalla el coste obtenido (y el coste optimo si esta disponible en el fichero) y generan dos imagenes PNG con el tour optimo y el tour heuristico para su comparacion visual