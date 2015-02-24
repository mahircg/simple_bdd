#include "BDD_ID.hpp"


bool Node::operator==(const BDD_ID& rhs) const
{
	return (this->variable==rhs->variable) && (this->left->id==rhs->left->id) && (this->right->id==rhs->right->id);
}

bool Node::operator!=(const BDD_ID& rhs) const
{
	return !(*this==rhs);
}


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
	osObject<<bddObj.variable<<" -> "<<static_cast<string>(*(bddObj.low))<<"|"<<static_cast<string>(*(bddObj.high));
	return osObject;
}



Node::Node(unsigned id):id(id){};


BDD_ID::BDD_ID(string variable,unsigned id):Node(id), variable(variable) {};

BDD_ID::BDD_ID(string variable,unsigned id,Node* t,Node* e):Node(id), variable(variable) 
{
	low=e;
	high=t;
}


BDD_ID::BDD_ID(string variable,unsigned id,Node& t,Node& e):Node(id), variable(variable) 
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