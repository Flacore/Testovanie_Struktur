#pragma once

#include "../array/array.h"
#include "../../ds_routines/ds_routines.h"

namespace std {
	class BitSet {
	public:
		BitSet(const int min, const int max) :
			min_(min),
			max_(max),
			BitMap(new structures::Array<int>((max - min) + 1))
		{}

		~BitSet() {
			delete BitMap;
			min_ = 0;
			max_ = 0;
		}

		void insert(const int item);

		void remove(const int item);

		bool isIn(const int item);

		bool operator==(BitSet other);

		bool isSubset(BitSet other);

		BitSet* setUnion(BitSet other);

		BitSet* intersection(BitSet other);

		BitSet* difference(BitSet other);

	private:
		int min_;
		int max_;
		structures::Array<int>* BitMap;

	private:
		int logical_OR(const int item1, const int item2);

		int logical_XOR(const int item1, const int item2);

		int logical_AND(const int item1, const int item2);

		int logical_NEG(const int item1);
	};


	template<typename T>
	class ByteSet {
	public:
		ByteSet(const int min, const int max) {
			size_ = ((max - min) / (sizeof(T) * 8)) + 1;
			min_ = min;
			max_ = max;
			ByteMap = new structures::Array<BitSet*>(size_);
			int i_min = min_;
			int i_max = min_ + size_;
			for (int i = 0; i < size_; i++) {
				(*ByteMap)[i] = new BitSet(i_min, i_max);
				i_min = i_max + 1;
				i_max += (size_ + 1);
			}
		}

		~ByteSet() {
			for (int i = 0; i < size_; i++) {
				delete (*ByteMap)[i];
			}
			delete ByteMap;
			min_ = 0;
			max_ = 0;
			size_ = 0;
		}

		void insert(const int item);

		void remove(const int item);

		bool isIn(const int item);

		bool operator==(ByteSet other);

		bool isSubset(ByteSet other);

		int sizeOfTypename();

		structures::Array<BitSet*>* setUnion(ByteSet other);

		structures::Array<BitSet*>* intersection(ByteSet other);

		structures::Array<BitSet*>* difference(ByteSet other);

	private:
		int size_;
		int min_;
		int max_;
		structures::Array<BitSet*>* ByteMap;
	};

	inline void BitSet::insert(const int item)
	{
		if (item >= min_ || item <= max_) {
			int index = item - min_;
			(*BitMap)[index] = 1;
		}
	}

	inline void BitSet::remove(const int item)
	{
		if (item >= min_ || item <= max_) {
			int index = item - min_;
			(*BitMap)[index] = 0;
		}
	}

