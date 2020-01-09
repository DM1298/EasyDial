#include "call_registry.hpp"

call_registry::call_registry() throw(error){
  reg.clear();
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){
  for(unsigned int i=0 ; i < R.reg.size() ; i++ ){
    reg.push_back(R.reg[i]);
  }/*
  for(unsigned int i=0 ; i < R.backup.size() ; i++ ){
    backup.push_back(R.backup[i]);
  }
  */
}

call_registry& call_registry::operator=(const call_registry& R) throw(error){
  //call_registry aux(R);
  return *this;
}
call_registry::~call_registry() throw(){

}

void call_registry::registra_trucada(nat num) throw(error){
  if(!reg.empty()){
    bool trobat = false;
    for(int i=0 ; i < reg.size() ; i++){
      if( reg[i].numero() == num ){
        reg[i]++;
        trobat == true;
        i = reg.size();
      }
    }
    if(!trobat){
      phone aux(num,"",1);
      phone aux2(0,"",0);
      for(int i=0 ; i<reg.size() ; i++){
        if((reg[i].numero() > num) and !trobat){
          trobat = true;
        }
        if(trobat){
          aux2 = reg[i];
          reg[i] = aux;
          aux = aux2;
        }
      }
      reg.push_back(aux);
    }
  }else{
    phone aux(num,"",1);
    reg.push_back(aux);
  }
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){
  bool trobat = false;
  for(int i=0 ; i < reg.size() ; i++){
    if( reg[i].numero() == num ){
      phone aux(num,name,reg[i].frequencia());
      trobat == true;
      reg[i] = aux;
    }
  }
  if(!trobat){
    phone aux(num,"",1);
    phone aux2(0,"",0);
    for(int i=0 ; i<reg.size() ; i++){
      if(reg[i].numero() > num and !trobat){
        trobat = true;
      }
      if(trobat){
        aux2 = reg[i];
        reg[i] = aux;
        aux = aux2;
      }
    }
    reg.push_back(aux);
  }
}

void call_registry::elimina(nat num) throw(error){
  bool trobat = false;
  for(int i=0 ; i < reg.size() ; i++){
    if( reg[i].numero() == num ){
      trobat == true;
    }
    if(trobat and i != reg.size()-1){
      reg[i] = reg[i+1];
    }
  }
  if(trobat)reg.erase(reg.begin()+reg.size()-1);
  else throw error(ErrNumeroInexistent);
}

/* Retorna cert si i només si el call_registry conté un
telèfon amb el número donat. */
bool call_registry::conte(nat num) const throw(){
  bool trobat = false;
  for(int i=0 ; i < reg.size() ; i++){
    if( reg[i].numero() == num ){
      trobat == true;
      i = reg.size();
    }
  }
  return trobat;
}

/* Retorna el nom associat al número de telèfon que s'indica.
Aquest nom pot ser l'string buit si el número de telèfon no
té un nom associat. Es produeix un error si el número no està en
el call_registry. */
string call_registry::nom(nat num) const throw(error){
  string ret;
  for(int i=0 ; i < reg.size() ; i++){
    if( reg[i].numero() == num ){
      ret = reg[i].nom();
      i = reg.size();
    }
  }
  return ret;
}

/* Retorna el comptador de trucades associat al número de telèfon
indicat. Aquest número pot ser 0 si no s'ha efectuat cap trucada a
aquest número. Es produeix un error si el número no està en el
call_registry. */
nat call_registry::num_trucades(nat num) const throw(error){
  nat ret;
  bool trobat=false;
  for(int i=0 ; i < reg.size() ; i++){
    if( reg[i].numero() == num ){
      ret = reg[i].frequencia();
      i = reg.size();
      trobat=true;
    }
  }
  if(!trobat) throw error(ErrNumeroInexistent);
  return ret;
}

/* Retorna cert si i només si el call_registry està buit. */
bool call_registry::es_buit() const throw(){
  return reg.empty();
}

/* Retorna quants números de telèfon hi ha en el call_registry. */
nat call_registry::num_entrades() const throw(){
  return reg.size();
}

void call_registry::dump(vector<phone>& V) const throw(error){
  if(!reg.empty()){
    bool final = false;
    int i,j;
    i = j = 0;
    vector<phone> aux(V);
    V.clear();
    if(V.empty() and (reg.size()==1) ) V.push_back(reg[0]);
    else{
      while (!final) {
        if(reg[i] < aux[j]){
          V.push_back(reg[i]);
          i++;
        }else{
          V.push_back(aux[j]);
          j++;
        }
        if(reg[i] == V.back() or aux[j] == V.back()) throw error(ErrNomRepetit);
        if(aux.size() == 0){
          if(i == (reg.size()-1) and j == (aux.size())) final = true;
        }
        if(reg.size() == 0){
          if(i == (reg.size()) and j == (aux.size()-1)) final = true;
        }
        if(i == (reg.size()-1) and j == (aux.size()-1)) final = true;
      }
    }
  }
}
