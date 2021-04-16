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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief EStructura utilizada para almacenar las sumas y luego imprimirlas
 *
 */
struct Pair {
    int64_t first;
    int64_t second;
    int64_t third;
};
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
 * @param numero entero
 * @return void
 */
void conjetura_fuerte(int64_t num_temp) {
    int64_t numero = 0;

    if (num_temp < 0) {
        numero = num_temp * -1;
    } else {
        numero = num_temp;
    }

    int64_t contador = 0;
    // int64_t temp = 2;
    int tamano = 10;

    struct Pair *sumas = (struct Pair *)calloc(tamano, sizeof(struct Pair));

    for (int64_t i = 2; i < numero; i++) {
        if (es_primo(i) == 1) {
            for (int64_t j = i; j < numero; j++) {
                if (i + j == numero && es_primo(j) == 1) {
                    if (num_temp < 0) {
                        sumas[contador].first = (int64_t)i;
                        sumas[contador].second = (int64_t)j;
                    }
                    contador++;
                    if (contador == tamano && num_temp < 0) {
                        tamano = tamano * 2;
                        struct Pair *sumas_temp =
                            realloc(sumas, (tamano * 2) * sizeof(struct Pair));
                        if (sumas_temp == NULL) {
                            printf("Memory not reallocated\n");
                            exit(0);
                        } else {
                            sumas = sumas_temp;
                        }
                    }
                }
            }
        }
    }
    if (num_temp < 0) {
        printf("-%ld: %ld sums : ", numero, contador);

        for (int i = 0; i < contador; i++) {
            printf("%ld + %ld, ", sumas[i].first, sumas[i].second);
        }
    } else {
        printf("%ld: %ld sums: ", numero, contador);
    }
    free(sumas);
}
/**
 * @brief Para todo numero impar utiliza la conjetura fuerte de goldbach
 * @param numero entero
 * @return void
 */
void conjetura_debil(int64_t num_temp) {
    int64_t numero = 0;

    if (num_temp < 0) {
        numero = num_temp * -1;
    } else {
        numero = num_temp;
    }

    int64_t contador = 0;
    int tamano = 10;

    struct Pair *sumas = (struct Pair *)calloc(tamano, sizeof(struct Pair));

    for (int64_t x = 2; x < numero; x++) {
        if (es_primo(x) == 1) {
            for (int64_t y = x; y < numero; y++) {
                if (es_primo(y) == 1) {
                    for (int64_t z = y; z < numero; z++) {
                        if (x + y + z == numero && es_primo(z) == 1) {
                            if (num_temp < 0) {
                                sumas[contador].first = (int64_t)x;
                                sumas[contador].second = (int64_t)y;
                                sumas[contador].third = (int64_t)z;
                            }
                            contador++;
                            if (contador == tamano && num_temp < 0) {
                                tamano = tamano * 2;
                                struct Pair *sumas_temp = realloc(
                                    sumas, (tamano * 2) * sizeof(struct Pair));
                                if (sumas_temp == NULL) {
                                    printf("Memory not reallocated\n");
                                    exit(0);
                                } else {
                                    sumas = sumas_temp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (num_temp < 0) {
        printf("- %ld: %ld sums : ", numero, contador);

        for (int i = 0; i < contador; i++) {
            printf("%ld + %ld + %ld, ", sumas[i].first, sumas[i].second,
                   sumas[i].third);
        }
    } else {
        printf("%ld: %ld sums: ", numero, contador);
    }

    free(sumas);
}

/**
 * @brief Determina si el dato ingresado es un caracter alfabetico
 * @param char
 * @return void
 */
int es_alpha(char *dato_entrada) {
    int tamano = strlen(dato_entrada);
    int ptr = 0;

    if (dato_entrada[0] == '-') {
        ptr = 1;
    }

    for (int i = ptr; i < tamano; i++) {
        if (isalpha(dato_entrada[i])) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Metodo que controla la entrada de datos para utilizar la conjetura de
 * GoldBach
 * @param numero entero
 * @return void
 */
void goldbach(int64_t num) {
    if (num > ((int64_t)pow(2, 63) - 1) || num < -((int64_t)pow(2, 63) - 1)) {
        printf("NA");
    } else {
        if ((num <= 5 && num >= -5)) {
            printf("%ld: NA\n", num);
        } else {
            if (par_impar(num) == 1) {
                conjetura_fuerte(num);
            } else {
                conjetura_debil(num);
            }
        }
    }
}

/**
 * @brief Muestra la interfaz del programa
 * @param -
 * @return void
 */
void iniciar() {
    char dato_entrada[100];
    int opcion = 1;

    while (opcion == 1) {
        printf("\n\nIngrese un digito mayor de 5 o menor de -5: \nNumero: ");
        scanf("%s", dato_entrada);
        if (es_alpha(dato_entrada) == 0) {
            int64_t num = atol(dato_entrada);
            goldbach(num);
        } else {
            opcion = 0;
        }
    }
}

/**
 * @return El menu del progama de la Conjetura De GoldBach
 */
int main(void) {
    iniciar();

    return 0;
}
