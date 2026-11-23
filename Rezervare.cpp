#include <iostream>
#include <string>
#include <exception>

using namespace std;

class ExceptieCustom : public exception {
private:
	string mesajEroare;
public:
	ExceptieCustom(const char* mesaj) : mesajEroare(mesaj) {}

	const char* what() const noexcept override {
		return mesajEroare.c_str();
	}
};

class Rezervare {
protected:
	const int codRezervare;
	string destinatie;
	float pretBaza;
public:
	static const float PRET_MINIM;

	Rezervare() : codRezervare(0), destinatie("Bucuresti - Atena"), pretBaza(500) {}

	Rezervare(int codR, string destinatieR, float pretBazaR)
		: codRezervare(codR), destinatie(destinatieR), pretBaza(pretBazaR) {
		if (pretBaza < PRET_MINIM) {
			throw ExceptieCustom("Pretul de baza este prea mic!");
		}
	}

	virtual void afisare() {
		cout << endl << "Cod rezervare: " << codRezervare;
		cout << endl << "Destinatie: " << destinatie;
		cout << endl << "Pret baza: " << pretBaza;
	}

	virtual ~Rezervare() {}

	virtual float calculeazaPretFinal() = 0;
};

const float Rezervare::PRET_MINIM = 50;

class RezervareVIP : public Rezervare {
private:
	float taxaBagajExtra;
public:
	RezervareVIP() : Rezervare() {
		taxaBagajExtra = 0;
	}

	RezervareVIP(int codR, string destinatieR, float pretBazaR, float taxaBagajExtraR)
		: Rezervare(codR, destinatieR, pretBazaR) {
		if (taxaBagajExtraR < 0) {
			throw ExceptieCustom("Taxa de bagaj nu poate fi negativa!");
		}
		taxaBagajExtra = taxaBagajExtraR;
	}

	void afisare() override {
		Rezervare::afisare();
		cout << endl << "Taxa bagaj extra: " << taxaBagajExtra;
		cout << endl << "Pret final VIP: " << calculeazaPretFinal();
	}

	float calculeazaPretFinal() override {
		return pretBaza + taxaBagajExtra;
	}
};

class CalculatorComision {
public:
	virtual float calculeazaComision(float suma) = 0;
	virtual float calculeazaTotalCuComision(float suma) = 0;
	virtual ~CalculatorComision() {}
};

class ComisionAgentie : public CalculatorComision {
private:
	float procent;
public:
	ComisionAgentie() {
		procent = 10;
	}

	ComisionAgentie(float procentC) {
		procent = procentC;
	}

	float calculeazaComision(float suma) override {
		return suma * (procent / 100.0f);
	}

	float calculeazaTotalCuComision(float suma) override {
		return suma + calculeazaComision(suma);
	}
};

int main() {
	try {
		RezervareVIP rInvalida(10, "Cairo", 20, 50);
	}
	catch (const exception& e) {
		cout << endl << "Eroare prinsa: " << e.what();
	}

	Rezervare* vectorRezervari[3];

	vectorRezervari[0] = new RezervareVIP(101, "Antalya", 1200, 150);
	vectorRezervari[1] = new RezervareVIP(102, "Creta", 950, 100);
	vectorRezervari[2] = new RezervareVIP(103, "Hurghada", 1500, 200);

	for (int i = 0; i < 3; i++) {
		vectorRezervari[i]->afisare();
		cout << endl << "-------------------";
		delete vectorRezervari[i];
	}

	Rezervare* pRezervare = new RezervareVIP();
	pRezervare->afisare();
	delete pRezervare;

	CalculatorComision* calc = new ComisionAgentie(15);
	cout << endl << "Comision: " << calc->calculeazaComision(1000);
	cout << endl << "Total cu comision: " << calc->calculeazaTotalCuComision(1000);

	delete calc;

	return 0;
}
