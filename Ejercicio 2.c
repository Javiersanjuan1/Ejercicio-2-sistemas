#include <stdio.h>
#include <pthread.h>

#define SIZE 10

typedef struct {
    int base;
    int exp;
    int potencia;
} potencia_t;

typedef potencia_t* potenciaP_t;

void initArrayEst(potencia_t arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i].base = i + 1;
        arr[i].exp = 0;
        arr[i].potencia = 1;
    }
}

void printArrayEst(potencia_t arr[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("arr[%d]: base: %d exp: %d potencia: %d\n",
               i, arr[i].base, arr[i].exp, arr[i].potencia);
    }
}

void* calcuPotHeb(void* arg) {
    potencia_t* pt = (potencia_t*)arg;

    pt->potencia = 1;
    for (int i = 0; i < pt->exp; i++) {
        pt->potencia *= pt->base;
    }

    return NULL;
}

int main() {
    potencia_t arr[SIZE];

    initArrayEst(arr);

    printf("Estado inicial del array:\n");
    printArrayEst(arr);

    pthread_t threads[SIZE];

    for (int i = 0; i < SIZE; i++) {
        pthread_create(&threads[i], NULL, calcuPotHeb, (void*)&arr[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nEstado final del array después de calcular las potencias:\n");
    printArrayEst(arr);

    return 0;
}
