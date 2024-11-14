#include <stdio.h>

#define SIZE 10

typedef struct {
    int base;
    int exp;
    int potencia;
} potencia_t;

typedef potencia_t* potenciaP_t;

void setBaseExp(potenciaP_t potencia, int base, int exp) {
    potencia->base = base;
    potencia->exp = exp;
    potencia->potencia = -1;
}

int getPotencia(int base, int exp) {
    int resultado = 1;

    for (int i = 0; i < exp; i++) {
        resultado *= base;
    }

    return resultado;
}

void setPotenciaEst(potenciaP_t potencia) {
    potencia->potencia = getPotencia(potencia->base, potencia->exp);
}

int main() {
    potencia_t potencias[SIZE];

    setBaseExp(&potencias[0], 2, 3);
    setPotenciaEst(&potencias[0]);

    printf("Base: %d, Exponente: %d, Potencia: %d\n",
           potencias[0].base, potencias[0].exp, potencias[0].potencia);

    return 0;
}
