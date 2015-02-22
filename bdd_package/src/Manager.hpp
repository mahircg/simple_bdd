/**
 * \class Manager
 *
 * \brief Public interface for BDD management
 * 
 * This class provides following functionalities
 * * Initialization and assignment of new variables/nodes
 * * Addition of variables/nodes into a BDD

#ifndef HPP_MANAGER
#define HPP_MANAGER

#include "BDD_ID.hpp"
#include<set>

using namespace std;

class Manager
{
private:
	//Not much here yet
public:
	Manager();
	~Manager();
	BDD_ID createVar(const string&);
	bool True(const BDD_ID&);
	bool false(const BDD_ID&);
	bool isVariable(const BDD_ID&);
	size_t topVar(const BDD_ID);
	BDD_ID coFactorTrue(const BDD_ID,const BDD_ID);
	BDD_ID coFactorFalse(const BDD_ID,const BDD_ID);
	BDD_ID coFactorTrue(const BDD_ID);
	BDD_ID coFactorFalse(const BDD_ID);
	BDD_ID ite (const BDD_ID,const BDD_ID,const BDD_ID);
	BDD_ID and2(const BDD_ID,const BDD_ID);
	BDD_ID or2(const BDD_ID,const BDD_ID);
	BDD_ID xor2(const BDD_ID,const BDD_ID);
	BDD_ID neg(const BDD_ID);
	BDD_ID nand2(const BDD_ID,const BDD_ID);
	BDD_ID nor2(const BDD_ID,const BDD_ID);
	string getTopVarName(const BDD_ID&);
	void findNodes(const BDD_ID&,set<BDD_ID>&);
	void findVars(const BDD_ID&,set<BDD_ID>&);

}

#endif