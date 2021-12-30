#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
using namespace std;

enum Stanje{slobodno=1,rezervisano};

char crta[]="----------------------------------------------------\n";

struct registracija{
    string password;
    string username;
};

struct sortiranje{
    int ID;
    double cijena;
    int brojSoba;
    int brojKreveta;
};

void prikaziMeniGlavni(){
	system("clear");
	cout << "----------------------------------------------\n";
	cout << "\t\tMeni:\n";
	cout << "----------------------------------------------\n";
	cout << "\t1. Admin\n";
	cout << "\t2. Rezervacija\n";
	cout << "\t3. Izlaz\n";
	cout << "----------------------------------------------\n";
    }

double nadjiSumu(double niz[],int brojac){
    if (brojac <= 0)
        return 0;
    return (nadjiSumu(niz, brojac - 1) + niz[brojac - 1]);
}

bool provjera(int unos){
    bool uspjelo=false;

    do{
        if(!cin || unos!=int(unos)){
            cin.clear();
            
        }else{
            uspjelo = true;
        }
    }while(!uspjelo);

    return uspjelo;
}

struct smjestaj{
    int ID;
    double cijena;
    int brojSoba;
    int brojKreveta;
    Stanje stanje;
    registracija admin;
    sortiranje sortTemp;

    void unosSmjestaja(){

        ofstream datoteka("smjestaji.txt",ios::app);
        ofstream pregled("tabela.txt",ios::app);

        do{
        cout<<"ID sobe: ";
        cin>>this->ID;
        }while(provjera(ID)==false);

        datoteka<<"ID sobe: "<<ID<<endl;
        pregled<<ID<<" ";

        do{
        cout<<"Cijena smjestaja: ";
        cin>>this->cijena;
        }while(provjera(cijena)==false);
        datoteka<<"Cijena smjestaja: "<<cijena<<endl;
        pregled<<cijena<<" ";

        do{
        cout<<"Broj kreveta u smjestaju: ";
        cin>>this->brojKreveta;
        }while(provjera(brojKreveta)==false);
        datoteka<<"Broj kreveta u smjestaju: "<<brojKreveta<<endl;
        pregled<<brojKreveta<<" ";

        do{
        cout<<"Broj soba u smjestaju: ";
        cin>>this->brojSoba;
        }while(provjera(brojSoba)==false);
        datoteka<<"Broj soba u smjestaju: "<<brojSoba<<endl;
        pregled<<brojSoba<<" ";
        int x;
        do{
        cout<<"Odaberite stanje sobe:\n\t1. Slobodno\n\t2. Rezervisano";
            do{
			cout << "\nOdabir: ";
			cin >> x;
            }while(provjera(x)==false);
		}while(x<1 || x>2);
		this->stanje = Stanje(x);

		if(x==1){
			datoteka << "Stanje: Slobodno" << endl;
			pregled << "Slobodno"<<endl;
        }else if(x==2){
			datoteka << "Stanje: Rezervisano" << endl;
			pregled<<"Rezervisano"<<endl;
        }

        datoteka.close();
        pregled.close();
    }

    void pregledSmjestajaAdmin(){

        ifstream ispis("smjestaji.txt");
		string provjera;

        if(ispis.is_open()){
            cout << left << setw(8) << "ID" << left << setw(20) << "Cijena" << left << setw(15)
            << "Broj kreveta" << left << setw(15) << "Broj soba" << left << setw(12) << "Stanje" << endl;

            while(ispis>>provjera){

                if(provjera == "sobe:"){
                    ispis >> provjera;
                    cout << left << setw(8) << provjera << "";
                }

                if(provjera == "smjestaja:"){
                    ispis >> provjera;
                    provjera += " KM";
                    cout << left << setw(20)<< provjera <<"";
                }

                if(provjera == "smjestaju:"){
                    ispis >> provjera;
                    cout << left << setw(15) << provjera << "";
                }

                if(provjera == "smjestaju:"){
                    ispis >> provjera;
                    provjera += " KM";
                    cout << left << setw(15) << provjera << "";
                }

                if(provjera == "Stanje:"){
                    ispis >> provjera;
                    cout << left << setw(12) << provjera << endl;
                }

            }

            cout<<"\n[ENTER] za povratak.";

		}else{
		    cout<<"[GRESKA] Nema registrovanih smjestaja!";
        }
    ispis.close();
    }

