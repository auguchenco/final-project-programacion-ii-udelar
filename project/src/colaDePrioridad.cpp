/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"



//    E S T R U C T U R A S   A U X I L I A R E S


struct tInf {
  nat elem;
  double valor;
};

typedef tInf* THeap;
typedef nat* TPosiciones;

//    F I N   E S T R U C T U R A S   A U X I L I A R E S



// Representación de 'TColaDePrioridad'
// Se debe definir en colaDePrioridad.cpp
// struct _rep_colaDePrioridad;
// Declaración del tipo 'TColaDePrioridad'
struct _rep_colaDePrioridad {
  nat cantAct;
  nat cantMax;
  TPosiciones posiciones;
  THeap heap;
  bool prInv;
};

//Auxiliar filtradoAscendente:
void filtradoAscendente(nat pos, TColaDePrioridad &cp){
  /*tInf swap;
  swap.elem = cp->heap[pos].elem;
  swap.valor = cp->heap[pos].valor;
  while ((pos > 1) && ((!(cp->prInv)) == ((cp->heap[pos/2].valor) > (swap.valor)))){
    cp->heap[pos].elem = cp->heap[pos/2].elem;
    cp->heap[pos].valor = cp->heap[pos/2].valor;
    cp->posiciones[cp->heap[pos/2].elem] = pos;
    pos = (pos/2);
  };
  cp->heap[pos].elem = swap.elem;
  cp->heap[pos].valor = swap.valor;
  cp->posiciones[swap.elem] = pos;*/
  tInf swap;
  swap.elem = cp->heap[pos].elem;
  swap.valor = cp->heap[pos].valor;
  if (cp->prInv){ // Esta invertida la prioridad
    while ((pos > 1) && ((cp->heap[pos/2].valor) < (swap.valor))){
      cp->heap[pos].elem = cp->heap[pos/2].elem;
      cp->heap[pos].valor = cp->heap[pos/2].valor;
      cp->posiciones[cp->heap[pos/2].elem] = pos;
      pos = (pos/2);
    };
  } else {  // NO esta invertida la prioridad
    while ((pos > 1) && ((cp->heap[pos/2].valor) > (swap.valor))){
      cp->heap[pos].elem = cp->heap[pos/2].elem;
      cp->heap[pos].valor = cp->heap[pos/2].valor;
      cp->posiciones[cp->heap[pos/2].elem] = pos;
      pos = (pos/2);
    };
  };
  cp->heap[pos].elem = swap.elem;
  cp->heap[pos].valor = swap.valor;
  cp->posiciones[swap.elem] = pos;
};

//Auxiliar filtradoDescendente:
void filtradoDescendente(nat pos, TColaDePrioridad &cp){
  /*tInf swap;
  swap.elem = cp->heap[pos].elem;
  swap.valor = cp->heap[pos].valor;
  if (pos*2 <= cp->cantAct) {
    nat posHijo;
    do {
      posHijo = pos*2;
      if (((posHijo+1) <= cp->cantAct) && ((!(cp->prInv)) == ((cp->heap[posHijo+1].valor) < (cp->heap[posHijo].valor)))){
        posHijo++;
      };
      if ((!(cp->prInv)) == ((swap.valor) > (cp->heap[posHijo].valor))){
        cp->heap[pos].elem = cp->heap[posHijo].elem;
        cp->heap[pos].valor = cp->heap[posHijo].valor;
        cp->posiciones[cp->heap[posHijo].elem] = pos;
        pos = posHijo;
      };
    } while (((pos*2) <= (cp->cantAct)) && ((!(cp->prInv)) == ((swap.valor) > (cp->heap[posHijo].valor))));
    cp->heap[pos].elem = swap.elem;
    cp->heap[pos].valor = swap.valor;
    cp->posiciones[swap.elem] = pos;
  };*/

  
  if (pos*2 <= cp->cantAct) {
    tInf swap;
    swap.elem = cp->heap[pos].elem;
    swap.valor = cp->heap[pos].valor;
    nat posHijo;
    if (cp->prInv){
      do {
        posHijo = pos*2;
        if (((posHijo+1) <= cp->cantAct) && ((cp->heap[posHijo+1].valor) > (cp->heap[posHijo].valor))){
          posHijo++;
        };
        if ((swap.valor) < (cp->heap[posHijo].valor)){
          cp->heap[pos].elem = cp->heap[posHijo].elem;
          cp->heap[pos].valor = cp->heap[posHijo].valor;
          cp->posiciones[cp->heap[posHijo].elem] = pos;
          pos = posHijo;
        };
      } while (((pos*2) <= (cp->cantAct)) && ((swap.valor) < (cp->heap[posHijo].valor)));
    } else {
      do {
        posHijo = pos*2;
        if (((posHijo+1) <= cp->cantAct) && ((cp->heap[posHijo+1].valor) < (cp->heap[posHijo].valor))){
          posHijo++;
        };
        if ((swap.valor) > (cp->heap[posHijo].valor)){
          cp->heap[pos].elem = cp->heap[posHijo].elem;
          cp->heap[pos].valor = cp->heap[posHijo].valor;
          cp->posiciones[cp->heap[posHijo].elem] = pos;
          pos = posHijo;
        };
      } while (((pos*2) <= (cp->cantAct)) && ((swap.valor) > (cp->heap[posHijo].valor)));
    };
    cp->heap[pos].elem = swap.elem;
    cp->heap[pos].valor = swap.valor;
    cp->posiciones[swap.elem] = pos;
  };

};

