/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

struct _rep_cadena {
  TCadena ant;
  TInfo info;
  TCadena sig;
};



//    A U X I L I A R E S

/*    liberarCeldas() , removerDeCadena()
  Libera la informacion de la primer celda de cadena.
  */
void liberarCelda(TCadena cel){
  if (cel!=NULL){
    liberarInfo(cel->info);
    delete cel;
  };
};

/*    liberarCadena()
  Libera la informacion de una cadena circular del tipo TCadena.
  Precondicion: (ini,fin != NULL) y (posicion(ini) <= posicion(fin))
  talque las posiciones sean continuas.
  Se debe poder llegar de ini a fin, siendo ini el inicio de la lista y fin el final.
  No se aplica a secciones individuales de la lista, se le plica a toda o nada.
  */
void liberarCeldas(TCadena ini, TCadena fin){
  while (ini != fin){
    TCadena borrar = ini;
    ini = ini->sig;
    liberarCelda(borrar);
  };
  //  ini == fin
  liberarCelda(ini);
};

/*    insertarAlInicio() , removerDeCadena()
  Conecta la celda 'a' con la cleda 'b'.
  Precondicion: a,b != NULL
  */
void conectarCeldas(TCadena a, TCadena b){
  a->sig = b;
  b->ant = a;
};

/*    infoCadena() , removerDeCadena()
  Selecciona la celda de la cadena cad
  cuyo TInfo tiene a natural como valor natural.
  Precondicion: estaEnCadena(natural,cad)
  */
TCadena seleccionarCelda(nat natural, TCadena cad){
  TCadena fin = cad->ant;
  while ((cad != fin) && (natural != natInfo(cad->info))){cad = cad->sig;};
  return cad;
};

//    F I N   A U X I L I A R E S



TCadena crearCadena() { return NULL; };

void liberarCadena(TCadena cad){
  if (cad != NULL){
    liberarCeldas(cad,cad->ant);
  };
  cad = NULL;
};

nat cantidadEnCadena(TCadena cad){
  if (cad == NULL){return 0;}
  else{
    TCadena fin = cad->ant;
    nat cont = 1;
    while (cad != fin){
      cad = cad->sig;
      cont++;
    };
    return cont;
  };
};

bool estaEnCadena(nat natural, TCadena cad){
  if (cad == NULL){return false;}
  else{
    TCadena fin = cad->ant;
    while ((cad != fin) && (natural != natInfo(cad->info))){cad = cad->sig;};
    return (cad != fin || natural == natInfo(cad->info));
  };
};

TCadena insertarAlInicio(nat natural, double real, TCadena cad){
  TCadena nueva = new _rep_cadena;
  nueva->info = crearInfo(natural,real);
  if (cad == NULL){
    conectarCeldas(nueva,nueva);
  }else{
    conectarCeldas(cad->ant,nueva);
    conectarCeldas(nueva,cad);
  };
  cad = nueva;
  return cad;
};

TInfo infoCadena(nat natural, TCadena cad){return ((seleccionarCelda(natural,cad))->info);};

TInfo primeroEnCadena(TCadena cad){return (cad->info);};

TCadena cadenaSiguiente(TCadena cad){
  if (cad != NULL) {cad = cad->sig;};
  return cad;
};

TCadena removerDeCadena(nat natural, TCadena cad){  
  //1 Celda
  if ((cad) == (cad->ant)){
    liberarCelda(cad);
    cad = NULL;
  //2+ Celdas
  } else {
    TCadena borrar = seleccionarCelda(natural,cad);
    if (borrar == cad){
      cad = cad->sig;
      conectarCeldas(borrar->ant,cad);
      liberarCelda(borrar);
    } else {
      conectarCeldas(borrar->ant, borrar->sig);
      liberarCelda(borrar);
    };
  };
  return cad;
};

void imprimirCadena(TCadena cad){
  if (cad != NULL){
    TCadena ini = cad;
    do {
      imprimirInfo(cad->info);
      cad = cad->sig;
    } while (cad!=ini);
  };
  printf("\n");
};

TCadena insertarAlFinal(nat natural, double real, TCadena cad){
  cad = insertarAlInicio(natural, real, cad);
  cad = cadenaSiguiente(cad);
  return cad;
};

TCadena removerPrimero(TCadena cad){
  cad = removerDeCadena(natInfo(primeroEnCadena(cad)),cad);
  return cad;
};

TCadena copiaCadena(TCadena cad){
  if (cad == NULL){ return crearCadena();}
  else {
    TCadena celda = cad;
    TCadena copia = crearCadena();
    do {
      copia = insertarAlFinal(natInfo(primeroEnCadena(celda)),realInfo(primeroEnCadena(celda)),copia);
      celda = cadenaSiguiente(celda);
    } while (celda != cad);
    return copia;
  };
};
