#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

//darbas atliktas su dinamine atmintimi
using std::cin;
using std::string;
using std::cout;

struct studentas {
    string* var;
    string* pav;

    int* paz; //pazymiai  
    int  pazkiek; //pazymiu kiekis
    int  pazcap; //kiek telpa - capacity 
    double* rez; //rezultatas vedant n.d vidurki
    double* rez2; //rezultatas skaiciuojant bendra bala su mediana
};

void didStud(studentas*& s, int& scap) { //didinti studentus
    int newCap;
    if (scap == 0) {
        newCap = 2; //pradinis dydis
    } else {
        newCap = scap * 2; //kai truksta vietos dvigubiname
    }

    studentas* ns = new studentas[newCap];

    for (int i = 0; i < scap; i++) ns[i] = s[i]; //kopijuoja rodykles

    delete[] s;
    s = ns;
    scap = newCap;
}

void pridBal(studentas& st, int grade) { //prideda Bala
    if (st.pazcap == 0) {
        st.pazcap = 4;
        st.paz = new int[st.pazcap];
        st.pazkiek = 0;
    }
    if (st.pazkiek == st.pazcap) {
        int newCap = st.pazcap * 2;
        int* np = new int[newCap];
        for (int i = 0; i < st.pazkiek; i++) np[i] = st.paz[i];
        delete[] st.paz;
        st.paz = np;
        st.pazcap = newCap;
    }
    st.paz[st.pazkiek++] = grade;
}

void atlaisvinti(studentas*& s, int& scount, int& scap) {
    for (int i = 0; i < scount; i++) {
        delete[] s[i].paz;
        delete s[i].var;
        delete s[i].pav;
        delete s[i].rez;
        delete s[i].rez2;
    }
    delete[] s;
    s = nullptr;
    scount = 0;
    scap = 0;
}

