#include <stdio.h>
#include <stdlib.h>
#define TAM 10

typedef struct estrutura {
	int tamanho;
	int numero;
	int *vetor;
	int fim;
	int posicao;
	struct estrutura *proximo;
} principal;

void inserir_secundaria(principal*);
principal* criar (int);
void inserir (principal*,int);
void listar (principal*);
int verificar_criacao (principal*,int);
void inserir_numero (principal*);
void ordenar_estrutura (int *temporario, int tamanho);
void listar_all_ordenado (principal *inicio);
void listar_ordenado (principal *);
void excluir_elemento (principal *);
int verificar_cheio (principal *, int);
void aumentar_estrutura (principal*);
void terminar (principal *);
int menu ();
void salvar_arquivo (principal *inicio);
void salvar_texto (principal *inicio, FILE *arq);
void salvar_binario (principal *inicio, FILE *arq);
void leitura (principal *inicio);
void leitura_texto (principal *inicio,FILE *arq);
void leitura_binario (principal *inicio,FILE *arq);

int main (){
	principal *inicio;
	int n=1,op,sair=0;
	
	inicio = (principal*) malloc (sizeof (principal));

	while (n<=TAM){ 
		inserir (inicio,n);
		n++;
	}
	
	leitura (inicio);

	while (!sair){
        op = menu();
        switch (op){
            case 0: {
                sair =1;
                terminar (inicio);
                break;
            }
            case 1: inserir_secundaria(inicio);
					break;
            case 2: listar (inicio);
					break;
			case 3: listar_ordenado (inicio);
					break;
		    case 4: listar_all_ordenado(inicio);
					break;
			case 5: excluir_elemento (inicio);
					break;	
			case 6: aumentar_estrutura (inicio);
					break;
            default:
                printf("opcao inválida\n");
            
        }
    }
	
	listar (inicio->proximo);
}

int menu(){
    int op;
    printf("\n========= Digite as opção desejada =========\n");
    printf("\n0 - Sair do Programa\n");
    printf("1 - Inserir Elemento\n");
    printf("2 - Listar All\n");
    printf("3 - Listar Ordenado \n");
    printf("4 - Listar todos ordenados\n");
    printf("5 - Excluir Elemento\n");
    printf("6 - Aumentar Estrutura\n");
    printf("\nOp.: ");
    scanf("%d", &op);
    
    return op;
}

void inserir (principal *inicio, int posicao){
	principal *temporario=NULL;	
	principal *novo= criar (posicao);
	
	if (inicio->proximo==NULL){
		inicio->proximo=novo;
	}
	else {
		temporario=inicio->proximo;
		while (temporario->proximo!=NULL){
			temporario = temporario->proximo;
		}
		temporario->proximo = novo;
	}
		
}

principal* criar (int posicao){
	principal *novo;
	
	novo = (principal*) malloc (sizeof(principal));
	
	novo->tamanho=0;
	novo->numero=0;
	novo->vetor=0;
	novo->fim=0;
    novo->posicao=posicao;
	
	novo->proximo=NULL;	
	
	return novo;
}

void inserir_secundaria (principal *inicio){
	principal *auxiliar=NULL;
	int posicao,contador=1;
	
	printf ("\n============ INSERIR ELEMENTO ==========");
	printf ("\n\nEscolha qual posicao deseja inserir: ");
	scanf ("%d",&posicao);
	
	for (auxiliar=inicio->proximo; auxiliar!=NULL; auxiliar=auxiliar->proximo){
		if (posicao==contador){
			
			auxiliar->posicao=posicao;
			
			if (verificar_criacao (auxiliar,posicao)) {
				inserir_numero (auxiliar);
			}
							
		} 
		
		contador++;
	}
}

void listar (principal *inicio){
	principal *auxiliar=NULL;
	int contador=1;
	
	printf ("\n=============== LISTAR TUDO ==============\n");
	for (auxiliar=inicio->proximo; auxiliar!=NULL; auxiliar=auxiliar->proximo){
		printf ("\n%d) =======================================\n",contador);
		printf ("Posicao da estrutura principal: %d\n",auxiliar->posicao);
		printf ("Tamanho da estrutura auxiliar: %d\n\n",auxiliar->tamanho);

		for (int i=0; i< (auxiliar->fim);i++){
			printf ("|%d| ",auxiliar->vetor[i]);
		}
		contador++;
	}
}

