#include "cpeer.h"

CPeer::CPeer(int query_port, int download_port, int keepAlive_port)
{
  m_query_port = query_port;
  m_download_port = download_port;
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
  int QuerySD = createServerSocket(m_query_port);
  int DownloadSD = createServerSocket(m_download_port);
  int KeepAliveSD = createServerSocket(m_keepAlive_port);

  std::thread(&CPeer::listenForClients,this,QuerySD,ACT_RCV_QUERY).detach();
  
  
}

void CPeer::listenForClients(int serverSD, char action)
{
  
}

void CPeer::iniClientBot()
{
  
}

void CPeer::opReadN(int clientSD)
{

}

void CPeer::opWriteN(int clientSD)
{

}

void CPeer::opN(int clientSD)
{

}

void CPeer::opReadL(int clientSD)
{

}

void CPeer::opWriteL(int clientSD)
{

}

void CPeer::opL(int clientSD)
{

}

void CPeer::opReadQ(int clientSD, string file_name)
{
 
}

void CPeer::opWriteQ(int clientSD, string file_name)
{
  
}

void CPeer::opQ(int clientSD, string file_name)
{
  opWriteQ(clientSD, file_name);
  opReadQ(clientSD, file_name);
}

void CPeer::opReadP(int clientSD)
{

}

void CPeer::opWriteP(int clientSD)
{

}

void CPeer::opP(int clientSD)
{

}

void CPeer::opReadKeep(int clientSD)
{

}

void CPeer::opWriteKeep(int clientSD)
{

}

//Server side

void CPeer::opNS(int clientSD)
{
  
}

string CPeer::opReadNS(int clientSD){
  
}

void CPeer::opWriteNS(int clientSD, string file_name){
  
}

void CPeer::opLS(int clientSD)
{
  
}

string CPeer::opReadLS(int clientSD){
  
}

void CPeer::opWriteLS(int clientSD, string file_name){
  
}

void CPeer::opQS(int clientSD)
{
  
}

string CPeer::opReadQS(int clientSD){
  
}

void CPeer::opWriteQS(int clientSD, string file_name){
  
}


void CPeer::opPS(int clientSD)
{
  
}

string CPeer::opReadPS(int clientSD){
  
}

void CPeer::opWritePS(int clientSD, string file_name){
  
}

void CPeer::opCS(int clientSD)
{
  
}

string CPeer::opReadCS(int clientSD){
  
}

void CPeer::opWriteCS(int clientSD, string file_name){
  
}


CPeer::~CPeer()
{
    //dtor
}