//Auxiliar modificar prioridad:
void actualizarPrioridad(nat elem, double valor, TColaDePrioridad &cp){
  /*nat pos = cp->posiciones[elem];
  double prAnt = cp->heap[pos].valor;
  if ((!(cp->prInv)) == (valor > prAnt)) {
    filtradoDescendente(pos,cp);
  } else if ((!(cp->prInv)) == (valor <  prAnt)){
    filtradoAscendente(pos,cp);
  };*/

  nat pos = cp->posiciones[elem];
  double prAnt = cp->heap[pos].valor;
  cp->heap[pos].valor = valor;

  if (cp->prInv){
    if (valor < prAnt){
      filtradoDescendente(pos,cp);
    } else if (valor >  prAnt){
      filtradoAscendente(pos,cp);
    };
  } else {
    if (valor > prAnt){
      filtradoDescendente(pos,cp);
    } else if (valor <  prAnt){
      filtradoAscendente(pos,cp);
    };
  };
  
};

//Auxiliar insertar elemento:
void insertarElemento(nat elem, double valor, TColaDePrioridad &cp){
  cp->cantAct++;
  cp->heap[cp->cantAct].elem = elem;
  cp->heap[cp->cantAct].valor = valor;
  cp->posiciones[elem] = cp->cantAct;
  filtradoAscendente(cp->cantAct, cp);
};

//Auxiliar eliminar prioritario:
void eliminarPrimero(TColaDePrioridad &cp){
  cp->posiciones[cp->heap[1].elem] = 0;
  cp->heap[1].elem = cp->heap[cp->cantAct].elem;
  cp->heap[1].valor = cp->heap[cp->cantAct].valor;
  cp->heap[cp->cantAct].elem = 0;
  cp->heap[cp->cantAct].valor = 0;
  cp->posiciones[cp->heap[1].elem] = 1;
  cp->posiciones[0] = 0;
  cp->cantAct--;
  if (cp->cantAct > 1) {
    filtradoDescendente(1, cp);
  };
};

/*
  Devuelve una 'TColaDePrioridad' vacía (sin elementos). Podrá contener
  elementos entre 1 y N.
  Un elemento es prioritario ante otro si su valor asociado es menor.
  El tiempo de ejecución en el peor caso es O(N).
 */
TColaDePrioridad crearCP(nat N)  { 
  TColaDePrioridad cp = NULL;
  if (0<N){
    cp = new _rep_colaDePrioridad;
    cp->cantAct = 0;
    cp->cantMax = N;
    cp->prInv = false;
    cp->posiciones = new nat[N+1];
    cp->heap = new tInf[N+1];
    for (nat i=0; i<=N; i++){
      cp->posiciones[i] = 0;
      cp->heap[i].elem = 0;
      cp->heap[i].valor = 0;
    };
  };
  return cp;
};

/*
  Modifica el criterio de prioridad: si el prioritario era el que tenía asociado
  el menor valor pasa a ser el que tiene asociado el mayor valor, y viceversa.
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cp'.
 */
TColaDePrioridad invertirPrioridad(TColaDePrioridad cp) {
  if (cp != NULL){
    cp->prInv = !(cp->prInv);
    if (!(estaVaciaCP(cp))){
      for (nat i=((cp->cantAct) / 2); i>0; i--){
        filtradoDescendente(i, cp);
      };
    };
  };
  return cp;
};

/*
  Libera la menoria asignada a 'cp' y a cada uno de sus elementos.
  El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
  pasado en crearCP.
 */
void liberarCP(TColaDePrioridad cp) { 
  if (cp != NULL){
    delete [] cp->heap;
    delete [] cp->posiciones;
    delete cp;
  };
};

/*
  Inserta 'elem' en 'cp' o, si ya estaba, actualiza su prioridad.
  La prioridad asociada a 'eĺem' queda en 'valor'.
  Si 'elem' no está en el rango 1..N no se hacen cambios.
  Devuelve 'cp'.
  No se debe dejar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(log N).
  'N' el parámetro pasado en crearCP.
 */
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp)  { 
  if ( (cp != NULL) && ((1 <= elem) && (elem <= (cp->cantMax))) ){

    if (estaEnCP(elem, cp)){
      actualizarPrioridad(elem, valor, cp);
    } else {
      insertarElemento(elem, valor, cp);
    };

  };
  return cp;
};

/*
  Devuelve 'true' si y solo si en 'cp' no hay elementos.
  El tiempo de ejecución en el peor casos es O(1).
 */
bool estaVaciaCP(TColaDePrioridad cp)  { 
  return ( (cp == NULL) || ((cp->cantAct) == 0) );
};

/*
  Devuelve el elemento prioritario de 'cp'.
  Precondición: !estaVaciaCP(cp).
  El tiempo de ejecución en el peor casos es O(1).
 */
nat prioritario(TColaDePrioridad cp)  {
  return ( (cp->heap[1]).elem );
};

/*
  Elimina de 'cp' el elemento prioritario.
  Libera la memoria asociada a ese elemento.
  Si estaVacioCP(cp) la operación no tiene efecto.
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) {
  if (!(estaVaciaCP(cp))) {
    eliminarPrimero(cp);
  };
  return cp;
};

/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnCP(nat elem, TColaDePrioridad cp) {
  return ( (cp != NULL) && ((1 <= elem) && (elem <= (cp->cantMax))) && ((cp->posiciones[elem]) != 0) );
};

/*
  Devuelve el valor de prioridad asociado a 'elem'.
  Precondición: estaEnCp(elem, cp).
  El tiempo de ejecución en el peor caso es O(1).
 */
double prioridad(nat elem, TColaDePrioridad cp){
  return  ((cp->heap[cp->posiciones[elem]]).valor) ;
};