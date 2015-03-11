/**
 * \class Manager
 *
 * \brief Public interface for BDD management
 *
 * BDD management is based on the ROBDD structure,where variables are in an order
 * and BDD is in reduced form in any step of run-time. Usage of the unique table guarantees
 * that every calculated function is in its canonical form.
 */

#ifndef HPP_MANAGER
#define HPP_MANAGER

#include<set>
#include<unordered_map>
#include<string>
#include"BDD_ID.hpp"

using namespace std;

/**
 * \typedef 
 * Unique table type,which uses BDD_ID as key and unsigned type as value,which is 
 * the id that the function is mapped into.
 *
 */
typedef unordered_map<BDD_ID,unsigned,BDD_Hash> uniqueTableType;

class Manager
{
private:
	unsigned nextID;	/*!< ID to be given to the next variable or function to be created */
	const unsigned low=1;	/*!< Constant 1,represents the value 0 in Bool logic */
	const unsigned high=2;  /*!< Constant 2,represents the value 1 in Bool logic */
	uniqueTableType uniqueTable; /*!< Unique table object */
	
	/**
	 * \brief Function to sort the top variables,and return the smallest
	 * \param f ID of the first parameter
	 * \param f ID of the second parameter
	 * \param f ID of the third parameter
	 * This function is called by ite,which sorts the top variables of f,g and h and returns the smallest
	 * For sorting,STL's get_minimum is used,since we only sort three variables,and nothing fancy is necessary.
	 * Variables are in ascending order,so the smallest of three is returned.Any terminal cases among the inputs are discarded out of sorting.
	 */
	unsigned getSortedID(unsigned,unsigned,unsigned);

public:
	/**
	 * \brief Default constructor
	 * A simple default constructor,which sets the nextID variable to start from 2. 
	 */
	Manager();
	/**
	 * \brief Destructor
	 * Since we do not allocate anything on the heap,nor we do have any virtual functions,body of this function is simply empty. 
	 */
	~Manager();
	/**
	 * \brief Creates a variable with given variable name and returns its id.
	 * \param var Name of the variable.
	 * Note that in the current revision,only the first character of the function name is used.
	 * Valid variable names: "a","x","y",etc. Invalid(in other words,unsupported) variable names: "x1","aNeg",etc.
	 * Function also performs a check on the unique table to see if the variable to be created has been created before.
	 * Since search is made on a hash table,it takes O(1) time and does not increase the execution time in every createVar call,unlike a linear search.
	 */
	unsigned createVar(const string&);
	/**
	 * \brief Returns a True node,that has a value of 2
	 * This function basically returns the high member of Manager class.
	 */
	unsigned True() const;
	/**
	 * \brief Returns a False node,that has a value of 1
	 * This function basically returns the low member of Manager class.
	 */
	unsigned False() const;
	/**
	 * \brief Checks if a given node is variable
	 * \param node Node to be checked
	 * Variable check is based on the assumption we made about the terminal nodes,simply put; every id that has a value other than 1 or 2 is a variable.
	 */
	bool isVariable(const unsigned&);
	/**
	 * \brief Checks if a given node is a terminal node
	 * \param node Node to be checked
	 * This function uses isVariable; if a node is not a variable,it must be a terminal node.
	 */
	bool isConstant(const unsigned&);
	
	/**
	 * \brief Returns the top variable of a node
	 * \param f ID of the top variable of function f
	 * Function simply returns the node itself. Most likely this function is inlined by compiler.
	 */
	unsigned topVar(const unsigned&);
	
	/**
	 * \brief Returns the high co-factor of a function given a variable.
	 * \param f Top variable of the function f
	 * \param g Cofactor
	 * Formally,function returns the value of f when g = 1. If f if independent of g(f is less than cofactor),then f is returned.
	 * If co-factor equals to f,then high value of f is returned.
	 * Last case is g is less than f,where ite operation must be applied until finding cofactor in the function,and returning it.
	 * Example: f=ac+bc; coFactorTrue(f,c)=a+b
	 */
	unsigned coFactorTrue(const unsigned,const unsigned);
	
