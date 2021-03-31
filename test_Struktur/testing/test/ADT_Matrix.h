#pragma once
#include "../../structures/priority_queue/priority_queue_two_lists.h";

#include <string>

#include "../time.h";

#include "../../structures/matrix/coherant_matrix.h";
#include "../../structures/matrix/incoherant_matrix.h";

#define MIN_VALUE 1
#define MAX_VALUE 10
#define MIN_SIZE 1
#define MAX_SIZE 2000
#define FILE "vysledky/uloha3/"

namespace std {
	class ADT_Matrix {
	public:
		ADT_Matrix(const int type, std::string scnr) :
			scenarioName(scnr),
			type_(type),
			cas_operacie_Coherant(new int[(((MAX_SIZE-MIN_SIZE)+1)*2)]),
			cas_operacie_Incoherant(new int[(((MAX_SIZE - MIN_SIZE) + 1) * 2)])
		{
			i = 0;
		}

		~ADT_Matrix() {
			scenarioName = "";
			delete cas_operacie_Coherant;
			delete cas_operacie_Incoherant;
			type_ = 0;
			i = 0;
		}

		void do_testing();


	private:
		std::string scenarioName;

		Time time_;

		int type_;
		int i;

		int* cas_operacie_Coherant;
		int* cas_operacie_Incoherant;
	private:
		void scenarA_nesuvysla(int m, int n);

		void scenarA_suvysla(int m, int n);

		void scenarB_nesuvysla(int m, int n);

		void scenarB_suvysla(int m, int n);

		void naplnSuvysla(int m, int n, structures::CoherantMatrix<int>* other);

		void naplnNesuvysla(int m, int n, structures::IncoherantMatrix<int>* other);

		void saveFiles();
	};

	inline void ADT_Matrix::do_testing()
	{
		for (int k = 1; k <= 2; k++) {
			for (int j = MIN_SIZE; j <= MAX_SIZE; j++) {
				int m, n;
				if (k == 1) {
					m = j;
					n = MIN_SIZE;
				}
				else {
					m = MIN_SIZE;
					n = j;
				}

				cout << m << " " << n << endl;

				if (type_ == 1) {
					scenarioName = "scenarioA.csv";
					scenarA_nesuvysla(m, n);
					scenarA_suvysla(m, n);
				}
				else {
					scenarioName = "scenarioB.csv";
					scenarB_nesuvysla(m, n);
					scenarB_suvysla(m, n);
				}
				i++;
			}
		}
		cout << "Ukladanie" << endl;
		saveFiles();
	}