    void rezervacija(){

        string stanjeTemp;
        vector<int> vec;
        ifstream pregled("tabela.txt");

        cout<<"\t\t---------------------------------------\n";
        cout<<"\t\t|   Sistem za rezervaciju smjestaja   |\n";
        cout<<"\t\t---------------------------------------\n\n";



        if(pregled.is_open()){

        cout << left << setw(8) << "ID" << left << setw(15) << "Cijena" << left << setw(15)
        << "Broj kreveta" << left << setw(15) << "Broj soba" << endl;

            while(pregled>>ID>>cijena>>brojKreveta>>brojSoba>>stanjeTemp){
                if(stanjeTemp=="Slobodno"){
                    cout << left << setw(8) << ID << "";
                    vec.push_back(ID);
                    cout << left << setw(15) << cijena << "";
                    cout << left << setw(15) << brojKreveta << "";
                    cout << left << setw(15) << brojSoba << "";
                    cout<<endl;
                }
            }
        }else{
            cout<<"[GRESKA] Nema unesenih smjestaja!\n";
            cout<<"[ENTER] za povratak";
            return;
        }
        pregled.close();

        int rb;
        char yn;
        cout<<endl<<crta;
        while(true){
            jump:
            do{
                do{
                cout<<"Molimo vas unesite ID broj sobe koju zelite rezervisati\n->";
                cin>>rb;
                }while(provjera(rb)==false);
            }while(find(vec.begin(), vec.end(), rb) == vec.end());

            cout<<"Da li ste sigurni da zelite sobu sa ID "<<rb<<"\n[Y/N]->";
            rb=char(rb);
            cin>>yn;
            if(yn=='Y' || yn=='y'){
                break;
            }else{
                goto jump;
            }
        }
        system("cls");

        ifstream pregled2("tabela.txt");
        ofstream potvrda("potvrdaRezervacije.txt");

        if(pregled2.is_open() && potvrda.is_open()){
            cout<<"Hvala vam na rezervaciji!\n";
            while(pregled2>>ID>>cijena>>brojKreveta>>brojSoba>>stanjeTemp){
                if(ID==rb){
                    cout<<"Izabrali ste smjestaj sa "<<brojKreveta<<" kreveta.\nNa raspolaganju imate "<<brojSoba
                    <<" sobe, a cijena koristenja na jednu noc je "<<cijena<<" KM.";

                    potvrda<<"Uspjesna rezervacija za smjestaj pod ID brojem "<<ID<<".\n";
                    potvrda<<crta<<"Informacije o smjestaju\n"<<crta<<endl;
                    potvrda<<"Broj kreveta: "<<brojKreveta<<endl;
                    potvrda<<"Broj soba: "<<brojSoba<<endl;
                    potvrda<<"Cijena za jednu noc: "<<cijena<<" KM"<<endl<<endl<<crta<<endl;
                    potvrda<<endl<<endl<<"[isprintani tekst ove datoteke predajete prilikom dolaska u hotel]";

                    cout<<endl<<crta<<endl<<"Potvrda o rezervaciji sobe i informacije o smjestaju\nmozete naci u datoteci potvrdaRezervacije.txt\n";
                }
            }
        }else{
        cout<<"[GRESKA] Nemoguce otvoriti datoteke!";
        }
        pregled2.close();

        cout<<"\n[ENTER] za povratak";

    }

