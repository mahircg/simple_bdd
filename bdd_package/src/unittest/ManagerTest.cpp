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
  CPPUNIT_ASSERT(a != b); 								//no two variables have the same id
  CPPUNIT_ASSERT(a!=man->True() || a!=man->False());	//createVar shall not return constant
  unsigned c = man->createVar("x");
  CPPUNIT_ASSERT_EQUAL(c,a);							//every different key should be mapped into a unique id
  
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
	unsigned a=man->createVar("a");
	
	CPPUNIT_ASSERT_EQUAL(man->isConstant(a),false);					//check for a variable
	CPPUNIT_ASSERT_EQUAL(man->isConstant(man->and2(t,e)),true);		//result of 1 and 0: a check for and2 function in the meantime
	CPPUNIT_ASSERT_EQUAL(man->isConstant(man->or2(t,e)),true);		//result of 1 or 0: a check for or2 function in the meantime
	CPPUNIT_ASSERT_EQUAL(man->isConstant(t),true);
    CPPUNIT_ASSERT_EQUAL(man->isConstant(e),true);
}

void ManagerTest::isVariableTest(void)
{
  unsigned a=man->createVar("a");
  unsigned b=man->createVar("b");
  unsigned f=man->or2(a,b);
  unsigned g=man->and2(f,man->False());
  
  CPPUNIT_ASSERT_EQUAL(man->isVariable(g),false);		//result of 0.(a+b) should return constant
  CPPUNIT_ASSERT_EQUAL(man->isVariable(f),true);		//output of an operation,should return constant
  
  //check if createVar returns variables
  CPPUNIT_ASSERT_EQUAL(man->isVariable(a),true);		
  CPPUNIT_ASSERT_EQUAL(man->isVariable(b),true);
 
}

void ManagerTest::topVarTest(void)
{
	
	
}

void ManagerTest::coFactorWithTopTrueTest(void)
{
	unsigned a=man->createVar("a");
	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
	unsigned f=man->and2(a,c);
	unsigned g=man->and2(b,c);
	unsigned h=man->or2(f,g);
	unsigned cNeg=man->neg(c);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(h,c),man->or2(a,b));		// get co-factor of h(a,b,c)=ac+bc with c,result should be a+b
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f,a),c);					//get co-factor of f with a,result should be c
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f,c),a);					//get co-factor of f with c,result should be a
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(c,a),c);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(cNeg,a),cNeg);
}

void ManagerTest::coFactorWithTopFalseTest(void)
{
	unsigned a=man->createVar("a");
	unsigned b=man->createVar("b");
	unsigned c=man->createVar("c");
	unsigned f=man->and2(a,c);
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f,b),f);
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f,a),man->False());
	unsigned g=man->and2(b,c);
	unsigned h=man->or2(f,g);
	unsigned i=man->coFactorFalse(h,c);
	CPPUNIT_ASSERT_EQUAL(i,man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(c,a),c);
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->neg(c),a),man->neg(c));
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
  CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(g),c);//check right of g=a.c,should equal to c
  CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(h),c);	//check right of h=f+g,should be equal to c
  CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(h),g);	//check left of h,should be equal to g=b.c
  CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->and2(h,c)),g); //check left of c.(ac+bc),result would be the same
 
}

void ManagerTest::or2Test(void)
{
  unsigned a=man->createVar("a");
  unsigned b=man->createVar("b");
  unsigned c=man->createVar("c");
  unsigned f=man->or2(a,b);
  unsigned g=man->or2(man->False(),f);
  unsigned h=man->or2(g,man->True());
  unsigned i=man->and2(f,c);
  
  CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),b);
  CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),man->True());
  CPPUNIT_ASSERT_EQUAL(f,g);
  CPPUNIT_ASSERT_EQUAL(h,man->True());
  CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(i),c);
  CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(i),man->and2(b,c));

}

void ManagerTest::xorTest(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
  	unsigned f=man->xor2(a,b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorTrue(f)),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorFalse(f)),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorFalse(f)),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(f)),man->True());

}

void ManagerTest::negTest(void)
{
	unsigned a=man->createVar("a");
	unsigned aNeg=man->neg(a);
	unsigned b=man->createVar("b");
	unsigned f=man->neg(man->and2(a,b));
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(aNeg),man->False());		//check right of not(a)
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(aNeg),man->True());		//check left of not(a)
	CPPUNIT_ASSERT_EQUAL(man->neg(man->True()),man->False());		//check output of not(true)
	CPPUNIT_ASSERT_EQUAL(man->and2(a,aNeg),man->False());			//check output of a and not(a)
    CPPUNIT_ASSERT_EQUAL(man->or2(a,aNeg),man->True());				//check output of a or not(a)
	

}

void ManagerTest::nand2Test(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
  	unsigned f=man->nand2(a,b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorTrue(f)),man->False());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(f),man->True());
	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(man->coFactorFalse(f)),man->True());
}

void ManagerTest::nor2Test(void)
{
	unsigned a=man->createVar("a");
  	unsigned b=man->createVar("b");
	unsigned c=man->neg(b);
  	unsigned f=man->nor2(a,b);
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorFalse(f)),man->True());
  	CPPUNIT_ASSERT_EQUAL(man->coFactorTrue(f),man->False());
	CPPUNIT_ASSERT_EQUAL(man->coFactorFalse(man->coFactorTrue(f)),man->False());

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











