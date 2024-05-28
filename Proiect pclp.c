/*
        Last update: 01.01.2024
*/
/* Proiect PCLP Pentru Data De 3 Ianuarie 2024


    Titlu:Portal de inregistrare al vaccinurilor

    Cerinta:
        Scrieti un program pentru a construi un portal de inregistrare a vaccinarii impotriva Covid-19 bazat pe meniu folosind C
    si care poate efectua urmatoarele operatiuni:
    1) Inregistrarea numelor candidatilor.
    2) Data, ora si locul pentru vaccinare.
    3) Anuntarea datei candidatilor pentru rapel.
    4) Tiparirea bonului de vaccinare.
    5) Cautarea unui candidat pentru informatii: data vaccinarii, tipul vaccinului, rapel, etc.
    6) Afisarea in timp real a nr de vaccinuri utlizate


    Autori:

    1. Zugravu Cristina-Vasilica, Universitatea din Craiova, Facultatea de Automatica, Calculatoare si Electronica, Calculatoare Romana, grupa CR1.2B
    2. Stoian Cristian-Georgian, Universitatea din Craiova, Facultatea de Automatica, Calculatoare si Electronica, Calculatoare Romana, grupa CR1.2B

*/

/*
        Exemplu comanda:

        inregistrare
        ispasoiu robert
        04.01.2024
        16:00
        Bucuresti
        Pfizer
        STOP

        sau

        inregistrare
        Stoian Cristian Georgian
        23.12.2023
        23:59
        Craiova
        Moderna
        inregistrare
        Zugravu Cristina-Vasilica
        23.12.2024
        09:39
        Bucuresti
        Sinopharm
        baza
        STOP

        comanda time -> verifica daca un vaccin se va efectua pe data respectiva


*/

/*

    Vom considera ca fiecare persoana are o data diferita de vaccinare (precum si rapelul), astfel nu exista 2 persoane care sa se vaccineze in aceeasi zi.

    Vom considera ca persoanele inregistrate sunt vaccinate in ziua respectiva, astfel numarul de vaccinuri utilizate (FARA RAPEL) = numar persoane inregistrate

    Vom considera ca persoanele nu au acelasi nume (ID), fiecare persoana numindu-se diferit. Insa diferenta de un singur pronume este acceptata

    ex: AB CD EF != AB CD

*/
/*
                       Tipuri de vaccinuri:

        1) AstraZeneca
        2) Pfizer
        3) Moderna
        4) Sinopharm
        5) Sputnik-V (Gam-COVID-Vac)
        6) CoronaVac
        7) Janssen/Johnson & Johnson

*/

