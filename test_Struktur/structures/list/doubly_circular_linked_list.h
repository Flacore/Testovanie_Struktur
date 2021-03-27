#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../../ds_routines/ds_routines.h"

namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class DoublyCircularLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		DoublyCircularLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		DoublyCircularLinkedListItem(const DoublyCircularLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~DoublyCircularLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		DoublyCircularLinkedListItem<T>* getNext();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(DoublyCircularLinkedListItem<T>* next);

		DoublyCircularLinkedListItem<T>* getPrevious();

		void setPrevious(DoublyCircularLinkedListItem<T>* previous);

	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		DoublyCircularLinkedListItem<T>* next_;
		DoublyCircularLinkedListItem<T>* previous_;
	};

	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoublyCircularLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		DoublyCircularLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other);

		///Move constructor
		DoublyCircularLinkedList(const DoublyCircularLinkedList<T>&& other);

		/// <summary> Destruktor. </summary>
		~DoublyCircularLinkedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		DoublyCircularLinkedList<T>& operator=(const DoublyCircularLinkedList<T>& other);

		///Move semantik
		DoublyCircularLinkedList<T>& operator=(const DoublyCircularLinkedList<T>&& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		DoublyCircularLinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		DoublyCircularLinkedListItem<T>* last_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		DoublyCircularLinkedListItem<T>* getItemAtIndex(int index) const;
	private:
		/// <summary> Iterator pre LinkedList. </summary>
		class DoublyCircularLinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			DoublyCircularLinkedListIterator(DoublyCircularLinkedListItem<T>* position);

			/// <summary> Destruktor. </summary>
			~DoublyCircularLinkedListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Aktualna pozicia v zozname. </summary>
			DoublyCircularLinkedListItem<T>* position_;
		};
	};

	template<typename T>
	inline DoublyCircularLinkedListItem<T>::DoublyCircularLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		previous_(nullptr)
	{
	}

	template<typename T>
	inline  DoublyCircularLinkedListItem<T>::DoublyCircularLinkedListItem(const  DoublyCircularLinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_),
		previous_(other.previous_)
	{
	}

	template<typename T>
	inline  DoublyCircularLinkedListItem<T>::~DoublyCircularLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}

	template<typename T>
	inline  DoublyCircularLinkedListItem<T>* DoublyCircularLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline void  DoublyCircularLinkedListItem<T>::setNext(DoublyCircularLinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline  DoublyCircularLinkedListItem<T>* DoublyCircularLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}

	template<typename T>
	inline void  DoublyCircularLinkedListItem<T>::setPrevious(DoublyCircularLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}


	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedList() :
		List<T>::List(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other) :
		DoublyCircularLinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedList(const DoublyCircularLinkedList<T>&& other)
	{
		size_ = other.size_;
		first_ = other.first_;
		last_ = other.last_;

		other.last_ = nullptr;
		other.first_ = nullptr;
		other.size_ = 0;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::~DoublyCircularLinkedList()
	{
		clear();
	}

	template<typename T>
	inline Structure* DoublyCircularLinkedList<T>::clone() const
	{
		return new DoublyCircularLinkedList<T>(*this);
	}

	template<typename T>
	inline size_t DoublyCircularLinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& DoublyCircularLinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const DoublyCircularLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	DoublyCircularLinkedList<T>& DoublyCircularLinkedList<T>::operator=(const DoublyCircularLinkedList<T>&& other) {
		if (this != &other)
		{
			clear();
			DoublyCircularLinkedListItem<T>* currentLLI = other.first_;
			while (currentLLI != nullptr)
			{
				add(currentLLI->accessData());
				currentLLI = currentLLI->getNext();
			}
		}
		return *this;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>& DoublyCircularLinkedList<T>::operator=(const DoublyCircularLinkedList<T>& other)
	{
		if (this != &other)
		{
			clear();
			for (T data : other)
			{
				add(data);
			}
		}
		return *this;
	}

	template<typename T>
	inline T& DoublyCircularLinkedList<T>::operator[](const int index)
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T DoublyCircularLinkedList<T>::operator[](const int index) const
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::add(const T& data)
	{
		DoublyCircularLinkedListItem<T>* newLLI = new DoublyCircularLinkedListItem<T>(data);
		if (first_ == nullptr || size_ == 0) {
			first_ = newLLI;
			first_->setNext(newLLI);
			first_->setPrevious(newLLI);
		}
		else {
			last_->setNext(newLLI);
			first_->setPrevious(newLLI);
		}
		last_ = newLLI;
		last_->setNext(first_);
		size_++;
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::insert(const T& data, const int index)
	{
		if (index == size_) {
			add(data);
		}
		else {
			if (index == 0) {
				DoublyCircularLinkedListItem<T>* newLLI = new DoublyCircularLinkedListItem<T>(data);
				newLLI->setNext(first_);
				newLLI->setPrevious(last_);
				first_->setPrevious(newLLI);
				first_ = newLLI;
			}
			else
			{
				DoublyCircularLinkedListItem<T>* prevLLI = getItemAtIndex(index - 1);
				DoublyCircularLinkedListItem<T>* newLLI = new DoublyCircularLinkedListItem<T>(data);
				newLLI->setNext(prevLLI->getNext());
				newLLI->setPrevious(prevLLI);
				prevLLI->setNext(newLLI);
			}
			size_++;
		}
	}

	template<typename T>
	inline bool DoublyCircularLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);
		if (index != -1) {
			removeAt(index);
			return true;
		}
		else {
			return false;
		}
	}

	template<typename T>
	inline T DoublyCircularLinkedList<T>::removeAt(const int index)
	{
		T item = 0;
		DoublyCircularLinkedListItem<T>* deleteLLI = nullptr;
		if (index == 0 && size_ > 0) {
			deleteLLI = first_;
			item = deleteLLI->accessData();
			first_ = first_->getNext();
			first_->setPrevious(last_);
			if (deleteLLI == last_) {
				last_ = nullptr;
			}
		}
		else {
			if (index != size_ - 1) {
				DoublyCircularLinkedListItem<T>* prevLLI = getItemAtIndex(index - 1);
				deleteLLI = prevLLI->getNext();
				item = deleteLLI->accessData();
				prevLLI->setNext(deleteLLI->getNext());
				(deleteLLI->getNext())->setPrevious(prevLLI);
				if (deleteLLI == last_) {
					last_ = prevLLI;
				}
			}
		}
		size_--;
		return item;
	}

	template<typename T>
	inline int DoublyCircularLinkedList<T>::getIndexOf(const T& data)
	{
		int index = 0;
		DoublyCircularLinkedListItem<T>* currentLLI = first_;
		while (index != size_) {
			if (currentLLI->accessData() == data) {
				return index;
			}
			index++;
			currentLLI = currentLLI->getNext();
		}
		return-1;
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::clear()
	{
		DoublyCircularLinkedListItem<T>* currentLLI = first_;
		int i = 0;
		while (i != size()) {
			DoublyCircularLinkedListItem<T>* deleteLLI = currentLLI;
			currentLLI = currentLLI->getNext();
			delete deleteLLI;
			i++;
		}
		first_ = last_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* DoublyCircularLinkedList<T>::getBeginIterator() const
	{
		return new DoublyCircularLinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* DoublyCircularLinkedList<T>::getEndIterator() const
	{
		return new DoublyCircularLinkedListIterator(last_);
	}

	template<typename T>
	inline  DoublyCircularLinkedListItem<T>* DoublyCircularLinkedList<T>::getItemAtIndex(int index) const
	{
		if (index == size_ - 1) {
			return last_;
		}
		else {
			DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
			DoublyCircularLinkedListItem<T>* currentLLI = first_;
			for (int i = 0; i < index; i++)
			{
				currentLLI = currentLLI->getNext();
			}
			return currentLLI;
		}
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::DoublyCircularLinkedListIterator(DoublyCircularLinkedListItem<T>* position) :
		position_(position)
	{
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::~DoublyCircularLinkedListIterator()
	{
		position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator=(const Iterator<T>& other)
	{
		position_ = dynamic_cast<const DoublyCircularLinkedListIterator&>(other).position_;
		return *this;
	}

	template<typename T>
	inline bool DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator!=(const Iterator<T>& other)
	{
		return position_ != dynamic_cast<const DoublyCircularLinkedListIterator&>(other).position_;
	}

	template<typename T>
	inline const T DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator*()
	{
		return position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator++()
	{
		position_ = position_->getNext();
		return *this;
	}

}