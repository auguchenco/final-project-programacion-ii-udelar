/*
  Módulo de definición de 'TIterador'.

  Los elementos de tipo 'TIterador' son estructuras para recorrer colecciones
  lineales de elementos de tipo 'nat'.
  Tiene implícita una posición actual.

  La posición actual no está definida si la colección es vacía o si se avanza
  cuando la posición  es la última.

  El valor de una variable de tipo 'TIterador' no cambia una vez que es
  asignada. Esto significa, dado que son punteros, que la dirección de memoria a
  la que apuntan no cambia. Sí puede cambiar el contenido de esa dirección.

  Seudocódigo de una recorrida de un iterador:
  reiniciar
  mientras la posición actual está definida
    procesar el elemento definido por la posición actual
    avanzar

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _TIterador_H
#define _TIterador_H

#include "utils.h"

// Representación de 'TIterador',
// Se debe definir en iterador.cpp
// struct _rep_iterador;
// Declaración del tipo 'TIterador'
typedef struct _rep_iterador *TIterador;

/*
  Devuelve un 'TIterador' vacío (sin elementos) cuya posición actual no está
  definida.
  El tiempo de ejecución debe ser O(1).
 */
TIterador crearIterador();

/*
  Libera la memoria asignada a 'iter'.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'iter'.
 */
void liberarIterador(TIterador iter);

/*
  Devuelve 'true' si y solo si la posición actual de 'iter' está definida.
  El tiempo de ejecución debe ser O(1).
 */
bool estaDefinidaActual(TIterador iter);

/*
  Agrega 'elem' al final de 'iter'.
  La posición actual no se modifica.
  No se modifica el valor (dirección de memoria) de la variable 'iter'.
  El tiempo de ejecución debe ser O(1).
 */
void agregarAIterador(nat elem, TIterador const iter);

/*
  Mueve la posición actual de 'iter' al primero si y solo si 'iter' tiene
  elementos.
  No se modifica el valor (dirección de memoria) de la variable 'iter'.
  El tiempo de ejecución debe ser O(1).
 */
void reiniciarIterador(TIterador const iter);

/*
  Avanza la posición actual de 'iter' hacia el siguiente si
  estaDefinidaActual(iter).
  En otro caso no tiene efecto.
  Si la posición actual es la última posición entonces la posición actual
  queda indefinida.
  No se modifica el valor (dirección de memoria) de la variable 'iter'.
  El tiempo de ejecución debe ser O(1).
 */
void avanzarIterador(TIterador const iter);

/*
  Devuelve el elemento de la posición actual de 'iter'.
  Precondición: estaDefinidaActual(iter).
  El tiempo de ejecución debe ser O(1).
 */
nat actualEnIterador(TIterador iter);

#endif