int main()
{
    string pavardes[] = { "Kazlauskas", "Petrauskas", "Jankauskas", "Vaitkus",
        "Kazlauskaite", "Petrauskaite", "Jankauskaite", "Vaitkute" };
    int pavN = sizeof(pavardes) / sizeof(pavardes[0]);

    string vardai[] = { "Jonas", "Petras", "Mantas", "Lukas", "Tomas",
        "Ieva", "Aiste", "Monika", "Greta", "Laura" };
    int vardN = sizeof(vardai) / sizeof(vardai[0]);

    srand(time(nullptr)); //kad kiekviena karta butu generuojami skirtingi pazymiai
    studentas* s = nullptr;
    int scount = 0; //kiek studentų ivesta
    int scap = 0;   //kiek telpa
    int a;
    string v, p;
    int pz;

    //meniu
    int m = 0;
    while (m != 4) {
        cout << "Pasirinkite, kokiu budu norite, kad programa vykdytu uzduoti (1 - duomenu irasymas ranka, 2 - generuoti tik pazymius, 3 - generuoti studentu vardus, pavardes ir pazymius, 4 - baigti darba): " << std::endl;
        cin >> m;

        if (m == 1)
        {
            while (true) {
                cout << "Iveskite studento varda ir pavarde, jei norite baigti ivedima, iveskite 0:\n";
                cin >> v;
                if (v == "0") break;
                cin >> p;

                if (scount == scap) didStud(s, scap);

                // inicializacija
                s[scount].var = new string(v);
                s[scount].pav = new string(p);
                s[scount].paz = nullptr;
                s[scount].pazkiek = 0;
                s[scount].pazcap = 0;
                s[scount].rez = nullptr;
                s[scount].rez2 = nullptr;

                cout << "Iveskite pazymius (paskutinis - egzaminas), baigti 0:\n";
                while (true) {
                    cin >> pz;
                    if (pz == 0) break;
                    pridBal(s[scount], pz);
                }

                scount++;
            }

            int n = scount;

            for (int i = 0; i < n; i++)
            {
                int k = s[i].pazkiek;
                s[i].rez = new double(0.0);
                if (k >= 2) { // tik tada skaičiuojam
                    double suma = 0;
                    for (int j = 0; j < k - 1; j++) suma += s[i].paz[j];
                    double vid = suma / (k - 1);
                    int egz = s[i].paz[k - 1];
                    *s[i].rez = 0.4 * vid + 0.6 * egz;
                }
            }

            for (int i = 0; i < n; i++) //rusiavimas medianai
            {
                for (int j = 0; j < s[i].pazkiek - 1; j++)
                {
                    for (int jj = 0; jj < s[i].pazkiek - 1; jj++) {
                        if (s[i].paz[j] < s[i].paz[jj]) std::swap(s[i].paz[j], s[i].paz[jj]);
                    }
                }
            }

            for (int i = 0; i < n; i++)
            {
                int k = s[i].pazkiek;
                s[i].rez2 = new double(0.0);
                if (k >= 2) {
                    int nd = k - 1;

                    double med;
                    if (nd % 2 == 1) med = s[i].paz[nd / 2];
                    else med = (s[i].paz[nd / 2 - 1] + s[i].paz[nd / 2]) / 2.0;

                    int egz = s[i].paz[k - 1];
                    *s[i].rez2 = 0.4 * med + 0.6 * egz;
                }
            }

            cout << "Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):" << std::endl;
            cin >> a;
            if (a == 0)
            {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < n; i++) {
                    cout << std::left << std::setw(15) << *s[i].pav << std::left << std::setw(15) << *s[i].var
                        << std::fixed << std::setprecision(2) << *s[i].rez << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            else {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < n; i++) {
                    cout << std::left << std::setw(15) << *s[i].pav << std::left << std::setw(15) << *s[i].var
                        << std::fixed << std::setprecision(2) << *s[i].rez2 << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
      atlaisvinti(s, scount, scap);
        }

        if (m == 3)
        {
            cout << "Vardai ir pavardes bus sugeneruoti automatiskai, iveskite, kiek norite, jog butu studentu: \n";
            int skiek;
            cin >> skiek;

            cout << "Programa sugeneruos pazymius (paskutinis - egzaminas), iveskite kiek pazymiu turi studentai: \n";
            int kiek;
            cin >> kiek;

            for (int t = 0; t < skiek; t++)
            {
                if (scount == scap) didStud(s, scap);

                v = vardai[rand() % vardN];
                if (v.back() == 's') {
                    do { p = pavardes[rand() % pavN]; } while (p.back() != 's');
                } else {
                    do { p = pavardes[rand() % pavN]; } while (p.back() == 's');
                }

                s[scount].var = new string(v);
                s[scount].pav = new string(p);
                s[scount].paz = nullptr;
                s[scount].pazkiek = 0;
                s[scount].pazcap = 0;
                s[scount].rez = nullptr;
                s[scount].rez2 = nullptr;

                for (int i = 0; i < kiek; i++) {
                    pz = rand() % 10 + 1;
                    pridBal(s[scount], pz);
                }

                scount++; // studentų skaičių didinam 1 kartą per studentą
            }

            int n = scount;

            for (int i = 0; i < n; i++)
            {
                int k = s[i].pazkiek;
                s[i].rez = new double(0.0);     
                   if (k >= 2) {
                    double suma = 0;
                    for (int j = 0; j < k - 1; j++) suma += s[i].paz[j];
                    double vid = suma / (k - 1);
                    int egz = s[i].paz[k - 1];
                    *s[i].rez = 0.4 * vid + 0.6 * egz;
                }
            }

            for (int i = 0; i < n; i++) //rusiavimas medianai
            {
                for (int j = 0; j < s[i].pazkiek - 1; j++)
                {
                    for (int jj = 0; jj < s[i].pazkiek - 1; jj++) {
                        if (s[i].paz[j] < s[i].paz[jj]) std::swap(s[i].paz[j], s[i].paz[jj]);
                    }
                }
            }

            for (int i = 0; i < n; i++)
            {
                int k = s[i].pazkiek;
                s[i].rez2 = new double(0.0);   
                if (k >= 2) {
                    int nd = k - 1;

                    double med;
                    if (nd % 2 == 1) med = s[i].paz[nd / 2];
                    else med = (s[i].paz[nd / 2 - 1] + s[i].paz[nd / 2]) / 2.0;

                    int egz = s[i].paz[k - 1];
                    *s[i].rez2 = 0.4 * med + 0.6 * egz;
                }
            }

            cout << "Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):" << std::endl;
            cin >> a;
            if (a == 0)
            {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < n; i++) {
                    cout << std::left << std::setw(15) << *s[i].pav << std::left << std::setw(15) << *s[i].var
                        << std::fixed << std::setprecision(2) << *s[i].rez << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            else {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < n; i++) {
                    cout << std::left << std::setw(15) << *s[i].pav << std::left << std::setw(15) << *s[i].var
                        << std::fixed << std::setprecision(2) << *s[i].rez2 << "\n";                 }
                cout << "-----------------------------------------------\n";
            }

            atlaisvinti(s, scount, scap); 
        }

        if (m == 2)
        {
            while (true) {
                cout << "Iveskite studento varda ir pavarde, jei norite baigti ivedima, iveskite 0:\n";
                cin >> v;
                if (v == "0") break; 
                cin >> p;

                if (scount == scap) didStud(s, scap);

                s[scount].var = new string(v);
                s[scount].pav = new string(p);
                s[scount].paz = nullptr;
                s[scount].pazkiek = 0;
                s[scount].pazcap = 0;
                s[scount].rez = nullptr;
                s[scount].rez2 = nullptr;

                cout << "Programa sugeneruos pazymius (paskutinis - egzaminas), iveskite kiek pazymiu turi studentai: \n";
                int kiek;
                cin >> kiek;
                for (int i = 0; i < kiek; i++)
                {
                    pz = rand() % 10 + 1;
                    pridBal(s[scount], pz);
                }

                scount++;
            }

            int n = scount;

            for (int i = 0; i < n; i++)
            {
                int k = s[i].pazkiek;
                s[i].rez = new double(0.0);  
                if (k >= 2) {
                    double suma = 0;
                    for (int j = 0; j < k - 1; j++) suma += s[i].paz[j];
                    double vid = suma / (k - 1);
                    int egz = s[i].paz[k - 1];
                    *s[i].rez = 0.4 * vid + 0.6 * egz;
                }
            }

            for (int i = 0; i < n; i++) //rusiavimas medianai
            {
                for (int j = 0; j < s[i].pazkiek - 1; j++)
                {
                    for (int jj = 0; jj < s[i].pazkiek - 1; jj++) {
                        if (s[i].paz[j] < s[i].paz[jj]) std::swap(s[i].paz[j], s[i].paz[jj]);
                    }
                }
            }

            for (int i = 0; i < n; i++)
            {
                int k = s[i].pazkiek;
                s[i].rez2 = new double(0.0); 
                if (k >= 2) {
                    int nd = k - 1;

                    double med;
                    if (nd % 2 == 1) med = s[i].paz[nd / 2];
                    else med = (s[i].paz[nd / 2 - 1] + s[i].paz[nd / 2]) / 2.0;

                    int egz = s[i].paz[k - 1];
                    *s[i].rez2 = 0.4 * med + 0.6 * egz;
                }
            }

            cout << "Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):" << std::endl;
            cin >> a;
            if (a == 0)
            {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < n; i++) {
                    cout << std::left << std::setw(15) << *s[i].pav << std::left << std::setw(15) << *s[i].var
                        << std::fixed << std::setprecision(2) << *s[i].rez << "\n";
                }
                cout << "-----------------------------------------------\n";
            }
            else {
                cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
                cout << "-----------------------------------------------\n";
                for (int i = 0; i < n; i++) {
                    cout << std::left << std::setw(15) << *s[i].pav << std::left << std::setw(15) << *s[i].var
                        << std::fixed << std::setprecision(2) << *s[i].rez2 << "\n";
                }
                cout << "-----------------------------------------------\n";
            }

            atlaisvinti(s, scount, scap); 
        }

        if (m == 4) cout << "Baigiamas darbas.\n";
    }

    return 0;
}
