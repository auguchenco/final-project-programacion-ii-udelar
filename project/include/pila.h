/*
  Módulo de definición de 'TPila'.

  Los elementos de tipo TPila son pilas de elementos de tipo TInfo.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#include "info.h"

// Representación de 'TPila'.
// Se debe definir en pila.cpp.
// struct _rep_pila;
// Declaración del tipo 'TPila'
typedef struct _rep_pila *TPila;

/*
  Devuelve una TPila vacía (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TPila crearPila();

/*
  Libera la memoria asignada a 'p' y la de todos sus elementos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'p'.
 */
void liberarPila(TPila p);

/*
  Devuelve la cantidad de elementos de 'p'.
  El tiempo de ejecución debe ser O(1).
 */
nat cantidadEnPila(TPila p);

/*
  Apila 'info' en 'p'-
  Devuelve 'p'.
  La TPila resultado no comparte memoria con 'info'.
  El tiempo de ejecución debe ser O(1).
 */
TPila apilar(TInfo info, TPila p);

/*
  Devuelve el elemento más nuevo en 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TInfo cima(TPila p);

/*
  Remueve de 'p' su elemento más nuevo.
  Se libera la memoria asignada al mismo.
  Devuelve 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TPila desapilar(TPila p);

#endif
