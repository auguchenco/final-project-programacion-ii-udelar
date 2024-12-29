/* 1234567 */
/*
  Módulo de implementación de `TPalabras'.

  Se implementa struct _rep_palabras con un árbol binario con semántica
  primer hijo - siguiente hermano.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/palabras.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

struct _rep_palabras {
  char letra;
  TPalabras primerHijo, sigHermano;
};

TPalabras crearPalabras() {
  TPalabras nuevo = new _rep_palabras;
  nuevo->letra = '~';
  nuevo->sigHermano = NULL;
  nuevo->primerHijo = NULL;
  return nuevo;
}

void liberarPalabras(TPalabras pals) {
  if (pals != NULL) {
    liberarPalabras(pals->sigHermano);
    liberarPalabras(pals->primerHijo);
    delete pals;
  }
}

char letra(TPalabras pals) { return pals->letra; }

TPalabras subarboles(TPalabras pals) { return pals->primerHijo; }

TPalabras siguientes(TPalabras pals) { return pals->sigHermano; }

TPalabras palabra_a_arbol(ArregloChars palabra) {
  TPalabras res = crearPalabras();
  _rep_palabras *cursor = res;
  // <= en vez de < para incluir el '\0'
  for (size_t i = 0; i <= strlen(palabra); i++) {
    cursor->primerHijo = new _rep_palabras;
    cursor = cursor->primerHijo;
    cursor->letra = palabra[i];
    cursor->sigHermano = NULL;
  }
  assert(cursor->letra == '\0');
  cursor->primerHijo = NULL;
  return res;
}

/*
  Inserta el árbol 'arbolPalabra' en la lista de árboles 'listaArboles'.
 */
static TPalabras ins_en_listaArboles(TPalabras arbolPalabra,
                                     TPalabras listaArboles) {
  if ((listaArboles == NULL) || (arbolPalabra->letra < listaArboles->letra)) {
    arbolPalabra->sigHermano = listaArboles;
    listaArboles = arbolPalabra;
  } else if (arbolPalabra->letra > listaArboles->letra) {
    listaArboles->sigHermano =
        ins_en_listaArboles(arbolPalabra, listaArboles->sigHermano);
  } else {
    _rep_palabras *aborrar = arbolPalabra;
    arbolPalabra = arbolPalabra->primerHijo;
    delete aborrar;
    if (arbolPalabra != NULL)
      listaArboles->primerHijo =
          ins_en_listaArboles(arbolPalabra, listaArboles->primerHijo);
    // podría ser a == NULL si la palabra ya estaba
    // en b
  }
  return listaArboles;
}

TPalabras insertarPalabra(char *palabra, TPalabras pals) {
  return ins_en_listaArboles(palabra_a_arbol(palabra), pals);
}

void imprimirPalabras(ArregloChars prefijo, nat largo, TPalabras secuencia) {
  if (secuencia->letra == '\0') {
    prefijo[largo] = '\0';
    printf("%s\n", prefijo);
  } else {
    prefijo[largo] = secuencia->letra;
    imprimirPalabras(prefijo, largo + 1, secuencia->primerHijo);
  }
  if (secuencia->sigHermano != NULL)
    imprimirPalabras(prefijo, largo, secuencia->sigHermano);
}
