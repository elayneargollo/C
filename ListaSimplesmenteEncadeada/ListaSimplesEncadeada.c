#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int elemento;
    struct lista *proximo;

} list;

void inserir (list *inicio);
void apagar (list *inicio);
void listar (list *inicio);
int buscar (list *inicio, int valor);
list *criar ();

int main(int argc, char** argv) {
    list *inicio = (list*) malloc (sizeof(list));
    int valor;
    
    for (int i=0; i<3; i++){
        inserir (inicio);    
    }
    
    printf ("Escolha o valor: ");
    scanf ("%d", &valor);
    
    if ((buscar(inicio,valor) == valor)){
        printf ("Achei!\n");
    } else printf ("Não tem na lista\n");

    apagar (inicio);
    listar (inicio);
}

void inserir (list *inicio){
    list *temp;
    list *novo = criar ();
    
    if (inicio->proximo==NULL){
        inicio->proximo = novo;
    } else {
        temp = inicio->proximo;
        while (temp->proximo!=NULL){
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }
}

list *criar (){
    list *novo = (list*) malloc (sizeof (list));
    int valor;
    
    printf ("Informe o numero: ");
    scanf ("%d",&valor);
    
    novo->elemento = valor;
    novo->proximo = NULL;
    
    return novo;
    
}

int buscar (list *inicio, int val){
    list *temp;
    
    for (temp=inicio; temp!=NULL; temp=temp->proximo){
        if (temp->elemento == val){
            return val;
        }
    }
    
}

void apagar (list *inicio){
    list *temp;
    list *busca=NULL;
    int elemento;
    
    printf ("Informe numero q deseje apagar: ");
    scanf ("%d",&elemento);
    
    for (temp=inicio; temp!=NULL; temp=temp->proximo){
        if (temp->elemento == elemento){
            if (busca == NULL){
                busca = temp->proximo;
            } else {
              busca->proximo = temp->proximo;        
            } 
        free (temp);
        break;
        }
        busca = temp;     
    }
}

void listar (list *inicio){
    list *temp;
    
    for (temp=inicio->proximo; temp!=NULL; temp=temp->proximo){
        printf ("%d\n", temp->elemento);
    }

}