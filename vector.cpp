#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

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
            if (j != studentai[i].pazymiukiek - 1) suma+=studentai[i].pazymiai[j];
        }
        studentai[i].rez=suma/(studentai[i].pazymiukiek-1)*0.4+studentai[i].pazymiai.back()*0.6;
    }
    
    
    /* Isvedimas
    cout << "\nStudentai:\n";
    for (int i = 0; i < vardai.size(); i++) {
        cout << vardai[i] << " " << pavardes[i] << " | Pazymiai: ";
        for (int p : pazymiai[i]) {
            cout << p << " ";
        }
        cout << endl;
    }
*/
    return 0;
}
