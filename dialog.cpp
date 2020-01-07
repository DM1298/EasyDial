#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input,vector<string>& answers, nat& numtelf) throw(){
  answers.push_back(easy.inici());
  for(nat i=1; i<input.size() ; i++){
    answers.push_back(easy.seguent(input[i]));
  }
  numtelf = easy.num_telf();
}
