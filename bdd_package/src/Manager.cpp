#include "Manager.hpp"
#include<iostream>
#include<vector>
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
  	bool isAvailable=false;
  	unsigned presentID;
  	BDD_ID tmp(varName,low,high);
  	for(auto& itr : uniqueTable)
  	{
		BDD_ID k((BDD_ID)(itr.first));
		if(uniqueTable.key_eq()(k,tmp))
		{
			isAvailable=true;
			presentID=itr.second;
		}
  	}
  	if(!isAvailable)
  	{
		nextID+=1;
    		pair<BDD_ID,unsigned> elem(tmp,nextID);
    		uniqueTable.insert(elem);
  	}
  	else
		return presentID;
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
			unsigned cft,cff;
			if(getTopVarName(f)==getTopVarName(g))
				return coFactorTrue(f);
			cft=coFactorTrue(coFactorTrue(f),g);
			cff=coFactorTrue(coFactorFalse(f),g);
			BDD_ID tmp(getTopVarName(f),cff,cft);
			return ite(uniqueTable[tmp],cft,cff);
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
		else if(f<g) 
			return f; 
		else
		{
			unsigned cft,cff;
			if(getTopVarName(f)==getTopVarName(g))
				return coFactorFalse(f);
			cft=coFactorFalse(coFactorTrue(f),g);
			cff=coFactorFalse(coFactorFalse(f),g);
			BDD_ID tmp(getTopVarName(f),cff,cft);
			return ite(uniqueTable[tmp],cft,cff);
		}
    } 

}

unsigned Manager::coFactorTrue(const unsigned f) // T CoFactor of f
{
	
	unsigned high;
	if(isConstant(f))
		return f;
	else
	{
		for(auto it=uniqueTable.begin();it != uniqueTable.end();it++)
			{
				if(it->second==f)
				{
				  BDD_ID tmp((BDD_ID)(it->first));
					high=tmp.high;
				}
			}
	}
	
	return high;
}

unsigned Manager::coFactorFalse(const unsigned f) // E CoFactor of f
{

        
	unsigned low;
	if(isConstant(f))
		return f;
	else
	{
		for(auto it=uniqueTable.begin();it != uniqueTable.end();it++)
			{
				if(it->second==f)
				{
				  BDD_ID tmp((BDD_ID)(it->first));
					low=tmp.low;
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
	else if (h == g)
		return g;
	//else if (h ==True() && g == False())
		//return ite(f,False(),True());
  	else 
    	{ 
      
      		unsigned x=getSortedID(topVar(f),topVar(g),topVar(h));
      		unsigned t=ite(coFactorTrue(f,x),coFactorTrue(g,x),coFactorTrue(h,x)); 
      		unsigned e=ite(coFactorFalse(f,x),coFactorFalse(g,x),coFactorFalse(h,x)); 
      		if(t==e) 
       			return t; 
	  	BDD_ID tmp(getTopVarName(x),e,t);
	  	auto res=uniqueTable.find(tmp);
	  	if(res==uniqueTable.end())
	  	{
			nextID += 1; 
			pair<BDD_ID,unsigned> elem(tmp,nextID); 
			uniqueTable.insert(elem);
			return nextID;
	  	}
	  	else
	  	{
			return uniqueTable[tmp];
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
	//check in g=not(f) without calling neg
	if(coFactorTrue(f)==coFactorFalse(g) && coFactorFalse(f)==coFactorTrue(g))
		return False();
  	return ite(f,g,False());
}

unsigned Manager::or2(const unsigned f,const unsigned g)
{
  	if(isConstant(f) || isConstant(g))
  	{
    		if(f==True() || g==True())
      			return True();
    		else if(f==True())
      			return g;
    		else if(g==True())
      			return f;
    		else
      		{}
  	}
	//check in g=not(f) without calling neg
	if(coFactorTrue(f)==coFactorFalse(g) && coFactorFalse(f)==coFactorTrue(g))
		return True();
  	return ite(f,True(),g);
}

unsigned Manager::xor2(const unsigned f,const unsigned g)
{
	if(isConstant(f) || isConstant(g))
  	{
    		if(f==False())
      			return g;
    		else if(g==False())
      			return f;
    		else
      		{}
  	}
	
	//neg creates a node -- creating confusion in ite method
  	return ite(f,neg(g),g);
}


unsigned Manager::nand2(const unsigned f,const unsigned g)
{
	if(isConstant(f) || isConstant(g))
  	{
    		if(f==False())
      			return g;
    		else if(g==False())
      			return f;
    		else
      		{}
  	}
	//check in g=not(f) without calling neg
	if(coFactorFalse(f)==coFactorFalse(g) && coFactorTrue(f)==coFactorFalse(g))
		return True();
	//neg creates a node -- creating confusion in ite method
  	return ite(f,neg(g),True());
	//return neg(and2(f,g));
}

unsigned Manager::nor2(const unsigned f,const unsigned g)
{
	if(isConstant(f) || isConstant(g))
  	{
    		if(f==True() || g==True())
      			return False();
    		else if(f==True())
      			return g;
    		else if(g==True())
      			return f;
    		else
      		{}
  	}
	//check in g=not(f) without calling neg
	if(coFactorTrue(f)==coFactorTrue(g) && coFactorFalse(f)==coFactorTrue(g))
		return False();

	return ite(f,False(),invert(g));
	//return neg(or2(f,g));
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

void Manager::findNodes(const unsigned& f)
{	
	
}

void Manager::findVars(const unsigned& f,set<size_t>& vars_of_root)
{

}

void Manager::printTable() const
{
  
  unsigned tmpID;
  cout<<"Variable\tLow\tHigh\tID\t"<<endl;
  for (auto it=uniqueTable.begin();it!=uniqueTable.end();it++)
    {
      BDD_ID tmpBDD((BDD_ID)(it->first));
      tmpID=it->second;
      cout<<tmpBDD.var<<"\t"<<tmpBDD.low<<"\t"<<tmpBDD.high<<"\t"<<tmpID<<"\t"<<endl;
    }
}

unsigned Manager::getSortedID(unsigned f,unsigned g, unsigned h)
{
	
	vector<BDD_ID> list;

	for(auto& itr: uniqueTable)
	{
		if(itr.second==f)
		{
			list.push_back((BDD_ID)(itr.first));
		}
		else if (itr.second==g)
		{
			list.push_back((BDD_ID)(itr.first));
		}
		else if(itr.second==h)
		{
			list.push_back((BDD_ID)(itr.first));
		}
	}
	
	BDD_ID minBDD((*min_element(list.begin(),list.end())));
	return uniqueTable[minBDD];	
}

unsigned Manager::invert(unsigned f)
{
	for(auto& itr: uniqueTable)
		{
			if(itr.second==f)
			{
				BDD_ID tmp((BDD_ID)(itr.first));
				tmp.low = itr.first.high;
				tmp.high = itr.first.low;
				uniqueTable.erase(itr.first);
				pair<BDD_ID,unsigned> elem(tmp,nextID);
    				uniqueTable.emplace(elem);
				return nextID;
			}
		}
}
