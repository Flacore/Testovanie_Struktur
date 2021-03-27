#pragma once

#include "../array/array.h"

namespace structures
{
	template<typename T>
	class IncoherantMatrix
	{
	public:

		IncoherantMatrix(const size_t size_x, const size_t size_y);

		IncoherantMatrix(const IncoherantMatrix<T>& other);

		~IncoherantMatrix();

		Array<T>* operator[](const int index);

		T& operator()(const int index_x, const int index_y);

		const T operator()(const int index_x, const int index_y)const;

		Structure& operator=(const Structure& other);

		IncoherantMatrix<T>& operator=(const IncoherantMatrix<T>& other);

	private:
		Array<Array<T>*>* array_;
		size_t size_x;
		size_t size_y;
	};

	template<typename T>
	inline IncoherantMatrix<T>::IncoherantMatrix(const size_t size_x, const size_t size_y) :
		array_(new Array<Array<T>*>(size_x)),
		size_x(size_x),
		size_y(size_y)
	{
		for (int x = 0; x < size_x;x++) {
			(*array_)[x] = new Array<T>(size_y);
		}
	}

	template<typename T>
	inline  IncoherantMatrix<T>::IncoherantMatrix(const IncoherantMatrix<T>& other) :
		array_(new Array<< Array<T >>((*other.size_x)* (*other.size_y))),
		size_x(other.size_x),
		size_y(other.size_y)
	{
		for (int x = 0; x < size_x; x++) {
			(*array_)[x] = (*other.array_)[x];
		}
	}

	template<typename T>
	inline  IncoherantMatrix<T>::~IncoherantMatrix()
	{
		delete array_;
		array_ = nullptr;
		size_x = 0;
		size_y = 0;
		for (int x = 0; x < size_x;x++) {
			delete((*array_)[x]);
		}
		delete(array_);
	}

	template<typename T>
	Array<T>* IncoherantMatrix<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_x * size_y, "Ivalid index.");
		return (*array_)[index];
	}

	template<typename T>
	inline T& IncoherantMatrix<T>::operator()(const int index_x, const int index_y)
	{
		DSRoutines::rangeCheckExcept(index_x * index_y, size_x * size_y, "Ivalid index.");
		return (*(*array_)[index_x])[index_y];
	}

	template<typename T>
	inline const T IncoherantMatrix<T>::operator()(const int index_x, const int index_y) const
	{
		DSRoutines::rangeCheckExcept(index_x * index_y, size_x * size_y, "Ivalid index.");
		return (*(*array_)[index_x])[index_y];
	}

	template<typename T>
	Structure& IncoherantMatrix<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const IncoherantMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	IncoherantMatrix<T>& IncoherantMatrix<T>::operator=(const IncoherantMatrix<T>& other)
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