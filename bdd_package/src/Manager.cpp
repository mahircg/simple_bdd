#include "Manager.hpp"

using namespace std;


Manager::Manager()
{
      
	nextID=2;
<<<<<<< Updated upstream
=======
	low=new BDD_ID("F",1);
	high=new BDD_ID("T",2);
>>>>>>> Stashed changes
}

Manager::~Manager()
{
        
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
  return new BDD_ID(" ",2);
}

BDD_ID* Manager::False() const
{
  return new BDD_ID(" ",1);
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

BDD_ID Manager::coFactorTrue(const BDD_ID f,const BDD_ID g)
{
<<<<<<< Updated upstream
	if (f.getID()==1 || g.getID()==1){
		return 	False();
	}
	if (f.getID()==2 || g.getID()==2){
		return 	f;
	}
	if (coFactorFalse(g) == True()){
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
=======

  if(isConstant(f))
    return f;
  else
    {
      if((unsigned)g==(unsigned)f)
	return coFactorTrue(f);
      else if((unsigned)f < (unsigned)g)
	return g;
      else
	{
	  return f;
	  //here will be the case where second id is less then first id
	}
    }
    

>>>>>>> Stashed changes
	
}

BDD_ID Manager::coFactorFalse(const BDD_ID f,const BDD_ID g)
{
<<<<<<< Updated upstream
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
=======
  
  if(isConstant(f))
    return f;
  else
    {
      if((unsigned)g==(unsigned)f)
	return coFactorFalse(f);
      else if((unsigned)f < (unsigned)g)
	return g;
      else
	{
	  return f;
	  //here will be the case where second id is less then first id
	}
    }
>>>>>>> Stashed changes
}

BDD_ID Manager::coFactorTrue(const BDD_ID f) // T CoFactor of f
{
<<<<<<< Updated upstream
	if (f.getID()==1){
		return False();
	}

	else if ((f.getLow())->getID() == (f.getHigh())->getID() == f.getID()){
		return f;
	}
	else if (f.getID()==2){
		return f;
	}
	// return *f.getHigh();
=======
         if(isConstant(f))
	     return f;

	 
	 return (*f.getHigh());
>>>>>>> Stashed changes
}

BDD_ID Manager::coFactorFalse(const BDD_ID f) // E CoFactor of f
{
<<<<<<< Updated upstream
	if (f.getID()==2){
		return True();
	}
	else if ((f.getLow())->getID() == (f.getHigh())->getID() == f.getID()){
		return f;
	}
	else if (f.getID()==1){
		return f;
	}
	// return *f.getLow();
=======
         if(isConstant(f))
	     return f;

	 
	 return (*f.getLow());
>>>>>>> Stashed changes
}

BDD_ID Manager::ite(const BDD_ID f,const BDD_ID g,const BDD_ID h)
{
<<<<<<< Updated upstream
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
=======
  //Terminal cases of recursion
  if(f==*True())     
     return g;
  else if (f==*False())
       return h;
  else if (h ==*False() && g == *True())
       return f;
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
      uniqueTable.insert(elem);
      return tmp;
    }

>>>>>>> Stashed changes

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
      else
	{}
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
    else
      {}
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

