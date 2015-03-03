#ifndef HPP_BDD_ID
#define HPP_BDD_ID

#include<iostream>
#include<string>
#include<cassert>

using namespace std;



/**
 * \class BDD_ID 
 * \brief This class is used for storing the BDD structure
 * 
 * Each node(except leaves) has its successors which are either variables or terminal nodes.
 */
class BDD_ID 
{
	friend ostream& operator<<(ostream&,const BDD_ID&);
private:
	class BDD_ID *low,*high;
	string variable;
        unsigned id;
public:
	bool operator==(const BDD_ID&) const;
        BDD_ID(const BDD_ID&);
	BDD_ID(const string,unsigned);
	BDD_ID(const string,unsigned,BDD_ID*,BDD_ID*);
        
	void setLow(BDD_ID&);
	void setHigh(BDD_ID&);
        unsigned getID(void) const;
        void setID(unsigned);
        BDD_ID* getLow(void) const;
        BDD_ID* getHigh(void) const; 
	operator string() const;
};

class BDD_Hash
{
public:
   size_t operator() (const BDD_ID& bdd_id) const
    {
    
      return ((hash<unsigned>()(static_cast<int>(((string)bdd_id)[0]))) *  (hash<unsigned>()(bdd_id.getLow()->getID())) / (hash<unsigned>()(bdd_id.getHigh()->getID())));
    }
};



#endif
