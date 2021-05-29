/**
 * @file goldbach_serial.c
 * @author Jarod Venegas(JAROD.VENEGAS@ucr.ac.cr)
 * @brief  Conjetura debil y fuerte de Goldbcah
 * @version 0.1
 * @date 2021-04-15
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief EStructura utilizada para almacenar las sumas y luego imprimirlas
 *
 */
typedef struct {
    int64_t first;
    int64_t second;
    int64_t third;
} Sumas;
/**
 * @brief Determina si un numero es primo
 * @param numero entero
 * @return devuelve un 1 si es primo y un 0 si no es primo
 */
int es_primo(int64_t num) {
    for (int64_t i = 2; i < num; i++) {
        if (num % i == 0) {
            return 0;  // no es primo
        }
    }
    return 1;  // si es primo
}

/**
 * @brief Determina si un numero es par o impar
 * @param numero entero
 * @return devuelve un 1 si es par y un 0 si es impar
 */
int par_impar(int64_t num) {
    if (num < 0) {
        num = num * -1;
    }
    if (num % 2 == 0) {
        return 1;  // el numero es par
    }
    return 0;  // el numero es impar
}

/**
 * @brief Para todo numero par utiliza la conjetura fuerte de goldbach
 * @param num_temp entero de 64 bits
 * @param contador entero de 64 bits
 * @param output file
 * @return Una struct de Sumas
 */
Sumas* conjetura_fuerte(int64_t num_temp, int64_t* contador, FILE* output) {
    int64_t numero = 0;

    if (num_temp < 0) {
        numero = num_temp * -1;
    } else {
        numero = num_temp;
    }
    int tamano = 10;

    Sumas* sumas = (Sumas*)calloc(tamano, sizeof(Sumas));
    int64_t pivote = 2;
    for (int64_t i = numero - pivote; i > 2; i--) {
        if ((es_primo(pivote) == 1) && (es_primo(i) == 1) && pivote <= i) {
            if (num_temp < 0) {
                sumas[*contador].first = (int64_t)pivote;
                sumas[*contador].second = (int64_t)i;
            }

            *contador = *contador + 1;
            if (*contador == tamano && numero < 0) {
                Sumas* sumas_temp =
                    realloc(sumas, (tamano * 2) * sizeof(Sumas));
                if (sumas_temp == NULL) {
                    fprintf(output, "Memory not reallocated\n");
                    exit(0);
                } else {
                    tamano = tamano * 2;
                    sumas = sumas_temp;
                }
            }
        }
        pivote++;
    }

    return sumas;
}

/**
 * @brief Para todo numero impar utiliza la conjetura debil de goldbach
 * @param num_temp entero de 64 bits
 * @param contador entero de 64 bits
 * @param output file
 * @return Una struct de Sumas
 */
