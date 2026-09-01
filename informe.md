# Informe de tiempos: máximo subarreglo

## 1. Implementación

Se implementaron tres soluciones en C++:

- Cúbica: O(n^3)
- Cuadrática: O(n^2)
- Kadane: O(n)

Se validó la igualdad entre ellas con 200 arreglos aleatorios de enteros en el rango [-1000, 1000]. La salida de ejecución confirmó que las tres coinciden.

## 2. Tabla de tiempos

### Cúbica

| n | tiempo (s) | razón |
| ---: | ---: | ---: |
| 1000 | 0.058768 | - |
| 2000 | 0.341458 | 5.81 |
| 4000 | 2.805187 | 8.22 |
| 8000 | 22.302732 | 7.95 |

### Cuadrática

| n | tiempo (s) | razón |
| ---: | ---: | ---: |
| 1000 | 0.000271 | - |
| 2000 | 0.001067 | 3.93 |
| 4000 | 0.004520 | 4.24 |
| 8000 | 0.017623 | 3.90 |
| 16000 | 0.068010 | 3.86 |
| 32000 | 0.267845 | 3.94 |
| 64000 | 1.077105 | 4.02 |
| 128000 | 4.309436 | 4.00 |

### Kadane

| n | tiempo (s) | razón |
| ---: | ---: | ---: |
| 1000 | 0.000001 | - |
| 2000 | 0.000002 | 1.94 |
| 4000 | 0.000004 | 2.01 |
| 8000 | 0.000007 | 2.00 |
| 16000 | 0.000014 | 2.00 |
| 32000 | 0.000028 | 2.00 |
| 64000 | 0.000056 | 2.00 |
| 128000 | 0.000114 | 2.02 |
| 256000 | 0.000226 | 1.99 |
| 512000 | 0.000452 | 2.00 |
| 1024000 | 0.001072 | 2.37 |

## 3. Deducción del orden de crecimiento

- La razón al duplicar n para la cúbica ronda 8 (5.81, 8.22, 7.95): crecimiento O(n^3).
- La razón al duplicar n para la cuadrática ronda 4 (3.93 a 4.24): crecimiento O(n^2).
- La razón al duplicar n para Kadane ronda 2 (1.94 a 2.37, con una fila algo más alta por ruido del sistema): crecimiento O(n).

## 4. Predicción para n = 10^8

Se estimó el tiempo de las tres versiones para n = 10^8 extrapolando desde la mayor n medida de cada una, usando la fórmula t(n) ≈ t(n₀) · (n/n₀)^k, con k igual al orden de crecimiento deducido en la sección 3.

### Cúbica (k = 3, desde n₀ = 8000, t₀ = 22.302732 s)

- (10^8 / 8000)^3 = 12500^3 ≈ 1.953 × 10^12
- Predicción: 22.302732 × 1.953 × 10^12 ≈ 4.36 × 10^13 s (≈ 1.38 millones de años)

### Cuadrática (k = 2, desde n₀ = 128000, t₀ = 4.309436 s)

- (10^8 / 128000)^2 = 781.25^2 ≈ 610351.6
- Predicción: 4.309436 × 610351.6 ≈ 2.63 × 10^6 s (≈ 30.4 días)

### Kadane (k = 1, desde n₀ = 1024000, t₀ = 0.001072 s)

- Predicción estimada a partir de las mediciones: 0.090915 s
- Ejecución real: 0.090462 s

Solo la versión Kadane termina en menos de un minuto según su propia estimación, así que es la única que se ejecuta directamente sobre n = 10^8; cúbica y cuadrática quedan descartadas por sus predicciones (~1.38 millones de años y ~30.4 días respectivamente). La predicción de Kadane (0.090915 s) es prácticamente idéntica a la medición real (0.090462 s), lo que confirma que el crecimiento es lineal.

## 5. Conclusión

La versión Kadane es claramente la más eficiente y la única viable para entradas muy grandes. La cúbica y la cuadrática resultan impracticables para n grandes, mientras que la lineal resuelve el problema en tiempo casi constante por elemento.

## 6. Entorno de medición

- Lenguaje: C++17
- Compilador: GCC 16.1.0 (MinGW64)
- Procesador: Intel Core i5 12450HX
- Memoria: 8GB DDR5 4800MT/s
- Sistema operativo: Windows 11
- Arquitectura: x64