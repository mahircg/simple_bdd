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
  	CPPUNIT_ASSERT_EQUAL(t->getID(),(unsigned)2);	
}

void ManagerTest::falseTest(void)
{
  	BDD_ID* e=man->False();
  	CPPUNIT_ASSERT_EQUAL(e->getID(),(unsigned)1);	
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
	BDD_ID* d=man->False();
  	//BDD_ID f=man->or2(a,b);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(a),true);
	CPPUNIT_ASSERT_EQUAL(man->isVariable(b),true);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(*d),false);
}

void ManagerTest::topVarTest(void)
{
	BDD_ID c=man->createVar("c");
	CPPUNIT_ASSERT_EQUAL(man->topVar(c), (long unsigned)3);
	BDD_ID d=man->createVar("d");
	CPPUNIT_ASSERT_EQUAL(man->topVar(d), (long unsigned)4); 
	BDD_ID e=man->createVar("e");
	CPPUNIT_ASSERT_EQUAL(man->topVar(e), (long unsigned)5); 
}

void ManagerTest::coFactorWithTopTrueTest(void)
{
	BDD_ID* a=man->False();
	BDD_ID* b=man->True();
	BDD_ID c=man->createVar("c");
	BDD_ID d=man->createVar("d");	
	BDD_ID e=man->createVar("e");
	BDD_ID f=man->createVar("f");
	f.setLow(e); f.setHigh(d);
	e.setLow(c); e.setHigh(d);
	d.setLow(*a); d.setHigh(*b);
	c.setLow(*a); d.setHigh(*b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(d,f).getID(),f.getID());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(*a,d).getID(),f->getID());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(d,d).getID(),d.getHigh().getID());
	// Recursive Test
	

}

void ManagerTest::coFactorWithTopFalseTest(void)
{
	BDD_ID* a=man->False();
	BDD_ID* b=man->True();
	BDD_ID c=man->createVar("c");
	BDD_ID d=man->createVar("d");	
	BDD_ID e=man->createVar("e");
	BDD_ID f=man->createVar("f");
	f.setLow(e); f.setHigh(d);
	e.setLow(c); e.setHigh(d);
	d.setLow(*a); d.setHigh(*b);
	c.setLow(*a); d.setHigh(*b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(d,f).getID(),f.getID());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(*a,d).getID(),f->getID());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(d,d).getID(),d.getLow().getID());
	// Recursive Test
	
}

void ManagerTest::coFactorTrueTest(void)
{
	BDD_ID* a=man->False();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(*a).getID(),(unsigned)1);

	BDD_ID* b=man->True();
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(*b).getID(),(unsigned)2);

	BDD_ID c=man->createVar("c"); c.setID(4); 	
	BDD_ID d=man->createVar("d"); d.setID(4); c.setLow(d); 
	BDD_ID e=man->createVar("e"); e.setID(4); c.setHigh(e); 
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c).getID(),(unsigned)4);

	c.setID(8); 	
	d.setID(6); c.setLow(d); 
	e.setID(7); c.setHigh(e);  
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c).getID(),(unsigned)7);
	
}

void ManagerTest::coFactorFalseTest(void)
{
	BDD_ID* a=man->False();
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(*a).getID(),(unsigned)1);

	BDD_ID* b=man->True();
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(*b).getID(),(unsigned)2);

	BDD_ID c=man->createVar("c"); c.setID(5); 	
	BDD_ID d=man->createVar("d"); d.setID(5); c.setLow(d); 
	BDD_ID e=man->createVar("e"); e.setID(5); c.setHigh(e); 
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c).getID(),(unsigned)5);

	c.setID(8); 	
	d.setID(6); c.setLow(d); 
	e.setID(7); c.setHigh(e); 
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c).getID(),(unsigned)6);
}

void ManagerTest::iteTest(void)
{
	BDD_ID f=man->createVar("f"); 	// f.id=3
	BDD_ID g=man->createVar("g");	// g.id=4
	BDD_ID h=man->createVar("h");	// h.id=5
	//CPPUNIT_ASSERT_EQUAL(man->ite(f,g,h).getID(),f.getID());
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











