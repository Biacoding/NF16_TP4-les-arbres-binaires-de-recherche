#include<stdio.h>
#include<stdlib.h> 
#include"tp4.h"
#include<string.h>

//O(1)
Patient* CreerPatient(char* nm, char* pr) {
	Patient* p=(Patient*)malloc(sizeof(Patient));
	p->nom = nm; 
	p->prenom =pr;
	p->fils_droit = NULL;
	p->fils_gauche = NULL;
	p->Listconsult = NULL;
	p->nbrconsult = 0;
	return p;
}
//O(h)
void inserer_patient(Parbre* abr, char* nm, char* pr){
	Patient* tmp = *abr;
	Patient* Parent = NULL;
	int i=0; //Déterminez s'il faut insérer à gauche ou à droite à la fin
	while (tmp != NULL)  
	{
		Parent = tmp;
		if (strcmp(tmp->nom,nm)>0)
		{
			tmp=tmp->fils_gauche;
			i = 1;
		}
		else if(strcmp(tmp->nom, nm) < 0)
		{
			tmp = tmp->fils_droit;
			i = 2;
		}
		else {
			printf("le patient existe déjà\n");
			return NULL;
		}
	}
	if (tmp == NULL)
	{
		if (Parent == NULL) {
			*abr = CreerPatient(nm, pr);
		}
		else if(i==1)
		{
			Parent->fils_gauche = CreerPatient(nm, pr);
		}
		else if(i==2) {
			Parent->fils_droit = CreerPatient(nm, pr);
		}
	}
}
//O(h)
Patient* rechercher_patient(Parbre* abr, char* nm) {
	Patient* tmp = *abr;
	if (tmp == NULL) {
		printf("il n'y a plus de patient dans l'ABR\n");
		return NULL;
	}
	while (tmp != NULL && strcmp(tmp->nom, nm) != 0)
	{
		if (strcmp(tmp->nom, nm) > 0)
		{
			tmp = tmp->fils_gauche;
		}
		else 
		{
			tmp = tmp->fils_droit;
		}

	}
	return tmp;
}
//O(k)
void afficher_consultation(Patient* p) {
	Consultation* tmp = p->Listconsult;
	int nb = 1;
	while (tmp != NULL)
	{
		printf("Consultation:%d\n ", nb);
		printf("\tla date :%s\n", tmp->date);
		printf("\tle motif:%s\n", tmp->motif);
		printf("\tle niveau d'urgence:%d\n\n", tmp->niveauUrg);
		tmp = tmp->suivant;
		nb++;
	}
}
//O(k)
void free_consultaion(Patient* p) {
	Consultation* tmp = p->Listconsult;
	Consultation* tmp2;
	while (tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->suivant;
		free(tmp2);
	}
}
//O(h+k)
void afficher_fiche(Parbre* abr, char* nm) {
	Patient* p = rechercher_patient(abr, nm);
	if (p == NULL) { printf("le patient recherché n'est pas dans l'ABR\n"); return NULL; }
	printf("\nLe patient:%s %s \n", p->prenom, p->nom);
	printf("Nombre de consultation:%d\n", p->nbrconsult);
	afficher_consultation(p);
}
//O(n)
void afficher_patients(Parbre* abr) {
	//l'affichage prefixe
	Patient* tmp;
	tmp = *abr;
	if (tmp == NULL)return NULL;
	else {
		printf("\nLe patient:%s %s \n", tmp->prenom, tmp->nom);
		printf("Nombre de consultation:%d\n\n", tmp->nbrconsult);
		afficher_patients(&(tmp->fils_gauche));
		afficher_patients(&(tmp->fils_droit));
	}
}
//O(k*n)
void free_arbre(Parbre* abr) {
	Patient* tmp;
	tmp = *abr; 
	if (tmp == NULL)return NULL;
	else {
		free_consultaion(tmp);
		Parbre* tmp_fils_gauche=(Parbre*)malloc(sizeof(Parbre));
		Parbre* tmp_fils_droit= (Parbre*)malloc(sizeof(Parbre));
		*tmp_fils_gauche = tmp->fils_gauche;
		*tmp_fils_droit = tmp->fils_droit;
		free(tmp);
		free_arbre(tmp_fils_gauche);
		free(tmp_fils_gauche);
		free_arbre(tmp_fils_droit);
		free(tmp_fils_droit);
	}
}
//O(1)
Consultation* CreerConsult(char* date, char* motif, int nivu) {
	Consultation* c = (Consultation*)malloc(sizeof(Consultation));
	c->date = date;
	c->motif = motif;
	c->niveauUrg = nivu;
	c->suivant = NULL;
}
//O(h+k)
void ajouter_consultation(Parbre* abr, char* nm, char* date, char* motif, int nivu) {
	Patient* p;
	p=rechercher_patient(abr, nm);
	if (p == NULL) { printf("le patient recherché n'est pas dans l'ABR\n"); return NULL; }
	Consultation* tmp = p->Listconsult;
	if (tmp == NULL) {//S'il n'y a pas d'élément dans Listconsult, insérez-le en tête de liste chaînée
		p->Listconsult = CreerConsult(date, motif, nivu);
	}
	else {
		while (tmp->suivant != NULL) {
			tmp = tmp->suivant;
		}
		tmp->suivant = CreerConsult(date, motif, nivu);
	}
	p->nbrconsult++;
}
//O(2h+k)
void supprimer_patient(Parbre* abr, char* nm) {
	Patient* rechercher;
	Patient* tmp1 = *abr;
	Patient* Parent = NULL;
	int i = 0;
	if (*abr == NULL) {
		printf("il n'y a plus de patient dans l'ABR\n");
		return NULL;
	}
	else {
		//Déterminer si le patient à supprimer se trouve dans l'arbre binaire
		while (tmp1 != NULL && strcmp(tmp1->nom, nm) != 0)
		{
			Parent = tmp1;
			if (strcmp(tmp1->nom, nm) > 0)
			{
				tmp1 = tmp1->fils_gauche;
				i = 1;
			}
			else
			{
				tmp1 = tmp1->fils_droit;
				i = 2;
			}
		}
		switch (i)
		{
		case 1:rechercher= Parent->fils_gauche;break;
		case 2:rechercher = Parent->fils_droit;break;
		default:rechercher = *abr;break;
		}
	}

	if (rechercher == NULL) {
		printf("le patient recherché n'est pas dans l'ABR\n");
		return NULL;
	}
	else {
		//le sous-arbre de gauche n'est pas vide
		if (rechercher->fils_gauche != NULL) {
			//Trouver le nœud le plus à droite du sous-arbre de gauche
			Patient* tmp2 = rechercher->fils_gauche;
			while (tmp2->fils_droit != NULL)
			{
				tmp2 = tmp2->fils_droit;
			}
			tmp2->fils_droit = rechercher->fils_droit;
			switch (i)
			{
			case 1:Parent->fils_gauche=rechercher->fils_gauche;break;
			case 2:Parent->fils_droit= rechercher->fils_gauche;break;
			default:*abr = rechercher->fils_gauche;break; 
			}
		}
		else {
			switch (i)
			{
			case 1:Parent->fils_gauche= rechercher->fils_droit;break;
			case 2:Parent->fils_droit = rechercher->fils_droit;break;
			default:*abr = rechercher->fils_droit;break;
			}
		}
		free_consultaion(rechercher);
	}
}
//O(k*n)
void maj(Parbre* abr, Parbre* abr2) {
	Patient* tmp;
	Patient* tmp2;
	Consultation* tmpc1;
	Consultation* tmpc2;
	tmp = *abr;
	tmp2 = *abr2;
	if (tmp == NULL)
	{
		*abr2 = NULL;
		free_arbre(&tmp2);
	}
	else {
		//parcours récursif
		
		//Lorsqu'il n'y a pas d'élément dans abr2, insérez-le directement
		if (tmp2 == NULL) {
			inserer_patient(abr2, tmp->nom, tmp->prenom);//Parce que tmp2=NULL, l'insertion doit être à la racine de l'arbre binaire
		}
		//Lorsque les deux arbres ont la même position mais des nœuds différents
		else if (strcmp(tmp->nom, tmp2->nom) != 0 ) {
			tmp2->nom = tmp->nom;
			tmp2->prenom = tmp->prenom;
			tmp2->fils_droit = NULL;
			tmp2->fils_gauche = NULL;
			//tmp2->nbrconsult = tmp->nbrconsult;
		}
		//tmp->nom == tmp2->nom  Dans ce cas, la liste est toujours copiée
		tmp2 = *abr2;
		tmpc1 = tmp->Listconsult;
		//Attribuer liste1 à liste2
		tmp2->nbrconsult = tmp->nbrconsult;
		if (tmpc1 == NULL) { free_consultaion(tmp2);tmp2->Listconsult = NULL; }
		else if (tmpc1 != NULL) {
			tmp2->Listconsult = CreerConsult(tmpc1->date, tmpc1->motif, tmpc1->niveauUrg);
			tmpc2 = tmp2->Listconsult;
			while (tmpc1->suivant != NULL) {
				tmpc1 = tmpc1->suivant;
				tmpc2->suivant = CreerConsult(tmpc1->date, tmpc1->motif, tmpc1->niveauUrg);
				tmpc2 = tmpc2->suivant;
			}
		}
		maj(&(tmp->fils_gauche), &(tmp2->fils_gauche));
		maj(&(tmp->fils_droit), &(tmp2->fils_droit));
	}
}