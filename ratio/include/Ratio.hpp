#pragma once

#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include <cmath>
#include <cassert>

// Doxygen menu
/// \version 0.1
/// \mainpage
/// \image html myImage.png width=400px
/// \tableofcontents
/// \section instroduction_sec What for?
/// Rational number is a number that can be expressed as the quotient or fraction p/q of two integers, a numerator p and a non-zero denominator q. It can be usefull for 
/// certain operations.
/// \section install_bigsec How to install
/// \subsection dependencies_sec Dependecies
/// \li nothing
/// \li Doxygen (if you want the documentation)
/// \subsection install_sec Install with cmake (Linux / Mac)
/// \li Just add the Ratio.hpp file in yours include files
/// \li For this example project : if Doxygen installed: make html
/// \li The documentation is located in :
/// 	- [path to build]/doc/doc-doxygen/html/index.html or 
/// 	- or [path to build]/INTERFACE/doc/doc-doxygen/html/index.html


/// \class Ratio
/// \brief class defining a rational number.
template <typename T>
class Ratio{

	private : 
		T m_num;
		T m_den;

	public :
		// default constructor
		Ratio() : m_num(0), m_den(1) {};

		/// \brief constructor from a numerator and denominator
		/// \param numerator : the numerator of the rational number
		/// \param denominator : the denominator of the rational number
		Ratio(const T& numerator, const T &denominator) : m_num(numerator), m_den(denominator) {
			if(denominator == 0){
				throw std::invalid_argument("You can't divide by 0 (infinite values not managed).");
			}

			this->reduce();

			assert((this->m_den != 0) && "m_den should not be 0");
			assert((this->m_den > 0) && "m_den should not be negative");
		};


		/// \brief constructor from a value number, convert it into a rational number
		/// \param ratio the other rational number
		Ratio(const double& value);

		/// \brief constructor from another rational number
		/// \param ratio the other rational number
		Ratio(const Ratio &ratio) = default;

		/// \brief destructor
		~Ratio() = default;

		/// \brief getter of the numerator
		inline T getNumerator() const {return m_num;};

		/// \brief getter of the denominator
		inline T getDenominator() const {return m_den;};

		/// \brief setter of the numerator
		/// \param numerator the new numerator
		void setNumerator(const T numerator) {this->m_num = numerator;};

		/// \brief setter of the denominator
		/// \param denominator the new denominator
		void setDenominator(const T denominator) {this->m_den = denominator;};

		/// \brief operator addition for rational numbers
		/// \param r the rational number to be added
		template<typename U>
		Ratio<T> operator+(const Ratio<U> &r){
			return Ratio<T>(this->m_num * r.getDenominator() + this->m_den * r.getNumerator(), this->m_den * r.getDenominator());
		}
		
		/// \brief operator addition for rational numbers with a value
		/// \param value the value to be added
		template<typename U>
		Ratio<T> operator+(const U &value) const {
			return Ratio<T>(this->m_num + this->m_den * value, this->m_den);
		}

		/// \brief operator addition for rational numbers with a value
		/// \param value the value to be added
		/// \param r the rational number to be added
		template<typename U>
		friend Ratio<T> operator+(const U &value, const Ratio<T> &r){
			return Ratio<T>(r.getNumerator()  + r.getDenominator() * value, r.getNumerator());
		}

		/// \brief operator subtraction for rational numbers
		/// \param r the rational number to substract
		template<typename U>
		Ratio<T> operator-(const Ratio<U> &r){
			return Ratio<T>(this->m_num * r.getDenominator() - this->m_den * r.getNumerator(), this->m_den * r.getDenominator());
		}

		/// \brief operator subtract for rational numbers with a value
		/// \param value the value to be subtracted
		template<typename U>
		Ratio<T> operator-(const U &value) const {
			return Ratio<T>(this->m_num - this->m_den * value, this->m_den);
		}

		/// \brief operator subtract for rational numbers with a value
		/// \param value the value to be subtracted
		/// \param r the rational number
		template<typename U>
		friend Ratio<T> operator-(const U &value, const Ratio<T> &r){
			return Ratio<T>(r.getDenominator() * value - r.getNumerator(), r.getDenominator());
		}
	
