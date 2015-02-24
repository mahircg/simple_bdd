#include "BDD_ID.hpp"



Node::operator std::string() const
{
	return to_string(static_cast<long long>(id));
}

void Node::setID(unsigned id)
{
	this->id = id;
}

unsigned Node::getID()
{
	return id;
}



ostream& operator<<(ostream& osObject,const BDD_ID &bddObj)
{
	osObject<<bddObj.name<<" -> "<<static_cast<string>(*(bddObj.low))<<"|"<<static_cast<string>(*(bddObj.high));
	return osObject;
}



Node::Node(unsigned id):id(id){};


BDD_ID::BDD_ID(string name,unsigned id):Node(id), name(name) {};

BDD_ID::BDD_ID(string name,unsigned id,Node* t,Node* e):Node(id), name(name) 
{
	low=e;
	high=t;
}


BDD_ID::BDD_ID(string name,unsigned id,Node& t,Node& e):Node(id), name(name) 
{
	low=&e;
	high=&t;
}

void BDD_ID::setLow(class Node& e)
{
	low=&e;
}

void BDD_ID::setHigh(class Node& t)
{
	high=&t;
}