    void pregledSmjestajGuest(){

        ifstream pregledGuest("tabela.txt");
        string stanjeTemp;
        int brojac=0;


        cout<<"\t\t-----------------------------------\n";
        cout<<"\t\t|   Pregled dostupnih smjestaja   |\n";
        cout<<"\t\t-----------------------------------\n\n";

        if(pregledGuest.is_open()){


            while(pregledGuest>>ID>>cijena>>brojKreveta>>brojSoba>>stanjeTemp){
                if(stanjeTemp=="Slobodno"){
                    brojac++;
                }
            }
        }else{
            cout<<"[GRESKA] Nema unesenih smjestaja!";
            cout<<"\n[ENTER] za povratak";
            return;

        }
        pregledGuest.close();

        sortiranje sortTemp[brojac];
        int i=0;
        pregledGuest.open("tabela.txt");

        if(pregledGuest.is_open()){
            while(pregledGuest>>ID>>cijena>>brojKreveta>>brojSoba>>stanjeTemp){
                if(stanjeTemp=="Slobodno"){
                    sortTemp[i].ID=ID;
                    sortTemp[i].cijena=cijena;
                    sortTemp[i].brojKreveta=brojKreveta;
                    sortTemp[i].brojSoba=brojSoba;
                    i++;
                }
            }
        }else{
            cout<<"[GRESKA] Nema unesenih smjestaja!";
            cout<<"\n[ENTER] za povratak";
            return;
        }

        for(int i=0;i<brojac;i++){
            for(int j=i+1;j<brojac;j++){
                if(sortTemp[i].cijena>sortTemp[j].cijena){
                    swap(sortTemp[i].ID,sortTemp[j].ID);
                    swap(sortTemp[i].cijena,sortTemp[j].cijena);
                    swap(sortTemp[i].brojKreveta,sortTemp[j].brojKreveta);
                    swap(sortTemp[i].brojSoba,sortTemp[j].brojSoba);
                }
            }
        }

        cout << left << setw(8) << "ID" << left << setw(20) << "Cijena/noc" << left << setw(15)
        << "Broj kreveta" << left << setw(15) << "Broj soba" << endl;

        for(int i=0;i<brojac;i++){
            cout << left << setw(8) << sortTemp[i].ID << "";
            cout << left << setw(20) << sortTemp[i].cijena <<"";
            cout << left << setw(15) << sortTemp[i].brojKreveta << "";
            cout << left << setw(15) << sortTemp[i].brojSoba << "";
            cout<<endl;
        }

        cout<<"\n[ENTER] za povratak";

    }

    void statistika(){

        ifstream brojanje("tabela.txt");
        string stanjeTemp;
        int suma;
        int brojacKreveta=0;
        int brojacSoba=0;
        int brojSmjestaja=0;
        int brojSlobodnih=0;


        if(brojanje.is_open()){
             while(brojanje>>ID>>cijena>>brojKreveta>>brojSoba>>stanjeTemp){
                if(brojanje.end){
                    brojSmjestaja++;
                }
             }
        }
        brojanje.close();


        ifstream pregled("tabela.txt");
        double *arr=new double[brojSmjestaja];

        if(pregled.is_open()){
            int i=0;
            while(pregled>>ID>>cijena>>brojKreveta>>brojSoba>>stanjeTemp){
                if(cijena>0){
                    arr[i]=cijena;
                    i++;
                }
                if(brojKreveta==1){
                    brojacKreveta++;
                }
                if(brojSoba==1){
                    brojacSoba++;
                }
                if(stanjeTemp=="Slobodno"){
                    brojSlobodnih++;
                }

            }
        }else{
            cout<<"[GRESKA] Nema unesenih smjestaja!";
            cout<<"\n[ENTER] za povratak";
            return;
        }

        double prosjekCijene,prosjekSoba,prosjekKreveta,prosjekSlobodnih;
        prosjekCijene=nadjiSumu(arr,brojSmjestaja)/brojSmjestaja;
        prosjekKreveta=((double)brojacKreveta/brojSmjestaja)*100;
        prosjekSoba=((double)brojacSoba/brojSmjestaja)*100;
        prosjekSlobodnih=((double)brojSlobodnih/brojSmjestaja)*100;
        cout<<"Prosjecna cijena smjestaja: "<<setprecision(2)<<fixed<<prosjekCijene<<" KM"<<endl;
        cout<<"Broj soba sa jednim krevetom: "<<prosjekKreveta<<"% ("<<brojacKreveta<<")\n";
        cout<<"Broj smjestaja sa jednom sobom: "<<prosjekSoba<<"% ("<<brojacSoba<<")\n";
        cout<<"Slobodnih soba: "<<prosjekSlobodnih<<"% ("<<brojSlobodnih<<")\n";

        cout<<"\n[ENTER] za povratak";
        delete[] arr;
    }

