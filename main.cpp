#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

struct Adresat
{
    int idAdresata;
    string imie, nazwisko, numerTelefonu, email, adres;
};

void wyswietlanieWszystkichAdresatow(vector <Adresat> &adresaci);
void wczytywanieAdresatowZPliku(vector <Adresat> &adresaci);
void dodawanieCalejLiniiDoStruktur(vector <Adresat> &adresaci, string linia);
void dodajAdresata(vector<Adresat> &adresaci);
void wczytywanieAdresatowPoImieniu(vector<Adresat> &adresaci);
void wczytywanieAdresatowPoNazwisku(vector<Adresat> &adresaci);
void usuwanieAdresata(vector<Adresat> &adresaci);
void edytowanieAdresata(vector<Adresat> &adresaci);
void aktualizowanieAdresatowPrzenoszenieStrukturDoPliku(vector <Adresat> &adresaci);

int main()
{
    vector<Adresat> adresaci;
    int iloscUzytkowikow = 0;
    char wybor;

    wczytywanieAdresatowZPliku(adresaci);

    while (true)
    {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            dodajAdresata(adresaci);
        }
        else if (wybor == '2')
        {
            wczytywanieAdresatowPoImieniu(adresaci);
        }
        else if (wybor == '3')
        {
            wczytywanieAdresatowPoNazwisku(adresaci);
        }
        else if (wybor == '4')
        {
            wyswietlanieWszystkichAdresatow(adresaci);
        }
        else if (wybor == '5')
        {
            usuwanieAdresata(adresaci);
        }
        else if (wybor == '6')
        {
            edytowanieAdresata(adresaci);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}

void wczytywanieAdresatowZPliku(vector <Adresat> &adresaci)
{
    string linia;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good() == false)
    {

    }
    else
    {
        for (int i = 0; !plik.eof(); i++)
        {
            getline (plik,linia);
            if (linia!="")
            {
                dodawanieCalejLiniiDoStruktur (adresaci, linia);
            }
        }
    }
    system("pause");
    plik.close();
}

void usuwanieAdresata(vector<Adresat> &adresaci)
{
    cout << "Podaj id adresata ktorego zamierzasz usunac" << endl;
    string idAdresataDoUsuniecia;
    cin >> idAdresataDoUsuniecia;
    cin.sync();
    cout << endl << "Potwierdzasz? Tego wybory nie da sie cofnac (t/n): " << endl;
    char wybor;
    wybor = getchar();

    while (true)
    {
        if (wybor=='t')
        {
            string linia;
            fstream plik;
            //plik.open("KsiazkaAdresowa.txt", ios::in); ios::out | ios::app);
            plik.open("KsiazkaAdresowa.txt", ios::out | ios::in);
            fstream tymczasowyPlik;
            tymczasowyPlik.open("KsiazkaAdresowaKopia.txt", ios::out | ios::app);

            for (int i = 0; !plik.eof(); i++)
            {
                getline (plik,linia);
                cout << "Pobrana linia to: " << linia << endl;
                if (linia!="")
                {
                    string pierwszeCyrtyIdAdresata = linia.substr(0, 5);
                    size_t found = pierwszeCyrtyIdAdresata.find(idAdresataDoUsuniecia);
                    if ((pierwszeCyrtyIdAdresata).find(idAdresataDoUsuniecia) != string::npos)
                    {
                        cout << "Adresat został usuniety" << endl;
                    }
                    else
                    {
                        tymczasowyPlik << linia << endl;
                    }
                }
            }
            plik.close();
            tymczasowyPlik.close();
            remove("KsiazkaAdresowa.txt");
            rename("KsiazkaAdresowaKopia.txt","KsiazkaAdresowa.txt");
            cout << "Zakonczono pocerudre usuwania" << endl;

            adresaci.clear();
            wczytywanieAdresatowZPliku(adresaci);
            break;
        }
        else if (wybor=='n')
        {
            break;
        }
        else
        {
            cout << "Nieprawidłowy znak, powrot do poprzedniego menu" << endl;
            system("pause");
            break;
        }
    }
}

void edytowanieAdresata(vector<Adresat> &adresaci)
{
    cout << "Podaj id adresata ktorego zamierzasz edytowac" << endl;
    int idAdresataDoEdycji, numerAdresataWStrukturze;
    cin >> idAdresataDoEdycji;
    cin.sync();
    string nowyParametr;

    cout << "Jaki parametr chcesz edytowac?" << endl;

    for (int i = 0; i<adresaci.size(); i++)
    {
        if (idAdresataDoEdycji == adresaci[i].idAdresata)
        {
            cout << "ID adresata: " << adresaci[i].idAdresata << endl;
            cout << "1 - imie: " << adresaci[i].imie << endl;
            cout << "2 - nazwisko: " << adresaci[i].nazwisko << endl;
            cout << "3 - numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "4 - email: " << adresaci[i].email << endl;
            cout << "5 - adres: " << adresaci[i].adres << endl;
            cout << "6 - powrot do menu" << endl;
            cout << "-------------------------" << endl;
            numerAdresataWStrukturze = i;
        }
    }
    char wybor;
    wybor = getchar();

    while (true)
    {
        if (wybor=='1')
        {
            cout << "Podaj nowe imie: " << endl;
            cin >> nowyParametr;
            adresaci[numerAdresataWStrukturze].imie = nowyParametr;
            break;
        }
        if (wybor=='2')
        {
            cout << "Podaj nowe nazwisko: " << endl;
            cin >> nowyParametr;
            adresaci[numerAdresataWStrukturze].nazwisko = nowyParametr;
            break;
        }
        if (wybor=='3')
        {
            cout << "Podaj nowy numer telefonu: " << endl;
            cin.sync();
            getline(cin, adresaci[numerAdresataWStrukturze].numerTelefonu);
            break;
        }
        if (wybor=='4')
        {
            cout << "Podaj nowy email: " << endl;
            cin >> nowyParametr;
            adresaci[numerAdresataWStrukturze].email = nowyParametr;
            break;
        }
        if (wybor=='5')
        {
            cout << "Podaj nowy adres: " << endl;
            cin.sync();
            getline(cin, adresaci[numerAdresataWStrukturze].adres);
            break;
        }
        if (wybor=='6')
        {
            cout << "Powrot " << endl;
            break;
        }
    }
    aktualizowanieAdresatowPrzenoszenieStrukturDoPliku(adresaci);
    system("pause");

}

