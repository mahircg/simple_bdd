#include "Manager.hpp"

using namespace std;


Manager::Manager()
{
      
	nextID=2;
}

Manager::~Manager()
{
        
}

BDD_ID Manager::createVar(const string& varName)
{
  nextID+=1;
  
  return BDD_ID(varName,nextID,True(),False());
	
}

BDD_ID Manager::True() const
{
  
  return BDD_ID(" ",2);
}

BDD_ID Manager::False() const
{
  return BDD_ID(" ",1);
}

bool Manager::isVariable(const BDD_ID& node)
{
	return (node.getID()==1 || node.getID()==2);
}

bool Manager::isConstant(const BDD_ID& node)
{
	return !isVariable(node);
}

size_t Manager::topVar(const BDD_ID& node)
{
	return 1;
}

BDD_ID Manager::coFactorTrue(const BDD_ID f,const BDD_ID x)
{
  return BDD_ID(" ",1);
}

BDD_ID Manager::coFactorFalse(const BDD_ID f,const BDD_ID x)
{
	return BDD_ID(" ",1);
}

BDD_ID Manager::coFactorTrue(const BDD_ID f)
{
        return BDD_ID(" ",1);
}

BDD_ID Manager::coFactorFalse(const BDD_ID f)
{
        return BDD_ID(" ",1);
}

BDD_ID Manager::ite(const BDD_ID f,const BDD_ID g,const BDD_ID h)
{
        return BDD_ID(" ",1);
}

BDD_ID Manager::and2(const BDD_ID f,const BDD_ID g)
{
        return BDD_ID(" ",1);
}

BDD_ID Manager::or2(const BDD_ID f,const BDD_ID g)
{
        return BDD_ID(" ",1);
}

BDD_ID Manager::xor2(const BDD_ID f,const BDD_ID g)
{
       return BDD_ID(" ",1);
}

BDD_ID Manager::nand2(const BDD_ID f,const BDD_ID g)
{
	return BDD_ID(" ",1);
}

BDD_ID Manager::nor2(const BDD_ID f,const BDD_ID g)
{
        return BDD_ID(" ",1);
}

BDD_ID Manager::neg(const BDD_ID f)
{
	return BDD_ID(" ",1);
}

string Manager::getTopVarName(const BDD_ID& f)
{
	return f;
}

void Manager::findNodes(const BDD_ID& f,set<BDD_ID>& list)
{
}

void Manager::findVars(const BDD_ID& f,set<BDD_ID>& list)
{
}

