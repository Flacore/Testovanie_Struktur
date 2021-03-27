#pragma once

//TEST
//Porovnajte rozdiel vzhladom na velkost bazovej ,moziny
//
// [25%]  Skup 1 -> Vloz
// [25%]  Skup 2 -> Odober
// [25%] Skup 3 -> Patrí, Je rovná, Je podmnožina
// [25%] Skup 4 -> Zjednotenie, Prienik Rozdiel

#include "../../structures/priority_queue/priority_queue_two_lists.h";

#include "../../structures/bit_map/array_bit_map.h";

#define MIN_VALUE 1
#define MAX_VALUE 10000
#define MIN_SIZE 10
#define MAX_SIZE 100000
#define POCET_OPERACII 100000
#define FILE "vysledky//uloha6//"

namespace std {
	class ADT_BitMap {
	public:
		ADT_BitMap(const int vloz, const int zrus, const int LogOperacie, const int MnozOperacie):
			vloz_(vloz + zrus),
			zrus_(zrus),
			LogOperacie_(LogOperacie + vloz + zrus),
			MnozOperacie_(MnozOperacie + LogOperacie + vloz + zrus)
		{
			recal = i = count_1 = count_2 = count_3 = count_4 = 0;

			shorter_ = new ByteSet<int>(MIN_VALUE, MAX_VALUE);
			longer_ = new ByteSet<unsigned long long>(MIN_VALUE, MAX_VALUE);

			nazov_operacie_ = new structures::Array<string>(POCET_OPERACII);
			cas_operacie_Shorter = new structures::Array<int>(POCET_OPERACII);
			cas_operacie_Longer = new structures::Array<int>(POCET_OPERACII);
		}

		~ADT_BitMap() {
			recal = i = 0;
			vloz_ = zrus_ = LogOperacie_ = MnozOperacie_ = 0;
			count_1 = count_2 = count_3 = count_4 = 0;

			delete shorter_;
			delete longer_;

			delete nazov_operacie_;
			delete cas_operacie_Longer;
			delete cas_operacie_Shorter;
		}

		void do_testing();


	private:
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

		structures::Array<string>* nazov_operacie_;
		structures::Array<int>* cas_operacie_Shorter;
		structures::Array<int>* cas_operacie_Longer;

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
		int choice = 0;

		for (i = 0; i < POCET_OPERACII; i++) {
			choice = (rand() % 100) + 0;

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
		}

		saveTesting();
	}

	inline void ADT_BitMap::remove()
	{
		int value = (rand() % MAX_VALUE) + MIN_VALUE;

		if (POCET_OPERACII * ((double(zrus_) / 100)) > count_1) {

			int time = time_.getTime();
			shorter_->remove(value);
			time -= time_.getTime();
			(*cas_operacie_Shorter)[i] = time;

			time = time_.getTime();
			longer_->remove(value);
			time -= time_.getTime();
			(*cas_operacie_Longer)[i] = time;


			(*nazov_operacie_)[i] = "1. Odstranovanie.";

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

			int time = time_.getTime();
			shorter_->insert(value);
			time -= time_.getTime();
			(*cas_operacie_Shorter)[i] = time;

			time = time_.getTime();
			longer_->insert(value);
			time -= time_.getTime();
			(*cas_operacie_Longer)[i] = time;

			(*nazov_operacie_)[i] = "2. Vkladanie.";

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

		if (POCET_OPERACII * (double(LogOperacie_ - vloz_ - zrus_) / 100) > count_3) {
			int choose = (rand() % 3) + 1;

			if (choose == 1) {
				int value = (rand() % MAX_VALUE) + MIN_VALUE;

				int time = time_.getTime();
				tmp = shorter_->isIn(value);
				time -= time_.getTime();
				(*cas_operacie_Shorter)[i] = time;

				time = time_.getTime();
				tmp = longer_->isIn(value);
				time -= time_.getTime();
				(*cas_operacie_Longer)[i] = time;

				(*nazov_operacie_)[i] = "3. Patri.";
			}
			if (choose == 2) {
				int time = time_.getTime();
				tmp = (shorter_ == shorter_);
				time -= time_.getTime();
				(*cas_operacie_Shorter)[i] = time;

				time = time_.getTime();
				tmp = (longer_ == longer_);
				time -= time_.getTime();
				(*cas_operacie_Longer)[i] = time;

				(*nazov_operacie_)[i] = "3. Je rovna.";
			}
			if (choose == 3) {
				int time = time_.getTime();
				tmp = shorter_->isSubset(*shorter_);
				time -= time_.getTime();
				(*cas_operacie_Shorter)[i] = time;

				time = time_.getTime();
				tmp = longer_->isSubset(*longer_);
				time -= time_.getTime();
				(*cas_operacie_Longer)[i] = time;

				(*nazov_operacie_)[i] = "3. Je podmnozina.";
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
		if (POCET_OPERACII * (double(MnozOperacie_ - LogOperacie_ - vloz_ - zrus_) / 100) > count_4) {
			int choose = (rand() % 3) + 1;

			if (choose == 1 ) {
				int time = time_.getTime();
				shorter_->setUnion(*shorter_);
				time -= time_.getTime();
				(*cas_operacie_Shorter)[i] = time;

				time = time_.getTime();
				longer_->setUnion(*longer_);
				time -= time_.getTime();
				(*cas_operacie_Longer)[i] = time;

				(*nazov_operacie_)[i] = "4. Zjednotenie.";
			}
			if (choose == 2) {
				int time = time_.getTime();
				shorter_->intersection(*shorter_);
				time -= time_.getTime();
				(*cas_operacie_Shorter)[i] = time;

				time = time_.getTime();
				longer_->intersection(*longer_);
				time -= time_.getTime();
				(*cas_operacie_Longer)[i] = time;

				(*nazov_operacie_)[i] = "4. Prienik.";
			}
			if (choose == 3) {
				int time = time_.getTime();
				shorter_->difference(*shorter_);
				time -= time_.getTime();
				(*cas_operacie_Shorter)[i] = time;

				time = time_.getTime();
				longer_->difference(*longer_);
				time -= time_.getTime();
				(*cas_operacie_Longer)[i] = time;

				(*nazov_operacie_)[i] = "4. Rozdiel.";
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
		//TODO
	}

}