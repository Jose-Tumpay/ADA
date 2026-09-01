# Máximo subarreglo en C++

Este proyecto implementa las tres soluciones del problema del máximo subarreglo:

- Cúbica: O(n^3)
- Cuadrática: O(n^2)
- Kadane: O(n)

## Archivos

- `max_subarray.hpp`: implementación de las tres funciones.
- `main.cpp`: validación aleatoria, benchmarking y ejecución de la versión lineal.

## Verificación

Se validan 200 arreglos aleatorios con enteros en el rango [-1000, 1000] y se comprueba que las tres funciones devuelven el mismo valor.

## Medición

Se toman tiempos para tamaños de entrada 1000, 2000, 4000, 8000, 16000, ... hasta el máximo permitido por la máquina. La razón entre tiempos consecutivos permite inferir el orden de crecimiento.

## Conclusión

- Cúbica crece como O(n^3), con razones cercanas a 8 al duplicar n.
- Cuadrática crece como O(n^2), con razones cercanas a 4 al duplicar n.
- Kadane crece como O(n), con razones cercanas a 2 al duplicar n.

## Entorno donde se midió

- Lenguaje: C++17
- Compilador: GCC 16.1.0 (MinGW64)
- Procesador: equipo Windows con arquitectura x86_64 (detallado por systeminfo)
- Memoria: se reportó memoria total física con `systeminfo`
