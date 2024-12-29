/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
	TInfo info;
	TAbb left;
	TAbb right;
};



//    A U X I L I A R E S

/*    rotar()
  Aplica una rotacion simple en un arbol avl (o no).
  Creada unicamente para rotar(): ver informacion y
  precondiciones para mayor entendimiento.
  */
TAbb rotacionSimple(char tipo, TAbb abb){
  if (abb!=NULL){
    if ((tipo == 'L') && (abb->left != NULL)) { 
      TAbb hijo = abb->left;
      abb->left = hijo->right;
      hijo->right = abb;
      abb = hijo;
    } else if ((tipo == 'R') && (abb->right != NULL)) {
      TAbb hijo = abb->right;
      abb->right = hijo->left;
      hijo->left = abb;
      abb = hijo;
    };
  };
  return abb;
};

/*    rotar()
  Aplica una rotacion doble en un arbol avl (o no).
  Creada unicamente para rotar(): ver informacion y
  precondiciones para mayor entendimiento.
  */
TAbb rotacionDoble(char tipo, TAbb abb){
  if (abb!=NULL){
    if ((tipo == 'L') && (abb->left != NULL) && ((abb->left)->right != NULL)){
      TAbb hijo = abb->left;
      TAbb nieto = hijo->right;
      hijo->right = nieto->left;
      abb->left = nieto->right;
      nieto->left = hijo;
      nieto->right = abb;
      abb = nieto;
    } else if ((tipo == 'R') && (abb->right != NULL) && ((abb->right)->left != NULL)) {
      TAbb hijo = abb->right;
      TAbb nieto = hijo->left;
      hijo->left = nieto->right;
      abb->right = nieto->left;
      nieto->right = hijo;
      nieto->left = abb;
      abb = nieto;
    };
  };
  return abb;
};

//    F I N   A U X I L I A R E S



TAbb crearAbb() { return NULL; };

void liberarAbb(TAbb abb) {
	if (abb != NULL){
		liberarAbb(abb->left);
		liberarAbb(abb->right);
		liberarInfo(abb->info);
		delete (abb);
	};
};

bool esVacioAbb(TAbb abb) { return (abb == NULL); };

TAbb buscarSubarbol(nat clave, TAbb abb) {
	while ((!esVacioAbb(abb)) && (natInfo(abb->info) != clave)){
		if (natInfo(abb->info) > clave){
			abb = izquierdo(abb);
		} else {
			abb = derecho(abb);
		};
	};
	return abb;
};

TInfo raiz(TAbb abb) { return (abb->info); };

TAbb izquierdo(TAbb abb) { return (abb->left); };

TAbb derecho(TAbb abb) { return (abb->right); };

TInfo menorEnAbb(TAbb abb) {
	while (!esVacioAbb(izquierdo(abb))){
		abb = izquierdo(abb);
	};
	return raiz(abb);
};

TInfo mayorEnAbb(TAbb abb) {
	while (!esVacioAbb(derecho(abb))){
		abb = derecho(abb);
	};
	return raiz(abb);
};

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) {
	TAbb abb = new _rep_abb;
	abb->info = dato;
	abb->left = izq;
	abb->right = der;
	return abb;
};

TAbb insertarEnAbb(TInfo dato, TAbb abb) { 
	if (esVacioAbb(abb)){
		abb = consAbb(dato,NULL,NULL);
	} else if (natInfo(dato) < natInfo(raiz(abb))){
		abb->left = insertarEnAbb(dato, izquierdo(abb));
	} else if (natInfo(dato) > natInfo(raiz(abb))){
		abb->right = insertarEnAbb(dato, derecho(abb));
	};
	return abb;
};

TAbb removerDeAbb(nat clave, TAbb abb) {
	if (clave < natInfo(raiz(abb))){
		abb->left = removerDeAbb(clave,izquierdo(abb));
	} else if (clave > natInfo(raiz(abb))){
		abb->right = removerDeAbb(clave,derecho(abb));
	} else {        //  clave == natInfo(raiz(abb))
		if (esVacioAbb(izquierdo(abb))){
			TAbb remover = abb;
			abb = derecho(abb);
			liberarInfo(raiz(remover));
			delete remover;
		} else if (esVacioAbb(derecho(abb))){
			TAbb remover = abb;
			abb = izquierdo(abb);
			liberarInfo(raiz(remover));
			delete remover;
		} else {        //  abb->left,abb->right != NULL
			TInfo infoMayIzq = copiaInfo(mayorEnAbb(izquierdo(abb)));
			abb->left = removerDeAbb(natInfo(infoMayIzq), izquierdo(abb));
			liberarInfo(raiz(abb));
			abb->info = infoMayIzq;
		};
	};
	return abb;
};

TAbb copiaAbb(TAbb abb) {
	if (esVacioAbb(abb)){
		return crearAbb();
	} else {
		return consAbb(copiaInfo(raiz(abb)), copiaAbb(izquierdo(abb)), copiaAbb(derecho(abb)));
	};
};

TAbb rotar(nat clave, char tipo[2], TAbb abb) { 
  if (abb!=NULL) {
    //  Buscamos con recursion el nodo clave:
    if (clave < natInfo(abb->info)) { abb->left = rotar(clave, tipo, abb->left); }
    else if (clave > natInfo(abb->info)) { abb->right = rotar(clave, tipo, abb->right); }
    //  Si no encuentra el nodo clave no hace nada
    //  Si lo encuentra se pociciona en el y podemos trabajar tranquilamente
    //  gracias a la recurcion que nos permite pararnos en ese nodo y trabajar sin problemas
    //  ya que lo 're-asignamos' como 'hijo-modificado' a su nodo padre
    else { // clave == natInfo(abb->info)   |   Ahora podemos trabajar sobre abb tranquilamente, ya que es el nodo clave.
      if (tipo[0] == tipo[1]){
        abb = rotacionSimple(tipo[0], abb);
      } else {
        abb = rotacionDoble(tipo[0], abb);
      };
    };
  };
  return abb;
  return NULL;
};
