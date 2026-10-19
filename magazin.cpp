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
~Magazin() 
{ if(this->preturiProduse != nullptr) 
   { delete[] this->preturiProduse;
   }
}
}; 
int Magazin :: nrMagazine = 0;
int main() 
{
   Magazin mMega;
	 mMega.afisareMagazin();
	 float* preturi = new float[3] { 12.5f, 45.0f, 9.99f };
	 Magazin* pZara = new Magazin(5, "Zara", 3, preturi);
	 pZara->afisareMagazin();
	 delete pZara;
   delete[] preturi;
cout << endl << "Am construit " << Magazin::nrMagazine << " magazine!" << endl;
return 0;
}
