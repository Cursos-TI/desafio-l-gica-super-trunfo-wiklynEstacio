#include "card.h"
#include "city.h"
#include "interface.h"
#include "util.h"

void show_functionalities_menu()
{
    puts("O programa possui as seguintes funcionalidades:\n");
    puts("\033[1m1. Registro de cartas:\033[0m Permite registrar cartas e ver os dados registrados para cada carta.\n");
    puts("\033[1m2. Registro de duas cartas e comparacao entre a propriedade \"Populacao\":\033[0m Permite registrar duas cartas, ver os dados de cada uma, fazer a comparacao entre os valores da propriedade \"Populacao\" e ver qual a carta vencedora, que será a que tiver maior valor de \"Populacao\".\n");
    puts("\033[1m3. Registro de duas cartas e comparacao entre uma propriedade, a escolha do usuario:\033[0m Permite registrar duas cartas, ver os dados de cada uma, fazer a comparacao entre os valores da propriedade escolhida e ver qual a carta vencedora, que será a que tiver maior valor na propriedade escolhida, com excessão de \"Densidade Populacional\", que terá como verncedora a carta com menor valor.\n");
    puts("\033[1m4. Registro de duas cartas e comparacao entre duas propriedades, a escolha do usuario:\033[0m Permite registrar duas cartas, ver os dados de cada uma, fazer a comparacao entre os valores das propriedades escolhidas e ver qual a carta vencedora, que será a que tiver maior valor de soma das propriedades escolhidas.");
}

int choose_functionality()
{
    int chosen_functionality = 0;

    printf("\nEscolha o numero da opcao que deseja executar: ");

    do
    {
        // Tenta ler a entrada
        if (scanf("%d", &chosen_functionality) != 1)
        {
            // Se a entrada for inválida: limpa o buffer de entrada
            while (getchar() != '\n');
            printf("Opcao invalida. Por favor, insira uma das opcoes apresentadas: ");
            continue;
        }
        
        // Se a entrada for válida, checa se é um dos valores possíveis
        if (!is_valid_functionality(chosen_functionality))
            printf("Opcao invalida. Por favor, insira uma das opcoes apresentadas: ");

    } while (!is_valid_functionality(chosen_functionality));

    puts("");
    return chosen_functionality;
}

void register_cards(int max_cities)
{
    if (max_cities <= 0)
    {
        fprintf(stderr, "Erro: valor de `max_cites` precisa ser positivo em `register_cards`.\n");
        exit(EXIT_FAILURE);
    }

    // Cria uma lista de ponteiros nulos, onde serão apontadas as cartas
    City* city_list[max_cities];
    for (int i = 0; i < max_cities; i++) {
        city_list[i] = NULL;
    }
    
    // Adiciona variáveis de apoio
    int registered_cities_count = 0;
    char keep_registering = 'S';
    
    // Mantém interação com usuário até o número máximo de cartas ser registrado
    // ou até o usuário responder que não quer mais registrar nenhuma carta.
    while (registered_cities_count < max_cities && keep_registering == 'S')
    {
        // Cria um ponteiro para ter acesso aos dados enviados pelo usuário
        City* city = get_city_data();

        city_list[registered_cities_count] = (City*) calloc(1, sizeof(City));

        // Usa um dos ponteiros da lista de cidades para apontar para os dados
        // enviados pelo usuário
        register_city(city, city_list[registered_cities_count]);

        puts("\nCarta registrada com sucesso.\n");

        // Exibe os dados enviados pelo usuário
        print_city(city_list[registered_cities_count]);

        registered_cities_count++;

        // Libera o ponteiro `city`
        free_city(&city);

        // Pergunta ao usuário se deve continuar a registrar cartas
        if (registered_cities_count < max_cities)
        {
            if (ask_to_keep_registering())
            {
                keep_registering = 'S';
                puts("");
            }
            else
                keep_registering = 'N';
        } else
            puts("\nNumero maximo de registros atingido.");
    }

    // Libera o espaço na memória alocado para as cidades
    free_city_list(city_list, registered_cities_count);
}

void run_one_fixed_property_comparison()
{
    City* city_list[2];

    // Aloca duas cidades na variável city_list
    alocate_cities_to_compare(city_list);

    // Compara o valor de população das duas cidades
    compare_population_size(city_list);
}

