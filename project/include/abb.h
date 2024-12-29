/*
  Módulo de definición de 'TAbb'.

  Los elementos de tipo 'TAbb' son árboles binarios de búsqueda de
  elementos de tipo 'TInfo'.

  La propiedad de orden de los árboles es definida por el componente
  natural de sus elementos. O sea, para cada nodo, el componente natural
  del elemento contenido en él es mayor que el componente natural de los
  elementos contenidos en los nodos de su subárbol izquierdo y menor que
  el componente natural de los elementos contenidos en los nodos de su
  subárbol derecho.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _ABB_H
#define _ABB_H

#include "info.h"

// Representación de 'TAbb'.
// Se debe definir en abb.cpp.
// struct _rep_abb;
// Declaración del tipo 'TAbb'
typedef struct _rep_abb *TAbb;

/*-----------   NUEVA ---------------  */
/*
  Aplica la rotación descrita en tipo[0] y tipo[1] en el nodo de 'abb' cuyo
  componente natural es 'clave'.
  Las rotaciones son las de los árboles AVL, aunque 'abb' no necesariamente
  cumple la propiedad de estructura de esos árboles (puede cumplirla o no).
  El nodo en el que se pretende hacer la rotación no necesariamente está
  desbalanceado.
  La rotación propuesta no necesariamente mejoraría el balance en el nodo.

  El valor de 'tipo' describe el camino que seguiría la inserción en un AVL
  si la rotación fuera consecuencia de un desbalance producido por esa
  inserción. Por ejemplo tipo[0] = 'L' y tipo[1] = 'R' significa que la
  inserción se habría hecho en el subárbol izquierdo del nodo en el que se
  aplica la rotación, y a su vez en el subárbol derecho del hijo izquierdo de
  ese nodo.

  Devuelve 'abb'.
  Si 'clave' no es nodo de 'abb' o la rotación no se puede aplicar la operación
  no tiene efecto.
  Precondición: el valor tanto de tipo[0] como de tipo[1] es 'L' o 'R'.
  El tiempo de ejecución debe ser O(h), siendo 'h' la altura de 'abb'.
 */
TAbb rotar(nat clave, char tipo[2], TAbb abb);

/*
  Devuelve un 'TAbb' vacío (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TAbb crearAbb();

/*
  Libera la memoria asociada a 'abb' y todos sus elementos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'abb'.
 */
void liberarAbb(TAbb abb);

/*
  Devuelve 'true' si y solo si 'abb' es vacío (no tiene elementos).
  El tiempo de ejecución debe ser O(1).
 */
bool esVacioAbb(TAbb abb);

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo
  componente natural es 'clave'.
  Si 'clave' no pertenece a 'abb', devuelve el árbol vacío.
  El tiempo de ejecución debe ser O(h), siendo 'h' la altura de 'abb'.
 */
TAbb buscarSubarbol(nat clave, TAbb abb);

/*
  Devuelve el elemento contenido en la raíz de 'abb'.
  Precondición: ! esVacioAbb(abb).
  El tiempo de ejecución debe ser O(1).
 */
TInfo raiz(TAbb abb);

/*
  Devuelve el subárbol izquierdo de 'abb'.
  Precondición: ! esVacioAbb(abb).
  El tiempo de ejecución debe ser O(1).
 */
TAbb izquierdo(TAbb abb);

/*
  Devuelve el subárbol derecho de 'abb'.
  Precondición: ! esVacioAbb(abb).
  El tiempo de ejecución debe ser O(1).
 */
TAbb derecho(TAbb abb);

/*
  Devuelve el elemento menor (según la propiedad de orden definida) de 'abb'.
  Precondición: ! esVacioAbb(abb).
  El tiempo de ejecución debe ser O(h), siendo 'h' la altura de 'abb'.
 */
TInfo menorEnAbb(TAbb abb);

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de 'abb'.
  Precondición: ! esVacioAbb(abb).
  El tiempo de ejecución debe ser O(h), siendo 'h' la altura de 'abb'.
 */
TInfo mayorEnAbb(TAbb abb);

/*
  Devuelve un 'TAbb' con 'dato' en su raíz y subárboles izquierdo y
  derecho son 'izq' y 'der' respectivamente.
  El resulrado comparte memoria con los parámetros.
  Precondiciones:
    - esVacioAbb(izq) || (natInfo(mayorEnAbb(izq)) < natInfo(dato))
    - esVacioAbb(der) || (natInfo(menorEnAbb(der)) > natInfo(dato))
  El tiempo de ejecución debe ser O(1).
 */
TAbb consAbb(TInfo dato, TAbb izq, TAbb der);

/*
  Inserta 'dato' en 'abb' respetando la propiedad de orden definida.
  Devuelve 'abb'.
  Precondición: esVacioAbb(buscarSubarbol(natInfo(dato), abb))
  El tiempo de ejecución debe ser O(h), siendo 'h' la altura de 'abb'.
 */
TAbb insertarEnAbb(TInfo dato, TAbb abb);

/*
  Remueve de 'abb' el nodo que contiene el elemento cuyo componente natural
  es 'clave'.
  Libera la memoria del nodo y del elemento.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución
  del elemento removido debe quedar el que es el mayor (segun la propiedad
  de orden definida) en el subárbol izquierdo.
  Devuelve 'abb'.
  Precondición: ! esVacioAbb(buscarSubarbol(clave, abb))
  El tiempo de ejecución debe ser O(h), siendo 'h' la altura de 'abb'.
 */
TAbb removerDeAbb(nat clave, TAbb abb);

/*
  Devuelve una copia de 'abb'.
  El resultado NO comparte memoria con el parámetro.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'abb'.
 */
TAbb copiaAbb(TAbb abb);

#endif
