/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"

struct _rep_colCadenas {
	TCadena* cad;
	nat tamanio;
};



TColCadenas crearColCadenas(nat tamanio) {
	if (tamanio == 0){ return NULL; }
  else {
    TColCadenas col = new _rep_colCadenas;
	  col->tamanio = tamanio;
    col->cad = new TCadena[tamanio];
    for (nat i=0; i<tamanio; i++){
		  col->cad[i] = crearCadena();
    };
	  return col;
  };
};

void liberarColCadenas(TColCadenas col){
	if (col!=NULL){
		for (nat i=0; i<col->tamanio; i++){
		  liberarCadena(col->cad[i]);
  	};
    delete [] (col->cad);
  	delete col;
	};
};

nat tamanioColCadenas(TColCadenas col){
	if (col != NULL){ return (col->tamanio); }
	else { return 0; };
};

TCadena cadenaDeColCadenas(nat pos, TColCadenas col){ return (col->cad[pos]); };

nat cantidadColCadenas(nat pos, TColCadenas col) { return (cantidadEnCadena(col->cad[pos])); };

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) { return estaEnCadena(natural, col->cad[pos]); };

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos, TColCadenas col) {
	(col->cad)[pos] = insertarAlInicio(natural, real, (col->cad)[pos]);
	return col;
};

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) { return infoCadena(natural, col->cad[pos]); };

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
	col->cad[pos] = removerDeCadena(natural, col->cad[pos]);
	return col;
};
