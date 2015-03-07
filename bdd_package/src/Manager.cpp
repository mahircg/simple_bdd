#include "Manager.hpp"
#include<iostream>
#include<algorithm>

using namespace std;


Manager::Manager()
{
	nextID=2;
}

Manager::~Manager()
{

}

unsigned Manager::createVar(const string& varName)
{
  	nextID+=1;

  	BDD_ID *tmp=new BDD_ID(varName,low,high);
  	pair<BDD_ID,unsigned> elem(*tmp,nextID);
  	uniqueTable.insert(elem);
  	delete tmp;
  	return nextID;

}

unsigned Manager::True() const
{
  	return high;
}

unsigned Manager::False() const
{
  	return low;
}

bool Manager::isVariable(const unsigned& node)
{
  	return ((unsigned)node!=1 && (unsigned)node!=2);
}

bool Manager::isConstant(const unsigned& node)
{
	return !isVariable(node);
}

unsigned Manager::topVar(const unsigned& node) // Root Node Id
{
  	return node;
}

unsigned Manager::coFactorTrue(const unsigned f,const unsigned g)
{
	if(isConstant(f)) 
		return f; 
	else 
	{ 
      		if(f==g) 
			return coFactorTrue(f); 
      		else if(f<g) 
			return g; 
      		else 
		{ 
			return ite(f,coFactorTrue(coFactorFalse(f),g),coFactorTrue(coFactorTrue(f),g));
		} 
    } 	
}

unsigned Manager::coFactorFalse(const unsigned f,const unsigned g)
{

	if(isConstant(f)) 
		return f; 
	else 
	{ 
		if(f==g) 
			return coFactorFalse(f); 
		else if(f < g) 
			return g; 
		else 
		{ 
			return ite(f,coFactorFalse(coFactorFalse(f),g),coFactorFalse(coFactorTrue(f),g));
		} 
    } 
}

unsigned Manager::coFactorTrue(const unsigned f) // T CoFactor of f
{
	BDD_ID *tmp;
	unsigned high;
	if(isConstant(f))
		return f;
	else
	{
		for(auto it=uniqueTable.begin();it != uniqueTable.end();it++)
			{
				if(it->second==f)
				{
					tmp=new BDD_ID((BDD_ID)(it->first));
					high=tmp->high;
					delete tmp;
				}
			}
	}
	return high;
}

unsigned Manager::coFactorFalse(const unsigned f) // E CoFactor of f
{

	BDD_ID *tmp;
	unsigned low;
	if(isConstant(f))
		return f;
	else
	{
		for(auto it=uniqueTable.begin();it != uniqueTable.end();it++)
			{
				if(it->second==f)
				{
					tmp=new BDD_ID((BDD_ID)(it->first));
					low=tmp->low;
					delete tmp;
				}
			}
	}
	return low;
}

unsigned Manager::ite(const unsigned f,const unsigned g,const unsigned h)
{
  	if(f==True())      
     		return g; 
  	else if (f==False()) 
       		return h; 
  	else if (h ==False() && g == True()) 
       		return f; 
  	else 
    	{ 
      		//unsigned x=max(max(topVar(f),topVar(g)),topVar(h));
		unsigned x=topVar(f);
      		unsigned t=ite(coFactorTrue(f,x),coFactorTrue(g,x),coFactorTrue(h,x)); 
      		unsigned e=ite(coFactorFalse(f,x),coFactorFalse(g,x),coFactorFalse(h,x)); 
      		if(t==e) 
       			return t; 
      		nextID += 1; 
      		BDD_ID tmp(getTopVarName(x),e,t); 
      		pair<BDD_ID,unsigned> elem(tmp,nextID);
		
		// Find or Add to Unique Table
		for(auto it=uniqueTable.begin();it != uniqueTable.end();++it){
			if (it->second == nextID){
				return it->second;
			}
			else{
				uniqueTable.insert(elem);
				return nextID;
			}			
		}   
    	} 
}

unsigned Manager::and2(const unsigned f,const unsigned g)
{
  	if(isConstant(f) || isConstant(g))
    	{
      		if(f == False() || g == False())
			return False();
      		else if(f==True())
			return g;
      		else if(g==True())
			return f;
      		else
		{}
    	}
  	return ite(f,g,False());
}

unsigned Manager::or2(const unsigned f,const unsigned g)
{
  	if(isConstant(f) || isConstant(g))
  	{
    		if(f==True() || g==True())
      			return True();
    		else if(f==False())
      			return g;
    		else if(g==False())
      			return f;
    		else
      		{}
  	}
  	return ite(f,True(),g);
}

unsigned Manager::xor2(const unsigned f,const unsigned g)
{
  	return ite(f,neg(g),g);
}

unsigned Manager::nand2(const unsigned f,const unsigned g)
{
  	return ite(f,neg(g),True());
}

unsigned Manager::nor2(const unsigned f,const unsigned g)
{
  	return ite(f,False(),neg(g));
}

unsigned Manager::neg(const unsigned f)
{	
	if (isConstant(f)){
		if(f==False())
      			return True();
    		else if(f==True())
      			return False();
    		else
      		{}		
	}
  	return ite(f,False(),True());
}

string Manager::getTopVarName(const unsigned& f)
{
	
	BDD_ID *tmp;
	string var;
	if(isConstant(f))
		return " ";
	else
	{
		for(auto it=uniqueTable.begin();it != uniqueTable.end();it++)
			{
				if(it->second==f)
				{
					tmp=new BDD_ID((BDD_ID)(it->first));
					var=tmp->var;
					delete tmp;
				}
			}
	}
	
	return var;
}

void Manager::findNodes(const unsigned& f,set<unsigned>& list)
{
}

void Manager::findVars(const unsigned& f,set<unsigned>& list)
{
}

