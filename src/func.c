#include <stdio.h>
#include "lib.h"

float calcularConsumo(float potencia, float horas) {
    return (potencia / 1000) * horas; // Converte W para kW
}

float calcularConsumoMensal(float consumoDiario, int mes) {
    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return consumoDiario * diasPorMes[mes - 1];
}

float calcularCustoMensal(float consumoMensal, float custoKwh, int bandeiraTarifaria) {
    float bandeiraCusto = 0.0;

    switch (bandeiraTarifaria) {
        case 1: bandeiraCusto = ACRESCIMO_AMARELA * (consumoMensal / 100.0); break;
        case 2: bandeiraCusto = ACRESCIMO_VERMELHA_1 * (consumoMensal / 100.0); break;
        case 3: bandeiraCusto = ACRESCIMO_VERMELHA_2 * (consumoMensal / 100.0); break;
        default: bandeiraCusto = 0.0; break;
    }

    return (consumoMensal * custoKwh) + bandeiraCusto;
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
        float consumoMensal = calcularConsumoMensal(consumos[i], 1);
        custoTotais[i] = calcularCustoMensal(consumoMensal, custoKwh, bandeiraTarifaria);
    }
}

void exibirResultados(float* consumos, float* custoTotais, int numEletrodomesticos) {
    printf("\nResultados:\n");
    printf("-------------------------------------------------------\n");
    printf("| Eletrodoméstico | Consumo Diário | Custo Mensal (R$) |\n");
    printf("-------------------------------------------------------\n");
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        printf("|       %d         |     %.2f kWh   |       %.2f       |\n",
               i + 1, consumos[i], custoTotais[i]);
    }
    printf("-------------------------------------------------------\n");
}

void identificarMaiorConsumo(float* consumos, int numEletrodomesticos) {
    int maior = 0;
    int i;
    for (i = 1; i < numEletrodomesticos; i++) {
        if (consumos[i] > consumos[maior]) maior = i;
    }
    printf("\nO eletrodoméstico com maior consumo é o %d com %.2f kWh por dia.\n", maior + 1, consumos[maior]);
}

void simularMudancas(float* consumos, int numEletrodomesticos, float custoKwh, int bandeiraTarifaria) {
    printf("\nSimulação de Redução de Consumo (50%%):\n");
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float novoConsumo = consumos[i] * 0.5;
        float consumoMensal = calcularConsumoMensal(novoConsumo, 1);
        float novoCusto = calcularCustoMensal(consumoMensal, custoKwh, bandeiraTarifaria);
        printf("Eletrodoméstico %d: Consumo Reduzido = %.2f kWh, Novo Custo = R$ %.2f\n", i + 1, consumoMensal, novoCusto);
    }
}

void calcularEconomiaSolar(float* consumos, float custoKwh, int numEletrodomesticos) {
    float totalConsumoMensal = 0.0, totalCustoAtual = 0.0;
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        totalConsumoMensal += calcularConsumoMensal(consumos[i], 1);
        totalCustoAtual += totalConsumoMensal * custoKwh;
    }

    printf("\nEstudo de Viabilidade Solar:\n");
    printf("Consumo Total Mensal: %.2f kWh\n", totalConsumoMensal);
    printf("Custo Total Atual: R$ %.2f\n", totalCustoAtual);
    printf("Com energia solar (redução de 80%%): Custo Reduzido = R$ %.2f\n",
           totalCustoAtual * 0.2);
}
