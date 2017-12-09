#ifndef SERVER_H
#define SERVER_H

#include "red.h"
//Sizes
#define ACTION_SIZE 1
#define DATA_SIZE 3
#define ATTRIBUTE_LIST_SIZE 4
#define DATA_LIST_SIZE 4
#define RESPONSE_SIZE 4
#define ATTRIBUTE_SIZE 2
#define REDUNDANCE_SIZE 2
#define USE_SIZE 1
#define SUCCESS_SIZE 1
//Actions
#define ACT_SND_N 'N'
#define ACT_RCV_N 'n'
#define ACT_SND_L 'L'
#define ACT_RCV_L 'l'
#define ACT_SND_Q 'Q' //Receive query Action
#define ACT_RCV_Q 'q' //Send query Action
#define ACT_SND_P 'P'
#define ACT_RCV_P 'p'
#define ACT_SND_C 'C'
#define ACT_RCV_C 'c'

class Server
{
  public:
    int mainPort,checkPort;
    Server(int mainPort, int checkPort);
    virtual ~Server();
    void iniMasterCheckBot();
    void iniSlaveCheckBot();
    int createClientSocket(int portNumber, string serverIP);
    int createServerSocket(int portNumber);

	//Client side
		void opReadKeep(int clientSD); //Keep Alive operation
    void opWriteKeep(int clientSD);
	  void opKeep(int senderSD, int receiverSD);

	//Server side

};

#endif // CPEER_H
