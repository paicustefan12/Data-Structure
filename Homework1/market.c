#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pr_sm {

	char* nume;
	char* categorie;
	int pret;
	int cantitate;
	int stoc;
}pr_sm;

typedef struct lista1 {

	char* nume;
	char* categorie;
	int pret;
	int cantitate;
	int stoc;
	struct lista1* next;
}lista1;

typedef struct pr_cump {

	char* nume;
	char* categorie;
	int cantitate;
}pr_cump;

typedef struct lista2 { 

	char* nume;
	char* categorie;
	int cantitate;
	struct lista2* next;
}lista2;

typedef struct pr_lcump {

	char* nume;
	char* categorie;
	int cantitate;
}pr_lcump;

typedef struct lista3 {

	char *nume;
	char *categorie;
	int cantitate;
	struct lista3* next;
}lista3;

typedef struct stiva {

	int pret;
	struct stiva* next;
}stiva;

typedef struct arbore {

	int cantitate;
	struct arbore *left, *right;
}arbore;

void adaug_el1(lista1 **last, pr_sm a) {

	lista1 *temp = malloc(sizeof(lista1));
	temp->nume = (char*)malloc(30*sizeof(char));
	temp->categorie = (char*)malloc(30*sizeof(char));
	
	strcpy(temp->categorie, a.categorie);
	strcpy(temp->nume, a.nume);
	temp->pret = a.pret;
	temp->cantitate = a.cantitate;
	temp->stoc = a.stoc;
	(*last)->next = temp;
	*last = temp;
}

void adaug_el2(lista2 **last, pr_cump a) {

	lista2 *temp = malloc(sizeof(lista2));
	temp->nume = (char*)malloc(30*sizeof(char));
	temp->categorie = (char*)malloc(30*sizeof(char));

	strcpy(temp->categorie, a.categorie);
	strcpy(temp->nume, a.nume);
	temp->cantitate = a.cantitate;
	(*last)->next = temp;
	*last = temp;
}

lista1 *citire1(FILE* f1, int *nr_elem) {

	int n,i;
	pr_sm a;
	lista1 *head, *last;
	
	head = malloc(sizeof(lista1));
	a.nume = (char*)malloc(30*sizeof(char));
	a.categorie = (char*)malloc(30*sizeof(char));
	head->nume = (char*)malloc(30*sizeof(char));
	head->categorie = (char*)malloc(30*sizeof(char));
	
	fscanf(f1, "%d", &n);
	for(i=0;i<n;i++) {

		if(i == 0) {

			fscanf(f1, "%s", a.nume);
			fscanf(f1, "%s", a.categorie);
			fscanf(f1, "%d%d%d", &a.pret, &a.cantitate, &a.stoc);


			strcpy(head->categorie, a.categorie);
			strcpy(head->nume, a.nume);
			head->pret = a.pret;
			head->cantitate = a.cantitate;
			head->stoc = a.stoc;
			last = head;
		}
		else { 

				fscanf(f1, "%s", a.nume);
				fscanf(f1, "%s", a.categorie);
				fscanf(f1, "%d%d%d", &a.pret, &a.cantitate, &a.stoc);

				adaug_el1(&last, a);
 			}
	}
	*nr_elem = n;
	free(a.nume);
	free(a.categorie);
	return head;
}

lista2* citire2(FILE* f2) {

	int n,i;
	pr_cump a;
	lista2 *head, *last;
	
	a.nume = malloc(30*sizeof(char));
	a.categorie = malloc(30*sizeof(char));
	head = malloc(sizeof(lista2));
	head->nume = (char*)malloc(30*sizeof(char));
	head->categorie = (char*)malloc(30*sizeof(char));

	fscanf(f2, "%d", &n);
	for(i=0;i<n;i++){

		
		if(i == 0) {

			fscanf(f2, "%s", a.nume);
			fscanf(f2, "%s", a.categorie);
			fscanf(f2, "%d", &a.cantitate);


			strcpy(head->categorie, a.categorie);
			strcpy(head->nume, a.nume);
			head->cantitate = a.cantitate;
			last = head;
	}
	else {

			fscanf(f2, "%s", a.nume);
			fscanf(f2, "%s", a.categorie);
			fscanf(f2, "%d", &a.cantitate);

			adaug_el2(&last, a);
	}
	}
	free(a.nume);
	free(a.categorie);
	return head;

}