void aktualizowanieAdresatowPrzenoszenieStrukturDoPliku(vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::in);
    fstream tymczasowyPlik;
    tymczasowyPlik.open("KsiazkaAdresowaKopia.txt", ios::out | ios::app);

    for (int i = 0; i<adresaci.size(); i++)
    {
        tymczasowyPlik << adresaci[i].idAdresata << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" <<  endl;
    }
    plik.close();
    tymczasowyPlik.close();
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowaKopia.txt","KsiazkaAdresowa.txt");
    cout << "Zakonczono pocerudre aktualizacji" << endl;

    adresaci.clear();
    wczytywanieAdresatowZPliku(adresaci);
}

void dodawanieCalejLiniiDoStruktur(vector <Adresat> &adresaci, string linia)
{
    string s = linia;
    string delimiter = "|";
    //fragment kodu skopiowanego z internetu, dzieli linie na wyrazy, separatorem jest "|"
    size_t pos = 0;
    string token[5];
    int i = 0;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token[i] = s.substr(0, pos);
        cout << token[i] << endl;
        s.erase(0, pos + delimiter.length());
        i++;
    }
    Adresat adres;
    adres.idAdresata = atoi(token[0].c_str());
    adres.imie = token[1];
    adres.nazwisko = token[2];
    adres.numerTelefonu = token[3];
    adres.email = token[4];
    adres.adres = token[5];

    adresaci.push_back(adres);
}

void dodajAdresata(vector<Adresat> &adresaci)
{
    Adresat adres;

    if (adresaci.size()==0)
    {
        adres.idAdresata = 0;
    }
    else
    {
        adres.idAdresata = adresaci[adresaci.size()-1].idAdresata+1;
    }

    cout << "Podaj imie:";
    cin >> adres.imie;
    cout << "Podaj nazwisko:";
    cin >> adres.nazwisko;
    cout << "Podaj numer telefonu:";
    cin.sync();
    getline(cin, adres.numerTelefonu);
    cout << "Podaj e-mail:";
    cin >> adres.email;
    cout << "Podaj adres:";
    cin.sync();
    getline(cin, adres.adres);

    adresaci.push_back(adres);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << adres.idAdresata << "|" << adres.imie << "|" << adres.nazwisko << "|" << adres.numerTelefonu << "|" << adres.email << "|" << adres.adres << "|" <<  endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    system("pause");

}

void wczytywanieAdresatowPoImieniu(vector<Adresat> &adresaci)
{
    system("cls");
    string imieUzytkownika;
    cout << "Podaj imie adresata: ";
    cin >> imieUzytkownika;
    for (int i = 0; i<adresaci.size(); i++)
    {
        if (imieUzytkownika == adresaci[i].imie)
        {
            cout << "id uzytkownika to : " << adresaci[i].idAdresata << endl;
            cout << "imie uzytkownika to : " << adresaci[i].imie << endl;
            cout << "nazwisko uzytkownika to : " << adresaci[i].nazwisko << endl;
            cout << "numerTelefonuefon uzytkownika to : " << adresaci[i].numerTelefonu << endl;
            cout << "email uzytkownika to : " << adresaci[i].email << endl;
            cout << "adres uzytkownika to : " << adresaci[i].adres << endl;
            cout << "-------------------------" << endl;
        }
    }
    system("pause");
}

void wczytywanieAdresatowPoNazwisku(vector<Adresat> &adresaci)
{
    system("cls");
    string nazwiskoAdresata;
    cout << "Podaj nazwisko adresata: ";
    cin >> nazwiskoAdresata;
    for (int i = 0; i<adresaci.size(); i++)
    {
        if (nazwiskoAdresata == adresaci[i].nazwisko)
        {
            cout << "id uzytkownika to : " << adresaci[i].idAdresata << endl;
            cout << "imie uzytkownika to : " << adresaci[i].imie << endl;
            cout << "nazwisko uzytkownika to : " << adresaci[i].nazwisko << endl;
            cout << "numerTelefonuefon uzytkownika to : " << adresaci[i].numerTelefonu << endl;
            cout << "email uzytkownika to : " << adresaci[i].email << endl;
            cout << "adres uzytkownika to : " << adresaci[i].adres << endl;
            cout << "-------------------------" << endl;
        }
    }
    system("pause");
}

void wyswietlanieWszystkichAdresatow(vector <Adresat> &adresaci)
{
    system("cls");
    for (int i = 0; i<adresaci.size(); i++)
    {
        cout << "id uzytkownika to : " << adresaci[i].idAdresata << endl;
        cout << "imie uzytkownika to : " << adresaci[i].imie << endl;
        cout << "nazwisko uzytkownika to : " << adresaci[i].nazwisko << endl;
        cout << "numerTelefonuefon uzytkownika to : " << adresaci[i].numerTelefonu << endl;
        cout << "email uzytkownika to : " << adresaci[i].email << endl;
        cout << "adres uzytkownika to : " << adresaci[i].adres << endl;
        cout << "-------------------------" << endl;
    }
    system("pause");
}
