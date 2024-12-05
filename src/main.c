#include <stdio.h>
#include "lib.h"

#define NUM_ELETRODOMESTICOS 3

int main() {
    float potencias[NUM_ELETRODOMESTICOS] = {220, 220, 220}; // Potências em W
    float horas[NUM_ELETRODOMESTICOS] = {24, 8, 4};  // Horas de uso diário
    float consumos[NUM_ELETRODOMESTICOS];
    float custoTotais[NUM_ELETRODOMESTICOS];
    float custoKwh = 0.85; // Custo fixo por kWh para exemplo
    int bandeiraTarifaria = 3;  // Bandeira tarifária fixa (VERMELHA_2) para exemplo
    char nomes[NUM_ELETRODOMESTICOS][20] = {"Geladeira", "Ar Condicionado", "Chuveiro"};
    char tipoCasa = 'P'; // 'P' para pequena, 'M' para média, 'G' para grande 
    int mes = 5; // Defina o mês desejado (1-12), por exemplo, maio (5)

    calcularConsumoTotal(potencias, horas, consumos, NUM_ELETRODOMESTICOS);
    calcularCustoTotal(consumos, custoKwh, custoTotais, NUM_ELETRODOMESTICOS, bandeiraTarifaria);

    exibirResultados(consumos, custoTotais, NUM_ELETRODOMESTICOS, mes);
    exibirResultadosComNomes(consumos, custoTotais, NUM_ELETRODOMESTICOS, nomes, mes);
    identificarMaiorConsumo(consumos, NUM_ELETRODOMESTICOS, nomes);
    calcularEconomiaSolar(consumos, custoKwh, NUM_ELETRODOMESTICOS);

    // Cálculo do consumo total mensal para análise de viabilidade solar
    float consumoTotalMensal = 0;
    int i;
    for (i = 0; i < NUM_ELETRODOMESTICOS; i++) {
        consumoTotalMensal += calcularConsumoMensal(consumos[i], 1);
    }

    calcularViabilidadeSolar(consumoTotalMensal, custoKwh, tipoCasa);

    return 0;
}