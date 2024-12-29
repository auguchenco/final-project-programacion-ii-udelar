/*
  Módulo principal de la tarea 6.

Intérprete de comandos para probar los módulos.

Están creados una TCadena 'cad', una TColCadenas 'colCads', un TIterador 'iter'
, un TAbb 'abb', una TPila 'pila', uno TCola 'cola', un TMapping 'map', un
TPalabras 'palabras' y una TColaDePrioridad 'cp'.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo TInfo su formato cumple con lo descrito en
'infoATexto' del módulo 'info''.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciarEstructuras
libera la memoria asignada a 'cad', 'colCads', 'iter', 'abb', 'palabras',
'pila', 'cola' y los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/abb.h"
#include "include/aplicaciones.h"
#include "include/cadena.h"
#include "include/colCadenas.h"
#include "include/cola.h"
#include "include/colaDePrioridad.h"
#include "include/info.h"
#include "include/iterador.h"
#include "include/mapping.h"
#include "include/palabras.h"
#include "include/pila.h"
#include "include/utils.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256

#define MAX_CP 10
#define MAX_MAP 10
#define TAM_COL_CAD 10

/*
  Lee y devuelve una TCadena desde la entrada estándar.
  Se asume que en la entrada hay un espacio en blanco después de cada elemento.
 */
TCadena leerCadena() {
  nat n = leerNat();
  TCadena res = crearCadena();
  for (nat i = 1; i <= n; i++) {
    TInfo info = leerInfo();
    res = insertarAlFinal(natInfo(info), realInfo(info), res);
    liberarInfo(info);
  }
  return res;
} // leerCadena

TInfo *leerArregloInfos(nat n) {
  TInfo *res = new TInfo[n];
  if (n > 0) {
    res[0] = leerInfo();
    for (nat i = 1; i < n; i++) {
      TInfo info = leerInfo();
      assert(natInfo(info) > natInfo(res[i - 1]));
      res[i] = info;
    }
  }
  return res;
} // leerArregloInfos

TAbb leerAbb() {
  TCadena cad = leerCadena();
  TAbb res = crearAbb();
  TCadena sig = cad;
  for (nat i = 1, cant = cantidadEnCadena(cad); i <= cant;
       i++, sig = cadenaSiguiente(sig)) {
    res = insertarEnAbb(copiaInfo(primeroEnCadena(sig)), res);
  }
  liberarCadena(cad);
  return res;
} // leerAbb

// inserta en 'pal' las palabras de longitud entre 'pos' y 'limite' formadas por
// las letras {'a', ..., 'd'} que tienen como prefijo prefijo[0 .. pos - 1].
TPalabras poblarVocabulario(ArregloChars prefijo, nat pos, nat limite,
                            TPalabras pal) {
  assert(pos <= limite);
  assert(prefijo[pos] == '\0');
  pal = insertarPalabra(prefijo, pal);
  if (pos < limite) {
    for (char letra = 'a'; letra <= 'd'; letra++) {
      prefijo[pos] = letra;
      prefijo[pos + 1] = '\0';
      poblarVocabulario(prefijo, pos + 1, limite, pal);
    }
  }
  return pal;
} // crearVocabulario

// Devuelve un iterador ordenado de manera creciente
TIterador leerIteradorOrdenado() {
  TIterador res = crearIterador();
  int primero;
  scanf("%d", &primero);
  if (primero >= 0) {
    nat actual = primero;
    agregarAIterador(actual, res);
    nat ultimo = actual;
    actual = leerNat();
    while (actual > ultimo) {
      agregarAIterador(actual, res);
      ultimo = actual;
      actual = leerNat();
    }
  }
  reiniciarIterador(res);
  return res;
} // leerIteradorOrdenado

