#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>

//Creation d'un Noeud
typedef struct Compte Compte;
    struct Compte{
        int numero;
        char date_create[11];
        char nom[30];
        char prenom[30];
        int telephone;
        char email[60];
        float montant;
        char etat;
        int pin;
        Compte *suiv;
    };

    //Creation de la liste chainee
typedef struct Liste_compte Liste_compte;
    struct Liste_compte{
        Compte *premier;
    };

    //Initialiser la liste a NULL
void init_Liste_compte(Liste_compte *L){
    L->premier = NULL;
}

// Permet de positionner le curseur de souris sur l'écran à l'endroit
// de coordonnées x,y
void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    fflush(stdout);
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

// Fonction pour dessiner un rectangle
void rectangle(int x, int y, int lon, int haut)
{
     int i;
     gotoxy(x,y); printf("%c",218);
     gotoxy(x+lon,y); printf("%c",191);
     gotoxy(x, y+haut); printf("%c",192);
     gotoxy(x+lon, y+haut); printf("%c",217);
     for (i=1; i<lon;i++)
     {
         gotoxy(x+i,y); printf("%c",196);
         gotoxy(x+i,y+haut); printf("%c",196);
     }
     for (i=1; i<haut;i++)
     {
         gotoxy(x,y+i); printf("%c",179);
         gotoxy(x+lon,y+i); printf("%c",179);
     }
}

//Pour définir une couleur de texte et une couleur de fond du texte.
void Color(int t,int f)
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,f*16+t);
}

//Affichage d'un compte
void affi_Compte(Compte C){
    rectangle(16, 2, 53, 28);
    rectangle(43, 6, 0, 22);
    gotoxy(19,7);printf("NUMERO ");
    gotoxy(44,7);printf("=> %d",C.numero);
    gotoxy(19,10);printf("DATE CREATION");
    gotoxy(44,10);printf("=> %s",C.date_create);
    gotoxy(19,13);printf("NOM");
    gotoxy(44,13);printf("=> %s",C.nom);
    gotoxy(19,16);printf("PRENOMS");
    gotoxy(44,16);printf("=> %s",C.prenom);
    gotoxy(19,19);printf("TELEPHONE ");
    gotoxy(44,19);printf("=> %d",C.telephone);
    gotoxy(19,22);printf("EMAIL ");
    gotoxy(44,22);printf("=> %s",C.email);
    gotoxy(19,25);printf("ETAT (A=actif/B=Bloque)");
    gotoxy(44,25);printf("=> %c",C.etat);
    gotoxy(19,28);printf("Pin: ");
    gotoxy(44,28);printf("=> ********");
    gotoxy(19,33);
}

//Cacher le mot de passe lors de l'inscription d'un compte
void cacherPasse(int *pass){
    char pwd[9];
    char pwd1[9];
    char pd;
    int k=19,l=22,k1=18,l1=21;
    int i =0,j=0, modif = 0;
    do{
        rectangle(44, k1, 16, 2);
        gotoxy(19,k);printf("Votre pin (Ex: 12345678): ");
        for(i=0; i<8; i++){
            fflush(stdin);
            pd = getch();
        pwd[i] = pd;
        pd = '*';
        printf("%c",pd);
        }
        rectangle(47, l1, 13, 2);
        gotoxy(19,l);printf("Confirmation du mot de passe ");
        for(i=0; i<8; i++){
            fflush(stdin);
        pd = getch();
        pwd1[i] = pd;
        pd = '*';

    printf("%c",pd);
    }
    *pass = atoi(pwd);
    int pass1 = atoi(pwd1);

    if(*pass == pass1){
            modif = 1;
    }else{
    *pass = -1;
    j++;
    k = k+6;
    l = l+6;
    k1 = k1+6;
    l1 = l1+6;
    }
 }while(j<2 && ! modif);
 system("cls");
}

