#ifndef HPP_BDD_ID
#define HPP_BDD_ID

#include<string>


using namespace std;



/**
 * \class BDD_ID
 * \brief This class is used for storing the BDD structure
 *
 * Each node(except leaves) has its successors which are either variables or terminal nodes.
 */
struct BDD_ID
{
	unsigned low,high;
	string var;
  
	bool operator==(const BDD_ID&) const;
	BDD_ID(const string,unsigned,unsigned);
	BDD_ID(const BDD_ID&);
        
};

class BDD_Hash
{
public:
   size_t operator() (const BDD_ID& bdd_id) const
    {
	   return ((hash<unsigned>()(static_cast<int>(((string)bdd_id.var)[0]))) *  (hash<unsigned>()(bdd_id.low)) / (hash<unsigned>()(bdd_id.high)));
    }
};



#endif
