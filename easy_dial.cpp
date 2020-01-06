#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){
  vector<phone> aux;
  R.dump(aux);
  arrel = new node;
  for(int i=0 ; i<aux.size() ; i++){
    arrel = insereix_paraula(arrel,0,aux[i].nom(),aux[i].numero());
  }
}