//Cacher le mot de passe lors de l'authentification d'un compte
int validation(){
    char pwd[9];
    char pd;
    int pass;
    int i =0,j=0, modif = 0;
        printf("Entrez le mot de passe (8 caractere)");
        for(i=0; i<8; i++){
            fflush(stdin);
            pd = getch();
        pwd[i] = pd;
        pd = '*';
        printf("%c",pd);
        pass = atoi(pwd);
    }
    return pass;
}
int numeroValide(){
    char tel[8];
    printf("Telephone: (Ex: 62869062)  ");
    scanf("%[^\n]",tel);
    size_t length = strlen(tel);

    int c = 1;
    for(int i=0;i<length;i++){
        if(! isdigit(tel[i])|| !isdigit(tel[7])!=0){
           c= -1;
        }
    }
    if(c==1){
        c=atoi(tel);
    }
    return c;
}
//Ajouter des comptes a la liste chainee(FILE)
void ajouter_Liste(Liste_compte *L, Compte C){
    Compte *N = malloc(sizeof(Compte));

    N->numero = C.numero;
    strcpy(N->date_create,C.date_create);
    strcpy(N->nom,C.nom);
    strcpy(N->prenom,C.prenom);
    N->telephone = C.telephone;
    strcpy(N->email,C.email);
    N->montant = C.montant;
    N->etat = C.etat;
    N->pin = C.pin;
    N->suiv = NULL;

    if(L->premier != NULL){
        Compte *ptr = L->premier;
        while(ptr->suiv != NULL){
            ptr = ptr->suiv;
        }
    ptr->suiv = N;
    }
    else{
        L->premier = N;
    }
}

