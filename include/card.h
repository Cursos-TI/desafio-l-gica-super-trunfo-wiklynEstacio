#ifndef CARD_H // Include Guards
#define CARD_H

/**
 * @enum Functionality
 * @brief Representa os fluxos de execução do programa.
 */
enum Functionality
{
    RegisterCards = 1, /**< O fluxo associado ao simples registro de cartas. Permite registrar 32 cartas. */
    CompareOnePropertyStatically, /**< O fluxo associado ao registro de duas cartas e à comparação das propriedades "População" de cada carta. Vence a carta que tiver maior população.*/
    CompareOnePropertyDinamically, /**< O fluxo associado ao registro de duas cartas e à comparação de uma propriedade escolhida pelo usuário. Permite fazer a comparação várias vezes, podendo ser executado em todas as propriedades numéricas. Vence a carta que tiver a propriedade de maior valor, com excessão de "Densidade Populacional", que vence a carta que tiver menor valor.*/
    CompareTwoPropertiesDinamically /**< O fluxo associado ao registro de duas cartas e à comparação da soma de duas propriedades escolhidas pelo usuário. Permite fazer a comparação várias vezes, podendo ser executado em todas as propriedades numéricas. Vence a carta que tiver maior valor da soma.*/
};

/**
 * @brief Exibe o menu de funcionalidades do programa.
 * 
 * Esta função imprime na tela as funcionalidades disponíveis no programa,
 * utilizando formatação ANSI para destacar os títulos das opções.
 * 
 * @details As funcionalidades apresentadas no menu são:
 * - Registro de cartas
 * - Comparação de cartas pela propriedade "População"
 * - Comparação de cartas por uma propriedade escolhida pelo usuário
 * - Comparação de cartas por duas propriedades escolhidas pelo usuário
 */
void show_functionalities_menu();

/**
 * @brief Exibe as funcionalidades disponíveis para o usuário e solicita uma
 *        escolha válida.
 * 
 * Esta função apresenta ao usuário duas opções de funcionalidades e solicita
 * que ele escolha uma delas.
 * Caso o valor inserido seja inválido (não seja 1 ou 2), exibe uma mensagem de
 * erro e solicita novamente.
 * 
 * @details
 * - A função utiliza um loop `do-while` para garantir que o usuário insira um
 *   valor válido.
 * - Caso a entrada fornecida não seja um número, o buffer de entrada é limpo.
 * - Mensagens claras são exibidas para orientar o usuário em caso de erro.
 * 
 * @note Esta função é interativa e requer entrada do usuário pelo teclado.
 * 
 * @return int O número da funcionalidade escolhida pelo usuário:
 * 
 *         - 1: Registro de cartas.
 * 
 *         - 2: Registro e comparação de cartas.
 */
int choose_functionality();

/**
 * @brief Registra múltiplas cartas de cidades, gerenciando entrada de dados e
 *        alocação de memória.
 * 
 * Esta função permite que o usuário registre até um número máximo de cartas
 * (cidades) especificado.
 * Os dados de cada carta são obtidos por meio da função `get_city_data`,
 * armazenados em memória dinâmica
 * e exibidos ao usuário. O processo continua até que o limite seja atingido ou
 * o usuário escolha não registrar mais cartas.
 * 
 * @param max_cities O número máximo de cartas (cidades) que podem ser
 *                   registradas.
 * 
 * @details
 * - A função verifica se o valor de `max_cities` é positivo. Caso contrário, um
 *   erro é exibido e o programa é encerrado.
 * - Cria uma lista de ponteiros para armazenar as cartas registradas.
 * - Para cada cidade, a memória é alocada dinamicamente e os dados são copiados
 *   para a estrutura correspondente.
 * - Após cada registro, os dados são exibidos e o ponteiro usado para entrada
 *   temporária é liberado.
 * - O usuário é perguntado se deseja continuar registrando até atingir o limite
 *   de cartas.
 * - No final, todos os dados alocados são liberados para evitar vazamentos de
 *   memória.
 * 
 * @note A função depende das seguintes funções auxiliares:
 * 
 *   - `get_city_data`: Obtém os dados da cidade do usuário.
 * 
 *   - `register_city`: Copia os dados da cidade para o ponteiro correspondente
 *     e calcula o valor de propriedades extras utilizando os dados fornecidos.
 * 
 *   - `print_city`: Exibe os dados da cidade para o usuário.
 * 
 *   - `ask_to_keep_registering`: Pergunta ao usuário se deseja continuar
 *     registrando.
 * 
 *   - `free_city`: Libera a memória de uma única cidade.
 * 
 *   - `free_city_list`: Libera a memória de todas as cidades registradas.
 * 
 * @pre 
 * - O valor de `max_cities` deve ser maior que 0.
 * 
 * @warning 
 * - Caso `max_cities` seja menor ou igual a 0, a função exibirá um erro e
 *   encerrará a execução do programa.
 * 
 * - A função auxiliar `get_city_data` não realiza validações rigorosas de
 *   entrada, portanto, espera-se que o usuário insira dados válidos para evitar
 *   comportamentos indesejados.
 */
