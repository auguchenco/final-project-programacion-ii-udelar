/*
  Módulo de definición de 'TCola'.

  Los elementos de tipo TCola son colas de elementos de tipo TInfo.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_H
#define _COLA_H

#include "info.h"

// Representación de 'TCola'.
// Se debe definir en cola.cpp.
// struct _rep_cola;
// Declaración del tipo 'TCola'
typedef struct _rep_cola *TCola;

/*
  Devuelve una TCola vacía (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TCola crearCola();

/*
  Libera la memoria asignada a 'c' y la de todos sus elementos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'c'.
 */
void liberarCola(TCola c);

/*
  Devuelve la cantidad de elementos de 'c'.
  El tiempo de ejecución debe ser O(1).
 */
nat cantidadEnCola(TCola c);

/*
  Encola 'info' en 'c'-
  Devuelve 'c'.
  La TCola resultado no comparte memoria con 'info'.
  El tiempo de ejecución debe ser O(1).
 */
TCola encolar(TInfo info, TCola c);

/*
  Devuelve el elemento más antiguo en 'c'.
  Precondición: cantidadEnCola(c) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TInfo frente(TCola c);

/*
  Remueve de 'c' su elemento más antiguo.
  Se libera la memoria asignada al mismo.
  Devuelve 'c'.
  Precondición: cantidadEnCola(c) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TCola desencolar(TCola c);

#endif