	inline void ADT_Matrix::scenarA_nesuvysla(int m, int n)
	{
		structures::IncoherantMatrix<int>* matica2_ = new structures::IncoherantMatrix<int>(m, n);
		naplnNesuvysla(m, n, matica2_);
		structures::IncoherantMatrix<int>* matica1_ = new structures::IncoherantMatrix<int>(m, n);
		naplnNesuvysla(m, n, matica1_);
		structures::IncoherantMatrix<int>* vysledok_ = new structures::IncoherantMatrix<int>(m, n);

		time_.setStart();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*vysledok_)(x, y) = (((*matica1_)(x, y)) + ((*matica1_)(x, y)));
			}
		}
		time_.setEnd();
		(cas_operacie_Incoherant)[i] = time_.getDuration();

		delete matica1_;
		delete matica2_;
		delete vysledok_;
	}

	inline void ADT_Matrix::scenarA_suvysla(int m, int n)
	{
		structures::CoherantMatrix<int>* matica2_ = new structures::CoherantMatrix<int>(m, n);
		naplnSuvysla(m, n, matica2_);
		structures::CoherantMatrix<int>* matica1_ = new structures::CoherantMatrix<int>(m, n);
		naplnSuvysla(m, n, matica1_);
		structures::CoherantMatrix<int>* vysledok_ = new structures::CoherantMatrix<int>(m, n);

		time_.setStart();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*vysledok_)(x, y) = (((*matica1_)(x, y)) + ((*matica1_)(x, y)));
			}
		}
		time_.setEnd();
		(cas_operacie_Coherant)[i] = time_.getDuration();

		delete matica1_;
		delete matica2_;
		delete vysledok_;
	}

	inline void ADT_Matrix::scenarB_nesuvysla(int m, int n)
	{
		structures::IncoherantMatrix<int>* matica2_ = new structures::IncoherantMatrix<int>(m, n);
		naplnNesuvysla(m, n, matica2_);
		structures::IncoherantMatrix<int>* matica1_ = new structures::IncoherantMatrix<int>(n, m);
		naplnNesuvysla(n, m, matica1_);
		structures::IncoherantMatrix<int>* vysledok_ = new structures::IncoherantMatrix<int>(m, m);

		time_.setStart();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < m; y++) {
				(*vysledok_)(x, y) = 0;
				for (int k = 0; k < n; k++){
					(*vysledok_)(x, y) += (((*matica2_)(x, k)) * ((*matica1_)(k, y)));
				}
			}
		}
		time_.setEnd();
		(cas_operacie_Incoherant)[i] = time_.getDuration();

		delete matica1_;
		delete matica2_;
		delete vysledok_;
	}

	inline void ADT_Matrix::scenarB_suvysla(int m, int n)
	{
		structures::CoherantMatrix<int>* matica2_ = new structures::CoherantMatrix<int>(m, n);
		naplnSuvysla(m, n, matica2_);
		structures::CoherantMatrix<int>* matica1_ = new structures::CoherantMatrix<int>(n, m);
		naplnSuvysla(n, m, matica1_);
		structures::CoherantMatrix<int>* vysledok_ = new structures::CoherantMatrix<int>(m, m);

		time_.setStart();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < m; y++) {
				(*vysledok_)(x, y) = 0;
				for (int k = 0; k < n; k++) {
					(*vysledok_)(x, y) += (((*matica2_)(x, k)) * ((*matica1_)(k, y)));
				}
			}
		}
		time_.setEnd();
		(cas_operacie_Coherant)[i] = time_.getDuration();

		delete matica1_;
		delete matica2_;
		delete vysledok_;
	}

	inline void ADT_Matrix::naplnSuvysla(int m, int n, structures::CoherantMatrix<int>* other)
	{
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*other)(x, y) = ((rand() % MAX_VALUE) + MIN_VALUE);
			}
		}
	}

	inline void ADT_Matrix::naplnNesuvysla(int m, int n, structures::IncoherantMatrix<int>* other)
	{
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*other)(x, y) = ((rand() % MAX_VALUE) + MIN_VALUE);
			}
		}
	}

	inline void ADT_Matrix::saveFiles()
	{
		file* file_ = new file(FILE, scenarioName);

		file_->addItem("n,N,M,Cas Coherant,Cas Incoherant,");
		file_->newLine();

		for (int n = 0; n < (((MAX_SIZE - MIN_SIZE) + 1) * 2); n++) {
			int N = 0;
			int M = 0;

			//Min Size -> Max Size
			if (n < (MAX_SIZE-MIN_SIZE+1)) {
				M = MIN_SIZE;
				N = (n + MIN_SIZE);
			}
			else {
				M = (n + MIN_SIZE) - MAX_SIZE;
				N = MIN_SIZE;
			}

			file_->addItem(to_string(n + 1));
			file_->addComma();
			file_->addItem(to_string(N));
			file_->addComma();
			file_->addItem(to_string(M));
			file_->addComma();
			file_->addItem(to_string((cas_operacie_Coherant)[n]));
			file_->addComma();
			file_->addItem(to_string((cas_operacie_Incoherant)[n]));
			if (n < (((MAX_SIZE - MIN_SIZE) + 1) * 2) - 1) {
				file_->newLine();
			}
		}

		file_->saveFile();
		delete file_;
	}
}