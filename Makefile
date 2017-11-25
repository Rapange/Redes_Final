make: server.cpp main_server.cpp
	g++ server.cpp main_server.cpp -o main_server -std=c++11 -lpthread

make2: node.cpp slave.cpp main_slave.cpp
	g++ node.cpp slave.cpp main_slave.cpp -o main_slave -std=c++11 -lpthread

make3: client.cpp main_client.cpp
	g++ client.cpp main_client.cpp -o main_client -std=c++11 -lpthread
