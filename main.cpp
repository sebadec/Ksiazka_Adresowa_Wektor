#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

struct Adresat
{
    int idAdresata, idUzytkownika;
    string imie, nazwisko, numerTelefonu, email, adres;
};

void wyswietlanieWszystkichAdresatow(vector <Adresat> &adresaci);
void wczytywanieAdresatowZPliku(vector <Adresat> &adresaci, int idUzytkownikaStala);
void dodawanieCalejLiniiDoStruktur(vector <Adresat> &adresaci, string linia, int idUzytkownikaStala);
void dodajAdresata(vector<Adresat> &adresaci, int idUzytkownikaStala);
void wczytywanieAdresatowPoImieniu(vector<Adresat> &adresaci);
void wczytywanieAdresatowPoNazwisku(vector<Adresat> &adresaci);
void usuwanieAdresata(vector<Adresat> &adresaci, int idUzytkownikaStala);
void edytowanieAdresata(vector<Adresat> &adresaci, int idUzytkownikaStala);
void aktualizowanieAdresatowPrzenoszenieStrukturDoPliku(vector <Adresat> &adresaci, int idUzytkownikaStala, int idAdresataDoEdycji, int numerAdresataWStrukturze);
void menu(vector <Uzytkownik> uzytkownicy, int idUzytkownikaStala);
void dodajUzytkownika(vector <Uzytkownik> &uzytkownicy);
void wczytywanieUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy);
void dodawanieCalejLiniiDoStrukturUzytkownicy(vector <Uzytkownik> &uzytkownicy, string linia);
void logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy);
int wyznaczanieMaxIdAdresata ();
void zmianaHasla (vector <Uzytkownik> &uzytkownicy, int idUzytkownikaStala);

int main()
{
    vector <Uzytkownik> uzytkownicy;
    char wybor;
    Adresat adres;

    wczytywanieUzytkownikowZPliku(uzytkownicy);

    while (true)
    {
        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            uzytkownicy.clear();
            wczytywanieUzytkownikowZPliku (uzytkownicy);

            logowanieUzytkownika(uzytkownicy);
        }
        else if (wybor == '2')
        {
            dodajUzytkownika(uzytkownicy);
        }
        else if (wybor == '3')
        {
            exit(0);
        }
    }

    return 0;
}

int wyznaczanieMaxIdAdresata ()
{
    int maxIdAdresataStala = 1;
    vector <string> IdAdresatow;
    string linia;
    fstream plik;
    plik.open("Adresaci.txt", ios::in);
    if (plik.good() == false)
    {

    }
    else
    {
        for (int i = 0; !plik.eof(); i++)
        {
            cin.sync();
            getline (plik,linia);
            if (linia!="")
            {
                string s = linia;
                string delimiter = "|";
                string token = s.substr(0, s.find(delimiter));
                IdAdresatow.push_back(token);
            }
        }
    }
    sort(IdAdresatow.begin(),IdAdresatow.end());
    maxIdAdresataStala = atoi(IdAdresatow.back().c_str());
    plik.close();
    return maxIdAdresataStala;
}

void logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    //system("cls");
    string imieUzytkownika, hasloUzytkownika;
    int idUzytkownikaStala, maxIdAdresataStala;
    cout << "Podaj login: ";
    cin >> imieUzytkownika;
    for (int i = 0; i<uzytkownicy.size(); i++)
    {
        if (imieUzytkownika == uzytkownicy[i].nazwa)
        {
            cout << "Podaj haslo: ";
            cin >> hasloUzytkownika;
            if (hasloUzytkownika == uzytkownicy[i].haslo)
            {
                cout << "Logowanie udane" << endl;
                idUzytkownikaStala = uzytkownicy[i].idUzytkownika;
                menu(uzytkownicy, idUzytkownikaStala);
                return;
            }
            else
            {
                cout << "Podane haslo jest nieprawidlowe." << endl;
                system("pause");
                return;
            }
        }
    }
    cout << "Brak uzytkownika o podanym loginie." << endl;
    system("pause");
    return;
}

void dodajUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik adres;

    if (uzytkownicy.size()==0)
    {
        adres.idUzytkownika = 0;
    }
    else
    {
        adres.idUzytkownika = uzytkownicy[uzytkownicy.size()-1].idUzytkownika+1;
    }
    cout << "Podaj login:";
    cin >> adres.nazwa;
    cout << "Podaj haslo:";
    cin >> adres.haslo;

    uzytkownicy.push_back(adres);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << adres.idUzytkownika << "|" << adres.nazwa << "|" << adres.haslo << "|" <<  endl;

        plik.close();

        cout << "Uzytkownik zostala dodany." << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }
    system("pause");

}

void menu(vector <Uzytkownik> uzytkownicy, int idUzytkownikaStala)
{
    vector <Adresat> adresaci;
    int iloscUzytkowikow = 0;
    char wybor;

    wczytywanieAdresatowZPliku(adresaci, idUzytkownikaStala);

    while (true)
    {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "9. Wyloguj sie" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            dodajAdresata(adresaci, idUzytkownikaStala);
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
            usuwanieAdresata(adresaci, idUzytkownikaStala);
        }
        else if (wybor == '6')
        {
            edytowanieAdresata(adresaci, idUzytkownikaStala);
        }
        else if (wybor == '7')
        {
            zmianaHasla (uzytkownicy, idUzytkownikaStala);
        }
        else if (wybor == '9')
        {
            break;
        }
    }
}

void zmianaHasla (vector <Uzytkownik> &uzytkownicy, int idUzytkownikaStala)
{
    string noweHaslo;
    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;

    uzytkownicy[idUzytkownikaStala].haslo = noweHaslo;

    string linia;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::in);
    fstream tymczasowyPlik;
    tymczasowyPlik.open("UzytkownicyKopia.txt", ios::out | ios::app);

    for (int i = 0; !plik.eof(); i++)
    {
        getline (plik,linia);
        if (linia!="")
        {
            string s = linia;
            string delimiter = "|";
            size_t pos = 0;
            string token[2];
            int i = 0;
            while ((pos = s.find(delimiter)) != string::npos)
            {
                token[i] = s.substr(0, pos);
                s.erase(0, pos + delimiter.length());
                i++;
            }

            if (atoi(token[0].c_str()) == idUzytkownikaStala)
            {
                tymczasowyPlik << token[0] << "|" << token[1] << "|" << noweHaslo << "|" << endl;
            }
            else
            {
                tymczasowyPlik << linia << endl;
            }
        }
    }


    /*
    string linia;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::in);
    fstream tymczasowyPlik;
    tymczasowyPlik.open("UzytkownicyKopia.txt", ios::out | ios::app);

    for (int i = 0; !plik.eof(); i++)
    {
        getline (plik,linia);
        if (linia!="")
        {
            string s = linia;
            string delimiter = "|";
            string token = s.substr(0, s.find(delimiter));
            if (atoi(token.c_str()) == idUzytkownikaStala)
            {
                tymczasowyPlik << uzytkownicy[idUzytkownikaStala].idUzytkownika << "|" << uzytkownicy[idUzytkownikaStala].nazwa << "|" << uzytkownicy[idUzytkownikaStala].haslo << "|" << endl;
            }
            else
            {
                tymczasowyPlik << linia << endl;
            }
        }
    }
    */

    plik.close();
    tymczasowyPlik.close();
    remove("Uzytkownicy.txt");
    rename("UzytkownicyKopia.txt","Uzytkownicy.txt");
    cout << "Zakonczono pocerudre aktualizacji" << endl;

    uzytkownicy.clear();
    wczytywanieUzytkownikowZPliku (uzytkownicy);

    system("pause");
}

