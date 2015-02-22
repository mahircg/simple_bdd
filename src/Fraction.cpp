/**
 * \brief ‫Implements methods of the fraction class
 *
 * \author Carlos Villarraga
 *
 */

#include "Fraction.hpp" 

Fraction::Fraction(int n, int d) throw (DivisionByZeroException) :
		n(n / gcd(n, d)), d(d / gcd(n, d)) {
	if (d == 0)
		throw DivisionByZeroException();
}

int Fraction::gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}


Fraction& Fraction::operator *=(const Fraction& rhs) {
	return *this;
}

int Fraction::num() const {
	return n;
}

int Fraction::den() const {
	return d;
}

Fraction operator *(const Fraction& lhs, const Fraction& rhs) {
	return 0;
}

bool Fraction::operator ==(const Fraction& rhs) const {
	return false;
}

bool Fraction::operator !=(const Fraction& rhs) const {
	return false;
}

ostream& operator <<(ostream& out, const Fraction& rhs) {
	return out << "";
}

