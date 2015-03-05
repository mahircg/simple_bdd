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
  BDD_ID* low  = False();
  BDD_ID* high = True();
  BDD_ID tmp(varName,nextID,high,low);
  pair<BDD_ID,unsigned> elem(tmp,nextID);
  uniqueTable.insert(elem);
  return tmp;
	
}

BDD_ID* Manager::True() const
{
  return new BDD_ID(" ",2);
}

BDD_ID* Manager::False() const
{
  return new BDD_ID(" ",1);
}

bool Manager::isVariable(const BDD_ID& node)
{
	return (node.getID()!=1 && node.getID()!=2);
}

bool Manager::isConstant(const BDD_ID& node)
{
	return !isVariable(node);
}

size_t Manager::topVar(const BDD_ID& node) // Root Node Id
{
	return (unsigned)node;
}

BDD_ID Manager::coFactorTrue(const BDD_ID f,const BDD_ID x)
{
	// Base Case
	if (f.getID() < x.getID()){
		return x;	
	}
	else if (isConstant(f)){
		return f;
	}
	else if (f.getID() == x.getID()){
		return *f.getHigh;
	}
	// Recursive Case
	else{
		BDD_ID RHH = coFactorTrue(*f.getHigh(),x);
		BDD_ID RLL = coFactorTrue(*f.getLow(),x);
		if (RHH == RLL){
			return RHH;		
		}
		nextID += 1;
		BDD_ID tmp((string)x,nextID,RHH,RLL);
		pair<BDD_ID,unsigned> elem(tmp,nextID);
		//it = uniqueTable.find(elem);
		//if (it == 0){
		//	uniqueTable.insert(elem);
		//}
		return tmp;	
	}
}

BDD_ID Manager::coFactorFalse(const BDD_ID f,const BDD_ID x)
{
	// Base Case
	if (f.getID() < x.getID()){
		return x;	
	}
	else if (isConstant(f)){
		return f;
	}
	else if (f.getID() == x.getID()){
		return *f.getLow;
	}
	// Recursive Case
	else{
		BDD_ID RHH = coFactorFalse(*f.getHigh(),x);
		BDD_ID RLL = coFactorFalse(*f.getLow(),x);
		if (RHH == RLL){
			return RLL;		
		}
		nextID += 1;
		BDD_ID tmp((string)x,nextID,RHH,RLL);
		pair<BDD_ID,unsigned> elem(tmp,nextID);
		//it = uniqueTable.find(elem);
		//if (it == 0){
		//	uniqueTable.insert(elem);
		//}
		return tmp;	
	}
}

BDD_ID Manager::coFactorTrue(const BDD_ID f) // T CoFactor of f
{
	if (isConstant(f)){
		return f;
	}
	
	if ((f.getLow())->getID() == (f.getHigh())->getID() == f.getID()){
		return f;
	}
	return *f.getHigh();
}

BDD_ID Manager::coFactorFalse(const BDD_ID f) // E CoFactor of f
{
	if (isConstant(f)){
		return f;
	}
	
	if ((f.getLow())->getID() == (f.getHigh())->getID() == f.getID()){
		return f;
	}
	return *f.getLow();

}

BDD_ID Manager::ite(const BDD_ID f,const BDD_ID g,const BDD_ID h)
{  	
	// Terminal Cases of Recursion
	if (f==*True()){
		return g;	
	}
	else if (f==*False()){
		return h;
	}
	else if ((g==*True())&&(h==*False())){
		return f;
	}
	else if (g==h){
		return f;	
	}
	else if ((g==*False())&&(h==*True())){
		return neg(f);
	}
	else {
		BDD_ID x=topVar(f);
      		BDD_ID t=ite(coFactorTrue(f,x),coFactorTrue(g,x),coFactorTrue(h,x));
      		BDD_ID e=ite(coFactorFalse(f,x),coFactorFalse(g,x),coFactorFalse(h,x));
      		if(t==e)
			return t;
      		nextID += 1;
      		BDD_ID tmp((string)x,nextID,t,e);
      		pair<BDD_ID,unsigned> elem(tmp,nextID);
      		uniqueTable.insert(elem);
      		return tmp;	
	}

}

BDD_ID Manager::and2(const BDD_ID f,const BDD_ID g)
{
  return ite(f,g,*False());
}

BDD_ID Manager::or2(const BDD_ID f,const BDD_ID g)
{
  return ite(f,*True(),g);
}

BDD_ID Manager::xor2(const BDD_ID f,const BDD_ID g)
{
  return ite(f,neg(g),g);
}

BDD_ID Manager::nand2(const BDD_ID f,const BDD_ID g)
{
  return ite(f,neg(g),*True());
}

BDD_ID Manager::nor2(const BDD_ID f,const BDD_ID g)
{
  return ite(f,*False(),neg(g));
}

BDD_ID Manager::neg(const BDD_ID f)
{
  return ite(f,*False(),*True());
}

string Manager::getTopVarName(const BDD_ID& f)
{
  //string() operator overloaded for BDD_ID,so statement below is valid
  return f;
}

void Manager::findNodes(const BDD_ID& f,set<BDD_ID>& list)
{
}

void Manager::findVars(const BDD_ID& f,set<BDD_ID>& list)
{
}