//Gestion de la date local
void date_Local(char date[]){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char j[3];
    char m[3];
    char a[5];
    char date_actuel[11] = "";
    itoa(tm.tm_year+1900,a,10);
    itoa(tm.tm_mon+1,m,10);
    itoa(tm.tm_mday,j,10);
    strcat(date_actuel,j);
    strcat(date_actuel,"-");
    strcat(date_actuel,m);
    strcat(date_actuel,"-");
    strcat(date_actuel,a);
    strcpy(date,date_actuel);
}
//Copier les donnees de la liste dans le fichier
void copier_Compte_Dans_Le_Fichier(Liste_compte *L){
    FILE *Fichier;
    Fichier = fopen("inscrire.txt","w");
    Compte *ptr = L->premier;

        while(ptr != NULL){
            fprintf(Fichier,"%d %s %s %s %d %s %f %c %d \n",ptr->numero,ptr->date_create,ptr->nom,ptr->prenom,ptr->telephone,ptr->email,ptr->montant,ptr->etat,ptr->pin);
            ptr = ptr->suiv;
        }
    fclose(Fichier);
}
//Creation d'un compte
void creer_Un_Compte(Liste_compte *L, Compte *C){
    FILE *fichier;
    fichier = fopen("inscrire.txt","a+");
    int c,i =0;

    while((c=fgetc(fichier)) != EOF){
        if(c=='\n')
            i++;
    }
    rectangle(17, 3, 43, 2);
    gotoxy(27,4);Color(11,0);printf("ENTREZ LES INFORMATIONS\n");
    Color(15,0);
    rectangle(27, 6, 33, 2);
    gotoxy(19,7);printf("Nom:     ");
    scanf("%s",&C->nom);
    fflush(stdin);
    rectangle(27, 9, 33, 2);
    gotoxy(19,10);printf("Prenom:  ");
    scanf("%s",&C->prenom);
    fflush(stdin);
    rectangle(45, 12, 15, 2);
    gotoxy(19,13);C->telephone=numeroValide();
    if(C->telephone<0){
        system("cls");
        printf("Telephone invalide\n");
        system("pause");
        system("cls");
    }else{
    fflush(stdin);
    rectangle(27, 15, 33, 2);
    gotoxy(19,16);printf("Email:   ");
    scanf("%s",&C->email);
    fflush(stdin);
    cacherPasse(&C->pin);
    if(C->pin < 0){
            Color(12,0);
            rectangle(34,24,25,2);
            gotoxy(36,25);printf("Confirmation invalide\n");
        }
    else{
    C->numero = i+1;
    char date[11];
    date_Local(date);
    strcpy(C->date_create,date);
    C->montant = 0;
    C->etat = 'A';
    system("cls");
    rectangle(22, 3, 43, 2);
    gotoxy(29,4);Color(11,0);printf("VOICI LES INFORMATIONS");
    Color(15,0);
    affi_Compte(*C);
    fflush(stdin);
    char reponse;
    gotoxy(18,34);printf("Souhaitez-vous modifier une informations (o/n) ? ");
    scanf("%c",&reponse);
    system("cls");
    if(reponse == 'o'){
        do {
        fflush(stdin);
        system("cls");
        gotoxy(17,3);printf("______________________________________");
        gotoxy(19,5);printf("1 - Pour changer le nom.");
        gotoxy(19,7);printf("2 - Pour changer le prenom.");
        gotoxy(19,9);printf("3 - Pour changer l'email.");
        gotoxy(19,11);printf("4 - Pour changer le pin.");
        gotoxy(19,13);printf("5 - Quitter");
        int choix;
        fflush(stdin);
        gotoxy(17,18);printf("_______________________________________");
        gotoxy(19,17);printf("Quel est votre choix (1 2 3 4 5):");
        scanf("%d",&choix);
        fflush(stdin);

            switch(choix){
            case 1 :
                gotoxy(19,21);printf("Changer %s en : ",C->nom);
                scanf("%s",&C->nom);
            break;
            case 2 :
                gotoxy(19,21);printf("Changer %s en : ",C->prenom);
                scanf("%s",&C->prenom);
            break;
            case 3 :
                gotoxy(19,21);printf("Changer %s en : ",C->email);
                scanf("%s",&C->email);
            break;
            case 4 :
                    cacherPasse(&C->pin);
                    if(C->pin < 0){
                            rectangle(32,30,27,3);
                            gotoxy(34,32);printf("Confirmation invalide");
                        }
            break;
            case 5 :
                gotoxy(19,24);printf("Quitter");
            break;
            default :
                gotoxy(19,23);printf("Entrez un numero entre 1 et 5");
            break;
            }
            fflush(stdin);
        gotoxy(19,26);printf("Modifier encore (o/n) ? ");
        scanf("%c",&reponse);
        system("cls");
        }while(reponse == 'o');
    }
        ajouter_Liste(&(*L),*C);
        copier_Compte_Dans_Le_Fichier(&(*L));
        Color(2,0);
        rectangle(32,25,27,2);
        gotoxy(38,26);printf("Inscription valide");
        Color(15,0);
    fclose(fichier);
    }
    }
}

//Transfert des donnees dans la liste afin de facilte les modifications
void transfert_donnees(Liste_compte *L){

    Compte C;
    int numero;
    char date_create[11];
    char nom[30];
    char prenom[30];
    int telephone;
    char email[60];
    float montant;
    char etat;
    int pin;

    FILE *Fichier;
    Fichier = fopen("inscrire.txt","a+");
    fseek(Fichier,0,0);
    init_Liste_compte(&(*L));
    while((fscanf(Fichier,"%d %s %s %s %d %s %f %c %d",&numero,&date_create,&nom,&prenom,&telephone,&email,&montant,&etat,&pin)) != EOF){
        C.numero = numero;
        strcpy(C.date_create,date_create);
        strcpy(C.nom,nom);
        strcpy(C.prenom,prenom);
        C.telephone = telephone;
        strcpy(C.email,email);
        C.montant = montant;
        C.etat = etat;
        C.pin = pin;

        ajouter_Liste(&(*L),C);
    }
    fclose(Fichier);
}



//Recuperation du numero du compte
int numero_id(){
    int num;
    printf("Entrez le numero du compte: ");
    scanf("%d",&num);
    return num;
}