void run_one_property_comparison()
{
    // Aloca um array com dois ponteiros nulos
    City* city_list[2];
    alocate_cities_to_compare(city_list);

    puts("");
    // Lista as propriedades passíveis de comparação
    show_properties_to_compare();

    bool keep_comparing = 1;

    do
    {
        // Variável para armazenar a propriedade escolhida pelo usuário
        int property = choose_property();

        // Executa a comparação específica de acordo com a propriedade escolhida
        // pelo usuário
        switch (property)
        {
            case PopulationSize:
                puts("Comparação da propriedade \"Populacao\" das cartas:");

                // Exibe o número da cada carta e os seus valores de estado,
                //código e população
                for (int i = 0; i < 2; i++)
                {
                    printf(
                        "Carta %d - Estado: %c, Código: %s, Populacao: %ld\n",
                        i + 1,
                        city_list[i]->state,
                        city_list[i]->card_code,
                        city_list[i]->population_size
                    );
                }

                // Compara os valores da propriedade. A propriedade vencedora é
                // a que tiver maior valor
                compare_one_long_int_property(
                    city_list[0]->population_size, city_list[1]->population_size
                );

                break;

            case Area:
                puts("Comparação da propriedade \"Area\" das cartas:");

                for (int i = 0; i < 2; i++)
                {
                    printf(
                        "Carta %d - Estado: %c, Código: %s, Area: %.2f\n",
                        i + 1,
                        city_list[i]->state,
                        city_list[i]->card_code,
                        city_list[i]->area
                    );
                }

                compare_one_float_property(
                    city_list[0]->area, city_list[1]->area
                );

                break;

            case PopulationDensity:
                puts("Comparação da propriedade \"Densidade Populacional\" das cartas:");

                for (int i = 0; i < 2; i++)
                {
                    printf(
                        "Carta %d - Estado: %c, Código: %s, Densidade Populacional: %.2f\n",
                        i + 1,
                        city_list[i]->state,
                        city_list[i]->card_code,
                        city_list[i]->population_density
                    );
                }

                // Compara os valores da propriedade. No caso de densidade
                // populacional, a propriedade vencedora é a que tiver menor
                // valor
                compare_population_density(
                    city_list[0]->population_density,
                    city_list[1]->population_density
                );

                break;

            case GPD:
                puts("Comparação da propriedade \"PIB\" das cartas:");

                for (int i = 0; i < 2; i++)
                {
                    printf(
                        "Carta %d - Estado: %c, Código: %s, PIB: %.2f\n",
                        i + 1,
                        city_list[i]->state,
                        city_list[i]->card_code,
                        city_list[i]->gpd
                    );
                }

                compare_one_float_property(
                    city_list[0]->gpd, city_list[1]->gpd
                );

                break;

            case GPD_PC:
                puts("Comparação da propriedade \"PIB per Capta\" das cartas:");

                for (int i = 0; i < 2; i++)
                {
                    printf(
                        "Carta %d - Estado: %c, Código: %s, PIB per Capta: %.0f\n",
                        i + 1,
                        city_list[i]->state,
                        city_list[i]->card_code,
                        city_list[i]->gpd_pc
                    );
                }

                compare_one_float_property(
                    city_list[0]->gpd_pc, city_list[1]->gpd_pc
                );

                break;

            case TouristSitesCount:
                puts("Comparação da propriedade \"Numero de pontos turisticos\" das cartas:");

                for (int i = 0; i < 2; i++)
                {
                    printf(
                        "Carta %d - Estado: %c, Código: %s, Numero de pontos turisticos: %d\n",
                        i + 1,
                        city_list[i]->state,
                        city_list[i]->card_code,
                        city_list[i]->tourist_sites_count
                    );
                }

                compare_one_long_int_property(
                    (long int) city_list[0]->tourist_sites_count,
                    (long int) city_list[0]->tourist_sites_count
                );

                break;
        }

        // Pergunta se o usuário deseja comparar outra propriedade
        keep_comparing = ask_to_keep_comparing();
    // O loop continua até que o usuário decida não comparar mais nenhuma
    // propriedade
    } while (keep_comparing);
}

