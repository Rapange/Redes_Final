#include "server.h"

Server::Server(int n_port, int l_port, int q_port, int p_port, int c_port, int keepAlive_port)
{
  m_n_port = n_port;
  m_l_port = l_port;
  m_q_port = q_port;
  m_c_port = c_port;
  m_p_port = p_port;
  m_keepAlive_port = keepAlive_port;
  //ctor
}

//Transforms an int to a sized string e.g., intToStr(21,4) => 0021, intToStr(9,3) => 009
std::string Server::intToStr(int num, int size){
    std::string result;
    for(int i= 0; i < size; i++)
      result+='0';
    for(int i = size - 1; i >= 0; --i){
      result[i] = std::to_string(num%10)[0];
      num = num/10;
    }
    return result;
}

int Server::createServerSocket(int portNumber)
{
    vector<unsigned int> holder;
    struct sockaddr_in stSockAddr;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int ConnectFD = 0;

    if(-1 == SocketFD)
    {
      perror("can not create socket");
      exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(portNumber);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;

    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("error bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    if(-1 == listen(SocketFD, 10))
    {
      perror("error listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    return SocketFD;

    /*while(true)
    {
      ConnectFD = accept(SocketFD, NULL, NULL);

      if(0 > ConnectFD)
      {
        perror("error accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
    }

    close(SocketFD);
    return 0;*/
}

int Server::createClientSocket(int portNumber,std::string ServerIP)
{
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  int n, Res;

  if (-1 == SocketFD)
  {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }

  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(portNumber);

  Res = inet_pton(AF_INET, ServerIP.data(), &stSockAddr.sin_addr);

  if (0 > Res)
  {
    perror("error: first parameter is not a valid address family");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  else if (0 == Res)
  {
    perror("char string (second parameter does not contain valid ipaddress");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }

  if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    perror("connect failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  return SocketFD;
}

void Server::iniServerBot()
{



}

void Server::listenForClients(int ServerSD, char action)
{

}

void Server::iniClientBot()
{

}

void Server::opReadN(int clientSD, string word, string attributes)
{

}

void Server::opWriteN(int clientSD, string word, string attributes)
{

}

void Server::opN(int clientSD, string word, string attributes)
{

}

void Server::opReadL(int clientSD, string word, string word2, string attributes)
{

}

void Server::opWriteL(int clientSD, string word, string word2, string attributes)
{

}

void Server::opL(int clientSD, string word, string word2, string attributes)
{

}

void Server::opReadQ(int clientSD, string word, int depth, bool attributes)
{

}

void Server::opWriteQ(int clientSD, string word, int depth, bool attributes)
{

}

void Server::opQ(int clientSD, string word, int depth, bool attributes)
{
  opWriteQ(clientSD, word, depth, attributes);
  opReadQ(clientSD, word, depth, attributes);
}

void Server::opReadP(int clientSD, string words, int depth, string attribute_name)
{

}

void Server::opWriteP(int clientSD, string words, int depth, string attribute_name)
{

}

void Server::opP(int clientSD, string words, int depth, string attribute_name)
{

}

void Server::opReadC(int clientSD, string word){
}

void Server::opWriteC(int clientSD, string word){
}

void Server::opC(int clientSD, string word){
}

void Server::opReadKeep(int clientSD)
{

}

void Server::opWriteKeep(int clientSD)
{

}

void Server::opKeep(int clientSD){
}

//Server side

void Server::opNS(int clientSD, string word, string attributes)
{

}

void Server::opReadNS(int clientSD, string word, string attributes){

}

void Server::opWriteNS(int clientSD, string word, string attributes){

}

void Server::opLS(int clientSD, string word, string word2, string attributes)
{

}

void Server::opReadLS(int clientSD, string word, string word2, string attributes){

}

void Server::opWriteLS(int clientSD, string word, string word2, string attributes){

}

void Server::opQS(int clientSD, string word, int depth, bool attributes)
{

}

void Server::opReadQS(int clientSD, string word, int depth, bool attributes){

}

void Server::opWriteQS(int clientSD, string word, int depth, bool attributes){

}


void Server::opPS(int clientSD, string words, int depth, string attribute_name)
{

}

void Server::opReadPS(int clientSD, string words, int depth, string attribute_name){

}

void Server::opWritePS(int clientSD, string words, int depth, string attribute_name){

}

void Server::opCS(int clientSD, string word)
{

}

void Server::opReadCS(int clientSD, string word){

}

void Server::opWriteCS(int clientSD, string word){

}

Server::~Server()
{
    //dtor
}
