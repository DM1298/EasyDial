#include "phone.hpp"

/* Construeix un telèfon a partir del seu número (num), el seu nom
(name) i el seu comptador de trucades (compt).
Es produeix un error si name no és un identificador legal. */


phone::phone(nat num, const string& name, nat compt) throw(error){
  try{
    for(unsigned int i=0; i < name.size(); i++){
      if(name[i] == DELETECHAR or name[i] == ENDCHAR or name[i] == ENDPREF){
        i = name.size();
        throw ErrNomIncorrecte;
      }
    }
    cont = compt;
    tlf = num;
    nombre = name;
  } catch(int error){
    std::cout << "ERROR: " << error << endl << "No s'ha creat el phone" << endl;
  }
}

phone::phone(const phone& T) throw(error){
    tlf = T.numero();
    nombre = T.nom();
    cont = T.frequencia();
}

phone& phone::operator=(const phone& T) throw(error){
  phone aux;
  aux.tlf = T.numero();
  aux.nombre = T.nom();
  aux.cont = T.frequencia();
  return aux;
}

phone::~phone() throw(){

}

nat phone::numero() const throw(){
  return tlf;
}

/* Retorna el nom associat al telèfon, eventualment l'string buit. */
string phone::nom() const throw(){
  return nombre;
}

/* Retorna el número de vegades que s'ha trucat al telèfon. */
nat phone::frequencia() const throw(){
  return cont;
}

phone& phone::operator++() throw(){
  cont++;
  return *this;
}

phone phone::operator++(int) throw(){
  phone aux(*this);
  cont++;
  return  aux;
}

bool phone::operator==(const phone& T) const throw(){
  return tlf == T.numero() and nombre == T.nom() and cont == T.frequencia();
}

bool phone::operator!=(const phone& T) const throw(){
  return !(*this == T);
}

bool phone::operator<(const phone& T) const throw(){
  return !(*this > T);
}

bool phone::operator>(const phone& T) const throw(){
  bool ret;
  unsigned int max;
  if(cont > T.frequencia()) ret = true;
  else if(cont < T.frequencia()) ret = false;
  else{
    if(nombre.size() > T.nom().size()){
      max = T.nom().size();
      ret = true;
    }else{
      max = nombre.size();
      ret = false;
    }
    for(unsigned int i=0 ; i < max ; i++){
      if(nombre[i] > T.nom()[i]){
        i = max;
        ret = true;
      }else if(nombre[i] < T.nom()[i]){
        i = max;
        ret = false;
      }
    }
  }
  return ret;
}

bool phone::operator<=(const phone& T) const throw(){
  return cont <= T.frequencia();
}

bool phone::operator>=(const phone& T) const throw(){
  return cont >= T.frequencia();
}
