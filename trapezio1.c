//Matheus Henrique da Silva de Oliveira RA 200987
//Vitor Augusto de Lima Soares RA 200327

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Structs
typedef struct dados{
    float var;
    int grau;
} dados;

typedef struct h{
    float a;
    float b;
    float h;
    int n;
}h;

typedef struct tabela{
    float x;
    float fx;
}tabela;

//Funcoes
void alocaDados(dados **p_dados, int tamanho);
void alocaH(h **p_h, int tamanho);
void recebeDados(dados *p_dados, int tamanho);
void recebeDiv(h *p_h);
void calculaH(h *p_h);
void alocaTabela(tabela **p_tabela, int tamanho);
void montaTabela(dados *p_dados, h *p_h, tabela *p_tabela);
void calculoIT(dados *p_dados, h *p_h, tabela *p_tabela);

int main(){
    dados *p_dados = NULL;
    h *p_h = NULL;
    tabela *p_tabela = NULL;

    int qtd, qtdT;
    char d = 's';
    char d2 = 'n';

    do{
        system("cls");
        printf("\nDigite o grau do polinomio: ");
        scanf("%d", &qtd);

        if(qtd != 2){
            printf("\nPrograma em obras, por favor digite outro valor: ");
            scanf("%d", &qtd);
        }
    
        alocaDados(&p_dados, qtd);
        alocaH(&p_h, qtd);
        recebeDados(p_dados,qtd);
        recebeDiv(p_h);

        do{
            calculaH(p_h);

            //TAMANHO DA ALOCACAO DA TABELA DE VALORES
            qtdT = (p_h->n + 1);  
            alocaTabela(&p_tabela, qtdT);
 
            montaTabela(p_dados, p_h, p_tabela);
            calculoIT(p_dados, p_h, p_tabela);

            printf("\n\nDeseja calcular novamente com outro numero de trapezios ? (S/N): ");
            fflush(stdin);
            scanf("%c", &d);

        }while (d != 'n' && d != 'N');

        printf("\n\nDeseja encerrar o programa ? (S/N): ");
        fflush(stdin);
        scanf("%c", &d2);

    }while(d2 != 's' && d != 'S');
}

void alocaDados(dados **p, int tamanho) {
    if ((*p = (dados *)malloc(tamanho * sizeof(dados))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
    }
}

void alocaH(h **p, int tamanho) {
    if ((*p = (h *)malloc(tamanho * sizeof(h))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
    }
}

void alocaTabela(tabela **p, int tamanho) {
    if ((*p = (tabela *)malloc(tamanho * sizeof(tabela))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
    }
}

void recebeDados(dados *p_dados, int qtd){
    int i;

    //ATRIBUINDO VALOR DE QTD PARA GRAU
    p_dados->grau = qtd;

    printf("\nDigite os valores do polinomio: ");
    printf("\n\n f(x) = ax^2 + bx^1 + c ");
    printf("\n");
    for(i = 0; i < (p_dados->grau+1); i++){
        printf("\nDigite o valor de %c: ", 'a'+i);
        scanf("%f", &((p_dados+i)->var));
    }
}

void recebeDiv(h *p_h){
    printf("\n\nIntervalo - Calculo h");
    printf("\n\nDigiteo intervalo [a,b]");
    printf("\n[a]: ");
    scanf("%f", &p_h->a);
    printf("\n[b]: ");
    scanf("%f", &p_h->b);

    //VERIFICACAO PARA QUE A SEJA SEMPRE MENOR QUE B
    if(p_h->a > p_h->b){ //se a > b
        p_h->b = p_h->a; // a = b
        p_h->a = p_h->b; // a = b
        printf("\n\nAtencao - Intervalo incorreto:");
        printf("\nDigite um intervalor correto (a<b): ");
        printf("\n[a]: ");
        scanf("%f", &p_h->a);
        printf("\n[b]: ");
        scanf("%f", &p_h->b);
    }
}

void calculaH(h *p_h){
    int i;
    
    //RECEBE N
    printf("\nDigite o numero de divisoes do intervalo [%.2f, %.2f]: ", p_h->a, p_h->b);
    scanf("%d", &p_h->n);

    printf("\nh = (%.4f - %.4f) / %d", p_h->b, p_h->a, p_h->n);

    //CALCULA H
    p_h->h = (p_h->b - p_h->a) / p_h->n;
    
    printf("\nh: %f", p_h->h);
      
}

void montaTabela(dados *p_dados, h *p_h, tabela *p_tabela){
    //TABELA X = a + h, F(X) = polinomio fornecido
    //TAMANHO DA TABELA = N+1

    printf("\n\nTabela de Valores");

    int i,j,k;

    float a = p_h->a; //iniciando a var ao valor de p_h->a

    //VALORES DE X
    for(k = 0; k < (p_h->n + 1); k++){
        (p_tabela+k)->x = a; 
        a = a + p_h->h;// valor de a encrementado coma a soma de h
    }
    float x2, x1, x;

    //VALORES DE F(X)
    for(k = 0; k < (p_h->n + 1); k++){
        x2 = ((p_dados)->var * pow((p_tabela+k)->x, 2));
        x1 = ((p_dados+1)->var * pow((p_tabela+k)->x, 1));
        x = (p_dados+2)->var;
        (p_tabela+k)->fx = x2 + x1 + x;
    }

    //MONTAGEM TABELA
    printf("\n");
    printf("x\tf(x)");
    for(i = 0; i < 1; i++){ //COLUNA (independentemente sao 2 colunas)
        for(j = 0; j < (p_h->n + 1); j++){//LINHA
            printf("\n%.4f\t%.4f", (p_tabela+j)->x, (p_tabela+j)->fx);
        }
    }

}

void calculoIT(dados *p_dados, h *p_h, tabela *p_tabela){
    int i;
    float it, itr;
    float mult; 
    int tam = (p_h->n); //usado dentro do ponteiro para determinar o ultimo termo dentro do array
    float div = (p_h->h / 2);

    //para o calculo do itr o pv, vai somar o primeiro e o ultimo
    float pv = (p_tabela->fx + (p_tabela + tam)->fx);

    //REGRA DO TRAPEZIO COMPOSTOS
    if(p_h->n > 1){
        for(i = 1; i < (p_h->n); i++){
            mult += (p_tabela + i)->fx;
            itr =  div * (pv + (2 * (mult)));
        }
    printf("\n\nITR = %.4f", itr);
    }

    //REGRA DO TRAPEZIO SIMPLES
    if(p_h->n == 1){
        it = div * pv;
        printf("\n\nIT = %.4f", it);
    }
}