void elim_nod(lista2 *temp,lista2 **head) {

	lista2 *aux;
	lista2 *headcopy;
	headcopy = *head;
	
	if(headcopy == temp) {

		*head = (*head)->next;
		free(headcopy);
		return;
	}
	else {

			aux = *head;
			
			while (headcopy != NULL) {

				
				if(headcopy != temp) {
					
					aux = headcopy;
					headcopy = headcopy->next;
				}
				else {

					aux->next = headcopy->next;
					free(headcopy);
					return;
				}
			}
	}
}


void eliminare(lista1 *head1, lista2 **head2) {

	int OK = 0;
	lista1 *headcopy1, *aux1;
	lista2 *headcopy2;

	headcopy1 = head1;
	headcopy2 = *head2;
	while(headcopy2 != NULL) {

		OK = 0;
		headcopy1 = head1;
		while(headcopy1 != NULL) {

			if(strcmp(headcopy2->nume, headcopy1->nume) == 0) {

				aux1 = headcopy1;
				OK = 1;
			}
			headcopy1 = headcopy1->next;
		}
		if(OK == 1) {

				if(aux1->stoc == 0) {

					elim_nod(headcopy2, head2);
				}
			}
		headcopy2 = headcopy2->next;
		}
}


void adaug_el3(lista3 **last, lista2 *headcopy, int k) {

	lista3 *temp = malloc(sizeof(lista3));
	temp->nume = (char*)malloc(30*sizeof(char));
	temp->categorie = (char*)malloc(30*sizeof(char));

	strcpy(temp->categorie, headcopy->categorie);
	strcpy(temp->nume, headcopy->nume);
	temp->cantitate = k;
	(*last)->next = temp;
	*last = temp;
}

lista3 *lcump(lista1 *head1, lista2 *head2, int buget) {

	int bug = 0, p, c, i, k, OK, OK1 = 0;
	lista1 *headcopy1;
	lista2 *headcopy2 = malloc(sizeof(lista2));
	lista3 *head3 = malloc(sizeof(lista3));
	lista3 *last ;

	head3->nume = (char*)malloc(30*sizeof(char));
	head3->categorie = (char*)malloc(30*sizeof(char));

	headcopy2 = head2;

	while(headcopy2 != NULL) {

		headcopy1 = head1;
		OK = 0;
		if (OK1 == 0) {
				while(headcopy1 != NULL) {

					if(strcmp(headcopy2->nume, headcopy1->nume) == 0) {

					p = headcopy1->pret;
					if(headcopy2->cantitate <= headcopy1->cantitate)
						c = headcopy2->cantitate;
					else c = headcopy1->cantitate;
					OK = 1;
					}
					headcopy1 = headcopy1->next;
				}
			if(OK == 1) {
				if((bug+p*c) <= buget ) {

					bug = bug+p*c;
					strcpy(head3->nume, headcopy2->nume);
					strcpy(head3->categorie, headcopy2->categorie);
					head3->cantitate = c;
					last = head3;
				}	
				else {
					k = 0;
					for(i=1;i<=c;i++) {

						if((bug+p) <= buget) {
							
							bug = bug+p;
							k = i;
						}
						else i = c+1;
					}
					if(k != 0) {
						strcpy(head3->nume, headcopy2->nume);
						strcpy(head3->categorie, headcopy2->categorie);
						head3->cantitate = k;
						last = head3;
					}
				}
			}
			OK1 = 1;
		}
		else {
			while(headcopy1 != NULL) {

				if(strcmp(headcopy2->nume, headcopy1->nume) == 0) {

					p = headcopy1->pret;
					if(headcopy2->cantitate <= headcopy1->cantitate)
						c = headcopy2->cantitate;
					else c = headcopy1->cantitate;
					OK = 1;
				}
				headcopy1 = headcopy1->next;
			}
			if(OK == 1) {
				if((bug+p*c) <= buget ) {

					bug = bug+p*c;
					adaug_el3(&last, headcopy2, c);
				}	
				else {
					k = 0;
					for(i=1;i<=c;i++) {

						if((bug+p) <= buget) {
							
							bug = bug+p;
							k = i;
						}
						else i=c+1;
					}
					if(k != 0)
						adaug_el3(&last, headcopy2, k);
				}
			}
		}
	headcopy2 = headcopy2->next;
	}
	return head3;
}

