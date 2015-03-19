#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>

namespace SMO {
	template < typename T, int SIZE = 5>
	class Matrix {
	private:
		T * ptr;
		int n_;
		int m_;
	public:
		static int count;

		//Default constructor 
		Matrix() :n_(SIZE), m_(SIZE) { ptr = new T[SIZE*SIZE]; count++; std::cout << "Constr 1 \n"; }

		//Default constructor 
		Matrix(int n, int m) :n_(n), m_(m) { ptr = new T[n_*m_]; count++; std::cout << "Constr 2 \n"; }

		//Copy Constructor  
		Matrix(const Matrix & ma) :n_(ma.n_), m_(ma.m_) {
			ptr = new T[n_*m_];
			std::memcpy(ptr, ma.ptr, n_*m_*sizeof(T));
			count++; std::cout << "Constr 3 \n";
		}

		//Assignement constructor 
		/*	Matrix & operator=(const Matrix & cp) {
		m_ = cp.m_;
		n_ = cp.n_;
		if(ptr != cp.ptr) {
		if(ptr) delete[] ptr;
		ptr = new T[m_*n_]; memcpy(ptr, cp.ptr, m_*n_*sizeof(T));
		}
		return *this;
		}
		*/
		void swap(Matrix & other) { swap(m_, other.m_); swap(n_, other.n_); swap(ptr, other.ptr); }
		Matrix & operator=(Matrix other) { swap(other, *this); return *this; }
		//assignment with swap 
		/*	Matrix& operator=(Matrix ma){

		if(ptr)delete [] ptr;
		std::swap(n_,ma.n_);
		std::swap(m_,ma.m_);
		//std::swap(ptr,ma.ptr);
		ptr = new T[n_*m_] ;
		std::memcpy (ptr,ma.ptr, n_*m_*sizeof(T) );
		std::cout<<"=operator"<<std::endl;
		return *this;

		}
		*/

		Matrix(Matrix&& mv) : n_(mv.n_), m_(mv.m_), ptr(mv.ptr) { std::cout << "Move copy constructor" << std::endl;  mv.ptr = 0; }

		Matrix& operator=(Matrix && mv) {
			m_ = mv.m_;
			n_ = mv.n_;
			ptr = mv.ptr;
			mv.ptr = 0;
			std::cout << "Move assignment" << std::endl;
			return *this;
		}

		Matrix  operator+(const Matrix & rv) {
			Matrix Tmp(rv);
			for (int i = 0; i< rv.n_*rv.m_; ++i)
				Tmp.ptr[i] += ptr[i];
			return Tmp;
		}


		/*
		void swap(Matrix & other) { swap(m, other.m); swap(n, other.n); swap(ptr, other.ptr); }
		Matrix & operator=(Matrix other) { swap(other, *this); return *this; }
		*/
		/*Matrix & operator=(Matrix && mv) {
		m = cp.m;
		n = cp.n;
		ptr = mv.ptr;
		mv.ptr = 0;
		return *this;
		}*/


		bool operator==(const Matrix &other) {
			if (n_ != other.n_) return false;
		}
		~Matrix() {
			count--;
			std::cout << "Destr \n";
			if (ptr)
				delete[] ptr;

		}
		int getElement(int n) const {
			return ptr[n];
		}

		void init() {
			for (auto i = 0; i <n_*m_; ++i)
				ptr[i] = i;
		}

	};

}

template <>
int SMO::Matrix<int>::count = 0;

int main() {
	SMO::Matrix<int> T;
	SMO::Matrix<int> T1(2, 2);
	T.init();
	T1.init(); //
	std::cout << T1.getElement(6) << "\n";
	std::cout << SMO::Matrix<int>::count << "\n";

	std::cout << " \n Dec 2 ";

	SMO::Matrix<int> T2(T1);
	std::cout << SMO::Matrix<int>::count << "\n";

	SMO::Matrix<int> T3, T4;
	T3.init();
	T4.init();
	T3 = T4 + T4;
	return 0;
}