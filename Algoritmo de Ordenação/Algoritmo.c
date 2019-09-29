#include <stdio.h>
#define TAM 3

void inserir ();
void InsertSort ();
void imprime ();
void menu ();
void BubbleSort ();
void SelectSort();
void ShellSort ();

int main (){
	int vt[TAM];
	
	inserir (vt);
	menu (vt);
	imprime (vt);
}

void inserir (int *vt){
	int i;
	
	printf ("\n\n========= Alimente o vetor =========\n");
	for (i=0; i<=TAM; i++){
		printf ("vt[%d]: ",i);
		scanf (" %d",&vt[i]);		
	}
}

void menu (int *vt){
	int op;
	
	do {
	printf ("\n========== Menu de Selecao ==============\n");
	printf ("1- InsertSort                  2- BubblerSort\n");
	printf ("3- SelecSort                   4- ShellSort   \n");
	printf("op. ");
	scanf ("%d",&op);
	
	switch (op){
		case 1: InsertSort (vt);
				break;
		case 2: BubbleSort (vt);
				break;
		case 3: SelectSort (vt);
				break;	
		case 4: ShellSort (vt);
				break;
		default: printf ("Opção Inválida\n"); 
				 menu(vt);
	}
	
	} while (op>=1 && op<=4);
}

void BubbleSort (int *vt){
	int i, troca=1, aux;
	
	while (troca==1){     //  ---------->  n - 1       
		troca=0; 		 //  ---------->  n - 1
		for (i=0; i<=TAM-1; i++){   //  ---------->  n(n - 1)
			if (vt[i]>vt[i+1]){    //  ---------->  n(n - 1)
				aux = vt[i]; 	  //  ---------->  n(n - 1)
				vt[i] = vt[i+1]; //  ---------->  n(n - 1)
				vt[i+1]=aux;    //  ---------->  n(n - 1)			
				troca=1;       //  ---------->  n(n - 1)
			}
		}	
	}
} // Pior caso: t(n)= 2(n-1) + 6n(n-1)/2 ; Médio caso: t(n)= 2(n-1) + 6n(n-1)/2

void InsertSort (int *vt){  // Analogia: funciona como jogo de baralho 
	int aux,j,i;

	for (i=1; i<TAM; i++){   //  ---------->  n - 1
		aux = vt[i];        //  ---------->  n - 1
		j=i-1; 				//  ---------->  n - 1

		while ((j>=0) && (vt[j]>aux)){   //  ---------->  n(n - 1)/2
			vt[j+1]=vt[j]; 				//  ---------->  n(n - 1)/2
			j--; 						//  ---------->  n(n - 1)/2
		}
		vt[j+1]=aux;					// n - 1;
	}
} // Pior caso: t(n)= 4(n-1) + 3n(n-1)/2 ; Médio caso: t(n)= 4(n-1) + 3n(n-1)/4

void SelectSort (int *vt){
  int i, j, min, aux;
  
  for (i = 0; i < (TAM-1); i++) {   // ---------->  n-1
     min = i;						// ---------->  n-1
     for (j = (i+1); j < TAM; j++) { // --------->  n(n-1)/2
       if(vt[j] < vt[min]) 			// --------->  n(n-1)/2
         min = j;					// --------->  n(n-1)/2
		}
     if (vt[i] != vt[min]) {		// ---------->  n-1
       aux = vt[i];					// ---------->  n-1
       vt[i] = vt[min];				// ---------->  n-1
       vt[min] = aux;				// ---------->  n-1
     }
  }
} // Pior caso: t(n)= 6(n-1) + 3n(n-1)/2 ; Médio caso: t(n)= 6(n-1) + 3n(n-1)/4

void imprime (int *vt){
	int i;
	
	printf ("\n========== Vetor Ordenado ==========\n");
	for (i=0; i<=TAM; i++){
		printf("Vt[%d]: %d\n",i,vt[i]);
	}
}

void ShellSort (int *vt){
	int i,j,aux;
	
	int salto=1; // -----> 1
	do { // ----> n/3
		salto = 3*salto+1; // ----> n/3
	} while (salto<TAM); // ----> log2N*(n/3)
	
	do {  // ---> log2N
		salto = salto/3; // ---> log2N
		for (i=salto; i<=TAM; i++){ // ----> log2N * (n)
			aux = vt[i]; // -----> 1
			j = i - salto; // -----> 1
			
			while (j>=0 && aux<vt[j]){ // ----> log2N * (n)
				vt[j+salto] = vt[j]; // -----> 1
				j -=salto;// -----> 1
			}
			vt[j+salto]=aux;// ----> log2N * (n)
		}
		
	} while (salto >1);// ----> log2N 
}
