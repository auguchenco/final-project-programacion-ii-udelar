/*
  Módulo de definición de 'TCadena'.

  Los elementos de tipo TCadena son colecciones lineales NO acotadas de
  elementos de tipo TInfo.
  Tienen un comportamiento circular.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CADENA_H
#define _CADENA_H

#include "info.h"

// Representación de 'TCadena'.
// Se debe definir en 'cadena.cpp'.
// struct _rep_cadena;
// Declaración del tipo 'TCadena'
typedef struct _rep_cadena *TCadena;

/*
  Inserta al final de 'cad' un elemento cuyos componentes son 'natural' y
  'real'.
  Devuelve 'cad'.
  El tiempo de ejecución debe ser O(1).
 */
TCadena insertarAlFinal(nat natural, double real, TCadena cad);

/*
  Remueve el primer elemento de 'cad'.
  Se libera la memoria asignada al mismo.
  Devuelve 'cad'.
  Precondición: cantidadEnCadena(cad) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TCadena removerPrimero(TCadena cad);

/*
  Devuelve una copia de 'cad'.
  El resultado no comparte memoria con el parámetro.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
TCadena copiaCadena(TCadena cad);

/*
  Devuelve la 'TCadena' vacía (sin elementos).
  No se debe obtener memoria.
  El tiempo de ejecución debe ser O(1).
 */
TCadena crearCadena();

/*
  Libera la memoria asignada a 'cad' y la de todos sus elementos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
void liberarCadena(TCadena cad);

/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
nat cantidadEnCadena(TCadena cad);

/*
  Devuelve 'true' si y solo si 'natural' es el componente natural de algún
  elemento de 'cad'.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
bool estaEnCadena(nat natural, TCadena cad);

/*
  Inserta al inicio de 'cad' un elemento cuyos componentes son 'natural' y
  'real'.
  Los demás elementos de 'cad' mantienen su orden relativo.
  Devuelve 'cad'.
  El tiempo de ejecución debe ser O(1).
 */
TCadena insertarAlInicio(nat natural, double real, TCadena cad);

/*
  Devuelve el primer elemento de 'cad' cuyo componente natural es 'natural'.
  Precondición: estaEnCadena(natural, cad).
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
TInfo infoCadena(nat natural, TCadena cad);

/*
  Devuelve el primer elemento de 'cad'.
  Precondición: cantidadEnCadena(cad) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TInfo primeroEnCadena(TCadena cad);

/*
  Devuelve la TCadena que tiene los mismos elementos que 'cad' y en el mismo
  orden 'circular' pero cuyo primer elemento es el siguiente al primer
  elemento de 'cad'.
  Si 'cad' no tiene elementos o tiene solo uno el resultado es 'cad'.
  La TCadena resultado comparte memoria con 'cad'. No se debe obtener nueva
  memoria.
  El parámetro 'cad' no cambia, en particular su primer elemento sigue siendo
  el mismo.
  El tiempo de ejecución debe ser O(1).

  Por ejemplo, sea la cadena
  [(7,7.00), (3,3.00), (5,5.00), (9,9.00)]
  en que su primer elemento es (7,7.00) y su último elemento es (9,9.00).

  Que el comportamiento sea circular significa que la cadena siguiente es
  [(3,3.00), (5,5.00), (9,9.00), (7,7.00)].

  El parámetro 'cad' no cambia, sigue siendo
  [(7,7.00), (3,3.00), (5,5.00), (9,9.00)].
 */
TCadena cadenaSiguiente(TCadena cad);

/*
  Remueve el primer elemento de 'cad' cuyo componente natural es 'natural'.
  Se libera la memoria asignada al mismo.
  Los demás elementos de 'cad' mantienen su orden relativo.
  Devuelve 'cad'.
  Precondición: estaEnCadena(natural, cad).
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
TCadena removerDeCadena(nat natural, TCadena cad);

/*
  Imprime los elementos de 'cad' de la siguiente forma:
  (n de pos1,r de pos1)(n de pos2,r de pos2) ...
  donce 'n' es el componente natural y 'r' es el componente real.
  Antes de terminar, se debe imprimir un fin de linea (salto de línea).
  Si cantidadEnCadena(cad) es 0 sólo se imprime el fin de línea.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'cad'.
 */
void imprimirCadena(TCadena cad);

#endif
