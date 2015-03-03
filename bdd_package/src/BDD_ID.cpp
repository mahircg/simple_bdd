#include "BDD_ID.hpp"

using namespace std;





bool BDD_ID::operator==(const BDD_ID& rhs) const
{
  
  return (this->variable==rhs.variable) && (this->low->id==rhs.low->id) && (this->high->id==rhs.high->id);
}


BDD_ID::operator string() const
{
	return variable;
}

void BDD_ID::setID(unsigned id)
{
	this->id = id;
}

unsigned BDD_ID::getID() const
{
	return id;
}



ostream& operator<<(ostream& osObject,const BDD_ID &bddObj)
{
	osObject<<bddObj.variable<<" -> "<<static_cast<string>(*(bddObj.low))<<"|"<<static_cast<string>(*(bddObj.high));
	return osObject;
}

BDD_ID::BDD_ID(const BDD_ID& rhs)
{
  
  this->id = rhs.id;
  this->variable=rhs.variable;
  if(!(rhs.low == NULL || rhs.high==NULL))
  {
    this->low=rhs.low;
    this->high=rhs.high;
  }
}



BDD_ID* BDD_ID::getLow() const
{
  
  return low;
}

BDD_ID* BDD_ID::getHigh() const
{
  return high;
}


BDD_ID::BDD_ID(const string variable,unsigned id):id(id), variable(variable) 
{
  low=NULL;
  high=NULL;
}

BDD_ID::BDD_ID(const string variable,unsigned id,BDD_ID* t,BDD_ID* e):id(id), variable(variable) 
{
  
	low=e;
	high=t;
}



 
void BDD_ID::setLow(class BDD_ID& e)
{
	*low=e;
}

void BDD_ID::setHigh(class BDD_ID& t)
{
	*high=t;
}
