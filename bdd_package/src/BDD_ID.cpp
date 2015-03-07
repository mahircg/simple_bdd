#include "BDD_ID.hpp"


bool BDD_ID::operator==(const BDD_ID& rhs) const
{
  return (this->var==rhs.var) && (this->low==rhs.low) && (this->high==rhs.high);
}

BDD_ID::BDD_ID(const string var,unsigned low,unsigned high):var(var),low(low),high(high)
{
}

BDD_ID::BDD_ID(const BDD_ID& rhs)
{
	this->var=rhs.var;
	this->low=rhs.low;
	this->high=rhs.high;
}
