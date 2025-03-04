#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){
  if(R.es_buit()) throw error(99);
  vector<phone> aux;
  R.dump(aux);
  arrel = new node;
  current = new node;
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
    if(D.arrel != NULL) arrel = copia_node(D.arrel);
    else throw error(98);

}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
  if(D.arrel == NULL) throw error(97);
  return *this;
}

easy_dial::~easy_dial() throw(){
  esborra_node(arrel);
}

string easy_dial::inici() throw(){
  pre.clear();
  pre = arrel->info;
  current = arrel;
  return pre;
}

string easy_dial::seguent(char c) throw(error){
  if(pre.empty()) throw error(ErrPrefixIndef);
  if (current->fe->info == c or current->fc->info == c or current->fd->info == c) {
    pre.push_back(c);
    if(current->fe->info == c) current = current->fe;
    if(current->fc->info == c) current = current->fc;
    if(current->fd->info == c) current = current->fd;

  }
  return pre;
}

string easy_dial::anterior() throw(error){
  if(!pre.empty()){
    current = retorna_node(arrel,pre,0);
    pre.erase(pre[pre.size()-1]);
  }else throw error(ErrNoHiHaAnterior);
  return pre;
}

nat easy_dial::num_telf() const throw(error){
  node *aux = arrel;;
  for(int i=0 ; i<pre.size() ; i++){
    if(pre[i] == aux->fe->info) aux = aux->fe;
    if(pre[i] == aux->fc->info) aux = aux->fc;
    if(pre[i] == aux->fd->info) aux = aux->fd;
  }
  if(aux->num == 0) throw error(ErrNoExisteixTelefon);
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