		/// \brief operator unary minus operator
		Ratio operator-() const;

		/// \brief operator multiply for rational numbers
		/// \param r the rational number to multiply
		template<typename U>
		Ratio<T> operator*(const Ratio<U> &r) {
			return Ratio<T>(this->m_num * r.getNumerator(), this->m_den * r.getDenominator());
		}

		/// \brief operator subtract for rational numbers with a value
		/// \param value the value to multiply
		template<typename U>
		Ratio operator*(const U &value) const {
			return Ratio<T>(value*this->m_num, this->m_den);
		}

		/// \brief operator subtract for rational numbers with a value
		/// \param value the value to be multiplied
		/// \param r the rational number
		template<typename U>
		friend Ratio<T> operator*(const U &value, const Ratio<T> &r){
			return Ratio<T>(value * r.getNumerator(), r.getDenominator());
		}

		/// \brief operator divide for rational numbers
		/// \param r the rational number to divide
		template<typename U>
		Ratio<T> operator/(const Ratio<U> &r) {
			return Ratio<T>(this->m_num * r.getDenominator(), r.getNumerator() * this->m_den);
		}
		
		/// \brief operator divide for rational numbers with a value
		/// \param value the value to divide
		template<typename U>
		Ratio operator/(const U &value) const {
			return Ratio<T>(this->m_num, this->m_den * value);
		}

		/// \brief operator divide for rational numbers with a value
		/// \param value the value to divided
		/// \param r the rational number
		template<typename U>
		friend Ratio<T> operator/(const U &value, const Ratio<T> &r){
			return Ratio<T>(value * r.getDenominator(), r.getNumerator());
		}

		/// \brief operator print for rational numbers
		/// \param r the rational number to print
		template<typename U>
        friend std::ostream& operator<< (std::ostream& stream, const Ratio<U> &r);

		/// \brief operator sin for rational numbers
		/// \param r the rational number to use
		static Ratio sin(const Ratio &r);
		/// \brief operator cos for rational numbers
		/// \param r the rational number to use
		static Ratio cos(const Ratio &r);
		/// \brief operator tan for rational numbers
		/// \param r the rational number to use
		static Ratio tan(const Ratio &r);
		/// \brief operator exp for rational numbers
		/// \param r the rational number to use
		static Ratio exp(const Ratio &r);
		/// \brief operator ln for rational numbers
		/// \param r the rational number to use
		static Ratio ln(const Ratio &r);
		/// \brief operator log10 for rational numbers
		/// \param r the rational number to use
		static Ratio log10(const Ratio &r);
		/// \brief operator abs for rational numbers
		/// \param r the rational number to use
		static Ratio abs(const Ratio &r);
		/// \brief operator pow for rational numbers
		/// \param r the rational number to use
		static Ratio pow(const Ratio &r, const T &n);
		/// \brief operator sqrt for rational numbers
		/// \param r the rational number to use
		static Ratio sqrt(const Ratio &r);

		/// \brief invert a rational number
		/// \param x the rational number to invert
		static Ratio invert(const Ratio &r);

		/// \brief this method reduce a rational number so it is irreducible
		void reduce();

		/// \brief same method as void reduce() but it reduce the rational number in the parameters
		/// \param r the rational number to reduce
		static Ratio reduce(const Ratio &r);

		/// \brief return the int part of a ratonal number
		/// \param r the rational number
		static int intPart(const Ratio &r);

		/// \brief return the int part of a floating number
		/// \param x the floating number
		static int intPart(const float &x);

		/// \brief this method convert a floating number to a rational number
		/// \param x the number to convert
		/// \param nbIter the number of iteration for the convertion
		static Ratio convertFloatToRatio(const double &x, unsigned int nbIter);
		
		/// \brief this method convert a rational number to a floating number
		/// \param x the number to convert
		static float convertRatioToFloat(const Ratio &r);
};

template <typename T>
Ratio<T>::Ratio(const double& value){
	const Ratio<T> r(convertFloatToRatio(value,4));

	this->m_num = r.getNumerator();
	this->m_den = r.getDenominator();

	assert((this->m_den != 0) && "m_den should not be 0");
	assert((this->m_den > 0) && "m_den should not be negative");
}

