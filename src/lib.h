#ifndef lib_h
#define lib_h

#define MAX_ELETRODOMESTICOS 10 

// valores definidos a partir da fonte: https://www.solsticioenergia.com/bandeiras-tarifarias#:~:text=Reajuste%20das%20bandeiras%20tarif%C3%A1rias%202024&text=Os%20novos%20valores%20s%C3%A3o%20os,consumidos%20(%2D%2031%2C3%25)%3B
#define ACRESCIMO_VERDE 0.0          // sem acréscimo
#define ACRESCIMO_AMARELA 1.885      // R$ 1,885 a cada 100 kWh
#define ACRESCIMO_VERMELHA_1 4.463   // R$ 4,463 a cada 100 kWh
#define ACRESCIMO_VERMELHA_2 7.877   // R$ 7,877 a cada 100 kWh

// valores dos custos de instalações solares => https://www.energiatotal.com.br/saiba-qual-e-o-preco-medio-para-ter-um-sistema-fotovoltaico
#define EFICIENCIA_PAINEL_SOLAR 0.165 // https://solarisenergia.eco.br/eficiencia-do-painel-solar-fotovoltaico/
#define TAXA_MANUTENCAO_ANUAL 0.005 // https://elysia.com.br/manutencao-de-painel-fotovoltaico/

// funções existentes
float calcularConsumo(float potencia, float horas);
float calcularConsumoMensal(float consumoDiario, int mes);
float calcularCustoMensal(float consumoMensal, float custoKwh, int bandeiraTarifaria);
void calcularConsumoTotal(float* potencias, float* horas, float* consumos, int numEletrodomesticos);
void calcularCustoTotal(float* consumos, float custoKwh, float* custoTotais, int numEletrodomesticos, int bandeiraTarifaria, int mes);
void exibirResultados(float* consumos, float* custoTotais, int numEletrodomesticos, int mes);

void identificarMaiorConsumo(float* consumos, int numEletrodomesticos, char nomes[][20]);
void calcularEconomiaSolar(float* consumos, float custoKwh, int numEletrodomesticos, int mes, int bandeiraTarifaria);
float calcularCustoInstalacaoSolar(char tipoCasa);
void calcularViabilidadeSolar(float consumoTotalAnual, float custoKwh, char tipoCasa);

// função que lida com recursão
int identificarMaiorConsumoRecursivo(float* consumos, int numEletrodomesticos, int indiceAtual);

// função que lida com strings
void exibirResultadosComNomes(float* consumos, float* custoTotais, int numEletrodomesticos, char nomes[][20], int mes);

#endif 