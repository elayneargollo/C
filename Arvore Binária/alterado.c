#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

int menu_geral ();
void ler_arquivo();
int display_arquivo ();
int menu_arquivo ();
void criar_arquivo (char *endereco);
void apagar_arquivo();
void mover_arquivo();
void editar_arquivo ();
void local_arquivo ();
void mostrar_diretorio();
void formar_endereco (char *pasta, char *arquivo, char *caminho);
void Acessar_Dir();
void Voltar();
int menu_diretorio ();
int display_diretorio ();
void criar_diretorio ();
void apagar_diretorio ();
void formar_endereco_diretorio (char *pasta);


int menu_geral (){
    int op;
    
    printf ("========= Menu =========\n");
    printf ("1- Opcoes de arquivo\n");
    printf ("2- Opcoes de diretorio\n");
    printf("3- Sair\n");
    printf ("Escolha uma opcao: ");
    scanf ("%d", &op);
    
    return op;
}

int display_arquivo (){ /*Alterado*/
    int arquivo;
       
    do{
    	mostrar_diretorio();

    	arquivo = menu_arquivo();

        switch (arquivo){
            case 1: local_arquivo(); 
                    break;

            case 2: ler_arquivo ();
                    break;

            case 3: editar_arquivo();
                    break;

            case 4: mover_arquivo();
                    break;

            case 5: apagar_arquivo ();
                    break;

           	case 6: Acessar_Dir();
           			break;

            case 7: Voltar();
            		break;

           	case 8: exit(0);
           			break;

            default: printf ("Opcao Invalida\n");
            		 break;       
        }

        printf("\n");

    }while (arquivo);  
}

int menu_arquivo (){    
    int op;
    
    printf (" ======== Display Arquivo ========= \n");
    printf ("1- Criar Arquivo\n");
    printf ("2- Ler arquivo\n");
    printf ("3- Editar um arquivo\n");
    printf ("4- Mover arquivo\n");
    printf ("5- Apagar arquivo\n");
    printf ("6- Acessar diretorio\n");
    printf("7- Voltar diretorio\n");
    printf("8- Sair\n");
    printf("Escolha uma opcao: ");
    scanf ("%d", &op);
    
    return op;

}

void mover_arquivo(){
	char NomeArq[30];
	char Comando[100] = "copy ";
	char EnderecoAtual[30];
	char NovoEndereco[30];
	char space[] = " ";
	char Token[] = "\\";
	char Comando2[50] = "erase ";

	printf("Insira o nome do arquivo que deseja mover: ");
	scanf("%s", NomeArq);

	getcwd(EnderecoAtual, sizeof(EnderecoAtual));

	printf("Insira o novo caminho para o arquivo: ");
	scanf("%s", NovoEndereco);

	strcat(EnderecoAtual, Token);
	strcat(EnderecoAtual, NomeArq);
	strcat(Comando, EnderecoAtual);
	strcat(Comando, space);
	strcat(Comando, NovoEndereco);
	strcat(Comando2, NomeArq);

	printf("%s", Comando);
	system(Comando);
	system(Comando2);
}

void ler_arquivo(){
	FILE *arq;
	char NomeArq[30];

	printf("Insira o nome do arquivo que deseja ler: ");
	scanf("%s", NomeArq);

	arq = fopen(NomeArq, "r");

	if(arq == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		printf("Digite qualquer tecla para continuar...\n");
		getchar();
	}

	char *Texto = (char *)malloc(sizeof(arq));

	printf("\n");

	while(fgets(Texto, sizeof(arq), arq) != NULL){
		printf("%s", Texto);
	}

	printf("Digite qualquer tecla para continuar...\n");
	getchar();	

	fclose(arq);

	free(Texto);
}

void mostrar_diretorio(){
    //system("cls");

	printf("\n");
	system("dir");
	printf("\n");
}

void Voltar(){
    
    chdir("..");
}

void Acessar_Dir(){
    char Dir[30];
    char Adress[17] = "C:\\trab\\Raiz\\";

    printf("Insira a pasta que deseja acessar (digite '.' para acessar raiz): ");
    scanf("%s", Dir);

    printf("\n");
    strcat(Adress, Dir);
    printf("%s", Adress);
    chdir(Adress);

    if(!chdir(Adress)){
        printf("Pasta inexistente!\n");
		printf("Digite qualquer tecla para continuar...\n");
		getchar();
    }
}

void apagar_diretorio(){
	char Dir[30];
	char Token[3] = "rd ";
	int retorno = 0;

	printf("Insira diretorio a ser excluido: ");
	scanf("%s", Dir);

	strcat(Token, Dir);

	if(!system(Token)){
		printf("\nDiretorio inexistente!\n");
		printf("Digite qualquer tecla para continuar...\n");
		getchar();
	}
}

int display_diretorio (){
    int diretorio;
    
    do{
    	mostrar_diretorio();

    	diretorio = menu_diretorio ();

        switch (diretorio){
            case 1: criar_diretorio ();
            		break;

            case 2: apagar_diretorio ();
                    break;

            case 3: Acessar_Dir();
                    break;

            case 4: Voltar();
            		break;

            case 5: exit(0);
                    break;

            default: printf ("Opcao Invalida\n");
            		 break;       
        }

        printf("\n");

    }while (diretorio);   

}

