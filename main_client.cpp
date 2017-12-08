#include "client.h"
#include <iostream>

int main(int argc, char* argv[]){
  int n_port = -10;
  vector<string> arguments;
  char action;
  action = argv[1][1];
  for(unsigned int i = 2; i < argc; i++){
      arguments.push_back(argv[i]);
  }
  //cout<<"Ingrese un puerto; ";
  //cin>>n_port;
  Client client(n_port,n_port+1,n_port+2,n_port+3,n_port+4,n_port+5,n_port+6);
  client.iniClientBot(action, arguments);
  return 0;
}
