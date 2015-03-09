#include "ManagerTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ManagerTest);

void ManagerTest::setUp(void)
{
  man=new Manager();
}

void ManagerTest::tearDown(void)
{
  delete man;
}

void ManagerTest::constructorTest(void)
{
	
}

void ManagerTest::createVarTest(void)
{	
  	unsigned a = man->createVar("x");
  	unsigned b = man->createVar("y");
  	CPPUNIT_ASSERT(a != b); //no two variables have the same id
  	CPPUNIT_ASSERT(a != (unsigned)2); // id of a var cannot be 2
	CPPUNIT_ASSERT(a != (unsigned)1); // id of a var cannot be 1
	unsigned c = man->createVar("x");
	CPPUNIT_ASSERT_EQUAL(c,a); //every different key should be mapped into a unique id
}

void ManagerTest::trueTest(void)
{
  	const unsigned t=man->True();
  	CPPUNIT_ASSERT_EQUAL(t,(const unsigned)2);	//ID for terminal node TRUE
}

void ManagerTest::falseTest(void)
{
  	const unsigned e=man->False();
  	CPPUNIT_ASSERT_EQUAL(e,(const unsigned)1);	//ID for terminal node FALSE
}

void ManagerTest::isConstantTest(void) 
{
	unsigned t=man->True();
        unsigned e=man->False();
	unsigned a=man->createVar("a");
	CPPUNIT_ASSERT_EQUAL(man->isConstant(t),true);
        CPPUNIT_ASSERT_EQUAL(man->isConstant(e),true);
	CPPUNIT_ASSERT_EQUAL(man->isConstant(a),false);
	//result of 1 and 0: a check for and2 function in the meantime
	CPPUNIT_ASSERT_EQUAL(man->isConstant(man->and2(t,e)),true);
	//result of 1 or 0: a check for or2 function in the meantime
	CPPUNIT_ASSERT_EQUAL(man->isConstant(man->or2(t,e)),true);
}

void ManagerTest::isVariableTest(void)
{
  	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	unsigned t=man->True();
  	unsigned f=man->or2(a,b);
	unsigned g=man->and2(f,man->False());
	//check if createVar returns variables
	CPPUNIT_ASSERT_EQUAL(man->isVariable(a),true);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(b),true);
	CPPUNIT_ASSERT_EQUAL(man->isVariable(t),false);
	//output of an operation,shouldn't return constant
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(f),true);
	//result of 0.(a+b) should return constant
	CPPUNIT_ASSERT_EQUAL(man->isVariable(g),false);
	
}

void ManagerTest::topVarTest(void)
{
	unsigned c=man->createVar("c");
	CPPUNIT_ASSERT_EQUAL(man->topVar(c), (unsigned)3);
	unsigned d=man->createVar("d");
	CPPUNIT_ASSERT_EQUAL(man->topVar(d), (unsigned)4);
	unsigned t=man->True();
	CPPUNIT_ASSERT_EQUAL(man->topVar(t), (unsigned)2);
        unsigned e=man->False();
	CPPUNIT_ASSERT_EQUAL(man->topVar(e), (unsigned)1);
}

void ManagerTest::coFactorWithTopTrueTest(void)
{
	unsigned a=man->createVar("a");
	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
	unsigned f=man->and2(a,c);
	unsigned g=man->and2(b,c);
	//---unsigned h=man->or2(f,g);
	//co-factor of h(a,b,c)=ac+bc with c,result should be a+b
	//---CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(h,c),man->or2(a,b));
	//get co-factor of f with a,result should be c
	//CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f,a),c);
	//get co-factor of f with c,result should be a
	//CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f,c),a);
}

void ManagerTest::coFactorWithTopFalseTest(void)
{
	//unsigned a=man->createVar("a");
	//unsigned b=man->createVar("b");
	//unsigned c=man->createVar("c");
	//unsigned f=man->and2(a,c);
	//CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f,b),f);
	//CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f,a),man->False());
	//unsigned g=man->and2(b,c);
	//unsigned h=man->or2(f,g);
	//CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(h,c),man->False());
}

void ManagerTest::coFactorTrueTest(void)
{
	unsigned a=man->False();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(a),(unsigned)1);

	unsigned b=man->True();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(b),(unsigned)2);

	unsigned c=man->createVar("c");
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c),man->False());
}

void ManagerTest::coFactorFalseTest(void)
{
	unsigned a=man->False();
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(a),(unsigned)1);

	unsigned b=man->True();
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(b),(unsigned)2);

	unsigned c=man->createVar("c");
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c),man->True());
}

