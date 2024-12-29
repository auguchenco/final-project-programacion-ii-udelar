/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"



//    E S T R U C T U R A S   A U X I L I A R E S

typedef struct iLista* TILista;
struct iLista{
  nat num;
  TILista sig;
};

//    F I N   E S T R U C T U R A S   A U X I L I A R E S



struct _rep_iterador {
  TILista ini;
  TILista posAct;
  TILista fin;
};



//    A U X I L I A R E S

/*    liberarIterador()
  Libera la estructura TLista que se
  encuentra dentro de una estructura TIterador.
  */
void liberarListaDesde(TILista elem){
  while (elem != NULL){
    TILista borrar = elem;
    elem = elem->sig;
    delete borrar;
  };
  /*if (elem != NULL){
    liberarListaDesde(elem->sig);
    delete elem;
  };*/
};

/*		agregarAlIterador()
	Devuelve true si y solo si iter esta vacio.
	*/
bool esVacioIter(TIterador iter) {
	return ((iter == NULL) || ((iter->ini) == NULL) || ((iter->fin) == NULL));
};
//    F I N   A U X I L I A R E S




TIterador crearIterador(){
  TIterador nuevo = new _rep_iterador;
  nuevo->ini = NULL;
  nuevo->posAct = NULL;
  nuevo->fin = NULL;
  return nuevo;
};

void liberarIterador(TIterador iter){
  if (iter!=NULL){
    liberarListaDesde(iter->ini);
    delete iter;
  };
};

bool estaDefinidaActual(TIterador iter){
  return ((iter != NULL) && (iter->posAct != NULL));
};

void agregarAIterador(nat elem, TIterador const iter){
  //	Creamos la nueva celda donde almacenaremos el nuevo elem
  TILista nuevo = new iLista;
  nuevo->num = elem;
  nuevo->sig = NULL;

	//	Almacenamos la casilla final de iter
	TILista finAnt = iter->fin;

	//	Le indicamos el final a iter
	iter->fin = nuevo;

	//	Ahora tenemos que conectar el final de la cadena que es finAnt con la nueva cadena
  if (esVacioIter(iter)) {	//	Aqui iter es vacio
    iter->ini = nuevo;
  } else {
    finAnt->sig = nuevo;
  };
};

void reiniciarIterador(TIterador const iter){
  if ((iter!=NULL) && ((iter->ini)!=NULL)){
    iter->posAct = iter->ini;
  };
};

void avanzarIterador(TIterador const iter){
  if (estaDefinidaActual(iter)){
    iter->posAct = (iter->posAct)->sig;
  };
};

nat actualEnIterador(TIterador iter){return ((iter->posAct)->num);};