// programa principal
int main() {

  TColaDePrioridad cp = crearCP(MAX_CP);
  TMapping map = crearMap(MAX_MAP);
  TCola cola = crearCola();
  TPila pila = crearPila();
  TPalabras palabras = crearPalabras();
  TAbb abb = crearAbb();
  TIterador iter = crearIterador();
  TColCadenas colCads = crearColCadenas(TAM_COL_CAD);
  TCadena cad = crearCadena();

  char restoLinea[MAX_LINEA + 1];
  char nom_comando[MAX_PALABRA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    leerChars(nom_comando);

    // procesar el comando
    if (0 == strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (0 == strcmp(nom_comando, "#")) {
      leerRestoLinea(restoLinea);
      printf("# %s.\n", restoLinea);

      // operaciones de cp

    } else if (0 == strcmp(nom_comando, "invertirPrioridad")) {
      cp = invertirPrioridad(cp);
      printf("Se cambió el criterio de prioridad.\n");

    } else if (0 == strcmp(nom_comando, "insertarEnCP")) {
      nat elem = leerNat();
      double valor = leerDouble();
      cp = insertarEnCP(elem, valor, cp);
      printf("Se intenta insertar %u con prioridad %.2lf.\n", elem, valor);

    } else if (0 == strcmp(nom_comando, "eliminarPrioritario")) {
      cp = eliminarPrioritario(cp);
      printf("Se intenta eliminar el prioritario.\n");

    } else if (0 == strcmp(nom_comando, "prioritario")) {
      assert(!estaVaciaCP(cp));
      printf("El prioritario es %d\n", prioritario(cp));

    } else if (0 == strcmp(nom_comando, "estaVaciaCP")) {
      printf("La cp está %s.\n", estaVaciaCP(cp) ? "vacia" : "no vacía");

    } else if (0 == strcmp(nom_comando, "estaEnCP")) {
      nat elem = leerNat();
      printf("En la cp %s %u.\n", estaEnCP(elem, cp) ? "está" : "no está",
             elem);

    } else if (0 == strcmp(nom_comando, "prioridad")) {
      nat elem = leerNat();
      assert(estaEnCP(elem, cp));
      printf("La prioridad de %u es %.2lf.\n", elem, prioridad(elem, cp));

      // operaciones de map
    } else if (0 == strcmp(nom_comando, "asociarEnMap")) {
      assert(!estaLlenoMap(map));
      nat clave = leerNat();
      double valor = leerDouble();
      assert(!esClaveEnMap(clave, map));
      map = asociarEnMap(clave, valor, map);
      printf("Establecida la asociación.\n");

    } else if (0 == strcmp(nom_comando, "desasociarEnMap")) {
      nat clave = leerNat();
      assert(esClaveEnMap(clave, map));
      map = desasociarEnMap(clave, map);
      printf("Eliminada la asociación.\n");

    } else if (0 == strcmp(nom_comando, "esClaveEnMap")) {
      nat clave = leerNat();
      printf("%s.\n", esClaveEnMap(clave, map) ? "Existe asociacion"
                                               : "No existe asociacion");

    } else if (0 == strcmp(nom_comando, "valorEnMap")) {
      nat clave = leerNat();
      assert(esClaveEnMap(clave, map));
      printf("%.2lf\n", valorEnMap(clave, map));

    } else if (0 == strcmp(nom_comando, "estaLlenoMap")) {
      printf("%s.\n", estaLlenoMap(map) ? "LLeno" : "No lleno");

      // operaciones de pila
    } else if (0 == strcmp(nom_comando, "cantidadEnPila")) {
      printf("Cantidad en pila: %u.\n", cantidadEnPila(pila));

    } else if (0 == strcmp(nom_comando, "apilar")) {
      TInfo info = leerInfo();
      pila = apilar(info, pila);
      printf("Apilando ");
      imprimirInfo(info);
      printf("\n");
      liberarInfo(info);

    } else if (0 == strcmp(nom_comando, "cima")) {
      assert(cantidadEnPila(pila) > 0);
      imprimirInfo(cima(pila));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "desapilar")) {
      assert(cantidadEnPila(pila) > 0);
      pila = desapilar(pila);
      printf("Desapilando.\n");

      // operaciones de cola
    } else if (0 == strcmp(nom_comando, "cantidadEnCola")) {
      printf("Cantidad en cola: %u.\n", cantidadEnCola(cola));

    } else if (0 == strcmp(nom_comando, "encolar")) {
      TInfo info = leerInfo();
      cola = encolar(info, cola);
      printf("Encolando ");
      imprimirInfo(info);
      printf("\n");
      liberarInfo(info);

    } else if (0 == strcmp(nom_comando, "frente")) {
      assert(cantidadEnCola(cola) > 0);
      imprimirInfo(frente(cola));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "desencolar")) {
      assert(cantidadEnCola(cola) > 0);
      cola = desencolar(cola);
      printf("Desencolando.\n");

      // operaciones de palabras
    } else if (0 == strcmp(nom_comando, "insertarPalabra")) {
      char palabra[MAX_LINEA];
      scanf("%s", palabra);
      //            if (!strcmp(palabra, "^")) palabra[0] = '\0';
      insertarPalabra(palabra, palabras);
      printf("Insertando %s.\n", palabra);

    } else if (0 == strcmp(nom_comando, "imprimirPalabrasCortas")) {
      nat k = leerNat();
      printf("\n");
      imprimirPalabrasCortas(k, palabras);

    } else if (0 == strcmp(nom_comando, "buscarFinPrefijo")) {
      char prefijo[MAX_LINEA];
      scanf("%s", prefijo);
      if (!strcmp(prefijo, "^"))
        prefijo[0] = '\0';
      printf("\n");
      TPalabras arbolFin = buscarFinPrefijo(prefijo, palabras);
      if (arbolFin != NULL)
        imprimirPalabras(prefijo, strlen(prefijo), subarboles(arbolFin));
      else
        printf("palabras no contiene %s.\n", prefijo);

      // operaciones de abb

    } else if (0 == strcmp(nom_comando, "rotar")) {
      nat clave = leerNat();
      char tipo[2];
      scanf("%*[ ]"); // para consumir los espacios en blanco
      scanf("%c", &tipo[0]);
      scanf("%c", &tipo[1]);
      abb = rotar(clave, tipo, abb);
      printf("\n");

    } else if (0 == strcmp(nom_comando, "esVacioAbb")) {
      printf("El abb %s vacío.\n", esVacioAbb(abb) ? "es" : "NO es");

    } else if (0 == strcmp(nom_comando, "buscarSubarbol")) {
      nat clave = leerNat();
      TAbb res = buscarSubarbol(clave, abb);
      if (!esVacioAbb(res))
        imprimirInfo(raiz(res));
      else
        printf("%u no está en el abb.", clave);
      printf("\n");

    } else if (0 == strcmp(nom_comando, "raiz")) {
      assert(!esVacioAbb(abb));
      printf("La raíz del abb es: ");
      imprimirInfo(raiz(abb));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "izquierdo")) {
      assert(!esVacioAbb(abb));
      TAbb res = izquierdo(abb);
      if (!esVacioAbb(res)) {
        printf("La raíz del hijo izquierdo del abb es: ");
        imprimirInfo(raiz(res));
      } else
        printf("El abb no tiene hijo izquierdo.");
      printf("\n");

    } else if (0 == strcmp(nom_comando, "derecho")) {
      assert(!esVacioAbb(abb));
      TAbb res = derecho(abb);
      if (!esVacioAbb(res)) {
        printf("La raíz del hijo derecho del abb es: ");
        imprimirInfo(raiz(res));
      } else
        printf("El abb no tiene hijo derecho.");
      printf("\n");

    } else if (0 == strcmp(nom_comando, "menorEnAbb")) {
      assert(!esVacioAbb(abb));
      printf("El menor en el abb es: ");
      imprimirInfo(menorEnAbb(abb));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "mayorEnAbb")) {
      assert(!esVacioAbb(abb));
      printf("El mayor en el abb es: ");
      imprimirInfo(mayorEnAbb(abb));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "insertarEnAbb")) {
      TInfo dato = leerInfo();
      assert(esVacioAbb(buscarSubarbol(natInfo(dato), abb)));
      abb = insertarEnAbb(dato, abb);
      printf("Se insertó ");
      imprimirInfo(dato);
      printf(" en el abb.\n");

    } else if (0 == strcmp(nom_comando, "removerDeAbb")) {
      nat clave = leerNat();
      assert(!esVacioAbb(buscarSubarbol(clave, abb)));
      abb = removerDeAbb(clave, abb);
      printf("Se removió %u del abb.\n", clave);

    } else if (0 == strcmp(nom_comando, "copiaAbb")) {
      TAbb res = copiaAbb(abb);
      printf("\n");
      imprimirAbb(res);
      liberarAbb(res);

    } else if (0 == strcmp(nom_comando, "consAbb")) {
      TInfo dato = leerInfo();
      nat rizq = leerNat();
      nat rder = leerNat();
      TAbb subizq = buscarSubarbol(rizq, abb);
      assert(esVacioAbb(subizq) || natInfo(mayorEnAbb(subizq)) < natInfo(dato));

      TAbb subder = buscarSubarbol(rder, abb);
      assert(esVacioAbb(subder) || natInfo(menorEnAbb(subder)) > natInfo(dato));

      TAbb res = consAbb(dato, copiaAbb(subizq), copiaAbb(subder));
      printf("\n");
      imprimirAbb(res);
      liberarAbb(res);

      // operaciones de iterador

    } else if (0 == strcmp(nom_comando, "agregarAIterador")) {
      nat elem = leerNat();
      /*iter = */ agregarAIterador(elem, iter);
      printf("Agregando %u a it.\n", elem);

    } else if (0 == strcmp(nom_comando, "reiniciarIterador")) {
      /*iter = */ reiniciarIterador(iter);
      printf("Reiniciando it.\n");

    } else if (0 == strcmp(nom_comando, "avanzarIterador")) {
      /*iter = */ avanzarIterador(iter);
      printf("Avanzando en it.\n");

    } else if (0 == strcmp(nom_comando, "actualEnIterador")) {
      assert(estaDefinidaActual(iter));
      printf("El actual de it es %d.\n", actualEnIterador(iter));

    } else if (0 == strcmp(nom_comando, "estaDefinidaActual")) {
      printf("Actual de it %s definida.\n",
             estaDefinidaActual(iter) ? "está" : "NO está");

      // operaciones de cadena

    } else if (0 == strcmp(nom_comando, "cantidadEnCadena")) {
      printf("La cantidad es %u.\n", cantidadEnCadena(cad));

    } else if (0 == strcmp(nom_comando, "estaEnCadena")) {
      nat natural = leerNat();
      printf("%u %s en la cadena.\n", natural,
             (estaEnCadena(natural, cad)) ? "está" : "no está");

    } else if (0 == strcmp(nom_comando, "insertarAlInicio")) {
      nat natural = leerNat();
      double real = leerDouble();
      cad = insertarAlInicio(natural, real, cad);
      printf("Se insertó (%d,%4.2lf) al inicio de la cadena.\n", natural, real);

    } else if (0 == strcmp(nom_comando, "primeroEnCadena")) {
      assert(cantidadEnCadena(cad) > 0);
      printf("El primero es ");
      imprimirInfo(primeroEnCadena(cad));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "infoCadena")) {
      nat natural = leerNat();
      assert(estaEnCadena(natural, cad));
      printf("El elemento es ");
      imprimirInfo(infoCadena(natural, cad));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "cadenaSiguiente")) {
      nat sigs = leerNat();
      TCadena siguiente = cad;
      for (nat i = 0; i < sigs; i++)
        siguiente = cadenaSiguiente(siguiente);
      imprimirCadena(siguiente);

    } else if (0 == strcmp(nom_comando, "removerDeCadena")) {
      nat natural = leerNat();
      assert(estaEnCadena(natural, cad));
      cad = removerDeCadena(natural, cad);
      printf("Se removió la primera aparición de %u de la cadena.\n", natural);

    } else if (0 == strcmp(nom_comando, "imprimirCadena")) {
      imprimirCadena(cad);

      // operaciones de colCadenas
    } else if (0 == strcmp(nom_comando, "cadenaDeColCadenas")) {
      nat pos = leerNat();
      assert((0 <= pos) && (pos < tamanioColCadenas(colCads)));
      printf("La cadena %u es :", pos);
      imprimirCadena(cadenaDeColCadenas(pos, colCads));

    } else if (0 == strcmp(nom_comando, "tamanioColCadenas")) {
      printf("La colección tiene %u cadenas .\n", tamanioColCadenas(colCads));

    } else if (0 == strcmp(nom_comando, "cantidadColCadenas")) {
      nat pos = leerNat();
      assert((0 <= pos) && (pos < tamanioColCadenas(colCads)));
      printf("La cantidad en la cadena %u es %u.\n", pos,
             cantidadColCadenas(pos, colCads));

    } else if (0 == strcmp(nom_comando, "estaEnColCadenas")) {
      nat natural = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < tamanioColCadenas(colCads)));
      printf("%u %s en la cadena %u.\n", natural,
             (estaEnColCadenas(natural, pos, colCads)) ? "está" : "no está",
             pos);

    } else if (0 == strcmp(nom_comando, "insertarEnColCadenas")) {
      nat natural = leerNat();
      double real = leerDouble();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < tamanioColCadenas(colCads)));
      colCads = insertarEnColCadenas(natural, real, pos, colCads);
      printf("Se insertó (%u,%4.2lf) en la cadena %u.\n", natural, real, pos);

    } else if (0 == strcmp(nom_comando, "infoEnColCadenas")) {
      nat natural = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < tamanioColCadenas(colCads)));
      assert(estaEnColCadenas(natural, pos, colCads));
      printf("La primera aparición de %u en la cadena %u es ", natural, pos);
      imprimirInfo(infoEnColCadenas(natural, pos, colCads));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "removerDeColCadenas")) {
      nat natural = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < tamanioColCadenas(colCads)));
      assert(estaEnColCadenas(natural, pos, colCads));
      colCads = removerDeColCadenas(natural, pos, colCads);
      printf("Se removió la primera aparición de %d de la cadena %d.\n",
             natural, pos);

      // operaciones de aplicaciones

    } else if (0 == strcmp(nom_comando, "filtradaOrdenada")) {
      TIterador itOrdenado = leerIteradorOrdenado();
      TCadena filtrada = filtradaOrdenada(cad, itOrdenado);
      imprimirCadena(filtrada);
      liberarCadena(filtrada);
      liberarIterador(itOrdenado);

    } else if (0 == strcmp(nom_comando, "esAvl")) {
      printf("%s.\n", esAvl(abb) ? "Es AVL" : "NO es AVL");

    } else if (0 == strcmp(nom_comando, "avlMin")) {
      nat h = leerNat();
      TAbb aMin = avlMin(h);
      imprimirAbb(aMin);
      liberarAbb(aMin);

    } else if (0 == strcmp(nom_comando, "estaOrdenada")) {
      printf("La cadena %s ordenada.\n",
             estaOrdenada(cad) ? "está" : "no está");

    } else if (0 == strcmp(nom_comando, "mezclaCadenas")) {
      TCadena cad1 = leerCadena();
      assert(estaOrdenada(cad1));
      TCadena cad2 = leerCadena();
      assert(estaOrdenada(cad2));
      TCadena mezcla = mezclaCadenas(cad1, cad2);
      imprimirCadena(mezcla);
      liberarCadena(cad1);
      liberarCadena(cad2);
      liberarCadena(mezcla);

    } else if (0 == strcmp(nom_comando, "crearBalanceado")) {
      nat n = leerNat();
      TInfo *arreglo = leerArregloInfos(n);
      TAbb balanceado = crearBalanceado(arreglo, n);
      printf("\n");
      imprimirAbb(balanceado);

      for (nat i = 0; i < n; i++)
        liberarInfo(arreglo[i]);
      delete[] arreglo;
      liberarAbb(balanceado);

    } else if (0 == strcmp(nom_comando, "unionAbbs")) {
      TAbb abb1 = leerAbb();
      TAbb abb2 = leerAbb();
      TAbb u = unionAbbs(abb1, abb2);
      printf("\n");
      imprimirAbb(u);

      liberarAbb(abb1);
      liberarAbb(abb2);
      liberarAbb(u);

    } else if (0 == strcmp(nom_comando, "ordenadaPorModulo")) {
      nat p = leerNat();
      assert(p > 1);
      TCola ordenada = ordenadaPorModulo(p, cad);
      while (cantidadEnCola(ordenada) > 0) {
        imprimirInfo(frente(ordenada));
        ordenada = desencolar(ordenada);
      }
      printf("\n");
      liberarCola(ordenada);

    } else if (0 == strcmp(nom_comando, "menoresQueElResto")) {
      TPila menores = menoresQueElResto(cad, cantidadEnCadena(cad));
      while (cantidadEnPila(menores) > 0) {
        imprimirInfo(cima(menores));
        menores = desapilar(menores);
      }
      printf("\n");
      liberarPila(menores);

    } else if (0 == strcmp(nom_comando, "linealizacion")) {
      TCadena res = linealizacion(abb);
      imprimirCadena(res);
      liberarCadena(res);

    } else if (0 == strcmp(nom_comando, "esPerfecto")) {
      printf("El abb %s perfecto.\n", esPerfecto(abb) ? "es" : "NO es");

    } else if (0 == strcmp(nom_comando, "imprimirAbb")) {
      printf("\n");
      imprimirAbb(abb);

    } else if (0 == strcmp(nom_comando, "menores")) {
      nat limite = leerDouble();
      TAbb res = menores(limite, abb);
      printf("\n");
      imprimirAbb(res);
      liberarAbb(res);

    } else if (0 == strcmp(nom_comando, "caminoAscendente")) {
      nat clave = leerNat();
      assert(!esVacioAbb(buscarSubarbol(clave, abb)));
      nat k = leerNat();
      TIterador res = caminoAscendente(clave, k, abb);
      reiniciarIterador(res);
      while (estaDefinidaActual(res)) {
        printf("%u ", actualEnIterador(res));
        avanzarIterador(res);
      }
      printf("\n");
      printf("La posición actual %s definida.\n",
             (!estaDefinidaActual(res)) ? "NO está" : "está");
      liberarIterador(res);

    } else if (0 == strcmp(nom_comando, "insertarAlFinal")) {
      nat natural = leerNat();
      double real = leerDouble();
      cad = insertarAlFinal(natural, real, cad);
      printf("Se insertó (%d,%4.2lf) al final de la cadena.\n", natural, real);

    } else if (0 == strcmp(nom_comando, "removerPrimero")) {
      assert(cantidadEnCadena(cad) > 0);
      cad = removerPrimero(cad);
      printf("Se removió el primer elemento de la cadena.\n");

    } else if (0 == strcmp(nom_comando, "copiaCadena")) {
      TCadena copia = copiaCadena(cad);
      imprimirCadena(copia);
      liberarCadena(copia);

    } else if (0 == strcmp(nom_comando, "reversoDeIterador")) {
      TIterador reverso = reversoDeIterador(iter);
      reiniciarIterador(reverso);
      if (estaDefinidaActual(iter))
        printf("Error: la posición de iter no debe estar definida.\n");
      while (estaDefinidaActual(reverso)) {
        printf("%u ", actualEnIterador(reverso));
        avanzarIterador(reverso);
      }
      printf("\n");
      liberarIterador(reverso);

      // test de tiempo

    } else if (0 == strcmp(nom_comando, "tiempo-cp")) {
      nat N = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      TColaDePrioridad a;
      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        a = crearCP(N);
        for (nat i = N; i >= 1; i--) {
          a = insertarEnCP(i, (double)i, a);
          prioritario(a);
        }
        for (nat i = N; i <= 1; i++) {
          a = insertarEnCP(N, 0, a);
          a = insertarEnCP(1, 0, a);
          a = insertarEnCP(N + 1, 0, a);
        }
        for (nat i = 1; i <= N; i++)
          a = eliminarPrioritario(a);
        liberarCP(a);

        a = crearCP(N);
        for (nat i = 1; i <= N; i++) {
          a = insertarEnCP(i, (double)i, a);
          prioritario(a);
        }
        for (nat i = 1; i <= N; i++)
          a = eliminarPrioritario(a);
        liberarCP(a);

        a = crearCP(N);
        a = invertirPrioridad(a);
        for (nat i = 1; i <= N; i++) {
          a = insertarEnCP(i, (double)i, a);
          prioritario(a);
        }
        for (nat i = 1; i <= N; i++)
          a = eliminarPrioritario(a);
        liberarCP(a);

        a = crearCP(N);
        for (nat i = N; i >= 1; i--) {
          a = insertarEnCP(i, (double)i, a);
          prioritario(a);
        }
        a = invertirPrioridad(a);
        for (nat i = 1; i <= N; i++) {
          prioritario(a);
          a = eliminarPrioritario(a);
        }
        liberarCP(a);

        a = crearCP(N);
        a = insertarEnCP(N, (double)N, a);
        for (nat i = 1; i <= N; i++) {
          a = insertarEnCP(1, 1.0, a);
          prioritario(a);
          a = eliminarPrioritario(a);
        }
        liberarCP(a);

        a = crearCP(N);
        a = insertarEnCP(1, (double)1, a);
        for (nat i = 1; i <= N; i++) {
          a = insertarEnCP(N, (double)N, a);
          prioritario(a);
          a = eliminarPrioritario(a);
        }
        liberarCP(a);

        a = crearCP(N);
        a = insertarEnCP(1, 1.0, a);
        a = insertarEnCP(N, (double)N, a);
        for (nat i = 1; i <= N; i++) {
          estaEnCP(1, a);
          estaEnCP(N / 2, a);
          estaEnCP(N, a);
        }
        liberarCP(a);
      }
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      //      printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

    } else if (0 == strcmp(nom_comando, "tiempo-map")) {
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();
      const nat MODULO = 1000000;
      srand(1);

      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        TMapping a = crearMap(tamanio);
        //      printf("prueba asociar, desasociar, existeAsociacion. \n");
        for (nat j = 1; j < tamanio; j++) {
          nat rnd = rand() % MODULO;
          if (esClaveEnMap(rnd, a))
            a = desasociarEnMap(rnd, a);
          a = asociarEnMap(rnd, (double)rnd, a);
        }
        //      printf("prueba existeAsociacion, valorEnMap. \n");
        for (nat j = 0; j < MODULO; j++) {
          nat rnd = rand() % MODULO;
          if (esClaveEnMap(rnd, a))
            valorEnMap(rnd, a);
        }
        liberarMap(a);
      }
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      //      printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

    } else if (0 == strcmp(nom_comando, "tiempo-esAVL")) {
      nat cantidad = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();
      TInfo *arreglo = new TInfo[cantidad];
      for (nat i = 0; i < cantidad; i++) {
        arreglo[i] = crearInfo(i + 2, 0);
      }
      TAbb arbol = crearBalanceado(arreglo, cantidad);
      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        esAvl(arbol);
      }
      arbol = insertarEnAbb(crearInfo(1, 0), arbol);
      arbol = insertarEnAbb(crearInfo(0, 0), arbol);
      for (nat i = 1; i <= iteraciones; i++) {
        esAvl(arbol);
      }
      arbol = removerDeAbb(0, arbol);
      arbol = insertarEnAbb(crearInfo(cantidad + 3, 0), arbol);
      arbol = insertarEnAbb(crearInfo(cantidad + 4, 0), arbol);
      for (nat i = 1; i <= iteraciones; i++) {
        esAvl(arbol);
      }
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      //            printf("%f \n", tiempo);
      liberarAbb(arbol);
      for (nat i = 0; i < cantidad; i++) {
        liberarInfo(arreglo[i]);
      }
      delete[] arreglo;
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

    } else if (0 == strcmp(nom_comando, "tiempo-filtradaOrdenada")) {
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();
      TCadena cadParametro = crearCadena();
      TIterador itParametro = crearIterador();
      for (nat i = 0; i <= tamanio; i++) {
        cadParametro = insertarAlInicio(i, 0, cadParametro);
        cadParametro = insertarAlFinal(i, 0, cadParametro);
        agregarAIterador(i, itParametro);
      }
      cadParametro = insertarAlInicio(1234567891, 0, cadParametro);
      cadParametro = insertarAlFinal(1345678912, 0, cadParametro);
      agregarAIterador(1234567891, itParametro);
      agregarAIterador(1345678912, itParametro);

      TCadena filtrada;
      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        filtrada = filtradaOrdenada(cadParametro, itParametro);
        liberarCadena(filtrada);
      }
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      liberarCadena(cadParametro);
      liberarIterador(itParametro);
      //            printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

    } else if (0 == strcmp(nom_comando, "tiempo-cadena")) {
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      clock_t tm = clock();
      TCadena cadenaTiempo = crearCadena();
      for (nat i = tamanio; i >= 1; i--) {
        cadenaTiempo = insertarAlInicio(i, 0, cadenaTiempo);
      }

      TCadena segunda = crearCadena();
      for (nat i = 1; i <= tamanio; i++) {
        segunda = insertarAlFinal(2 * i, 0, segunda);
      }
      if (estaOrdenada(segunda)) {
        TCadena mezcla = mezclaCadenas(cadenaTiempo, segunda);
        liberarCadena(mezcla);
      }

      liberarCadena(segunda);

      for (nat i = 1; i <= iteraciones; i++) {
        nat primero = natInfo(primeroEnCadena(cadenaTiempo));
        cadenaTiempo = removerPrimero(cadenaTiempo);
        cadenaTiempo = insertarAlFinal(primero, 0, cadenaTiempo);
        cadenaTiempo = cadenaSiguiente(cadenaTiempo);
      }

      liberarCadena(cadenaTiempo);

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

    } else if (0 == strcmp(nom_comando, "tiempo-colCadenas")) {
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      clock_t tm = clock();
      TColCadenas colCadenasTiempo = crearColCadenas(tamanio);
      for (nat i = 1; i <= tamanio; i++) {
        colCadenasTiempo = insertarEnColCadenas(i, 0, 0, colCadenasTiempo);
        colCadenasTiempo =
            insertarEnColCadenas(i, 0, tamanio - 1, colCadenasTiempo);
      }

      TCadena cadena_pos;
      for (nat i = 1; i <= iteraciones; i++) {
        cadena_pos = cadenaDeColCadenas(0, colCadenasTiempo);
        cadena_pos = cadenaDeColCadenas(tamanio / 2, colCadenasTiempo);
        cadena_pos = cadenaDeColCadenas(tamanio - 1, colCadenasTiempo);
        nat primero = natInfo(primeroEnCadena(cadena_pos));
        if (primero == 0)
          printf("ERROR: Componente natural igual a 0.\n");
      }

      liberarColCadenas(colCadenasTiempo);

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

    } else if (0 == strcmp(nom_comando, "tiempo-iterador")) {
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      clock_t tm = clock();
      TIterador iteradorTiempo = crearIterador();
      for (nat i = 1; i <= tamanio; i++) {
        agregarAIterador(i, iteradorTiempo);
      }
      TIterador reverso = reversoDeIterador(iteradorTiempo);
      for (nat i = 1; i <= iteraciones; i++) {
        if (estaDefinidaActual(iteradorTiempo)) {
          nat actual = actualEnIterador(iteradorTiempo);
          if (actual == 0)
            printf("ERROR: actual igual a 0.\n");
          avanzarIterador(iteradorTiempo);
        } else
          reiniciarIterador(iteradorTiempo);
      }
      liberarIterador(iteradorTiempo);
      liberarIterador(reverso);

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

    } else if (0 == strcmp(nom_comando, "tiempo-abb")) {
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      TInfo *arreglo1 = new TInfo[tamanio];
      TInfo *arreglo2 = new TInfo[tamanio];
      for (nat i = 0; i < tamanio; i++) {
        arreglo1[i] = crearInfo(2 * i + 1, 0);
        arreglo2[i] = crearInfo(2 * i, 0);
      }

      clock_t tm = clock();
      TAbb abb1 = crearBalanceado(arreglo1, tamanio);
      TAbb abb2 = crearBalanceado(arreglo2, tamanio);
      TAbb u = unionAbbs(abb1, abb2);
      TAbb copia = consAbb(copiaInfo(raiz(u)), copiaAbb(izquierdo(u)),
                           copiaAbb(derecho(u)));
      for (nat i = 1; i <= iteraciones; i++) {
        menorEnAbb(u);
        mayorEnAbb(copia);
        buscarSubarbol(1, abb2);
        buscarSubarbol(2 * tamanio + 2, abb1);
        buscarSubarbol(2 * (tamanio / 2), abb1);
        buscarSubarbol(2 * (tamanio / 2) + 1, abb1);
        abb2 = insertarEnAbb(crearInfo(2 * (tamanio / 2) + 1, 0), abb2);
        abb2 = removerDeAbb(2 * (tamanio / 2) + 1, abb2);
      }

      liberarAbb(abb1);
      liberarAbb(abb2);
      liberarAbb(u);
      liberarAbb(copia);

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

      for (nat i = 0; i < tamanio; i++) {
        liberarInfo(arreglo1[i]);
        liberarInfo(arreglo2[i]);
      }
      delete[] arreglo1;
      delete[] arreglo2;

    } else if (0 == strcmp(nom_comando, "tiempo-menores")) {
      nat altura = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();
      nat cantidad = pow(2, altura) - 1;
      TInfo *arreglo = new TInfo[cantidad];
      for (nat i = 0; i < cantidad; i++) {
        if (i % 2 == 0)
          arreglo[i] = crearInfo(i, 0);
        else
          arreglo[i] = crearInfo(i, 10);
      }
      TAbb arbol = crearBalanceado(arreglo, cantidad);

      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        TAbb res = menores(1, arbol);
        liberarAbb(res);
      }

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

      for (nat i = 0; i < cantidad; i++) {
        liberarInfo(arreglo[i]);
      }
      delete[] arreglo;
      liberarAbb(arbol);

    } else if (0 == strcmp(nom_comando, "tiempo-palabras")) {
      TPalabras palabrasTiempo = crearPalabras();
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();
      char prefijo[MAX_LINEA];
      prefijo[0] = '\0';
      palabrasTiempo = poblarVocabulario(prefijo, 0, tamanio, palabrasTiempo);

      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        char buscado[MAX_LINEA];
        strcpy(buscado, "aaaa");
        buscarFinPrefijo(buscado, palabrasTiempo);
        strcpy(buscado, "bcbabcd");
        buscarFinPrefijo(buscado, palabrasTiempo);
        strcpy(buscado, "dddd");
        buscarFinPrefijo(buscado, palabrasTiempo);
      }

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

      liberarPalabras(palabrasTiempo);

    } else if (0 == strcmp(nom_comando, "tiempo-pila")) {
      TPila pilaTiempo = crearPila();

      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      clock_t tm = clock();

      for (nat i = 1; i <= iteraciones; i++) {
        for (nat j = 1; j <= tamanio; j++) {
          TInfo info = crearInfo(j, 0);
          pilaTiempo = apilar(info, pilaTiempo);
          cantidadEnPila(pilaTiempo);
          liberarInfo(info);
        }
        for (nat j = 1; j <= tamanio; j++) {
          cima(pilaTiempo);
          pilaTiempo = desapilar(pilaTiempo);
        }
      }

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

      liberarPila(pilaTiempo);

    } else if (0 == strcmp(nom_comando, "tiempo-cola")) {
      TCola colaTiempo = crearCola();

      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      clock_t tm = clock();

      for (nat i = 1; i <= iteraciones; i++) {
        for (nat j = 1; j <= tamanio; j++) {
          TInfo info = crearInfo(j, 0);
          colaTiempo = encolar(info, colaTiempo);
          cantidadEnCola(colaTiempo);
          liberarInfo(info);
        }
        for (nat j = 1; j <= tamanio; j++) {
          frente(colaTiempo);
          colaTiempo = desencolar(colaTiempo);
        }
      }

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");

      liberarCola(colaTiempo);

    } else if (0 == strcmp(nom_comando, "tiempo-ordenadaPorModulo")) {
      TCadena ordenadaTiempo = crearCadena();
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      for (nat i = 1; i <= tamanio; i++)
        ordenadaTiempo = insertarAlInicio(i, 0, ordenadaTiempo);

      TCola res;
      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        res = ordenadaPorModulo(2, ordenadaTiempo);
        liberarCola(res);
        res = ordenadaPorModulo(7, ordenadaTiempo);
        liberarCola(res);
        res = ordenadaPorModulo(10, ordenadaTiempo);
        liberarCola(res);
      }

      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");
      liberarCadena(ordenadaTiempo);

    } else if (0 == strcmp(nom_comando, "tiempo-menoresQueElResto")) {
      TCadena menoresTiempo = crearCadena();
      nat tamanio = leerNat();
      nat iteraciones = leerNat();
      nat timeout = leerNat();

      for (nat i = 1; i <= tamanio; i++)
        menoresTiempo = insertarAlInicio((i % 13) * (i % 11), 0, menoresTiempo);

      clock_t tm = clock();
      for (nat i = 1; i <= iteraciones; i++) {
        TPila res = menoresQueElResto(menoresTiempo, tamanio);
        liberarPila(res);
      }
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
      else
        printf("Bien.\n");
      liberarCadena(menoresTiempo);

    } else if (0 == strcmp(nom_comando, "reiniciarEstructuras")) {
      liberarCP(cp);
      cp = crearCP(MAX_CP);
      liberarMap(map);
      map = crearMap(MAX_MAP);
      liberarCola(cola);
      cola = crearCola();
      liberarPila(pila);
      pila = crearPila();
      liberarPalabras(palabras);
      palabras = crearPalabras();
      liberarAbb(abb);
      abb = crearAbb();
      liberarIterador(iter);
      iter = crearIterador();
      liberarCadena(cad);
      cad = crearCadena();
      liberarColCadenas(colCads);
      colCads = crearColCadenas(TAM_COL_CAD);
      printf("Estructuras reiniciadas.\n");

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(restoLinea, MAX_LINEA + 1, stdin);
  } // while

  liberarCP(cp);
  liberarMap(map);
  liberarCola(cola);
  liberarPila(pila);
  liberarPalabras(palabras);
  liberarAbb(abb);
  liberarIterador(iter);
  liberarCadena(cad);
  liberarColCadenas(colCads);
  return 0;
} // main