//Authentification d'un compte
int identification(Liste_compte *L, int *num){
    int modif = 0,modif1=0, pin=0, i=0;
    Color(13,0);
    printf("AUTHENTIFICATION");
    Color(15,0);
    gotoxy(1,9);printf("   Entrez le numero du compte: ");
    scanf("%d",&(*num));
    printf("\n");
    Compte *ptr = L->premier;
    do{
        if(ptr->numero == *num && ptr->etat != 'B'){
                modif = 1;
                do{
                    pin = validation();
                    if(ptr->pin == pin){
                        modif1 = 1;
                        printf("\nAuthentification valide\n");
                    }
                    else{
                        printf("\nMot de passe invalide.\n");
                        i++;
                    }
                }while(i<3 && ! modif1);
                if(!modif1){
                 ptr->etat = 'B';
                 printf("Compte bloque.\n");
                 *num = -1;
                }
                copier_Compte_Dans_Le_Fichier(&(*L));
        }else{
            ptr = ptr->suiv;
        }
    }while(ptr != NULL && ! modif);
    if(!modif){
        *num = -1;
        rectangle(1, 10, 40, 8);
        gotoxy(3,12);printf("Le compte n'est pas disponible.");
        gotoxy(3,14);printf("Ou votre compte a ete bloque.");
        gotoxy(3,16);printf("Merci");
        gotoxy(3,20);
    }
return *num;
}
 //Rechercher un compte
void rechercher_Un_Compte(Liste_compte *L){
    int num =0, modif = 0;
    int choix;
    char nom2[30];
    rectangle(17, 3, 43, 4);
    rectangle(16, 2, 45, 18);
    gotoxy(30,2);Color(13,0);printf("TYPE DE RECHERCHE");
    Color(15,0);
    gotoxy(25,4);printf("1 - Avec le Numero");
    gotoxy(25,6);printf("2 - Avec le Nom");
    gotoxy(19,8);printf("Votre choix : ");
    scanf("%d",&choix);
    switch(choix){
    case 1 :
        system("cls");
    rectangle(17, 3, 43, 4);
    rectangle(16, 2, 45, 26);
    gotoxy(23,5);num = numero_id();
    system("cls");
    Compte *ptr = L->premier;
    //Recherche avec le numero
    do{
        if(ptr->numero == num){
            modif = 1;
                rectangle(16, 2, 45, 26);
                Color(11,0);
                rectangle(17, 3, 43, 2);
                gotoxy(32,4);
                printf("COMPTE TROUVER");
                Color(15,0);
                rectangle(43, 6, 0, 22);
                gotoxy(19,7);printf("Numero ");
                gotoxy(44,7);printf("=> %d",ptr->numero);
                gotoxy(19,10);printf("Date_Create ");
                gotoxy(44,10);printf("=> %s",ptr->date_create);
                gotoxy(19,13);printf("Nom ");
                gotoxy(44,13);printf("=> %s",ptr->nom);
                gotoxy(19,16);printf("Prenom");
                gotoxy(44,16);printf("=> %s",ptr->prenom);
                gotoxy(19,19);printf("Telephone ");
                gotoxy(44,19);printf("=> %d",ptr->telephone);
                gotoxy(19,22);printf("Email ");
                gotoxy(44,22);printf("=> %s",ptr->email);
                gotoxy(19,25);printf("Etat  (A=actif/B=Bloque)");
                gotoxy(44,25);printf("=> %c",ptr->etat);
                gotoxy(19,31);
        }else{
            ptr = ptr->suiv;
        }
    }while(ptr != NULL && ! modif);
        if(!modif){
            Color(12,0);
            rectangle(12, 7, 56, 4);
            Color(15,0);
            gotoxy(16,9);printf("Le compte recherche n'est pas disponible. Merci !!!");
            gotoxy(19,20);
        }
    break;

    //Recherche avec le nom
    case 2 :
    gotoxy(19,9);printf("_________________________________________");
    gotoxy(19,11);printf("ENTRER LE NOM : ");
    scanf("%s",&nom2);
    system("cls");

    int numero;
    char date_create[11];
    char nom[30];
    char prenom[30];
    int telephone;
    char email[60];
    float montant;
    char etat;
    int pin;
    int j = 7;

    FILE *Fichier;
    Fichier = fopen("inscrire.txt","r");

        fseek(Fichier,0,0);
        rectangle(5,2,58,3);
        gotoxy(15,3);Color(11,0);printf("LISTE DES COMPTES AVEC NOM: %s",nom2);
        Color(15,0);

    while((fscanf(Fichier,"%d %s %s %s %d %s %f %c %d",&numero,&date_create,&nom,&prenom,&telephone,&email,&montant,&etat,&pin)) != EOF){
        if(strcmp(nom,nom2) == 0){
            j = j+3;
            gotoxy(5,j);printf("%d    %s    %s    %c    %d    %s",numero,nom,prenom,etat,telephone,email);
        }
    }
    fclose(Fichier);
    gotoxy(4,j+1);printf("____________________________________________________________");
    gotoxy(7,j+5);
    break;
    default :
        printf("CHOIX NON VALIDE");
    break;
    }
}

