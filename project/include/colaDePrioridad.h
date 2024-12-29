/*
  Módulo de definición de 'TColaDePrioridad'.

  Los elementos de tipo 'TColaDePrioridad' son colas de prioridad cuyos
  elementos son de tipo 'nat' entre 1 y N, siendo N un parámetro pasado al
  crear la cola de prioridad.
  No hay elementos repetidos.
  La prioridad asociada al elemento es de tipo double y la determina un valor
  establecido al insertar el elemento. Ese valor puede ser modificado.

  El criterio para establecer la prioridad entre elementeos es, de manera
  predeterminada, que un elemento es prioritario ante otro si su valor asociado
  es menor.
  Este criterio se puede modificar, haciendo que el prioritario sea el de mayor
  valor asociado.

  Si la 'TColaDePrioridad' no es vacía hay un elemento considerado el
  prioritario, según el criterio de prioridad. Si hay más de un elemento con el
  mismo valor asociado cualquiera de ellos es el prioritario.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CP_H
#define _CP_H

#include "utils.h"

// Representación de 'TColaDePrioridad'
// Se debe definir en colaDePrioridad.cpp
// struct _rep_colaDePrioridad;
// Declaración del tipo 'TColaDePrioridad'
typedef struct _rep_colaDePrioridad *TColaDePrioridad;

/*
  Devuelve una 'TColaDePrioridad' vacía (sin elementos). Podrá contener
  elementos entre 1 y N.
  Un elemento es prioritario ante otro si su valor asociado es menor.
  El tiempo de ejecución en el peor caso es O(N).
 */
TColaDePrioridad crearCP(nat N);

/*
  Modifica el criterio de prioridad: si el prioritario era el que tenía asociado
  el menor valor pasa a ser el que tiene asociado el mayor valor, y viceversa.
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cp'.
 */
TColaDePrioridad invertirPrioridad(TColaDePrioridad cp);

/*
  Libera la menoria asignada a 'cp' y a cada uno de sus elementos.
  El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
  pasado en crearCP.
 */
void liberarCP(TColaDePrioridad cp);

/*
  Inserta 'elem' en 'cp' o, si ya estaba, actualiza su prioridad.
  La prioridad asociada a 'eĺem' queda en 'valor'.
  Si 'elem' no está en el rango 1..N no se hacen cambios.
  Devuelve 'cp'.
  No se debe dejar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(log N).
  'N' el parámetro pasado en crearCP.
 */
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp);

/*
  Devuelve 'true' si y solo si en 'cp' no hay elementos.
  El tiempo de ejecución en el peor casos es O(1).
 */
bool estaVaciaCP(TColaDePrioridad cp);

/*
  Devuelve el elemento prioritario de 'cp'.
  Precondición: !estaVaciaCP(cp).
  El tiempo de ejecución en el peor casos es O(1).
 */
nat prioritario(TColaDePrioridad cp);

/*
  Elimina de 'cp' el elemento prioritario.
  Libera la memoria asociada a ese elemento.
  Si estaVacioCP(cp) la operación no tiene efecto.
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp);

/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnCP(nat elem, TColaDePrioridad cp);

/*
  Devuelve el valor de prioridad asociado a 'elem'.
  Precondición: estaEnCp(elem, cp).
  El tiempo de ejecución en el peor caso es O(1).
 */
double prioridad(nat elem, TColaDePrioridad cp);

#endif
