/* 4767749 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/mapping.h"



//    A U X I L I A R E S

/*    esAvl() , esPerfecto()
  Retorna el maximo entre dos naturales.
*/
nat max(nat a, nat b){
  if (a < b){
    return b;
  } else {
    return a;
  };
};

/*    esAvl() , esPerfecto()
  Retorna la altura de un arbol abb.
*/
nat alturaAbb(TAbb abb){
  if (esVacioAbb(abb)){
    return 0;
  } else {
    return 1+max(alturaAbb(izquierdo(abb)), alturaAbb(derecho(abb)));
  };
};

/*    avlMin()
  Creada unicamente con el fin de ser utilizada en alvMin.
  */
TAbb avlMinAux(nat h, TCola &cola){
  if (h == 0){ return NULL; }
  else if (h == 1){
    TInfo info = crearInfo( natInfo(frente(cola))+1, 0);
    cola = encolar( info, cola);
    liberarInfo(info);
    TAbb abb = consAbb( copiaInfo(frente(cola)) , NULL , NULL );
    cola = desencolar(cola);
    return abb;
  } else { // h > 1
    TAbb abbIzq = avlMinAux(h-1, cola);
    TInfo info = crearInfo( natInfo(frente(cola))+1, 0);
    cola = encolar( info, cola);
    liberarInfo(info);
    TInfo abbRaiz = copiaInfo(frente(cola));
    cola = desencolar(cola);
    TAbb abbDer = avlMinAux(h-2, cola);
    TAbb abb = consAbb(abbRaiz, abbIzq, abbDer);
    return abb;
  };
};

/*    crearBalanceado()
  Creada unicamente con el fin de ser utilizada en crearBalanceado.
  */
TAbb crearBalanceadoAux(TInfo *arreglo, nat ini, nat fin){
  if (ini == fin) {
    return consAbb(copiaInfo(arreglo[ini]),NULL,NULL);
  } else {
    nat act = ini + ((fin-ini)/2);
    TAbb izq, der;
    if (act == ini) {
      izq = NULL;
    } else { // ini < act
      izq = crearBalanceadoAux(arreglo, ini, act-1);
    };
    /*if (act == fin) {
      der = NULL;
    } else { // ini < act
      der = crearBalanceadoAux(arreglo, act+1, fin);
    };*/
    der = crearBalanceadoAux(arreglo, act+1, fin);
    return consAbb(copiaInfo(arreglo[act]), izq, der);
  };
};

/*    linealizacion()
  Concatena la cadena 'a' a cad.
  Retorna cad.
  La cadena 'a' queda igual solo cuando: ('a' no es vacia) && (cad es vacia).
  Si 'a' es vacia retorna cad, sea cad vacia o no.
  Si 'a' es no vacia y cad es vacia, entonces retorna 'a'.
  Si 'a' y cad son no vacias entonces las concatena de la siguiente forma:
  Toma todos los elementos de a y los agrega a cad.
  */
TCadena concatCadenas(TCadena a, TCadena cad){
  if (a == NULL){
		return cad;
  } else if (cad == NULL){
    return a;
	} else {

		//Capturamos la info del primer elemento de a, sera lo ultimo a insertar
		nat natural = natInfo(primeroEnCadena(a));
		double real = realInfo(primeroEnCadena(a));

		//Removemos el primer elemento de a
		a = removerDeCadena(natural, a);

		//Insertamos al inicio de cad la info eliminada, cad es la concatenacion del resto de a y cad.
		cad = insertarAlInicio(natural, real, concatCadenas(a,cad));

		//Retornamos cad
		return cad;
	};

};

/*    imprimirAbbGuiones()
  SOLO imprime una cantidad n de guiones.
  No hay saltos de linea ni espacios.
  Los guiones se imprimern de manera continua.
  Ej.:  imprimirGuiones(3)  ==  printf('---')
  */
void imprimirGuiones(nat n){
	for (nat i = 0; i<n; i++){
		printf("-");
	};
};

/*    imprimirAbb()
  Se creo con el unico fin de ser utilizada en imprimirAbb.
  Imprime un arbol de la forma que se especifica en imprimirAbb.
  El parametro 'cantGui' es la cantidad de guiones inicial que se van a
  imprimir junto con el primer elemento del arbol.
  Segun se decienda en el arbol se agrega un guion mas por nivel.
  Si cantGui = 0 entonces la raiz tendra 0 guiones, y sus hijos tendran un guion mas,
  sus nietos dos guiones mas, y asi suscesivamente.
  */