void adaug_el31(lista3 **last, lista1 *headcopy,int k) {

	lista3 *temp = malloc(sizeof(lista3));
	temp->nume = (char*)malloc(30*sizeof(char));
	temp->categorie = (char*)malloc(30*sizeof(char));

	strcpy(temp->categorie, headcopy->categorie);
	strcpy(temp->nume, headcopy->nume);
	temp->cantitate = k;
	(*last)->next = temp;
	*last = temp;
}
void lcump_neli(lista3 **head3, lista2 **head2, lista1 *head1) {

	lista1 *headcopy1, *headcopy11;
	lista2 *headcopy2 = malloc(sizeof(lista2));
	lista3 *last;
	int Min, OK = 0, OK2, c, c1, k, t;

	(*head3)->nume = (char*)malloc(30*sizeof(char));
	(*head3)->categorie = (char*)malloc(30*sizeof(char));
	headcopy2 = *head2;

	while(headcopy2 != NULL) {

		headcopy1 = head1;
		Min = 9999;
		OK2 = 2;
		if(OK == 0) {

			while(headcopy1 != NULL) {

				if(strcmp(headcopy2->nume, headcopy1->nume) == 0) {

					OK = 1;
					if(headcopy2->cantitate <= headcopy1->cantitate) {

						OK2 = 0;
						c = headcopy2->cantitate;
						headcopy2->cantitate = 0;
					}
					else {

						OK2 = 1;
						c = headcopy1->cantitate;
						headcopy2->cantitate = headcopy2->cantitate - headcopy1->cantitate;
						c1 = headcopy2->cantitate;
						headcopy11 = headcopy1;
					}
				}
				headcopy1 = headcopy1->next;
			}

				if(OK2 == 0) {

					strcpy((*head3)->nume, headcopy2->nume);
					strcpy((*head3)->categorie, headcopy2->categorie);
					(*head3)->cantitate = c;
					last = *head3;
				}
				else if(OK2 == 1) {

					strcpy((*head3)->nume, headcopy2->nume);
					strcpy((*head3)->categorie, headcopy2->categorie);
					(*head3)->cantitate = c;
					last = *head3;
					
					headcopy1 = headcopy11->next;
					while(headcopy1 != NULL) {

						if(strcmp(headcopy1->categorie, headcopy2->categorie) == 0) {

							if(headcopy11->pret >= headcopy1->pret) 
								k = headcopy11->pret - headcopy1->pret;
							else k = headcopy1->pret - headcopy11->pret;
						}
						if(k < Min)
							Min = k;
						headcopy1 = headcopy1->next;
					}

					headcopy1 = headcopy11->next;
					while(headcopy1 != NULL) {

						if(strcmp(headcopy1->categorie, headcopy11->categorie) == 0) {

							if((headcopy11->pret - headcopy1->pret) == Min)
								{if(headcopy1->cantitate >= c1) 
										{
											adaug_el31(&last, headcopy1, c1);
											headcopy2->cantitate = headcopy2->cantitate - c1;
										}
								else {
									adaug_el31(&last, headcopy1, headcopy1->cantitate);
									headcopy2->cantitate = headcopy2->cantitate - headcopy1->cantitate;
								}
							}
							else {
								t = headcopy1->pret-headcopy11->pret;
								if( t == Min)
									{if(headcopy1->cantitate >= c1)
										{
											adaug_el31(&last, headcopy1, c1);
											headcopy2->cantitate = headcopy2->cantitate - c1;
										}
									else adaug_el31(&last, headcopy1, headcopy1->cantitate);
									}
								}
						}
						headcopy1 = headcopy1->next;	
					}
				}
			}
		else {
			while(headcopy1 != NULL) {

				if(strcmp(headcopy2->nume, headcopy1->nume) == 0) {

					if(headcopy2->cantitate <= headcopy1->cantitate) {

						OK2 = 0;
						c = headcopy2->cantitate;
						headcopy2->cantitate = 0;
					}
					else {

						OK2 = 1;
						c = headcopy1->cantitate;
						headcopy2->cantitate = headcopy2->cantitate - headcopy1->cantitate;
						c1 = headcopy2->cantitate;
						headcopy11 = headcopy1;
					}
				}
				headcopy1 = headcopy1->next;
			}

				if(OK2 == 0) {

					adaug_el3(&last, headcopy2, c);
				}
				else if(OK2 == 1) {

					adaug_el3(&last, headcopy2, c);
					
					headcopy1 = headcopy11->next;
					while(headcopy1 != NULL) {

						if(strcmp(headcopy1->categorie, headcopy2->categorie) == 0) {

							if(headcopy11->pret >= headcopy1->pret) 
								k = headcopy11->pret - headcopy1->pret;
							else k = headcopy1->pret - headcopy11->pret;
						}
						if(k < Min)
							Min = k;
						headcopy1 = headcopy1->next;
					}

					headcopy1 = headcopy11->next;
					while(headcopy1 != NULL) {

						if(strcmp(headcopy1->categorie, headcopy2->categorie) == 0) {

							if( (headcopy11->pret - headcopy1->pret) == Min)
									{if(headcopy1->cantitate >= c1) 
										{
											adaug_el31(&last, headcopy1, c1);
											headcopy2->cantitate = headcopy2->cantitate - c1;
										}
								else {
									adaug_el31(&last, headcopy1, headcopy1->cantitate);
									headcopy2->cantitate = headcopy2->cantitate - headcopy1->cantitate;
									}
								}
							else {
								t = headcopy1->pret-headcopy11->pret;
								if(t == Min)
									{
										if(headcopy1->cantitate >= c1)
											{
												adaug_el31(&last, headcopy1, c1);
												headcopy2->cantitate = headcopy2->cantitate - c1;
											}
									
									else {
										adaug_el31(&last, headcopy1, headcopy1->cantitate);
										headcopy2->cantitate = headcopy2->cantitate - headcopy1->cantitate;
									}
								}
							}
						}
						headcopy1 = headcopy1->next;
					}
				}

			}
		headcopy2 = headcopy2->next;
		}
	}