void wczytywanieAdresatowZPliku(vector <Adresat> &adresaci, int idUzytkownikaStala)
{
    string linia;
    fstream plik;
    plik.open("Adresaci.txt", ios::in);

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
                dodawanieCalejLiniiDoStruktur (adresaci, linia, idUzytkownikaStala);
            }
        }
    }
    system("pause");
    plik.close();
}

void wczytywanieUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    string linia;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

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
                dodawanieCalejLiniiDoStrukturUzytkownicy (uzytkownicy, linia);
            }
        }
    }
    plik.close();
}

void dodawanieCalejLiniiDoStrukturUzytkownicy(vector <Uzytkownik> &uzytkownicy, string linia)
{
    string s = linia;
    string delimiter = "|";
    size_t pos = 0;
    string token[2];
    int i = 0;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token[i] = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
        i++;
    }
    Uzytkownik adres;
    adres.idUzytkownika = atoi(token[0].c_str());
    adres.nazwa = token[1];
    adres.haslo = token[2];
    uzytkownicy.push_back(adres);
}


void usuwanieAdresata(vector<Adresat> &adresaci, int idUzytkownikaStala)
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
            plik.open("Adresaci.txt", ios::out | ios::in);
            fstream tymczasowyPlik;
            tymczasowyPlik.open("AdresaciKopia.txt", ios::out | ios::app);

            for (int i = 0; !plik.eof(); i++)
            {
                getline (plik,linia);
                if (linia!="")
                {
                    string s = linia;
                    string delimiter = "|";
                    string token = s.substr(0, s.find(delimiter));
                    if (token == idAdresataDoUsuniecia)
                    {
                        cout << "Adresat zostal usuniety" << endl;
                    }
                    else
                    {
                        tymczasowyPlik << linia << endl;
                    }
                }
            }
            plik.close();
            tymczasowyPlik.close();
            remove("Adresaci.txt");
            rename("AdresaciKopia.txt","Adresaci.txt");
            cout << "Zakonczono pocerudre usuwania" << endl;

            adresaci.clear();
            wczytywanieAdresatowZPliku(adresaci, idUzytkownikaStala);
            break;
        }
        else if (wybor=='n')
        {
            break;
        }
        else
        {
            cout << "Nieprawidlowy znak, powrot do poprzedniego menu" << endl;
            system("pause");
            return;
        }
    }
}

void edytowanieAdresata(vector<Adresat> &adresaci, int idUzytkownikaStala)
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
            cout << "ID uzytkownika: " << adresaci[i].idUzytkownika << endl;
            cout << "1 - imie: " << adresaci[i].imie << endl;
            cout << "2 - nazwisko: " << adresaci[i].nazwisko << endl;
            cout << "3 - numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "4 - email: " << adresaci[i].email << endl;
            cout << "5 - adres: " << adresaci[i].adres << endl;
            cout << "6 - powrot do menu" <<  endl;
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
    aktualizowanieAdresatowPrzenoszenieStrukturDoPliku(adresaci, idUzytkownikaStala, idAdresataDoEdycji, numerAdresataWStrukturze);
    system("pause");

}

