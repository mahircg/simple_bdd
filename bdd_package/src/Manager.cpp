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
	return (node.getID()!=1 || node.getID()!=2);
}

bool Manager::isConstant(const BDD_ID& node)
{
	return !isVariable(node);
}

size_t Manager::topVar(const BDD_ID& node) // Root Node Id
{
	return node.getID();
}

BDD_ID Manager::coFactorTrue(const BDD_ID f,const BDD_ID g)
{
	if (f.getID()==1 || g.getID()==1){
		return 	False();
	}
	if (f.getID()==2 || g.getID()==2){
		return 	f;
	}
	if (coFactorFalse(g) == False()){
		return coFactorTrue(coFactorTrue(f),coFactorTrue(g));	
	}
	if (coFactorTrue(g) == False()){
		return coFactorTrue(coFactorFalse(f),coFactorFalse(g));	
	}
	BDD_ID t = coFactorTrue(coFactorTrue(f),coFactorTrue(g));
	BDD_ID e = coFactorTrue(coFactorFalse(f),coFactorFalse(g));
	if (t == e){
		return t;	
	}
	/* TODO: Find Or Create Node to be Implemented -> Unique Table*/
	
}

BDD_ID Manager::coFactorFalse(const BDD_ID f,const BDD_ID g)
{
	if (f.getID()==1 || g.getID()==1){
		return 	f;
	}
	if (f.getID()==2 || g.getID()==2){
		return 	True();
	}
	if (coFactorFalse(g) == True()){
		return coFactorFalse(coFactorTrue(f),coFactorTrue(g));	
	}
	if (coFactorTrue(g) == False()){
		return coFactorFalse(coFactorFalse(f),coFactorFalse(g));	
	}
	BDD_ID t = coFactorFalse(coFactorTrue(f),coFactorTrue(g));
	BDD_ID e = coFactorFalse(coFactorFalse(f),coFactorFalse(g));
	if (t == e){
		return t;	
	}
	/* TODO: Find Or Create Node to be Implemented -> Unique Table*/
}

BDD_ID Manager::coFactorTrue(const BDD_ID f) // T CoFactor of f
{
	if (f.getID()==1){
		return False();
	}

	else if ((f.getLow())->getID() == (f.getHigh())->getID() == f.getID()){
		return f;
	}
	else if (f.getID()==2){
		return f;
	}
	return *f.getHigh();
}

BDD_ID Manager::coFactorFalse(const BDD_ID f) // E CoFactor of f
{
	if (f.getID()==2){
		return True();
	}
	else if ((f.getLow())->getID() == (f.getHigh())->getID() == f.getID()){
		return f;
	}
	else if (f.getID()==1){
		return f;
	}
	return *f.getLow();
}

BDD_ID Manager::ite(const BDD_ID f,const BDD_ID g,const BDD_ID h)
{
    	/*===== Terminal Case Recursion Check =====*/
	if ((f.getID()==2)||(f.getID()==1)||((g.getID()==2) && (h.getID()==1))||(g.getID()==h.getID())){
		return f;	
	}
	else if ((g.getID()==1) && (h.getID()==2)){
		return f;	
	}
	/*TODO: Check Computed Table: Eliminate Repetitions in Computations */
	
	else{
		BDD_ID rhh = ite(*f.getHigh(), *g.getHigh(), *h.getHigh());
		BDD_ID rll = ite(*f.getLow(), *g.getLow(), *h.getLow());
		if (rhh == rll){
			return rhh;		
		}
		/*TODO: Find Or Add in/to Unique Table -> Eliminate Isomorphic Sub-Graphs */
		/* BDD_ID r = find_or_add_unique_table(topVar, rhh, rll) 
		END TODO*/
		/*TODO: Update Computed Table 
		END TODO*/
		/* return r;*/
	}

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

