#include <iostream>
#include <string>

using namespace std;

enum TipHotel { URBAN = 1, RESORT = 2 };

class Hotel {
private:
	const int id;
	float pretMediuCamera;
	string denumire;
	TipHotel tip;
	int nrCamere;
	float* preturiCamere;
public:
	static int nrHoteluri;

	Hotel() : id(++nrHoteluri) {
		this->denumire = "Hotel Default";
		this->pretMediuCamera = 0.0f;
		this->tip = URBAN;
		this->nrCamere = 0;
		this->preturiCamere = nullptr;
	}

	Hotel(int id, float pretMediuCamera, string denumire, TipHotel tip, int nrCamere, float* preturiCamere)
		: id(id) {
		this->pretMediuCamera = pretMediuCamera;
		this->denumire = denumire;
		this->tip = tip;
		this->nrCamere = nrCamere;
		this->preturiCamere = new float[nrCamere];
		for (int i = 0; i < this->nrCamere; i++) {
			this->preturiCamere[i] = preturiCamere[i];
		}
		nrHoteluri++;
	}

	Hotel(const Hotel& h) : id(++nrHoteluri) {
		this->denumire = h.denumire;
		this->pretMediuCamera = h.pretMediuCamera;
		this->tip = h.tip;
		this->nrCamere = h.nrCamere;

		if (h.preturiCamere != nullptr) {
			this->preturiCamere = new float[h.nrCamere];
			for (int i = 0; i < h.nrCamere; i++) {
				this->preturiCamere[i] = h.preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
		}
	}

	Hotel& operator=(const Hotel& h) {
		if (this == &h) return *this;

		this->denumire = h.denumire;
		this->pretMediuCamera = h.pretMediuCamera;
		this->tip = h.tip;
		this->nrCamere = h.nrCamere;

		if (this->preturiCamere != nullptr) {
			delete[] this->preturiCamere;
			this->preturiCamere = nullptr;
		}

		if (h.preturiCamere != nullptr) {
			this->preturiCamere = new float[h.nrCamere];
			for (int i = 0; i < h.nrCamere; i++) {
				this->preturiCamere[i] = h.preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
		}
		return *this;
	}

	void afisareHotel() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret mediu camera: " << this->pretMediuCamera << " lei";
		cout << endl << "Nr camere: " << this->nrCamere;
		cout << endl << "Tip: ";
		if (this->tip == URBAN) {
			cout << "URBAN";
		}
		else {
			cout << "RESORT";
		}

		if (this->nrCamere > 0 && this->preturiCamere != nullptr) {
			cout << endl << "Preturi camere: ";
			for (int i = 0; i < this->nrCamere - 1; i++) {
				cout << this->preturiCamere[i] << ", ";
			}
			cout << this->preturiCamere[this->nrCamere - 1] << ".";
		}
	}

	int getNrCamere() {
		return this->nrCamere;
	}

	void setNrCamere(int nrCamereNou) {
		if (nrCamereNou >= 0) {
			this->nrCamere = nrCamereNou;
		}
		else {
			throw "Valoare negativa";
		}
	}

	float* getPreturiCamere() {
		if (this->nrCamere == 0 || this->preturiCamere == nullptr) return nullptr;
		float* preturiNou = new float[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++) {
			preturiNou[i] = this->preturiCamere[i];
		}
		return preturiNou;
	}

	void setPreturiCamere(float* vector, int nrC) {
		setNrCamere(nrC);

		if (this->preturiCamere != nullptr) {
			delete[] this->preturiCamere;
		}

		this->preturiCamere = new float[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++) {
			this->preturiCamere[i] = vector[i];
		}
		delete[] vector;
	}

	~Hotel() {
		if (this->preturiCamere != nullptr) {
			delete[] this->preturiCamere;
		}
	}

	bool operator<(const Hotel& h) {
		return this->nrCamere < h.nrCamere;
	}

	void operator+=(float pretDeAdunat) {
		this->pretMediuCamera += pretDeAdunat;
	}

	bool operator!() {
		return this->pretMediuCamera > 0;
	}

	float operator()(float valoareDeAdaugat) {
		return this->pretMediuCamera + valoareDeAdaugat;
	}

	float& operator[](int index) {
		if (index >= 0 && index < this->nrCamere) {
			return this->preturiCamere[index];
		}
		else {
			throw exception();
		}
	}

	friend ostream& operator<<(ostream& out, const Hotel& h) {
		out << endl << "--- Afisare Hotel (operator <<) ---";
		out << endl << "Id: " << h.id;
		out << endl << "Denumire: " << h.denumire;
		out << endl << "Pret mediu: " << h.pretMediuCamera;
		out << endl << "Tip: ";
		if (h.tip == URBAN) out << "URBAN";
		else if (h.tip == RESORT) out << "RESORT";
		out << endl << "Nr camere: " << h.nrCamere;
		if (h.preturiCamere != nullptr && h.nrCamere > 0) {
			out << endl << "Preturi camere: ";
			for (int i = 0; i < h.nrCamere - 1; i++) {
				out << h.preturiCamere[i] << " lei, ";
			}
			out << h.preturiCamere[h.nrCamere - 1] << " lei.";
		}
		return out;
	}

	friend istream& operator>>(istream& in, Hotel& h) {
		cout << endl << "Pret mediu camera: ";
		in >> h.pretMediuCamera;

		cout << endl << "Denumire: ";
		in >> h.denumire;

		cout << endl << "Tip (1-URBAN, 2-RESORT): ";
		int tipInt;
		in >> tipInt;
		if (tipInt == 1) h.tip = URBAN;
		else h.tip = RESORT;

		cout << endl << "Nr camere: ";
		in >> h.nrCamere;

		if (h.preturiCamere != nullptr) {
			delete[] h.preturiCamere;
			h.preturiCamere = nullptr;
		}

		if (h.nrCamere > 0) {
			h.preturiCamere = new float[h.nrCamere];
			for (int i = 0; i < h.nrCamere; i++) {
				cout << "preturiCamere[" << i << "]: ";
				in >> h.preturiCamere[i];
			}
		}
		return in;
	}

	Hotel operator++(int) {
		Hotel copie = *this;
		this->pretMediuCamera++;
		return copie;
	}

	Hotel operator++() {
		this->pretMediuCamera++;
		return *this;
	}

	explicit operator int() {
		return this->nrCamere;
	}
};

int Hotel::nrHoteluri = 0;

int main() {
	Hotel hGrand;

	hGrand += 150.5f;

	if (!hGrand) {
		cout << endl << "Pret mediu nenul!";
	}
	else {
		cout << endl << "Pret mediu nul!";
	}

	cout << endl << "Apel operator functie: " << hGrand(50.0f);

	cout << hGrand;

	Hotel h1 = hGrand++;
	cout << h1;
	cout << hGrand;

	Hotel h2 = ++hGrand;
	cout << h2;
	cout << hGrand;

	float* preturi = new float[3] {250.0f, 300.5f, 450.0f};
	Hotel* pHotelLux = new Hotel(10, 335.0f, "Luxor", RESORT, 3, preturi);
	pHotelLux->afisareHotel();

	if (hGrand < *pHotelLux) {
		cout << endl << "Hotelul Grand are mai putine camere decat Luxor!";
	}
	else {
		cout << endl << "Hotelul Luxor are mai putine camere!";
	}

	try {
		(*pHotelLux)[0] = 280.0f;
		cout << endl << "Apel operator index [0] modificat: " << (*pHotelLux)[0];
	}
	catch (...) {
		cout << endl << "Eroare la accesarea indexului!";
	}

	cout << endl << "Am construit in total " << Hotel::nrHoteluri << " hoteluri!";

	cout << endl << "Cast explicit la int (nr camere): " << (int)(*pHotelLux);

	delete pHotelLux;
	return 0;
}
