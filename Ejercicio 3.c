#include <stdio.h>
#include <pthread.h>

#define SIZE 10

typedef struct {
    int base;
    int exp;
    int potencia;
} potencia_t;

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

void setBaseExp(potencia_t* pt, int base, int exp) {
    pt->base = base;
    pt->exp = exp;
    pt->potencia = -1;
}

int main() {
    potencia_t arr1[SIZE];
    pthread_t threads[SIZE];

    initArrayEst(arr1);

    printf("Estado inicial de arr1:\n");
    printArrayEst(arr1);

    for (int i = 0; i < SIZE; i++) {
        setBaseExp(&arr1[i], i, 2);
    }

    printf("\nEstado de arr1 después de setBaseExp:\n");
    printArrayEst(arr1);

    for (int i = 0; i < SIZE; i++) {
        pthread_create(&threads[i], NULL, calcuPotHeb, (void*)&arr1[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nEstado de arr1 después de calcular las potencias con hebras:\n");
    printArrayEst(arr1);

    return 0;
}
