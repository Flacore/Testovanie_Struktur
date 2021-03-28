#pragma once

#include "../../structures/list/array_list.h";
#include "../../structures/list/linked_list.h";

#include <string>

#include "../file.h";
#include "../time.h";

#define POCET_OPERACII 100000
#define FILE "vysledky/uloha1/"

namespace std {
	class ADT_List {
	public:
		ADT_List(const int vloz, const int zrus,
			const int item_index, const int set, std::string scnr)
			:
			scenarioName(scnr),
			zrus_(zrus),
			vloz_(vloz + zrus),
			item_index_(item_index + vloz + zrus),
			set_(set + item_index + vloz + zrus),

			nazov_operacie_(new std::string [POCET_OPERACII]),
			cas_operacie_List(new double[POCET_OPERACII]),
			cas_operacie_Array(new double[POCET_OPERACII]),

			array_(new structures::ArrayList<int>()),
			list_(new structures::LinkedList<int>())
		{
			count_a = recap = i = count_i = count_s = count_v = count_z = 0;
		}

		~ADT_List()
		{
			scenarioName = "";
			delete array_;
			delete list_;
			delete cas_operacie_List;
			delete cas_operacie_Array;
			count_i = count_s = count_v = count_z = 0;
			zrus_ = 0;
			vloz_ = 0;
			item_index_ = 0;
			set_ = 0;
			recap = i = 0;
			count_a = 0;
		}

		void start_testing();

	private:
		std::string scenarioName;

		int i, recap;

		int vloz_;
		int zrus_;
		int item_index_;
		int set_;

		int count_a;
		int count_v;
		int count_z;
		int count_i;
		int count_s;

		structures::ArrayList<int>* array_;
		structures::LinkedList<int>* list_;

		std::string* nazov_operacie_;
		double* cas_operacie_List;
		double* cas_operacie_Array;

		Time time_;
	private:
		void insert();

		void del();

		void set();

		void find();

		void saveToFiles();
	};


	inline void ADT_List::start_testing()
	{
		int choice = 0;

		for (i = 0; i < POCET_OPERACII; i++) {
			choice = (rand() % 100) + 0;

			if (count_a == POCET_OPERACII) {
				break;
			}

			if (choice <= zrus_) {
				del();
			}
			if ((zrus_ < choice && choice <= vloz_ )|| recap > 5) {
				insert();
			}
			if (vloz_ < choice && choice <= item_index_) {
				find();
			}
			if (item_index_ < choice && choice <= set_) {
				set();
			}
		}

		saveToFiles();
	}

	inline void ADT_List::insert()
	{
		int value = (rand() % POCET_OPERACII) + 0;

		if (POCET_OPERACII * (double(vloz_ - zrus_) / 100) > count_v || recap > 5) {
			int choose = (rand() % 3) + 1;
			if (choose == 1 && count_v > 0 || recap > 5) {
				choose == 1;
				
				time_.setStart();
				array_->insert(value, 0);
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				list_->insert(value, 0);
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "1.Vloz prvy";
			}
			if (choose == 2 && count_v > 0) {
				int index = 0;
				if (array_->size() != 0) {
					int index = (rand() % (array_->size())) - 1;
					if (index < 0) index = 0;
				}

				time_.setStart();
				array_->insert(value, index);
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				list_->insert(value, index);
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "1. Vloz na indexe";
			}
			if (choose == 3 || (choose != 0 && count_v == 0)) {
				time_.setStart();
				array_->add(value);
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				list_->add(value);
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "1. Vloz na koniec";
			}

			count_a++;
			count_v++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_List::del()
	{
		if (POCET_OPERACII * (double(zrus_) / 100) > count_z && count_v >= 1 && array_->size() > 0) {
			int choose = (rand() % 3) + 1;
			if (choose == 1) {
				time_.setStart();
				array_->removeAt(0);
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				list_->removeAt(0);
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "2. Odstran prvy";
			}
			if (choose == 2) {
				int index = 0;
				if (array_->size() != 0) {
					int index = (rand() % (array_->size())) - 1;
					if (index < 0) index = 0;
				}

				time_.setStart();
				array_->removeAt(index);
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				list_->removeAt(index);
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "2. Odstran na indexe";
			}
			if (choose == 3) {
				time_.setStart();
				array_->removeAt(array_->size()-1);
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				list_->removeAt(list_->size()-1);
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "2. Odstran posledny";
			}

			count_a++;
			count_z++;
			recap = 0;
		}
		else {
			recap++;
			i--;
		}
	}

	inline void ADT_List::set()
	{
		if (POCET_OPERACII * (double(set_ - item_index_) / 100) > count_s && count_v >= 1 && array_->size() > 0) {
			int index = 0;
			if (array_->size() != 0) {
				int index = (rand() % (array_->size())) - 1;
				if (index < 0) index = 0;
			}

			if (rand() % POCET_OPERACII <= 50) {
				int value = 0;

				time_.setStart();
				value = (*array_)[index];
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				value = (*list_)[index];
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "3. Spristupni";
			}
			else {
				int long long value = (rand() % POCET_OPERACII) + 0;

				time_.setStart();
				(*array_)[index] = value;
				time_.setEnd();
				(cas_operacie_Array)[count_a] = time_.getDuration();

				time_.setStart();
				(*list_)[index] = value;
				time_.setEnd();
				(cas_operacie_List)[count_a] = time_.getDuration();

				nazov_operacie_[count_a] = "3. Nastav";
			}

			count_a++;
			count_s++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_List::find()
	{
		if (POCET_OPERACII * (double(item_index_ - vloz_) / 100) > count_i) {
			int value = (rand() % POCET_OPERACII) + 0;

			time_.setStart();
			array_->getIndexOf(value);
			time_.setEnd();
			(cas_operacie_Array)[count_a] = time_.getDuration();

			time_.setStart();
			list_->getIndexOf(value);
			time_.setEnd();
			(cas_operacie_List)[count_a] = time_.getDuration();

			nazov_operacie_[count_a] = "4. Index Prvku";

			count_a++;
			count_i++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_List::saveToFiles()
	{
		file* file_ = new file(FILE, scenarioName);

		file_->addItem("n,Nazov Operacie,Cas list,Cas Array,");
		file_->newLine();

		for (int n = 0; n < POCET_OPERACII; n++) {
			file_->addItem(to_string(n+1));
			file_->addComma();
			file_->addItem(nazov_operacie_[n]);
			file_->addComma();
			file_->addItem(to_string((cas_operacie_List)[n]));
			file_->addComma();
			file_->addItem(to_string((cas_operacie_Array)[n]));
			if (n < POCET_OPERACII - 1) {
				file_->newLine();
			}
		}

		std::string name = FILE;

		file_->saveFile();
		delete file_;
	}
};