void aktualizowanieAdresatowPrzenoszenieStrukturDoPliku(vector <Adresat> &adresaci, int idUzytkownikaStala, int idAdresataDoEdycji, int numerAdresataWStrukturze)
{
    string linia;
    fstream plik;
    plik.open("Adresaci.txt", ios::out | ios::in);
    fstream tymczasowyPlik;
    tymczasowyPlik.open("AdresaciKopia.txt", ios::out | ios::app);

    for (int i = 0; !plik.eof(); i++)
    {
        getline (plik,linia);
        if (linia!="")
        {
            string s = linia;
            string delimiter = "|";
            string token = s.substr(0, s.find(delimiter));
            if (atoi(token.c_str()) == idAdresataDoEdycji)
            {
                tymczasowyPlik << adresaci[numerAdresataWStrukturze].idAdresata << "|" << adresaci[numerAdresataWStrukturze].idUzytkownika << "|" << adresaci[numerAdresataWStrukturze].imie << "|" << adresaci[numerAdresataWStrukturze].nazwisko << "|" << adresaci[numerAdresataWStrukturze].numerTelefonu << "|" << adresaci[numerAdresataWStrukturze].email << "|" << adresaci[numerAdresataWStrukturze].adres << "|" <<  endl;
            }
            else
            {
                tymczasowyPlik << linia << endl;
            }
        }
    }

    plik.close();
    tymczasowyPlik.close();
    remove("Adresaci.txt");
    rename("AdresaciKopia.txt","Adresaci.txt");
    cout << "Zakonczono pocerudre aktualizacji" << endl;

    adresaci.clear();
    wczytywanieAdresatowZPliku(adresaci, idUzytkownikaStala);
}

void dodawanieCalejLiniiDoStruktur(vector <Adresat> &adresaci, string linia, int idUzytkownikaStala)
{
    string s = linia;
    string delimiter = "|";
    size_t pos = 0;
    string token[6];
    int i = 0;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token[i] = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
        i++;
    }

    if ((atoi(token[1].c_str())) == idUzytkownikaStala)
    {
        Adresat adres;
        adres.idAdresata = atoi(token[0].c_str());
        adres.idUzytkownika = atoi(token[1].c_str());
        adres.imie = token[2];
        adres.nazwisko = token[3];
        adres.numerTelefonu = token[4];
        adres.email = token[5];
        adres.adres = token[6];
        adresaci.push_back(adres);
    }
}

void dodajAdresata(vector<Adresat> &adresaci, int idUzytkownikaStala)
{
    Adresat adres;
    adres.idUzytkownika = idUzytkownikaStala;
    adres.idAdresata = wyznaczanieMaxIdAdresata()+1;
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
    plik.open("Adresaci.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << adres.idAdresata << "|" << adres.idUzytkownika << "|" << adres.imie << "|" << adres.nazwisko << "|" << adres.numerTelefonu << "|" << adres.email << "|" << adres.adres << "|" <<  endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Adresaci.txt" << endl;
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
            cout << "id adresata to : " << adresaci[i].idAdresata << endl;
            cout << "id uzytkownika to : " << adresaci[i].idUzytkownika << endl;
            cout << "imie adresata to : " << adresaci[i].imie << endl;
            cout << "nazwisko adresata to : " << adresaci[i].nazwisko << endl;
            cout << "numerTelefonuefon adresata to : " << adresaci[i].numerTelefonu << endl;
            cout << "email adresata to : " << adresaci[i].email << endl;
            cout << "adres adresata to : " << adresaci[i].adres << endl;
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
            cout << "id adresata to : " << adresaci[i].idAdresata << endl;
            cout << "id uzytkownika to : " << adresaci[i].idUzytkownika << endl;
            cout << "imie adresata to : " << adresaci[i].imie << endl;
            cout << "nazwisko adresata to : " << adresaci[i].nazwisko << endl;
            cout << "numerTelefonuefon adresata to : " << adresaci[i].numerTelefonu << endl;
            cout << "email adresata to : " << adresaci[i].email << endl;
            cout << "adres adresata to : " << adresaci[i].adres << endl;
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
        cout << "id adresata to : " << adresaci[i].idAdresata << endl;
        cout << "id uzytkownika to : " << adresaci[i].idUzytkownika << endl;
        cout << "imie adresata to : " << adresaci[i].imie << endl;
        cout << "nazwisko adresata to : " << adresaci[i].nazwisko << endl;
        cout << "numerTelefonuefon adresata to : " << adresaci[i].numerTelefonu << endl;
        cout << "email adresata to : " << adresaci[i].email << endl;
        cout << "adres adresata to : " << adresaci[i].adres << endl;
        cout << "-------------------------" << endl;
    }
    system("pause");
}
