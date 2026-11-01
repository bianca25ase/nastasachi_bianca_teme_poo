#include <iostream>
#include <string>
using namespace std;

enum SistemOperare { ANDROID = 1, IOS = 2 };
 
class TelefonMobil {     
private:     
    const int id;
    string producator;
    int baterie;          
    string model;         
    SistemOperare sistem;
    int* memorie;
    int nrMemorie;

public:     
    static int nrTelefoane;

    TelefonMobil() : id(++nrTelefoane) { 
        producator = "Apple";
        model = "Iphone10";
        baterie = 60;
        sistem = ANDROID;
        nrMemorie = 3;
        memorie = new int[nrMemorie]; 
        for(int i = 0; i < nrMemorie; i++) { 
            memorie[i] = 128; 
        } 
    }     

    TelefonMobil(string producator, string model, int baterie, SistemOperare sistem, int* memorie, int nrMemorie)
    : id(++nrTelefoane) {     
        this->producator = producator;
        this->model = model;
        this->baterie = baterie;
        this->sistem = sistem;
        this->nrMemorie = nrMemorie;
        this->memorie = new int[nrMemorie];
        for(int i = 0; i < nrMemorie; i++) { 
            this->memorie[i] = memorie[i]; 
        }
    }     
    TelefonMobil(const TelefonMobil& c) : id(++nrTelefoane) { 
        this->producator = c.producator; 
        this->model = c.model;
        this->baterie = c.baterie;
        this->sistem = c.sistem;
        this->nrMemorie = c.nrMemorie;
        if(c.memorie != nullptr) { 
            this->memorie = new int[nrMemorie];
            for(int i = 0; i < nrMemorie; i++) { 
                this->memorie[i] = c.memorie[i]; 
            }
        } else { 
            this->memorie = nullptr; 
        }
    }     

    TelefonMobil& operator=(const TelefonMobil& c) { 
        if (this != &c) { 
            this->producator = c.producator;
            this->model = c.model;
            this->baterie = c.baterie;
            this->sistem = c.sistem;
            this->nrMemorie = c.nrMemorie;
            
            if(this->memorie != nullptr) { 
                delete[] this->memorie;
                this->memorie = nullptr;
            }
            
            if(c.memorie != nullptr) { 
                this->memorie = new int[nrMemorie];
                for(int i = 0; i < nrMemorie; i++) { 
                    this->memorie[i] = c.memorie[i];
                }
            } else { 
                this->memorie = nullptr; 
            }
        } 
        return *this; 
    }
    ~TelefonMobil() { 
        if (memorie != nullptr) { 
            delete[] memorie; 
        }
    }     

    int getId() { return id; }
    string getProd() { return producator; }
    string getMod() { return model; }
    int getBaterie() { return baterie; }
    SistemOperare getSistem() { return sistem; }
    int getNrmemorie() { return nrMemorie; }

    int getMemorie(int i) {
        if (i >= 0 && i < nrMemorie) {
            return memorie[i];
        }
        return -1;
    }

    void setProd(string prod) { producator = prod; }
    void setMod(string mod) { model = mod; }
    void setBaterie(int bat) {
        if (bat >= 0 && bat <= 100) {
            baterie = bat;
        }
        else {
            throw "Procent de baterie invalid!";
        }
    }

    void setMemorie(int i, int valoare) {
        if (i >= 0 && i < nrMemorie) {
            memorie[i] = valoare;
        }
    }
}; 

int TelefonMobil::nrTelefoane = 0;

int main()
{
    TelefonMobil t;
    int valori[] = { 128, 256, 512 };
    int nr = sizeof(valori) / sizeof(valori[0]);
    TelefonMobil t2("Samsung", "A56", 50, ANDROID, valori, nr);
    TelefonMobil t3(t2);

    cout << "TELEFON 1:" << endl;
    cout << t.getId() << endl;
    cout << t.getProd() << endl;
    cout << t.getMod() << endl;
    cout << t.getBaterie() << endl;

    cout << "TELEFON 2:" << endl;
    cout << t2.getId() << endl;
    cout << t2.getProd() << endl;
    cout << t2.getMod() << endl;
    cout << t2.getBaterie() << endl;

    for (int i = 0; i < t2.getNrmemorie(); i++)
    {
        cout << t2.getMemorie(i) << endl;
    }

    t2.setMod("Huawei");
    t2.setBaterie(90);
    t2.setMemorie(0, 1024);

    cout << "DUPA SETTER:" << endl;
    cout << t2.getMod() << endl;
    cout << t2.getBaterie() << endl;
    cout << t2.getMemorie(0) << endl;

    cout << "TELEFON 3:" << endl;
    cout << t3.getId() << endl;
    cout << t3.getProd() << endl;
    cout << t3.getMod() << endl;
    cout << t3.getBaterie() << endl;

    t = t2;
    cout << "DUPA OPERATORUL = (TELEFON 1):" << endl;
    cout << t.getMod() << endl;
    cout << t.getBaterie() << endl;
    try {
        t2.setBaterie(200); 
    }
    catch (const char* mesaj) {
        cout << "Eroare prinsa: " << mesaj << endl;
    }

    cout << "Numar total de telefoane create: " << TelefonMobil::nrTelefoane << endl;

    return 0;
}