void imprimirAbbGuiones(nat cantGui, TAbb abb){
	if (!esVacioAbb(abb)){
		//Imprime rama dereha si la rama derecha es no vacia
		imprimirAbbGuiones(cantGui+1 ,derecho(abb));
		//Imprime raiz
		imprimirGuiones(cantGui);
		imprimirInfo(raiz(abb));
		printf("\n");
		//Imprime rama izquierda
		imprimirAbbGuiones(cantGui+1 ,izquierdo(abb));
	}; //Sino no imprime nada...
};

/*    caminoAscendente()
  Retorna la cantidad de elementos que hay en el TIterador it.
  Al final el actual en it queda indefinido.
  */
nat cantidadEnIterador(TIterador iter){
  reiniciarIterador(iter);
  nat cont = 0;
  while (estaDefinidaActual(iter)){
    cont++;
    avanzarIterador(iter);
  };
  return cont;
};

/*    imprimirPalabrasCortas()
  Este procedimiento auxiliar se creo con la finalidad de
  ser utilizada solo en el procedimiento: imprimirPalabrasCortas.
  Ver especificaciones de imprimirPalabrasCortas.
  */
void imprimir_palabras_cortas(ArregloChars prefijo, nat largo, nat k, TPalabras secuencia) {
  if (largo <= k) {  
    if ((letra(secuencia) == '\0')) {
      prefijo[largo] = '\0';
      printf("%s\n", prefijo);
    } else {
      prefijo[largo] = letra(secuencia);
      imprimir_palabras_cortas(prefijo, largo + 1, k, subarboles(secuencia));
    };
  };
  if (siguientes(secuencia) != NULL) {
    imprimir_palabras_cortas(prefijo, largo, k, siguientes(secuencia));
  };
};

/*    buscarFinPrefijo()
  Esta funcion fue creada solo para ser utilizada
  en la funcion buscarFinPrefijo.
  Ver especificaciones de buscarFinPrefijo.
  */
TPalabras buscar_fin_prefijo(ArregloChars prefijo, nat cont, TPalabras pal){
  if (prefijo[cont] == letra(pal)){

    if (prefijo[cont+1] == '\0'){
      return pal;
    } else {
      cont++;
      return buscar_fin_prefijo(prefijo, cont, subarboles(pal));
    };

  } else if (prefijo[cont] < letra(pal)){
    return NULL;
  
  } else {  //prefijo[cont] > letra(pal)
    if (siguientes(pal) == NULL){
      return NULL;
    } else {
      return buscar_fin_prefijo(prefijo, cont, siguientes(pal));
    };
  };
};

/*    reversoDelIterador()
  Esta funcion fue creada solo para ser utilizada
  en la funcion reversoDelIterador.
  Ver especificaciones de reversoDelIterador.
  */
TIterador reversoDeIteradorAux(TIterador iter) {
  if (!estaDefinidaActual(iter)){
    return crearIterador();
  }else{
    nat x = actualEnIterador(iter);
    avanzarIterador(iter);
    if (!estaDefinidaActual(iter)){
      TIterador reverso = crearIterador();
      agregarAIterador(x,reverso);
      return reverso;
    }else{
      TIterador reverso = reversoDeIteradorAux(iter);
      agregarAIterador(x,reverso);
      return reverso;
    };
  };
};

//    F I N   A U X I L I A R E S



bool esAvl(TAbb abb) {
  if (abb == NULL) { return true; }
  else {
    nat altL = alturaAbb(izquierdo(abb));
    nat altR = alturaAbb(derecho(abb));
    nat maxi = max(altL, altR);
    nat mini;
    if (altL == maxi) { mini = altR; }
    else { mini = altL; };
    return ((esAvl(izquierdo(abb)) && esAvl(derecho(abb))) && ((maxi-mini)<=1));
  };
};

TAbb avlMin(nat h) {
  TCola cola = crearCola();
  TInfo info = crearInfo(1, 0);
  cola = encolar( info, cola);
  liberarInfo(info);
  TAbb abb = avlMinAux(h, cola);
  liberarCola(cola);
  return abb;
};

