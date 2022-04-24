#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <cstring>
#include <conio.h>
#include <limits>
#include <windows.h>

using namespace std;






class abonament_simplu
{

private:
    string nume_abonament;
    float pret;
    int perioada;

public:

    abonament_simplu(string nume_abonament, float pret, int perioada)
    {
        this->nume_abonament=nume_abonament;
        this->perioada= perioada;
        this->pret= pret;
    }

    abonament_simplu()
    {
        nume_abonament=" ";
        perioada=0;
        pret=0.0;
    }

    virtual ~abonament_simplu(){}


    abonament_simplu& operator= (const abonament_simplu &ab);

    abonament_simplu(const abonament_simplu &ab);

    friend ostream& operator<< (ostream& out, abonament_simplu& ob);
    friend istream& operator>> (istream& in, abonament_simplu& ob);


    /// -- settere

    void setter_nume_abonament(string nume)
    {
        nume_abonament=nume;
    }

    void setter_perioada(int perioada)
    {
        this->perioada= perioada;
    }

    void setter_pret ( float pret)
    {
        this->pret = pret;
    }

    virtual char* getter_tip()= 0;


    /// --- gettere

    string getter_nume_abonament()
    {
        return nume_abonament;
    }

    float getter_pret()
    {
        return pret;
    }

    int getter_perioada()
    {
        return perioada;
    }


