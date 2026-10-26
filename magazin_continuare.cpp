#include<iostream>
#include<string>
using namespace std;

class Magazin
{  private: 
          const int id;
          string denumire;
          int nrProduse;
          float* preturiProduse;
   public: 
          static int nrMagazine;

Magazin() : id(++nrMagazine)
{  this->denumire="Default";
   this->nrProduse=0;
   this->preturiProduse=nullptr;
}
Magazin(int id, string denumire, int nrProduse, float* preturiProduse)
   : id(id)
{
   this->denumire=denumire;
   this->nrProduse=nrProduse;
   this->preturiProduse=new float[nrProduse];
   for( int i=0; i< this->nrProduse; i++)
     {  this->preturiProduse[i] = preturiProduse[i]; }
nrMagazine++;
}

// Constructor de copiere 
    Magazin(const Magazin& m) : id(m.id) 
{
        this->denumire = m.denumire;
        this->nrProduse = m.nrProduse;
        if (m.preturiProduse != nullptr && m.nrProduse > 0) {
            this->preturiProduse = new float[m.nrProduse];
            for (int i = 0; i < m.nrProduse; i++) {
                this->preturiProduse[i] = m.preturiProduse[i];
            }
        }
        else {
            this->preturiProduse = nullptr;
        }
    }
// Operator de atribuire
Magazin& operator=(const Magazin& m) 
{
        if (this != &m) {
            this->denumire = m.denumire;
            this->nrProduse = m.nrProduse;

            if (this->preturiProduse != nullptr) {
                delete[] this->preturiProduse;
            }

            if (m.preturiProduse != nullptr && m.nrProduse > 0) {
                this->preturiProduse = new float[m.nrProduse];
                for (int i = 0; i < m.nrProduse; i++) {
                    this->preturiProduse[i] = m.preturiProduse[i];
                }
            }
            else {
                this->preturiProduse = nullptr;
            }
        }
        return *this;
    }

void afisareMagazin() 
{ cout<<endl<<"Id: "<< this->id;
  cout<<endl<<"Denumire: "<< this->denumire;
  cout<<endl<<"NrProduse: "<<this->nrProduse;
  if(this-> nrProduse > 0)
{ cout << endl << "Preturi produse: ";
  for(int i=0; i<this->nrProduse -1; i++)
   { 
     cout<<this->preturiProduse[i]<<" , ";
   } 
  cout<<this->preturiProduse[this->nrProduse -1] <<" . ";
} 
cout<<endl;
}

// Get și Set pentru nrProduse
    int getNrProduse() {
        return this->nrProduse;
    }

    void setNrProduse(int nrProduseNou) 
{
        if (nrProduseNou >= 0) {
            this->nrProduse = nrProduseNou;
        }
        else {
            throw "Valoare negativa pentru numarul de produse!";
        }
    }

    // Get și Set pentru preturiProduse
    float* getPreturiProduse() {
        if (this->nrProduse == 0 || this->preturiProduse == nullptr) 
        {
            return nullptr;
        }
        float* preturiNoi = new float[this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++) {
            preturiNoi[i] = this->preturiProduse[i];
        }
        return preturiNoi;
    }
void setPreturiProduse(const float* preturi, int nrP) {
        setNrProduse(nrP);

        if (this->preturiProduse != nullptr) {
            delete[] this->preturiProduse;
        }

        if (this->nrProduse > 0 && preturi != nullptr) {
            this->preturiProduse = new float[this->nrProduse];
            for (int i = 0; i < this->nrProduse; i++) {
                this->preturiProduse[i] = preturi[i];
            }
        }
        else {
            this->preturiProduse = nullptr;
        }
    }
~Magazin() 
{ if(this->preturiProduse != nullptr) 
   { delete[] this->preturiProduse;
   }
}
}; 
int Magazin :: nrMagazine = 0;
int main() {
    Magazin mMega;
    mMega.afisareMagazin();

    // Testare set și try-catch
    try {
        mMega.setNrProduse(3);
    }
    catch (const char* mesaj) {
        cout << endl << mesaj;
    }
    catch (...) {
        cout << endl << "Eroare necunoscuta!";
    }
    cout << endl << "Noul numar de produse este: " << mMega.getNrProduse();
    float* preturiInitiale = new float[3] { 12.5f, 45.0f, 9.99f };
    mMega.setPreturiProduse(preturiInitiale, 3);
    delete[] preturiInitiale; 
    float* preturi = mMega.getPreturiProduse();
    if (preturi != nullptr) {
        cout << endl << "Preturile preluate prin get sunt: ";
        for (int i = 0; i < 3; i++) {
            cout << preturi[i] << " lei, ";
        }
        delete[] preturi; 
    }
    mMega.afisareMagazin();
    float* preturiProduseZara = new float[3] { 35.0f, 27.0f, 41.0f };
    Magazin* pZara = new Magazin(5, "Zara", 3, preturiProduseZara);
    pZara->afisareMagazin();
    
    delete pZara;
    delete[] preturiProduseZara; 
    cout << endl << "Am construit " << Magazin::nrMagazine << " magazine!" << endl;
    return 0;
}







