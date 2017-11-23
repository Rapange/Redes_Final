#include "client.h"
#include <iostream>

int main(){
  int n_port, l_port, q_port, p_port, c_port, s_port, keepAlive_port;
  cin>>n_port>>l_port>>q_port>>p_port>>c_port>>s_port>>keepAlive_port;
  Client client(n_port,l_port,q_port,p_port,c_port,s_port,keepAlive_port);
  client.iniClientBot();
  return 0;
}
