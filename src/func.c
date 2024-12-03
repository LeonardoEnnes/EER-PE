#include <stdio.h>
#include "lib.h"

float calcularConsumo(float potencia, float horas) {
    return (potencia / 1000) * horas; // Converte W para kW
}

float calcularConsumoMensal(float consumoDiario, int mes) {
	// Vetor de dias em cada mês 
	int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
    if (mes < 1 || mes > 12) {
        printf("Mês inválido! Usando 30 dias como padrão.\n");
        return consumoDiario * 30; // padrão: 30 dias
    }
    return consumoDiario * diasPorMes[mes - 1];
}

float calcularCustoMensal(float consumoMensal, float custoKwh, int bandeiraTarifaria) {
    float bandeiraCusto = 0.0;

    // Determina o acréscimo com base na bandeira tarifária
    switch (bandeiraTarifaria) {
        case 0: bandeiraCusto = 0.0; break;
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
        float consumoMensal = calcularConsumoMensal(consumos[i], 1); // Considera Janeiro (31 dias) como exemplo
        custoTotais[i] = calcularCustoMensal(consumoMensal, custoKwh, bandeiraTarifaria);
    }
}

void exibirResultados(float* consumos, float* custoTotais, int numEletrodomesticos) {
    printf("\nResultados:\n");
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i], 1); // Exemplo com Janeiro
        printf("Eletrodoméstico %d: Consumo Diário = %.2f kWh, Consumo Mensal = %.2f kWh, Custo Total = R$ %.2f\n", 
               i + 1, consumos[i], consumoMensal, custoTotais[i]);
    }
}
#include <stdio.h>
#include "lib.h"

float calcularConsumo(float potencia, float horas) {
    return (potencia / 1000) * horas; // Converte W para kW
}

float calcularConsumoMensal(float consumoDiario, int mes) {
	// Vetor de dias em cada mês 
	int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
    if (mes < 1 || mes > 12) {
        printf("Mês inválido! Usando 30 dias como padrão.\n");
        return consumoDiario * 30; // padrão: 30 dias
    }
    return consumoDiario * diasPorMes[mes - 1];
}

float calcularCustoMensal(float consumoMensal, float custoKwh, int bandeiraTarifaria) {
    float bandeiraCusto = 0.0;

    // Determina o acréscimo com base na bandeira tarifária
    switch (bandeiraTarifaria) {
        case 0: bandeiraCusto = 0.0; break;
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
        float consumoMensal = calcularConsumoMensal(consumos[i], 1); // Considera Janeiro (31 dias) como exemplo
        custoTotais[i] = calcularCustoMensal(consumoMensal, custoKwh, bandeiraTarifaria);
    }
}

void exibirResultados(float* consumos, float* custoTotais, int numEletrodomesticos) {
    printf("\nResultados:\n");
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i], 1); // Exemplo com Janeiro
        printf("Eletrodoméstico %d: Consumo Diário = %.2f kWh, Consumo Mensal = %.2f kWh, Custo Total = R$ %.2f\n", 
               i + 1, consumos[i], consumoMensal, custoTotais[i]);
    }
}
