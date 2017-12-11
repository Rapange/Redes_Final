#include "slave.h"
#include <iostream>

int main(){
  int n_port;
  string name, name_syn;
  cout<<"Ingrese un puerto:";
  cin>>n_port;
  cout<<"Ingrese nombres de las BD"<<endl;
  cin>>name>>name_syn;
  Slave slave(n_port,n_port+1,n_port+2,n_port+3,n_port+4,n_port+5,n_port+6);

  slave.readDB(name,name_syn);
  
  slave.iniServerBot();
  cout<<"Se inicio servidor."<<endl;
  cin>>n_port;
  slave.iniClientBot();
  return 0;
}