int isEmpty (stiva* top) {

	return(top == NULL);
}

void push(stiva **top, int p) {

	stiva *new = (stiva*)malloc(sizeof(stiva));
	new->pret = p;
	new->next = *top;
	*top = new;
}

void pop(stiva **top) {

	stiva *temp = (*top);
	(*top) = (*top)->next;
	free(temp);
}

int top(stiva *top) {

	if(isEmpty(top))
		return -1;
	return(top->pret);
}

void stergere_stiva(stiva **top) {

	stiva *topCopy = *top, *temp;
	while (topCopy != NULL) {

		temp = topCopy;
		topCopy = topCopy->next;
		free(temp);
	}
}
void pstiva(lista1 *head, int *v, int *l) {

	stiva *top1, *top2;
	lista1 *headcopy1 = head;
	int k;
	top1 = NULL;
	top2 = NULL;
	*l = 0;
	while(headcopy1 != NULL) {
	
		k = 0;
		if(isEmpty(top1)) {

			push(&top1, headcopy1->pret);
			v[*l] = 0;
		}
		else {

			while(!isEmpty(top1) && (headcopy1->pret)<(top(top1))){

				push(&top2, top(top1));
				pop(&top1);
				
				k++;
			}
			v[*l] = k;
			while(!isEmpty(top2)) {

				push(&top1, top(top2));
				pop(&top2);
				
			}
			push(&top1, headcopy1->pret);
		}
	*l = *l+1;
	headcopy1 = headcopy1->next;
	}
	stergere_stiva(&top1);
	stergere_stiva(&top2);
}

arbore *creare_arbore(int N) {

	if(N>0) {

		arbore *root = malloc(sizeof(arbore));
		root->left = creare_arbore(N/2);
		root->right = creare_arbore(N-1-N/2);
		return root;
	}
	else return NULL;
}

void alc_arbore(arbore *root, int *v,int i, int N) {

	
	if(root) {

		root->cantitate = v[i];
		i++;
		alc_arbore(root->left, v, i, N);
		if(N%2 == 0)
			alc_arbore(root->right, v, N-N/2+1, N);
			else alc_arbore(root->right, v, N-N/2, N);
	}
}

void preorder(arbore *root, FILE *f) {

	if(root) {

		fprintf(f, "%d ", root->cantitate);
		preorder(root->left, f);
		preorder(root->right, f);
	}
}

void bubble_sort(int *v, int n) {

	int i, sortat = 1;
	while(sortat == 1) {

		sortat = 0;
		for(i=0;i<n-1;i++) {

			if(v[i]>v[i+1]) {
				int temp = v[i];
				v[i] = v[i+1];
				v[i+1] = temp;
				sortat = 1;
			}
		}
	}
}

void stergere_lista1(lista1 **head) {

	lista1 *headcopy;
	while(*head != NULL) {

		headcopy = (*head)->next;
		free((*head)->nume);
		free((*head)->categorie);
		free(*head);
		*head = headcopy;
	}
	*head = NULL;
}

void stergere_lista2(lista2 **head) {

	lista2 *headcopy;
	while(*head != NULL) {

		headcopy = (*head)->next;
		free((*head)->nume);
		free((*head)->categorie);
		free(*head);
		*head = headcopy;
	}
	*head = NULL;
}