void ManagerTest::iteTest(void)
{
	//Testing Terminal Cases:
	unsigned  a=man->createVar("a");
	unsigned  b=man->createVar("b");
	unsigned  c=man->createVar("c");
	unsigned  d=man->createVar("d");
	unsigned  f=man->and2(a,b);
	unsigned  g=man->and2(a,c);
	unsigned  h=man->or2(b,d);
	//Testing Terminal Cases:
	CPPUNIT_ASSERT_EQUAL(man->ite(man->False(),g,h),h); 		// ite(0,g,h) = h
	CPPUNIT_ASSERT_EQUAL(man->ite(man->True(),g,h),g); 		// ite(1,g,h) = g
	CPPUNIT_ASSERT_EQUAL(man->ite(f,g,g),g); 			// ite(f,g,g) = g
	CPPUNIT_ASSERT_EQUAL(man->ite(f,man->True(),man->False()),f); 	// ite(f,1,0) = f
	CPPUNIT_ASSERT_EQUAL(man->ite(f,man->False(),man->True()),man->neg(f)); // ite(f,0,1) = neg(f)
	//Testing Recursive Cases:
	
}

void ManagerTest::and2Test(void)
{
  	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
  	unsigned f=man->and2(a,c);
	unsigned g=man->and2(b,c);
	//unsigned h=man->or2(f,g);

  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),c);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorTrue(f)),man->True());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(f)),man->False());
	
	//check right of f=a.c; should equal to c
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),c);
	//check left of f=a.c; should equal to zero
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),man->False());
	//check left of g=a.c,should equal to zero
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(g),man->False());
	//check right of g=a.c,should equal to c
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(g),c);
	//check right of h=f+g,should be equal to c
  	//---CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(h),c);
	//check left of h,should be equal to g=b.c	
  	//---CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(h),g);
	//check left of c.(ac+bc),result would be the same	
  	//---CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->and2(h,c)),g);
}

void ManagerTest::or2Test(void)
{
  	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
  	unsigned f=man->or2(a,b);
	unsigned i=man->and2(f,c);
	
  	unsigned g=man->or2(man->False(),f);
  	unsigned h=man->or2(g,man->True());
  	
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorFalse(f)),man->False());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorFalse(f)),man->True());
	
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),b);
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),man->True());
  	CPPUNIT_ASSERT_EQUAL(f,g);
  	CPPUNIT_ASSERT_EQUAL(h,man->True());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(i),man->or2(a,b));
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(i),man->and2(b,c));	
}

void ManagerTest::xorTest(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
  	unsigned f=man->xor2(a,b);
	//man->printTable();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorTrue(f)),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorFalse(f)),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorFalse(f)),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(f)),man->True());
}

void ManagerTest::negTest(void)
{	
	unsigned x=man->createVar("x");
	unsigned xNeg=man->neg(x);
	//check right of not(x)
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(xNeg),man->True());
	//check left of not(x)
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(xNeg),man->False());
	//check output of not(true)		
	CPPUNIT_ASSERT_EQUAL(man->neg(man->True()),man->False());
	//check output of a and not(a)		
	CPPUNIT_ASSERT_EQUAL(man->and2(x,xNeg),man->False());
	//check output of a or not(a)			
    	CPPUNIT_ASSERT_EQUAL(man->or2(x,xNeg),man->True());

	unsigned a=man->createVar("a");
	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
	unsigned f=man->neg(man->and2(a,c));
	unsigned g=man->neg(man->or2(b,c));

	//Test for neg(and2)
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorTrue(f)),man->False());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(f)),man->True());

	//Test for neg(or2)
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorFalse(g)),man->True());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(g),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(g)),man->False());

}

void ManagerTest::nand2Test(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
  	unsigned f=man->nand2(a,b);
	//man->printTable();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorTrue(f)),man->False());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorFalse(f)),man->True());
}

void ManagerTest::nor2Test(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	//unsigned c=man->neg(b);
  	unsigned f=man->nor2(a,b);
	//man->printTable();
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorFalse(f)),man->True());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(f)),man->False());
}

void ManagerTest::getTopVarNameTest(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
  	unsigned f=man->or2(a,b);
	unsigned g=man->and2(b,c);
	//man->printTable();
	CPPUNIT_ASSERT_EQUAL(man->getTopVarName(a)[0],'a');
	CPPUNIT_ASSERT_EQUAL(man->getTopVarName(f)[0],'a');
	CPPUNIT_ASSERT_EQUAL(man->getTopVarName(g)[0],'b');
}

void ManagerTest::findNodesTest(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
  	unsigned f=man->or2(a,b);
	man->printTable();
}
  
void ManagerTest::findVarsTest(void)
{
	
}












