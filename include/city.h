#ifndef CITY_H // Include Guards
#define CITY_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct City
 * @brief Representa os dados de uma cidade.
 *
 * Esta estrutura armazena informações detalhadas sobre uma cidade, 
 * incluindo estado, nome, população, área e outras estatísticas relevantes.
 */
typedef struct _city
{
    char state; /**< O estado associado à cidade. Possíveis valores: A, B, C, D, E, F, G, H. */
    char* card_code; /**< O código da carta associado à cidade. Possíveis valores: a combinação de valor de `state` e um número entre 01, 02, 03 e 04.*/
    char* city_name; /**< O nome da cidade. */
    unsigned long int population_size; /**< Tamanho da população da cidade. */
    float area; /**< Área da cidade (km²). */
    float population_density; /**< Densidade populacional (pessoas por km²). */
    float gpd; /**< Produto Interno Bruto (PIB) da cidade. */
    float gpd_pc; /**< PIB per capita da cidade. */
    int tourist_sites_count; /**< Número de pontos turísticos na cidade. */
    float super_power; /**< A soma de todos os valores numéricos da cidade. */
} City;

/**
 * @enum Property
 * @brief Representa as propriedades que podem ser comparadas.
 */
enum Property
{
    PopulationSize = 1, /**< Tamanho da população. */
    Area, /**< Área em km². */
    PopulationDensity, /**< Densidade populacional em pessoa/km². */
    GPD, /**< PIB. */
    GPD_PC, /**< PIB per Cap. */
    TouristSitesCount /**< Número de pontos turísticos. */
};

/**
 * @brief Aloca memória para uma nova cidade.
 *
 * Esta função aloca dinamicamente memória para uma estrutura do tipo `City`
 * usando a função `calloc`. Se a alocação falhar, a função imprime uma
 * mensagem de erro e termina o programa com `exit(EXIT_FAILURE)`.
 *
 * @return Um ponteiro para a estrutura `City` alocada na memória.
 *
 * @note A memória alocada para a cidade deve ser liberada com a função
 *       `free_city` quando não for mais necessária.
 */
City* alocate_city();

/**
 * @brief Registra os dados de uma cidade em um item de lista.
 *
 * Esta função copia os dados de uma cidade (`city`) para um item de uma lista
 * de cidades (`city_in_list`). Ela realiza a alocação dinâmica de memória para
 * os campos da cidade na lista, como o nome da cidade e o código da carta.
 * Além disso, calcula a densidade populacional, o PIB per capita e o superpoder
 * da cidade com base nos dados fornecidos.
 *
 * @param city Ponteiro para a cidade de origem cujos dados serão copiados.
 * @param city_in_list Ponteiro para a cidade na lista onde os dados serão
 *                     registrados.
 *
 * @note Se algum dos ponteiros fornecidos for `NULL`, a função imprimirá uma
 *       mensagem de erro e finalizará o programa com `exit(EXIT_FAILURE)`.
 *       Além disso, a função realiza alocação dinâmica de memória, e o espaço
 *       alocado deve ser liberado quando não for mais necessário.
 *
 * @see alocate_city()
 */
void register_city(City* city, City* city_in_list);

/**
 * @brief Libera a memória alocada para uma cidade.
 *
 * Esta função libera a memória associada a uma cidade, incluindo o código da
 * carta, o nome da cidade e a estrutura da cidade em si. Ela verifica se o
 * ponteiro fornecido não é `NULL` antes de tentar liberar a memória, garantindo
 * que a operação seja segura.
 * Após liberar a memória, o ponteiro da cidade é setado para `NULL` para evitar
 * o uso de ponteiros pendentes.
 *
 * @param city_ref Ponteiro duplo para a cidade que será liberada.
 *
 * @note Se o ponteiro `city_ref` ou o ponteiro para a cidade (referenciado por
 *       `city_ref`) forem `NULL`, a função não realizará nenhuma operação.
 *
 * @see alocate_city()
 */
void free_city(City** city_ref);

/**
 * @brief Libera a memória de uma lista de cidades.
 *
 * Esta função itera sobre uma lista de cidades e, para cada cidade registrada
 * (não `NULL`), chama a função `free_city()` para liberar a memória alocada
 * para essa cidade. A função garante que a memória alocada para cada cidade da
 * lista seja liberada de forma segura.
 *
 * @param city_list Ponteiro para a lista de cidades a serem liberadas.
 * @param registered_cities_count Número de cidades registradas na lista.
 *
 * @note A função não verifica se `city_list` é `NULL`. A verificação é feita na
 *       função `free_city()`.
 *       A função `free_city()` é chamada para cada cidade na lista, garantindo
 *       que todos os elementos sejam liberados corretamente.
 *
 * @see free_city()
 */
