#ifndef CPEER_H
#define CPEER_H

#include "red.h"
#define ACTION_SIZE 1
#define FILE_NAME_SIZE 3
#define CHUNK_LIST_SIZE 4
#define IP_LIST_SIZE 3
#define ACT_SND_JOIN 'J'
#define ACT_RCV_JOIN 'j'
#define ACT_SND_QUERY 'Q' //Receive query Action
#define ACT_RCV_QUERY 'q' //Send query Action

class CPeer
{
    public:
        //Size of the types of messages
        const unsigned int HEADER_SIZE = 1; //[action]..
        const unsigned int QUERY_SIZE = 3;  //[size][of][query]..
        //Posible actions
        //char ACT_SND_QUERY= 'Q'; //Send query  Action
	//char ACT_RCV_QUERY= 'q'; //Receive query Action
	
	int m_query_port;
	int m_download_port;
	int m_keepAlive_port;

        std::vector< std::string > lstPeersIp;
	std::map <std::string, std::vector<int> > m_num_chunks;
        
        CPeer(int query_port, int download_port, int keepAlive_port);
        virtual ~CPeer();

        std::string intToStr(int num, int size);

        
	
        void iniServerBot();
	void listenForClients(int serverSD, char action);
	
        void iniClientBot();
        int createClientSocket(int portNumber, string serverIP);
        int createServerSocket(int portNumber);
        
	//Client side
	
        void opReadN(int clientSD, string file_name);
        void opWriteN(int clientSD, string file_name);
	void opN(int clientSD, string file_name);

	void opReadL(int clientSD);
        void opWriteL(int clientSD);
	void opL(int clientSD);

	void opReadQ(int clientSD);
        void opWriteQ(int clientSD);
	void opQ(int clientSD);

	void opReadP(int clientSD);
        void opWriteP(int clientSD);
	void opP(int clientSD);

	void opReadC(int clientSD);
        void opWriteC(int clientSD);
	void opC(int clientSD);
	
	void opReadKeep(int clientSD); //Keep Alive operation
        void opWriteKeep(int clientSD);
	void opKeep(int clientSD);

	//Server side

	void opNS(int clientSD);
	string opReadNS(int clientSD);
	void opWriteNS(int clientSD, string file_name);

	void opLS(int clientSD);
	string opReadLS(int clientSD);
	void opWriteLS(int clientSD, string file_name);

	void opQS(int clientSD);
	string opReadQS(int clientSD);
	void opWriteQS(int clientSD, string file_name);

	void opPS(int clientSD);
	string opReadPS(int clientSD);
	void opWritePS(int clientSD, string file_name);

	void opCS(int clientSD);
	string opReadCS(int clientSD);
	void opWriteCS(int clientSD, string file_name);
	
        

	
};

#endif // CPEER_H
