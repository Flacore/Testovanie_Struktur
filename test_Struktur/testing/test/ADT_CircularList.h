#pragma once

#include "../../structures/list/doubly_circular_linked_list.h";

#include "../file.h";
#include "../time.h";

#define POCET_OPERACII 100000
#define FILE "vysledky//uloha4//"

namespace std {
	class ADT_CircularList {
	public:
		ADT_CircularList(const int vloz, const int zrus,
			const int item_index, const int set)
			:
			zrus_(zrus),
			vloz_(vloz + zrus),
			item_index_(item_index + vloz + zrus),
			set_(set + item_index + vloz + zrus),

			nazov_operacie_(new structures::Array<std::string>(POCET_OPERACII)),
			cas_operacie_(new structures::Array<int>(POCET_OPERACII)),

			list_(new structures::DoublyCircularLinkedList<int>())
		{
			recap = i = count_i = count_s = count_v = count_z = 0;
		}

		~ADT_CircularList()
		{
			delete list_;
			delete nazov_operacie_;
			delete cas_operacie_;
			count_i = count_s = count_v = count_z = 0;
			zrus_ = 0;
			vloz_ = 0;
			item_index_ = 0;
			set_ = 0;
			recap = i = 0;
		}

		void start_testing();

	private:
		int i,recap;

		int vloz_;
		int zrus_;
		int item_index_;
		int set_;

		int count_v;
		int count_z;
		int count_i;
		int count_s;

		structures::DoublyCircularLinkedList<int>* list_;

		structures::Array<std::string>* nazov_operacie_;
		structures::Array<int>* cas_operacie_;


		Time time_;
	private:
		void insert();

		void del();

		void set();

		void find();

		void saveToFiles();
	};

	inline void ADT_CircularList::start_testing()
	{
		int choice = 0;

		for (i = 0; i < POCET_OPERACII; i++) {
			choice = (rand() % 100) + 0;

			if (choice <= zrus_) {
				del();
			}
			if (zrus_ < choice && choice <= vloz_ || recap > 5) {
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

	inline void ADT_CircularList::insert()
	{
		int value = (rand() % POCET_OPERACII) + 0;

		if (POCET_OPERACII * (double(vloz_ - zrus_) / 100) > count_v || recap > 5) {
			int choose = (rand() % 3) + 1;

			if (choose == 1 && count_v > 0 || recap > 5) {
				choose == 1;
				int time = time_.getTime();
				list_->insert(value, 0);
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "1.Vloz prvy.";
			}
			if (choose == 2 && count_v > 0) {
				int index = 0;
				if (list_->size() != 0) {
					int index = (rand() % (list_->size())) - 1;
					if (index < 0) index = 0;
				}

				int time = time_.getTime();
				list_->insert(value, index);
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "1. Vloz na indexe.";
			}
			if (choose == 3 || (choose != 0 && count_v == 0)) {
				int time = time_.getTime();
				list_->add(value);
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "1. Vloz na koniec.";
			}

			count_v++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_CircularList::del()
	{
		if (POCET_OPERACII * (double(zrus_) / 100) > count_z && list_->size() > 0) {
			int choose = (rand() % 3) + 1;

			if (choose == 1) {
				int time = time_.getTime();
				list_->removeAt(0);
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "2. Odstran prvy.";
			}
			if (choose == 2) {
				int index = 0;
				if (list_->size() != 0) {
					int index = (rand() % (list_->size())) - 1;
					if (index < 0) index = 0;
				}

				int time = time_.getTime();
				list_->removeAt(index);
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "2. Odstran na indexe.";
			}
			if (choose == 3) {
				int time = time_.getTime();
				list_->removeAt(list_->size() - 1);
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "2. Odstran posledny.";
			}

			count_z++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_CircularList::set()
	{
		if (POCET_OPERACII * (double(set_ - item_index_) / 100) > count_s && list_->size() > 0) {
			int index = 0;
			if (list_->size() != 0) {
				int index = (rand() % (list_->size())) - 1;
				if (index < 0) index = 0;
			}

			if (rand() % POCET_OPERACII <= 50) {
				int value = 0;

				int time = time_.getTime();
				value = (*list_)[index];
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "3. Spristupni.";
			}
			else {
				int value = (rand() % POCET_OPERACII) + 0;

				int time = time_.getTime();
				(*list_)[index] = value;
				time -= time_.getTime();
				(*cas_operacie_)[i] = time;

				(*nazov_operacie_)[i] = "3. Nastav.";
			}

			count_s++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_CircularList::find()
	{
		if (POCET_OPERACII * (double(item_index_ - vloz_) / 100) > count_i) {
			int value = (rand() % POCET_OPERACII) + 0;

			int time = time_.getTime();
			list_->getIndexOf(value);
			time -= time_.getTime();
			(*cas_operacie_)[i] = time;

			(*nazov_operacie_)[i] = "4. Index prvku.";

			count_i++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_CircularList::saveToFiles()
	{
		//TODO
	}
};