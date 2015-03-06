#include "Manager.hpp"

using namespace std;


Manager::Manager()
{
      
	nextID=2;
	low=new BDD_ID("F",1);
	high=new BDD_ID("T",2);

}

Manager::~Manager()
{
  	delete low;
  	delete high;

}

BDD_ID Manager::createVar(const string& varName)
{
  	nextID+=1;

  	BDD_ID tmp(varName,nextID,True(),False());
  	pair<BDD_ID,unsigned> elem(tmp,nextID);
  	uniqueTable.insert(elem);
  	return tmp;
	
} 
 
BDD_ID* Manager::True() const 
{ 
  	return high; 
} 
 
BDD_ID* Manager::False() const 
{ 
  	return low; 
} 
 
bool Manager::isVariable(const BDD_ID& node) 
{ 
  	return ((unsigned)node!=1 && (unsigned)node!=2); 
} 
 
bool Manager::isConstant(const BDD_ID& node) 
{ 
	return !isVariable(node); 
} 
 
BDD_ID Manager::topVar(const BDD_ID& node) // Root Node Id 
{ 
  	return node; 
} 
 
BDD_ID Manager::coFactorTrue(const BDD_ID f,const BDD_ID x) 
{ 

      	if((unsigned)x==(unsigned)f) 
		return coFactorTrue(f); 
      	else if((unsigned)f < (unsigned)x) 
		return x; 
      	else 
	 	return ite(f,coFactorTrue(coFactorFalse(f),x),coFactorTrue(coFactorTrue(f),x)); // ????
} 
 
BDD_ID Manager::coFactorFalse(const BDD_ID f,const BDD_ID x) 
{ 
      	if((unsigned)x==(unsigned)f) 
		return coFactorFalse(f); 
      	else if((unsigned)f < (unsigned)x) 
		return x; 
      	else 
	 	return ite(f,coFactorFalse(coFactorFalse(f),x),coFactorFalse(coFactorTrue(f),x)); // ????
} 
 
BDD_ID Manager::coFactorTrue(const BDD_ID f) // T CoFactor of f 
{ 

         if(isConstant(f)) 
	     return f; 
	 return (*f.getHigh()); 

} 
 
BDD_ID Manager::coFactorFalse(const BDD_ID f) // E CoFactor of f 
{ 

         if(isConstant(f)) 
	     return f; 
	 return (*f.getLow()); 

} 
 
BDD_ID Manager::ite(const BDD_ID f,const BDD_ID g,const BDD_ID h) 
{ 

  	if(f==*True())      
     		return g; 
  	else if (f==*False()) 
       		return h; 
  	else if (h ==*False() && g == *True()) 
       		return f;
	else if (h == g)
		return g;
	else if (g ==*False() && h == *True())
		return neg(f);
  	else 
    	{ 
      		BDD_ID x=topVar(f); 
      		BDD_ID t=ite(coFactorTrue(f,x),coFactorTrue(g,x),coFactorTrue(h,x)); 
      		BDD_ID e=ite(coFactorFalse(f,x),coFactorFalse(g,x),coFactorFalse(h,x)); 
      		if(t==e) 
       			return t; 
     		nextID += 1; 
      		BDD_ID* tempT=new BDD_ID(t); 
      		BDD_ID* tempE=new BDD_ID(e); 
      		BDD_ID tmp((string)x,nextID,tempT,tempE); 
      		pair<BDD_ID,unsigned> elem(tmp,nextID);
		// Find or Add to Unique Table
      		uniqueTable.insert(elem); 
      		return tmp; 
	 } 
} 
 
BDD_ID Manager::and2(const BDD_ID f,const BDD_ID g) 
{ 
  	if(isConstant(f) || isConstant(g)) 
    	{ 
      	if(f == *False() || g == *False()) 
		return *False(); 
      	else if(f==*True()) 
		return g; 
      	else if(g==*True()) 
		return f; 
      	else{} 
    	} 
  	return ite(f,g,*False()); 
} 
 
BDD_ID Manager::or2(const BDD_ID f,const BDD_ID g) 
{ 
  	if(isConstant(f) || isConstant(g)) 
  	{ 
    	if(f==*True() || g==*True()) 
      		return *True(); 
    	else if(f==*False()) 
     		 return g; 
    	else if(g==*False()) 
      		return f; 
    	else{} 
  	} 
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
	if (f == *True())
		return *False();
	else if (f == *False())
		return *True();
	else
  		return ite(f,neg(coFactorFalse(f)),neg(coFactorTrue(f))); 
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
 
