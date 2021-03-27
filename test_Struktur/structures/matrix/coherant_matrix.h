#pragma once

#include "../array/array.h"
#include"../list/list.h"

namespace structures
{
	template<typename T>
	class CoherantMatrix
	{
	public:

		CoherantMatrix(const size_t size_x, const size_t size_y) ;

		CoherantMatrix(const CoherantMatrix<T>& other) ;

		~CoherantMatrix() ;

		T& operator[](const int index) ;

		const T operator[](const int index)const;

		T& operator()(const int index_x, const int index_y);

		const T operator()(const int index_x,const int index_y)const;

		Structure& operator=(const Structure& other) ;

		CoherantMatrix<T>& operator=(const CoherantMatrix<T>& other) ;

	private:
		Array<T>* array_;
		size_t size_x;
		size_t size_y;
	};

	template<typename T>
	inline CoherantMatrix<T>::CoherantMatrix(const size_t size_x, const size_t size_y) :
		array_(new Array<T>(size_x* size_y)),
		size_x(size_x),
		size_y(size_y)
	{
	}

	template<typename T>
	inline CoherantMatrix<T>::CoherantMatrix(const CoherantMatrix<T>& other) :
		array_(new Array<T>((*other.size_x)*(*other.size_y))),
		size_x(other.size_x),
		size_y(other.size_y)
	{
	}

	template<typename T>
	inline CoherantMatrix<T>::~CoherantMatrix()
	{
		delete array_;
		array_ = nullptr;
		size_x = 0;
		size_y = 0;
	}

	template<typename T>
	inline T& CoherantMatrix<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_x* size_y, "Ivalid index.");
		return (*array_)[ index];
	}

	template<typename T>
	inline const T CoherantMatrix<T>::operator[](const int index) const
	{
	    DSRoutines::rangeCheckExcept( index, size_x* size_y, "Ivalid index.");
		return (*array_)[ index];
	}

	template<typename T>
	inline T& CoherantMatrix<T>::operator()(const int index_x, const int index_y)
	{
		DSRoutines::rangeCheckExcept(index_x*index_y, size_x * size_y, "Ivalid index.");
		return (*array_)[index_x * index_y];
	}

	template<typename T>
	inline const T CoherantMatrix<T>::operator()(const int index_x, const int index_y) const
	{
		DSRoutines::rangeCheckExcept(index_x * index_y, size_x * size_y, "Ivalid index.");
		return (*array_)[index_x * index_y];
	}

	template<typename T>
	Structure& CoherantMatrix<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const CoherantMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	CoherantMatrix<T>& CoherantMatrix<T>::operator=(const CoherantMatrix<T>& other)
	{
		if (this != &other)
		{
			if (size_x != other.size_x)
				throw std::invalid_argument("Matrix's sizes is different!");
			if (size_y != other.size_y)
				throw std::invalid_argument("Matrix's sizes is different!");
			*array_ = *other.array_;
		}
		return *this;
	}
}
