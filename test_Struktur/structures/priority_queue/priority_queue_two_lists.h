#pragma once

#define DEFAULT_MIN 4

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();
		PriorityQueueTwoLists(const int tmp);
		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other);
		///Move constructor
		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>&& other);
		~PriorityQueueTwoLists();

		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany dvojzoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>& other);

		///Move semantika
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>&& other);

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() const override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		void push(const int priority, const T& data) override;

		void setCapacityOfShortlist(const int size_);


		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		const T peek() const override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		int peekPriority() const override;
	
	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const int tmp) :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>(tmp)),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		*this = other;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>&& other)
	{
		this->shortList_ = other.shortList_;
		this->longList_ = other.longList_;

		other.shortList_ = nullptr;
		other.longList_ = nullptr;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		delete shortList_;
		shortList_ = nullptr;
		delete longList_;
		longList_ = nullptr;
	}

	template<typename T>
	Structure * PriorityQueueTwoLists<T>::clone() const
	{
		return new PriorityQueueTwoLists<T>(*this);
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueue<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueTwoLists<T>&>(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>& other)
	{
		if(this == &other)
			return *this;
		shortList_ = other.shortList_;
		longList_ = other.longList_;
		return *this;
	}

	//Move priradenie
	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>&& other) {
		if (this != other) {
			delete shortList_;
			delete longList_;

			this->shortList_ = other.shortList_;
			this->longList_ = other.longList_;

			other.shortList_ = nullptr;
			other.longList_ = nullptr;
		}
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size() const
	{
		return longList_->size() + shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		shortList_->clear();
		longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(const int priority, const T & data)
	{
		if (shortList_->minPriority() < priority || longList_->size() == 0) {
			PriorityQueueItem<T>* item = shortList_->pushAndRemove(priority, data);
			if (item != nullptr) {
				longList_->add(item);
			}
		}
		else {
			PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
			longList_->add(item);
		}
	}

	template<typename T>
	inline void PriorityQueueTwoLists<T>::setCapacityOfShortlist(const int size_)
	{
		shortList_->trySetCapacity(size_);
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		T item_ = 0;
		if (!shortList_->isEmpty()) {
			item_ = shortList_->pop();
			if (shortList_->isEmpty() && longList_->size() != 0) {
				if (sqrt(longList_->size()) > DEFAULT_MIN) {
					bool returnVal = shortList_->trySetCapacity(sqrt(longList_->size()));
					LinkedList<PriorityQueueItem<T>*>* queue = new LinkedList<PriorityQueueItem<T>*>();
					for (PriorityQueueItem<T>* item : *longList_) {
						queue->add(shortList_->pushAndRemove(item->getPriority(), item->accessData()));
					}
					delete longList_;
					longList_ = queue;
					delete queue;
				}
			}
		}
		return item_;
	}

	template<typename T>
	T & PriorityQueueTwoLists<T>::peek()
	{
		return shortList_->peek();
	}

	template<typename T>
	const T PriorityQueueTwoLists<T>::peek() const
	{
		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority() const
	{
		return shortList_->peekPriority();
	}
}