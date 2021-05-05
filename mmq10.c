//Matheus Henrique da Silva de Oliveira RA 200987
//Vitor Augusto de Lima Soares RA 200327

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//STRUCTS
typedef struct tabela
{
    int termos;
    float x;
    float y;
    int op;
} tabela;

typedef struct gauss
{
    float pv1;
    float pv2;
    float m21;
    float m31;
    float m32;
    float l2;
    float l3;
    float l32;
} gauss;

//FUNCOES
void alocacao(float **p, int tamanho);
void alocaT(tabela **p_tabela, int tamanho);
void alocaG(gauss **p_gauss, int tamanho);
void recebe_termos(tabela *p_tabela, int qtd);
void criacaoVet(tabela *p_tabela, float *mat);
void produtoEscalar(tabela *p_tabela, float *mat, float *matEscalar);
void calculaGauss(tabela *p_tabela, gauss *p_gauss, float *matEscalar);
void coeficientes(tabela *p_tabela, gauss *p_gauss, float *matEscalar);

int main()
{
    float *mat = NULL; //ponteiro para a matriz
    float *matEscalar= NULL;
    tabela *p_tabela = NULL;
    gauss *p_gauss = NULL;

    int qtd;
    char d = 's';

    do{
        system("cls");
        printf("\nDigite a quantidade de termos da sua tabela: ");
        scanf("%d", &qtd);

        alocaT(&p_tabela, qtd);
        alocaG(&p_gauss, qtd);

        printf("\nAjuste de funcao para: ");
        printf("\n[1]Reta");
        printf("\n[2]Parabola");
        printf("\n");
        scanf("%d", &p_tabela->op);

        if (p_tabela->op == 1){
            //alocacao reta
            alocacao(&mat, 6);
            alocacao(&matEscalar, 9);
        }
        else {
            // alocacao parabola
            alocacao(&mat, 9);
            alocacao(&matEscalar, 12);
        }
        recebe_termos(p_tabela, qtd);
        criacaoVet(p_tabela, mat);
        produtoEscalar(p_tabela, mat, matEscalar);
        calculaGauss(p_tabela, p_gauss, matEscalar);
        coeficientes(p_tabela, p_gauss, matEscalar);

        printf("\n\nDeseja calcular outro p(x) ? (S/N): ");
        flush(stdin);
        scanf("%c", &d);

    }while (d != 'n' && d != 'N');
}

void alocacao(float **p, int tamanho) {
    if ((*p = (float *)realloc(*p, tamanho * sizeof(float))) == NULL) {
        printf("Erro na alocação!");
        exit(1);
    }
}

