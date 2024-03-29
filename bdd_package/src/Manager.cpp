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
			
  BDD_ID tmp(varName,low,high);
  
  //check if a variable is added with same name before
  auto itr=uniqueTable.find(tmp);
  
  //if this is the first time with the varName argument,then add it to the unique table and increment nextID
  if(itr == uniqueTable.end())
  {
	nextID+=1;
    pair<BDD_ID,unsigned> elem(tmp,nextID);
    uniqueTable.insert(elem);
  }
  //if a variable with varName has been created before,return its ID
  else
	return itr->second;
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
	
	if(isConstant(f)) //formally,this is the case: <0,1> cofactorTrue g,which is equal to <0,1>
		return f; 
	else 
	{ 
      if(f==g) 			// f cofactor f,which is equal to right edge of f
			return coFactorTrue(f); 
      else if(f<g) 
		return f; 		//if f is independent of g,return f. Making the following implication is valid,since variables are ordered: f<g -> f is independent of g
      else 	//this is the challenging case :=) finding the cofactor of f with one of its variables,but in a lower index.
	  {		//formally,this equals to find cofactorTrue(f,g) where index(g) < index(f) = ite(topVar(f),right edge of f w.r.t g,left edge of f w.r.t g
	  	unsigned cft,cff;	
		if(getTopVarName(f)==getTopVarName(g))	//NOTE: this line might be buggy in case of following call: coFactorTrue(f,NOT(f)). It should be checked in unit tests. 
			return coFactorTrue(f);
		cft=coFactorTrue(coFactorTrue(f),g);	
		cff=coFactorTrue(coFactorFalse(f),g);
		BDD_ID tmp(getTopVarName(f),cff,cft);
		BDD_ID negTmp(tmp);						// a special treatment for negated values are needed,since they share the same top variable name
		negTmp.low=cft;
		negTmp.high=cff;
		auto itr=uniqueTable.find(negTmp);		//if there is a negated version of f(which is not intended to return),simply return f
		if(itr!=uniqueTable.end() )
			return f;
		else
			return ite(uniqueTable[tmp],cft,cff); //otherwise,calculate the use the cofactors calculated as described above and call ite
	  }
    } 	
}


//basically the same functionality with coFactorTrue,but the reverse
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
			BDD_ID negTmp(tmp);
			negTmp.low=cft;
			negTmp.high=cff;
			auto itr=uniqueTable.find(negTmp);
			if(itr!=uniqueTable.end() )
				return f;
			else
				return ite(uniqueTable[tmp],cft,cff);
		}
    } 

}

unsigned Manager::coFactorTrue(const unsigned f) // T CoFactor of f
{
	
	unsigned high;
	if(isConstant(f))
		return f;
		
	//since we do not hold a pointer to each node as it is in a DAG,table has to be traversed to find corresponding key and get the high value from it
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

//just a helper function for debugging
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

//ITE function is implemented by adhering to the textbook as much as possible. Even not line by line,function carries out the exact same functionality,except computed table.
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
      
      unsigned x=getSortedID(topVar(f),topVar(g),topVar(h));		//sort the top variables,since this is R'O'BDD,not RBDD
      unsigned t=ite(coFactorTrue(f,x),coFactorTrue(g,x),coFactorTrue(h,x)); 
      unsigned e=ite(coFactorFalse(f,x),coFactorFalse(g,x),coFactorFalse(h,x)); 

      if(t==e) 
       	return t; 
	  BDD_ID tmp(getTopVarName(x),e,t);
	  auto res=uniqueTable.find(tmp);
	  if(res==uniqueTable.end())		//these lines correspond to find or add into unique table
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

  if(coFactorTrue(f)==coFactorFalse(g) && coFactorFalse(f)==coFactorTrue(g))		//check in g=not(f) without calling neg
	return False();
  return ite(f,g,False());
}

unsigned Manager::or2(const unsigned f,const unsigned g)
{
  if(coFactorTrue(f)==coFactorFalse(g) && coFactorFalse(f)==coFactorTrue(g))		//check in g=not(f) without calling neg
	return True();	
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

unsigned Manager::getSortedID(unsigned f,unsigned g, unsigned h)
{
		//we do not check for terminal nodes with isConstant function here in the loop below;
		//because an ite function with terminal nodes(or cases) cannot(shouldn't!!) made it to this branch in control flow
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



void Manager::findNodes(const unsigned& f,set<unsigned>& list)
{	
	unsigned id=f;
	unsigned ll=min(coFactorTrue(id),coFactorFalse(id));
	unsigned hh=max(coFactorTrue(id),coFactorFalse(id));
	BDD_ID tmp(getTopVarName(id),coFactorFalse(id),coFactorTrue(id));
	int count=0;
	while (id>2)
	{
		for(auto itr=uniqueTable.begin();itr != uniqueTable.end();itr++)
			{
				if(itr->second==id)
				{
					list.insert(itr->second);
					id=max(max(itr->first.low,itr->first.high),ll);
					ll=max(min(itr->first.low,itr->first.high),ll);
					if (id==ll)
						ll=hh;
					hh=min(min(itr->first.low,itr->first.high),ll);
					count++;
				}
			}
	}
	list.insert(2); list.insert(1);
}

void Manager::findVars(const unsigned& f,set<size_t>& list)
{	
	unsigned id=f;
	unsigned ll=min(coFactorTrue(id),coFactorFalse(id));
	unsigned hh=max(coFactorTrue(id),coFactorFalse(id));
	BDD_ID tmp(getTopVarName(id),coFactorFalse(id),coFactorTrue(id));
	int count=0;
	while (id>2)
	{
		for(auto itr=uniqueTable.begin();itr != uniqueTable.end();itr++)
			{
				if(itr->second==id)
				{
					list.insert(itr->first.var[0]);
					id=max(max(itr->first.low,itr->first.high),ll);
					ll=max(min(itr->first.low,itr->first.high),ll);
					if (id==ll)
						ll=hh;
					hh=min(min(itr->first.low,itr->first.high),ll);
					count++;
				}
			}
	}
}
