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
    calcularCustoTotal(consumos, custoKwh, custoTotais, NUM_ELETRODOMESTICOS, bandeiraTarifaria, mes);

    exibirResultados(consumos, custoTotais, NUM_ELETRODOMESTICOS, mes);
    exibirResultadosComNomes(consumos, custoTotais, NUM_ELETRODOMESTICOS, nomes, mes);
    identificarMaiorConsumo(consumos, NUM_ELETRODOMESTICOS, nomes);
    
    // calculo de economia solar baseado no mes especifico
    calcularEconomiaSolar(consumos, custoKwh, NUM_ELETRODOMESTICOS, mes);

    
    // Cálculo anual
    float consumoTotalAnual = 0;
    int mes_calc;
    for (mes_calc = 1; mes_calc <= 12; mes_calc++) {
    	int i;
        for (i = 0; i < NUM_ELETRODOMESTICOS; i++) {
            consumoTotalAnual += calcularConsumoMensal(consumos[i], mes_calc);
        }
    }
    calcularViabilidadeSolar(consumoTotalAnual, custoKwh, tipoCasa);

    return 0;
}