//Consulter un compte
void consulter_Un_Compte(Liste_compte *L){
    int num;
    rectangle(0, 0, 42, 19);
    gotoxy(10,3);printf("CONSULTER UN COMPTE");
    rectangle(1, 1, 40, 4);
    gotoxy(7,7);num = identification(&(*L),&num);

    if(num > 0){
        Compte *ptr = L->premier;

        do{
            if(ptr->numero == num){
                system("cls");
                rectangle(16, 2, 50, 28);
                Color(11,0);
                rectangle(20, 3, 43, 2);
                gotoxy(28,4);
                printf("VOICI LES INFORMATIONS");
                Color(15,0);
                rectangle(43, 6, 0, 22);
                gotoxy(19,7);printf("NUMERO ");
                gotoxy(44,7);printf("=> %d",ptr->numero);
                gotoxy(19,10);printf("DATE DE CREATION ");
                gotoxy(44,10);printf("=> %s",ptr->date_create);
                gotoxy(19,13);printf("NOM ");
                gotoxy(44,13);printf("=> %s",ptr->nom);
                gotoxy(19,16);printf("PRENOMS");
                gotoxy(44,16);printf("=> %s",ptr->prenom);
                gotoxy(19,19);printf("TELEPHONE ");
                gotoxy(44,19);printf("=> %d",ptr->telephone);
                gotoxy(19,22);printf("EMAIL ");
                gotoxy(44,22);printf("=> %s",ptr->email);
                gotoxy(19,25);printf("ETAT (A=actif/B=Bloque)");
                gotoxy(44,25);printf("=> %c",ptr->etat);
                gotoxy(19,28);printf("SOLDE ");
                gotoxy(44,28);printf("=> %f",ptr->montant);
                gotoxy(19,35);
            }
            ptr= ptr->suiv;
        }while(ptr != NULL);
    }

}
// Enregistrer l'historique d'un compte
void historique_Des_Comptes(int num, char operation[], float *montant){
    FILE *historique;

    char date[11];
    date_Local(date);
    historique = fopen("historique.txt","a+");

    fprintf(historique,"%s %d %s %f\n",date,num,operation,*montant);

    fclose(historique);
}
//Faire un depot
void faire_Un_Depot(Liste_compte *L){
    int num, modif = 0;
    float montant;
    Compte *ptr = L->premier;
    rectangle(22,3,43,15);
    gotoxy(37,6);Color(11,0);printf("FAIRE UN DEPOT");
    Color(15,0);
    gotoxy(23,7);printf("__________________________________________");
    gotoxy(30,9);num = numero_id();
    char dat_trans[11];

    do{
        if(ptr->numero == num && ptr->etat != 'B'){
            modif = 1;
            gotoxy(23,10);printf("__________________________________________");
            gotoxy(30,12);printf("Entrez le montant :");
            scanf("%f",&montant);
            ptr->montant = ptr->montant+montant;
            copier_Compte_Dans_Le_Fichier(&(*L));
            historique_Des_Comptes(num,"Depot",&montant);
            system("cls");

            rectangle(22,3,43,15);
            date_Local(dat_trans);
            gotoxy(35,6);Color(2,0);printf("DEPOT VALIDE");
            Color(15,0);
            gotoxy(23,7);printf("__________________________________________");
            gotoxy(23,10);printf("NUMERO: %d",ptr->numero);
            gotoxy(45,10);printf("DATE: %s",dat_trans);
            gotoxy(23,12);printf("NOM: %s",ptr->nom);
            gotoxy(45,12);printf("PRENOMS: %s",ptr->prenom);
            gotoxy(27,16);printf("SOLDE: %f",montant);
            gotoxy(23,30);
        }
        else{
            ptr = ptr->suiv;
        }

    }while(ptr != NULL && ! modif);
        if(!modif){
            system("cls");
            rectangle(22,3,43,13);
            date_Local(dat_trans);
            gotoxy(35,6);Color(12,0);printf("DEPOT INVALIDE");
            Color(15,0);
            gotoxy(23,7);printf("__________________________________________");
            gotoxy(23,10);printf("Operation impossible");
            gotoxy(23,12);printf("Verifier l'etat de votre compte");
            gotoxy(35,14);printf("Merci :)...");
            gotoxy(23,30);
        }
}

