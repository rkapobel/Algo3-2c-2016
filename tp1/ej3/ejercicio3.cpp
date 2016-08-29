#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int max(int a, int b){
    return (a > b) ? a : b;
}

void maxProfitForAnObjectInAKnapSack(int objectUsed, int **objectsInfo, int M, int *knapSacksCapacities, int N, int *objectsValues, int *objectsWeights){
    int i, w;
    
    int maxCapacity = knapSacksCapacities[M-1];
    
    int K[N][maxCapacity + 1]; // la mochila con peso 0 es para finalizar
    
    printf("calculating profit if i put object (%d, %d) for each knapsack: \n", objectsValues[objectUsed], objectsWeights[objectUsed]);
    for (i = 0; i < N; i++) {
        for (w = 0; w <= maxCapacity; w++) {
            if (w == 0){
                K[i][w] = 0;
            }else if (objectsWeights[i] <= w && i != objectUsed){
                if (i == 0) {
                    K[i][w] = objectsValues[i];
                }else {
                    K[i][w] = max(objectsValues[i] + K[i - 1][w - objectsWeights[i]], K[i - 1][w]);
                }
            }else {
                //entra acá si no habia espacio o el objeto ya fue usado
                if (i == 0) {
                    K[i][w] = 0;
                }else {
                    K[i][w] = K[i - 1][w];
                }
            }
            printf("%d |", K[i][w]);
        }
        printf("\n");
    }
    printf("\n");
    
    // no se cuantas mochilas hay
    int maxM1Profit = -1;
    int maxM2Profit = -1;
    int maxM3Profit = -1;
    
    //la mochila en donde meti el objeto usado (j) tiene menos capacidad: capacidad(mochila usada)-peso(objeto usado)
    for (int knapSackUsed = 0; knapSackUsed < M; knapSackUsed++) {
        int actualKnapSackCapacity = knapSacksCapacities[knapSackUsed]-objectsWeights[objectUsed];
    
        // si pasa esto el objeto no entra en la mochila porque es mas pesado
        if (actualKnapSackCapacity < 0) {
            if (knapSackUsed == 0) {
                maxM1Profit = 0;
            }else if (knapSackUsed == 1) {
                maxM2Profit = 0;
            }else {
                maxM3Profit = 0;
            }
        }else {
            if (knapSackUsed == 0) {
                maxM1Profit = K[N-1][actualKnapSackCapacity];
            }else if (knapSackUsed == 1) {
                maxM2Profit = K[N-1][actualKnapSackCapacity];
            }else {
                maxM3Profit = K[N-1][actualKnapSackCapacity];
            }
            
            for (int z = 0; z < M; z++) {
                if (z != knapSackUsed) {
                    if (knapSackUsed == 0) {
                        maxM1Profit += K[N-1][knapSacksCapacities[z]];
                    }else if (knapSackUsed == 1) {
                        maxM2Profit += K[N-1][knapSacksCapacities[z]];
                    }else {
                        maxM3Profit += K[N-1][knapSacksCapacities[z]];
                    }
                }
            }
        }
    }
    
    int maxKnapSack = maxM1Profit;
    
    if (maxM2Profit >= maxM1Profit && maxM2Profit >= maxM3Profit) {
        maxKnapSack = maxM2Profit;
    }
    
    if (maxM3Profit >= maxM1Profit && maxM3Profit >= maxM2Profit) {
        maxKnapSack = maxM3Profit;
    }
    
    // si hay dos maximos quiere decir que ese objeto no influye, por lo tanto no conviene meterlo en esas mochilas.
    // esto parece que se genera cuando un objeto entra justo en una mochila dejando 0 capacidad a esa mochila y las otras dos maximizan igual.
    // tengo un caso en donde hay dos objetos que entran justo, utilizo la regla anterior pero luego, como es de esperar uno de los objetos sobra y se lo podria haber llevado otra mochila.
    
    if (maxM1Profit == maxKnapSack || maxM2Profit == maxM3Profit) {
        objectsInfo[objectUsed][0] = 0;
        objectsInfo[objectUsed][1] = -1;
        objectsInfo[objectUsed][2] = -1;
    }else if (maxM2Profit == maxKnapSack || maxM1Profit == maxM3Profit) {
        objectsInfo[objectUsed][0] = -1;
        objectsInfo[objectUsed][1] = 1;
        objectsInfo[objectUsed][2] = -1;
    }else if (maxM3Profit == maxKnapSack || maxM2Profit == maxM1Profit) {
        objectsInfo[objectUsed][0] = -1;
        objectsInfo[objectUsed][1] = -1;
        objectsInfo[objectUsed][2] = 2;
    }
    
    objectsInfo[objectUsed][3] = false; // no usado
    
    printf("knapsacks that maximize object %d, %d, %d \n\n", objectsInfo[objectUsed][0], objectsInfo[objectUsed][1], objectsInfo[objectUsed][2]);
    printf("object (%d,%d) maximums are (%d, %d, %d) \n\n", objectsValues[objectUsed], objectsWeights[objectUsed], maxM1Profit, maxM2Profit, maxM3Profit);
}