    void pretragaSmjestaja(){

        int brojO,brojS;
        cout<<"\t-------------------------\n";
        cout<<"\t|   Pretraga smjestaja  |\n";
        cout<<"\t-------------------------\n";

        do{
        cout<<"\nBroj osoba: ";
        cin>>brojO;
        }while(provjera(brojO)==false);

        do{
        cout<<"\nBroj soba: ";
        cin>>brojS;
        }while(provjera(brojS)==false);

        ifstream pregled("tabela.txt");
        string stanjeTemp;
        bool ima=false;
        if(pregled.is_open()){
                cout << left << setw(8) << "ID" << left << setw(15) << "Cijena/noc" << left << setw(20)
                << "Broj kreveta" << left << setw(15) << "Broj soba" << endl;

            while(pregled>>ID>>cijena>>brojKreveta>>brojSoba>>stanjeTemp){
                if(stanjeTemp=="Slobodno" && brojO<=brojKreveta && brojS<=brojSoba){
                    cout << left << setw(8) << ID << "";
                    cout << left << setw(15) << cijena << "";
                    cout << left << setw(20) << brojKreveta << "";
                    cout << left << setw(15) << brojSoba << endl;
                    ima=true;
                }
            }
        }else{
            cout<<"[GRESKA] Nema unesenih smjestaja!";
            cout<<"\n[ENTER] za povratak";
            return;
        }
        if(ima==false){
            cout<<"\nZao nam je. Nemamo odgovarajuci smjestaj za vas.\n";
            cout<<"[ENTER] za povratak";
        }

        char yn;
        if(ima==true){
            cout<<"\nDa li zelite rezervisani sobu?[Y/N]";
            cin>>yn;
            if(yn=='Y' || yn=='y'){
                system("cls");
                rezervacija();
            }else{
                cout<<"\n[ENTER] za povratak";
        }
        }

    }
};

bool login(string user, string pw){
    string userTemp,pwTemp;
    int brojac=3;
    while(brojac>0){
        cout<<"Username: ";
        cin>>userTemp;
        cout<<"Password: ";
        cin>>pwTemp;


        if(userTemp.compare(user)!=0 || pwTemp.compare(pw)!=0){
            if(brojac==1){
                return 0;
            }else{
                cout<<"Uneseni podaci su netacni. Pokusajte ponovno.\n";
                cout<<"Prestalo pokusaja: "<< --brojac<<endl<<endl;
            }
        }else{
            return 1;
        }
    }
}

void prikaziMeniAdmin(){
    system("cls");
	cout << "----------------------------------------------\n";
	cout << "\t\tMeni:\n";
	cout << "----------------------------------------------\n";
	cout << "\t1. Unos novog smjestaja\n";
	cout << "\t2. Pregled smjestaja\n";
	cout << "\t3. Statistika\n";
    cout << "\t4. Odjava\n";
	cout << "----------------------------------------------\n";
}

void prviMeni(){

	cout << "----------------------------------------------\n";
	cout << "\t\tMeni:\n";
	cout << "----------------------------------------------\n";
	cout << "\t1. Admin\n";
	cout << "\t2. Guest\n";
    cout << "\t3. Odjava\n";
	cout << "----------------------------------------------\n";
}

