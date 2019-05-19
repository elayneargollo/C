#include <stdio.h> 
#include <stdlib.h>
 
 typedef struct No { 
    int valor; 
    struct No *proximo; 
    struct No *anterior; 
 }no; 
 
 void inserir_fim (no **inicio, int valor);
 void inserir_inicio (no **inicio, int valor);
 void inserir (no **inicio);
 void listar (no *inicio);
 int buscar (no *inicio, int valor);
 
 int main (){
    no *inicio = NULL;
    int valor;
         
    for (int i=0; i<5;i++){
        inserir(&inicio);
    }
    
    printf ("Informe um elemento: ");
    scanf ("%d",&valor);
    
    if ((buscar (inicio,valor)) == valor){
        printf ("\nElemento %d foi encontrado na lista\n", valor);
    } else printf ("\nElemento %d não foi encontrado na lista\n", valor);
        
    listar (inicio);
 }
 
 void inserir_fim (no **inicio, int val){
     no *novo = (no*) malloc (sizeof(no));
     no *ultimo;
    
     ultimo = (*inicio)->anterior; 
    
    novo->valor = val;
    novo->proximo = (*inicio); 
    novo->anterior = ultimo; 
  
    (*inicio)->anterior = novo;
    ultimo->proximo = novo;
    
 }
 
 void inserir_inicio (no **inicio , int val){
    no *novo = (no*) malloc (sizeof(no));
    no *ultimo = (*inicio)->anterior;
    
    novo->valor = val;    
    novo->proximo = (*inicio);
    novo->anterior= ultimo;
    
    ultimo->proximo = novo;
    
    (*inicio)->anterior = novo;
    (*inicio) = novo;
 
 }
 
 void inserir (no **inicio){
     no *temp = (*inicio);
     int val;
     
     printf ("Informe o elemento a ser inserido: ");
     scanf ("%d", &val);
     
    no *novo = (no*) malloc (sizeof(no));
    no *proximo;
     
     if(temp == NULL) {
        novo -> valor = val;
        novo -> anterior = novo;
        novo -> proximo = novo;
        
        (*inicio) = novo; 
        
        return;
     }
             
    do {
         
        if(temp->proximo->valor > val){
            if((temp == (*inicio) && temp->valor > val)){
                inserir_inicio(inicio,val);
            }
            else if (temp->valor <= val && temp->proximo->valor > val){
                proximo = temp->proximo;
                proximo->anterior = novo;
           
                temp->proximo = novo;
                
                novo->valor = val;
                novo->anterior = temp;
                novo->proximo = proximo;
            }
            return;
        }
        temp = temp->proximo;
    } while (temp!=(*inicio));
        
    inserir_fim(&temp,val);
    
 }
 
void listar (no *inicio){
    no *temp = inicio;

    do { 
        printf ( "%d " , temp->valor); 
        temp = temp->proximo; 
    } while (temp != inicio);
    
} 
     
int buscar (no *inicio, int valor){
    no *temp = inicio;
    
    do {
        if (temp->valor==valor){
            return valor;        
        }
        temp = temp->proximo;
        
    } while (temp!=(inicio));
    
}