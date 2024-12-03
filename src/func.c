#include <stdio.h>
#include "lib.h"
#include <math.h>

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
    printf("| Eletrodomestico | Consumo Diario | Custo Mensal (R$) |\n");
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
    printf("\nO eletrodomestico com maior consumo e o %d com %.2f kWh por dia.\n", maior + 1, consumos[maior]);
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

void calcularViabilidadeSolar(float consumoTotalMensal, float custoKwh) {
    float economiaAnual, custoManutencaoAnual, economiaAnualTotal, payback;
    
    printf("\nAnalise de Viabilidade Solar no Rio Grande do Sul:\n");
    printf("---------------------------------------------------\n");
    
    // Cálculo da economia mensal
    float economiaMensal = consumoTotalMensal * custoKwh;
    printf("Economia Mensal: R$ %.2f\n", economiaMensal);
    
    // Cálculo da economia anual
    economiaAnual = economiaMensal * 12;
    printf("Economia Anual: R$ %.2f\n", economiaAnual);
    
    // Cálculo do custo de manutenção anual
    custoManutencaoAnual = CUSTO_INSTALACAO_SOLAR * TAXA_MANUTENCAO_ANUAL;
    printf("Custo de Manutencao Anual: R$ %.2f\n", custoManutencaoAnual);
    
    // Cálculo da economia anual total
    economiaAnualTotal = economiaAnual - custoManutencaoAnual;
    printf("Economia Anual Total: R$ %.2f\n", economiaAnualTotal);
    
    // Cálculo do payback
    payback = CUSTO_INSTALACAO_SOLAR / economiaAnualTotal;
    printf("Tempo de Retorno do Investimento (Payback): %.2f anos\n", payback);
    
    printf("\nEficiencia media dos paineis solares no RS: %.1f%%\n", EFICIENCIA_PAINEL_SOLAR * 100);
    
    printf("\nConclusao:\n");
    if (payback < 10) {
        printf("O investimento em energia solar e altamente recomendado.\n");
        printf("Voce tera um retorno do investimento em menos de 10 anos,\n");
        printf("com mais de 15 anos de economia significativa apos esse periodo.\n");
    } else if (payback < 15) {
        printf("O investimento em energia solar e recomendado.\n");
        printf("Embora o retorno do investimento seja um pouco mais longo,\n");
        printf("ainda havera uma economia significativa a longo prazo.\n");
    } else {
        printf("O investimento em energia solar pode ser considerado,\n");
        printf("mas o retorno sera mais longo. Reavalie em alguns anos,\n");
        printf("pois os custos de instalacao tendem a diminuir com o tempo.\n");
    }
}