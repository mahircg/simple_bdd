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
  BDD_ID a = man->createVar("x");
  BDD_ID b = man->createVar("y");
  CPPUNIT_ASSERT(a.getID() != b.getID()); //no two variables have the same id
	//more tests will come here
}

void ManagerTest::trueTest(void)
{
  BDD_ID* t=man->True();
  CPPUNIT_ASSERT_EQUAL(t->getID(),(unsigned)2);			//ID for terminal node TRUE
 
	
}

void ManagerTest::falseTest(void)
{
  BDD_ID* e=man->False();
  CPPUNIT_ASSERT_EQUAL(e->getID(),(unsigned)1);			//ID for terminal node FALSE
}

void ManagerTest::isConstantTest(void)
{
	BDD_ID* t=man->True();
        BDD_ID* e=man->False();
	CPPUNIT_ASSERT_EQUAL(man->isConstant(*t),true);
        CPPUNIT_ASSERT_EQUAL(man->isConstant(*e),true);
}

void ManagerTest::isVariableTest(void)
{
  BDD_ID a=man->createVar("a");
  BDD_ID b=man->createVar("b");
  BDD_ID f=man->or2(a,b);
  CPPUNIT_ASSERT_EQUAL(man->isVariable(f),true);
  CPPUNIT_ASSERT_EQUAL(man->isVariable(a),false);
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
  // BDD_ID a=man->createVar("a");
  // BDD_ID b=man->createVar("b");
  // BDD_ID f=man->and2(a,b);
  // CPPUNIT_ASSERT_EQUAL(f.getLow()->getID(),man->False().getID());
  // CPPUNIT_ASSERT_EQUAL(f.getHigh()->getID(),b.getID());
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

void ManagerTest::findNodesTest(void)
{

}

void ManagerTest::findVarsTest(void)
{
	
}











