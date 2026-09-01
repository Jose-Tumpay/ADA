# Informe de tiempos: máximo subarreglo

## 1. Implementación

Se implementaron tres soluciones en C++:

- Cúbica: O(n^3)
- Cuadrática: O(n^2)
- Kadane: O(n)

Se validó la igualdad entre ellas con 200 arreglos aleatorios de enteros en el rango [-1000, 1000]. La salida de ejecución confirmó que las tres coinciden.

## 2. Tabla de tiempos

### Cuadrática

| n | tiempo (s) | razón |
|---:|---:|---:|
| 1000 | 0.000292 | - |
| 2000 | 0.000977 | 3.34 |
| 4000 | 0.004381 | 4.48 |
| 8000 | 0.016190 | 3.70 |
| 16000 | 0.069041 | 4.26 |
| 32000 | 0.259971 | 3.77 |
| 64000 | 1.049105 | 4.04 |
| 128000 | 4.283246 | 4.08 |

### Kadane

| n | tiempo (s) | razón |
|---:|---:|---:|
| 1000 | 0.000001 | - |
| 2000 | 0.000002 | 1.96 |
| 4000 | 0.000003 | 2.00 |
| 8000 | 0.000007 | 2.01 |
| 16000 | 0.000013 | 2.00 |
| 32000 | 0.000026 | 1.99 |
| 64000 | 0.000055 | 2.09 |
| 128000 | 0.000151 | 2.76 |
| 256000 | 0.000212 | 1.41 |
| 512000 | 0.000422 | 1.99 |
| 1024000 | 0.000933 | 2.21 |

### Cúbica

La evidencia experimental muestra que al duplicar n, el tiempo se multiplica aproximadamente por 8:

- 4000 -> 2.73354 s
- 8000 -> 22.1875 s
- razón ≈ 8.12

Esto es consistente con crecimiento O(n^3).

## 3. Deducción del orden de crecimiento

- Si la razón al duplicar n es ~8, entonces el crecimiento es cúbico: O(n^3).
- Si la razón al duplicar n es ~4, entonces el crecimiento es cuadrático: O(n^2).
- Si la razón al duplicar n es ~2, entonces el crecimiento es lineal: O(n).

## 4. Predicción para n = 10^8

Con la versión de Kadane, la predicción estimada a partir de las mediciones fue:

- 0.086618 s

Ejecución real:

- 0.101995 s

La predicción es muy cercana a la medición real, por lo que la estimación del crecimiento lineal es correcta.

## 5. Conclusión

La versión Kadane es claramente la más eficiente y la única viable para entradas muy grandes. La cúbica y la cuadrática resultan impracticables para n grandes, mientras que la lineal resuelve el problema en tiempo casi constante por elemento.

## 6. Entorno de medición

- Lenguaje: C++17
- Compilador: GCC 16.1.0 (MinGW64)
- Sistema operativo: Windows
- Arquitectura: x64

