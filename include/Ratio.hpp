#ifndef RATIONNAL_H
#define RATIONNAL_H

#pragma once

#include <iostream>
#include <numeric>
#include <limits>
#include <fstream>
#include <cmath>

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

//git test

/// \class Ratio
/// \brief class defining a ratio number.
template <typename T>
class Ratio{

	private : 
		T m_num;
		T m_den;

	public :
		// default constructor
		Ratio() = default;

		/// \brief constructor from a numerator and denominator
		/// \param nominator : the nominator of the rational number
		/// \param denominator : the denominator of the rational number
		Ratio(const T& nominator, const T &denominator) : m_num(nominator), m_den(denominator) {};

		/// \brief constructor from another rational number
		/// \param ratio the other rational number
		Ratio(const Ratio &ratio) = default;

		/// \brief destructor
		~Ratio() = default;

		/// \brief getter of the nominator
		inline T & nominator() {return m_num;};
		/// \brief getter of the denominator
		inline T & denominator() {return m_den;};
		/// \brief setter of the nominator
		inline const T & nominator() const {return m_num;};
		/// \brief setter of the denominator
		inline const T & denominator() const {return m_den;};

		/// \brief operator addition for rational numbers
		/// \param r the rational number to be added
		Ratio operator+(const Ratio &r) const;
		/// \brief operator soustraction for rational numbers
		/// \param r the rational number to substract
		Ratio operator-(const Ratio &r) const;
		/// \brief operator multiply for rational numbers
		/// \param r the rational number to multiply
		Ratio operator*(const Ratio &r) const;
		/// \brief operator divide for rational numbers
		/// \param r the rational number to divide
		Ratio operator/(const Ratio &r) const;

		//inline friend Ratio operator*(const T &value, const Ratio &r) {return r*value;};
		//inline friend Ratio operator/(const T &value, const Ratio &r) {return Ratio(value)/r;};
		//inline friend Ratio operator-(const Ratio &r) {return Ratio(-r.m_num,-r.m_den);}; // unary minus

		/// \brief operator print for rational numbers
		/// \param r the rational number to print
		template<typename U>
        friend std::ostream& operator<< (std::ostream& stream, const Ratio<U> &r);

        void testRatioNumber();


};

template <typename T>
Ratio<T> Ratio<T>::operator+(const Ratio<T> &r) const {
	return Ratio<T>(this->m_num * r.m_den +this->m_den * r.m_num, this->m_den * r.m_den);
}

template <typename T>
Ratio<T> Ratio<T>::operator-(const Ratio<T> &r) const {
	return Ratio<T>(this->m_num * r.m_den - this->m_den * r.m_num, this->m_den * r.m_den);
}


template <typename T>
Ratio<T> Ratio<T>::operator*(const Ratio<T> &r) const {
	return Ratio<T>(this->m_num* r.m_num, this->m_den*r.m_den);
}


template <typename T>
Ratio<T> Ratio<T>::operator/(const Ratio<T> &r) const {
	return Ratio<T>(this->m_num * r.m_den, r.m_num * this->m_den);
}

template<typename T>
std::ostream& operator<< (std::ostream& stream, const Ratio<T> &r){
	stream << "(" << r.m_num << "/" << r.m_den << ")";
    return stream;
}

#endif