/*
        INPUT 1:
        inregistrare -> inregistram prima persoana
        Stoian Cristian Georgian
        24.12.2023
        05:22
        Craiova
        CoronaVac
        inregistrare -> inregistram a doua persoana
        Zugravu Cristina-Vasilica
        24.12.2024
        05:23
        Bucuresti
        AstraZeneca
        baza -> ne afiseaza numarul de vaccinuri utilizate(FARA RAPEL!!) (acestea reprezentand numarul de candidati inregistrati in baza de date datorita faptului ca momentul in care persoana este inregistrata, aceasta este si vaccinata)
        (CE NE AFISEAZA CAND INTRODUCEM "baza"):

    OUTPUT: In total avem un numar de 2 candidati, iar persoanele inregistrate in baza de date sunt:
    Stoian Cristian Georgian
    Zugravu Cristina-Vasilica

    back to INPUT: time
        24.12.2023
    OUTPUT:
    Pe data de 24.12.2023 se va vaccina persoana cu numele Stoian Cristian Georgian la ora 05:22, iar vaccinul se va efectua la locatia: Craiova
    back to INPUT: rapel
    25.11.2025
    25.11.2026
    anunta
    Stoian Cristian Georgian
    OUTPUT:Candidatul va efectua rapelul pe data de: 25.11.2025
    INPUT: anunta
    Zugravu Cristina-Vasilica
    OUTPUT:Candidatul va efectua rapelul pe data de 25.11.2026
    INPUT:STOP -> programul se va opri



        INPUT2:

        O sa facem input-uri si output-uri separate.


*/
#include <stdio.h>
#include <stdlib.h>
#define DIM 105  ///putem schimba dimensiunea in functie de cate vaccinuri vrem sa efectuam, pentru proiectul nostru il vom considera ~100
char comanda[DIM];
int nr_vaccinari_utilizate=0;
int nr_candidati=0;
char nume_candidat[DIM];
char baza_de_date_candidati[DIM][DIM]; /// baza_de_date_candidati[numarul_candidatului][lungime nume]
void afisare_candidati(char baza_de_date_candidati[DIM][DIM],int nr_candidati)
{
    for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati;numarul_candidatului++) ///afisarea tuturor candidatilor inregistrati in baza de date
    {
        printf("%s\n",baza_de_date_candidati[numarul_candidatului]);
    }
}
char data[DIM][15]; ///data[numarul_candidatului][lungime data] : ex: 23.04.2004
char ora[DIM][10]; ///ora[numarul_candidatului] la care va avea loc vaccinul
char locatie[DIM][30]; ///locatia unde va avea loc vaccinul : locatie[candidat][dimensiune locatie] : ex. Facultatea de Drept
char check_date[15];
char rapel_candidat[DIM][15];
char check_candidate[15];
char cauta_candidat[15];
char tip_vaccin[DIM][30];
char look_for_candidate[30];
int numar_vaccinari_cu_Pfizer=0;
int numar_vaccinari_cu_Moderna=0;
int numar_vaccinari_cu_AstraZeneca=0;
int numar_vaccinari_cu_Sinopharm=0;
int numar_vaccinari_cu_CoronaVac=0;
int numar_vaccinari_cu_Janssen=0;
int numar_vaccinari_cu_Sputnik=0;
char cauta_vaccin[30];
int main (){
    printf("Introduceti prima comanda: ");
    scanf("%s",&comanda);
    getchar();
    while(strcmp(comanda,"STOP")!=0){ ///cand scriem "STOP", programul se va opri din a introduce comenzi
        if(strcmp(comanda,"inregistrare")==0) ///daca comanda = inregistrare, vom introduce numele candidatului in baza de date
        {
            nr_candidati++;
            printf("Introduceti numele: ");
            fgets(baza_de_date_candidati[nr_candidati],DIM,stdin);
            int last_character=strlen(baza_de_date_candidati[nr_candidati])-1;
            baza_de_date_candidati[nr_candidati][last_character]=NULL;
            printf("Introduceti data vaccinarii: ");
            fgets(data[nr_candidati],DIM,stdin); ///ii atribuim o data de vaccinare candidatului
            int last_character2=strlen(data[nr_candidati])-1;
            data[nr_candidati][last_character2]=NULL;
            printf("Introduceti ora vaccinarii: ");
            fgets(ora[nr_candidati],DIM,stdin); ///ii atribuim o ora de vaccinare candidatului
            int last_character3=strlen(ora[nr_candidati])-1;
            ora[nr_candidati][last_character3]=NULL;
            printf("Introduceti locatia unde se va efectua vaccinul: ");
            fgets(locatie[nr_candidati],DIM,stdin); ///ii atribuim o locatie unde va avea loc vaccinul candidatului
            int last_character4=strlen(locatie[nr_candidati])-1;
            locatie[nr_candidati][last_character4]=NULL;
            printf("Introduceti tipul de vaccin care se va utiliza: ");
            fgets(tip_vaccin[nr_candidati],DIM,stdin); ///ii atribuim tipul vaccinului
            int last_character_forgotnumber=strlen(tip_vaccin[nr_candidati])-1;
            tip_vaccin[nr_candidati][last_character_forgotnumber]=NULL;
            if(strcmp(tip_vaccin[nr_candidati],"Pfizer")==0)
                numar_vaccinari_cu_Pfizer++;
            else
                if(strcmp(tip_vaccin[nr_candidati],"Moderna")==0)
                    numar_vaccinari_cu_Moderna++;
                else
                    if(strcmp(tip_vaccin[nr_candidati],"CoronaVac")==0)
                        numar_vaccinari_cu_CoronaVac++;
                    else
                        if(strcmp(tip_vaccin[nr_candidati],"AstraZeneca")==0)
                            numar_vaccinari_cu_AstraZeneca++;
                        else
                            if(strcmp(tip_vaccin[nr_candidati],"Sputnik-V")==0 || strcmp(tip_vaccin[nr_candidati],"Gam-Covid-Vac")==0)
                                numar_vaccinari_cu_Sputnik++;
                            else
                                if(strcmp(tip_vaccin[nr_candidati],"Sinopharm")==0)
                                    numar_vaccinari_cu_Sinopharm++;
                                else
                                    if(strcmp(tip_vaccin[nr_candidati],"Janssen")==0 || strcmp(tip_vaccin[nr_candidati],"Johnson")==0 || strcmp(tip_vaccin[nr_candidati],"Johnson & Johnson")==0)
                                        numar_vaccinari_cu_Janssen++;

        }
        if(strcmp(comanda,"time")==0) ///daca comanda = time, vom afisa numele candidatului care se va vaccina pe data respectiva, precum si ora si locatia sa.
        {
           printf("Introduceti data vaccinarii: ");
           fgets(check_date,DIM,stdin);
           int last_character5=strlen(check_date)-1;
           check_date[last_character5]=NULL;
           int found=0; ///variabila found ne va spune daca am gasit sau nu candidatul respectiv in baza de date
           for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati;numarul_candidatului++)
           {
               if(strcmp(data[numarul_candidatului],check_date)==0) ///verificam daca pe data check_date se vaccineaza un candidat comparand data fiecaruia
               {
                   found=1;
                   printf("Pe data de %s",check_date);
                   printf(" se va vaccina persoana cu numele %s",baza_de_date_candidati[numarul_candidatului]);
                   printf(" la ora %s",ora[numarul_candidatului]);
                   printf(" , iar vaccinul se va efectua la locatia: %s",locatie[numarul_candidatului]);
               }
           }
           if(found==0)
           {
               printf("Pe data de %s",check_date);
               printf(" nu se va vaccina nimeni");
           }
           printf("\n");
        }
        /*
            Comanda baza are rolul de a ne afisa persoanele inregistrate in baza de date, precum si sa ne spuna NUMARUL de persoane inregistrate.
        */
        if(strcmp(comanda,"baza")==0)
        {
            printf("In total avem un numar de %d",nr_candidati);
            printf(" candidati");
            printf(", iar persoanele inregistrate in baza de date sunt:\n");
            afisare_candidati(baza_de_date_candidati,nr_candidati);
            printf("\n");
        }
        if(strcmp(comanda,"rapel")==0)
        {
            for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati;numarul_candidatului++)
            {
                printf("Introduceti data cand se va efectua rapelul pentru candidatul cu numarul ");
                printf("%d",numarul_candidatului);
                printf(":");
                fgets(rapel_candidat[numarul_candidatului],DIM,stdin);
                int last_character6=strlen(rapel_candidat[numarul_candidatului])-1;
                rapel_candidat[numarul_candidatului][last_character6]=NULL;
                printf("\n");
            }
        }
        if(strcmp(comanda,"anunta")==0)
        {
            printf("Introduceti numele candidatului:");
            fgets(check_candidate,DIM,stdin);
            int last_character7=strlen(check_candidate)-1;
            check_candidate[last_character7]=NULL;
            printf("\n");
            for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati;numarul_candidatului++)
            {
                if(strcmp(baza_de_date_candidati[numarul_candidatului],check_candidate)==0)
                {
                    printf("Candidatul va efectua rapelul pe data de: ");
                    printf("%s",rapel_candidat[numarul_candidatului]);
                }
            }
            printf("\n");
        }
        /*
            comanda search ne va cauta un candidat in baza de date si ne va afisa informatiile acestuia.
        */
        if(strcmp(comanda,"search")==0)
        {
            printf("Introduceti numele candidatului pe care-l cautati: ");
            fgets(look_for_candidate,DIM,stdin);
            look_for_candidate[strlen(look_for_candidate)-1]=NULL;
            for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati;numarul_candidatului++)
            {
                if(strcmp(baza_de_date_candidati[numarul_candidatului],look_for_candidate)==0){
                    printf("Candidatul se va vaccina pe data de ");
                    printf("%s",data[numarul_candidatului]);
                    printf("\n");
                    printf("Ora la care se va vaccina este: ");
                    printf("%s",ora[numarul_candidatului]);
                    printf("\n");
                    printf("Locul unde va avea loc vaccinarea este: ");
                    printf("%s",locatie[numarul_candidatului]);
                    printf("\n");
                    printf("Tipul vaccinului este: ");
                    printf("%s",tip_vaccin[numarul_candidatului]);
                    printf("\n");
                    printf("Data pe care isi va face rapelul este: ");
                    printf("%s",rapel_candidat[numarul_candidatului]);
                }
            }
            printf("\n");
        }
        /*
            tiparirea bonului de vaccinare pentru o persoana aleasa de catre noi
        */
        if(strcmp(comanda,"tiparire")==0)
        {
            printf("Pentru ce persoana doriti sa tipariti bonul de vaccinare?");
            printf("\n");
            fgets(nume_candidat,DIM,stdin);
            int last_character_idk=strlen(nume_candidat)-1;
            nume_candidat[last_character_idk]=NULL;
            printf("Vom tipari bonul pentru ");
            printf("%s",nume_candidat);
            printf(":\n");
            for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati;numarul_candidatului++)
            {
                if(strcmp(baza_de_date_candidati[numarul_candidatului],nume_candidat)==0)
                {
                    /*
                    printf("%s",numarul_candidatului);
                    printf(":\n");
                    */
                    printf("Data la care a fost efectuata vaccinarea este: ");
                    printf("%s",data[numarul_candidatului]);
                    printf("\n");
                    printf("Ora la care a fost efectuata vaccinarea este: ");
                    printf("%s",ora[numarul_candidatului]);
                    printf("\n");
                    printf("Locatia unde s-a efectuat vaccinul este: ");
                    printf("%s",locatie[numarul_candidatului]);
                    printf("\n");
                    printf("Tipul vaccinului utilizat este: ");
                    printf("%s",tip_vaccin[numarul_candidatului]);
                    printf("\n");
                }
            }
            printf("\n");
        }
        /*
                O sa facem o comanda bonus care sa ne spuna numarul total de vaccinuri in care s-au utilizat:
            1) AstraZeneca
            2) Pfizer
            3) Moderna
            4) Sinopharm
            5) Sputnik-V (Gam-COVID-Vac)
            6) CoronaVac
            7) Janssen/Johnson & Johnson
        */
        if(strcmp(comanda,"vaccinuri")==0)
        {
            printf("Introduceti tipul de vaccin pe care doriti sa-l cautati: ");
            fgets(cauta_vaccin,DIM,stdin);
            int last_character_numaistiucare=strlen(cauta_vaccin)-1;
            cauta_vaccin[last_character_numaistiucare]=NULL;
            int gasit_vaccin=0; ///daca s-a facut sau nu vaccinul respectiv
            printf("\n");
            for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati && gasit_vaccin==0;numarul_candidatului++)
            {
                if(strcmp(tip_vaccin[numarul_candidatului],cauta_vaccin)==0)
                {
                    gasit_vaccin=1;
                    printf("Vaccinul cunoscut cu numele de ");
                    printf("%s",cauta_vaccin);
                    printf(" a fost efectuat la un numar de ");
                    if(strcmp(cauta_vaccin,"Pfizer")==0)
                        printf("%d",numar_vaccinari_cu_Pfizer);
                    else
                        if(strcmp(cauta_vaccin,"Moderna")==0)
                            printf("%d",numar_vaccinari_cu_Moderna);
                        else
                            if(strcmp(cauta_vaccin,"CoronaVac")==0)
                                printf("%d",numar_vaccinari_cu_CoronaVac);
                            else
                                if(strcmp(cauta_vaccin,"AstraZeneca")==0)
                                    printf("%d",numar_vaccinari_cu_AstraZeneca);
                                else
                                    if(strcmp(cauta_vaccin,"Sputnik-V")==0 || strcmp(cauta_vaccin,"Gam-Covid-Vac")==0)
                                        printf("%d",numar_vaccinari_cu_Sputnik);
                                    else
                                        if(strcmp(cauta_vaccin,"Sinopharm")==0)
                                            printf("%d",numar_vaccinari_cu_Sinopharm);
                                        else
                                            if(strcmp(cauta_vaccin,"Janssen")==0 || strcmp(cauta_vaccin,"Johnson")==0 || strcmp(cauta_vaccin,"Johnson & Johnson")==0)
                                                printf("%d",numar_vaccinari_cu_Janssen);
                    printf(" candidati");
                }
            }
            printf("\n");
        }
        /*
            ///Update: nr de vaccinuri utilizate reprezinta numarul de candidati * 2, deoarece persoanele sunt vaccinate in momentul inregistrarii + rapel

            Update 01.01.2024: Am reparat comanda, astfel numarul de vaccinuri utilizate este schimbat.
            Daca inregistram o persoana, iar apoi ii atribuim o data de rapel, urmand sa inregistram a 2-a persoana. Nr vaccinuri utilizate = (1->inregistrare+vaccinare prima persoana, +1 -> rapel prima persoana, +1 ->inregistrare a 2-a persoana)
        */
        if(strcmp(comanda,"total")==0)
        {
            printf("Numarul de vaccinuri utilizate in total este: ");
            for(int numarul_candidatului=1;numarul_candidatului<=nr_candidati;numarul_candidatului++)
            {
                if(strlen(rapel_candidat[numarul_candidatului])>9)
                    nr_vaccinari_utilizate++;
            }
            printf("%d",nr_vaccinari_utilizate+nr_candidati);
            printf("\n");
        }
        printf("\n");
        printf("Introduceti urmatoarea comanda: ");
        scanf("%s",&comanda);
        getchar();
    }
    return 0;
}
