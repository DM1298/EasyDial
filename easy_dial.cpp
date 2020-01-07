#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){
  vector<phone> aux;
  R.dump(aux);
  arrel = new node;
  nat freq, puls;
  freq = puls = 0;
  for(int i=0 ; i<aux.size() ; i++){
    puls += aux[i].frequencia();
    freq += (aux[i].frequencia() * i);
    arrel = insereix_paraula(arrel,0,aux[i].nom(),aux[i].numero(),aux[i].frequencia());
  }
  total_puls = puls/freq;
}

easy_dial::easy_dial(const easy_dial& D) throw(error){
  arrel = copia_node(D.arrel);
}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
  easy_dial aux(D);
  return aux;
}

easy_dial::~easy_dial() throw(){
  esborra_node(arrel);
}

string easy_dial::inici() throw(){
  pre.clear();
  pre = arrel->info;
  return pre;
}

string easy_dial::seguent(char c) throw(error){
  pre.push_back(c);
  return pre;
}

string easy_dial::anterior() throw(error){
  pre.pop_back();
}

nat easy_dial::num_telf() const throw(error){
  node *aux = arrel;;
  for(int i=0 ; i<pre.size() ; i++){
    if(pre[i] == aux->fe->info) aux = aux->fe;
    if(pre[i] == aux->fc->info) aux = aux->fc;
    if(pre[i] == aux->fd->info) aux = aux->fd;
  }
  return aux->num;
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
  node *aux = arrel;
  for(int i=0 ; i<pref.size() ; i++){
    if(pref[i] == aux->fe->info) aux = aux->fe;
    if(pref[i] == aux->fc->info) aux = aux->fc;
    if(pref[i] == aux->fd->info) aux = aux->fd;
  }
  string aux2 = "";
  result = retorna_noms(aux, result, aux2);

}

double easy_dial::longitud_mitjana() const throw(){
  return total_puls;
}
