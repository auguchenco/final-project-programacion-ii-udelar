/*
  Módulo de definición de 'TMapping'.

  Los elementos de tipo 'TMapping' son mappings cuyos elementos son
  asociaciones de 'nat' a 'double'.
  Puede haber hasta M asociaciones, siendo M un parámetro pasado al crear
  el 'TMapping'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _MAP_H
#define _MAP_H

#include "utils.h"

// Representación de 'TMapping'.
// Se debe definir en mapping.cpp.
// struct _rep_mapping;
// Declaración del tipo 'TMapping'.
typedef struct _rep_mapping *TMapping;

/*
  Crea un 'TMapping' vacío (sin elementos) de asociaciones nat -> double.
  Podrá haber hasta M asociaciones.
  Precondición: M > 0.
  El tiempo de ejecución en el peor caso es O(M).
 */
TMapping crearMap(nat M);

/*
  Libera la memoria asignada a 'map' y todos sus elementos.
  El tiempo de ejecución en el peor caso es O(M), siendo 'M' el parámetro
  pasado en crearMap.
 */
void liberarMap(TMapping map);

/*
  Inserta en 'map' la asociación entre 'clave' y 'valor'.
  Precondición: !estaLlenoMap(map) y !esClaveEnMap(clave, map).
  Devuelve 'map'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TMapping asociarEnMap(nat clave, double valor, TMapping map);

/*
  Elimina de 'map' la asociación correspondiente a 'clave' y libera la
  memoria  asignada a mantener esa asociación.
  Precondición: esClaveEnMap(clave, h).
  Devuelve 'map'.
  El 'TMapping' resultado comparte memoria con el parámetro'.
  El tiempo de ejecución es O(1) en promedio.
 */
TMapping desasociarEnMap(nat clave, TMapping map);

/*
  Devuelve 'true' si y solo si en 'map' hay una asociación correspondiente
  a 'clave'.
  El tiempo de ejecución es O(1) en promedio.
 */
bool esClaveEnMap(nat clave, TMapping map);

/*
  Devuelve el valor correspondiente a la asociacion de 'clave' en 'h'.
  Precondición: esClaveEnMap(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
double valorEnMap(nat clave, TMapping map);

/*
  Devuelve 'true' si y solo si 'map' tiene 'M' elementos, siendo 'M' el
  parámetro pasado en crearMap.
  El tiempo de ejecución es O(1).
 */
bool estaLlenoMap(TMapping map);

#endif
