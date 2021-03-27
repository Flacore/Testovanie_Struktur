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
			cas_operacie_Coherant(new structures::Array<int>(((MAX_SIZE-MIN_SIZE)+1)*2)),
			cas_operacie_Incoherant(new structures::Array<int>(((MAX_SIZE - MIN_SIZE) + 1) * 2))
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

		structures::Array<int>* cas_operacie_Coherant;
		structures::Array<int>* cas_operacie_Incoherant;
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
			for (i = MIN_SIZE; i <= MAX_SIZE; i++) {
				int m, n;
				if (k == 1) {
					m = i;
					n = 1;
				}
				else {
					m = 1;
					n = i;
				}

				cout << "m " << m << " n " << n << endl;

				if (type_ == 1) {
					scenarA_nesuvysla(m, n);
					scenarA_suvysla(m, n);
				}
				else {
					scenarB_nesuvysla(m, n);
					scenarB_suvysla(m, n);
				}
			}
		}
	}

	inline void ADT_Matrix::scenarA_nesuvysla(int m, int n)
	{
		structures::IncoherantMatrix<int>* matica2_ = new structures::IncoherantMatrix<int>(m, n);
		naplnNesuvysla(m, n, matica2_);
		structures::IncoherantMatrix<int>* matica1_ = new structures::IncoherantMatrix<int>(m, n);
		naplnNesuvysla(m, n, matica1_);
		structures::IncoherantMatrix<int>* vysledok_ = new structures::IncoherantMatrix<int>(m, n);

		int time = time_.getTime();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*vysledok_)(x, y) = (((*matica1_)(x, y)) + ((*matica1_)(x, y)));
			}
		}
		time -= time_.getTime();
		(*cas_operacie_Incoherant)[i] = time;

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

		int time = time_.getTime();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*vysledok_)(x, y) = (((*matica1_)(x, y)) + ((*matica1_)(x, y)));
			}
		}
		time -= time_.getTime();
		(*cas_operacie_Coherant)[i] = time;

		delete matica1_;
		delete matica2_;
		delete vysledok_;
	}

	inline void ADT_Matrix::scenarB_nesuvysla(int m, int n)
	{
		structures::IncoherantMatrix<int>* matica2_ = new structures::IncoherantMatrix<int>(m, n);
		naplnNesuvysla(m, n, matica2_);
		structures::IncoherantMatrix<int>* matica1_ = new structures::IncoherantMatrix<int>(m, n);
		naplnNesuvysla(m, n, matica1_);
		structures::IncoherantMatrix<int>* vysledok_ = new structures::IncoherantMatrix<int>(m, m);

		int time = time_.getTime();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*vysledok_)(x, y) = (((*matica1_)(x, y)) * ((*matica1_)(y, x)));
			}
		}
		time -= time_.getTime();
		(*cas_operacie_Incoherant)[i] = time;

		delete matica1_;
		delete matica2_;
		delete vysledok_;
	}

	inline void ADT_Matrix::scenarB_suvysla(int m, int n)
	{
		structures::CoherantMatrix<int>* matica2_ = new structures::CoherantMatrix<int>(m, n);
		naplnSuvysla(m, n, matica2_);
		structures::CoherantMatrix<int>* matica1_ = new structures::CoherantMatrix<int>(m, n);
		naplnSuvysla(m, n, matica1_);
		structures::CoherantMatrix<int>* vysledok_ = new structures::CoherantMatrix<int>(m, m);

		int time = time_.getTime();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				(*vysledok_)(x, y) = (((*matica1_)(x, y)) * ((*matica1_)(y, x)));
			}
		}
		time -= time_.getTime();
		(*cas_operacie_Coherant)[i] = time;

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
		//TODO
	}
}