/*
  Módulo de definición de 'aplicaciones'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _APLICACIONES_H
#define _APLICACIONES_H

#include "abb.h"
#include "cadena.h"
#include "cola.h"
#include "iterador.h"
#include "palabras.h"
#include "pila.h"

/* ++++++++++++++++++++++ NUEVAS ++++++++++++++++++++ */

/*
  Devuelve true si y solo si 'abb' cumple la propiedad de estructura de los AVL.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  nodos de 'abb'.
  Cada nodo se puede visitar una sola vez y no se deben visitar nodos si no es
  necesario..
 */
bool esAvl(TAbb abb);

/*
  Devuelve un 'TAbb' de altura 'h' con 'n' nodos, siendo 'n' la mínima cantidad
  de elementos que puede tener un árbol de altura 'h' que cumple la propiedad
  de estructura de los AVL.
  Los componentes naturales de los elementos van desde 1 hasta 'n'.
  Los componentes reales valen 0.
  En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el
  subárbol izquierdo.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución en el peor caso es O(n).
  Ver ejemplos en la letra.
 */

TAbb avlMin(nat h);

/*
  Devuelve una TCadena con un elemento por cada elemento de 'it' que sea
  componente natural de algún elemento de 'cad'.
  En la TCadena resultado, el componente natural del elemento debe ser igual al
  de 'it', y el componente real debe ser la suma de los componentes reales de
  todos los elementos de 'cad' que tengan ese mismo componente natural.
  La TCadena resultado debe estar ordenada de manera creciente estricta según
  sus componentes naturales.
  Al terminar, la posición de 'it' debe quedar no definida.
  Precondición: 'it' está ordenado de manera creciente estricta (no hay
  repetidos).
  El tiempo de ejecución debe ser O(ncad + nit) en promedio, siendo 'ncad' la
  cantidad de elementos de 'cad' y 'nit' es la cantidad de elementos de 'it'.
 */
TCadena filtradaOrdenada(TCadena cad, TIterador it);

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de manera creciente estricta
  (no hay repetidos) según los componenetes naturales.
  Si la cadena no tiene elementos o tiene solo uno está ordenada.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
bool estaOrdenada(TCadena cad);

/*
  Devuelve una TCadena con los elementos que están en 'cad1' o en 'cad2'.
  Si existe un elemento en 'cad1' con igual componente natural que uno de
  'cad2', entonces el componente real del elemento en el resultado debe ser el
  de 'cad1'.
  El resultado debe estar ordenada de manera crecietne estricta (no hay
  repetidos) según los componentes naturales.
  Precondición: 'cad1' y 'cad2' están ordenadas de esa misma manera.
  El resultado no comparte memoria con sus parámetros.
  El tiempo de ejecución debe ser O(n1 + n2), siendo 'n1' y 'n2' la cantidad de
  elementos de 'cad1' y 'cad2' respectivamente.
 */
TCadena mezclaCadenas(TCadena cad1, TCadena cad2);

/*
  Devuelve un TAbb con los elementos de 'arreglo'.
  Para cada nodo del árbol resultado se debe cumplir que la cantidad de nodos
  de sus dos subárboles es igual, o el subárbol derecho tiene un nodo más que el
  izquierdo.
  Precondición: 'arrego' tiene 'n' elementos y está ordenado de manera creciente
  estricta (no hay repetidos) según los componentes naturales.
  El resultado no comparte memoria con 'arreglo'.
  El tiempo de ejecución debe ser O(n).
 */
TAbb crearBalanceado(TInfo *arreglo, nat n);

/*
  Devuelve un TAbb con los elementos que están en 'abb1' o en 'abb2'.
  Si existe un elemento en 'abb1' con igual componente natural que uno de
  'abb2', entonces el componente real del elemento en el resultado debe ser el
  de 'abb1'.
  La altura del TAbb resultado debe ser O(log n), siendo 'n' su cantidad de
nodos.
  El resultado no comparte memoria con sus parámetros.
  El tiempo de ejecución debe ser O(n1 + n2), siendo 'n1' y 'n2' la cantidad de
  elementos de 'abb1' y 'abb2' respectivamente.
 */
TAbb unionAbbs(TAbb abb1, TAbb abb2);

/*
  Devuelve una TCola con los elementos de 'cad' ordenados de manera creciente
  según el resto de la división del componente natural por 'p'.
  En caso de igualdad en ese resto se debe mantener el orden en que estaban en
  'cad'.
  Que la TCola resultado esté ordenada de manera creciente implica que el
  componente natural del frente es menor o igual en módulo 'p' a todos los
  demás.
  Ver como se procesa el comando en principal.cpp y el resultado esperado en
  el .out.
  La TCola resultado no comparte memoria con 'cad'.
  El tiempo de ejecución debe ser O(max(n,p)), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCola ordenadaPorModulo(nat p, TCadena cad);

/*
  Devuelve una TPila con los elementos de 'cad' cuyos componentes naturales
  son menores estrictos que los de cada uno de los siguientes (hasta el
  'cantidad' de 'cad'), o sea, en el resto de la cadena no hay ningún elemento
  cuyo componente natural es menor o igual.
  En la TPila resultado los elementos deben estar en orden reverso al que
  estaban en 'cad'.
  Que la TPila resultado esté en orden reverso implica que el componente
  natural de la cima es mayor que  todos los  demás.
  Ver como se procesa el comando en principal.cpp y el resultado esperado en
  el .out.
  La TPila resultado no comparte memoria con 'cad'.
  No se debem usar estructuras auxiliares ni definir funciones auxiliares.
  Precondición: cantidadEnCadena(cad) = cantidad.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
TPila menoresQueElResto(TCadena cad, nat cantidad);

/*
  Devuelve una 'TCadena' con los elementos de 'abb' en orden creciente según
  sus componentes naturales.
  La 'TCadena' devuelta no comparte memoria con 'abb'.
  Cada elemento de 'abb' se debe visitar una sola vez.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'abb'.
 */
