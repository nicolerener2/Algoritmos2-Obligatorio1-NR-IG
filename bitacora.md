# Bitácora — Obligatorio 1

**Integrantes:** Nicole Rener (289407), Inés García (356051)

> **Instrucciones** 

## AAAA-MM-DD — Nombre
- Ejemplo: Leí la letra del ejercicio 1. Primera idea: ... pero la restricción de
  complejidad pide ..., así que ...

## 2026-09-10 — En conjunto
- Hicimos el ejercicio 1 completo. Nos fue de gran ayuda lo visto en clase. Nos costo un poco entender bien lo del template. 
- Falta hacer las pruebas.

## 2026-09-13 — En conjunto
- Hicimos el ejercicio 2 completo. Nos costo pensar como hacer para distinguir los cajones, ya que al principio pensabamos que cada bucket tenía que ser un cajón. Recién cuando entedimos que no fue que logramos pensar como hacerlo. Quisimos basarnos en lo que habiamos hecho en clase de hash cerrado, pero eso aunque un poco nos sirvió, nos terminó confundiendo al hacer las funciones ya que habiamos hecho muchas más de las que precisabamos para este ejercicio. 
- Falta hacer las pruebas.

## 2026-09-26 — Nicole
- Hice el ejercicio 3. Primero repasé el código del heap y usé una función de comparación para que funcionara como un MinHeap, porque necesitaba obtener siempre los dos archivos de menor tamaño.
- Guardé los tamaños de los archivos en el heap. Después, en cada paso, saqué los dos menores, sumé sus tamaños y volví a insertar el resultado, que representaba el nuevo archivo consolidado.
- Lo que más me costó fue darme cuenta de que no alcanzaba con ordenar los archivos una sola vez y recorrerlos. El archivo nuevo tenía que competir con los que todavía estaban disponibles, por lo que debía volver al heap para elegir nuevamente los dos más chicos.
- También tuve que distinguir entre el tamaño del archivo final y el costo total. Fui sumando el costo de cada consolidación en costoTotal, porque el contenido de un archivo podía copiarse varias veces al participar en distintas consolidaciones.
- Por último, repetí el proceso mientras quedaran al menos dos archivos y usé long long tanto para los tamaños como para el costo acumulado. También tuve en cuenta el caso de un único archivo, donde el resultado es 0 porque no se realiza ninguna consolidación.
- Falta hacer las pruebas.

## 2026-10-10 — Inés
- Hice el ejercicio 4. Primero estuve viendo el código de MaxHeap de las diapositivas de clase, ya que necesitaba adaptarlo a un MinHeap. Después repasé los ejercicios anteriores y me di cuenta de que el código del ejercicio 3 me servía mucho más, porque ya tenía una función para comparar los elementos. Entonces decidí basarme en ese.
- Después tuve que pensar cómo guardar las dependencias entre los módulos. Se me ocurrió usar listas de adyacencia con punteros, donde cada módulo tuviera una lista de los que dependían de él.
- También tuve que tener en cuenta que en el heap solo podían estar los módulos listos para compilarse. Lo que más me costó fue darme cuenta de cómo saber cuándo un módulo quedaba listo. Para eso usé un arreglo que contara las dependencias pendientes de cada uno, y cada vez que se compilaba un módulo, se les restaba una dependencia a los que lo estaban esperando.
- Por último, fui guardando el orden de compilación en un arreglo y usé una variable para contar cuántos módulos se habían compilado. Así, si al terminar esa cantidad era menor que el total de módulos, podía saber que había un ciclo e imprimir `imposible`.

## 2026-10-17 — Nicole
- Hice el ejercicio 5. Primero repasé cómo funcionaba Kruskal, porque tenía que conectar todos los refugios con el menor costo posible. Guardé los senderos en un vector y los ordené de menor a mayor costo usando una función para compararlos.
- Después implementé la estructura de conjuntos disjuntos con un vector de padres y otro de alturas. En find usé compresión de caminos y en merge unión por altura, para colgar siempre el árbol más bajo del más alto.
- Fui recorriendo los senderos ordenados y, cuando sus extremos pertenecían a conjuntos distintos, los unía y sumaba el costo. Si ya estaban en el mismo conjunto, descartaba el sendero porque formaría un ciclo.
- Usé m para contar cuántos iba agregando. Si al terminar tenía V - 1, todos los refugios estaban conectados; si no, imprimía “imposible”.
- Por último, usé long long para el costo total, porque la suma podía superar el rango de un int. También tuve en cuenta el caso de un solo refugio, donde el resultado es 0 porque no hace falta mantener ningún sendero.