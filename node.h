#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>

class Node
{
  private:
    std::string data;
    std::vector<std::string> relations;
    std::vector<std::string> attributes;
  public:
    bool addRelation(std::string node, std::string relAttributes = "");
    string doQuery(std::string msgQuery, int deep);
    Node(std::string data, std::string relations, std::string attributes);
    ~Node();
};
#endif
