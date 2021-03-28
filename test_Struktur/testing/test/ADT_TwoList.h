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

			nazov_operacie_(new std::string[POCET_OPERACII]),
			cas_operacie_pq1(new double[POCET_OPERACII]),
			cas_operacie_pq2(new double[POCET_OPERACII]),
			cas_operacie_pq3(new double[POCET_OPERACII]),

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

			//delete nazov_operacie_;
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

		std::string* nazov_operacie_;
		double* cas_operacie_pq1;
		double* cas_operacie_pq2;
		double* cas_operacie_pq3;

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

			time_.setStart();
			pq_1->push(priority, value);
			time_.setEnd();
			(cas_operacie_pq1)[i] = time_.getDuration();

			time_.setStart();
			pq_2->push(priority, value);
			time_.setEnd();
			(cas_operacie_pq2)[i] = time_.getDuration();

			time_.setStart();
			pq_3->push(priority, value);
			time_.setEnd();
			(cas_operacie_pq3)[i] = time_.getDuration();

			(nazov_operacie_)[i] = "1. Vloz.";

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

			time_.setStart();
			trashbin_ = pq_1->pop();
			time_.setEnd();
			(cas_operacie_pq1)[i] = time_.getDuration();

			time_.setStart();
			trashbin_ = pq_2->pop();
			time_.setEnd();
			(cas_operacie_pq2)[i] = time_.getDuration();

			time_.setStart();
			trashbin_ = pq_3->pop();
			time_.setEnd();
			(cas_operacie_pq3)[i] = time_.getDuration();

			(nazov_operacie_)[i] = "2. Vyber.";

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

			time_.setStart();
			trashbin_ = pq_1->peek();
			time_.setEnd();
			(cas_operacie_pq1)[i] = time_.getDuration();

			time_.setStart();
			trashbin_ = pq_2->peek();
			time_.setEnd();
			(cas_operacie_pq2)[i] = time_.getDuration();

			time_.setStart();
			trashbin_ = pq_3->peek();
			time_.setEnd();
			(cas_operacie_pq3)[i] = time_.getDuration();

			(nazov_operacie_)[i] = "3. Ukaz.";

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
		file* file_ = new file(FILE, scenarioName);

		file_->addItem("n,Nazov Operacie,Cas 1/1000,Cas sqrt(n), Cas n/2,");
		file_->newLine();

		for (int n = 0; n < POCET_OPERACII; n++) {
			file_->addItem(to_string(n + 1));
			file_->addComma();
			file_->addItem((nazov_operacie_)[n]);
			file_->addComma();
			file_->addItem(to_string((cas_operacie_pq1)[n]));
			file_->addComma();
			file_->addItem(to_string((cas_operacie_pq2)[n]));
			file_->addComma();
			file_->addItem(to_string((cas_operacie_pq3)[n]));
			if (n < POCET_OPERACII - 1) {
				file_->newLine();
			}
		}

		std::string name = FILE;

		file_->saveFile();
		delete file_;
	}

}