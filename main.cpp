#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

//darbas atliktas su dinamine atmintimi
using std::cin;
using std::string;
using std::cout;

struct studentas
{
   string *var, *pav;
   int *paz;
   //std::vector<int>paz; jei naudociau vector
   double* rez;
   double* rez2;
};

int main()
{
    int a;
    studentas A;
    studentas B;
    studentas C;

    A.paz=new int[4];
    B.paz=new int[4];
    C.paz=new int[4];

    A.var=new string;
    A.pav=new string;

    B.var=new string;
    B.pav=new string;

    C.var=new string;
    C.pav=new string;

    A.rez=new double;
    B.rez=new double;
    C.rez=new double;

    A.rez2=new double[4];
    B.rez2=new double[4];
    C.rez2=new double[4];

    *A.rez=0;
    *B.rez=0;
    *C.rez=0;

    *A.rez2=0;
    *B.rez2=0;
    *C.rez2=0;
    
    cout<<"Iveskite studentu vardus ir pavardes bei 4 gautus pazymius (pirmi 3 n.d, 4-tas egzaminas):"<<std::endl;
    cin>>*A.var>>*A.pav;
    for(int i=0; i<4; i++)
    {
      
        cin>>A.paz[i];
        A.rez2[i]=A.paz[i];
        if(i!=3) *A.rez+=A.paz[i];
        if(i==2) 
        {
            *A.rez=0.4*((*A.rez)/3);
            for(int j=0; j<3; j++)
            {
                for(int ii=0; ii<3; ii++)
                {
                    if(A.rez2[j]<A.rez2[ii]) std::swap(A.rez2[j], A.rez2[ii]);
                }
            }
        }
        if(i==3) *A.rez+=0.6*A.paz[i];
    }
   
    cin>>*B.var>>*B.pav;
    for(int i=0; i<4; i++)
    {
        
        cin>>B.paz[i];
        B.rez2[i]=B.paz[i];
        if(i!=3) *B.rez+=B.paz[i];
        if(i==2) 
        {
            *B.rez=0.4*((*B.rez)/3);
            for(int j=0; j<3; j++)
            {
                for(int ii=0; ii<3; ii++)
                {
                    if(B.rez2[j]<B.rez2[ii]) std::swap(B.rez2[j], B.rez2[ii]);
                }
            }
        }
        if(i==3) *C.rez+=0.6*C.paz[i];
    }

    cin>>*C.var>>*C.pav;
    for(int i=0; i<4; i++)
    {
        cin>>C.paz[i];
        C.rez2[i]=C.paz[i];
        if(i!=3) *C.rez+=C.paz[i];
        if(i==2) 
        {
            *C.rez=0.4*((*C.rez)/3);
            for(int j=0; j<3; j++)
            {
                for(int ii=0; ii<3; ii++)
                {
                    if(C.rez2[j]<C.rez2[ii]) std::swap(C.rez2[j], C.rez2[ii]);
                }
            }
        }
        if(i==3) *C.rez+=0.6*C.paz[i];
    }
   cout<<"Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):"<<std::endl;
   cin>>a;
   if(a==0)
   {
   cout<<std::left<<std::setw(15)<<"Pavarde"<<std::left<<std::setw(15)<<"Vardas"<< std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
   cout<<"-----------------------------------------------\n";
   cout<<std::left<<std::setw(15)<<*A.pav<<std::left<<std::setw(15)<<*A.var<<std::fixed<<std::setprecision(2)<<*A.rez<<"\n";
   cout<<std::left<<std::setw(15)<<*B.pav<<std::left<<std::setw(15)<<*B.var<<std::fixed<<std::setprecision(2)<<*B.rez<<"\n";
   cout<<std::left<<std::setw(15)<<*B.pav<<std::left<<std::setw(15)<<*C.var<<std::fixed<<std::setprecision(2)<<*C.rez<<"\n";
   cout<<"-----------------------------------------------\n";
   }
   else {
   cout<<std::left<<std::setw(15)<<"Pavarde"<<std::left<<std::setw(15)<<"Vardas"<< std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
   cout<<"-----------------------------------------------\n";
   cout<<std::left<<std::setw(15)<<*A.pav<<std::left<<std::setw(15)<<*A.var<<std::fixed<<std::setprecision(2)<<A.rez2[1]*0.4+A.rez2[3]*0.6<<"\n";
   cout<<std::left<<std::setw(15)<<*B.pav<<std::left<<std::setw(15)<<*B.var<<std::fixed<<std::setprecision(2)<<B.rez2[1]*0.4+B.rez2[3]*0.6<<"\n";
   cout<<std::left<<std::setw(15)<<*B.pav<<std::left<<std::setw(15)<<*C.var<<std::fixed<<std::setprecision(2)<<C.rez2[1]*0.4+C.rez2[3]*0.6<<"\n";
   cout<<"-----------------------------------------------\n";
   }
   
    delete[] A.paz;
    delete[] B.paz;
    delete[] C.paz;
    delete A.var;
    delete A.pav;
    delete B.var;
    delete B.pav;
    delete C.var;
    delete C.pav;
    delete A.rez;
    delete B.rez;
    delete C.rez;
    delete[] A.rez2;
    delete[] B.rez2;
    delete[] C.rez2;
    return 0;
}