void register_cards(int max_cities);

/**
 * @brief Compara duas cartas de cidades com base em várias propriedades.
 * 
 * A função registra duas cartas de cidades, comparando-as com base em
 * diferentes critérios, como população, área, densidade populacional, PIB, PIB
 * per capita, número de pontos turísticos e um atributo fictício de "super
 * poder".
 * Para cada propriedade, a carta vencedora é determinada e exibida ao usuário.
 * 
 * @details
 * - A função aloca dinamicamente memória para armazenar as cartas das duas
 *   cidades.
 * - As duas cidades são registradas e seus dados são comparados em diversas
 *   propriedades.
 * - Após a comparação, o resultado é impresso, indicando qual cidade venceu em
 *   cada uma das propriedades.
 * 
 * @note
 * - A função depende das seguintes funções auxiliares:
 * 
 *   - `alocate_city`: Aloca e inicializa duas estruturas `City` para comparação.
 * 
 *   - `print_card_to_compare`: Exibe os dados de uma cidade para comparação.
 * 
 * @warning A função não realiza validações rigorosas de entrada, portanto,
 *          espera-se que o usuário insira dados válidos para evitar
 *          comportamentos indesejados.
 */
void run_one_fixed_property_comparison();

/**
 * @brief Executa a comparação entre uma propriedade de cidades.
 *
 * A função aloca memória para armazenar duas cidades e permite ao usuário
 * escolher uma propriedade dessas cidades para comparar os seus valores. O
 * processo continua até que o usuário decida interromper.
 *
 * @note As cidades são alocadas e armazenadas em um array de dois ponteiros.
 *       A comparação é feita por meio da função `compare_one_float_property()`
 *       ou `compare_one_long_int_property()`, dependendo do tipo de dado
 *       envolvido.
 * 
 *       A função depende das seguintes funções auxiliares:
 * 
 * - `alocate_cities_to_compare`: Aloca e inicializa duas estruturas `City`para
 *                                comparação.
 * 
 * - `show_properties_to_compare`: Exibe as propriedades disponíveis para
 *                                 comparação entre as cartas.
 * 
 * - `choose_property`: Solicita ao usuário que escolha uma propriedade para
 *                      comparação.
 * 
 * - `compare_one_float_property`: Compara duas propriedades do tipo `float` de
 *                                 duas cidades e determina a vencedora.
 * 
 * - `compare_one_long_int_property`: Compara duas propriedades do tipo `long
 *                                    int` de duas cidades e determina a
 *                                    vencedora.
 * 
 * - `ask_to_keep_comparing`: Pergunta ao usuário se deseja continuar comparando
 *                            propriedades.
 * 
 * @see alocate_cities_to_compare()
 * @see show_properties_to_compare()
 * @see choose_property()
 * @see compare_one_float_property()
 * @see compare_one_long_int_property()
 * @see ask_to_keep_comparing()
 */
void run_one_property_comparison();

/**
 * @brief Executa a comparação entre duas propriedades de cidades.
 *
 * A função aloca memória para armazenar duas cidades e permite ao usuário
 * escolher duas propriedades dessas cidades para comparar a soma dos valores
 * correspondentes. O processo continua até que o usuário decida interromper.
 *
 * @note As cidades são alocadas e armazenadas em um array de dois ponteiros.
 *       A comparação é feita por meio da função `compare_two_float_properties()`
 *       ou `compare_two_long_int_properties()`, dependendo do tipo de dado
 *       envolvido.
 * 
 *       A função depende das seguintes funções auxiliares:
 * 
 * - `alocate_cities_to_compare`: Aloca e inicializa duas estruturas `City`para
 *                                comparação.
 * 
 * - `show_properties_to_compare`: Exibe as propriedades disponíveis para
 *                                 comparação entre as cartas.
 * 
 * - `choose_first_property`: Solicita ao usuário que escolha a primeira
 *                            propriedade para comparação.
 * 
 * - `choose_second_property`: Solicita ao usuário que escolha a segunda
 *                             propriedade para comparação.
 * 
 * - `compare_two_float_properties`: Compara duas propriedades do tipo `float`
 *                                   de duas cidades e determina a vencedora.
 * 
 * - `compare_two_long_int_properties`: Compara duas propriedades do tipo `long
 *                                      int` de duas cidades e determina a
 *                                      vencedora.
 * 
 * - `ask_to_keep_comparing`: Pergunta ao usuário se deseja continuar comparando
 *                            propriedades.
 *
 * @see alocate_cities_to_compare()
 * @see show_properties_to_compare()
 * @see choose_first_property()
 * @see choose_second_property()
 * @see compare_two_float_properties()
 * @see compare_two_long_int_properties()
 * @see ask_to_keep_comparing()
 */
void run_two_properties_comparison();

#endif