int profitForAKnapSack(int **objectsInfo, int knapSack, int knapSackCapacity, int N, int *objectsValues, int *objectsWeights) {
    int i, w;
    
    int K[N][knapSackCapacity + 1]; // la mochila con peso 0 es para finalizar
    
    // Build table K[][] in bottom up manner
    printf("profit for a knapsack %d: \n", knapSack);
    for (i = 0; i < N; i++) {
        for (w = 0; w <= knapSackCapacity; w++) {
            //printf("\n\n object (%d, %d) for knapsack: %d used: %d \n\n", objectsValues[i], objectsWeights[i], objectsInfo[i][knapSack], objectsInfo[i][3]);
            if (w == 0){
                K[i][w] = 0;
            }else if (objectsWeights[i] <= w && objectsInfo[i][knapSack] == knapSack && objectsInfo[i][3] == false){
                // condiciones adicionales: que esta mochila maximize para el objeto, y que no se haya usado en otra que tambien maximize
                if (i == 0) {
                    K[i][w] = objectsValues[i];
                }else {
                    K[i][w] = max(objectsValues[i] + K[i - 1][w - objectsWeights[i]], K[i - 1][w]);
                }
            }else {
                //entra acá si no habia espacio o el objeto no me convenia meterlo en la mochila knapsack
                if (i == 0) {
                    K[i][w] = 0;
                }else {
                    K[i][w] = K[i - 1][w];
                }
            }
            printf("%d |", K[i][w]);
        }
        printf("\n");
    }
    printf("\n");
    
    int actualCol = knapSackCapacity;
    int actualRow = N-1;
    printf("objects used in knapsack %d of capacity %d { \n\n", knapSack, knapSackCapacity);
    while (actualRow >= 0 && actualCol >= 0) {
        if (actualCol == 0) {
            actualCol=-1;
        }else if (actualRow == 0) {
            if (K[actualRow][actualCol]) {
                objectsInfo[actualRow][3] = true; // usado
                printf("used object (%d, %d) \n", objectsValues[actualRow], objectsWeights[actualRow]);
            }
            actualRow=-1;
        }else if (K[actualRow-1][actualCol] != K[actualRow][actualCol]) {
            objectsInfo[actualRow][3] = true; // usado
            printf("used object (%d, %d) \n", objectsValues[actualRow], objectsWeights[actualRow]);
            actualCol = abs(actualCol-objectsWeights[actualRow]); // por si acaso, valor absoluto.
            actualRow--;
        }else{
            actualRow--;
        }
    }
    
    printf("} \n");
    
    return K[N-1][knapSackCapacity];
}

void multipleKnapSackProblem(int M, int N, int *knapSacksCapacities, int *objectsValues, int *objectsWeights) {
    
    // Asumo para hacer mas simple por ahora que las mochilas vienen ordenadas por peso, lo mismo los objetos de menor a mayor.
    // Y que las clases son resueltas antes de esta llamada. Por lo tanto N es el TOTAL de objetos.
    
    int **objectsInfo = new int*[N];
    for (int i = 0; i < N; i++)
        objectsInfo[i] = new int[4]; // (maximiza M1, maximiza M2, maximiza M3, usado)
    
    int j = 0;
    while (j < N) {
        maxProfitForAnObjectInAKnapSack(j, objectsInfo, M, knapSacksCapacities, N, objectsValues, objectsWeights);
        
        j++;
    }
    
    int totalValue = 0;
    
    for (int knapSack = 0; knapSack < M; knapSack++) {
        totalValue += profitForAKnapSack(objectsInfo, knapSack, knapSacksCapacities[knapSack], N, objectsValues, objectsWeights);
    }
    
    printf("\n total value: %d \n", totalValue);
    
    delete [] objectsInfo;
}

int main(){
    
    int knapSacks[] = {3, 5, 12};
    
    int values[] = {7, 3, 5, 5, 7};
    
    int weights[] = {2, 3, 3, 5, 7};
    
    multipleKnapSackProblem(3, 5, knapSacks, values, weights);
    
	return 0;
}