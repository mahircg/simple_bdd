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
	//more tests will come here
}

void ManagerTest::trueTest(void)
{
  const unsigned t=man->True();
  CPPUNIT_ASSERT_EQUAL(t,(const unsigned)2);			//ID for terminal node TRUE
 
	
}

void ManagerTest::falseTest(void)
{
  const unsigned e=man->False();
  CPPUNIT_ASSERT_EQUAL(e,(const unsigned)1);			//ID for terminal node FALSE
}

void ManagerTest::isConstantTest(void)
{
	unsigned t=man->True();
        unsigned e=man->False();
	CPPUNIT_ASSERT_EQUAL(man->isConstant(t),true);
        CPPUNIT_ASSERT_EQUAL(man->isConstant(e),true);
}

void ManagerTest::isVariableTest(void)
{
  unsigned a=man->createVar("a");
  unsigned b=man->createVar("b");
  //unsigned f=man->or2(a,b);
  //CPPUNIT_ASSERT_EQUAL(man->isVariable(f),true);
  CPPUNIT_ASSERT_EQUAL(man->isVariable(a),true);
  CPPUNIT_ASSERT_EQUAL(man->isVariable(b),true);
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
  //unsigned a=man->createVar("a");
  //CPPUNIT_ASSERT_EQUAL(man->ite(a,*man->True(),*man->False()),a);
	
}

void ManagerTest::and2Test(void)
{
  unsigned a=man->createVar("a");
  unsigned b=man->createVar("b");
  unsigned c=man->createVar("c");
  unsigned f=man->and2(a,c);
  unsigned g=man->and2(b,c);
  unsigned h=man->or2(f,g);
  CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),c);//check right of f=a.c; should equal to c
  CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),man->False());//check left of f=a.c; should equal to zero
  CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(g),man->False());//check left of g=a.c,should equal to zero
  CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(g),c);//check right of h=a.c,should equal to c
  CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(h),c);
  CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(h),g);
}

void ManagerTest::or2Test(void)
{
  // unsigned a=man->createVar("a");
  // unsigned b=man->createVar("b");
  // unsigned f=man->or2(a,b);
  // unsigned g=man->or2(man->False(),f);
  // unsigned h=man->or2(g,man->True());
  // CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),b);
  // CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),man->True());
  // CPPUNIT_ASSERT_EQUAL(f,g);
  // CPPUNIT_ASSERT_EQUAL(h,man->True());

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











