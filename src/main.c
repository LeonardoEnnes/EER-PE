#include <stdio.h>
#include "lib.h"

#define NUM_ELETRODOMESTICOS 3 

int main() {
    float potencias[NUM_ELETRODOMESTICOS];
    float horas[NUM_ELETRODOMESTICOS];
    float consumos[NUM_ELETRODOMESTICOS];
    float custoTotais[NUM_ELETRODOMESTICOS];
    float custoKwh;
    int bandeiraTarifaria;
    int i;

    printf("Digite o custo por kWh: ");
    scanf("%f", &custoKwh);
    
    printf("Digite a bandeira tarifária (0: Verde, 1: Amarela, 2: Vermelha Patamar 1, 3: Vermelha Patamar 2): ");
    scanf("%d", &bandeiraTarifaria);

    for (i = 0; i < NUM_ELETRODOMESTICOS; i++) {
        printf("Digite a potencia do eletrodomestico %d (em W): ", i + 1);
        scanf("%f", &potencias[i]);
        printf("Digite as horas de uso diario do eletrodomestico %d: ", i + 1);
        scanf("%f", &horas[i]);
    }

    // Cálculo do consumo diário para todos os eletrodomésticos
    calcularConsumoTotal(potencias, horas, consumos, NUM_ELETRODOMESTICOS);
    
    // Cálculo do custo mensal para todos os eletrodomésticos
    calcularCustoTotal(consumos, custoKwh, custoTotais, NUM_ELETRODOMESTICOS, bandeiraTarifaria);
    
    // Exibição dos resultados
    exibirResultados(consumos, custoTotais, NUM_ELETRODOMESTICOS);

    return 0;
}