TCadena linealizacion(TAbb abb);

/*
  Imprime los elementos de 'abb', uno por línea, en orden descendente de la
  propiedad de orden de los árboles 'TAbb'.
  Antes del elemento imprime una cantidad de guiones igual a su profundidad.
  El elemento se imprime según la especificación dada en 'infoATexto'.
  La profundidad de la raíz es 0.
  Cada elemento de 'abb' se debe visitar una sola vez.
 */
void imprimirAbb(TAbb abb);

/*
  Devuelve 'true' si y solo si 'abb' es perfecto.
  Un árbol es perfecto si todas las hojas están en el mismo nivel y todos los
  nodos internos tienen dos subárboles no vacíos; o sea, si todos los niveles
  están completos.
  Ningún nodo debe ser visitado más de una vez.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'abb'.
 */
bool esPerfecto(TAbb abb);

/*
  Devuelve un 'TAbb' con copias de los elementos de 'abb' que cumplen la
  condición  "realInfo(elemento) < limite".
  La estructura del árbol resultado debe ser análoga a la de 'abb'. Esto
  significa que dados dos nodos 'U' y 'V' de 'abb' en los que se cumple la
  condición y tal que 'U' es ancestro de 'V', en el árbol resultado la copia de
  'U' debe ser ancestro de la copia de 'V' cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
  en el caso en el que en un nodo 'W' no se cumple la condición y en sus dos
  subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (según la propiedad de orden definida) de los que
  cumplen la condición en el subárbol izquierdo de 'W' deberá ser ancestro de
  las copias de todos los descendientes de 'W' que cumplen la condición.
  Ver ejemplos en la letra y en los casos en 'test'.
  El árbol resultado no comparte memoria con 'abb'.
  Cada elemento de 'abb' se debe visitar una sola vez.
  No se pueden crear estructuras auxiliares.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'abb'.
 */
TAbb menores(double limite, TAbb abb);

/*
  Devuelve un 'TIterador' con los hasta 'k' primeros componentes naturales de
  los elementos que están en el camino ascendente que va desde el nodo que
  contiene al elemento cuyo componente natrual es 'clave' hacia la raíz.
  Si 'k' es mayor que la cantidad de elementos en ese camino solo se incluyen
  los elementos corresponientes al camino.
  Ver ejemplos en la letra y en los casos en 'test'.
  El resultado NO comparte memoria con los parámetros.
  Precondición: ! esVacioAbb(buscarSubarbol(clave, abb)).
  Solo se puede acceder a nodos que están en el camino desde la raíz de 'abb'
  hacia el nodo que contiene al elemento cuyo componente natural es 'clave' y
  cada uno de ellos solo puede visitarse una vez .
  Poscondición: en el 'TIterador' resultado la posición debe quedar no definida.
  El tiempo de ejecución debe ser O(p), siendo 'p' la longitud del camino desde
  la raíz de 'abb' hasta el nodo cuyo componente natural es 'clave'.
 */
TIterador caminoAscendente(nat clave, nat k, TAbb abb);

/*
  Imprime las palabras representadas en el árbol 'palabras' cuyo largo es
  menor o igual a 'k'.
  Las imprime una por línea en orden lexicográfico.
  Ningún nodo debe ser visitado más de una vez.
  Precondición: k > 0.
  Ver ejemplos en la letra y en los casos de prueba.
 */
void imprimirPalabrasCortas(nat k, TPalabras palabras);

/*
  Devuelve el subárbol de 'palabras' que representa el fin (la última letra) de
  'prefijo'.
  Si 'prefijo' no está representado en 'pals' devuelve NULL.
  O sea, si 'prefijo' está en 'palabras' el nodo más profundo del camino que lo
  representa es la ráiz del subárbol resultado.
  Ningún nodo debe ser visitado más de una vez.
  El tiempo de ejecución debe ser O(n) siendo 'n' la cantidad de elementos de
  'palabras'.
  Ver ejemplos en la letra y en los casos de prueba.
 */
TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras);

/*
  Devuelve un TIterador con los mismos elementos que iter pero
  en sentido opuesto.
  El resultado no comparte memoria con el parámetro.
  Cada elemento de 'iter' solo se visita una vez.
  No se puede usar estructuras auxiliares.
  Poscondición: ! estaDefinidaActual(iter)
  (al terminar la posición actual de iter queda no definida)
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'iter'.
 */
TIterador reversoDeIterador(TIterador iter);

#endif