//Affichage de l'histoorique d'un compte
void affiche_historique(){
    rectangle(8,2,35,2);
    rectangle(7,1,39,8);
    gotoxy(15,3);Color(11,0);printf("HISTORIQUE DES COMPTES");
    Color(15,0);
    gotoxy(10,7); int num = numero_id();
    system("cls");
    FILE *historique;
    historique = fopen("historique.txt","r");
    fseek(historique,0,0);
    char date[11];
    int num1;
    char operation[50];
    float montant;
    int i = 0,j = 5;
    rectangle(5,2,45,3);
        gotoxy(15,3);Color(11,0);printf("HISTORIQUE DU COMPPE: %d",num);
        Color(29,0);
        gotoxy(8,5);printf("DATE     NUMERO    OPERATION       SOMME");
        Color(15,0);
    while((fscanf(historique,"%s %d %s %f",&date,&num1,&operation,&montant)) != EOF){
        if(num == num1){
                i++;
                j = j+3;
            gotoxy(5,j);printf("< %s > < %d > < %s > [ %f ] \n",date,num,operation,montant);
        }
    }
    if(i == 0){
        printf("Historique non disponble\n");
    }
    fclose(historique);
    gotoxy(4,j+1);printf("___________________________________________________");
    gotoxy(7,j+5);
}


