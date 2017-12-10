#include "server.h"
#include <iostream>

int main(){
  int n_port, seconds;
  cout<<"Ingrese un puerto: ";
  cin>>n_port;
  cout<<" Ingrese max cantidad de segundos: "<<endl;
  cin>>seconds;
  Server server(n_port,n_port+1,n_port+2,n_port+3,n_port+4,n_port+5,n_port+6);
  server.m_seconds = seconds;
  server.iniServerBot();
  cout<<"Se inicio servidor."<<endl;
  cin>>n_port;
  server.iniClientBot();
  return 0;
}
