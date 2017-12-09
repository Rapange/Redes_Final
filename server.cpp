#include "server.h"

Server::Server(int cpyMainPort,int cpyCheckPort)
{
  mainPort = cpyMainPort;
  checkPort = cpyCheckPort;
  ports.push_back(40001);
  ports.push_back(40003);
    //ctor
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

int Server::createClientSocket(int portNumber,std::string serverIP)
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

  struct timeval tv;
  tv.tv_sec = 15;        // 30 Secs Timeout
  tv.tv_usec = 0;        // Not init'ing this can cause strange errors
  setsockopt(SocketFD, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));

  if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    perror("connect failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  return SocketFD;
}

void Server::iniMasterCheckBot()
{
  for(int i=0;i<ports.size();i++)
  {
    int checkSD = createClientSocket(ports[i],"192.168.0.8");
    std::thread(&Server::opWriteKeep,this,checkSD).detach();
  }
  while(true){}
}

void Server::iniSlaveCheckBot()
{
  int checkSD = createServerSocket(checkPort);
  int ConnectFD = 0;
  ConnectFD = accept(checkSD, NULL, NULL);
  if(0 > ConnectFD)
  {
    perror("error accept failed");
    close(checkSD);
    exit(EXIT_FAILURE);
  }
  std::thread(&Server::opReadKeep,this,ConnectFD).detach();
  while (true) {}
}

void Server::opReadKeep(int clientSD)
{
  int n;
  char* message;
  message = new char[ACTION_SIZE+1];
  while(true){
    n = read(clientSD, message, ACTION_SIZE + 1);
    if (n < 0) perror("ERROR writing to socket");
    cout<<"Received Keep --"<<message<<"--"<<endl;
    if (n <= 0) {
      cout<<"fail"<<endl;
      break;
    }

    string confirm = "kR";
    n = write(clientSD,confirm.data(),confirm.size());
    if (n <= 0) {
      cout<<"fail"<<endl;
      break;
    }//perror("ERROR writing to socket");
  }
  shutdown(clientSD,SHUT_RDWR);
  close(clientSD);
}

void Server::opWriteKeep(int clientSD)
{
  int n;
  ssize_t timeout;
  char* protocol;
  protocol = new char[ACTION_SIZE+1];
  string message = "KT";
  cout<<"Ready Protocol"<<endl;
  while (true) {
    n = write(clientSD,message.data(),message.size());
    //if (n < 0) //perror("ERROR writing to socket");
    if (n <= 0) {
      cout<<"fail"<<endl;
      break;
    }
    cout<<"n = "<< n <<" ||Sended Keep"<<endl;

    n = read(clientSD, protocol, ACTION_SIZE + 1);
    //if (n > 0) perror("ERROR writing to socket");
    if (n <= 0) {
      cout<<"fail"<<endl;
      break;
    }
    cout<<"n = " << n <<" ||Received Keep --"<<protocol<<"--"<<endl;
    sleep(5);
  }
  shutdown(clientSD,SHUT_RDWR);
  close(clientSD);
}

void Server::opKeep(int senderSD, int receiverSD){
  opWriteKeep(senderSD);
  //opReadKeep(receiverSD);
}

//Server side

Server::~Server()
{
    //dtor
}