//------------------------------ARITHMETICS OPERATORS--------------------------------------//

template <typename T>
Ratio<T> Ratio<T>::operator-() const{
	return Ratio<T>(-m_num,m_den);
}

//----------------------------------------------------------------------------------------//

//------------------------------COMPARISON OPERATORS--------------------------------------//

template <typename T, typename U>
bool operator<(const Ratio<T> &r1, const Ratio<U> &r2){
	return (r1.getNumerator() * r2.getDenominator() < r1.getDenominator() * r2.getNumerator());
}

template <typename T, typename U>
bool operator<(const Ratio<T> &r1, const U &value){
	return (r1 < Ratio<T>::convertFloatToRatio(value, 4));
}

template <typename T, typename U>
bool operator<(const U &value, const Ratio<T> &r1){
	return (Ratio<T>::convertFloatToRatio(value, 4) < r1);
}

template <typename T, typename U>
bool operator<=(const Ratio<T> &r1, const Ratio<U> &r2){
	return (r1.getNumerator() * r2.getDenominator() <= r1.getDenominator() * r2.getNumerator());
}

template <typename T, typename U>
bool operator<=(const Ratio<T> &r1, const U &value){
	return (r1 <= Ratio<T>::convertFloatToRatio(value, 4));
}

template <typename T, typename U>
bool operator<=(const U &value, const Ratio<T> &r1){
	return (Ratio<T>::convertFloatToRatio(value, 4) <= r1);
}

template <typename T, typename U>
bool operator>(const Ratio<T> &r1, const Ratio<U> &r2){
	return (r1.getNumerator() * r2.getDenominator() > r1.getDenominator() * r2.getNumerator());
}

template <typename T, typename U>
bool operator>(const Ratio<T> &r1, const U &value){
	return (r1 > Ratio<T>::convertFloatToRatio(value, 4));
}

template <typename T, typename U>
bool operator>(const U &value, const Ratio<T> &r1){
	return (Ratio<T>::convertFloatToRatio(value, 4) > r1);
}

template <typename T, typename U>
bool operator>=(const Ratio<T> &r1, const Ratio<U> &r2){
	return (r1.getNumerator() * r2.getDenominator() >= r1.getDenominator() * r2.getNumerator());
}

template <typename T, typename U>
bool operator>=(const Ratio<T> &r1, const U &value){
	return (r1 >= Ratio<T>::convertFloatToRatio(value, 4));
}

template <typename T, typename U>
bool operator>=(const U &value, const Ratio<T> &r1){
	return (Ratio<T>::convertFloatToRatio(value, 4) >= r1);
}

template <typename T, typename U>
bool operator==(const Ratio<T> &r1, const Ratio<U> &r2){
	return (r1.getNumerator() * r2.getDenominator() == r1.getDenominator() * r2.getNumerator());
}

template <typename T, typename U>
bool operator==(const Ratio<T> &r1, const U &value){
	return (r1 == Ratio<T>::convertFloatToRatio(value, 4));
}

template <typename T, typename U>
bool operator==(const U &value, const Ratio<T> &r1){
	return (r1 == Ratio<T>::convertFloatToRatio(value, 4));
}

template <typename T, typename U>
bool operator!=(const Ratio<T> &r1, const Ratio<U> &r2){
	return (r1.getNumerator() * r2.getDenominator() != r1.getDenominator() * r2.getNumerator());
}

template <typename T, typename U>
bool operator!=(const Ratio<T> &r1, const U &value){
	return (r1 != Ratio<T>::convertFloatToRatio(value, 4));
}

template <typename T, typename U>
bool operator!=(const U &value, const Ratio<T> &r1){
	return (r1 != Ratio<T>::convertFloatToRatio(value, 4));
}

//----------------------------------------------------------------------------------------//

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Ratio<T> &r){
	stream << "(" << r.m_num << "/" << r.m_den << ")";
    return stream;
}

//------------------------------ARITHMETIC+ OPERATORS--------------------------------------//
template <typename T>
Ratio<T> Ratio<T>::sin(const Ratio<T> & r){
	return convertFloatToRatio(std::sin(convertRatioToFloat(r)),4);
}

