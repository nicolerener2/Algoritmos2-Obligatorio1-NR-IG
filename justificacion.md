# Justificación de órdenes — Obligatorio 1

> **Instrucciones** (borrar esta sección antes de entregar): para cada ejercicio cuya
> letra plantea restricciones de órdenes (tiempo o espacio), justificar brevemente por
> qué la solución cumple, indicando qué estructuras de datos o algoritmos se utilizaron.
> Ejemplo: "La letra exige inserción en O(log n); usamos un min-heap sobre arreglo,
> donde flotar/hundir recorren a lo sumo la altura del árbol". Si un ejercicio no tiene
> restricciones de órdenes, indicarlo.

## Ejercicio 1
Utilizamos un único AVL parametrizado por tipo, instanciado para monedas y pinturas. Siendo K la cantidad de piezas registradas en la colección:
- ALTA: O(log K) en el peor caso. Recorre un camino del árbol para insertar y actualiza las alturas y el balance al regresar. Como el AVL mantiene altura O(log K) y cada rotación cuesta O(1), se cumple el orden.
- BUSCAR: O(log K) en el peor caso. En cada paso continúa por un único subárbol, recorriendo como máximo la altura del AVL.
- RANGO: O(log K + R) en el peor caso. Realiza un recorrido en orden, descartando los subárboles que quedan fuera del intervalo. Visita los R elementos reportados y, adicionalmente, los caminos que delimitan el rango, de longitud O(log K).

## Ejercicio 2
Utilizamos una tabla de hash abierta con encadenamiento, donde cada nodo representa un cajón y guarda un arreglo de frecuencias de las 26 letras y la cantidad de palabras registradas que lo utilizan.
- Registrar y consultar: O(L) promedio. Construir el arreglo de frecuencias requiere O(L). Calcular el hash y comparar dos claves cuesta O(1), porque se recorren como máximo 26 posiciones. Con una distribución adecuada del hash y un factor de carga sano, recorrer el bucket cuesta O(1) promedio. Las palabras del mismo cajón se cuentan en un único nodo, por lo que no es necesario recorrerlas.
- Factor de carga: reservamos N buckets y almacenamos como máximo N cajones distintos, por lo que el factor de carga es como máximo 1. Así, usamos espacio O(N) sin necesitar rehash.
- Última línea: O(1) en el peor caso. Mantenemos actualizados cantCajones y max con O(1) adicional por registro y consultamos ambos directamente al finalizar.
- Tiempo total: O(tamaño total de la entrada) promedio, ya que cada palabra se procesa en O(L) promedio y la tabla se inicializa en O(N).

## Ejercicio 3
Utilizamos un min-heap binario sobre un arreglo, que permite obtener los dos archivos más pequeños en cada consolidación.
- Tiempo: O(N log N) en el peor caso. Insertamos inicialmente N archivos, cada uno en O(log N). Luego realizamos N − 1 consolidaciones, cada una con dos eliminaciones del mínimo y una inserción, todas en O(log N), porque flotar y hundir recorren como máximo la altura del heap. Consultar el tope y sumar los costos cuesta O(1).
- Espacio: O(N). El arreglo del heap tiene capacidad para N elementos y la cantidad de archivos disponibles disminuye con cada consolidación. La recursión de flotar y hundir ocupa O(log N) adicional, por lo que el espacio total sigue siendo O(N).
- Utilizamos long long para los tamaños y el costo acumulado, ya que pueden superar el rango de un entero de 32 bits.
## Ejercicio 4
Utilizamos el algoritmo de Kahn con listas de adyacencia y un min-heap binario, que selecciona el módulo listo de menor prioridad y, en caso de empate, el de menor número.
- Tiempo: O((V + A) log V) en el peor caso. Construir las listas de adyacencia y calcular los grados de entrada cuesta O(V + A). Cada módulo se inserta y se elimina del heap como máximo una vez, con costo O(log V) por operación. Además, cada dependencia se recorre como máximo una vez para actualizar los pendientes, en O(A). En total, obtenemos O(V log V + A), que cumple la cota exigida.
- Espacio: O(V + A). Las listas de adyacencia almacenan V cabeceras y A nodos. Los arreglos de prioridades, pendientes y orden, junto con el heap, ocupan O(V).
## Ejercicio 5
tilizamos Kruskal con conjuntos disjuntos (MFset), con compresión de caminos y unión por altura.
- Tiempo: O(E log E) en el peor caso. Si E < V − 1, respondemos “imposible” en O(1). En caso contrario, V ≤ E + 1, por lo que inicializar el MFset cuesta O(E). Ordenar los senderos cuesta O(E log E), y procesarlos con las optimizaciones del MFset no supera esa cota.
- Espacio: O(V + E). Guardamos E senderos y dos vectores de tamaño V + 1 para los padres y las alturas.
- Utilizamos long long para el costo total, porque puede superar el rango de un entero de 32 bits.

