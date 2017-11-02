#ifndef CPEER_H
#define CPEER_H

#include "red.h"
#define ACTION_SIZE 1
#define FILE_NAME_SIZE 3
#define IP_LIST_SIZE 3
#define ACT_SND_N 'N'
#define ACT_RCV_N 'n'
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
	
        void opReadN(int clientSD, string word, string attributes);
        void opWriteN(int clientSD, string word, string attributes);
	void opN(int clientSD, string word, string attributes);

	void opReadL(int clientSD, string word, string word2, string attributes);
        void opWriteL(int clientSD, string word, string word2, string attributes);
	void opL(int clientSD, string word, string word2, string attributes);

	void opReadQ(int clientSD, string word, int depth, bool attributes);
        void opWriteQ(int clientSD, string word, int depth, bool attributes);
	void opQ(int clientSD, string word, int depth, bool attributes);

	void opReadP(int clientSD, string words, int depth, string attribute_name);
        void opWriteP(int clientSD, string words, int depth, string attribute_name);
	void opP(int clientSD, string words, int depth, string attribute_name);

	void opReadC(int clientSD, string word);
        void opWriteC(int clientSD, string word);
	void opC(int clientSD, string word);
	
	void opReadKeep(int clientSD); //Keep Alive operation
        void opWriteKeep(int clientSD);
	void opKeep(int clientSD);

	//Server side

	void opNS(int clientSD, string word, string attributes);
	string opReadNS(int clientSD, string word, string attributes);
	void opWriteNS(int clientSD, string word, string attributes);

	void opLS(int clientSD, string word, string word2, string attributes);
	string opReadLS(int clientSD, string word, string word2, string attributes);
	void opWriteLS(int clientSD, string word, string word2, string attributes);

	void opQS(int clientSD, string word, int depth, bool attributes);
	string opReadQS(int clientSD, string word, int depth, bool attributes);
	void opWriteQS(int clientSD, string word, int depth, bool attributes);

	void opPS(int clientSD, string words, int depth, string attribute_name);
	string opReadPS(int clientSD, string words, int depth, string attribute_name);
	void opWritePS(int clientSD, string words, int depth, string attribute_name);

	void opCS(int clientSD, string word);
	string opReadCS(int clientSD, string word);
	void opWriteCS(int clientSD, string word);
	
        

	
};

#endif // CPEER_H