template <typename T>
Ratio<T> Ratio<T>::cos(const Ratio<T> & r){
	return convertFloatToRatio(std::cos(convertRatioToFloat(r)),4);
}

template <typename T>
Ratio<T> Ratio<T>::tan(const Ratio<T> & r){
	return convertFloatToRatio(std::tan(convertRatioToFloat(r)),4);
}

template <typename T>
Ratio<T> Ratio<T>::exp(const Ratio<T> & r){
	return convertFloatToRatio(std::exp(convertRatioToFloat(r)),4);
}

template <typename T>
Ratio<T> Ratio<T>::ln(const Ratio<T> & r){
	return convertFloatToRatio(std::log(r.m_num) - std::log(r.m_den), 4);
}
template <typename T>
Ratio<T> Ratio<T>::log10(const Ratio<T> & r){
	return convertFloatToRatio(std::log10(r.m_num) - std::log10(r.m_den), 4);
}

template <typename T>
Ratio<T> Ratio<T>::abs(const Ratio<T> & r){
	return Ratio<T>(std::abs(r.m_num),std::abs(r.m_den));
}

template <typename T>
Ratio<T> Ratio<T>::pow(const Ratio<T> & r, const T &n){
	return Ratio<T>(std::pow(r.m_num,n),std::pow(r.m_den,n));
}

template <typename T>
Ratio<T> Ratio<T>::invert(const Ratio<T> &r){
	return Ratio<T>(r.m_den,r.m_num);
}

template <typename T>
Ratio<T> Ratio<T>::sqrt(const Ratio<T> &r){

    if(r.m_num || r.m_den < 0)	{
		throw std::overflow_error("You can't sqrt a negative number !");
	}

	return Ratio<T>(std::sqrt(r.m_num),std::sqrt(r.m_den));
}

//----------------------------------------------------------------------------------------//

//------------------------------FONCTIONS--------------------------------------//
template <typename T>
int Ratio<T>::intPart(const Ratio &r){
	int iterator = 0;
	Ratio<T> error(2,1);

	if(r<1){
		return 0;
	}

	if(r==1){
		return 1;
	}

	while(error>1){
		iterator++;
		error = r - iterator;	
	}

	return iterator;
}
template <typename T>
int Ratio<T>::intPart(const float &x){
	int iterator = 0;
	float error = 2.0;

	if(x<1){
		return 0;
	}

	if(x==1){
		return 1;
	}

	while(error>1){
		iterator++;
		error = x - iterator;
	}
	
	return iterator;
}

template <typename T>
void Ratio<T>::reduce(){

	//si T est un entier, on utilise gcd()
	if constexpr (std::is_integral_v<T>){
		int theGcd = std::__gcd(this->m_num, this->m_den);

		this->m_num = this->m_num / theGcd;
		this->m_den = this->m_den / theGcd;

	} else {
		//sinon on throw une exception
		throw std::invalid_argument("You can't create a ratio with floating values, numerator and denominator must be integers");
	}

	if(this->m_num < 0 && this->m_den < 0){
		this->m_num *= -1;
		this->m_den *= -1;
	}

	if(this->m_den < 0 && this->m_num > 0){	
		this->m_num *= -1;
		this->m_den *= -1;
	}

}

template <typename T>
Ratio<T> Ratio<T>::convertFloatToRatio(const double &x, unsigned int nbIter){

	if(x == 0){
		return Ratio<T>(0,1);
	}

	if(nbIter == 0){
		return Ratio<T>(0,1);
	}

	if( x < 0){
		return -convertFloatToRatio(-x,nbIter);
	}

	if(x < 1){
		return invert(convertFloatToRatio(std::round(1/x * 1000.0) / 1000.0, nbIter));
	}

	if(x >= 1){
		double q = intPart(x);
		return (Ratio<T>(q,1) + convertFloatToRatio(x - q, nbIter - 1));
	}

	return Ratio<T>(0,1);
}

template <typename T>
float Ratio<T>::convertRatioToFloat(const Ratio &r){

	assert((r.getDenominator() != 0) && "m_den should not be 0");
		
    return r.m_num/(float)r.m_den;
}

//----------------------------------------------------------------------------------------//