void stergere_lista3(lista3 **head) {

	lista3 *headcopy;
	while(*head != NULL) {

		headcopy = (*head)->next;
		free((*head)->nume);
		free((*head)->categorie);
		free(*head);
		*head = headcopy;
	}
	*head = NULL;
}

int main(int argc, char *argv[])
{
	lista1 *head1;
	lista2 *head2, *headcopy2;
	lista3 *head3 = malloc(sizeof(lista3)), *headcopy3;
	arbore *root;
	int buget, c1, c2, c3, c4, c5, c6, *v, l, i, nr_elem, N = 0, *u;
	FILE *date1, *date2, *cerinte, *rezultate;
	
	date1 = fopen(argv[1], "rt");
	date2 = fopen(argv[2], "rt");
	cerinte = fopen(argv[3], "rt");
	rezultate = fopen(argv[4], "wt");

	head1 = citire1(date1, &nr_elem);
	head2 = citire2(date2);
	fscanf(cerinte, "%d", &c1);
	fscanf(cerinte, "%d", &c2);
	fscanf(cerinte, "%d", &c3);
	fscanf(cerinte, "%d", &c4);
	fscanf(cerinte, "%d", &c5);
	fscanf(cerinte, "%d", &c6);
	fscanf(cerinte, "%d", &buget);

	if(c1 == 1 && c2 == 0) {
		
		headcopy2 = head2;
		while(headcopy2 != NULL) {

			fprintf(rezultate, "%s %s %d\n", headcopy2->nume, headcopy2->categorie, headcopy2->cantitate);
			headcopy2 = headcopy2->next;
		}
		fprintf(rezultate, "\n");
	}
	if(c2 == 1 && c4 == 0) {
		
		eliminare(head1, &head2);
		headcopy2 = head2;
		while(headcopy2 != NULL) {

			fprintf(rezultate, "%s %s %d\n", headcopy2->nume, headcopy2->categorie, headcopy2->cantitate);
			headcopy2 = headcopy2->next;
		}
		fprintf(rezultate, "\n");
	}
	if(c3 == 1) {

		head3 = lcump(head1, head2, buget);
		headcopy3 = head3;
		i = 0;
		while(headcopy3 != NULL) {

			fprintf(rezultate, "%s %s %d\n", headcopy3->nume, headcopy3->categorie, headcopy3->cantitate);
			N++;
			headcopy3 = headcopy3->next;
		}
		u = (int*)malloc(N*sizeof(int));
		while(headcopy3 != NULL) {

			u[i] = headcopy3->cantitate;
			headcopy3 = headcopy3->next;
			i++;
		}
	fprintf(rezultate, "\n");
	}

	if(c4 == 1) {

		eliminare(head1, &head2);
		lcump_neli(&head3, &head2, head1);
		headcopy2 = head2;
		i = 0;
		while(headcopy2 != NULL) {

			fprintf(rezultate, "%s %s %d\n", headcopy2->nume, headcopy2->categorie, headcopy2->cantitate);
			headcopy2 = headcopy2->next;
		}
		fprintf(rezultate, "\n");
		headcopy3 = head3;
		while(headcopy3 != NULL) {

			fprintf(rezultate, "%s %s %d\n", headcopy3->nume, headcopy3->categorie, headcopy3->cantitate);
			N++;
			headcopy3 = headcopy3->next;
		}
		headcopy3 = head3;
		u = (int*)malloc(N*sizeof(int));
		while(headcopy3 != NULL) {

			u[i] = headcopy3->cantitate;
			headcopy3 = headcopy3->next;
			i++;
		}
	fprintf(rezultate, "\n");
	}

	if(c5 == 1) {

		root = creare_arbore(N);
		bubble_sort(u, N);
		i = 0;
		alc_arbore(root, u, i, N);
		preorder(root, rezultate);
	}
	if(c6 == 1) {

		v = (int*)malloc(nr_elem*(sizeof(int)));
		pstiva(head1, v, &l);
		for(i=0;i<l;i++)
			fprintf(rezultate, "%d ", v[i]);
	}

	stergere_lista1(&head1);
	stergere_lista2(&head2);
	if(c3 == 1 || c4 == 1)
		stergere_lista3(&head3);
	if(c6 == 1)
		free(v);
	if(c3 == 1 || c4 == 1)
		free(u);

	fclose(date1);
	fclose(date2);
	fclose(cerinte);
	fclose(rezultate);

	return 0;
}	