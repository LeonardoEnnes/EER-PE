#include <stdio.h>
#include "lib.h"
#include <math.h>
#include <string.h>

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

void calcularCustoTotal(float* consumos, float custoKwh, float* custoTotais, int numEletrodomesticos, int bandeiraTarifaria, int mes) {
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i], mes);
        custoTotais[i] = calcularCustoMensal(consumoMensal, custoKwh, bandeiraTarifaria);
    }
}

void exibirResultados(float* consumos, float* custoTotais, int numEletrodomesticos, int mes) {
    printf("\nResultados para o mes %d:\n", mes);
    printf("-------------------------------------------------------------------------\n");
    printf("| Eletrodomestico | Consumo Diario | Consumo Mensal | Custo Mensal (R$) |\n");
    printf("-------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i], mes);
        printf("|       %d         |    %.2f kWh   |   %.2f kWh    |       %.2f       |\n",
               i + 1, consumos[i], consumoMensal, custoTotais[i]);
    }
    printf("-------------------------------------------------------------------------\n");
}

void exibirResultadosComNomes(float* consumos, float* custoTotais, int numEletrodomesticos, char nomes[][20], int mes) {
    printf("\nResultados detalhados para o mes %d:\n", mes);
    printf("-------------------------------------------------------------------------\n");
    printf("| Eletrodomestico | Consumo Diario | Consumo Mensal | Custo Mensal (R$) |\n");
    printf("-------------------------------------------------------------------------\n");
    float consumoTotalMensal = 0.0;
    float custoTotalMensal = 0.0;
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i], mes);
        consumoTotalMensal += consumoMensal;
        custoTotalMensal += custoTotais[i];
        printf("| %-15s |    %.2f kWh   |   %.2f kWh    |       %.2f       |\n",
               nomes[i], consumos[i], consumoMensal, custoTotais[i]);
    }
    printf("-------------------------------------------------------------------------\n");
    printf("| Total           |               |   %.2f kWh    |       %.2f       |\n",
           consumoTotalMensal, custoTotalMensal);
    printf("-------------------------------------------------------------------------\n");
}

int identificarMaiorConsumoRecursivo(float* consumos, int numEletrodomesticos, int indiceAtual) {
    if (numEletrodomesticos == 1) {
        return 0;
    }
    
    int indiceMaior = identificarMaiorConsumoRecursivo(consumos, numEletrodomesticos - 1, indiceAtual + 1);
    
    if (consumos[indiceAtual] > consumos[indiceMaior]) {
        return indiceAtual;
    } else {
        return indiceMaior;
    }
}

void identificarMaiorConsumo(float* consumos, int numEletrodomesticos, char nomes[][20]) {
    int maior = identificarMaiorConsumoRecursivo(consumos, numEletrodomesticos, 0);
    printf("\nO eletrodomestico com maior consumo e %s com %.2f kWh por dia.\n", nomes[maior], consumos[maior]);
}

// se baseia em um mes especifico informado
void calcularEconomiaSolar(float* consumos, float custoKwh, int numEletrodomesticos, int mes, int bandeiraTarifaria) {
    float totalConsumoMensal = 0.0, totalCustoAtual = 0.0;
    int i;
    
    // Calcula o consumo e custo total mensal
    for (i = 0; i < numEletrodomesticos; i++) {
        float consumoMensal = calcularConsumoMensal(consumos[i], mes);
        totalConsumoMensal += consumoMensal;
        totalCustoAtual += calcularCustoMensal(consumoMensal, custoKwh, bandeiraTarifaria);
    }

    float economia = totalCustoAtual * 0.8;
    float novoCustoReduzido = totalCustoAtual * 0.2;

    printf("\nEstudo de Viabilidade Solar para o mes %d:\n", mes);
    printf("-------------------------------------------------------\n");
    printf("Consumo Total Mensal: %.2f kWh\n", totalConsumoMensal);
    printf("Custo Total Atual: R$ %.2f\n", totalCustoAtual);
    printf("Com energia solar (reducao de 80%%):\n");
    printf("Economia Mensal: R$ %.2f\n", economia);
    printf("Valor Reduzido da Conta: R$ %.2f\n", novoCustoReduzido);
}

