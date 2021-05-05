#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//Estruturas
typedef struct tabela {
    int termos;
    float x;
    float fx;
    float ponto;
}tabela;

typedef struct conta {
    float lx;
    float px;
}conta;

//FUNCOES
void intro(tabela *p_tabela, int qtd);                        
void alocaTabela(tabela **p, int tamanho);
void alocaConta(conta **p, int tamanho);
void contas(conta*p_conta, tabela*p_tabela);


int main(){
    int qtd;
    //PONTEIROS
    tabela *p_tabela;
    conta *p_conta;

    printf("\nDigite a quantidade de termos da sua tabela: ");
    scanf("%d", &qtd);

    //FUNCOES
    alocaTabela(&p_tabela, qtd); 
    alocaConta(&p_conta, qtd);
    intro(p_tabela,qtd);
    contas(p_conta,p_tabela);
}

void alocaTabela(tabela **p, int tamanho) {
    if ((*p = (tabela *) malloc(tamanho * sizeof(tabela))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
	}
}

void alocaConta(conta **p, int tamanho) {
    if ((*p = (conta *) malloc(tamanho * sizeof(conta))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
	}
}


void intro(tabela *p_tabela, int qtd){
    int i, j;

    //ATRIBUINDO VALOR DE QTD PARA TERMOS
    p_tabela->termos=qtd;
    
    //ARMAZENAMENTO DOS VALORES DE X
    for (i = 0; i < p_tabela->termos; i++) {
        printf("\nDigite os valores de X: ");
        printf("\nX(%d): ", i);
        scanf("%f", &((p_tabela+i)->x));
    }

    printf("\n\n");    
    printf("-------------------------------------");
    printf("\n\n");

    //ARMAZENAMENTO DOS VALORES DE FX
    for (j = 0; j < p_tabela->termos; j++) {
        printf("\nDigite os valores de F(x): "); 
        printf("\nF(X[%d]): ", j);
        scanf("%f", &((p_tabela+j)->fx));
            
    }

    printf("\n\n");    
    printf("-------------------------------------");
    printf("\n\n");

    //ARMAZENAMENTO DO PONTO 
    printf("\nDigite o ponto a ser interpolado: ");
    scanf("%f", &(p_tabela->ponto));

}

void contas(conta *p_conta, tabela *p_tabela) {
    int i, j;
    float lxfinal = 1;

    for(i=0; i < p_tabela->termos; i++) {
        lxfinal = 1; // zera o ponteiro para recomecar

        for(j=0; j < p_tabela->termos; j++){

            if(j==i) j++;

            float ponto = p_tabela->ponto;
            float xInicial = (p_tabela+i)->x;
            float xVariante = (p_tabela+j)->x;

            float cima = ponto - xVariante;
            float baixo = xInicial - xVariante;

            (p_conta+j)->lx = (cima / baixo);

            if(j != p_tabela->termos)
                lxfinal *= (p_conta+j)->lx;
        }
        p_conta->px += lxfinal * (p_tabela+i)->fx;
        printf("\n\nL(X[%d]): %f", i, lxfinal);
    }

    printf("\n\nValor de px = %f", p_conta->px);
}
 


        