	/**
	 * \brief Returns the low co-factor of a function given a variable.
	 * \param f Top variable of the function f
	 * \param g Cofactor
	 * Formally,function returns the value of f when g = 0. If f if independent of g(f is less than cofactor),then f is returned.
	 * If co-factor equals to f,then low value of f is returned.
	 * Last case is g is less than f,where ite operation must be applied until finding cofactor in the function,and returning it.
	 * Example: f=ac+bc; coFactorFalse(f,a)=bc
	 */
	unsigned coFactorFalse(const unsigned,const unsigned);
	
	/**
	 * \brief Returns the high edge of a variable
	 * \param f ID of the function
	 * It simply returns the high edge of a function.
	 * Example: f=a; coFactorTrue(a)=2
	 */
	unsigned coFactorTrue(const unsigned);
	
	/**
	 * \brief Returns the low edge of a variable
	 * \param f ID of the function
	 * Similar to coFactorFalse with 1 argument,simply returns the low edge of a function.
	 * Example: f=a.c; coFactorFalse(a)=1
	 */
	unsigned coFactorFalse(const unsigned);
	/**
	 * \brief Generic ITE function implementation
	 * \param f Function to be evaluated
	 * \param g High edge of function f
	 * \param g Low edge of function f
	 * If-then-else function returns the f.g+!f.h,which is used for representing all basic logical operations.
	 * All logical operations are based on this function.Function is implemented as "Efficient Implementation of a BDD Package".
	 */
	unsigned ite (const unsigned,const unsigned,const unsigned);
	/**
	 * \brief Logical AND operator 
	 * \param f First argument of function
	 * \param g Second argument of function
	 * Applies the logical AND operator to the variables f and g and returns the new ID,which corresponds to the top variable of x=f AND g
	 */
	unsigned and2(const unsigned,const unsigned);
	
	/**
	 * \brief Logical OR operator 
	 * \param f First argument of function
	 * \param g Second argument of function
	 * Applies the logical OR operator to the variables f and g and returns the new ID,which corresponds to the top variable of x=f OR g
	 */
	unsigned or2(const unsigned,const unsigned);
	
	/**
	 * \brief Logical XOR operator 
	 * \param f First argument of function
	 * \param g Second argument of function
	 * Applies the logical XOR operator to the variables f and g and returns the new ID,which corresponds to the top variable of x=f XOR g
	 */
	unsigned xor2(const unsigned,const unsigned);
	/**
	 * \brief Logical NOT operator 
	 * \param f First argument of function
	 * Applies the negation operator to the variable f and returns the new ID,which corresponds to the top variable of x= NOT f
	 */
	unsigned neg(const unsigned);
	/**
	 * \brief Logical NAND operator 
	 * \param f First argument of function
	 * \param g Second argument of function
	 * Applies the logical NAND operator to the variables f and g and returns the new ID,which corresponds to the top variable of x=NOT(f AND g)
	 */
	unsigned nand2(const unsigned,const unsigned);
	
	/**
	 * \brief Logical NOR operator 
	 * \param f First argument of function
	 * \param g Second argument of function
	 * Applies the logical NOR operator to the variables f and g and returns the new ID,which corresponds to the top variable of x=NOT(f OR g)
	 */
	unsigned nor2(const unsigned,const unsigned);
	
	/**
	 * \brief Returns the name of the top variable of a variable
	 * \param f ID of top variable of f
	 * Function returns the name of the top variable of a function. Since name of a variable is a part of the key,it is not possible to find it in O(1) time(at least not possible with one-directional hashing)
	 * So, a linear search is performed on the unique table to get the variable name. 
	 */
	string getTopVarName(const unsigned&);
	
	void findNodes(const unsigned&,set<unsigned>&);
	void findVars(const unsigned&,set<unsigned>&);
  void printTable() const;

};

#endif
