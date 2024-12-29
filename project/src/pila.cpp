/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"



//    F I N   E S T R U C T U R A S   A U X I L I A R E S

typedef struct pLista *TPLista;
struct pLista{
  TInfo info;
  TPLista sig;
};

//    F I N   E S T R U C T U R A S   A U X I L I A R E S



struct _rep_pila{
  TPLista cima;
  nat cantidad;
};



//    A U X I L I A R E S

/*    liberarPila()
  Libera la estructura TPLista que
  se encuentra dentro de una estructura TPila.
  */
void liberarLista(TPLista l){
  if (l!=NULL){
    liberarLista(l->sig);
    liberarInfo(l->info);
    delete l;
  };
};

//    F I N   A U X I L I A R E S



TPila crearPila(){
  TPila pila = new _rep_pila;
  pila->cima = NULL;
  pila->cantidad = 0;
  return pila;
};

void liberarPila(TPila p){
  if (p!=NULL){
    liberarLista(p->cima);
    delete p;
  };
};

nat cantidadEnPila(TPila p){
  if (p == NULL) { return 0; }
  else { return (p->cantidad); };
};

TPila apilar(TInfo info, TPila p){
  if (p == NULL) { p = crearPila(); };
  TPLista nuevaLista = new pLista;
  nuevaLista->info = copiaInfo(info);
  nuevaLista->sig = p->cima;
  p->cima = nuevaLista;
  p->cantidad++;
  return p;
};

TInfo cima(TPila p) { return ((p->cima)->info); };

TPila desapilar(TPila p) {
  TPLista borrar = p->cima;
  p->cima = ((p->cima)->sig);
  p->cantidad--;
  liberarInfo(borrar->info);
  delete borrar;
  return p;
};