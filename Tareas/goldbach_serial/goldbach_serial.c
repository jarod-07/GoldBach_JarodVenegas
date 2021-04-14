#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Determina si un numero es primo
 * @param numero entero
 * @return devuelve un 1 si es primo y un 0 si no es primo
*/
int es_primo(long long int num){
    for(long long int i = 2; i < num/2; i++){
            
        if (num % i == 0){
            return 0; // no es primo
        }
    }
    return 1;  // si es primo
}

/**
 * @brief Determina si un numero es par o impar
 * @param numero entero
 * @return devuelve un 1 si es par y un 0 si es impar
*/
int par_impar(long long int num)
{
    if(num<0){num * -1;}
    if (num % 2 == 0){
        return 1; // el numero es par
    }
    return 0; // el numero es impar
}

/**
 * @brief Para todo numero par utiliza la conjetura fuerte de goldbach
 * @param numero entero
 * @return void
*/
void conjetura_fuerte(long long int num_temp)
{
    for(long long int x=1; x<=2; x++){
        long long int numero = 0;
        
        if(num_temp<0){
            numero=num_temp * -1;
        }
        else{
            numero = num_temp;
        }

        long long int contador = 0;
        long long int temp = 2;

        for(long long int i = numero-temp; i>2; i--){
            if (es_primo(temp)==1 && es_primo(i)==1 && temp<=i){
                contador++;
                if(x==2 && num_temp<0 )
                {
                    printf("%lld + %lld, ",temp,i);
                }
            }
            temp++;
        }
        if(x==1){
            printf ("%lld: %lld sums : ",numero, contador);
        }
    }
}

/**
 * @brief Para todo numero impar utiliza la conjetura fuerte de goldbach
 * @param numero entero
 * @return void
*/
void conjetura_debil(long long int num_temp){

    for(long long int i=1; i<=2;i++){
        long long int numero=0;

        if( num_temp<0 ){
            numero=num_temp * -1;
        }
        else{
            numero = num_temp;
        }

        long long int contador = 0;

        for ( long long int x = 2; x < numero; x++ ){
            if ( es_primo(x) == 1 ){

                for ( long long int y = x; y < numero; y++ ){
                    if ( es_primo(y) == 1 ) {

                        for ( long long int z = y; z < numero; z++ ){
                            if ( x + y + z == numero && es_primo(z)==1 ){

                                contador++;
                                if(i==2 && num_temp<0 ){

                                    printf("%lld + %lld + %lld, ",x, y, z);
                                }
                            }
                        }
                    }
                }
            }
        }
        if(i==1){
            printf ("%lld: %lld sums : ",numero, contador);
        }
    }
}

/**
 * @brief Determina si el dato ingresado es un caracter alfabetico
 * @param char 
 * @return void
*/
int es_alpha(char *dato_entrada){
    int tamano = strlen(dato_entrada);
    int ptr = 0;

    if(dato_entrada[0] == '-'){
        ptr=1;
    }

    for(int i = ptr; i<tamano; i++){
        if(isalpha(dato_entrada[i])){
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Metodo que controla la entrada de datos para utilizar la conjetura de GoldBach
 * @param numero entero 
 * @return void
*/
void goldbach(long long int num){
    if(num > pow(2, 63)-1 || ( num <= 5 && num >= -5) ){
        printf ("%lld: NA\n",num);
    }
    else{

        if(par_impar(num) == 1){
            conjetura_fuerte(num);
        }
        else{
            conjetura_debil(num);
        }   
    }
}

/**
 * @brief Muestra la interfaz del programa
 * @param -
 * @return void
*/
void iniciar(){
    char dato_entrada[100];
    int opcion = 1;
    while(opcion == 1)
    {
        printf("\nIngrese un digito mayor de 5 o menor de -5: \nNumero: ");
        scanf("%p", &dato_entrada);

        if(es_alpha(dato_entrada) == 0 ){

            long long int num = atol(dato_entrada);

            goldbach(num);
            printf("\n");
            printf("\n\nDesea continuar?   || 1=Si || 0=No ||\n");
            scanf("%d", &opcion);

        }
        else{
            opcion = 0;
        }
    }
}

/**
 * @return El menu del progama de la Conjetura De GoldBach
 */
int main(void){

    iniciar();
    return 0;
}
