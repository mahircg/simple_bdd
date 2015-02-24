#ifndef HPP_BDD_ID
#define HPP_BDD_ID

#include<iostream>
#include<string>

using namespace std;




/**
 * \class Node 
 * \brief Base class for DAG node
 * 
 * A node might be either a variable or a constant(such as terminal or leaf node)
 */
class Node
{
protected:
	unsigned id;
public:
	Node(unsigned);	
	void setID(unsigned);
	unsigned getID();
	virtual operator string() const;
};


/**
 * \class BDD_ID 
 * \brief This class is used for storing the BDD structure
 * 
 * Each node(except leaves) has its successors which are either variables or terminal nodes.
 */
class BDD_ID : public Node
{
	friend ostream& operator<<(ostream&,const BDD_ID&);
private:
	class Node *low,*high;
	string variable;
public:
	bool operator==(const BDD_ID&) const;
	bool operator!=(const BDD_ID&) const;
	BDD_ID(string,unsigned);
	BDD_ID(string,unsigned,Node*,Node*);
	BDD_ID(string,unsigned,Node&,Node&);
	void setLow(Node&);
	void setHigh(Node&);
};
#endif