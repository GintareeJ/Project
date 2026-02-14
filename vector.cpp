#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iomanip>

using std::cin;
using std::string;
using std::cout;
std::vector<int>paz;


//darbas atliktas su vector konteineriu

struct studentas
{
   string vardas, pavarde;
   std::vector<int> pazymiai;
   int pazymiukiek; 
   double rez; //rezultatui su vidurkiu saugoti
   double rez2; //rezultatui su mediana saugoti
};

int main() {
    std::vector<studentas> studentai;
    srand(time(nullptr)); //kad kiekviena karta butu generuojami skirtingi pazymiai
    string pavardes[] = { "Kazlauskas", "Petrauskas", "Jankauskas", "Vaitkus",
        "Kazlauskaite", "Petrauskaite", "Jankauskaite", "Vaitkute" };
    int pavN = sizeof(pavardes) / sizeof(pavardes[0]);

    string vardai[] = { "Jonas", "Petras", "Mantas", "Lukas", "Tomas",
        "Ieva", "Aiste", "Monika", "Greta", "Laura" };
    int vardN = sizeof(vardai) / sizeof(vardai[0]);

    //meniu
    int m = 0;
    while (m != 4) {
        cout << "Pasirinkite, kokiu budu norite, kad programa vykdytu uzduoti (1 - duomenu irasymas ranka, 2 - generuoti tik pazymius, 3 - generuoti studentu vardus, pavardes ir pazymius, 4 - baigti darba): " << std::endl;
        cin >> m;

    if (m == 1)
    {
    while (true) {
        studentas s;
        cout << "Iveskite studento varda (0 - baigti): ";
        cin >> s.vardas;

        if (s.vardas == "0")
            break;

        cout << "Iveskite pavarde: ";
        cin >> s.pavarde;
        cout << "Iveskite pazymius (0 - baigti), paskutinis egzaminas: ";
        int p; //pazymiams
        int kiek=0; //pazymiu kiekiui
        while(true)
        {
          cin>>p;
          if(p!= 0) kiek++;
          if (p == 0) break;
          s.pazymiai.push_back(p);
        }
       s.pazymiukiek=kiek;
       kiek=0; 
       studentai.push_back(s);
    }

    double suma; //rezultatui skaiciuoti
    for(int i=0; i<studentai.size(); i++)
    {
        suma=0;
        for(int j=0; j<studentai[i].pazymiukiek; j++)
        {
            if (j != studentai[i].pazymiukiek - 1) suma+=studentai[i].pazymiai[j]; //sumuojame, tik jei j nera egzamino pazymio numeris
        }
        studentai[i].rez=suma/(studentai[i].pazymiukiek-1)*0.4+studentai[i].pazymiai.back()*0.6;
    }
    
    //rusiuojame medianai
    for(int i=0; i<studentai.size(); i++)
    {
        suma=0;
        for(int j=0; j<studentai[i].pazymiukiek-1; j++)
        {
           for(int jj=0; jj<studentai[i].pazymiukiek-1; jj++)
           {
            if(studentai[i].pazymiai[j]<studentai[i].pazymiai[jj]) std::swap(studentai[i].pazymiai[j], studentai[i].pazymiai[jj]);
           }
        }
    }
    //skaiciuojame mediana ir bendra bala
        for(int i=0; i<studentai.size(); i++)
    {
        int k = studentai[i].pazymiukiek;
        int nd = k - 1;

        double med;
        if (nd % 2 == 1) med = studentai[i].pazymiai[nd / 2];
        else med = (studentai[i].pazymiai[nd / 2 - 1] + studentai[i].pazymiai[nd / 2]) / 2.0;
        studentai[i].rez2=med*0.4+studentai[i].pazymiai.back()*0.6;
    }
    
    int a;
    cout << "Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):" << std::endl;
            cin >> a;
            if (a == 0)
            {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < studentai.size(); i++) {
                    cout << std::left << std::setw(15) << studentai[i].pavarde << std::left << std::setw(15) << studentai[i].vardas<< std::fixed << std::setprecision(2) << studentai[i].rez << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            else {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < studentai.size(); i++) {
                    cout << std::left << std::setw(15) << studentai[i].pavarde << std::left << std::setw(15) << studentai[i].vardas<<std::fixed << std::setprecision(2) << studentai[i].rez2 << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            studentai.clear();
        }
        if(m==2)
        {
          while (true) {
        studentas s;
        cout << "Iveskite studento varda (0 - baigti): ";
        cin >> s.vardas;

        if (s.vardas == "0")
            break;

        cout << "Iveskite pavarde: ";
        cin >> s.pavarde;
        cout << "Pazymiai bus generuojami automatiskai, iveskite pazymiu kieki: ";
        int kiek=0; //pazymiu kiekis
        int p; //pazymiams
        cin>>kiek;
        s.pazymiai.clear();
        for(int i=0; i<kiek; i++)
        {
          p=rand()% 10 + 1;  
          s.pazymiai.push_back(p);
        }
       s.pazymiukiek=kiek;
       kiek=0; 
       studentai.push_back(s);
    }

    double suma; //rezultatui skaiciuoti
    for(int i=0; i<studentai.size(); i++)
    {
        suma=0;
        for(int j=0; j<studentai[i].pazymiukiek; j++)
        {
            if (j != studentai[i].pazymiukiek - 1) suma+=studentai[i].pazymiai[j]; //sumuojame, tik jei j nera egzamino pazymio numeris
        }
        studentai[i].rez=suma/(studentai[i].pazymiukiek-1)*0.4+studentai[i].pazymiai.back()*0.6;
    }
    
    //rusiuojame medianai
    for(int i=0; i<studentai.size(); i++)
    {
        suma=0;
        for(int j=0; j<studentai[i].pazymiukiek-1; j++)
        {
           for(int jj=0; jj<studentai[i].pazymiukiek-1; jj++)
           {
            if(studentai[i].pazymiai[j]<studentai[i].pazymiai[jj]) std::swap(studentai[i].pazymiai[j], studentai[i].pazymiai[jj]);
           }
        }
    }
    //skaiciuojame mediana ir bendra bala
        for(int i=0; i<studentai.size(); i++)
    {
        int k = studentai[i].pazymiukiek;
        int nd = k - 1;

        double med;
        if (nd % 2 == 1) med = studentai[i].pazymiai[nd / 2];
        else med = (studentai[i].pazymiai[nd / 2 - 1] + studentai[i].pazymiai[nd / 2]) / 2.0;
        studentai[i].rez2=med*0.4+studentai[i].pazymiai.back()*0.6;
    }
    
    int a;
    cout << "Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):" << std::endl;
            cin >> a;
            if (a == 0)
            {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < studentai.size(); i++) {
                    cout << std::left << std::setw(15) << studentai[i].pavarde << std::left << std::setw(15) << studentai[i].vardas<< std::fixed << std::setprecision(2) << studentai[i].rez << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            else {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < studentai.size(); i++) {
                    cout << std::left << std::setw(15) << studentai[i].pavarde << std::left << std::setw(15) << studentai[i].vardas<<std::fixed << std::setprecision(2) << studentai[i].rez2 << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            studentai.clear();
        } 
        if(m==3)
        {
        studentas s;
        int skiek; //studentu kiekis
        cout << "Sudentu vardai ir pavardes bus generuojami automatiskai, iveskite studentu kieki: ";
        cin >> skiek;
        cout << "Pazymiai bus generuojami automatiskai, iveskite pazymiu kieki: ";
        int kiek; //pazymiu kiekis
        cin>>kiek;
        for(int i=0; i<skiek; i++)
        {
             s.vardas = vardai[rand() % vardN];
                if (s.vardas.back() == 's') {
                    do { s.pavarde = pavardes[rand() % pavN]; } while (s.pavarde.back() != 's');
                } else {
                    do { s.pavarde = pavardes[rand() % pavN]; } while (s.pavarde.back() == 's');
                }
        int p; //pazymiams
        s.pazymiai.clear();
        for(int i=0; i<kiek; i++)
        {
          p=rand()% 10 + 1;  
          s.pazymiai.push_back(p);
        }
       s.pazymiukiek=kiek; 
       studentai.push_back(s);
        }
    double suma; //rezultatui skaiciuoti
    for(int i=0; i<studentai.size(); i++)
    {
        suma=0;
        for(int j=0; j<studentai[i].pazymiukiek; j++)
        {
            if (j != studentai[i].pazymiukiek - 1) suma+=studentai[i].pazymiai[j]; //sumuojame, tik jei j nera egzamino pazymio numeris
        }
        studentai[i].rez=suma/(studentai[i].pazymiukiek-1)*0.4+studentai[i].pazymiai.back()*0.6;
    }
    
    //rusiuojame medianai
    for(int i=0; i<studentai.size(); i++)
    {
        suma=0;
        for(int j=0; j<studentai[i].pazymiukiek-1; j++)
        {
           for(int jj=0; jj<studentai[i].pazymiukiek-1; jj++)
           {
            if(studentai[i].pazymiai[j]<studentai[i].pazymiai[jj]) std::swap(studentai[i].pazymiai[j], studentai[i].pazymiai[jj]);
           }
        }
    }
    //skaiciuojame mediana ir bendra bala
        for(int i=0; i<studentai.size(); i++)
    {
        int k = studentai[i].pazymiukiek;
        int nd = k - 1;

        double med;
        if (nd % 2 == 1) med = studentai[i].pazymiai[nd / 2];
        else med = (studentai[i].pazymiai[nd / 2 - 1] + studentai[i].pazymiai[nd / 2]) / 2.0;
        studentai[i].rez2=med*0.4+studentai[i].pazymiai.back()*0.6;
    }
    
    int a;
    cout << "Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):" << std::endl;
            cin >> a;
            if (a == 0)
            {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < studentai.size(); i++) {
                    cout << std::left << std::setw(15) << studentai[i].pavarde << std::left << std::setw(15) << studentai[i].vardas<< std::fixed << std::setprecision(2) << studentai[i].rez << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            else {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < studentai.size(); i++) {
                    cout << std::left << std::setw(15) << studentai[i].pavarde << std::left << std::setw(15) << studentai[i].vardas<<std::fixed << std::setprecision(2) << studentai[i].rez2 << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            studentai.clear();
        }
        if (m == 4) cout << "Baigiamas darbas.\n";
    } 

    return 0;
}