//Faire un retait
void faire_Un_Retrait(Liste_compte *L){
    int num,modif1 = 0;
    float montant;
    char rep;


    rectangle(0, 0, 45, 35);
    Color(11,0);
    gotoxy(14,3);printf("FAIRE UN RETRAIT");
    Color(14,0);
    rectangle(1, 1, 40, 4);
    Color(15,0);
    gotoxy(8,7);num = identification(&(*L),&num);
    Compte *ptr = L->premier;
    if(num > 0){
        do{
        if(ptr->numero == num){
                if(ptr->montant == 0){
                        modif1 = 0;
        rectangle(1, 21, 40, 12);
        gotoxy(3,18);Color(12,0);printf("RETRAIT IMPOSSIBLE (COMPTE VIDE).");
        gotoxy(3,20);printf("_______________________________________");
        Color(15,0);
        gotoxy(3,22);printf("VOTRE COMPTE EST VIDE.");
        gotoxy(3,24);printf("NUMERO: %d \t\tNOM: %s",ptr->numero,ptr->nom);
        gotoxy(3,26);printf("SOLDE %f",ptr->montant);
        gotoxy(3,28);
        fflush(stdin);
        break;

        }else{
            gotoxy(3,18);printf("ENTRER LE SOLDE A RETIRER: ");
            scanf("%f",&montant);
            gotoxy(3,19);printf("_______________________________________");
            if(ptr->montant < montant){
            modif1 = 0;
            rectangle(1, 21, 40, 12);
                gotoxy(5,21);Color(12,0);printf("SOLDE INSUFFISANT.");
                Color(15,0);
                gotoxy(3,23);printf("IMPOSSIBLE DE RETIRER TELLE SOMME.");
                gotoxy(3,25);printf("NUMERO: %d \t\tNOM: %s",ptr->numero,ptr->nom);
                gotoxy(3,27);printf("SOLDE %f",ptr->montant);
                gotoxy(3,31);
                break;
            }
            else{
                modif1 = 1;
                char date_retr[11];
                date_Local(date_retr);
                ptr->montant = ptr->montant - montant;
                copier_Compte_Dans_Le_Fichier(&(*L));
                rectangle(1, 21, 40, 12);
                gotoxy(5,21);Color(2,0);printf("RETRAIT VALIDE.");
                Color(15,0);
                gotoxy(3,23);printf("NUMERO: %d \t\tDATE: %s",ptr->numero,date_retr);
                gotoxy(3,25);printf("NOM: %s \t\tPRENOMS: %s",ptr->nom,ptr->prenom);
                gotoxy(3,27);printf("SOLDE %f",montant);
                gotoxy(3,31);
                historique_Des_Comptes(num,"Retrait",&montant);
                    }
            }
        }else{
            ptr = ptr->suiv;
            }
        }while(ptr != NULL && ! modif1);
    }
}

//Faire un transfert entre deux comptes
void faire_Un_transfert(Liste_compte *L){

    int modif=0, modif1=0;
    float montant;
    Compte *ptr = L->premier;
    Compte *ptr1;
    int num;

    rectangle(0, 0, 45, 35);
    Color(11,0);
    gotoxy(14,3);printf("FAIRE UN TRANSFERT");
    Color(14,0);
    rectangle(1, 1, 40, 4);
    gotoxy(8,7);num = identification(&(*L),&num);
    if(num > 0){
        do{
            if(ptr->numero == num){
                modif = 1;
                gotoxy(3,18);printf("Entrez le montant a transfere : ");
                scanf("%f",&montant);
                gotoxy(3,19);printf("_______________________________________");
                if((ptr->montant < montant) || (ptr->montant == 0)){

                    rectangle(1, 21, 40, 12);
                    gotoxy(5,21);Color(12,0);printf("SOLDE INSUFFISANT.");
                    Color(15,0);
                    gotoxy(3,23);printf("IMPOSSIBLE DE RETIRER TELLE SOMME.");
                    gotoxy(3,25);printf("NUMERO: %d \t\tNOM: %s",ptr->numero,ptr->nom);
                    gotoxy(3,27);printf("SOLDE %f",ptr->montant);
                    gotoxy(3,34);
                }else{
                    rectangle(1, 21, 40, 12);
                    gotoxy(5,21);printf("ENVOYER VERS: ");
                    gotoxy(5,23);int num1 = numero_id();
                    ptr1 = L->premier;
                    do{
                        if(ptr1->numero == num1 && ptr1->etat != 'B' && num!=num1){
                            modif1 = 1;
                            ptr1->montant = ptr1->montant+montant;
                            ptr->montant = ptr->montant-montant;
                            copier_Compte_Dans_Le_Fichier(&(*L));
                            historique_Des_Comptes(num,"Transfert",&montant);
                    char date_trans[11];
                    date_Local(date_trans);
                    rectangle(48, 3, 42, 20);
                    gotoxy(55,4);Color(2,0);printf("TRANSFERT VALIDE.");
                    Color(15,0);
                    gotoxy(50,5);printf("_______________________________________");
                    gotoxy(49,8);printf("ENVOYER DE: ");
                    gotoxy(49,10);printf("NUMERO: %d \t\tDATE: %s",ptr->numero,date_trans);
                    gotoxy(49,12);printf("NOM: %s \t\tPRENOMS: %s",ptr->nom,ptr->prenom);

                    gotoxy(49,15);printf("VERS: ");
                    gotoxy(49,17);printf("NUMERO: %d ",ptr1->numero);
                    gotoxy(49,19);printf("NOM: %s \t\tPRENOMS: %s",ptr1->nom,ptr1->prenom);
                    gotoxy(49,21);printf("SOLDE: %f",montant);
                    gotoxy(17,40);
                }else{
                    ptr1 = ptr1->suiv;
                }
            }while(ptr1 != NULL && ! modif1);
            if(!modif1){
                rectangle(48, 3, 42, 20);
                gotoxy(56,4);Color(12,0);printf("TRANSFERT NON VALIDE");
                Color(15,0);
                gotoxy(50,5);printf("_______________________________________");
                gotoxy(49,8);printf("NB: Verifier l'etat de votre compte.");
                gotoxy(49,10);printf("   Impossible de tranferere de A vers A.");
                gotoxy(60,12);printf("MERCI");
                gotoxy(17,40);
            }
        }
    }else
    ptr = ptr->suiv;
}while(ptr != NULL && ! modif);
    }
}