    virtual void citire(istream &in)
    {

    cout<<endl;
    cout<<"Specificati numele abonamentului pe care doriti sa-l introduceti!"<<endl;

    char aux[200];
    in.getline(aux, 200, '\n');
    nume_abonament=aux;


    cout<<endl;
    cout<<"Specificati pretul ales pentru acest abonament!" <<endl;
    //in>>pret;
    int ok=1;

    do      ///try-catch pentru pret
        {

            try
            {
                in>>pret;

                if (in.fail())
                    throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti un numarul real!"<<endl;


                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);

    cout<<endl;
    cout<<"Specificati perioada minima impusa acestui abonament! ( in luni )"<<endl;
    //in>>perioada;

    do      ///try-catch pentru perioada
        {

            try
            {
                in>>perioada;

                if (in.fail())
                    throw 1;

                if (perioada==0)
                    throw 2;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti un numarul natural!"<<endl;

                if (x==2)
                    cout<<"Perioada nu poate fi nula!"<<endl;

                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

    cout<<endl;
    }

    virtual void afisare(ostream &out)
    {

    out<<"Tipul abonamentului: "<<getter_tip()<<endl;
    out<<"Numele abonamentului este: "<<nume_abonament<<endl;
   // out<<endl;
    out<<"Pretul acestui acestui abonament este: "<<pret<<" lei"<<endl;
    if (perioada!=1)
        out<<"Perioada minima pe care trebuie contractat acest document este de "<<perioada<<" luni"<<endl;
    else
        out<<"Perioada minima pe care trebuie contractat acest document este de o luna(1)"<<endl;



    }


};


abonament_simplu& abonament_simplu::operator=(const abonament_simplu& ab)
{
    if(this!=&ab){

            this->nume_abonament=ab.nume_abonament;
            this->perioada=ab.perioada;
            this->pret=ab.pret;
        }

        return *this;
}


abonament_simplu::abonament_simplu(const abonament_simplu &ab )
{
    this->nume_abonament=ab.nume_abonament;
    this->perioada=ab.perioada;
    this->pret=ab.pret;
}


istream& operator>> (istream& in, abonament_simplu& ob)
{
   ob.citire(in);
    return in;
}

ostream& operator<< (ostream& out, abonament_simplu& ob)
{
    ob.afisare(out);
    return out;
}



/// clasa normala


class abonament_normal: public abonament_simplu
{
    static int numarnormale;

public:
    abonament_normal():abonament_simplu(){}

    ~abonament_normal(){}


    abonament_normal& operator= (const abonament_normal &ab);

    abonament_normal(const abonament_normal &ab);


    static int getter_numarnormale()
    {
        return numarnormale;
    }

    static void crestere()
    {
        numarnormale++;
    }

    static void scadere()
    {
        numarnormale--;
    }

    char* getter_tip()
    {
        return "Abonament normal";
    }

     void citire(istream &in)
     {

        abonament_simplu::citire(in);

     }

     void afisare(ostream& out)
     {
         abonament_simplu::afisare(out);
     }


};

abonament_normal& abonament_normal:: operator= (const abonament_normal &ab)
{
   if (this!=&ab)
    {
    abonament_simplu &b = *this;
    const abonament_simplu  &ob = ab;

    b=ob;
    }

    return *this;
}

abonament_normal:: abonament_normal(const abonament_normal &ab)
{
    abonament_simplu &b = *this;
    const abonament_simplu  &ob = ab;

    b=ob;
}




/// clasa premium


class abonament_premium : public abonament_simplu
{

private:
    int reducere;
    static int numarpremium;

public:

    abonament_premium(int i=0):abonament_simplu()
    {
        reducere=i;
    }


    ~abonament_premium(){}

    static int getter_nrpremium()
    {
        return numarpremium;
    }

    static void crestere()
    {
        numarpremium++;
    }

    static void scadere()
    {
        numarpremium--;
    }

    abonament_premium& operator= (const abonament_premium &ab);

    abonament_premium(const abonament_premium &ab);

   // friend ostream& operator<< (ostream& out, abonament_premium& ob);
  //  friend istream& operator>> (istream& in, abonament_premium& ob);


    /// -- setter

    void setter_reducere(int reducere)
    {
        this->reducere=reducere;
    }

    /// -- getter

    int getter_reducere()
    {
        return reducere;
    }

    char* getter_tip()
    {
        return "Abonament premium";
    }


    void citire(istream &in)
    {
/*
    abonament_simplu *b; //= new abonament_simplu();

    b= dynamic_cast <abonament_simplu*> (this);

    in>>*b;
    cout<<endl;
*/

    abonament_simplu::citire(in);

    cout<<"Introduceti reducerea aplicata la acest abonament( daca nu exista, tastati 0)!"<<endl;
    //in>>reducere;
    int ok=1;

    do      ///try-catch pentru reducere
        {

            try
            {
                in>>reducere;

                if (in.fail())
                    throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti un numarul natural!"<<endl;


                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);

    }

    void afisare(ostream& out)
    {
/*
    abonament_simplu &b = *this;
    out<<b;
*/
    abonament_simplu::afisare(out);
    out<<"Reducerea aplicata acestui abonament este de "<<reducere<<" lei"<<endl;
    out<<endl;
    }

};

abonament_premium::abonament_premium(const abonament_premium &ab)
{

    abonament_simplu &b = *this;
    const abonament_simplu  &ob = ab;

    b=ob;

    this->reducere=ab.reducere;
}


abonament_premium& abonament_premium:: operator= (const abonament_premium &ab)
{
    if(this!=&ab){

            abonament_simplu &b = *this;
            const abonament_simplu  &ob = ab;

            b=ob;

            this->reducere=ab.reducere;

        }

        return *this;
}


istream& operator>> (istream& in, abonament_premium& ob)
{

    ob.citire(in);

    return in;
}

ostream& operator<< (ostream& out, abonament_premium& ob)
{
   ob.afisare(out);

    return out;
}






class persoana
{
    string nume;
    string cnp;
    string data_nastere;

public:

    persoana()
    {
        nume=" ";
        cnp=" ";
        data_nastere=" ";
    }


    persoana(string nume)
    {
        this->nume=nume;
        cnp=" ";
        data_nastere=" ";
    }


    virtual  ~persoana(){}


    persoana& operator= (const persoana &ab);

    persoana(const persoana &ab);


    virtual void citire(istream &in)
    {

    cout<<"Introduceti urmatoarele date despre persoana pe care doriti sa o adaugati!"<<endl;
    cout<<endl;
    cout<<endl;

    int ok=1;

    cout<<"Introduceti numele si prenumele: "<<endl;
    char aux[200];
   // in.getline(aux, 200, '\n');

    do      ///try-catch pentru nume sau prenume
        {

            try
            {
                in.getline(aux, 200, '\n');

                int ok2=0;
                string str="0123456789";
                for (int i=0;i<strlen(aux) and ok2==0;i++)
                    {
                    string str1(1, aux[i]);
                    if (str.find(str1) != string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;



                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x== 4)
                    cout<<"Numele sau prenumele nu trebuie sa contina cifre.\nIntroduceti din nou valoarea.\n";

                in.clear();
               // in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);

    nume=aux;

    cout<<endl;
    cout<<"Introduceti CNP-ul: " <<endl;
    //in>>cnp;

    do      ///try-catch pentru CNP
        {

            try
            {
                in>>cnp;

                int ok2=0;
                string str="0123456789";
                for (int i=0;i<cnp.length() and ok2==0;i++)
                    {
                    string str1(1, cnp[i]);
                    if (str.find(str1) == string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;
                if (cnp[0] =='0')
                    throw 2;
                if (cnp.length() !=13)
                     throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;
                if(x == 1)
                    cout<<"CNP-ul trebuie sa aiba 13 cifre.\nIntroduceti din nou valoarea.\n";
                if(x == 2)
                    cout<<"Prima cifra din numarul de telefon NU trebuie sa fie 0.\nIntroduceti din nou valoarea.\n";

                if (x== 4)
                    cout<<"CNP-ul trebuie sa contina doar cifre.\nIntroduceti din nou valoarea.\n";

                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);




    cout<<endl;
    cout<<"Introduceti data nasterii:"<<endl;
    //in>>data_nastere;

     do      ///try-catch pentru data
        {

            try
            {
                in>>data_nastere;

                int ok2=0;
                string str="0123456789.";
                for (int i=0;i<data_nastere.length() and ok2==0;i++)
                    {
                    string str1(1, data_nastere[i]);
                    if (str.find(str1) == string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;

                if (data_nastere.length() !=10)
                     throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;
                if(x == 1)
                    cout<<"Format gresit al datei! ( Format: dd.mm.yyyy ).\nIntroduceti din nou data!\n";

                if (x==4)
                    cout<<"Data introdusa gresit! Va rugam folositi doar cifre si simbolul '.' \nIntroduceti din nou data!\n";

                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);


    cout<<endl;

    }

    virtual void afisare(ostream &out)
    {

        out<<"Numele si prenumele este: "<<nume<<endl;

        out<<"CNP-ul este: "<<cnp<<endl;

        out<<"Data nasterii este: "<<data_nastere<<endl;
    }


    virtual char* afisare_tip()= 0;     /// virtual pur

    /// settere

    void setter_nume(string nume)
    {
        this->nume=nume;
    }

    void setter_cnp(string cnp)
    {
        this->cnp=cnp;
    }

    void setter_data_nastere (string data_nastere)
    {
        this->data_nastere=data_nastere;
    }

    /// gettere


    string getter_nume()
    {
        return nume;
    }

    string getter_cnp()
    {
        return cnp;
    }

    string getter_data_nastere()
    {
        return data_nastere;
    }




};



persoana& persoana:: operator= (const persoana &ab)
{
    if (this!=&ab)
    {
        this->cnp=ab.cnp;
        this->data_nastere=ab.data_nastere;
        this->nume=ab.nume;
    }

    return *this;
}


persoana::persoana(const persoana &ab)
{
        this->cnp=ab.cnp;
        this->data_nastere=ab.data_nastere;
        this->nume=ab.nume;
}


istream& operator>> (istream& in, persoana& ob)
{
   ob.citire(in);
   return in;
}


ostream& operator<< (ostream& out, persoana& ob)
{

    ob.afisare(out);
    return out;
}






class angajat: public persoana
{
    string cod_angajat;
    float salariu;

    static int numar;

public:

    angajat(string cod="Codul nu este setat!"):persoana()
    {
        cod_angajat=cod;
        salariu=0;
        numar++;
    }

    ~angajat(){}

    angajat& operator= (const angajat &);

    angajat(const angajat &);

    /// ostream& operator<< (ostream& out, angajat& ob);
    /// istream& operator>> (istream& in, angajat& ob);

    void citire(istream &in)
    {
        persoana::citire(in);
        int ok=1;
        cout<<"Introduceti codul angajatului: "<<endl;
        in>>cod_angajat;
        cout<<endl;
        cout<<"Introduceti salariul acestuia: "<<endl;

        do      ///try-catch pentru salariu
        {

            try
            {
                in>>salariu;

                if (in.fail())
                    throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti un numarul real!"<<endl;


                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);
    }


    void afisare(ostream &out)
    {
        persoana::afisare(out);
        out<<endl;
        out<<"Codul angajatului este: "<<cod_angajat<<endl;
        out<<"Salariul lui este de: "<<salariu<<" lei"<<endl;
    }

    char* afisare_tip()
    {
        return "Angajat";
    }

    string getter_cod_angajat()
    {
        return cod_angajat;
    }

    float getter_salariu()
    {
        return salariu;
    }
   static int getter_numarnr()
    {
        return numar;
    }

    void setter_salariu(float sal)
    {
        salariu=sal;
    }

    void setter_cod_anganjat(string cod)
    {
        cod_angajat=cod;
    }

};


angajat& angajat::operator= (const angajat &ab)
{
    if (this!=&ab)
            {
            persoana &b = *this;
            const persoana  &ob = ab;
            b=ob;
            this->cod_angajat =ab.cod_angajat;
            this->salariu= ab.salariu;
            numar=ab.numar;
            }

    return *this;
}

angajat::angajat(const angajat &ab)
{
    persoana &b = *this;
    const  persoana  &ob = ab;
    b=ob;
    this->cod_angajat =ab.cod_angajat;
    this->salariu= ab.salariu;
    numar=ab.numar;
}



class contract
{
    int numar;
    string data;

public:
    contract(int i=0, string date="1.01.1900")
    {
        numar=i;
        data=date;
    }

    ~contract(){}


    contract& operator= (const contract &ab);

    contract(const contract &ab);


    /// settere

    void setter_numar(int nr)
    {
        numar=nr;
    }

    void setter_data(string date)
    {
        data=date;
    }


    /// gettere

    int getter_numar()
    {
        return numar;
    }


    string getter_data()
    {
        return data;
    }



};

contract& contract::operator= (const contract &ab)
{
    if (this!=&ab)
    {
        this->numar=ab.numar;
        this->data=ab.data;
    }
    return *this;
}

contract::contract(const contract &ab)
{
    this->numar=ab.numar;
    this->data=ab.data;
}

int abonament_normal::numarnormale;
int abonament_premium::numarpremium;

class abonat: public persoana
{

    string nr_telefon;
    unique_ptr<contract> ins;    /// pot folosi unique pointer la clasa asta, adica aici cand declar
    abonament_simplu* abon;            /// abonatul are abonament
    static int numarabonati;

public:

    abonat(string nrtel="0000000000"): persoana()
    {
        nr_telefon=nrtel;
        ins.reset( new contract() );
        abon= NULL;
        numarabonati++;
    }

    abonat& operator= ( const abonat& ab);

    abonat( const abonat& ab);

    ~abonat(){ delete abon; }


    void schimbare(string optiune="1" )
    {
        if (optiune=="1")  /// din premium in normal
        {
            abonament_normal::crestere();
            abonament_premium::scadere();

            abon = dynamic_cast <abonament_normal*> (new abonament_normal);

            if (abon!=nullptr)
                {
                    //cin.get();
                    cin>>*abon;
                    system("cls");

                   // cout<<*abon;
                }



          //  cout<<endl;

        }

        else
            if (optiune=="2")   /// din normal in premium
                {

                abonament_normal::scadere();
                abonament_premium::crestere();

            abon = dynamic_cast <abonament_premium*> (new abonament_premium);

            if (abon!=nullptr)
                {
                    //cin.get();
                    cin>>*abon;
                    system("cls");

                   // cout<<*abon;
                }

                }

    }



    void citire(istream &in)
    {
        persoana::citire(in);
        cout<<"Introduceti numarul de telefon: "<<endl;

        int ok=1;

        do      ///try-catch pentru numarul de telefon
        {

            try
            {
                in>>nr_telefon;

                int ok2=0;
                string str="0123456789";
                for (int i=0;i<nr_telefon.length() and ok2==0;i++)
                    {
                    string str1(1, nr_telefon[i]);
                    if (str.find(str1) == string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;

                if (nr_telefon.length() !=10)
                     throw 1;

                if (nr_telefon[0] !='0')
                    throw 2;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;
                if(x == 1)
                    cout<<"Numarul de telefon trebuie sa aiba 10 cifre.\nIntroduceti din nou valoarea.\n";
                if(x == 2)
                    cout<<"Prima cifra din numarul de telefon trebuie sa fie 0.\nIntroduceti din nou valoarea.\n";

                if (x== 4)
                    cout<<"Numarul de telefon trebuie sa contina doar cifre.\nIntroduceti din nou valoarea.\n";

                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);



        cout<<endl;

        cout<<"Introduceti urmatoarele date despre abonamentul pe care doriti sa il atribuiti clientului: "<<endl;
        cout<<endl;

        cout<<"Clientul are abonament premium?( apasati tasta enter daca DA, respectiv scrieti 'nu' "<<endl;
        string s;

        in.get();
        getline(in,s);



        if (s=="nu")
            {
            abonament_normal::crestere();

            abon = dynamic_cast <abonament_normal*> (new abonament_normal);

            if (abon!=nullptr)
                {
                in>>*abon;
                //delete abona;
                }
            else
            {
                cout<<"nu merge pe simplu"<<endl;
            }

            }
        else
        {
            abonament_premium::crestere();

            abon = dynamic_cast <abonament_premium*> (new abonament_premium);

          //  cout<<"MERG PE PREMIUM"<<endl;
            if (abon!=nullptr)
                {
               // in.get();
                in>>*abon;
                //system("cls");
             //   cout<<typeid(*abon).name();

                }
            else
            {
                cout<<"nu merge pe premium"<<endl;
            }
        }


        cout<<endl;

        cout<<endl;
        cout<<"Introduceti urmatoarele detalii despre contract:"<<endl;
        cout<<endl;
        cout<<endl;


        ///  aici sunt cin-urile la contract



        cout<<"Numarul contractului: "<<endl;
        int auxiliar;

        do      ///try-catch pentru numarul de contract
        {

            try
            {
                in>>auxiliar;

                if (in.fail())
                    throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti un numarul natural!"<<endl;


                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        ins->setter_numar(auxiliar);
        cout<<endl;


        cout<<"Data la care s-a semnat contractul: ";
        string aux;

        do      ///try-catch pentru data
        {

            try
            {
                in>>aux;

                int ok2=0;
                string str="0123456789.";
                for (int i=0;i<aux.length() and ok2==0;i++)
                    {
                    string str1(1, aux[i]);
                    if (str.find(str1) == string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;

                if (aux.length() !=10)
                     throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;
                if(x == 1)
                    cout<<"Format gresit al datei! ( Format: dd.mm.yyyy ).\nIntroduceti din nou data!\n";

                if (x==4)
                    cout<<"Data introdusa gresit! Va rugam folositi doar cifre si simbolul '.' \nIntroduceti din nou data!\n";

                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        ins->setter_data(aux);


    }


    void afisare(ostream &out)
    {
        persoana::afisare(out);
        cout<<"Numarul de telefon al abonatului este: "<<nr_telefon<<endl;
        cout<<endl;
        cout<<endl;

        cout<<"Datele referitoare la abonamentul clientului sunt urmatoarele: "<<endl;
        cout<<endl;
        cout<<*abon;

        cout<<endl;
        cout<<"Numarul contractului semnat de abonat este:  "<<ins->getter_numar()<<endl;
        cout<<"Data semnarii este:  "<<ins->getter_data()<<endl;

        cout<<endl;
        cout<<endl;

        cout<<"Contractul se identifica sub forma: "<<ins->getter_numar()<<"/"<<ins->getter_data()<<endl;


    }

    char* afisare_tip()
    {
        return "Abonat";
    }

    string getter_nr_telefon()
    {
        return nr_telefon;
    }

    unique_ptr<contract>& getter_contract()
    {
        return ins;
    }

    abonament_simplu* getter_abonament()
    {
        return abon;
    }

    static int getter_numar()
    {
        return numarabonati;
    }

    void setter_nrtelefon(string nrtel)
    {
        nr_telefon=nrtel;
    }


};


abonat& abonat:: operator= ( const abonat& ab)
{
    if (this!=&ab)
            {

            persoana &b = *this;
            const persoana  &ob = ab;
            b=ob;
            nr_telefon=ab.nr_telefon;

            if (typeid(*ab.abon)==typeid(abonament_normal))
                    abon = static_cast <abonament_normal*> (new abonament_normal);

            else
                if (typeid(*ab.abon)==typeid(abonament_premium))
                    abon = static_cast <abonament_premium*> (new abonament_premium);


    abon= ab.abon;
    ins.reset(new contract);
    numarabonati=ab.numarabonati;
  // using ins=move(ab.ins);
    }

    return *this;
}

abonat::abonat(const abonat& ab)
{
    persoana &b = *this;
    const  persoana  &ob = ab;
    b=ob;

    nr_telefon=ab.nr_telefon;

    if (typeid(*ab.abon)==typeid(abonament_normal))
            abon = new abonament_normal;

    else
            if (typeid(*ab.abon)==typeid(abonament_premium))
                    abon = new abonament_premium;


    ///cout<<typeid(*ab.abon).name()<<endl;
    abon= ab.abon;

    ins.reset(new contract);
    numarabonati=ab.numarabonati;
//    ins=move(ab.ins);
}



class companie
{
    string nume;
    string domeniu_de_activiate;
    static int nr;
    vector <persoana*> lista;  /// STL


public:
    companie(string numes="", string domeniu="")
    {
        nume=numes;
        domeniu_de_activiate=domeniu;
    }

    companie& operator= (const companie& ab);

    companie(const companie& ab);

    ~companie(){}


    friend  ostream& operator<< (ostream& out, companie& ob);
    friend  istream& operator>> (istream& in, companie& ob);

    static void setter_nr(int nrr)
    {
        nr=nrr;
    }

    static int getter_nr()
    {
        return nr;
    }

    vector <persoana*>& getter_vector()
    {
        return lista;
    }


    int cautare_abonat_verificare(string nume);

    persoana* cautare_abonat (string nume);


    int cautare_angajat_verificare(string nume);

    persoana* cautare_angajat (string nume);

};


    /// abonat functii in companie

int companie::cautare_abonat_verificare (string nume)
{
    for (int i=0;i<getter_vector().size();i++)
    {
        if (typeid(*getter_vector()[i])==typeid(abonat))
           {
            abonat *temp= dynamic_cast<abonat* >(getter_vector()[i]);
            if (temp->getter_nume()==nume)
                return 1;
           }
    }
    return 0;
}


persoana* companie::cautare_abonat (string nume)
{
    for (int i=0;i<getter_vector().size();i++)
    {
        abonat *temp= dynamic_cast<abonat* >(getter_vector()[i]);
        if (temp->getter_nume()==nume)
            return getter_vector()[i];
    }

}




/// angajat functii in companie

int companie::cautare_angajat_verificare (string nume)
{
    for (int i=0;i<getter_vector().size();i++)
    {
        if (typeid(*getter_vector()[i])==typeid(angajat))
        {
        angajat *temp= dynamic_cast< angajat* >(getter_vector()[i]);
        if (temp->getter_nume()==nume)
            return 1;
        }
    }
    return 0;
}


persoana* companie::cautare_angajat (string nume)
{
    for (int i=0;i<getter_vector().size();i++)
    {
        angajat *temp= dynamic_cast< angajat* >(getter_vector()[i]);
        if (temp->getter_nume()==nume)
            return getter_vector()[i];
    }

}






int companie::nr;
int abonat::numarabonati;
int angajat::numar;
void first_read();

companie::companie(const companie& ab)
{
    nume=ab.nume;
    domeniu_de_activiate=ab.domeniu_de_activiate;


    lista.clear();

    for (int i=0;i<ab.lista.size();i++)
        lista.push_back(ab.lista[i]);

    nr=ab.nr;
}

companie& companie:: operator= (const companie& ab)
{
    if (this!=&ab)
    {

    nume=ab.nume;
    domeniu_de_activiate=ab.domeniu_de_activiate;

    lista.clear();

    for (int i=0;i<ab.lista.size();i++)
        lista.push_back(ab.lista[i]);

    nr=ab.nr;
    }

    return *this;

}


istream& operator>> (istream& in, companie& ob)
{
    cout<<"------- Cititi urmatoarele date despre companie! --------"<<endl;
    cout<<endl;
    cout<<endl;

    cout<<"Numele companiei: "<<endl;
    in>>ob.nume;


    cout<<endl;
    cout<<endl;

    cout<<"Specificati domeniul de activitate al firmei: "<<endl;
    in>>ob.domeniu_de_activiate;


    cout<<endl;
    cout<<endl;
    cout<<endl;


    cout<<"------- Apasati enter pentru a trece la pasul urmator! --------"<<endl;

    cin.get();
    cin.ignore();
    system("cls");



    cout<<"------- In continuare veti completa date despre angajatii, respectiv clientii firmei dvs! --------"<<endl;
    cout<<endl;
    cout<<" ---- ATENTIE! ----- "<<endl;
    cout<<endl;

    cout<<"Pentru fiecare persoana, veti specifica ce reprezinta aceasta in cadrul firmei"<<endl;
    cout<<"( se va raspunde unei intrebari implicite, don't worry :) )"<<endl;

    cout<<endl;
    cout<<"Dupa ce ati terminat citirea, scrieti dupa ultima persoana adaugata expresia 'gata'"<<endl;


    cout<<endl;
    cout<<endl;

    cout<<"Dupa ce ati citit instructiunile, apasati tasta ENTER pentru a continua"<<endl;


    cin.get();
    //cin.ignore();
    system("cls");

    int ok=1;

    while(ok==1)
    {
        cout<<"Persoana pe care urmeaza sa o adaugati este un ANGAJAT?"<<endl;
        cout<<"Apasati ENTER in caz AFIRMATIV, respectiv scrieti 'nu' "<<endl;

        string s;
        getline(in,s);
        if (s=="nu")
        {
            system("cls");
            cout<<"Ati ales sa cititi un ABONAT!"<<endl;

            //abonat ob2;
           // in>>ob;

            companie::nr++;

            ob.lista.push_back(new abonat);
            in>>*ob.lista[ob.lista.size()-1];


            system("cls");
            cout<<"--- Sfarsitul citirii actuale, acum puteti oprii citirea cu totul sau puteti continua. ---"<<endl;
            cout<<" ------ Pentru a stopa citirea, scrieti 'gata'! ------ "<<endl;
            string stop;
            in.get();
            getline(in,stop);
            if  (stop=="gata")
                ok=0;
            system("cls");

        }
        else
        {
            system("cls");
            cout<<"Ati ales sa cititi un ANGAJAT!"<<endl;

            ob.lista.push_back(new angajat);
            in>>*ob.lista[ob.lista.size()-1];

            companie::nr++;

            system("cls");
            cout<<"--- Sfarsitul citirii actuale, acum puteti oprii citirea cu totul sau puteti continua. ---"<<endl;
            cout<<" ------ Pentru a stopa citirea, scrieri 'gata'! ------ "<<endl;
            string stop;
            in.get();
            getline(in,stop);
            if  (stop=="gata")
                ok=0;
            system("cls");

        }




    }


        cout<<" ----  S-a terminat citirea!  ----"<<endl;
        cout<<endl;
        cout<<"Apasati ENTER pentru a trece la urmatoarea etapa!"<<endl;
        cin.get();
        system("cls");


}

ostream& operator<< (ostream& out, companie& ob)
{

    out<<"Numele companiei inregistrata in program este: "<<ob.nume<<endl;
    out<<"Domeniul de activitate al acesteia este: "<<ob.domeniu_de_activiate<<endl;

    out<<endl;
    out<<endl;

    out<<"Pentru a putea afisa evidenta totala a persoanelor din companie ( clienti + angajati ) apasati tasta ENTER "<<endl;

    cin.get();
   // cin.ignore();
    system("cls");

    out<<endl;




    out<<endl;
    out<<endl;

    out<<"------ Atentie !  ------ "<<endl;
    out<<"Pentru fiecare persoana va aparea inaintea datelor sale STATUTUL sau. (angajat sau abonat)!"<<endl;

    out<<endl;
    out<<endl;
    out<<endl;

    cin.get();
    system("cls");



    for (int i=0;i<ob.lista.size();i++)
    {

        out<<ob.lista[i]->afisare_tip()<<endl;
        out<<"Nume si prenume: "<<ob.lista[i]->getter_nume() <<endl;
        out<<"CNP-ul este: "<<ob.lista[i]->getter_cnp()<<endl;
        out<<"Data de nastere este: "<<ob.lista[i]->getter_data_nastere()<<endl;


        if (typeid(*ob.lista[i]) == typeid(abonat))
        {

           abonat *temp= dynamic_cast<abonat* >(ob.lista[i]);

          // out<<*temp;
           out<<"Numarul sau de telefon este: "<<temp->getter_nr_telefon()<<endl;
           out<<endl;

           out<<"Detalii despre abonamentul clientului:"<<endl;
           out<<endl;

            out<<"- Tipul abonamentului: "<<temp->getter_abonament()->getter_tip()<<endl;

           out<<"- Numele abonamentului: "<<temp->getter_abonament()->getter_nume_abonament()<<endl;

           out<<"- Perioada pe care s-a contractat: "<<temp->getter_abonament()->getter_perioada()<<endl;
           out<<"- Pretul abonamentului: "<<temp->getter_abonament()->getter_pret()<<" lei"<<endl;

            abonament_premium *temp2 = dynamic_cast <abonament_premium*> ( temp->getter_abonament() );

            if (temp2!=nullptr)
                if (typeid(*temp2)== typeid(abonament_premium))
                    out<<"- Reducerea aplicata acestui abonament este de "<<temp2->getter_reducere()<<endl;


            out<<endl;
            out<<"Detalii despre contractul abonatului: "<<endl;
            out<<endl;
            out<<"- Numarul contractului: "<<temp->getter_contract()->getter_numar()<<endl;
            out<<"- Data la care s-a semnat contractul este: "<<temp->getter_contract()->getter_data()<<endl;


        }
        if (typeid(*ob.lista[i])== typeid(angajat))
        {

         out<<endl;
         angajat *temp= dynamic_cast<angajat* >(ob.lista[i]);

        //out<<*temp;
         out<<"Codul sau este: "<<temp->getter_cod_angajat()<<endl;
         out<<"Salariul sau este de: "<<temp->getter_salariu()<<" lei"<<endl;

        }

        out<<endl;
        out<<endl;
        out<<endl;
        out<<endl;
        out<<endl;

    }

    out<<endl;
    out<<endl;
    out<<endl;



}



companie companieprincipala;


void meniu()
{

  system("cls");
 cout<<endl;
 cout<<"1) Afisati intreaga companie"<<endl;
 cout<<"2) Afisati detaliile despre un anumit angajat sau un anumit abonat"<<endl;
 cout<<"3) Schimbati tipul abonamentului unui anumit abonat"<<endl;
 cout<<"4) Schimbati detaliile unui ABONAT"<<endl;
 cout<<"5) Schimbati detaliile unui ANGAJAT"<<endl;
 cout<<"6) Afisati numarul de abonati ai companiei, respectiv numarul de angajati"<<endl;
 cout<<"7) Afisati numarul de abonati premium, respectiv numarul de abonati normali din cadrul companiei"<<endl;
 cout<<"8) Afisati castigul companiei pe o perioada aleasa"<<endl;
 cout<<endl;
 cout<<"9) Iesiti din program"<<endl;
 cout<<"10) Cititi alta companie"<<endl;




    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Introduceti numarul optinuii pe care doriti sa o executati, DOAR NUMARUL, dupa care apasati tasta ENTER!"<<endl;
    int raspuns;

    int ok=1;
    do      ///try-catch pentru optiune
        {
            try
            {
                cin>>raspuns;

                if (cin.fail())
                    throw 1;

                if (raspuns>10 or raspuns<1)
                    throw 2;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti o optiune valida!"<<endl;


                if (x==2)
                    cout<<"Optiune gresita, reintroduceti optiunea!"<<endl;

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);



    system("cls");


    switch(raspuns)
    {


    case 1:
        {
            cout<<companieprincipala;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<"          ------  S-a afisat toata compania! ------"<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
           // cin.get();
            cin.ignore();
            system("cls");
            meniu();
        }


    case 2:
        {

        cout<<"Ce entitate doriti sa interogati?"<<endl;

        cout<<endl;
        cout<<endl;

        cout<<"1) Abonat"<<endl;
        cout<<"2) Angajat"<<endl;
        cout<<endl;
        cout<<"3) Intoarcere la meniul principal"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"Introduceti numarul optiunii alese!"<<endl;
        int raspuns2=0;
        int ok=1;

        do      ///try-catch pentru optiune submeniu
        {

            try
            {
                cin>>raspuns2;

                if (cin.fail())
                    throw 1;

                if (raspuns2<1 or raspuns2>3)
                    throw 2;


                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti o optiune valabila! (1, 2 sau 3)"<<endl;

                if (x==2)
                    cout<<"Va rugam introduceti o optiune valabila!"<<endl;

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        system("cls");


        if (raspuns2==1)  /// abonat
          {
            cout<<"Introduceti numele abonatului pe care doriti sa il cautati, EXACT cum a fost introdus la inceput"<<endl;
            cin.get();
            char aux[200];
            //cin.getline(aux, 200, '\n');
            //string nume=aux;
            cout<<endl;

            do      ///try-catch pentru nume abonat
        {

            try
            {

                cin.getline(aux, 200, '\n');
               string nume=aux;
                system("cls");

                if (nume=="back")
                    throw 100;

                if (companieprincipala.cautare_abonat_verificare(nume)==0)
                    throw 10;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==100)
                    meniu();

                if (x==10)
                    {
                    cout<<"Abonatul "<<aux<<" nu exista in companie. Reintroduceti numele abonatului dorit! "<<endl;
                    cout<<"Daca doriti sa va intoarceti la meniul principal, tastati 'back'"<<endl;
                    cout<<endl;
                    }

                cin.clear();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        string nume=aux;

        system("cls");

      //  companieprincipala.cautare_abonat_verificare(nume)
        cout<<*companieprincipala.cautare_abonat(nume);

        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
        //cin.get();
        cin.ignore();
        system("cls");
        meniu();

          }  /// sfarsit if abonat



        if (raspuns2==2)
        {

             cout<<"Introduceti numele angajatului pe care doriti sa il cautati, EXACT cum a fost introdus la inceput"<<endl;
            cin.get();
            char aux[200];
            //cin.getline(aux, 200, '\n');
            //string nume=aux;
            cout<<endl;

            do      ///try-catch pentru nume abonat
        {

            try
            {

                cin.getline(aux, 200, '\n');
               string nume=aux;
                system("cls");

                if (nume=="back")
                    throw 100;

                if (companieprincipala.cautare_angajat_verificare(nume)==0)
                    throw 10;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==100)
                    meniu();

                if (x==10)
                    {
                    cout<<"Angajatul "<<aux<<" nu exista in companie. Reintroduceti numele angajatului dorit! "<<endl;
                    cout<<"Daca doriti sa va intoarceti la meniul principal, tastati 'back'"<<endl;
                    cout<<endl;
                    }

                cin.clear();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        string nume=aux;

        system("cls");

      //  companieprincipala.cautare_abonat_verificare(nume)
        cout<<*companieprincipala.cautare_angajat(nume);

        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
        //cin.get();
        cin.ignore();
        system("cls");
        meniu();



        }  /// sfarsit if angajat


        if (raspuns2==3)
        {
            meniu();
        }


        } /// sfarsit case 2 mare





    case 3:
        {

            cout<<"Introduceti numele abonatului pe care doriti sa il cautati, EXACT cum a fost introdus la inceput"<<endl;
            cin.get();
            char aux[200];
            //cin.getline(aux, 200, '\n');
            //string nume=aux;
            cout<<endl;

            do      ///try-catch pentru nume abonat
        {

            try
            {

                cin.getline(aux, 200, '\n');
               string nume=aux;
                system("cls");

                if (nume=="back")
                    throw 100;

                if (companieprincipala.cautare_abonat_verificare(nume)==0)
                    throw 10;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==100)
                    meniu();

                if (x==10)
                    {
                    cout<<"Abonatul "<<aux<<" nu exista in companie. Reintroduceti numele abonatului dorit! "<<endl;
                    cout<<"Daca doriti sa va intoarceti la meniul principal, tastati 'back'"<<endl;
                    cout<<endl;
                    }

                cin.clear();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        string nume=aux;

        system("cls");


       // cout<<*companieprincipala.cautare_angajat(nume);

        abonat *temp= dynamic_cast<abonat* >(companieprincipala.cautare_abonat(nume));

        if (typeid( *temp->getter_abonament() ) == typeid(abonament_normal) )
            {
                cout<<"----- Abonatul "<<nume<<" poseda momentan, un Abonament Normal! Urmeaza sa il schimbati in Abonament Premium! ----- "<<endl;
                temp->schimbare("2");
            }
        else
            if (typeid(*temp->getter_abonament())==typeid(abonament_premium) )
                {
                    cout<<"Abonatul "<<nume<<" poseda momentan, un Abonament Premium! Urmeaza sa il schimbati in Abonament Normal!"<<endl;
                    temp->schimbare();
                   // cout<<typeid(*a.getter_abonament()).name()<<endl;
                }




        cout<<endl;
        cout<<endl;
        cout<<"-------Schimbarea s-a efectual cu succes!--------"<<endl;
        cout<<endl;
        cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
        cin.get();
        cin.ignore();
        system("cls");
        meniu();


        }  /// sfarsit case 3





    case 4:
        {

            cout<<"Introduceti numele abonatului pe care doriti sa il cautati, EXACT cum a fost introdus la inceput"<<endl;
            cin.get();
            char aux[200];
            //cin.getline(aux, 200, '\n');
            //string nume=aux;
            cout<<endl;

            do      ///try-catch pentru nume abonat
        {

            try
            {

                cin.getline(aux, 200, '\n');
               string nume10=aux;
                system("cls");

                if (nume10=="back")
                    throw 100;

                if (companieprincipala.cautare_abonat_verificare(nume10)==0)
                    throw 10;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==100)
                    meniu();

                if (x==10)
                    {
                    cout<<"Abonatul "<<aux<<" nu exista in companie. Reintroduceti numele abonatului dorit! "<<endl;
                    cout<<"Daca doriti sa va intoarceti la meniul principal, tastati 'back'"<<endl;
                    cout<<endl;
                    }

                cin.clear();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        string nume7=aux;

        system("cls");


        cout<<"Ce doriti sa schimbati la datele abonatului "<<nume7<<" ?"<<endl;
        cout<<endl;

        cout<<"1) Numarul de telefon"<<endl;
        cout<<"2) Numele si prenumele ( in caz de casatorire / schimbare de nume )"<<endl;
        cout<<endl;
        cout<<endl;

        cout<<"3) Intoarcere la meniul principal"<<endl;

        cout<<endl;
        cout<<endl;
        cout<<"Alegeti o optiune!"<<endl;

        int raspuns3=0;
        int ok=1;

        do      ///try-catch pentru optiune submeniu
        {

            try
            {
                cin>>raspuns3;

                if (cin.fail())
                    throw 1;

                if (raspuns3<1 or raspuns3>3)
                    throw 2;


                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti o optiune valabila! (1, 2 sau 3)"<<endl;

                if (x==2)
                    cout<<"Va rugam introduceti o optiune valabila!"<<endl;

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        system("cls");



        if (raspuns3==2)
        {
            cin.get();
            char aux1[200];
            cout<<"Introduceti noul nume si prenume al abonatului!"<<endl;
            int ok=1;

            do      ///try-catch pentru nume nou
        {

            try
            {

                cin.getline(aux1, 200, '\n');
                string nume=aux;
                system("cls");

                int ok2=0;
                string str="0123456789";
                for (int i=0;i<strlen(aux1) and ok2==0;i++)
                    {
                    string str1(1, aux1[i]);
                    if (str.find(str1) != string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x== 4)
                    cout<<"Numele sau prenumele nu trebuie sa contina cifre.\nIntroduceti din nou valoarea.\n";

                cin.clear();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        string nume3=aux1;



        companieprincipala.cautare_abonat(nume7)->setter_nume(nume3);


        //temp->setter_nume(nume);


            system("cls");

            cout<<"------  Operatie efectuata cu succes! ------"<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            //cin.get();
            cin.ignore();
            system("cls");
            meniu();


        } /// if raspuns3 = 2


        if (raspuns3==1)
        {

            cout<<"Introduceti noul numar de telefon al abonatului!"<<endl;
            int ok=1;
            string nr_telefon;
            do      ///try-catch pentru numarul de telefon
        {

            try
            {
                cin>>nr_telefon;

                int ok2=0;
                string str="0123456789";
                for (int i=0;i<nr_telefon.length() and ok2==0;i++)
                    {
                    string str1(1, nr_telefon[i]);
                    if (str.find(str1) == string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;

                if (nr_telefon.length() !=10)
                     throw 1;

                if (nr_telefon[0] !='0')
                    throw 2;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;
                if(x == 1)
                    cout<<"Numarul de telefon trebuie sa aiba 10 cifre.\nIntroduceti din nou valoarea.\n";
                if(x == 2)
                    cout<<"Prima cifra din numarul de telefon trebuie sa fie 0.\nIntroduceti din nou valoarea.\n";

                if (x== 4)
                    cout<<"Numarul de telefon trebuie sa contina doar cifre.\nIntroduceti din nou valoarea.\n";

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
    while(ok == 0);

            abonat *temp= dynamic_cast<abonat* >(companieprincipala.cautare_abonat(nume7));
            temp->setter_nrtelefon(nr_telefon);

            system("cls");
            cout<<"------  Operatie efectuata cu succes! ------"<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            cin.get();
            cin.ignore();
            system("cls");
            meniu();


        }   /// if raspuns3 = 1


    if (raspuns3==3)
        meniu();



        } /// sfarsit case 4






    case 5:
        {


            cout<<"Introduceti numele angajatului pe care doriti sa il cautati, EXACT cum a fost introdus la inceput"<<endl;
            cin.get();
            char aux[200];
            //cin.getline(aux, 200, '\n');
            //string nume=aux;
            cout<<endl;

            do      ///try-catch pentru nume abonat
        {

            try
            {

                cin.getline(aux, 200, '\n');
               string nume=aux;
                system("cls");

                if (nume=="back")
                    throw 100;

                if (companieprincipala.cautare_angajat_verificare(nume)==0)
                    throw 10;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==100)
                    meniu();

                if (x==10)
                    {
                    cout<<"Angajatul "<<aux<<" nu exista in companie. Reintroduceti numele abonatului dorit! "<<endl;
                    cout<<"Daca doriti sa va intoarceti la meniul principal, tastati 'back'"<<endl;
                    cout<<endl;
                    }

                cin.clear();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        string nume8=aux;

        system("cls");


        cout<<"Ce doriti sa schimbati la datele angajatului "<<nume8<<" ?"<<endl;
        cout<<endl;

        cout<<"1) Codul angajatului"<<endl;
        cout<<"2) Numele si prenumele ( in caz de casatorire / schimbare de nume )"<<endl;
        cout<<"3) Salariul angajatului"<<endl;
        cout<<endl;
        cout<<endl;

        cout<<"4) Intoarcere la meniul principal"<<endl;

        cout<<endl;
        cout<<endl;
        cout<<"Alegeti o optiune!"<<endl;

        int raspuns3=0;
        int ok=1;

        do      ///try-catch pentru optiune submeniu
        {

            try
            {
                cin>>raspuns3;

                if (cin.fail())
                    throw 1;

                if (raspuns3<1 or raspuns3>4)
                    throw 2;


                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti o optiune valabila! (1, 2, 3 sau 4)"<<endl;

                if (x==2)
                    cout<<"Va rugam introduceti o optiune valabila!"<<endl;

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        system("cls");



        if (raspuns3==2)
        {
            cin.get();
            char aux1[200];
            cout<<"Introduceti noul nume si prenume al angajatului!"<<endl;
            int ok=1;

            do      ///try-catch pentru nume nou
        {

            try
            {

                cin.getline(aux1, 200, '\n');
                string nume=aux;
                system("cls");

                int ok2=0;
                string str="0123456789";
                for (int i=0;i<strlen(aux1) and ok2==0;i++)
                    {
                    string str1(1, aux1[i]);
                    if (str.find(str1) != string::npos)
                        ok2=1;
                    }

                if (ok2==1)
                    throw 4;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x== 4)
                    cout<<"Numele sau prenumele nu trebuie sa contina cifre.\nIntroduceti din nou valoarea.\n";

                cin.clear();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);

        string nume3=aux1;



        companieprincipala.cautare_angajat(nume8)->setter_nume(nume3);


        //temp->setter_nume(nume);


            system("cls");

            cout<<"------  Operatie efectuata cu succes! ------"<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            //cin.get();
            cin.ignore();
            system("cls");
            meniu();


        }



        if (raspuns3==1)
        {
            cout<<"Introduceti noul cod pentru angajatul "<<nume8<<endl;
            cout<<endl;
            string noul_cod;
            cin>>noul_cod;


            angajat *temp= dynamic_cast<angajat* >(companieprincipala.cautare_angajat(nume8));
            temp->setter_cod_anganjat(noul_cod);

            system("cls");

            cout<<"------  Operatie efectuata cu succes! ------"<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            //cin.get();
            cin.ignore();
            system("cls");
            meniu();


        }

        if (raspuns3==3)
        {
            cout<<"Introduceti noul salariu pentru angajatul "<<nume8<<endl;
            cout<<endl;
            float salariul;
            //cin>>salariul;


        int ok=1;

        do      ///try-catch pentru optiune submeniu
        {

            try
            {
                cin>>salariul;

                if (cin.fail())
                    throw 1;

                ok=1;

            }
            catch (int x)
            {
                ok = 0;

                if (x==1)
                    cout<<"Va rugam introduceti un numar real!"<<endl;

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        }
        while(ok == 0);


            angajat *temp= dynamic_cast<angajat* >(companieprincipala.cautare_angajat(nume8));
            temp->setter_salariu(salariul);

            system("cls");

            cout<<"------  Operatie efectuata cu succes! ------"<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            //cin.get();
            cin.ignore();
            system("cls");
            meniu();


        }





        if (raspuns3==4)
            meniu();



        } /// sfarsit case 5





    case 6:
        {

    if (companie::getter_nr()==1)
        cout<<"S-a creat 1 entitate in baza de date!"<<endl;
    else
        cout<<"S-au creat "<<companie::getter_nr()<<" entitati in baza de date!"<<endl;

    cout<<"Dintre care, abonati: "<<abonat::getter_numar()<<endl;
    cout<<"Si angajati: "<<angajat::getter_numarnr()<<endl;


            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            cin.get();
            cin.ignore();
            system("cls");
            meniu();

        }





    case 7:
        {

            cout<<"Numarul de abonati Premium: "<<abonament_premium::getter_nrpremium()<<endl;
            cout<<"Numarul de abonati Normali: "<<abonament_normal::getter_numarnormale()<<endl;


            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            cin.get();
            cin.ignore();
            system("cls");
            meniu();


        }




    case 8:
        {
            int suma=0;
            int partial=0;

            for (int i=0;i<companieprincipala.getter_vector().size();i++)
            {
                partial=0;

                persoana* item = companieprincipala.getter_vector()[i];

                if (typeid(*item)==typeid(abonat))
                {

                    abonat *temp= dynamic_cast<abonat* >(item);


                    if (typeid( *temp->getter_abonament() ) == typeid(abonament_normal) )
                        {
                            //cout<<"----- Abonatul "<<nume<<" poseda momentan, un Abonament Normal! Urmeaza sa il schimbati in Abonament Premium! ----- "<<endl;
                           abonament_normal *abon = dynamic_cast <abonament_normal*> (temp->getter_abonament());
                           partial=partial+abon->getter_pret() * abon->getter_perioada();
                        }
                    else
                        if (typeid(*temp->getter_abonament())==typeid(abonament_premium) )
                            {
                               abonament_premium *abon = dynamic_cast <abonament_premium*> (temp->getter_abonament());
                               partial=partial+( abon->getter_pret() - abon->getter_reducere() ) * abon->getter_perioada();
                            }

                }

                suma=suma+partial;
            }


            cout<<endl;
            cout<<"Suma incasata de companie din plata abonamentelor este de "<<suma<<" lei"<<endl;
            cout<<endl;
            cout<<endl;

            cout<<"------ Apasati tasta ENTER pentru a afisa meniul -------"<<endl;
            cin.get();
            cin.ignore();
            system("cls");
            meniu();


        }



    case 9:
        {
            cout<<endl;
            cout<<endl;
            cout<<"------ Va multumim pentru timpul alocat si utilizarea acestui program! --------"<<endl;
            cout<<endl;
            cout<<"-------------------- Pe curand! -----------------------"<<endl;

            cout<<endl;
            cout<<endl;
            exit(0);
        }

    case 10:
        {
            first_read();
        }


    } /// sfarsit switch mare


}


void first_read()
{
    system("cls");
    companie a;
    cin>>a;
    companieprincipala=a;
    meniu();
}

int main()
{


HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r);

  MoveWindow(console, r.left, r.top, 1550, 800, TRUE);


cout<<"                             _______  _____  _______  _____   ______ _______ __   _ _______"<<endl;
cout<<"                             |       |     | |  |  | |_____] |  ____ |______ | \  |    |   "<<endl;
cout<<"                             |_____  |_____| |  |  | |       |_____| |______ |  \_|    |   "<<endl;



cout<<endl;
cout<<endl;



    cout<<"                   ------------ DISCLAIMER --------------"<<endl;
    cout<<endl;
    cout<<"Se recomanda largirea terminalului pentru a intra un rand complet pe latimea acestuia!"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" Aceasta aplicatie simuleaza un SISTEM DE GESTIUNE a unei baze de date a unei companii ce se ocupa cu vanzarea de servicii prin intermediul abonamentelor!"<<endl;
    cout<<endl;
    cout<<"-------Aplicatia are aplicabilitate in cadrul departamentului de Resurse Umane in activitati precum gestiunea abonamentelor, salariatilor, abonatilor. ------"<<endl;
    cout<<endl;
    cout<<" Abonamentele prezente in aplicatie sunt cel simplu si cel premium, ultimul fiind caracterizat de o reducere aplicata la pretul stabilit " <<endl;
    cout<<endl;
    cout<<endl;
    cout<<"    Precizari despre folosirea aplicatiei:"<<endl;
    cout<<"- Contractul nu se poate copia de la abonat la abonat, el este unic per abonat."<<endl;
    cout<<"- Numele trebuiesc adaugate unul cate unul, pe fiecare trebuind introdus separat pe uz"<<endl;
    cout<<"- Unde nu se specifica ca trebuie apasata tasta ENTER, luati-o ca pe o actiune din oficiu :)"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"-------Rugam citirea cu atentie a instructiunilor date pe ecran!----------"<<endl;

    cout<<endl;
    cout<<endl;
    cout<<"Daca ati citit acest mesaj, puteti trece mai departe!"<<endl;
    cout<<"Pentru acest lucru, apasati tasta ENTER!"<<endl;
   // cin.get();
    cin.ignore();
    system("cls");






  HANDLE console_color;
  console_color = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(console_color, 10);

  system("cls");

  cout<<"Daca nu va place culoarea textului, tastati 'nu' pentru a se intoarce la default"<<endl;
  cout<<"Daca nu aveti nicio problema cu acest fapt, apasati tasta ENTER pentru a continua"<<endl;

  string s;
  getline(cin,s);
   if (s=="nu")
       SetConsoleTextAttribute(console_color, 15);

    first_read();

return 0;
}