void guestMeni(){

	cout << "----------------------------------------------\n";
	cout << "\t\tMeni:\n";
	cout << "----------------------------------------------\n";
	cout << "\t1. Pregled smjestaja\n";
	cout << "\t2. Rezervacija\n";
	cout << "\t3. Pretraga smjestaja\n";
    cout << "\t4. Odjava\n";
	cout << "----------------------------------------------\n";
}


int main(){

    int izbor1;
    int izbor2;
    int izbor3;
    int izborG;
    smjestaj s;
    registracija r;
    char crtica[]="-----------------------------------------------------";
    bool registrovan=false;


    do{
        do{
            system("cls");

            cout<<"\t"<<crtica<<endl;
            cout<<"\t|   Dobro dosli u program za evidenciju smjestaja.  |\n";
            cout<<"\t"<<crtica<<endl<<endl;

            prviMeni();
            do{
            cout<<"Izbor: ";
            cin>>izbor1;
            }while(provjera(izbor1)==false);




            if(izbor1==1){
                    while(!registrovan){
                        system("cls");
                        cout<<"\t--------------------------\n";
                        cout<<"\t|\tREGISTRACIJA\t |\n";
                        cout<<"\t--------------------------\n";
                        cout<<crta;
                        cout<<"Unesite username: ";
                        cin>>r.username;
                        cout<<"Unesite password: ";
                        cin>>r.password;
                        cout<<"\n\t------------------------";
                        cout<<"\n\tRegistracija je uspjesna!";
                        cout<<"\n\t------------------------\n";
                        cout<<"\n[ENTER] za nastavak!";
                        registrovan=true;
                        system("pause");
                    }

                    system("cls");

                    cout<<crta;
                    cout << "\tMolimo vas ulogujte se:\n";
                    cout << crta;

                    if(login(r.username,r.password)==1){
                        do{
                            do{
                                system("cls");
                                prikaziMeniAdmin();
                                do{
                                cout<<"Izbor: ";
                                cin>>izbor3;
                                }while(provjera(izbor3)==false);
                                if(izbor3==1){
                                    system("cls");
                                    cout << crta;
                                    cout << "\tUnos novog smjestaja:\n";
                                    cout << crta;
                                    s.unosSmjestaja();
                                }else if(izbor3==2){
                                    system("cls");
                                    cout << crta;
                                    cout << "\tPregled unesenih smjestaja:\n";
                                    cout << crta;
                                    s.pregledSmjestajaAdmin();
                                    cout<<endl;
                                    system("pause");
                                }else if(izbor3==3){
                                    system("cls");
                                    cout << crta;
                                    cout << "\tStatistika:\n";
                                    cout << crta;
                                    s.statistika();
                                    cout<<endl;
                                    system("pause");
                                }

                            }while(izbor3!=4);
                        }while(izbor3<1 || izbor3>4);
                    }else{
                        registrovan=false;
                    }

            }else if(izbor1==2){
                do{
                    do{
                        system("cls");
                        guestMeni();
                        do{
                        cout<<"Izbor: ";
                        cin>>izborG;
                        }while(provjera(izborG)==false);
                        if(izborG==1){
                            system("cls");
                            s.pregledSmjestajGuest();
                            cout<<endl;
                            system("pause");
                        }else if(izborG==2){
                            system("cls");
                            s.rezervacija();
                            cout<<endl;
                            system("pause");
                        }else if(izborG==3){
                           system("cls");
                           s.pretragaSmjestaja();
                           system("pause");

                        }else if(izborG==4){
                            system("cls");
                            cout<<"Hvala na koristenju naseg programa.\n";
                        }


                    }while(izborG!=4);
                }while(izborG<1 || izborG>4);
            }else if(izbor1==3){
                system("cls");
                cout<<"\t-----------------------"<<endl;
                cout<<"\t|   Hvala Vam.        |\n";
                cout<<"\t|   Vidimo se uskoro. |\n";
                cout<<"\t-----------------------"<<endl;
            }
        }while(izbor1!=3);
    }while(izbor1<1 || izbor1>3);


    return 0;
}