void inserir_numero (principal *no_estrutura){
	int numero;

	printf ("Insira o numero: ");
	scanf ("%d",&numero);
		
		if (no_estrutura->fim < no_estrutura->tamanho){
			
			no_estrutura->numero=numero;
			no_estrutura->vetor[no_estrutura->fim]=numero;
			no_estrutura->fim=no_estrutura->fim+1;
	
			printf ("\nNumero inserido com sucesso!\n");
		
		}  else 
		   printf ("\nMemoria cheia ! Não é possivel inserir.\n");
			
}

int verificar_criacao (principal *no_estrutura, int posicao){
	int total;
	
	if (no_estrutura->tamanho == 0 && no_estrutura->posicao==posicao){
		printf ("Escolha qual tamanho sua estrutura tera: ");
		scanf ("%d",&total); 
			
		if ( total!= 0 && total>0){
			no_estrutura->tamanho = total;
			no_estrutura-> vetor = malloc (total*sizeof(int));	
	
			return 1;
		} 	
		
		else if (total<=0){
				printf ("\nInforme um tamanho válido !\n");
				return 0;
		}	
	}
	
	return 1;

}

void ordenar_estrutura (int *temporario, int tamanho){
	int escolhido,j=0;

	for (int i = 1; i < tamanho; i++) { 
		escolhido = temporario[i];
		j = i - 1;
		
		while ((j >= 0) && (temporario[j] > escolhido)) {
		temporario[j + 1] = temporario[j];
		j--;
	}
		temporario[j + 1] = escolhido;
	}	 
	
}

void listar_ordenado (principal *inicio){
	principal *aux_principal=NULL;
	int *vetor_temp=NULL;
	int no_atual=1;
	
	for (aux_principal=inicio->proximo; aux_principal!=NULL; aux_principal=aux_principal->proximo){
		vetor_temp = malloc (aux_principal->tamanho*sizeof(vetor_temp));
		
		for (int i = 0; i < aux_principal->fim; i++){
			vetor_temp[i]=aux_principal->vetor[i];
		} 
		
		ordenar_estrutura(vetor_temp,aux_principal->fim);
		
		printf ("\n%d) ========== LISTAR ORDENADO =========\n",no_atual);
		printf("Posicao %d\n\n",no_atual);
		
		for (int i = 0; i < aux_principal->fim; i++){
			printf ("|%d| ",vetor_temp[i]);
		}
		free (vetor_temp);
		no_atual++;		
	}

}

void excluir_elemento (principal *inicio){
	int posicao,numero;
	principal *aux_principal=NULL;
		
	printf ("\n\n============ EXCLUIR ELEMENTO ==========");
	printf ("\nInforme a posicao da estrutura que deseja excluir: ");
	scanf ("%d",&posicao);

	if (verificar_cheio (inicio,posicao)){
		printf ("Informe o numero que deseja excluir: ");
		scanf ("%d",&numero);
		
		for (aux_principal=inicio->proximo; aux_principal!=NULL; aux_principal=aux_principal->proximo){
			if (aux_principal->posicao==posicao){
				for (int i=0; i< aux_principal->fim; i++){
					if (aux_principal->vetor[i]==numero){
						printf("Numero %d excluido com sucesso!\n",aux_principal->vetor[i]);
							while (i< aux_principal->fim){
								aux_principal->vetor[i]=aux_principal->vetor[i+1];
								i++;
							} aux_principal->fim = aux_principal->fim -1;
							  break;
					} else if (i==aux_principal->fim-1){
							printf ("O numero %d não existe na estrutura!\n",numero);
					} 
				} 
			} 
		}	
		
	} else printf ("\nNão há numero a ser excluido. Insira elementos na posicao informada!\n");
}

int verificar_cheio (principal *inicio, int posicao){
	principal *aux_principal=NULL;
	
	for (aux_principal=inicio->proximo; aux_principal!=NULL; aux_principal=aux_principal->proximo){		
		if (aux_principal->posicao == posicao && aux_principal->fim!=0){
			return 1;
		} 
	}

	return 0;
}

