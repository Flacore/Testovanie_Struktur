#pragma once
#include "../../structures/priority_queue/heap.h";
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h";

#include <string>

#include "../time.h";

#define POCET_OPERACII 100000
#define FILE "vysledky/uloha2/"

namespace std {
	class ADT_PriorityFront {
	public:
		ADT_PriorityFront(const int vloz, const int vyber, const int ukaz , std::string scnr) :
			scenarioName(scnr),
			vloz_(vloz),
			vyber_(vyber+vloz),
			ukaz_(ukaz+vyber+vloz),

			nazov_operacie_(new std::string[POCET_OPERACII]),
			cas_operacie_Heap(new double[POCET_OPERACII]),
			cas_operacie_Array(new double[POCET_OPERACII]),

			heap_(new structures::Heap<int>()),
			array_(new structures::PriorityQueueSortedArrayList<int>())
		{
			recap = i = count_i = count_g = count_s = 0;
		}

		~ADT_PriorityFront() {
			scenarioName = "";
			recap = i = vloz_ = vyber_ = ukaz_ = 0;
			count_i = count_g = count_s = 0;
			delete heap_;
			delete array_;

			//delete nazov_operacie_;
			delete cas_operacie_Array;
			delete cas_operacie_Heap;
		}

		void do_testing();
	private:
		std::string scenarioName;

		int i,recap;
		int vloz_;
		int vyber_;
		int ukaz_;

		int count_i;
		int count_g;
		int count_s;

		structures::Heap<int>* heap_;
		structures::PriorityQueueSortedArrayList<int>* array_;

		std::string* nazov_operacie_;
		double* cas_operacie_Heap;
		double* cas_operacie_Array;

		Time time_;
	private:

		void oInsert();

		void oGet();

		void oShow();

		void saveToFiles();
	};

	inline void ADT_PriorityFront::do_testing()
	{
		int choice = 0;

		for (i = 0; i < POCET_OPERACII; i++) {
			choice = (rand() % 100) + 0;

			if (choice <= vloz_ || recap > 5) {
				choice = 1;
				oInsert();
			}
			if (vloz_ < choice && choice <= vyber_) {
				oGet();
			}
			if (vyber_ < choice && choice <= ukaz_) {
				oShow();
			}
		}

		saveToFiles();
	}

	inline void ADT_PriorityFront::oInsert()
	{
		if (POCET_OPERACII * (double(vloz_) / 100) > count_i || recap > 5) {
			int priority = 0;
			int value = 0;

			time_.setStart();
			heap_->push(priority, value);
			time_.setEnd();
			(cas_operacie_Heap)[i] = time_.getDuration();

			time_.setStart();
			array_->push(priority, value);
			time_.setEnd();
			(cas_operacie_Array)[i] = time_.getDuration();

			(nazov_operacie_)[i] = "1. Vloz.";

			count_i++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_PriorityFront::oGet()
	{
		if (POCET_OPERACII * (double(vyber_ - vloz_) / 100) > count_g && count_i > 0) {
			int trashbin_ = 0;

			time_.setStart();
			trashbin_ = heap_->pop();
			time_.setEnd();
			(cas_operacie_Heap)[i] = time_.getDuration();

			time_.setStart();
			trashbin_ = array_->pop();
			time_.setEnd();
			(cas_operacie_Array)[i] = time_.getDuration();
			
			(nazov_operacie_)[i] = "2. Vyber.";

			count_g++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_PriorityFront::oShow()
	{
		if (POCET_OPERACII * (double(ukaz_ - vyber_) / 100) > count_s && count_i > 0) {
			int trashbin_ = 0;

			time_.setStart();
			trashbin_ = heap_->peek();
			time_.setEnd();
			(cas_operacie_Heap)[i] = time_.getDuration();

			time_.setStart();
			trashbin_ = array_->peek();
			time_.setEnd();
			(cas_operacie_Array)[i] = time_.getDuration();

			(nazov_operacie_)[i] = "3. Ukaz.";

			count_s++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_PriorityFront::saveToFiles()
	{
		file* file_ = new file(FILE, scenarioName);

		file_->addItem("n,Nazov Operacie,Cas Array list,Cas Heap,");
		file_->newLine();

		for (int n = 0; n < POCET_OPERACII; n++) {
			file_->addItem(to_string(n + 1));
			file_->addComma();
			file_->addItem((nazov_operacie_)[n]);
			file_->addComma();
			file_->addItem(to_string((cas_operacie_Array)[n]));
			file_->addComma();
			file_->addItem(to_string((cas_operacie_Heap)[n]));
			if (n < POCET_OPERACII - 1) {
				file_->newLine();
			}
		}

		std::string name = FILE;

		file_->saveFile();
		delete file_;
	}

}