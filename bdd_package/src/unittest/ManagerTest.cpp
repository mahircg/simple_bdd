#include "ManagerTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ManagerTest);

void ManagerTest::setUp(void)
{
	//not much yet
}

void ManagerTest::tearDown(void)
{
	//nothing to deallocate
}

void ManagerTest::constructorTest(void)
{
	
}

void ManagerTest::createVarTest(void)
{
	BDD_ID a=createVar("x");
	BDD_ID b=createVar("y");
	CPPUNIT_ASSERT_EQUAL(a.getID() != b.getID()); //no two variables have the same id
	//more tests will come here
}

void ManagerTest::trueTest(void)
{
	BDD_ID t=True();
	CPPUNIT_ASSERT_EQUAL(t.getID()==2);			//ID for terminal node TRUE
	
}

void ManagerTest::falseTest(void)
{
	BDD_ID e=False();
	CPPUNIT_ASSERT_EQUAL(t.getID()==1);			//ID for terminal node FALSE
}

void ManagerTest::isConstantTest(void)
{
	BDD_ID t=True();
	BDD_ID e=False();
	CPPUNIT_ASSERT_EQUAL(isConstant(t)==true);
	CPPUNIT_ASSERT_EQUAL(isConstant(e)==false);
}

void ManagerTest::isVariableTest(void)
{
	
}

void ManagerTest::topVarTest(void)
{
	
}

void ManagerTest::coFactorWithTopTrueTest(void)
{
	
}

void ManagerTest::coFactorWithTopFalseTest(void)
{
	
}

void ManagerTest::coFactorTrueTest(void)
{
	
}

void ManagerTest::coFactorFalseTest(void)
{
	
}

void ManagerTest::iteTest(void)
{
	
}

void ManagerTest::and2Test(void)
{
	
}

void ManagerTest::or2Test(void)
{
	
}

void ManagerTest::xorTest(void)
{
	
}

void ManagerTest::negTest(void)
{
	
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

void ManagerTest::findVarsTest(void)
{
	
}











