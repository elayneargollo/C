#include <stdio.h>
#include <stdlib.h>

struct Estrutura {
    struct Estrutura *esquerda; 
    struct Estrutura *direita;
    int elemento; 
    int altura; 
};


struct Estrutura *novoNo (int elemento);
struct Estrutura *direitaRotacao (struct Estrutura *y);
struct Estrutura  *esquerdaRotacao (struct Estrutura *x);
struct Estrutura  *inserir (struct Estrutura* folha, int elemento);
struct Estrutura  *movimentar (struct Estrutura* folha, int balance, int elemento);
struct Estrutura *RemoverElement (struct Estrutura* raiz, int elemento);
struct Estrutura  *ElementoMinimo (struct Estrutura *No);
void preOrdem (struct Estrutura *raiz);
int max (int a, int b);
int altura (struct Estrutura *N);
int Balancear (struct Estrutura *N);


int altura(struct Estrutura *N) {
    if (N == NULL)
        return 0;
    return N->altura;
}

int max(int a, int b) {
	if (a > b){
		return a;
	} else {
		return b;
	}
}

struct Estrutura *novoNo(int elemento) { 

    struct Estrutura* folha = (struct Estrutura*) malloc(sizeof(struct Estrutura));

    folha->elemento = elemento;
    folha->esquerda = NULL;
    folha->direita = NULL;
    folha->altura = 1;

    return(folha);
}

struct Estrutura *direitaRotacao(struct Estrutura *y) { 
    struct Estrutura *x = y->esquerda;
    struct Estrutura *aux = x->direita;

    x->direita = y;
    y->esquerda = aux;

    y->altura = max(altura(y->esquerda), altura(y->direita))+1;
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;

    return x;
}

struct Estrutura *esquerdaRotacao(struct Estrutura *x) { 
    struct Estrutura *y = x->direita;
    struct Estrutura *aux = y->esquerda;

    y->esquerda = x;
    x->direita = aux;

    x->altura = max(altura(x->esquerda), altura(x->direita))+1;
    y->altura = max(altura(y->esquerda), altura(y->direita))+1;

    return y;
}

int Balancear(struct Estrutura *N) {  
    if (N == NULL){
        return 0;
	} else {
		return altura(N->esquerda) - altura(N->direita);
	}
}

struct Estrutura *inserir(struct Estrutura *folha, int elemento) { 
	int balance;

    if (folha == NULL){
        return(novoNo(elemento));
	}

    if (elemento < folha->elemento){ 
        folha->esquerda  = inserir(folha->esquerda, elemento);
	}
	else if (elemento > folha->elemento){ 
        folha->direita = inserir(folha->direita, elemento);
	}
    else
        return folha;

    folha->altura = 1 + max(altura(folha->esquerda), altura(folha->direita));
    balance = Balancear(folha);
	movimentar (folha, balance, elemento);

}

struct Estrutura *movimentar (struct Estrutura *folha, int balance, int elemento){

	if (balance > 1 && elemento < folha->esquerda->elemento){
        return direitaRotacao(folha);
	}

    if (balance < -1 && elemento > folha->direita->elemento){
        return esquerdaRotacao(folha);
	}

    if (balance > 1 && elemento > folha->esquerda->elemento){
        folha->esquerda =  esquerdaRotacao(folha->esquerda);
        return direitaRotacao(folha);
    }

    if (balance < -1 && elemento < folha->direita->elemento){
        folha->direita = direitaRotacao(folha->direita);
        return esquerdaRotacao(folha);
    }

	return folha;
}

struct Estrutura *RemoverElement(struct Estrutura *raiz, int elemento){
    struct Estrutura *Aux;
    int balance;
    
    if(raiz == NULL){
        printf("Elemento nao encontrado!\n");
    }else if(elemento < raiz -> elemento){
        raiz -> esquerda = RemoverElement(raiz -> esquerda, elemento);
    }else if(elemento > raiz -> elemento){
        raiz -> direita = RemoverElement(raiz -> direita, elemento);
    }else{
        if(raiz -> esquerda == NULL){
            Aux = raiz -> direita;
            free(raiz);
            return Aux;
        }else if(raiz -> direita == NULL){
            Aux = raiz -> esquerda;
            free(raiz);
            return Aux;
        }else{
        
			Aux = ElementoMinimo(raiz -> direita);
			raiz -> elemento = Aux -> elemento;
			raiz -> direita = RemoverElement(raiz -> direita, Aux -> elemento);
        }
    }
 
	if (raiz == NULL) {
      return raiz;
	}
 
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    balance = Balancear(raiz);
    movimentar (raiz, balance, elemento);
}

struct Estrutura *ElementoMinimo(struct Estrutura *No){
    struct Estrutura *Atual = No;
    
    while(Atual -> esquerda != NULL){
        Atual = Atual -> esquerda;
    }    
        
   return Atual;
   
}

void preOrdem(struct Estrutura *raiz) {

    if(raiz != NULL) {
        printf("%d ", raiz->elemento);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }

}

int main() {
  struct Estrutura *raiz = NULL;
  int valor;
  int op = 0;
  
    preOrdem(raiz);

    while(op != 3){
    	printf("\n\n");
    	printf("1. Inserir\n");
    	printf("2. Remover\n");
    	printf("3. Sair\n");
    	scanf("%d", &op);

    	if(op == 1){
    		printf ("Insira o elemento que deseja adcionar na arvore: ");
	  		scanf ("%d",&valor);

	  		raiz = inserir(raiz, valor);
	  		printf("\n");
	  		preOrdem(raiz);
    	}else if(op == 2){
    		printf ("\nInsira o elemento que deseja remover da arvore: ");
			scanf ("%d",&valor);

    		raiz = RemoverElement(raiz, valor);

   			printf("\n");
   			preOrdem(raiz);
    	}else{
    		printf("Opção invalida!\n");
    	}
    }

    free (raiz); 

    return 0;
}
