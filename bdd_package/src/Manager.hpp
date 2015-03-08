/**
 * \class Manager
 *
 * \brief Public interface for BDD management
 *
 * This class provides following functionalities
 * * Initialization and assignment of new variables/nodes
 * * Addition of variables/nodes into a BDD
 */

#ifndef HPP_MANAGER
#define HPP_MANAGER

#include<set>
#include<unordered_map>
#include<string>
#include"BDD_ID.hpp"

using namespace std;

typedef unordered_map<BDD_ID,unsigned,BDD_Hash> uniqueTableType;

class Manager
{
private:
	unsigned nextID;
	const unsigned low=1;
	const unsigned high=2;
	uniqueTableType uniqueTable;

public:
	Manager();
	~Manager();
	unsigned createVar(const string&);
	unsigned True() const;
	unsigned False() const;
	bool isVariable(const unsigned&);
	bool isConstant(const unsigned&);
	unsigned topVar(const unsigned&);
	unsigned coFactorTrue(const unsigned,const unsigned);
	unsigned coFactorFalse(const unsigned,const unsigned);
	unsigned coFactorTrue(const unsigned);
	unsigned coFactorFalse(const unsigned);
	unsigned ite (const unsigned,const unsigned,const unsigned);
	unsigned and2(const unsigned,const unsigned);
	unsigned or2(const unsigned,const unsigned);
	unsigned xor2(const unsigned,const unsigned);
	unsigned neg(const unsigned);
	unsigned nand2(const unsigned,const unsigned);
	unsigned nor2(const unsigned,const unsigned);
	string getTopVarName(const unsigned&);
	void findNodes(const unsigned&,set<unsigned>&);
	void findVars(const unsigned&,set<unsigned>&);
  void printTable() const;

};

#endif
