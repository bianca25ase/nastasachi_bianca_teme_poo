#include<iostream>
#include<string>
#include<cstring>

using namespace std;

class Carte {

	const string ISBN;
	string titlu;
	char* autor;
	int nrPagini;

	static int nrCarti;

public:

	Carte() :ISBN("1234")
	{
		titlu = "default";
		autor = nullptr;
		nrPagini = 0;
		nrCarti++;
	}

	Carte(string ISBN, string titlu, const char* autor, int nrPagini) : ISBN(ISBN)
	{
		nrCarti++;
		this->titlu = titlu;

		if (autor != nullptr && nrPagini > 0)
		{
			this->nrPagini = nrPagini;
			this->autor = new char[strlen(autor) + 1];
			strcpy_s(this->autor, strlen(autor) + 1, autor);
		}
		else
		{
			this->autor = nullptr;
			this->nrPagini = 0;
		}
	}

	Carte(const Carte& c) : ISBN(c.ISBN)
	{
		nrCarti++;
		this->titlu = c.titlu;

		if (c.autor != nullptr && c.nrPagini > 0)
		{
			this->nrPagini = c.nrPagini;
			this->autor = new char[strlen(c.autor) + 1];
			strcpy_s(this->autor, strlen(c.autor) + 1, c.autor);
		}
		else
		{
			this->autor = nullptr;
			this->nrPagini = 0;
		}
	}

	~Carte()
	{
		if (autor != nullptr) {
			delete[] autor;
			autor = nullptr;
		}
		nrCarti--;
	}

	string getTitlu() {
		return titlu;
	}

	string getISBN() {
		return ISBN;
	}

	int getNrPagini() {
		return nrPagini;
	}

	static int getnrcarti()
	{
		return nrCarti;
	}

	char* getautor()
	{
		if (autor != nullptr)
		{
			char* copie = new char[strlen(autor) + 1];
			strcpy_s(copie, strlen(autor) + 1, autor);
			return copie;
		}
		return nullptr;
	}

	void setTitlu(string titlu)
	{
		this->titlu = titlu;
	}

	void setNrPagini(int nrPagini)
	{
		this->nrPagini = nrPagini;
	}

	static void setnrcarti(int nrCarti)
	{
		Carte::nrCarti = nrCarti;
	}

	void setAutor(const char* autor, int nr)
	{
		if (this->autor != nullptr)
		{
			delete[] this->autor;
			this->autor = nullptr;
		}

		if (autor != nullptr && nr > 0)
		{
			this->nrPagini = nr;
			this->autor = new char[strlen(autor) + 1];
			strcpy_s(this->autor, strlen(autor) + 1, autor);
		}
		else
		{
			this->autor = nullptr;
			nrPagini = 0;
		}
	}
};

int Carte::nrCarti = 0;

int main()
{
	Carte c1;

	Carte c2("978973", "Moara cu noroc", "Ioan Slavici", 120);

	Carte c3 = c2;

	cout << "Cartea 2 - Titlu: " << c2.getTitlu() << ", ISBN: " << c2.getISBN() << ", Pagini: " << c2.getNrPagini() << endl;

	char* autorC2 = c2.getautor();
	if (autorC2 != nullptr) {
		cout << "Autorul cartii 2: " << autorC2 << endl;
		delete[] autorC2;
	}

	c1.setTitlu("Ion");
	c1.setNrPagini(400);
	c1.setAutor("Liviu Rebreanu", 400);

	cout << "Cartea 1 modificata - Titlu: " << c1.getTitlu() << ", Pagini: " << c1.getNrPagini() << endl;

	cout << "Numar total de carti instantiate: " << Carte::getnrcarti() << endl;

	return 0;
}

