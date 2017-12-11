#ifndef SLAVE_H
#define SLAVE_H

#include "red.h"
#include "node.h"


class Slave
{
    public:

  int m_n_port, m_l_port, m_q_port, m_p_port, m_c_port, m_s_port, m_keepAlive_port;

       int state;
       mutex mtx;
	int id;
	std::vector< std::vector< std::pair < std::string, int > > > m_ip_port;
  std::vector<int> m_available;
        std::vector< std::vector< int > > m_sockets;
	std::unordered_map<std::string, Node* > m_words;

        Slave(int n_port, int l_port, int q_port, int p_port, int c_port, int s_port, int keepAlive_port);
        virtual ~Slave();
        std::string intToStr(int num, int size);
	vector<string> mySplit(string line);

	void readAll();
	void connectAll();
	void readDB(string name, string name_syn);

        void iniServerBot();
	void listenForClients(int serverSD, char action);

        void iniClientBot();

        void iniSlaveCheckBot();
        int createClientSocket(int portNumber, string serverIP);
        int createServerSocket(int portNumber);


	void strToVec(std::vector<std::string>& formatted_string, std::string& normal_string);
	char addWord(std::string data, std::vector<std::string>& attributes);
	char addRelation(std::string data_from, std::string data_to);
	//Client side

        char opReadN(int clientSD);
        void opWriteN(int clientSD, string n_protocol);
	char opN(int clientSD, string n_protocol);

	char opReadL(int clientSD);
        void opWriteL(int clientSD, string word, string word2);
        char opL(int clientSD, string word, string word2);

	string opReadQ(int clientSD);
        void opWriteQ(int clientSD, string word, int depth, char get_attributes);
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

	string formatResult(string word, char get_attributes, int how_many);
	void doAllQuery(int clientSD, string word, int depth, char get_attributes);

	void opNS(int clientSD);
	void opReadNS(int clientSD, string& data, string& attributes);
	void opWriteNS(int clientSD, char is_successful);

	void opLS(int clientSD);
	void opReadLS(int clientSD, string& word, string& word2);
	void opWriteLS(int clientSD, char is_successful);

	void opQS(int clientSD);
	void opReadQS(int clientSD, string &word, int &depth, char &get_attributes);
	void opWriteQS(int clientSD, string result, char is_hoja);

	void opPS(int clientSD);
	void opReadPS(int clientSD, string &word, int &depth);
	void opWritePS(int clientSD, string words);

	void opCS(int clientSD);
	void opReadCS(int clientSD, string& word);
	void opWriteCS(int clientSD, char found);

        void opSS(int clientSD);
	void opReadSS(int clientSD);
	void opWriteSS(int clientSD);


};

#endif // CPEER_H