TCadena filtradaOrdenada ( TCadena cad , TIterador it ) {

  reiniciarIterador(it);

  TCadena nuevaCadena = crearCadena();

  if ((cad != NULL) && (estaDefinidaActual(it))){

    TCadena inicioCadena = cad;

    TMapping map = crearMap(cantidadEnCadena(cad));



    do
    {

      nat natural = natInfo(primeroEnCadena(cad));
      double real = realInfo(primeroEnCadena(cad));

      if (!(esClaveEnMap(natural ,map))){
        if (!(estaLlenoMap(map))){
          map = asociarEnMap(natural, real, map);
        };
      
      } else { //Si es clave natural en map
        
        double valor = valorEnMap(natural, map);
        if (esClaveEnMap(natural, map)){
          map = desasociarEnMap(natural, map);
        };
        if (!(estaLlenoMap(map))){
          map = asociarEnMap(natural, valor+real, map);
        };

      };

      cad = cadenaSiguiente(cad);

    } while (cad != inicioCadena);



    while (estaDefinidaActual(it)) {

      nat actualEnIt = actualEnIterador(it);

      if (esClaveEnMap(actualEnIt, map)){
        nuevaCadena = insertarAlFinal(actualEnIt, valorEnMap(actualEnIt, map), nuevaCadena);
        map = desasociarEnMap(actualEnIt, map);
      };

      avanzarIterador(it);

    };


    liberarMap(map);

  };

  return nuevaCadena;

};

bool estaOrdenada(TCadena cad){
  if ((cad == NULL) || (cad == cadenaSiguiente(cad))){ return true; }
  else {
    TCadena ini = cad;
    nat act;
    do {
      act = natInfo(primeroEnCadena(cad));
      cad = cadenaSiguiente(cad);    
    } while ((cad!=ini) && (act<natInfo(primeroEnCadena(cad))));
    return (cad==ini);
  };
};

TCadena mezclaCadenas(TCadena cad1, TCadena cad2){
  
  if (cad1 == NULL) { return copiaCadena(cad2);}
  else if (cad2 == NULL) { return copiaCadena(cad1); }
  else { //cad1,cad2 != NULL

    TCadena cad = crearCadena();
    TCadena cad11 = copiaCadena(cad1);
    TCadena cad22 = copiaCadena(cad2);

    do
    {
      nat nat1 = natInfo(primeroEnCadena(cad11));
      nat nat2 = natInfo(primeroEnCadena(cad22));

      if (nat2 < nat1) {
        cad = insertarAlFinal(nat2, realInfo(primeroEnCadena(cad22)), cad);
        cad22 = removerPrimero(cad22);
      
      } else { // nat1 <= nat2
        cad = insertarAlFinal(nat1, realInfo(primeroEnCadena(cad11)), cad);
        cad11 = removerPrimero(cad11);
        if (nat1 == nat2) { cad22 = removerPrimero(cad22); };
      };
    } while ((cad11 != NULL) && (cad22 != NULL));

    //Este cambio solo se ve aca adentro, no se modifican ni cad11 ni cad 2
    if (cad11 == NULL) { cad11 = cad22; };

    while (cad11 != NULL) {
      cad = insertarAlFinal(natInfo(primeroEnCadena(cad11)), realInfo(primeroEnCadena(cad11)), cad);
      cad11 = removerPrimero(cad11);
    };
    
    return cad;
  };
  
};

TAbb crearBalanceado(TInfo *arreglo, nat n) {
  if (n == 0) { return crearAbb(); }
  else { return crearBalanceadoAux(arreglo, 0, n-1); };
};

TAbb unionAbbs(TAbb abb1, TAbb abb2){
  TCadena lin1 = linealizacion(abb1);
  TCadena lin2 = linealizacion(abb2);
  TCadena abbLineal = mezclaCadenas(lin1, lin2);
  liberarCadena(lin1);
  liberarCadena(lin2);
  nat cantAbbLineal = cantidadEnCadena(abbLineal);
  TInfo *arreglo = new TInfo[cantAbbLineal];
  for (nat i=0; i<cantAbbLineal; i++){
    arreglo[i] = copiaInfo(primeroEnCadena(abbLineal));
    abbLineal = removerPrimero(abbLineal);
  };
  liberarCadena(abbLineal);
  TAbb abb = crearBalanceado(arreglo, cantAbbLineal);
  for (nat i=0; i<cantAbbLineal; i++){
    liberarInfo(arreglo[i]);
  };
  delete [] arreglo;
  return abb;
};