void free_city_list(City** city_list, int registered_cities_count);

/**
 * @brief Aloca e inicializa duas estruturas `City` para comparação.
 * 
 * @details Esta função aloca memória para duas estruturas `City`, coleta os
 * dados de cada cidade, registra as informações e exibe os dados coletados no
 * terminal. A função recebe um array de dois ponteiros para `City` e os
 * inicializa com valores nulos antes de alocar as estruturas.
 * 
 * @param city_list Um array de dois ponteiros para `City`, onde as cidades
 *                  registradas serão armazenadas.
 */
void alocate_cities_to_compare(City* city_list[2]);

/**
 * @brief Compara a população de duas cartas e exibe a vencedora.
 * 
 * @details Esta função recebe uma lista de duas cidades, exibe os dados de cada
 * uma(estado, código da carta e população) e compara os valores de população. A
 * carta com a maior população é declarada vencedora e exibida no resultado.
 * 
 * @param city_list Um array de ponteiros para duas estruturas `City`, contendo
 *                  os dados das cartas a serem comparadas.
 */
void compare_population_size(City** city_list);

/**
 * @brief Compara duas propriedades do tipo `long int` de duas cidades e
 * determina a vencedora.
 * 
 * @details Esta função recebe dois valores do tipo `long int`, representando a
 * propriedade de duas cidades. Ela compara esses valores e define a cidade
 * vencedora. Se os valores forem iguais, um empate é indicado. O resultado da
 * comparação é exibido no terminal.
 * 
 * @param first_city_value O valor da propriedade da primeira cidade.
 * @param second_city_value O valor da propriedade da segunda cidade.
 */
void compare_one_long_int_property(
    long int first_city_value, long int second_city_value
);

/**
 * @brief Compara duas propriedades do tipo `float` de duas cidades e determina
 * a vencedora.
 * 
 * @details Esta função recebe dois valores do tipo `long int`, representando a
 * propriedade de duas cidades. Ela compara esses valores e define a cidade
 * vencedora. Se os valores forem iguais, um empate é indicado. O resultado da
 * comparação é exibido no terminal.
 * 
 * @param first_city_value O valor da propriedade da primeira cidade.
 * @param second_city_value O valor da propriedade da segunda cidade.
 */
void compare_one_float_property(
    float first_city_value, float second_city_value
);

/**
 * @brief Compara a densidade populacional entre duas cidades.
 * 
 * Esta função compara o valor da densidade populacional de duas cidades e exibe
 * qual cidade possui a menor densidade populacional. Caso ambos os valores
 * sejam iguais, a função exibirá uma mensagem de empate.
 * 
 * @param first_city_value Valor da densidade populacional da primeira cidade.
 * @param second_city_value Valor da densidade populacional da segunda cidade.
 * 
 * @note A função exibe o resultado diretamente na tela. Não retorna valores.
 */
void compare_population_density(
    float first_city_value, float second_city_value
);

/**
 * @brief Compara duas propriedades float de duas cidades e determina a
 * vencedora.
 * 
 * @details A função recebe dois valores float para cada cidade, soma os valores
 * de cada cidade e compara os resultados. A cidade com a maior soma vence. Se
 * os valores forem iguais, um empate é indicado. O resultado da comparação é
 * exibido no terminal.
 * 
 * @param first_value_first_city Primeiro valor da primeira cidade.
 * @param second_value_first_city Segundo valor da primeira cidade.
 * @param first_value_second_city Primeiro valor da segunda cidade.
 * @param second_value_second_city Segundo valor da segunda cidade.
 */
void compare_two_float_properties(
    float first_value_first_city, float second_value_first_city,
    float first_value_second_city, float second_value_second_city
);

/**
 * @brief Compara duas propriedades float de duas cidades e determina a
 * vencedora.
 * 
 * @details A função recebe dois valores long int para cada cidade, soma os
 * valores de cada cidade e compara os resultados. A cidade com a maior soma
 * vence. Se os valores forem iguais, um empate é indicado. O resultado da
 * comparação é exibido no terminal.
 * 
 * @param first_value_first_city Primeiro valor da primeira cidade.
 * @param second_value_first_city Segundo valor da primeira cidade.
 * @param first_value_second_city Primeiro valor da segunda cidade.
 * @param second_value_second_city Segundo valor da segunda cidade.
 */
void compare_two_long_int_properties(
    long int first_value_first_city, long int second_value_first_city,
    long int first_value_second_city, long int second_value_second_city
);

#endif
