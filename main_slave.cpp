#include "slave.h"
#include <iostream>

int main(){
  int n_port;
  cout<<"Ingrese un puerto:";
  cin>>n_port;
  Slave slave(n_port,n_port+1,n_port+2,n_port+3,n_port+4,n_port+5,n_port+6);

  slave.iniServerBot();
  cout<<"Se inicio servidor."<<endl;
  cin>>n_port;
  slave.iniClientBot();
  return 0;
}
