#ifndef UTIL_H // Include Guards
#define UTIL_H

/**
 * @brief Verifica se uma funcionalidade é válida.
 * 
 * @param functionality O valor da funcionalidade a ser verificada.
 * @return true se a funcionalidade for válida, false caso contrário.
 * 
 * @details Uma funcionalidade é considerada válida se seu valor estiver dentro 
 * do intervalo definido por `RegisterCards` e `CompareTwoPropertiesDinamically`.
 */
bool is_valid_functionality(int property);

/**
 * @brief Verifica se uma propriedade é válida.
 * 
 * @param property O valor da propriedade a ser verificada.
 * @return true se a propriedade for válida, false caso contrário.
 * 
 * @details Uma propriedade é considerada válida se seu valor estiver dentro 
 * do intervalo definido por `PopulationSize` e `TouristSitesCount`.
 */
bool is_valid_property(int property);

#endif
