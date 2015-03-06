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

void ManagerTest::createVarTest(void) // Tests Done!!!
{
  	BDD_ID a = man->createVar("x");
  	BDD_ID b = man->createVar("y");
  	CPPUNIT_ASSERT(a.getID() != b.getID()); //no two variables have the same id
	CPPUNIT_ASSERT(a.getID() != (unsigned)2); // id of a var cannot be 2
	CPPUNIT_ASSERT(a.getID() != (unsigned)1); // id of a var cannot be 1
	
}

void ManagerTest::trueTest(void) // Tests Done!!!
{
  	BDD_ID* t=man->True();
  	CPPUNIT_ASSERT_EQUAL(t->getID(),(unsigned)2);	
}

void ManagerTest::falseTest(void) // Tests Done!!!
{
  	BDD_ID* e=man->False();
  	CPPUNIT_ASSERT_EQUAL(e->getID(),(unsigned)1);	
}
	
void ManagerTest::isConstantTest(void) // Tests Done!!!
{
	BDD_ID* t=man->True();
        BDD_ID* e=man->False();
	BDD_ID a = man->createVar("x");
	CPPUNIT_ASSERT_EQUAL(man->isConstant(*t),true);
        CPPUNIT_ASSERT_EQUAL(man->isConstant(*e),true);
	CPPUNIT_ASSERT_EQUAL(man->isConstant(a),false);
}

void ManagerTest::isVariableTest(void) // Tests Done!!!
{
  	BDD_ID a=man->createVar("a");
  	BDD_ID b=man->createVar("b");
	BDD_ID* d=man->False();
  	//BDD_ID f=man->or2(a,b);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(a),true);
	CPPUNIT_ASSERT_EQUAL(man->isVariable(b),true);
  	CPPUNIT_ASSERT_EQUAL(man->isVariable(*d),false);
}

void ManagerTest::topVarTest(void) // Tests Done!!!
{
	BDD_ID c=man->createVar("c");
	CPPUNIT_ASSERT_EQUAL(man->topVar(c).getID(), (unsigned)3);
	BDD_ID d=man->createVar("d");
	CPPUNIT_ASSERT_EQUAL(man->topVar(d).getID(), (unsigned)4);
	BDD_ID* t=man->True();
	CPPUNIT_ASSERT_EQUAL(man->topVar(*t).getID(), (unsigned)2);
        BDD_ID* e=man->False();
	CPPUNIT_ASSERT_EQUAL(man->topVar(*e).getID(), (unsigned)1);
	
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
	c.setLow(*a); c.setHigh(*b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c,f).getID(),f.getID()); // Test f < var
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c,c).getID(),b->getID()); // Test f == var
	// Test f > var
	

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
	c.setLow(*a); c.setHigh(*b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c,f).getID(),f.getID()); // Test f < var
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c,c).getID(),a->getID()); // Test f == var
	// Test f > var	
}

void ManagerTest::coFactorTrueTest(void) // Tests Done!!!
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

void ManagerTest::coFactorFalseTest(void) // Tests Done!!!
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
	// Test Terminal Cases:
	BDD_ID* a=man->False();
	BDD_ID* b=man->True();
	BDD_ID  f=man->createVar("f");//d
	BDD_ID  g=man->createVar("g");//c
	BDD_ID  h=man->createVar("h");//b
	BDD_ID  i=man->createVar("i");//a

	CPPUNIT_ASSERT_EQUAL(man->ite(*a,g,h).getID(),h.getID()); // ite(0,g,h) = h
	CPPUNIT_ASSERT_EQUAL(man->ite(*b,g,h).getID(),g.getID()); // ite(1,g,h) = g
	CPPUNIT_ASSERT_EQUAL(man->ite(f,g,g).getID(),g.getID()); // ite(f,g,g) = g
	CPPUNIT_ASSERT_EQUAL(man->ite(f,*b,*a).getID(),f.getID()); // ite(f,1,0) = f
	CPPUNIT_ASSERT_EQUAL(man->ite(f,*a,*b).getID(),man->neg(f).getID()); // ite(f,0,1) = neg(f)
	// Recursive Case Test:
	
	
	
	
}

void ManagerTest::and2Test(void)
{
  	
  	BDD_ID b=man->createVar("b");
	BDD_ID a=man->createVar("a");
  	BDD_ID f=man->and2(a,b);
  	CPPUNIT_ASSERT_EQUAL(f.getLow()->getID(),man->False()->getID());
  	CPPUNIT_ASSERT_EQUAL(f.getHigh()->getID(),a.getID());
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











