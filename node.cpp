#include "node.h"
Node::Node(std::string data, std::vector<std::string> &attributes)
{
  m_data = data;
  m_attributes = attributes;
}

Node::Node(){
}

bool Node::isInRelations(std::string node){
  for(unsigned int i = 0; i < m_relations.size(); i++){
    if(m_relations[i] == node) return true;
  }
  return false;
}

bool Node::addRelation(std::string node)
{
  if(isInRelations(node)) return false;
  m_relations.push_back(node);
  return true;
}

std::string Node::doQuery(std::string msgQuery, int deep)
{

}


Node::~Node()
{
    //dtor
}