TCola ordenadaPorModulo(nat p, TCadena cad){
  TCola cola = crearCola();
  if ((cad != NULL) && (p != 0)) {
    TCadena* restos = new TCadena[p];
    for (nat i=0; i<p; i++) { restos[i] = crearCadena(); };
    TCadena ini = cad;
    do {
      nat natural = natInfo(primeroEnCadena(cad));
      double real = realInfo(primeroEnCadena(cad));
      nat resto = natural%p;
      restos[resto] = insertarAlFinal(natural, real, restos[resto]);
      cad = cadenaSiguiente(cad);
    } while (cad != ini);
    for (nat i=0; i<p; i++){
      if (restos[i] != NULL){
        ini = restos[i];
        do {
          cola = encolar(primeroEnCadena(restos[i]), cola);
          restos[i] = removerPrimero(restos[i]);
        } while (restos[i] != NULL);
      };
    };
    delete [] restos;
  };
  return cola;
};

TPila menoresQueElResto(TCadena cad, nat cantidad){

  if ((cad==NULL) || (cantidad == 0)){ return (crearPila()); }
  else { // cad != NULL y cantidad != 0

    TPila pilaCad = crearPila();
    TCadena ini = cad;
    do
    {
      pilaCad = apilar(primeroEnCadena(cad), pilaCad);
      cad = cadenaSiguiente(cad);
    } while (cad != ini);

    TPila pilaElementos = crearPila();
    pilaElementos = apilar(cima(pilaCad), pilaElementos);
    pilaCad = desapilar(pilaCad);
    while (0 < cantidadEnPila(pilaCad)){
      if (natInfo(cima(pilaCad)) < natInfo(cima(pilaElementos))){
        pilaElementos = apilar(cima(pilaCad), pilaElementos);
      };
      pilaCad = desapilar(pilaCad);
    };
    liberarPila(pilaCad);

    TPila pilaNueva = crearPila();
    do {
      pilaNueva = apilar(cima(pilaElementos), pilaNueva);
      pilaElementos = desapilar(pilaElementos);
    } while (0 < cantidadEnPila(pilaElementos));
    liberarPila(pilaElementos);

    return pilaNueva;

  };
};

TCadena linealizacion(TAbb abb) {
	if (esVacioAbb(abb)){ return crearCadena(); }
	else {
		TCadena cad = linealizacion(derecho(abb));
		cad = insertarAlInicio(natInfo(raiz(abb)), realInfo(raiz(abb)), cad);
		cad = concatCadenas(linealizacion(izquierdo(abb)), cad);
		return cad;		
	};
};

void imprimirAbb(TAbb abb) {
	imprimirAbbGuiones(0, abb);
};

bool esPerfecto(TAbb abb) {
  if (esVacioAbb(abb)){
    return true;
  } else {
    return ((esPerfecto(izquierdo(abb)) && esPerfecto(derecho(abb))) && (alturaAbb(izquierdo(abb)) == alturaAbb(derecho(abb))));
  };
};

TAbb menores(double limite, TAbb abb) {
  if (esVacioAbb(abb)){
    return crearAbb();
  } else {
    TAbb izq = menores(limite, izquierdo(abb));
    TAbb der = menores(limite, derecho(abb));
    if (realInfo(raiz(abb)) < limite){
      TInfo info = copiaInfo(raiz(abb));
      return consAbb(info, izq, der);
    } else {
      if (esVacioAbb(izq)){
        return der;
      } else {
        TInfo info = copiaInfo(mayorEnAbb(izq));
        izq = removerDeAbb(natInfo(info), izq);
        return consAbb(info, izq, der);
      };
    };
  };
};

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {

  if (k == 0){ return crearIterador(); }
  else { TIterador iter;
    
    if (clave == natInfo(raiz(abb))){
      iter = crearIterador();
      agregarAIterador(clave, iter);

    } else {
      if (clave < natInfo(raiz(abb))) { iter = caminoAscendente(clave, k, izquierdo(abb)); }
      else { iter = caminoAscendente(clave, k, derecho(abb)); };

      if (cantidadEnIterador(iter) < k) { agregarAIterador(natInfo(raiz(abb)), iter); };
    };
    
    return iter;
  };
};

void imprimirPalabrasCortas(nat k, TPalabras palabras) {
  if ((palabras != NULL) && (subarboles(palabras) != NULL)){
    char prefijo[256];
    imprimir_palabras_cortas(prefijo, 0, k, subarboles(palabras));
  };
};

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
  if ((prefijo[0] != '\0') && (palabras != NULL) && (subarboles(palabras) != NULL)){
    return buscar_fin_prefijo(prefijo, 0,subarboles(palabras));
  } else {
    return NULL;
  };
};

TIterador reversoDeIterador(TIterador iter){
  reiniciarIterador(iter);
  return reversoDeIteradorAux(iter);
};
