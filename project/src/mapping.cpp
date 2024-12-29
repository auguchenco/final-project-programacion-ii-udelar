/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"



//    E S T R U C T U R A S   A U X I L I A R E S

typedef struct mLista* TMLista;
struct mLista {
  nat natural;
  double real;
  TMLista sig;
};

//    F I N   E S T R U C T U R A S   A U X I L I A R E S



struct _rep_mapping {
  nat cant;
  nat max;
  TMLista* tabla;
};



//    A U X I L I A R E S

/*    liberarMap*(
  Libera la estructura TMLista que se encuentra
  dentro de una estructura TMapping.
  */
void liberarLista(TMLista l){
  if (l!=NULL){
    liberarLista(l->sig);
    delete l;
  };
};

/*    asociarEnMap()
  Inserta al princpio de la TMLista l una nueva celda
  con su componente natural n y su componente real r.
  Devuelve lista.
  */
TMLista insertar(nat n, double r, TMLista l){
  TMLista nuevaCelda = new mLista;
  nuevaCelda->natural = n;
  nuevaCelda->real = r;
  nuevaCelda->sig = l;
  l = nuevaCelda;
  return l;
};

/*    desasociarEnMap()
  Remueve de la TMLista l la primer celda cuyo valor natural
  coincide con n.
  Si no lo encuentra no hace nada.
  Si la lista queda vacia l debe ser la lista vacia.
  Se retorna l.
  */
TMLista remover(nat n, TMLista l){
  if (l != NULL) {
    if ((l->natural) != n){
      l->sig = remover(n, l->sig);
    } else {  // l->natural == n
      TMLista remover = l;
      l = l->sig;
      delete remover;
    };
  };
  return l;
};

/*    esClaveEnMap()
  Devuelve true si y solo si exite al menos una celda
  cuyo componente natural es n.
  */
bool estaEnLista(nat n, TMLista l){
  while ((l != NULL) && ((l->natural) != n)) { l = l->sig; };
  return (l != NULL);
};

/*    valorEnMap()
  Retorna el valor real asociado a la primer celda cuyo valor
  natural es n.
  Precondicion: existe al menos una celda cuyo valor natural es n.
  */
double valorEnLista(nat n, TMLista l){
  while ((l->natural) != n) { l = l->sig; };
  return (l->real);
};

//    F I N   A U X I L I A R E S



TMapping crearMap(nat M) {
  TMapping map = new _rep_mapping;
  map->cant = 0;
  map->max = M;
  map->tabla = new TMLista[M+1];
  for (nat i=0; i<M; i++){
    map->tabla[i] = NULL;
  };
  map->tabla[M] = NULL;
  return map;
};

void liberarMap(TMapping map) {
  for (nat i=0; i < (map->max); i++){
    liberarLista(map->tabla[i]);
  };
  delete [] map->tabla;
  delete map;
};

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
  map->tabla[((clave % (map->max)))] = insertar(clave, valor, map->tabla[(clave % (map->max))]);
  map->cant++;
  return map;
};

TMapping desasociarEnMap(nat clave, TMapping map) {
  map->tabla[(clave % (map->max))] = remover(clave, map->tabla[(clave % (map->max))]);
  map->cant--;
  return map;
};

bool esClaveEnMap(nat clave, TMapping map) {
  return estaEnLista(clave, map->tabla[(clave % (map->max))]);
};

double valorEnMap(nat clave, TMapping map) {
  return valorEnLista(clave, map->tabla[(clave % (map->max))]);
};

bool estaLlenoMap(TMapping map) { return ((map->cant) == (map->max)); };
