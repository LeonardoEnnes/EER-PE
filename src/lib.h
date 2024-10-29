#ifndef lib_h
#define lib_h

#define MAX_ELETRODOMESTICOS 10 

// valores definidos a partir da fonte: https://istoe.com.br/istoegeral/2024/09/03/contas-de-luz-em-alta-bandeira-tarifaria-vermelha-pesa-no-bolso-dos-brasileiros/
#define ACRESCIMO_VERDE 0.0          // sem acréscimo
#define ACRESCIMO_AMARELA 1.50       // R$ 1,50 a cada 100 kWh
#define ACRESCIMO_VERMELHA_1 4.44    // R$ 4,44 a cada 100 kWh
#define ACRESCIMO_VERMELHA_2 7.87    // R$ 7,87 a cada 100 kWh

// funções existentes
float calcularConsumo(float potencia, float horas);
float calcularConsumoMensal(float consumoDiario);
float calcularCustoMensal(float consumoMensal, float custoKwh, int bandeiraTarifaria);
void calcularConsumoTotal(float* potencias, float* horas, float* consumos, int numEletrodomesticos);
void calcularCustoTotal(float* consumos, float custoKwh, float* custoTotais, int numEletrodomesticos, int bandeiraTarifaria);
void exibirResultados(float* consumos, float* custoTotais, int numEletrodomesticos);

#endif 
