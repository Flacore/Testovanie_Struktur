#pragma once
#include "../../structures/priority_queue/priority_queue_two_lists.h";

#include <string>

#define POCET_OPERACII 100000
#define FILE "vysledky/uloha5/"

namespace std {
	class ADT_TwoList {
	public:
		ADT_TwoList(const int vloz, const int vyber, const int ukaz, std::string scnr) :
			scenarioName(scnr),
			vloz_(vloz),
			vyber_(vyber + vloz),
			ukaz_(ukaz + vyber + vloz),

			nazov_operacie_(new structures::Array<std::string>(POCET_OPERACII)),
			cas_operacie_pq1(new structures::Array<int>(POCET_OPERACII)),
			cas_operacie_pq2(new structures::Array<int>(POCET_OPERACII)),
			cas_operacie_pq3(new structures::Array<int>(POCET_OPERACII)),

			pq_1(new structures::PriorityQueueTwoLists<int>((POCET_OPERACII/1000))),
			pq_2(new structures::PriorityQueueTwoLists<int>()),
			pq_3(new structures::PriorityQueueTwoLists<int>())
		{
			recap = i = count_i = count_g = count_s = 0;
		}

		~ADT_TwoList() {
			scenarioName = "";
			recap = i = vloz_ = vyber_ = ukaz_ = 0;
			count_i = count_g = count_s = 0;
			delete pq_1;
			delete pq_2;
			delete pq_3;

			delete nazov_operacie_;
			delete cas_operacie_pq1;
			delete cas_operacie_pq2;
			delete cas_operacie_pq3;
		}

		void do_testing();


	private:
		std::string scenarioName;

		int i, recap;
		int vloz_;
		int vyber_;
		int ukaz_;

		int count_i;
		int count_g;
		int count_s;

		structures::PriorityQueueTwoLists<int>* pq_1;
		structures::PriorityQueueTwoLists<int>* pq_2;
		structures::PriorityQueueTwoLists<int>* pq_3;

		structures::Array<std::string>* nazov_operacie_;
		structures::Array<int>* cas_operacie_pq1;
		structures::Array<int>* cas_operacie_pq2;
		structures::Array<int>* cas_operacie_pq3;

		Time time_;
	private:

		void oInsert();

		void oGet();

		void oShow();

		void saveToFiles();

	};

	inline void ADT_TwoList::do_testing()
	{
		int choice = 0;

		for (i = 0; i < POCET_OPERACII; i++) {
			choice = (rand() % 100) + 0;

			cout << i << endl;

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

	inline void ADT_TwoList::oInsert()
	{ 
		if (POCET_OPERACII * (double(vloz_) / 100) > count_i || recap > 5) {
			int priority = 0;
			int value = 0;

			int time = time_.getTime();
			pq_1->push(priority, value);
			time -= time_.getTime();
			(*cas_operacie_pq1)[i] = time;

			time = time_.getTime();
			pq_2->push(priority, value);
			time -= time_.getTime();
			(*cas_operacie_pq2)[i] = time;
			pq_2->setCapacityOfShortlist(round(sqrt(pq_2->size())));

			time = time_.getTime();
			pq_3->push(priority, value);
			time -= time_.getTime();
			(*cas_operacie_pq2)[i] = time;
			pq_3->setCapacityOfShortlist(round(pq_2->size() / 2));

			(*nazov_operacie_)[i] = "1. Vloz.";

			count_i++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_TwoList::oGet()
	{
		if (POCET_OPERACII * (double(vyber_ - vloz_) / 100) > count_g) {
			int trashbin_ = 0;

			int time = time_.getTime();
			trashbin_ = pq_1->pop();
			time -= time_.getTime();
			(*cas_operacie_pq1)[i] = time;

			time = time_.getTime();
			trashbin_ = pq_2->pop();
			time -= time_.getTime();
			(*cas_operacie_pq2)[i] = time;
			pq_2->setCapacityOfShortlist(round(sqrt(pq_2->size())));

			time = time_.getTime();
			trashbin_ = pq_3->pop();
			time -= time_.getTime();
			(*cas_operacie_pq2)[i] = time;
			pq_3->setCapacityOfShortlist(round(pq_2->size() / 2));

			(*nazov_operacie_)[i] = "2. Vyber.";

			count_g++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_TwoList::oShow()
	{
		if (POCET_OPERACII * (double (ukaz_ - vyber_) / 100) > count_s) {
			int trashbin_ = 0;

			int time = time_.getTime();
			trashbin_ = pq_1->peek();
			time -= time_.getTime();
			(*cas_operacie_pq1)[i] = time;

			time = time_.getTime();
			trashbin_ = pq_2->peek();
			time -= time_.getTime();
			(*cas_operacie_pq2)[i] = time;

			time = time_.getTime();
			trashbin_ = pq_3->peek();
			time -= time_.getTime();
			(*cas_operacie_pq3)[i] = time;

			(*nazov_operacie_)[i] = "3. Ukaz.";

			count_s++;
			recap = 0;
		}
		else {
			i--;
			recap++;
		}
	}

	inline void ADT_TwoList::saveToFiles()
	{
		//TODO
	}

}