#include <stdio.h>
#include "lib.h"

float calcularConsumo(float potencia, float horas) {
    return (potencia / 1000) * horas; // Converte W para kW
}

float calcularConsumoMensal(float consumoDiario) {
    return consumoDiario * 30; // 30 dias no mês
}

float calcularCustoMensal(float consumoMensal, float custoKwh, int bandeiraTarifaria) {
    float bandeiraCusto;

    // Determina o acréscimo com base na bandeira tarifária
    switch (bandeiraTarifaria) {
        case 0: // Verde
            bandeiraCusto = ACRESCIMO_VERDE;
            break;
        case 1: // Amarela
            bandeiraCusto = ACRESCIMO_AMARELA / 100.0; // Divide por 100 para aplicar corretamente
            break;
        case 2: // Vermelha Patamar 1
            bandeiraCusto = ACRESCIMO_VERMELHA_1 / 100.0; // Divide por 100 para aplicar corretamente
            break;
        case 3: // Vermelha Patamar 2
            bandeiraCusto = ACRESCIMO_VERMELHA_2 / 100.0; // Divide por 100 para aplicar corretamente
            break;
        default:
            bandeiraCusto = 0.0; // Caso inválido, sem acréscimo
            break;
    }

    return consumoMensal * (custoKwh + bandeiraCusto);
}

void calcularConsumoTotal(float* potencias, float* horas, float* consumos, int numEletrodomesticos) {
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        consumos[i] = calcularConsumo(potencias[i], horas[i]);
    }
}

void calcularCustoTotal(float* consumos, float custoKwh, float* custoTotais, int numEletrodomesticos, int bandeiraTarifaria) {
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i]);
        custoTotais[i] = calcularCustoMensal(consumoMensal, custoKwh, bandeiraTarifaria);
    }
}

void exibirResultados(float* consumos, float* custoTotais, int numEletrodomesticos) {
    printf("\nResultados:\n");
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i]);
        printf("Eletrodoméstico %d: Consumo Mensal = %.2f kWh, Custo Total = R$ %.2f\n", 
               i + 1, consumoMensal, custoTotais[i]);
    }
}