//FONCTION PRINCIPALE
int main()
{
    Compte monCompte;
    Liste_compte maListe;
    int choix = 0;

    init_Liste_compte(&maListe);
    transfert_donnees(&maListe);

    //MENU
    do{
        Color(15,0);
        rectangle(16, 2, 45, 28);
        rectangle(15, 1, 47, 31);
        gotoxy(32,31);Color(10,0);printf("ESGIS-BENIN");
        Color(13,0);
        gotoxy(30,2);printf("GESTION DE BANQUE");
        Color(14,0);
        rectangle(17, 3, 43, 2);
        gotoxy(35,4);printf("MENU");
        Color(15,0);
        gotoxy(18,7);printf("Tapez :");
        gotoxy(18,9);printf("1 - Creer un compte.");
        gotoxy(18,11);printf("2 - Rechercher un compte.");
        gotoxy(18,13);printf("3 - Consulter un compte.");
        gotoxy(18,15);printf("4 - Faire un depot.");
        gotoxy(18,17);printf("5 - Faire un retrait.");
        gotoxy(18,19);printf("6 - Faire un transfert vers un compte.");
        gotoxy(18,21);printf("7 - Consulter l'historique d'un compte.");
        gotoxy(18,23);printf("0 - Quitter.");
        Color(11,0);
        gotoxy(18,26);printf("Votre choix: ");
        gotoxy(18,27);printf(">>>");Color(15,0);scanf("%d",&choix);
        system("cls");

        switch(choix){
        case 1 :
            rectangle(16, 2, 45, 35);
            creer_Un_Compte(&maListe,&monCompte);
        break;
        case 2 :
            rechercher_Un_Compte(&maListe);
            system("pause");
            system("cls");
        break;
        case 3 :
            consulter_Un_Compte(&maListe);
            system("pause");
            system("cls");
        break;
        case 4 :
            faire_Un_Depot(&maListe);
            system("pause");
            system("cls");
        break;
        case 5 :
            faire_Un_Retrait(&maListe);
            system("pause");
            system("cls");
        break;
        case 6 :
            faire_Un_transfert(&maListe);
            system("pause");
            system("cls");
        break;
        case 7 :
            affiche_historique();
            system("pause");
            system("cls");
        break;
        case 0 :
            rectangle(21, 7, 30, 6);
            gotoxy(25,10);printf("A bientot le GROUPE :)\n\n\n\n");
            exit(0);
        break;
        default :
            Color(12,0);
            rectangle(32,25,27,2);
            gotoxy(38,26);printf("Choix non valide\n");
        break;
        }
    }while(choix != 0);

    return 0;
}