void alocaT(tabela **p, int tamanho) {
    if ((*p = (tabela *)malloc(tamanho * sizeof(tabela))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
    }
}

void alocaG(gauss **p, int tamanho) {
    if ((*p = (gauss *)malloc(tamanho * sizeof(gauss))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
    }
}

void recebe_termos(tabela *p_tabela, int qtd) {
    int i, j;
    //ATRIBUINDO VALOR DE QTD PARA TERMOS
    p_tabela->termos = qtd;

    //ARMAZENAMENTO DOS VALORES DE X
    for (i = 0; i < p_tabela->termos; i++) {
        printf("\nDigite os valores de X: ");
        printf("\nX(%d): ", i);
        scanf("%f", &((p_tabela + i)->x));
    }

    printf("\n\n");
    printf("-------------------------------------");
    printf("\n\n");

    //ARMAZENAMENTO DOS VALORES DE Y
    for (j = 0; j < p_tabela->termos; j++) {
        printf("\nDigite os valores de Y: ");
        printf("\nY[%d]: ", j);
        scanf("%f", &((p_tabela + j)->y));
    }

    printf("\n\n");
    printf("-------------------------------------");
    printf("\n\n");
}

void criacaoVet(tabela *p_tabela, float *mat) {
    int i, j;
    // Define a parada para RETA = termos-1 e PARABOLA = termos
    int parada = p_tabela->op == 1 ? p_tabela->termos - 1 : p_tabela->termos;

    printf("\nVetores:\n");

    for (i = 0; i < p_tabela->termos; i++) { //LINHA
        for (j = 0; j < parada; j++) { //COLUNA
            *(mat + (i * p_tabela->termos) + j) = pow((p_tabela + i)->x, j); //x^0, x^1, x^2
            printf("%2.f\t", *(mat + (i * p_tabela->termos + j)));
        }
        printf("\n");
    }
}

void produtoEscalar(tabela *p_tabela, float *mat, float *matEscalar) {
    int i, j, k;
    float fixo1, var1, fixo2, var2, fixo3, var3;
    float y1 = p_tabela->y;
    float y2 = (p_tabela+1)->y;
    float y3 = (p_tabela+2)->y;
    
    // Define a parada para RETA = termos-1 e PARABOLA = termos
    int parada = p_tabela->op == 1 ? p_tabela->termos - 1 : p_tabela->termos;

    printf("\n Matriz Escalar:\n");

    for (i = 0; i < parada; i++) {
        fixo1 = *(mat + i);
        fixo2 = *(mat + p_tabela->termos + i);
        fixo3 = *(mat + (2 * p_tabela->termos) + i);
        
        for (j = 0; j < parada; j++) {
            var1 = *(mat + j); 
            var2 = *(mat + p_tabela->termos + j);
            var3 = *(mat + (2 * p_tabela->termos) + j);

            *(matEscalar + (i * p_tabela->termos + j + i )) = (fixo1 * var1) + (fixo2 * var2) + (fixo3 * var3);
            printf("%2.f\t", *(matEscalar + (i * p_tabela->termos + j + i )));
        }

        *(matEscalar + (i * p_tabela->termos + j + i )) = (fixo1 * y1) + (fixo2 * y2) + (fixo3 * y3);
        printf("%2.f\n", *(matEscalar + (i * p_tabela->termos + j + i )));
    }
}

void calculaGauss(tabela *p_tabela, gauss *p_gauss, float *matEscalar) {
    int i,j,k;

    p_gauss->pv1 = *matEscalar; // PIVO 1 = 00
    p_gauss->m21 = *(matEscalar + p_tabela->termos + 1) / p_gauss->pv1; // M21 = L2 / pivo
    p_gauss->m31 = *(matEscalar + (2 * p_tabela->termos) + 2) / p_gauss->pv1; // M31 = L3 / pivo  

    printf("\nEliminacao de Gauss\n");

    // RETA
    if(p_tabela->op == 1) {
        // Imprime primeira linha
        for (j = 0; j < 3; j++) {
            printf("%.2f\t", *(matEscalar + j));
        }

        printf("\n");

        // PASSO K1 => L2 = L2 - L1 * M21
        for (j = 0; j < 3; j++) { //coluna
            (p_gauss + j)->l2 = *(matEscalar + p_tabela->termos + j + 1) - *(matEscalar + j) * p_gauss->m21;
            printf("%.2f\t", (p_gauss + j)->l2);
        }
    }

    //PARABOLA
    if (p_tabela->op == 2) {
        // Imprime primeira linha
        for (j = 0; j < 4; j++) {
            printf("%.2f\t", *(matEscalar + j));
        }
        printf("\n");


        //PASSO K1 => L2 = L2 - L1 * M21
        for (j = 0; j < 4; j++) { //coluna
            (p_gauss + j)->l2 = *(matEscalar + p_tabela->termos + j + 1) - *(matEscalar + j) * p_gauss->m21;
            printf("%.2f\t",(p_gauss + j)->l2);
        }
        printf("\n");

        for (j = 0; j < 4; j++) { //coluna
            (p_gauss + j)->l3 = *(matEscalar + (2 * p_tabela->termos) + j + 2) - *(matEscalar + j) * p_gauss->m31;// L3 - L1 * M31

        }

        //PASSO K2
        p_gauss->pv2 = (p_gauss + 1)->l2;
        p_gauss->m32 = (p_gauss + 1)->l3 / p_gauss->pv2;

        for (j = 0; j < 4; j++) { //coluna
            (p_gauss + j)->l32 = (p_gauss + j)->l3 - (p_gauss + j)->l2 * p_gauss->m32;
            printf("%.2f\t",(p_gauss + j)->l32);
        }
    }
}

void coeficientes(tabela *p_tabela, gauss *p_gauss, float *matEscalar) { 

    float a1, a2, a0;

    printf("\n\nResposta: ");

    if (p_tabela->op == 1) {
        a1 = (p_gauss+2)->l2 / (p_gauss+1)->l2;
        a0 = (*(matEscalar +  2) - (*(matEscalar +  1) * a1)) / *(matEscalar +  0);
        printf("\na0= %.3f", a0);
        printf("\na1 = %.3f", a1);
        printf("\n\nA reta que melhor se aproxima a funcao tabelada e p(x) =  %.3f + %.3fx.", a0, a1);
    }

    if(p_tabela->op == 2){
        a2 = (p_gauss+3)->l32 / (p_gauss+2)->l32;
        a1 = ((p_gauss + 3)->l2 - ((p_gauss + 2)->l2 * a2)) / (p_gauss + 1)->l2;
        a0 =  (*(matEscalar +  3) - (*(matEscalar +  1) * a1) - (*(matEscalar +  2) * a2)) / *(matEscalar +  0);
        printf("\na0 = %.3f", a0);
        printf("\na1 = %.3f", a1);
        printf("\na2 = %.3f", a2);
        printf("\n\nO polinomio de 2 grau que melhor se aproxima a funcao tabelada e p(x) =  %.3f + %.3fx + %.3fx^2", a0, a1, a2);
    }
}