	inline bool BitSet::isIn(const int item)
	{
		if (item >= min_ || item <= max_) {
			int index = item - min_;
			if ((*BitMap)[index] == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}

	inline bool BitSet::operator==(BitSet other)
	{
		if (other.max_ == max_ && other.min_ == min_) {
			for (int i = 0; i <= (max_ - min_); i++) {
				if (!(BitMap[i] == other.BitMap[i])) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	inline bool BitSet::isSubset(BitSet other)
	{
		if (other.max_ >= max_ && other.min_ <= min_) {
			for (int i = 0; i <= (max_ - min_); i++) {
				if (!(BitMap[i] == other.BitMap[i] && other.BitMap[i] == 1)) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	inline BitSet* BitSet::setUnion(BitSet other)
	{
		int tmp_min = 0;
		if (other.min_ > min_) {
			tmp_min = min_;
		}
		else {
			tmp_min = other.min_;
		}
		int tmp_max = 0;
		if (other.max_ < max_) {
			tmp_max = max_;
		}
		else {
			tmp_max = other.max_;
		}
		BitSet* newBitSet = new BitSet(tmp_min, tmp_max);
		for (int i = 0; i <= (tmp_max - tmp_min); i++) {
			int item1, item2;
			item1 = item2 = 0;
			if (tmp_min + i >= other.min_ && tmp_min + i <= other.max_) {
				item1 = (*other.BitMap)[i];
			}
			if (tmp_min + i >= min_ && tmp_min + i <= max_) {
				item1 = (*BitMap)[i];
			}
			newBitSet->BitMap[i] = logical_OR(item1, item2);
		}

		return newBitSet;
	}

	inline BitSet* BitSet::intersection(BitSet other)
	{
		int tmp_min = 0;
		if (other.min_ <= min_) {
			tmp_min = min_;
		}
		else {
			tmp_min = other.min_;
		}
		int tmp_max = 0;
		if (other.max_ >= max_) {
			tmp_max = max_;
		}
		else {
			tmp_max = other.max_;
		}
		BitSet* newBitSet = new BitSet(tmp_min, tmp_max);
		for (int i = 0; i <= (tmp_max - tmp_min); i++) {
			int item1, item2;
			item1 = item2 = 0;
			if (tmp_min + i >= other.min_ && tmp_min + i <= other.max_) {
				item1 = (*other.BitMap)[i];
			}
			if (tmp_min + i >= min_ && tmp_min + i <= max_) {
				item1 = (*BitMap)[i];
			}
			newBitSet->BitMap[i] = logical_OR(item1, item2);
		}

		return newBitSet;
	}

	inline BitSet* BitSet::difference(BitSet other)
	{
		int tmp_min = 0;
		if (other.min_ > min_) {
			tmp_min = min_;
		}
		else {
			tmp_min = other.min_;
		}
		int tmp_max = 0;
		if (other.max_ < max_) {
			tmp_max = max_;
		}
		else {
			tmp_max = other.max_;
		}
		BitSet* newBitSet = new BitSet(tmp_min, tmp_max);
		for (int i = 0; i <= (tmp_max - tmp_min); i++) {
			int item1, item2;
			item1 = item2 = 0;
			if (tmp_min + i >= other.min_ && tmp_min + i <= other.max_) {
				item1 = (*other.BitMap)[i];
			}
			if (tmp_min + i >= min_ && tmp_min + i <= max_) {
				item2 = (*BitMap)[i];
			}
			newBitSet->BitMap[i] = logical_XOR(item1, item2);
		}

		return newBitSet;
	}

	inline int BitSet::logical_OR(const int item1, const int item2)
	{
		if (item1 == item2 && item1 == 0) {
			return 0;
		}
		return 1;
	}

	inline int BitSet::logical_XOR(const int item1, const int item2)
	{
		if (item1 == item2) {
			return 0;
		}
		return 1;
	}

	inline int BitSet::logical_AND(const int item1, const int item2)
	{
		if (item1 == item2 && item1 == 1) {
			return 1;
		}
		return 0;
	}

	inline int BitSet::logical_NEG(const int item1)
	{
		if (item1 == 0) {
			return 1;
		}
		return 0;
	}

		template<typename T>
		inline void ByteSet<T>::insert(const int item)
		{
			if (item <= max_ && item >= min_) {
				int index = 0;
				int i_min = min_;
				int i_max = min_ + size_;
				for (int i = 0; i < size_; i++) {
					i_min = i_max + 1;
					i_max += (size_ + 1);
					if (i_min <= item && i_max >= item) {
						index = i+1;
						break;
					}
				}
				(*(*ByteMap)[index]).insert(item);
			}
		}

		template<typename T>
		inline void ByteSet<T>::remove(const int item)
		{
			if (item <= max_ && item >= min_) {
				int index = 0;
				int i_min = min_;
				int i_max = min_ + size_;
				for (int i = 0; i < size_; i++) {
					i_min = i_max + 1;
					i_max += (size_ + 1);
					if (i_min <= item && i_max >= item) {
						index = i + 1;
						break;
					}
				}
				(*(*ByteMap)[index]).remove(item);
			}
		}

		template<typename T>
		inline bool ByteSet<T>::isIn(const int item)
		{
			if (item <= max_ && item >= min_) {
				int index = 0;
				int i_min = min_;
				int i_max = min_ + size_;
				for (int i = 0; i < size_; i++) {
					i_min = i_max + 1;
					i_max += (size_ + 1);
					if (i_min <= item && i_max >= item) {
						index = i;
						break;
					}
				}
				return (*(*ByteMap)[index]).isIn(item);
			}
			return false;
		}

		template<typename T>
		inline bool ByteSet<T>::operator==(ByteSet<T> other)
		{
			if (other.max_ == max_ && other.min_ == min_) {
				if (other.sizeOfTypename() == sizeOfTypename()) {
					for (int i = 0; i <= (max_ - min_); i++) {
						if (!((*ByteMap)[i] == (*other.ByteMap)[i])) {
							return false;
						}
					}
				}
				return true;
			}
			return false;
		}

		template<typename T>
		inline bool ByteSet<T>::isSubset(ByteSet<T> other)
		{
			if (other.max_ >= max_ && other.min_ <= min_) {
				if (other.sizeOfTypename() >= sizeOfTypename()) {
					for (int i = 0; i <= (max_ - min_); i++) {
						if (!( (*(*ByteMap)[i]).isSubset((*(*other.ByteMap)[i])) )) {
							return false;
						}
					}
					return true;
				}
			}
			return false;
		}

		template<typename T>
		int ByteSet<T>::sizeOfTypename()
		{
			return sizeof(T);
		}

		template<typename T>
		inline structures::Array<BitSet*>* ByteSet<T>::setUnion(ByteSet<T> other)
		{
			structures::DSRoutines::rangeCheckExcept(sizeOfTypename(), other.sizeOfTypename(), "The sets of diferent typename!");

			int tmp_min, tmp_max = tmp_min = 0;
			if (other.min_ > min_)
			{
				tmp_min = min_;
			}
			else
			{
				tmp_min = other.min_;
			}
			if (other.max_ < max_) {
				tmp_max = max_;
			}
			else {
				tmp_max = other.max_;
			}

			structures::Array<BitSet*>* newByteSet = new structures::Array<BitSet*>(((tmp_max - tmp_min) / sizeof(T) * 8) + 1);
			for (int i = 0; i < (*newByteSet).size(); i++) {
				(*newByteSet)[i] = (*(*ByteMap)[i]).setUnion((*(*other.ByteMap)[i]));
			}

			return newByteSet;
		}

		template<typename T>
		inline structures::Array<BitSet*>* ByteSet<T>::intersection(ByteSet<T> other)
		{
			structures::DSRoutines::rangeCheckExcept(sizeOfTypename(), other.sizeOfTypename(), "The sets of diferent typename!");

			int tmp_min, tmp_max = tmp_min = 0;
			if (other.min_ < min_)
			{
				tmp_min = min_;
			}
			else
			{
				tmp_min = other.min_;
			}
			if (other.max_ > max_) {
				tmp_max = max_;
			}
			else {
				tmp_max = other.max_;
			}
			structures::Array<BitSet*>* newByteSet = new structures::Array<BitSet*>(((tmp_max - tmp_min) / sizeof(T) * 8) + 1);
			for (int i = 0; i < (*newByteSet).size(); i++) {
				(*newByteSet)[i] = (*(*ByteMap)[i]).intersection((*(*other.ByteMap)[i]));
			}

			return newByteSet;
		}

		template<typename T>
		inline structures::Array<BitSet*>* ByteSet<T>::difference(ByteSet<T> other)
		{
			structures::DSRoutines::rangeCheckExcept(sizeOfTypename(), other.sizeOfTypename(), "The sets of diferent typename!");

			int tmp_min, tmp_max = tmp_min = 0;
			if (other.min_ > min_)
			{
				tmp_min = min_;
			}
			else
			{
				tmp_min = other.min_;
			}
			if (other.max_ < max_) {
				tmp_max = max_;
			}
			else {
				tmp_max = other.max_;
			}
			structures::Array<BitSet*>* newByteSet = new structures::Array<BitSet*>(((tmp_max - tmp_min) / sizeof(T) * 8) + 1);
			for (int i = 0; i < (*newByteSet).size(); i++) {
				(*newByteSet)[i] = (*(*ByteMap)[i]).difference((*(*other.ByteMap)[i]));
			}

			return newByteSet;
		}
}