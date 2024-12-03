#include <stdio.h>
#include "lib.h"

#define NUM_ELETRODOMESTICOS 3

int main() {
    float potencias[NUM_ELETRODOMESTICOS] = {1000, 2000, 1500}; // Potências em W
    float horas[NUM_ELETRODOMESTICOS] = {4, 3, 2};  // Horas de uso diário
    float consumos[NUM_ELETRODOMESTICOS];
    float custoTotais[NUM_ELETRODOMESTICOS];
    float custoKwh = 0.85; // Custo fixo por kWh para exemplo
    int bandeiraTarifaria = 1;  // Bandeira tarifária fixa (amarela) para exemplo

    calcularConsumoTotal(potencias, horas, consumos, NUM_ELETRODOMESTICOS);
    calcularCustoTotal(consumos, custoKwh, custoTotais, NUM_ELETRODOMESTICOS, bandeiraTarifaria);

    exibirResultados(consumos, custoTotais, NUM_ELETRODOMESTICOS);
    identificarMaiorConsumo(consumos, NUM_ELETRODOMESTICOS);
    calcularEconomiaSolar(consumos, custoKwh, NUM_ELETRODOMESTICOS);

    // Cálculo do consumo total mensal para análise de viabilidade solar
    float consumoTotalMensal = 0;
    int i;
    for (i = 0; i < NUM_ELETRODOMESTICOS; i++) {
        consumoTotalMensal += calcularConsumoMensal(consumos[i], 1);
    }

    // Nova chamada para análise de viabilidade solar no RS
    calcularViabilidadeSolar(consumoTotalMensal, custoKwh);

    return 0;
}