float calcularCustoInstalacaoSolar(char tipoCasa) {
    switch (tipoCasa) {
        case 'P': 
            return 14000.0; 
        case 'M': 
            return 15800.0; 
        case 'G': 
        default:
            return 25000.0;
    }
}

// faz a previsão durante o ano todo
void calcularViabilidadeSolar(float consumoTotalAnual, float custoKwh, char tipoCasa) {
    float custoInstalacao = calcularCustoInstalacaoSolar(tipoCasa);
    float economiaAnualBruta, custoManutencaoAnual, economiaAnualLiquida, payback;
    
    printf("\nAnalise de Viabilidade Solar Anual:\n");
    printf("-------------------------------------------------------\n");
    
    // Mostrar o consumo total anual
    printf("Consumo Total Anual: %.2f kWh\n", consumoTotalAnual);
    
    // Cálculo da economia anual
    float economiaAnual = consumoTotalAnual * custoKwh * 0.8;
    printf("Economia Anual: R$ %.2f\n", economiaAnual);
    
    // Cálculo da economia anual bruta (não considerando os custos de manutenção)
    economiaAnualBruta = economiaAnual;
    printf("Economia Anual Bruta: R$ %.2f\n", economiaAnualBruta);
    
    // Cálculo do custo de manutenção anual
    custoManutencaoAnual = custoInstalacao * TAXA_MANUTENCAO_ANUAL;
    printf("Custo de Manutencao Anual: R$ %.2f\n", custoManutencaoAnual);
    
    // Cálculo da economia anual líquida (considerando os custos de manutenção)
    economiaAnualLiquida = economiaAnualBruta - custoManutencaoAnual;
    printf("Economia Anual Liquida: R$ %.2f\n", economiaAnualLiquida);
    
    // Cálculo do payback
    payback = custoInstalacao / economiaAnualLiquida;
    printf("Tempo de Retorno do Investimento (Payback): %.2f anos\n", payback);
    
    printf("\nConclusao:\n");
    printf("-------------------------------------------------------\n");
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
    printf("-------------------------------------------------------\n");
}

// funçao que salva o relatorio completo em um arquivo .txt na pasta do projeto 
void salvarRelatorio(float* consumos, float* custoTotais, int numEletrodomesticos, char nomes[][20], int mes, float consumoTotalAnual, float custoKwh, char tipoCasa) {
    FILE *arquivo;
    arquivo = fopen("relatorio_geral.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Redirecionar a saída padrão para o arquivo
    FILE *stdout_original = freopen("relatorio_geral.txt", "w", stdout);

    // Chamar as funções existentes para escrever no arquivo
    exibirResultadosComNomes(consumos, custoTotais, numEletrodomesticos, nomes, mes);
    identificarMaiorConsumo(consumos, numEletrodomesticos, nomes);
    calcularEconomiaSolar(consumos, custoKwh, numEletrodomesticos, mes, 3); // Assumindo bandeira vermelha 2
    
	// Adicionar o cálculo da média de consumo diario
    float mediaDeConsumoDiario = calcularMediaConsumo(consumos, numEletrodomesticos);
    printf("\nMedia de consumo diario: %.2f kWh\n", mediaDeConsumoDiario);
    
    // calculo de viabilidade solar
    calcularViabilidadeSolar(consumoTotalAnual, custoKwh, tipoCasa);

    // Restaurar a saída padrão
    freopen("CON", "w", stdout);

    fclose(arquivo);
    printf("Relatorio salvo com sucesso em 'relatorio_geral.txt'.\n");
}

// alocação dinamica para consumo diario
float calcularMediaConsumo(float* consumos, int numEletrodomesticos) {
    float* consumosCopia = (float*) malloc(numEletrodomesticos * sizeof(float));
    if (consumosCopia == NULL) {
        printf("Erro na alocacao de memoria\n");
        return 0;
    }

    float soma = 0;
    int i;
    for (i = 0; i < numEletrodomesticos; i++) {
        consumosCopia[i] = consumos[i];
        soma += consumosCopia[i];
    }

    float media = soma / numEletrodomesticos;

    free(consumosCopia);

    return media;
}