void aumentar_estrutura (principal *inicio){
	principal *aux_principal=NULL;
	int posicao,total;
	
	printf ("\n============ AUMENTAR ESTRUTURA ==========");
	printf ("\n\nInforme qual estrutura deseja aumentar: ");
	scanf ("%d",&posicao);
		
	for (aux_principal=inicio->proximo; aux_principal!=NULL; aux_principal=aux_principal->proximo){
		if ((aux_principal->posicao==posicao) && (aux_principal->tamanho!=0)) {
			printf ("Informe o tamanho adcional: ");
			scanf ("%d",&total);
			aux_principal->tamanho=aux_principal->tamanho + total;
			aux_principal->vetor = (int*) realloc (aux_principal->vetor,aux_principal->tamanho * sizeof(int));

			printf ("Novo tamanho: %d\n",aux_principal->tamanho);
			printf("Posicao: %d\n",aux_principal->posicao);
			break;
		}else if (aux_principal->posicao==posicao && aux_principal->tamanho==0){
			printf ("\nA estrutura escolhida ainda não foi criada!\n");
		} 	
	}
}

void listar_all_ordenado (principal *inicio){
	principal *auxiliar=NULL;
	int *vetor_temp;
	int fim=0,j=0;
	
	printf ("\n============ ORDENAR TUDO ==========\n");
	
	for (auxiliar=inicio->proximo; auxiliar!=NULL; auxiliar=auxiliar->proximo){
		fim = auxiliar->fim + fim;
	} 
	
	vetor_temp = malloc (fim*sizeof(vetor_temp));

	for (auxiliar=inicio->proximo; auxiliar!=NULL; auxiliar=auxiliar->proximo){
		for (int i=0; i<auxiliar->fim; i++){
			vetor_temp[j]=auxiliar->vetor[i];
			j++;
		}
	}
	ordenar_estrutura (vetor_temp,fim);
	
	for (j=0; j<fim; j++){
		printf ("|%d| ",vetor_temp[j]);
	}	
	
	printf ("\n");
	
	free (vetor_temp);
}

void terminar (principal *inicio){
	principal *temporario=inicio;
	principal *auxiliar=NULL;

	salvar_arquivo (inicio);
	
	for (temporario=inicio; temporario!=NULL; temporario=temporario->proximo){
		free (temporario->vetor);
		
		if (auxiliar!=NULL){
			free (temporario);
		}
		auxiliar=temporario;
	}
	
	if (auxiliar!=NULL){
		free (temporario);
	}
	
	exit (1);	
}

void salvar_arquivo (principal *inicio){
	FILE *arq;


	arq = fopen ("trab3.txt","w");
	
	if (arq == NULL){
		printf ("Erro ao tentar abrir o arquivo\n");
		exit (1);
	} 					
					
	salvar_texto (inicio,arq);			
	fclose (arq);
}

void salvar_texto (principal *inicio, FILE *arq){
	principal *aux_principal;
	
	for (aux_principal=inicio->proximo; aux_principal!=NULL; aux_principal=aux_principal->proximo){

		fprintf (arq, "\n%d,", aux_principal->tamanho);
		fprintf (arq, "%d,", aux_principal->numero);
		fprintf (arq, "%d,", aux_principal->fim);
		fprintf (arq, "%d;", aux_principal->posicao);
		
		for (int i=0; i<aux_principal->fim; i++){
			fprintf (arq, "%d;", aux_principal->vetor[i]);
		}			
	}
	
	printf ("Dados gravados com sucesso\n");
	
}

void leitura (principal *inicio){
	FILE *arq;
	
	arq = fopen ("trab3.txt","r");
	leitura_texto (inicio,arq);
	
}

void leitura_texto (principal *inicio,FILE *arq){
	principal *temp = inicio->proximo;
	
	if (arq == NULL){
			return;
	}
		
	for (temp=inicio->proximo; temp!=NULL; temp=temp->proximo){
		 
		fscanf (arq, "\n%d,", &temp->tamanho);
		fscanf (arq, "%d,", &temp->numero);
		fscanf (arq, "%d,", &temp->fim);
		fscanf (arq, "%d;", &temp->posicao);
			
		if (temp->tamanho > 0){
			 temp->vetor= (int *)malloc((temp->tamanho)*sizeof(int));  
			 if (temp->vetor == NULL){
					printf ("Memoria insuficiente\n");
			 } else
				for (int i=0; i<temp->fim; i++){
					fscanf (arq, "%d;", &temp->vetor[i]);
				}				
			}
	}
	
	fclose (arq);
	
}
