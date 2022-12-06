#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tp4.h"
int main() {
	Parbre* abr = (Parbre*)malloc(sizeof(Parbre));
	Parbre* abr2 = (Parbre*)malloc(sizeof(Parbre));
	*abr = NULL;
	*abr2 = NULL;
	Patient* p;
	int run = 1;
	int choice;
	int nivu;
	while (run) {
		char *nom =(char*)malloc(sizeof(char)*10);
		char *prenom =(char*)malloc(sizeof(char) * 10);
		char *date = (char*)malloc(sizeof(char) * 10);
		char *motif = (char*)malloc(sizeof(char) * 10);
		printf("1.Ajouter un patient\n");
		printf("2.Ajouter une consultation à un patient\n");
		printf("3.Afficher une fiche médicale\n");
		printf("4.Afficher la liste des patients\n");
		printf("5.Supprimer un patient\n");
		printf("6.Copier ou mettre à jour la liste des patients\n");
		printf("7.Quitter\n");
		printf("\nQuel est votre choix :(1-7) \n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("\nQuel est le  nom du patient : \n");
			scanf("%s",nom);
			printf("\nQuel est le  prénom du patient : \n");
			scanf("%s", prenom);
			//convertir en majuscules
			for  (int i = 0; i < strlen(nom);  i++)
			{
				nom[i] = toupper(nom[i]);
			}
			inserer_patient(abr,nom, prenom);
			printf("Action terminée!\n\n");
			break;

		case 2:
			printf("\nQuel est le  nom du patient : \n");
			scanf("%s", nom);
			printf("\nQuel est le  date de consultation (JJ-MM-AAAA) : \n");
			scanf("%s", date);
			int c;
			while (((c = getchar()) != '\n') && c != EOF) {}    //vide le flux  
			printf("Quel est le  motif de consultation :\n");
			scanf("%[^\n]s", motif);
			printf("\nQuel est le niveau d'urgence : \n");
			scanf("%d", &nivu);
			for (int i = 0; i < strlen(nom); i++)
			{
				nom[i] = toupper(nom[i]);
			}
			ajouter_consultation(abr, nom, date, motif, nivu);
			printf("Action terminée!\n\n");
			break;
		case 3:
			printf("\nQuel est le  nom du patient : \n");
			scanf("%s", nom); 
			for (int i = 0; i < strlen(nom); i++)
			{
				nom[i] = toupper(nom[i]);
			}
			afficher_fiche(abr,nom);
			printf("\nAction terminée\n\n");
			break;
		case 4:
			afficher_patients(abr);
			printf("\nAction terminée\n\n");
			break;
		case 5:
			printf("\nQuel est le  nom du patient à supprimer: \n");
			scanf("%s", nom);
			for (int i = 0; i < strlen(nom); i++)
			{
				nom[i] = toupper(nom[i]);
			}
			supprimer_patient(abr, nom);
			printf("Action terminée!\n\n");
			break;
		case 6:
			maj(abr, abr2);
			printf("\nListe après la mise à jour :\n");
			afficher_patients(abr2);
			printf("Mise à jour effectuée avec succès!\n\n");
			break;
		case 7:
			free_arbre(abr);
			free_arbre(abr2);
			run = 0;
			printf("Au revoir!\n");
			break;
		default:
			printf("\nchoix non valide, réesseyer : \n\n");
			break;
		}
	}
	return 0;
}