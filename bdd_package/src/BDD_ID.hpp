/**
 * \class BDD_ID
 * \brief A simple data structure to use as a key in unique table.
 *
 * This class is used for mapping nodes in ROBBD to unique ID's for every different function.
 * It basically consists of three fields,namely; variable,low and high.
 * Variable member corresponds to the top variable of the function,while high and low holds the true and false co-factors of a node,respectively.
 * For terminal nodes it is assumed that id of 1 represents zero,while id of 2 represents 1.
 */


#ifndef HPP_BDD_ID
#define HPP_BDD_ID

#include<string>


using namespace std;

struct BDD_ID
{
	unsigned low,high;
	string var;
  
	/**
	 * \brief Equality operator
	 * \param rhs BDD_ID,which will be compared to
	 * Overloaded equality operator checks if two BDD_ID objects are equal.
	 * Comparison is based on variable,low and high.
	 * If every member of two BDD_ID are equal,results is true,otherwise false.
	 * This function is used by unordered_map structure,which is used for hashing the unique table
	 */
	bool operator==(const BDD_ID&) const;
	/**
	 * \brief Less than operator
	 * \param rhs BDD_ID,which will be compared to
	 * Overloaded less than operator checks the precedence of two BDD_ID objects based on their top-variable.
	 * This operator is overloaded in order to find the smallest ID in a list of BDD_ID's.
	 * Purpose of finding minimum is to sort the top variables in the ite function,since variables are assumed to be ordered.
	 */
	bool operator<(const BDD_ID&) const;
	/**
	 * \brief Less than or equal operator
	 * \param rhs BDD_ID,which will be compared to
	 * Overloaded less than or equal operator.For more details; see documentation of less than operator.
	 */
	bool operator<=(const BDD_ID&) const;
	
	/**
	 * \brief Greater than  operator
	 * \param rhs BDD_ID,which will be compared to
	 * Overloaded greater than operator.For more details; see documentation of less than operator.
	 */
	bool operator>(const BDD_ID&) const;
	/**
	 * \brief Greater than or equal  operator
	 * \param rhs BDD_ID,which will be compared to
	 * Overloaded greater than or equal operator.For more details; see documentation of less than operator.
	 */
	bool operator>=(const BDD_ID&) const;
	
	/**
	 * \brief Three-arg constructor
	 * \param var top variable
	 * \param low low(left) node
	 * \param high high(right) node
	 * Constructor with three-arguments.Note that there is no default constructor.
	 */
	BDD_ID(const string,unsigned,unsigned);
	
	/**
	 * \brief Copy constructor
	 * \param rhs righ-hand side BDD_ID object
	 * Copy constructor,copies the values of rhs to lhs.
	 */
	BDD_ID(const BDD_ID&);
        
};

/**
 * \class BDD_Hash
 * \brief Class definition for using BDD_ID object as a key for STL's unordered-map
 *
 * This class contains the overloaded hash operator for BDD_ID
 * Basically,when a key-value pair is created for a node,() operator is used to resolve hashing method for BDD_ID ADT
 */

class BDD_Hash
{
public:
	/**
	 * \brief overloaded std::hash<key>::operator() operator for BDD_ID
	 * \param bdd_id BDD_ID object,in which the key value will be generated from
	 * This method simply multiplies the ASCII value of first character in variable member
	 * with the id of low and divides that multiplication to the high member.
	 * Since smallest id is 1,division by zero should not be possible.
	 * It is assumed that every variable has one letter in variable field.As of this version,string of characters as variable name
	 * is not supported. As a future work,API can be extended to support that feature.
	 */
   size_t operator() (const BDD_ID& bdd_id) const
    {
	   return ((hash<unsigned>()(static_cast<int>(((string)bdd_id.var)[0]))) *  (hash<unsigned>()(bdd_id.low)) / (hash<unsigned>()(bdd_id.high)));
    }
};



#endif
