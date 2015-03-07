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
}

void ManagerTest::isVariableTest(void)
{
  	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	unsigned t=man->True();
  	unsigned f=man->or2(a,b);
	unsigned g=man->and2(a,b);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(f),true);
	CPPUNIT_ASSERT_EQUAL(man->isVariable(g),true);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(a),true);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(b),true);
	CPPUNIT_ASSERT_EQUAL(man->isVariable(t),false);
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
	
}

void ManagerTest::coFactorWithTopFalseTest(void)
{
	
}

void ManagerTest::coFactorTrueTest(void)
{
	unsigned a=man->False();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(a),(unsigned)1);

	unsigned b=man->True();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(b),(unsigned)2);

	unsigned c=man->createVar("c");
	//CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c),(unsigned)2);
	//CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c),(unsigned)1);
}

void ManagerTest::coFactorFalseTest(void)
{
	
}

void ManagerTest::iteTest(void)
{
	//Testing Terminal Cases:
	unsigned  a=man->createVar("a");
	unsigned  b=man->createVar("b");
	unsigned  c=man->createVar("c");
	unsigned  d=man->createVar("d");
	unsigned  f=man->and2(a,b);
	man->printTable();
	unsigned  g=man->and2(a,c);
	unsigned  h=man->or2(b,d);
	//Testing Terminal Cases:
	CPPUNIT_ASSERT_EQUAL(man->ite(man->False(),g,h),h); 		// ite(0,g,h) = h
	CPPUNIT_ASSERT_EQUAL(man->ite(man->True(),g,h),g); 		// ite(1,g,h) = g
	CPPUNIT_ASSERT_EQUAL(man->ite(f,g,g),g); 			// ite(f,g,g) = g
	CPPUNIT_ASSERT_EQUAL(man->ite(f,man->True(),man->False()),f); 	// ite(f,1,0) = f
	//CPPUNIT_ASSERT_EQUAL(man->ite(f,man->False(),man->True()),man->neg(f)); // ite(f,0,1) = neg(f)

	//Testing Recursive Cases:

}

void ManagerTest::and2Test(void)
{
  	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
  	unsigned f=man->and2(a,b);
	//man->printTable();
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorTrue(f)),man->True());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(f)),man->False());
}

void ManagerTest::or2Test(void)
{
  	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
  	unsigned f=man->or2(a,b);
	//man->printTable();
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorFalse(f)),man->False());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorFalse(f)),man->True());  	
}

void ManagerTest::xorTest(void)
{

}

void ManagerTest::negTest(void)
{
	unsigned a=man->createVar("a");
	man->printTable();
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(b),man->True()); 
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(b),man->False());
	//unsigned c=man->createVar("c");
	//unsigned d=man->createVar("d");
	//unsigned f=man->and2(c,d);
	//man->printTable();
}

void ManagerTest::nand2Test(void)
{
	
}

void ManagerTest::nor2Test(void)
{

}

void ManagerTest::getTopVarNameTest(void)
{

}

void ManagerTest::findNodesTest(void)
{

}

void ManagerTest::findVarsTest(void)
{
	
}