int menu_diretorio (){
    int op;
    
    printf ("\n ======== Display Diretorio ========= \n");
    printf ("1- Criar Diretorio\n");
    printf ("2- Apagar Diretorio\n");
    printf ("3- Acessar Diretorio\n"); //Ã‰ acessar diretorio mesmo ou mover arquivos?
    printf("4- Voltar\n");
    printf("5- Sair\n");
    printf("Escolha uma opcao: ");
    scanf ("%d", &op);
    
    return op;
}

int main(int argc, char** argv) {
    int display; 
    
    display = menu_geral ();
    
    do {
        switch (display){
            case 1: display_arquivo ();
            		menu_arquivo ();
            		break;

            case 2: display_diretorio ();
                    break;

            case 3: exit(0);
                    break;

            default : printf ("Opcao Invalida\n");       
        }
    } while (display);   
    
}

void criar_diretorio (){ /*Alterado*/
	char pasta[20];  
    
    printf ("Informe o nome da pasta: ");
    fflush (stdin);
    gets (pasta); 
   
    formar_endereco_diretorio (pasta);
    
}

void formar_endereco_diretorio (char *pasta){  /*criado e comentado*/
	char Comd[19] = "mkdir C:\\trab\\Raiz\\" ; // seria a pasta raiz , todas as novas sao criadas dentro dela

	strcat(Comd, pasta);
	
	/* Se a pasta já existe, ele informa se não, ele cria. Como estava antes */
	if (!system(Comd)){ 
        chdir("C:\\trab\\Raiz"); // isso so deve ser implementado quando conseguirmos identificar se pasta raiz existe ou nao. Por enquanto, so funciona quando nao existe raiz.
		printf("Sua pasta foi criada em Raiz \nPressione Enter para continuar! "); 
		getchar();  
	}
	
}

void local_arquivo (){ /*criado*/
	char escolha;
	char pasta[20];
	char quebra [3]="\\";
    char endereco[41]= "C:\\Trab\\Raiz\\"; // caso dê erro, verifica se entre as aspas e C tem algum espaco
    
    criar_arquivo (endereco);
}

void criar_arquivo (char *endereco){  /*Alterado*/
    FILE *arq;
    char arquivo [10]; 
    char txt [5] = ".txt"; 
    char escreva [200];
    		
    printf ("Informe o nome do documento: ");
    fflush (stdin);
    gets (arquivo);
    
    strcat(arquivo, txt);	
    
	strcat(endereco,arquivo);

    arq = fopen (endereco, "a");   
    
    if (arq == NULL) { 
    	printf ("\nErro ao criar arquivo\n");
		printf("Digite qualquer tecla para continuar...\n");
		getchar();
    } 
	else {
    	printf ("\nArquivo criado com sucesso! \n\n");
		printf("Digite qualquer tecla para continuar...\n");
		getchar();	
	}

    fclose (arq);
}

void apagar_arquivo (){ /*Alterado e comentado*/
    FILE *arq;
    char pasta [10]; 
    char arquivo [10]; 
    char endereco [60];  
    char* caminho = malloc(30 * sizeof(char));
    
    printf ("Informe o nome do documento: ");
    fflush (stdin);
    gets (arquivo);
         
    sprintf (endereco, "%s/%s.txt",pasta,arquivo);

    formar_endereco (pasta,arquivo,caminho); // chama algoritmo de busca
  	
	arq = fopen (endereco, "w"); 
  	 
   if (arq){
    	fclose (arq);
    	 
       	remove(caminho);
    	printf ("\nArquivo removido com sucesso ! \n");
		printf("Digite qualquer tecla para continuar...\n");
		getchar();

   }
   
}

void formar_endereco (char *pasta, char *arquivo, char* caminho){ /*Esta formando endereco*/
    char quebra [3] = "\\";
    char txt [5] = ".txt";    
    
    strcpy(caminho, pasta);	
    strcat(caminho,quebra);
    strcat(caminho,arquivo);
    strcat(caminho,txt);
    
}

void editar_arquivo (){ /*Alterado e comentado*/
 	FILE *arq;
 	char escreva[200];
    int a;
    char c;
	char* caminho = malloc(30 * sizeof(char));
    
    /* Isso se transformara em struct */
    char pasta [10]; /*nome da pasta*/
    char arquivo [10]; /*nome do arquivo*/
    char endereco [60]; /*nome do endereco*/
    /*===========================================*/
   
    
    printf ("* Informe o nome do documento: ");
    fflush (stdin);
    gets (arquivo);
       
    sprintf (endereco, "%s/%s.txt",pasta,arquivo);

    formar_endereco (pasta,arquivo,endereco); // chama algoritmo de busca
  	
	arq = fopen (endereco, "w"); 
		
	printf ("Arquivo aberto para Escrita\n");
	fflush (stdin);
	gets (escreva);
	fflush (stdin);
	fprintf (arq, "%s", escreva);	

 	fclose (arq); 	
 	
 	printf ("Dados gravados com sucesso\n");
	printf("Digite qualquer tecla para continuar...\n");
	getchar();
}
