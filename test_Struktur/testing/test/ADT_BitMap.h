#pragma once

//TEST
//Porovnajte rozdiel vzhladom na velkost bazovej ,moziny
//
// [25%]  Skup 1 -> Vloz
// [25%]  Skup 2 -> Odober
// [25%] Skup 3 -> Patrí, Je rovná, Je podmnožina
// [25%] Skup 4 -> Zjednotenie, Prienik Rozdiel

#include <string>

#include "../../structures/priority_queue/priority_queue_two_lists.h";
#include "../../structures/bit_map/array_bit_map.h";

#define MIN_VALUE 1
#define MAX_VALUE 100
#define POCET_OPERACII 1000
//#define POCET_OPERACII 100000
#define FILE "vysledky/uloha6/"

namespace std {
	class ADT_BitMap {
	public:
		ADT_BitMap(const int vloz, const int zrus, const int LogOperacie, const int MnozOperacie, std::string scnr):
			scenarioName(scnr),
			vloz_(vloz + zrus),
			zrus_(zrus),
			LogOperacie_(LogOperacie + vloz + zrus),
			MnozOperacie_(MnozOperacie + LogOperacie + vloz + zrus)
		{
			recal = i = count_1 = count_2 = count_3 = count_4 = 0;

			shorter_ = new ByteSet<int>(MIN_VALUE, MAX_VALUE);
			longer_ = new ByteSet<unsigned long long>(MIN_VALUE, MAX_VALUE);

			nazov_operacie_ = new string[POCET_OPERACII];
			cas_operacie_Shorter = new int[POCET_OPERACII];
			cas_operacie_Longer = new int[POCET_OPERACII];
		}

		~ADT_BitMap() {
			scenarioName = "";

			recal = i = 0;
			vloz_ = zrus_ = LogOperacie_ = MnozOperacie_ = 0;
			count_1 = count_2 = count_3 = count_4 = 0;

			delete shorter_;
			delete longer_;

			//delete nazov_operacie_;
			delete cas_operacie_Longer;
			delete cas_operacie_Shorter;
		}

		void do_testing();


	private:
		std::string scenarioName;

		int i, recal;

		int vloz_;
		int zrus_;
		int LogOperacie_;
		int MnozOperacie_;

		int count_1;
		int count_2;
		int count_3;
		int count_4;

		ByteSet<int>* shorter_;
		ByteSet<unsigned long long>* longer_;

		string* nazov_operacie_;
		int* cas_operacie_Shorter;
		int* cas_operacie_Longer;

		Time time_;
	private:
		void remove();

		void insert();

		void LogOp();

		void SetOp();

		void saveTesting();
	};

	inline void ADT_BitMap::do_testing()
	{
		int choice = zrus_ + 1;

		for (i = 0; i < POCET_OPERACII; i++) {
			

			if (choice <= zrus_) {
				remove();
			}
			if (zrus_ < choice && choice <= vloz_ || recal > 5) {
				insert();
				choice = 1;
			}
			if (vloz_ < choice && choice <= LogOperacie_) {
				LogOp();
			}
			if (LogOperacie_ < choice && choice <= MnozOperacie_) {
				SetOp();
			}

			choice = (rand() % 100) + 0;
		}

		saveTesting();
	}

	inline void ADT_BitMap::remove()
	{
		int value = (rand() % MAX_VALUE) + MIN_VALUE;

		if (POCET_OPERACII * ((double(zrus_) / 100)) > count_1) {

			time_.setStart();
			shorter_->remove(value);
			time_.setEnd();
			(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

			time_.setStart();
			longer_->remove(value);
			time_.setEnd();
			(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();


			(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "1. Odstranovanie.";

			recal = 0;
			count_1++;
		}
		else {
			i--;
			recal++;
		}
	}

	inline void ADT_BitMap::insert()
	{
		int value = (rand() % MAX_VALUE) + MIN_VALUE;

		if (POCET_OPERACII * (double(vloz_ - zrus_) / 100) > count_2 || recal > 5) {

			time_.setStart();
			shorter_->insert(value);
			time_.setEnd();
			(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

			time_.setStart();
			longer_->insert(value);
			time_.setEnd();
			(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

			(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "2. Vkladanie.";

			count_2++;
			recal = 0;
		}
		else {
			i--;
			recal++;
		}
	}

	inline void ADT_BitMap::LogOp()
	{
		bool tmp;

		if (POCET_OPERACII * (double(LogOperacie_ - vloz_) / 100) > count_3) {
			int choose = (rand() % 3) + 1;

			choose = 1;

			if (choose == 1) {
				int value = (rand() % MAX_VALUE) + MIN_VALUE;

				time_.setStart();
				tmp = shorter_->isIn(value);
				time_.setEnd();
				(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				time_.setStart();
				tmp = longer_->isIn(value);
				time_.setEnd();
				(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "3. Patri.";
			}
			if (choose == 2) {
				time_.setStart();
				tmp = (shorter_ == shorter_);
				time_.setEnd();
				(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				time_.setStart();
				tmp = (longer_ == longer_);
				time_.setEnd();
				(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "3. Je rovna.";
			}
			if (choose == 3) {
				time_.setStart();
				tmp = shorter_->isSubset(*shorter_);
				time_.setEnd();
				(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				time_.setStart();
				tmp = longer_->isSubset(*longer_);
				time_.setEnd();
				(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "3. Je podmnozina.";
			}

			count_3++;
			recal = 0;
		}
		else {
			i--;
			recal++;
		}
	}

	inline void ADT_BitMap::SetOp()
	{
		if (POCET_OPERACII * (double(MnozOperacie_ - LogOperacie_ ) / 100) > count_4) {
			int choose = (rand() % 3) + 1;

			choose = 2;

			if (choose == 1 ) {
				time_.setStart();
				//shorter_->setUnion(*shorter_);
				time_.setEnd();
				(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				time_.setStart();
				//longer_->setUnion(*longer_);
				time_.setEnd();
				(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "4. Zjednotenie.";
			}
			if (choose == 2) {
				time_.setStart();
				//shorter_->intersection(*shorter_);
				time_.setEnd();
				(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				time_.setStart();
				//longer_->intersection(*longer_);
				time_.setEnd();
				(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "4. Prienik.";
			}
			if (choose == 3) {
				time_.setStart();
				//shorter_->difference(*shorter_);
				time_.setEnd();
				(cas_operacie_Shorter)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				time_.setStart();
				//longer_->difference(*longer_);
				time_.setEnd();
				(cas_operacie_Longer)[count_1 + count_2 + count_3 + count_4] = time_.getDuration();

				(nazov_operacie_)[count_1 + count_2 + count_3 + count_4] = "4. Rozdiel.";
			}

			count_4++;
			recal = 0;
		}
		else {
			i--;
			recal++;
		}
	}

	inline void ADT_BitMap::saveTesting()
	{
		file* file_ = new file(FILE, scenarioName);

		file_->addItem("n,Nazov Operacie,Cas Longer,Cas Shorter,");
		file_->newLine();

		for (int n = 0; n < POCET_OPERACII; n++) {
			file_->addItem(to_string(n + 1));
			file_->addComma();
			file_->addItem(nazov_operacie_[n]);
			file_->addComma();
			file_->addItem(to_string(cas_operacie_Longer[n]));
			file_->addComma();
			file_->addItem(to_string(cas_operacie_Shorter[n]));
			if (n < POCET_OPERACII - 1) {
				file_->newLine();
			}
		}

		std::string name = FILE;

		file_->saveFile();
		delete file_;
	}

}