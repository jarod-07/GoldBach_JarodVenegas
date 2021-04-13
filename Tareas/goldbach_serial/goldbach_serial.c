#include <Stdio.h>
#include <math.h>
#include <ctype.h>

/*
Funcion: determina si un numero es negativo
Input: numero entero 
*/
int es_negativo(long long int num)
{
    if(num < 0)
    {
        return 1; // es negativo
    }
    return 0; // es positivo
}

/*
Funcion: determina si un numero primo
Input: numero entero
Output: devuelve un 1 si es primo y un 0 si no es primo
*/
int es_primo(long long int num)
{
    for(long long int i = 2; i <= (long long int)sqrt(num); i++)
    {
            
        if (num % i == 0)
        {
            return 0; // no es primo
        }
    }
    return 1;  // si es primo
}

/*
Funcion: determina si un numero es par o impar
Input: numero entero
Output: devuelve un 1 si es par y un 0 si es impar
*/
int par_impar(long long int num)
{
    if(num<0){num * -1;}
    if (num % 2 == 0)
    {
        return 1; // el numero es par
    }
    return 0; // el numero es impar
}

/*
Funcion: para todo numero par determina el numero de sumas con numeros impares que se pueden hacer
Input: numero entero
Output: void
*/
void conjetura_fuerte(long long int num_temp)
{
    for(long long int x=1; x<=2; x++)
    {
        long long int numero = 0;
        if(es_negativo(num_temp)==1)
        {
            numero=num_temp * -1;
        }
        else
        {
            numero = num_temp;
        }

        long long int contador = 0;
        long long int temp = 2;

        for(long long int i = numero-temp; i>2; i--)
        {
            if (es_primo(temp)==1 && es_primo(i)==1 && temp<=i)
            {
                contador++;
                if(x==2 && es_negativo(num_temp))
                {
                    printf("%lld + %lld, ",temp,i);
                }
            }
            temp++;
        }

        if(x==1)
        {
            printf ("%lld: %lld sums : ",numero, contador);
        }
    }
}

/*
Funcion: para todo numero impar determina el numero de sumas con numeros impares que se pueden hacer
Input: numero entero
Output: void
*/
void conjetura_debil(long long int num_temp)
{
    for(long long int i=1; i<=2;i++)
    {
        long long int numero=0;

        if(es_negativo(num_temp)==1)
        {
            numero=num_temp * -1;
        }
        else
        {
            numero = num_temp;
        }

        long long int contador = 0;

        for ( long long int x = 2; x < numero; x++ )
        {
            if ( es_primo(x) == 1 )
            {
                for ( long long int y = x; y < numero; y++ )
                {
                    if ( es_primo(y) == 1 ) 
                    {
                        for ( long long int z = y; z < numero; z++ )
                        {
                            if ( x + y + z == numero && es_primo(z)==1 )
                            {
                                contador++;
                                if(i==2 && es_negativo(num_temp))
                                {
                                    printf("%lld + %lld + %lld, ",x, y, z);
                                }
                            }
                        }
                    }
                }
            }
        }
        if(i==1)
        {
            printf ("%lld: %lld sums : ",numero, contador);
        }
    }
}

/*
Funcion: metodo que controla toda la conjetura de GoldBach
Input: numero entero
Output: void
*/
void goldbach(long long int num){
    if(num > pow(2, 62)-1)
    {
        printf ("%lld: NA ",num);
    }
    else{
            if( num <= 5 || num >= -5 )
            {
                printf("%i: NA\n", num);
            }
            else
            {
                if(par_impar(num) == 1)
                {
                    conjetura_fuerte(num);
                }
                else
                {
                    conjetura_debil(num);
                }
            }
        }
}

int main(void) {

    // es_negativo(-11);
    // es_negativo(11);

    // pasar_positivo(-28);
    // pasar_positivo(-111);

    //conjetura_fuerte(10);
    //conjetura_fuerte(-10);

    //conjetura_debil(12345);

    //goldbach(12345);
    //goldbach(-10);     
    long long int num;
    int opcion = 1;
    while(opcion == 1)
    {

        printf("\nIngrese un digito mayor de 5 o menor de -5: \nNumero: ");
        scanf("%lld", &num);

        printf("\n");
        goldbach(num);

        printf("\n\nDesea continuar?   || 1=Si || 0=No ||\n");
        scanf("%lld", &opcion);
    }
    
    return 0;

}
