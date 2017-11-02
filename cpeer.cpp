#include "cpeer.h"

CPeer::CPeer(int n_port, int l_port, int q_port, int p_port, int c_port, int keepAlive_port)
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
std::string CPeer::intToStr(int num, int size){
    std::string result;
    for(int i= 0; i < size; i++)
      result+='0';
    for(int i = size - 1; i >= 0; --i){
      result[i] = std::to_string(num%10)[0];
      num = num/10;
    }
    return result;
}





int CPeer::createServerSocket(int portNumber)
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

int CPeer::createClientSocket(int portNumber,std::string serverIP)
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

  Res = inet_pton(AF_INET, serverIP.data(), &stSockAddr.sin_addr);

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

void CPeer::iniServerBot()
{
  
  
  
}

void CPeer::listenForClients(int serverSD, char action)
{
  
}

void CPeer::iniClientBot()
{
  
}

void CPeer::opReadN(int clientSD, string word, string attributes)
{

}

void CPeer::opWriteN(int clientSD, string word, string attributes)
{

}

void CPeer::opN(int clientSD, string word, string attributes)
{

}

void CPeer::opReadL(int clientSD, string word, string word2, string attributes)
{

}

void CPeer::opWriteL(int clientSD, string word, string word2, string attributes)
{

}

void CPeer::opL(int clientSD, string word, string word2, string attributes)
{

}

void CPeer::opReadQ(int clientSD, string word, int depth, bool attributes)
{
 
}

void CPeer::opWriteQ(int clientSD, string word, int depth, bool attributes)
{
  
}

void CPeer::opQ(int clientSD, string word, int depth, bool attributes)
{
  opWriteQ(clientSD, word, depth, attributes);
  opReadQ(clientSD, word, depth, attributes);
}

void CPeer::opReadP(int clientSD, string words, int depth, string attribute_name)
{

}

void CPeer::opWriteP(int clientSD, string words, int depth, string attribute_name)
{

}

void CPeer::opP(int clientSD, string words, int depth, string attribute_name)
{

}

void CPeer::opReadC(int clientSD, string word){
}

void CPeer::opWriteC(int clientSD, string word){
}

void CPeer::opC(int clientSD, string word){
}

void CPeer::opReadKeep(int clientSD)
{

}

void CPeer::opWriteKeep(int clientSD)
{

}

void CPeer::opKeep(int clientSD){
}

//Server side

void CPeer::opNS(int clientSD, string word, string attributes)
{
  
}

void CPeer::opReadNS(int clientSD, string word, string attributes){
  
}

void CPeer::opWriteNS(int clientSD, string word, string attributes){
  
}

void CPeer::opLS(int clientSD, string word, string word2, string attributes)
{
  
}

void CPeer::opReadLS(int clientSD, string word, string word2, string attributes){
  
}

void CPeer::opWriteLS(int clientSD, string word, string word2, string attributes){
  
}

void CPeer::opQS(int clientSD, string word, int depth, bool attributes)
{
  
}

void CPeer::opReadQS(int clientSD, string word, int depth, bool attributes){
  
}

void CPeer::opWriteQS(int clientSD, string word, int depth, bool attributes){
  
}


void CPeer::opPS(int clientSD, string words, int depth, string attribute_name)
{
  
}

void CPeer::opReadPS(int clientSD, string words, int depth, string attribute_name){
  
}

void CPeer::opWritePS(int clientSD, string words, int depth, string attribute_name){
  
}

void CPeer::opCS(int clientSD, string word)
{
  
}

void CPeer::opReadCS(int clientSD, string word){
  
}

void CPeer::opWriteCS(int clientSD, string word){
  
}

CPeer::~CPeer()
{
    //dtor
}
