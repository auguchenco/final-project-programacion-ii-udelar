/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"



//    E S T R U C T U R A S   A U X I L I A R E S

typedef struct cLista *TCLista;
struct cLista{
  TInfo info;
  TCLista sig;
};

//    F I N   E S T R U C T U R A S   A U X I L I A R E S



struct _rep_cola{
  nat cantidad;
  TCLista primero;
  TCLista ultimo;
};



//    A U X I L I A R E S

/*    liberarCola()
  Libera la estructura TLista que se incluye dentro
  de la estructura TCola.
  */
void liberarListaCola(TCLista l){
  if (l!=NULL){
    liberarListaCola(l->sig);
    liberarInfo(l->info);
    delete l;
  };
};

//    F I N   A U X I L I A R E S



TCola crearCola() {
  TCola nuevaCola = new _rep_cola;
  nuevaCola->cantidad = 0;
  nuevaCola->primero = NULL;
  nuevaCola->ultimo = NULL;
  return nuevaCola;
};

void liberarCola(TCola c){
  if (c!=NULL){
    liberarListaCola(c->primero);
    delete c;
  };
};

nat cantidadEnCola(TCola c){
  if (c == NULL) { return 0; }
  else { return (c->cantidad); };
};

TCola encolar(TInfo info, TCola c){
  if (c==NULL) { c = crearCola(); };
  TCLista nuevaLista = new cLista;
  nuevaLista->info = copiaInfo(info);
  nuevaLista->sig = NULL;
  if ((c->primero == NULL) && (c->ultimo == NULL) && (c->cantidad == 0)){
    c->primero = nuevaLista;
  } else {
    c->ultimo->sig = nuevaLista;
  };
  c->ultimo = nuevaLista;
  c->cantidad++;
  return c;
}

TInfo frente(TCola c) { return ((c->primero)->info); };

TCola desencolar(TCola c) {
  TCLista borrar = c->primero;
  c->primero = ((c->primero)->sig);
  c->cantidad--;
  if ((c->cantidad == 0) && (c->primero == NULL)){ c->ultimo = NULL; };
  liberarInfo(borrar->info);
  delete borrar;
  return c;
};
