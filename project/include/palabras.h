/*
  Módulo de definición de 'TPalabras'.

  Ver Ejercicio 9 del Práctico 4.

  Se implementa en palabras.cpp como árbol binario con semántica primer hijo,
  siguiente hermano:

struct _rep_palabras {
  char letra;
  TPalabras primerHijo, sigHermano;
}

  'TPalabras' representa árboles y secuencias de árboles cuyos nodos contienen
  letras (elementos de tipo char).

  - Considerado como árbol, 'letra' es el contenido del nodo y mediante
  'primerHijo' se accede al primero de la secuencia de los subárboles del nodo.

  - Considerado como secuencia de árboles, mediante 'sigHermano' se accede al
  siguiente en la secuencia de subárboles del mismo padre.

  En este módulo se usa para mantener conjuntos de palabras.
  La concatenación de letras en el camino desde la raíz hasta una hoja es una
  palabra del conjunto.
  La letra que está en la raíz no se considera parte de la palabra.
  La letra de la hoja no se considera parte de la palabra (es '\0').

  Un prefijo está contenido en el árbol si es la concatenación de letras en el
  camino desde la raíz hasta cualquier nodo que no sea hoja.
  El último nodo del camino contiene la última letra del prefijo.
  La letra que está en la raíz no se considera parte del prefijo.

  Las secuencias de subárboles están ordenada de manera creciente según la letra
  del nodo. La letra en las hojas es menor que cualquier otra letra (o sea
  '\0' < letra, para cualquier letra de alguna palabra).
  El siguiente hermano del último nodo de una secuencia es NULL.
  Se debe notar que el siguiente hermano de una hoja puede no ser NULL.

  El tipo ArregloChars está definido en utils.h y es un alias de char *.
  Los parámetros de tipo ArregloChars siguen el comportamiento de la biblioteca
  string.h de C, con '\0' como terminador de string. La longitud del
  string se calcula mediante strlen(string). El string está contenido en e
l
  arreglo entre las posiciones 0, incluida, y strlen(string), NO incluída.



  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PALABRAS_H
#define _PALABRAS_H

#include "utils.h"

// Representación de 'TPalabras'.
// Se debe definir en palabras.cpp.
// struct _rep_palabras;
// Declaración del tipo 'TPalabras'
typedef struct _rep_palabras *TPalabras;

/*
  Devuelve un 'TPalabras' vacío (sin letras).
  Es una celda cuya letra no pertenece al alfabeto.
 */
TPalabras crearPalabras();

/*
  Libera la memoria asignada a 'palabras',
 */
void liberarPalabras(TPalabras palabras);

/*
  Devuelve la letra contenida en el nodo apuntado por 'palabras'
  (palabras->letra).
  Precondición: palabras != NULL.
 */
char letra(TPalabras palabras);

/*
  Devuelve la secuencia de subárboles "hijos" del nodo apuntado por 'palabras'
  (palabras->primerHijo).
  Precondición: palabras != NULL.
 */
TPalabras subarboles(TPalabras palabras);

/*
  Devuelve la secuencia de árboles que sigue al nodo apuntado por 'palabras'.
  (palabras->sigHermano).
  Precondición: palabras != NULL.
 */
TPalabras siguientes(TPalabras palabras);

/*
  Inserta 'palabra' en 'palabras'.
  Si 'palabra' ya estaba en 'palabras' la operación no tiene efecto.
  Devuelve 'palabras'.
 */
TPalabras insertarPalabra(ArregloChars palabra, TPalabras palabras);

/*
  Devuelve el árbol de palabras con 'palabra' como única palabra.
  Es usada en la implementación de 'insertarPalabra' y puede ser usada como
  función auxiliar.
  Se debe notar que el resultado también puede ser interpretado como una lista
  de letras encadenadas mediante los punteros 'primerHijo'.
 */
TPalabras palabra_a_arbol(ArregloChars palabra);

/*
  Para cada camino hacia una hoja de cada árbol de 'secuencia' imprime la
  concatenación de un prefijo dado y las letras del camino (sin incluir el '\0'
  de la hoja).
  Los imprime una por línea en orden lexicográfico.
  El prefijo está definido en prefijo[0 .. largo -1].
  Se debe notar que en este caso el parámetro de tipo TPalabras es considerado
  como una secuencia de árboles.

  Es usada en 'principal.cpp' para probar 'buscarFinPrefijo'.
 */
void imprimirPalabras(ArregloChars prefijo, nat largo, TPalabras secuencia);

#endif
