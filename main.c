#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void inicializaVetorPesos(double *w){
    int i;
    srand((double) time(NULL)); // mudar a sequencia usando o relógio

    printf("vetor pesos sinapticos original:\n");
    for(i=0;i<31;i++){ // inicializar os pesos c valores aleatórios entre 0 e 1
        w[i] = ((double) rand() / (double)(RAND_MAX));
        printf("%lf\n",w[i]);
    }
    printf("**************\n");
}

void inicializaEntradas(double entradas[31][3]){

    double entradasAux[31][3] =
    {
        {-1,-1,-1}, {-0.6508, 0.1097, 4.0009}, {-1.4492, 0.8896, 4.4005},
        {2.0850, 0.6876, 12.0710},{0.2626 , 1.1476, 7.7985},
        {0.6418, 1.0234, 7.0427},{0.2569, 0.6730, 8.3265},
        {1.1155, 0.6043, 7.4446},{0.0914, 0.3399, 7.0677},
        {0.0121, 0.5256, 4.6316},{-0.0429, 0.4660, 5.4323},
        {0.4340, 0.6870, 8.2287},{0.2735, 1.0287, 7.1934},
        {0.4839, 0.4851, 7.4850},{0.4089, -0.1267, 5.5019},
        {1.4391, 0.1614, 8.5843},{-0.9115, -0.1973, 2.1962},
        {0.3654, 1.0475, 7.4858},{0.2144, 0.7515, 7.1699},
        {0.2013, 1.0014, 6.5489},{0.6483, 0.2183, 5.8991},
        {-0.1147, 0.2242, 7.2435},{-0.7970, 0.8795, 3.8762},
        {-1.0625, 0.6366, 2.4707},{0.5307, 0.1285, 5.6883},
        {-1.2200, 0.7777, 1.7252},{0.3957, 0.1076,5.6623},
        {-0.1013, 0.5989, 7.1812},{2.4482, 0.9455, 11.2095},
        {2.0149, 0.6192, 10.9263},{0.2012, 0.2611, 5.4631},
    };

    int i,j;
    for(i=0;i<31;i++){
        for(j=0;j<3;j++){
            entradas[i][j] = entradasAux[i][j];
            //printf("%lf ",entradas[i][j]);
        }
        //printf("\n");
    }
}

void inicializaSaidasDesejadas(double *saidasDesejadas){

    double saidasDesejadasAux[30] = {-1.0000, -1.0000, -1.0000, 1.0000, 1.0000,
    -1.0000, 1.0000, -1.0000, 1.0000, 1.0000, -1.0000, 1.0000, -1.0000,
    -1.0000,-1.0000,-1.0000, 1.0000, 1.0000, 1.0000, 1.0000, -1.0000, 1.0000,
    1.0000,1.0000,1.0000,-1.0000,-1.0000,1.0000,-1.0000,1.0000};

    int i;
    for(i=0;i<30;i++){
        saidasDesejadas[i] = saidasDesejadasAux[i];
        //printf("%lf ",saidasDesejadas[i]);
    }
}

int sinal(double u){

    // neste caso estou utilizando uma função degrau bipolar

    if(u >= 0.0){

        return 1;
    }
    return -1;
}

int main()
{
    int barreiraDeSegurancaEpocas = 1000; // se em 1000 épocas nao convergir a rede para pois o conjunto nao é linearmente separável

    double entradas[31][3];
    inicializaEntradas(entradas);

    double saidasDesejadas[30];
    inicializaSaidasDesejadas(saidasDesejadas);

    double w[31]; // pesos sinápticos
    inicializaVetorPesos(w);

    double taxaAprendizado = 0.01,u;

    int contEpocas = 0;

    int erro,i,j,y;

    erro = 1; // inicialmente suponhamos que exista erro

    /// algoritmo de treinamento de Hebb
    while(erro!= 0 && contEpocas <= barreiraDeSegurancaEpocas){

        erro = 0;

        for(i=0;i<31;i++){

            u = 0.0;

            for(j=0;j<3;j++){

                u += w[i]*entradas[i][j]; /// produto escalar dos pesos e das entradas
            }

            y = sinal(u); /// sinal é a função de ativação

            if(y != saidasDesejadas[i]){

                for(j=0;j<3;j++){

                    w[i] = w[i] + taxaAprendizado * ( saidasDesejadas[i]- y ) * entradas[i][j];

                }
                erro = 1;
            }
        }
        contEpocas++;
    }

    printf("vetor pesos sinapticos final:\n");
    for(i=0;i<31;i++){

        printf("%lf\n",w[i]);
    }
    printf("@@@@@@@@@@@@@@@@\n\n");

    printf("qtd epocas = %d\n\n",contEpocas);

    // Fase de operação
    double testes[10][3] =
    {
        {-0.3565, 0.0620, 5.9891}, {-0.7842, 1.1267, 5.5912},
        {0.3012,0.5611, 5.8234},{0.7757 , 1.0648, 8.0677},
        {0.1570, 0.8028, 6.3040},{-0.7014, 1.0316, 3.6005},
        {0.3748, 0.1536, 6.1537},{-0.6920,0.9404,4.4058},
        {-1.3970, 0.7141, 4.9263},{-1.8842, -0.2805, 1.2548}
    };

    for(i=0;i<10;i++){

        for(j=0;j<3;j++){

            u = w[i] * testes[i][j];
            y = sinal(u);

            if(y==-1){
                printf("%lf pertence a classe A\n",testes[i][j]);
            }else
                printf("%lf pertence a classe B\n",testes[i][j]);
            }
    }
    return 0;
}
