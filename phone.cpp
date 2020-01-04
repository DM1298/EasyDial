#include "phone.hpp"

/* Construeix un telèfon a partir del seu número (num), el seu nom
(name) i el seu comptador de trucades (compt).
Es produeix un error si name no és un identificador legal. */
phone::phone(nat num, const string& name, nat compt) throw(error){
  try{
    for(int i=0; i < name.size(); i++){
      if(name[i] == DELETECHAR or name[i] == ENDCHAR or name[i] == ENDPREF){
        i = name.size();
        throw "caracter ilegal";
      }
    }
    cont = compt;
    tlf = num;
    nombre = name;
  } catch(string error){
    std::cout << "ERROR: " << error << endl << "No s'ha creat el phone" << endl;
  }
}

phone::phone(const phone& T) throw(error){
    tlf = T.numero();
    nombre = T.nom();
    cont = T.frequencia();
}

phone& phone::operator=(const phone& T) throw(error){
  phone aux(T);
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
  if(cont > T.frequencia()) ret = true;
  else if(cont < T.frequencia()) ret = false;
  else{
    //TODO: Falta realizar la comparación sobre los nombre en caso de que sean  frquencias iguales.
  }
  return ret;
}

bool phone::operator<=(const phone& T) const throw(){
  return cont <= T.frequencia();
}

bool phone::operator>=(const phone& T) const throw(){
  return cont >= T.frequencia();
}
