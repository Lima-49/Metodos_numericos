#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct baskara {
    int termos;
    float coef[10];
    float expo[10];
    float x1;
    float x2;
    float precisao;
    float k;
} baskara;

typedef struct linha {
    float a;
    float m;
    float b;
    float fa;
    float fm;
    float fb;
    float paradaK;
} linha;

baskara intro();
float calculaK(float a, float b, float precisao);
float funcao(baskara p_baskara, linha *p_linha, float variavel);
void alocaTabela(linha **p, int tamanho);
void montaTabela(linha *tabela, baskara p_baskara);
void mostraTabela(linha *p_linha, baskara p_baskara);
void verificaIntervalo(linha *p_linha);
float paradaK(baskara p_baskara);


int main() {
    baskara p_baskara = intro();

    linha *tabela;
    alocaTabela(&tabela, p_baskara.k);
    montaTabela(tabela, p_baskara);
    mostraTabela(tabela, p_baskara);
}

void montaTabela(linha *p_linha, baskara p_baskara) {
    
    
    for (int i = 0; i < p_baskara.k; i++, p_linha++) {
        if (i == 0) {
            p_linha->paradaK = (p_baskara.x2 - p_baskara.x1);
            p_linha->a = p_baskara.x1;
            p_linha->b = p_baskara.x2;
        }
        else {
            verificaIntervalo(p_linha);
        }

        // Média m
        p_linha->m = (p_linha->a + p_linha->b) / 2;

        // Funções
        p_linha->fa = funcao(p_baskara, p_linha, p_linha->a);
        p_linha->fm = funcao(p_baskara, p_linha, p_linha->m);
        p_linha->fb = funcao(p_baskara, p_linha, p_linha->b);

        //Parada b-a
        p_linha->paradaK = paradaK(p_baskara);

        
    }
   
}

void alocaTabela(linha **p, int tamanho) {
    if ((*p = (linha *) malloc(tamanho * sizeof(linha))) == NULL) {
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
	}
}

baskara intro() {
    int termos;

    printf("\nDigite a quantidade de termos da sua equacao (max 10): ");
    scanf("%d", &termos);

    if (termos >= 10) {
    
        printf("\nInsira um numero valido de termos");
        system("cls");
        return intro();
    }
    else {
        baskara p_baskara;

        p_baskara.termos = termos;

        for (int i = 0; i < p_baskara.termos; i++) {
            printf("\nDigite o valor do '%c' e o expoente de x: ", 'a'+i);
            scanf("%f %f", &p_baskara.coef[i], &p_baskara.expo[i]);
        }

        printf("\nDigite o valor do intervalo (a,b): ");
        scanf("%f,%f", &p_baskara.x1, &p_baskara.x2);

        printf("\nDigite o valor da precisao: ");
        scanf("%f", &p_baskara.precisao);

        // Calcula o K
        p_baskara.k = calculaK(p_baskara.x1, p_baskara.x2, p_baskara.precisao);

        return p_baskara;
    }
}

float funcao(baskara p_baskara, linha *p_linha, float variavel) {
    float resultado = 0;

    for (int i = 0; i < p_baskara.termos; i++) {
        resultado += p_baskara.coef[i] * pow(variavel, p_baskara.expo[i]);
    };

    return resultado;
}

float calculaK(float a, float b, float precisao) {
    float k = ((log(b - a) - log(precisao)) / log(2));

    if(k < 0) {
        k *= -1;
    }

    return ceil(k);
}

void mostraTabela(linha *p_linha, baskara p_baskara) {
    
    printf("\ni\ta\t\tm\t\tb\t\tf(a)\tf(m)\tf(b)\t(b-a)");

    // Da pra só iterar o 'p_linha' que ele entende que é o próximo ponteiro e mantem o 'i' pra controlar o for
    for (int i = 0; i < p_baskara.k; i++, p_linha++) {
        printf("\n\n%d\t%2.3f\t%2.3f\t%2.3f\t%2.3f\t%2.3f\t%2.3f\t%2.3f", i, p_linha->a, p_linha->m, p_linha->b, p_linha->fa, p_linha->fm, p_linha->fb, p_linha->paradaK);
    }

    // Pega da última linha da coluna (p_linha - 1), porque o 'p_linha' ta com o endereço da última linha + 1
    printf("\n\nA raiz da funcao e %.3f com erro de %.3f (< %.3f)", (p_linha-1)->m, (p_linha-1)->fm, p_baskara.precisao);
    printf("\nA quantidade de iteracoes e k = %.3f", p_baskara.k);
}

void verificaIntervalo(linha *p_linha) {
    // Valores da linha anterior
	float a_anterior = (p_linha-1)->a;
	float b_anterior = (p_linha-1)->b;
	float m_anterior = (p_linha-1)->m;

    // Se f(a) * f(m) < 0; b = m anterior, se não b = b anterior;
	if ((p_linha-1)->fa * (p_linha-1)->fm < 0)
		p_linha->b = m_anterior;
	else
		p_linha->b = b_anterior;

    // Se f(b) * f(m) < 0; a = m anterior, se não a = a anterior;
	if ((p_linha-1)->fb * (p_linha-1)->fm < 0)
		p_linha->a = m_anterior;
	else
		p_linha->a = a_anterior;
}

float paradaK(baskara p_baskara){
    float r;
    r = (p_baskara.x2 - p_baskara.x1);
    return r;
}