void run_two_properties_comparison()
{
    // Aloca um array com dois ponteiros nulos
    City* city_list[2];
    alocate_cities_to_compare(city_list);

    puts("");
    // Exibe as propriedades passíveis a comparação
    show_properties_to_compare();

    bool keep_comparing = 1;

    do
    {
        // Variável que armazena a primeira propriedade escolhida pelo usuário
        int first_property = choose_first_property();

        // Variável que armazena a segunda propriedade escolhida pelo usuário.
        // A segunda propriedade não deve ser igual à primeira
        int second_property = choose_second_property(first_property);

        puts("Comparação da soma das propriedades escolhidas:");

        // Executa a comparação específica de acordo com a primeira propriedade
        // escolhida pelo usuário
        switch (first_property)
        {
            // Executa a comparação específica de acordo com a segunda
            // propriedade escolhida pelo usuário
            case PopulationSize:
                switch (second_property)
                {
                    case Area:
                        // Exibe o número da cada carta e os seus valores de
                        // estado, código, das duas propriedades escolhidas e da
                        // soma destas duas propriedades
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Populacao: %ld, Area: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_size,
                                city_list[i]->area,
                                (float) city_list[i]->population_size + city_list[i]->area
                            );
                        }

                        // Compara os valores da propriedade. A carta vencedora
                        // é a que tiver maior valor da soma das propriedades
                        // escolhidas
                        compare_two_float_properties(
                            (float) city_list[0]->population_size,
                            city_list[0]->area,
                            (float) city_list[1]->population_size,
                            city_list[1]->area
                        );

                        break;
                    
                    case PopulationDensity:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Populacao: %ld, Densidade Populacional: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_size,
                                city_list[i]->population_density,
                                (float) city_list[i]->population_size + city_list[i]->population_density
                            );
                        }

                        compare_two_float_properties(
                            (float) city_list[0]->population_size,
                            city_list[0]->population_density,
                            (float) city_list[1]->population_size,
                            city_list[1]->population_density
                        );

                        break;
                    
                    case GPD:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Populacao: %ld, PIB: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_size,
                                city_list[i]->gpd,
                                (float) city_list[i]->population_size + city_list[i]->gpd
                            );
                        }

                        compare_two_float_properties(
                            (float) city_list[0]->population_size,
                            city_list[0]->gpd,
                            (float) city_list[1]->population_size,
                            city_list[1]->gpd
                        );

                        break;
                    
                    case GPD_PC:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Populacao: %ld, PIB per Capta: %.0f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_size,
                                city_list[i]->gpd_pc,
                                (float) city_list[i]->population_size + city_list[i]->gpd_pc
                            );
                        }

                        compare_two_float_properties(
                            (float) city_list[0]->population_size,
                            city_list[0]->gpd_pc,
                            (float) city_list[1]->population_size,
                            city_list[1]->gpd_pc
                        );

                        break;
                    
                    case TouristSitesCount:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Populacao: %ld, Numero de pontos turisticos: %d, Soma: %ld\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_size,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->population_size + city_list[i]->tourist_sites_count
                            );
                        }

                        compare_two_long_int_properties(
                            city_list[0]->population_size,
                            (long int) city_list[0]->tourist_sites_count,
                            city_list[1]->population_size,
                            (long int) city_list[1]->tourist_sites_count
                        );

                        break;

                    default:
                        break;
                }

                break;

            case Area:
                switch (second_property)
                {
                    case PopulationSize:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Area: %.2f, Populacao: %ld, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->area,
                                city_list[i]->population_size,
                                city_list[i]->area + (float) city_list[i]->population_size
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->area,
                            (float) city_list[0]->population_size,
                            city_list[1]->area,
                            (float) city_list[1]->population_size
                        );

                        break;
                    
                    case PopulationDensity:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Area: %.2f, Densidade Populacional: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->area,
                                city_list[i]->population_density,
                                city_list[i]->area + city_list[i]->population_density
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->area,
                            city_list[0]->population_density,
                            city_list[1]->area,
                            city_list[1]->population_density
                        );

                        break;
                    
                    case GPD:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Area: %.2f, PIB: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->area,
                                city_list[i]->gpd,
                                city_list[i]->area + city_list[i]->gpd
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->area, city_list[0]->gpd,
                            city_list[1]->area, city_list[1]->gpd
                        );

                        break;
                    
                    case GPD_PC:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Area: %.2f, PIB per Capta: %.0f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->area,
                                city_list[i]->gpd_pc,
                                city_list[i]->area + city_list[i]->gpd_pc
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->area, city_list[0]->gpd_pc,
                            city_list[1]->area, city_list[1]->gpd_pc
                        );

                        break;
                    
                    case TouristSitesCount:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Area: %.2f, Numero de pontos turisticos: %d, Soma: %lf\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->area,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->area + (float) city_list[i]->tourist_sites_count
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->area,
                            (float) city_list[0]->tourist_sites_count,
                            city_list[1]->area,
                            (float) city_list[1]->tourist_sites_count
                        );

                        break;

                    default:
                        break;
                }

                break;

            case PopulationDensity:
                switch (second_property)
                {
                    case PopulationSize:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Densidade Populacional: %.2f, Populacao: %ld, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_density,
                                city_list[i]->population_size,
                                city_list[i]->population_density + (float) city_list[i]->population_size
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->population_density,
                            (float) city_list[0]->population_size,
                            city_list[1]->population_density,
                            (float) city_list[1]->population_size
                        );

                        break;
                    
                    case Area:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Densidade Populacional: %.2f, Area: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_density,
                                city_list[i]->area,
                                city_list[i]->population_density + city_list[i]->area
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->population_density,
                            city_list[0]->area,
                            city_list[1]->population_density,
                            city_list[1]->area
                        );

                        break;
                    
                    case GPD:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Densidade Populacional: %.2f, PIB: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_density,
                                city_list[i]->gpd,
                                city_list[i]->population_density + city_list[i]->gpd
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->population_density, city_list[0]->gpd,
                            city_list[1]->population_density, city_list[1]->gpd
                        );

                        break;
                    
                    case GPD_PC:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Densidade Populacional: %.2f, PIB per Capta: %.0f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_density,
                                city_list[i]->gpd_pc,
                                city_list[i]->population_density + city_list[i]->gpd_pc
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->population_density,
                            city_list[0]->gpd_pc,
                            city_list[1]->population_density,
                            city_list[1]->gpd_pc
                        );

                        break;
                    
                    case TouristSitesCount:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Densidade Populacional: %.2f, Numero de pontos turisticos: %d, Soma: %lf\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->population_density,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->population_density + (float) city_list[i]->tourist_sites_count
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->population_density,
                            (float) city_list[0]->tourist_sites_count,
                            city_list[1]->population_density,
                            (float) city_list[1]->tourist_sites_count
                        );

                        break;

                    default:
                        break;
                }

                break;

            case GPD:
                switch (second_property)
                {
                    case PopulationSize:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB: %.2f, Populacao: %ld, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd,
                                city_list[i]->population_size,
                                city_list[i]->gpd + (float) city_list[i]->population_size
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd,
                            (float) city_list[0]->population_size,
                            city_list[1]->gpd,
                            (float) city_list[1]->population_size
                        );

                        break;
                    
                    case Area:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB: %.2f, Area: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd,
                                city_list[i]->area,
                                city_list[i]->gpd + city_list[i]->area
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd, city_list[0]->area,
                            city_list[1]->gpd, city_list[1]->area
                        );

                        break;
                    
                    case PopulationDensity:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB: %.2f, Densidade Populacional: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd,
                                city_list[i]->population_density,
                                city_list[i]->gpd + city_list[i]->population_density
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd, city_list[0]->population_density,
                            city_list[1]->gpd, city_list[1]->population_density
                        );

                        break;
                    
                    case GPD_PC:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB: %.2f, PIB per Capta: %.0f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd,
                                city_list[i]->gpd_pc,
                                city_list[i]->gpd + city_list[i]->gpd_pc
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd, city_list[0]->gpd_pc,
                            city_list[1]->gpd, city_list[1]->gpd_pc
                        );

                        break;
                    
                    case TouristSitesCount:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB: %.2f, Numero de pontos turisticos: %d, Soma: %lf\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->gpd + (float) city_list[i]->tourist_sites_count
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd,
                            (float) city_list[0]->tourist_sites_count,
                            city_list[1]->gpd,
                            (float) city_list[1]->tourist_sites_count
                        );

                        break;

                    default:
                        break;
                }

                break;
            
            case GPD_PC:
                switch (second_property)
                {
                    case PopulationSize:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB per Capta: %.0f, Populacao: %ld, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd_pc,
                                city_list[i]->population_size,
                                city_list[i]->gpd_pc + (float) city_list[i]->population_size
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd_pc,
                            (float) city_list[0]->population_size,
                            city_list[1]->gpd_pc,
                            (float) city_list[1]->population_size
                        );

                        break;
                    
                    case Area:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB per Capta: %.0f, Area: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd_pc,
                                city_list[i]->area,
                                city_list[i]->gpd_pc + city_list[i]->area
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd_pc, city_list[0]->area,
                            city_list[1]->gpd_pc, city_list[1]->area
                        );

                        break;
                    
                    case PopulationDensity:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB per Capta: %.0f, Densidade Populacional: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd_pc,
                                city_list[i]->population_density,
                                city_list[i]->gpd_pc + city_list[i]->population_density
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd_pc,
                            city_list[0]->population_density,
                            city_list[1]->gpd_pc,
                            city_list[1]->population_density
                        );

                        break;
                    
                    case GPD:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB per Capta: %.0f, PIB: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd_pc,
                                city_list[i]->gpd,
                                city_list[i]->gpd_pc + city_list[i]->gpd
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd_pc, city_list[0]->gpd,
                            city_list[1]->gpd_pc, city_list[1]->gpd
                        );

                        break;
                    
                    case TouristSitesCount:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, PIB per Capta: %.0f, Numero de pontos turisticos: %d, Soma: %lf\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->gpd_pc,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->gpd_pc + (float) city_list[i]->tourist_sites_count
                            );
                        }

                        compare_two_float_properties(
                            city_list[0]->gpd_pc,
                            (float) city_list[0]->tourist_sites_count,
                            city_list[1]->gpd_pc,
                            (float) city_list[1]->tourist_sites_count
                        );

                        break;

                    default:
                        break;
                }

                break;

            case TouristSitesCount:
                switch (second_property)
                {
                    case PopulationSize:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Numero de pontos turisticos: %d, Populacao: %ld, Soma: %ld\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->population_size,
                                city_list[i]->tourist_sites_count + city_list[i]->population_size
                            );
                        }

                        compare_two_long_int_properties(
                            city_list[0]->tourist_sites_count,
                            (long int) city_list[0]->population_size,
                            city_list[1]->tourist_sites_count,
                            (long int) city_list[1]->population_size
                        );

                        break;

                    case Area:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Numero de pontos turisticos: %d, Area: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->area,
                                (float) city_list[i]->tourist_sites_count + city_list[i]->area
                            );
                        }

                        compare_two_float_properties(
                            (float) city_list[0]->tourist_sites_count,
                            city_list[0]->area,
                            (float) city_list[1]->tourist_sites_count,
                            city_list[1]->area
                        );

                        break;
                    
                    case PopulationDensity:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Numero de pontos turisticos: %d, Densidade Populacional: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->population_density,
                                (float) city_list[i]->tourist_sites_count + city_list[i]->population_density
                            );
                        }

                        compare_two_float_properties(
                            (float) city_list[0]->tourist_sites_count,
                            city_list[0]->population_density,
                            (float) city_list[1]->tourist_sites_count,
                            city_list[1]->population_density
                        );

                        break;
                    
                    case GPD:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Numero de pontos turisticos: %d, PIB: %.2f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->gpd,
                                (float) city_list[i]->tourist_sites_count + city_list[i]->gpd
                            );
                        }

                        compare_two_float_properties(
                            (float) city_list[0]->tourist_sites_count,
                            city_list[0]->gpd,
                            (float) city_list[1]->tourist_sites_count,
                            city_list[1]->gpd
                        );

                        break;
                    
                    case GPD_PC:
                        for (int i = 0; i < 2; i++)
                        {
                            printf(
                                "Carta %d - Estado: %c, Código: %s, Numero de pontos turisticos: %d, PIB per Capta: %.0f, Soma: %.2f\n",
                                i + 1,
                                city_list[i]->state,
                                city_list[i]->card_code,
                                city_list[i]->tourist_sites_count,
                                city_list[i]->gpd_pc,
                                (float) city_list[i]->tourist_sites_count + city_list[i]->gpd_pc
                            );
                        }

                        compare_two_float_properties(
                            (float) city_list[0]->tourist_sites_count,
                            city_list[0]->gpd_pc,
                            (float) city_list[1]->tourist_sites_count,
                            city_list[1]->gpd_pc
                        );

                        break;

                    default:
                        break;
                }

                break;
        }
        // Pergunta se o usuário deseja comparar outra propriedade
        keep_comparing = ask_to_keep_comparing();
    // O loop continua até que o usuário decida não comparar mais nenhuma
    // propriedade
    } while (keep_comparing);
}
