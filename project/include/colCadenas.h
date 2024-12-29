/*
  Módulo de definición de 'TColCadenas'.

  Un elemento de tipo 'TColCadenas' es una colección acotada de 'TCadena's.
  La cantidad de cadenas es un parámetro pasado al crear la colección.
  En esta descripción 'tamanio' denota esa cantidad.

  Cada cadena se identifica con una posición entre 0 y 'tamanio' - 1.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COL_CADENAS_H
#define _COL_CADENAS_H

#include "cadena.h"
#include "info.h"

// Representación de 'TColCadenas'.
// Se debe definir en 'colCadenas.cpp'.
// struct _rep_colCadenas;
// Declaración del tipo 'TColCadenas'
typedef struct _rep_colCadenas *TColCadenas;

/*
  Devuelve una colección de 'tamanio' cadenas vacías.
  El tiempo de ejecución debe ser O(tamanio).
 */
TColCadenas crearColCadenas(nat tamanio);

/*
  Libera la memoria asignada a 'col' y todos sus elementos.
 */
void liberarColCadenas(TColCadenas col);

/* ++++++++++++++++++++++ NUEVA ++++++++++++++++++++ */
/*
  Devuelve la cantidad de cadenas de 'col'.
  El tiempo de ejecución debe ser O(1).
 */
nat tamanioColCadenas(TColCadenas col);

/*
  Devuelve la TCadena de 'col' identificada con 'pos'.
  La TCadena resultado comparte memoria con 'col'.
  Precondición: 0 <= pos < 'tamanio'.
  El tiempo de ejecución debe ser O(1).
 */
TCadena cadenaDeColCadenas(nat pos, TColCadenas col);

/*
  Devuelve la cantidad de elementos de la TCadena de 'col' identificada con
  'pos'.
  Precondición: 0 <= pos < 'tamanio'.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  la TCadena de 'col' identificada con 'pos'.
 */
nat cantidadColCadenas(nat pos, TColCadenas col);

/*
  Devuelve 'true' si y solo si 'natural' es el componente natural de algún
  elemento de la cadena de 'col' identificada con 'pos'.
  Precondición: 0 <= pos < 'tamanio'.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  la TCadena de 'col' identificada con 'pos'.
 */
bool estaEnColCadenas(nat natural, nat pos, TColCadenas col);

/*
  Inserta al inicio de la TCadena de 'col' identificada con 'pos'
  un elemento cuyos componentes son 'natural' y 'real'.
  Los demás elementos de 'cad' mantienen su orden relativo.
  Devuelve col.
  Precondición: 0 <= pos < 'tamanio'.
  El tiempo de ejecución debe ser O(1).
 */
TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,
                                 TColCadenas col);

/*
  Devuelve el primer elemento (el más cercano al inicio) de la TCadena de 'col'
  identificada con 'pos' cuyo componenete natural es 'natural'.
  Precondición: estaEnColCadenas(natural, pos, col)
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  la TCadena de 'col' identificada con 'pos'.
 */
TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col);

/*
  Remueve el primer elemento (el más cercano al inicio) de la TCadena de 'col'
  identificada con 'pos' cuyo componenete natural es ' natural'.
  Los demás elementos de 'cad' mantienen su orden relativo.
  Devuelve col.
  Precondición: estaEnColCadenas(natural, pos, col).
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  la TCadena de 'col' identificada con 'pos'.
 */
TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col);

#endif
