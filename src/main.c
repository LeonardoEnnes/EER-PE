#include <stdio.h>
#include "lib.h"

#define NUM_ELETRODOMESTICOS 3

int main() {
    float potencias[NUM_ELETRODOMESTICOS] = {1000, 2000, 1500}; // Potências em W
    float horas[NUM_ELETRODOMESTICOS] = {4, 3, 2};              // Horas de uso diário
    float consumos[NUM_ELETRODOMESTICOS];
    float custoTotais[NUM_ELETRODOMESTICOS];
    float custoKwh = 0.85; // Custo fixo por kWh para exemplo
    int bandeiraTarifaria = 1; // Bandeira tarifária fixa (amarela) para exemplo

    // Cálculo do consumo diário e custo mensal
    calcularConsumoTotal(potencias, horas, consumos, NUM_ELETRODOMESTICOS);
    calcularCustoTotal(consumos, custoKwh, custoTotais, NUM_ELETRODOMESTICOS, bandeiraTarifaria);

    // Relatórios
    exibirResultados(consumos, custoTotais, NUM_ELETRODOMESTICOS);
    identificarMaiorConsumo(consumos, NUM_ELETRODOMESTICOS);
    simularMudancas(consumos, NUM_ELETRODOMESTICOS, custoKwh, bandeiraTarifaria);
    calcularEconomiaSolar(consumos, custoKwh, NUM_ELETRODOMESTICOS);

    return 0;
}
