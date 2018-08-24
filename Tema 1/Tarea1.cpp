#include <iostream>
#include <cstdlib>
using std::cout;
using std::cin;
using std::malloc;
using std::free;

typedef struct list_int {
	int n;
	struct list_int *ptr;
} LISTA;

LISTA *init_list, *aux, *e, *temp;
int Elems = 1;

void insertAfter(struct LISTA* prev_node, int new_data)
{
    if (prev_node == NULL) 
    { 
       printf("El nodo no puede ser NULL");       
       return;  
    }  
    struct LISTA* new_node =(struct LISTA*) malloc(sizeof(LISTA));
    new_node->n  = new_data;
    new_node->ptr = prev_node->next; 
    prev_node->ptr = new_node;
}

void deleteNode(struct LISTA **head_ref, int key)
{
    struct LISTA* temp = *init_list, *prev;
    if (temp != NULL && temp->data == key)
    {
        *init_list = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->n != key)
    {
        prev = temp;
        temp = temp->ptr;
    }
    if (temp == NULL) return;
    prev->ptr = temp->ptr;
    free(temp);
}

void search(struct LISTA* head, int x)
{
    if (head == NULL)
        return;
    if (head->n == x)
        insertAfter(head,x);
    search(head->ptr, x);
}


int main() {


	cout << "Dar 5 elementos ordenados a la lista\n";
	e = (LISTA*) malloc(sizeof(LISTA));
	cout << "Elemento " << Elems << "  ";
	cin >> temp->n;
	search(init_list,temp->n);
	e->ptr = NULL;
	aux = e;
	init_list = e;
	Elems++;
	while (Elems <= 5) {
		cout << "Elemento " << Elems << "  ";
		cin >> temp->n;
		search(init_list,temp->n);
		Elems++;
	}
	cout << "Los valores son: \n";
	aux = init_list;
	while (aux != NULL) {
		cout << aux->n << "\n";
		aux = aux->ptr;
	}
	cin.get();
	cin.get();
	return 0;
}
