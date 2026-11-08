#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Autoturism
{
private:
    string marca;
    string model;
    int putere;
    double pret;
    float* distanteParcurse;
    int nrDrumuri;
    char* taraDeProductie;

public:
    Autoturism()
    {
        marca = "Necunoscuta";
        model = "Necunoscut";
        putere = 0;
        pret = 5000;
        distanteParcurse = nullptr;
        nrDrumuri = 0;
        taraDeProductie = nullptr;
    }

    Autoturism(string marca, string model, int putere)
    {
        this->marca = marca;
        this->model = model;
        this->putere = putere;
        pret = 5000;
        distanteParcurse = nullptr;
        nrDrumuri = 0;
        taraDeProductie = nullptr;
    }

    Autoturism(string marca, string model, float* distante, int nrDrumuri)
    {
        this->marca = marca;
        this->model = model;
        this->putere = 0;
        pret = 5000;
        this->nrDrumuri = 0;
        distanteParcurse = nullptr;
        taraDeProductie = nullptr;

        if (nrDrumuri > 0 && distante != nullptr)
        {
            this->nrDrumuri = nrDrumuri;
            this->distanteParcurse = new float[nrDrumuri];
            for (int a = 0; a < nrDrumuri; a++)
            {
                distanteParcurse[a] = distante[a];
            }
        }
    }

    ~Autoturism()
    {
        if (distanteParcurse != nullptr)
        {
            delete[] distanteParcurse;
            distanteParcurse = nullptr;
        }
        if (taraDeProductie != nullptr)
        {
            delete[] taraDeProductie;
            taraDeProductie = nullptr;
        }
    }

    Autoturism(const Autoturism& c)
    {
        marca = c.marca;
        model = c.model;
        putere = c.putere;
        pret = c.pret;
        nrDrumuri = c.nrDrumuri;
        distanteParcurse = nullptr;
        taraDeProductie = nullptr;

        if (c.nrDrumuri > 0 && c.distanteParcurse != nullptr)
        {
            distanteParcurse = new float[c.nrDrumuri];
            for (int a = 0; a < c.nrDrumuri; a++)
            {
                distanteParcurse[a] = c.distanteParcurse[a];
            }
        }

        if (c.taraDeProductie != nullptr)
        {
            taraDeProductie = new char[strlen(c.taraDeProductie) + 1];
            strcpy_s(taraDeProductie, strlen(c.taraDeProductie) + 1, c.taraDeProductie);
        }
    }

    string getMarca()
    {
        return marca;
    }

    void setMarca(string marca)
    {
        if (marca.length() >= 3)
        {
            this->marca = marca;
        }
    }

    int getNrDrumuri()
    {
        return nrDrumuri;
    }

    float* getDistanteParcurse()
    {
        if (distanteParcurse == nullptr || nrDrumuri <= 0)
        {
            return nullptr;
        }
        float* copie = new float[nrDrumuri];
        for (int i = 0; i < nrDrumuri; i++)
        {
            copie[i] = distanteParcurse[i];
        }
        return copie;
    }

    void setDistante(float* distanteParcurse, int nrDrumuri)
    {
        if (this->distanteParcurse != nullptr)
        {
            delete[] this->distanteParcurse;
            this->distanteParcurse = nullptr;
        }

        if (nrDrumuri > 0 && distanteParcurse != nullptr)
        {
            this->nrDrumuri = nrDrumuri;
            this->distanteParcurse = new float[nrDrumuri];
            for (int i = 0; i < nrDrumuri; i++)
            {
                this->distanteParcurse[i] = distanteParcurse[i];
            }
        }
        else
        {
            this->nrDrumuri = 0;
            this->distanteParcurse = nullptr;
        }
    }

    char* getTaraDeProductie()
    {
        if (taraDeProductie != nullptr)
        {
            char* copie = new char[strlen(taraDeProductie) + 1];
            strcpy_s(copie, strlen(taraDeProductie) + 1, taraDeProductie);
            return copie;
        }
        return nullptr;
    }

    void setTaraDeProductie(const char* tara)
    {
        if (taraDeProductie != nullptr)
        {
            delete[] taraDeProductie;
            taraDeProductie = nullptr;
        }

        if (tara != nullptr)
        {
            taraDeProductie = new char[strlen(tara) + 1];
            strcpy_s(taraDeProductie, strlen(tara) + 1, tara);
        }
    }

    char* AdresaInceputTaraDeProductie()
    {
        return taraDeProductie;
    }
};

int main()
{
    Autoturism a1;
    Autoturism a2("BMW", "X5", 300);

    float distante[] = { 10.5f, 25.0f, 15.2f };
    Autoturism a3("Audi", "A4", distante, 3);

    Autoturism a4 = a3;

    a1.setMarca("Dacia");
    a1.setTaraDeProductie("Romania");

    cout << "Marca a1: " << a1.getMarca() << endl;
    cout << "Nr drumuri a3: " << a3.getNrDrumuri() << endl;

    char* tara = a1.getTaraDeProductie();
    if (tara != nullptr)
    {
        cout << "Tara a1: " << tara << endl;
        delete[] tara;
    }

    return 0;
}
