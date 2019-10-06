#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*				TRAVAIL SUR LA NOTION DE FILE (QUEUE)					*/
/*	Utilisation du programme :											*/
/*		Entrer une commande :											*/
/*				- queue <value>	  Insertion d'une valeur en fin de file	*/
/*				- dequeue		  Extraction de la première valeur		*/
/*				- bye			  Fin, libération mémoire				*/
/*																		*/
/*	NB : Utilisation d'un tableau circulaire pour stocker les valeurs	*/
/************************************************************************/

/************************************************************************/
/*																		*/
/*				DECLARATIONS DE STRUCTURES & FONCTIONS					*/
/*																		*/
/************************************************************************/

/*	Structure Queue : File d'attente	*/
typedef struct {
	int taille ; /* taille du tableau de valeurs */
	int debut; /* Indice du début de la file */
	int fin;    /* Indice de la fin de la file */
	int *array;    /* array of values */
} Queue;


/*			FONCTIONS			*/

/* Init allocates the structure Queue and
 * also the membre array with the given size 
 * it also fill taille (size) and intializes 
 * debut and fin to 0 */
Queue * Init(int size);

/* InsertValue insert value into the queue
 * the array is reallocated if necessary (allocated changed 
 * with respect to the new size )
 * fin is incremented by 1 */
void InsertValue(Queue * queue, int value);

/* Extraction returns 0 if the queue is empty
 * otherwise it returns 1 and fills *val with the maximum 
 * value present in the queue
 * debut is incremented by 1  and the first value is removed
 * from the queue*/
int Extraction(Queue * queue, int * val);

/* Destroy frees the structure and the array */
void Destroy(Queue * queue);



/************************************************************************/
/*																		*/
/*									MAIN								*/
/*																		*/
/************************************************************************/

int main(void) 
{
	char lecture[100];
	int val;
	Queue * queue;
	queue = Init(100);	//Initialisation de la file

	fscanf(stdin,"%99s",lecture);
	while (strcmp(lecture,"bye")!=0) 
	{
		if (strcmp(lecture,"queue")==0) 
		{	//Insertion dans la file
			fscanf(stdin,"%99s",lecture);
			val = strtol(lecture,NULL,10);
			InsertValue(queue,val);
		} 
		
		else if (strcmp(lecture,"dequeue")==0) 
		{	//Suppression
			if(Extraction(queue,&val))
			{	//Si la suppression se fait correctement, affichage de la valeur sortie
				printf("%d\r\n",val);
			}
		}
		
		fscanf(stdin,"%99s",lecture);
	}
	
	//Fin du programme, libération de la mémoire allouée
	Destroy(queue);
	return 0;
}



/************************************************************************/
/*																		*/
/*						DEFINITIONS DES FONCTIONS						*/
/*																		*/
/************************************************************************/

/*	Fonction d'initialisation de la file	*/
Queue * Init(int size)
{
	//Allocation de la structure
	Queue * queue = malloc(sizeof(Queue));
	
	queue->taille = size ;
	queue->debut = 0 ;
	queue->fin = 0 ;	//	debut = fin => file vide
	
	//Allocation du tableau circulaire
	queue->array = malloc(size*sizeof(int));
	
	return queue;
}


/*	Fonction d'insertion d'une valeur	*/
void InsertValue(Queue * queue, int value)
{
	//Si on a plus de place dans la file (tableau plein)
	if ((queue->fin == queue->taille-1 && queue->debut == 0)
		|| (queue->debut - queue->fin == 1)) 
	{
		return ; //On quitte
	}
	
	//Si ce n'est pas plein mais que le compteur fin
	//est à la fin physique de la mémoire allouée
	if (queue->fin == queue->taille-1) 
	{	// On retourne au début de la zone mémoire et on insère
		queue->array[queue->fin] = value ;
		queue->fin = 0 ;
		return ;
	}
	
	//Sinon on insère à la fin et on incrémente la fin
	queue->array[queue->fin] = value ;
	queue->fin ++ ;
}


/*	Fonction de suppression de l'élément en tête	*/
int Extraction(Queue * queue, int *res)
{
	//Si la file est vide
	if (queue->debut == queue->fin) 
	{
		return 0 ; //Aucune suppression
	}
	
	//On récupère la valeur qui va être supprimée
	*res = queue->array[queue->debut] ;
	
	//Si l'indice de début de la file était arrivé à la fin de la mémoire physique
	if (queue->debut == queue->taille-1) 
	{
		queue->debut = 0 ;	//On reprend au début
	}
	
	//Sinon on incrémente simplement l'indice de début de la file
	else 
	{
		queue->debut ++ ;
	}
	
	return 1 ;
}


/*	Fonction de destruction de la structure et libération de la mémoire	*/
void Destroy(Queue * queue)
{
	free(queue->array) ;	//Libération du tableau de valeurs
	free(queue) ;			//Libération de la structure entière
}