Sumas* conjetura_debil(int64_t num_temp, int64_t* contador, FILE* output) {
    int64_t numero = 0;

    if (num_temp < 0) {
        numero = num_temp * -1;
    } else {
        numero = num_temp;
    }
    int tamano = 10;
    Sumas* sumas = (Sumas*)calloc(tamano, sizeof(Sumas));

    for (int64_t i = 2; i < numero; i++) {
        if (es_primo(i) == 1) {
            for (int64_t j = i; j < numero; j++) {
                if (es_primo(j)) {
                    int64_t numero_posible = numero - (i + j);
                    if (i + j + numero_posible == numero &&
                        es_primo(numero_posible)) {
                        if (numero_posible > 2 && numero_posible >= j) {
                            if (num_temp < 0) {
                                sumas[*contador].first = (int64_t)i;
                                sumas[*contador].second = (int64_t)j;
                                sumas[*contador].third =
                                    (int64_t)numero_posible;
                            }
                            *contador = *contador + 1;
                            if (*contador == tamano && num_temp < 0) {
                                Sumas* sumas_temp = realloc(
                                    sumas, (tamano * 2) * sizeof(Sumas));
                                if (sumas_temp == NULL) {
                                    fprintf(output, "Memory not reallocated\n");
                                    exit(0);
                                } else {
                                    tamano = tamano * 2;
                                    sumas = sumas_temp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return sumas;
}

/**
 * @brief Imprime las sumas de la conjetura debil
 * @param num_temp entero de 64 bits
 * @param contador entero de 64 bits
 * @param  Sumas struct Sumas
 * @param output file
 * @return void
 */
void imprimir_debil(int64_t num_temp, int64_t contador, Sumas* sumas,
                    FILE* output) {
    int64_t primera;
    int64_t segunda;
    int64_t tercera;
    int64_t numero = 0;
    if (num_temp < 0) {
        numero = num_temp * -1;
    } else {
        numero = num_temp;
    }
    if (num_temp < 0) {
        fprintf(output,
                "-%" PRIu64
                ": "
                "%" PRIu64 " sums: ",
                numero, contador);
        for (int64_t i = 0; i < contador; i++) {
            if (i != contador - 1) {
                primera = sumas[i].first;
                segunda = sumas[i].second;
                tercera = sumas[i].third;
                fprintf(output,
                        "%" PRIu64
                        " + "
                        "%" PRIu64
                        " + "
                        "%" PRIu64 ", ",
                        primera, segunda, tercera);
            } else {
                primera = sumas[i].first;
                segunda = sumas[i].second;
                tercera = sumas[i].third;
                fprintf(output,
                        "%" PRIu64
                        " + "
                        "%" PRIu64
                        " + "
                        "%" PRIu64 "\n",
                        primera, segunda, tercera);
            }
        }
    } else {
        fprintf(output,
                "%" PRIu64
                ": "
                "%" PRIu64 " sums\n",
                num_temp, contador);
    }
}

/**
 * @brief Imprime las sumas de la conjetura fuerte
 * @param num_temp entero de 64 bits
 * @param contador entero de 64 bits
 * @param Sumas Struct de Sumas
 * @param output file
 * @return void
 */
void imprimir_fuerte(int64_t num_temp, int64_t contador, Sumas* sumas,
                     FILE* output) {
    int64_t primera;
    int64_t segunda;
    int64_t numero = 0;
    if (num_temp < 0) {
        numero = num_temp * -1;
    } else {
        numero = num_temp;
    }
    if (num_temp < 0) {
        fprintf(output,
                "-%" PRIu64
                ": "
                "%" PRIu64 " sums: ",
                numero, contador);
        for (int64_t i = 0; i < contador; i++) {
            if (i != contador - 1) {
                primera = sumas[i].first;
                segunda = sumas[i].second;
                fprintf(output,
                        "%" PRIu64
                        " + "
                        "%" PRIu64 ", ",
                        primera, segunda);
            } else {
                primera = sumas[i].first;
                segunda = sumas[i].second;
                fprintf(output,
                        "%" PRIu64
                        " + "
                        "%" PRIu64 "\n",
                        primera, segunda);
            }
        }
    } else {
        fprintf(output,
                "%" PRIu64
                ": "
                "%" PRIu64 " sums\n",
                num_temp, contador);
    }
}

/**
 * @brief Metodo que controla la entrada de datos para utilizar la conjetura de
 * GoldBach
 * @param numero entero de 64 bits
 * @param output File
 * @return void
 */
void goldbach(int64_t num, FILE* output) {
    int64_t contador_sumas = 0;
    if (num > ((int64_t)pow(2, 63) - 1) || num < -((int64_t)pow(2, 63) - 1)) {
        fprintf(output, "NA");
    } else {
        if ((num <= 5 && num >= -5)) {
            fprintf(output, "%ld :NA\n", num);
        } else {
            if (par_impar(num) == 1) {
                Sumas* sumas_pares =
                    conjetura_fuerte(num, &contador_sumas, output);
                imprimir_fuerte(num, contador_sumas, sumas_pares, output);
                free(sumas_pares);
            } else {
                Sumas* sumas_impares =
                    conjetura_debil(num, &contador_sumas, output);
                imprimir_debil(num, contador_sumas, sumas_impares, output);
                free(sumas_impares);
            }
        }
    }
}

/**
 * @brief Ingresa los valores digitados por el usuario dentro de un array
 * @param input file
 * @param output file
 * @return void
 */
void iniciar(FILE* input, FILE* output) {
    int64_t num;
    int tamano = 10;
    int contador = 0;
    int* valores = (int*)calloc(tamano, sizeof(int));
    while (fscanf(input, "%" SCNu64, &num) == 1) {
        if (contador == tamano) {
            valores = (int*)realloc(valores, (tamano * 2) * sizeof(int));
            if (valores == NULL) {
                fprintf(output, "Memory not reallocated\n");
                exit(0);
            } else {
                tamano = tamano * 2;
                valores[contador] = num;
            }
        } else {
            valores[contador] = num;
        }
        contador++;
    }
    for (int x = 0; x < contador; x++) {
        goldbach(valores[x], output);
    }
    free(valores);
}

/**
 * @return La interfaz del progama de la Conjetura De GoldBach
 */
int main(void) {
    FILE* input = stdin;
    FILE* output = stdout;
    iniciar(input, output);

    return 0;
}
