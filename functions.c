#include "stdio.h"

//f1 is a simple print
void f1() {
    printf ("Riccardo Mantegazza 1986433 - Ingegneria Informatica\n");
}

//f2 calculates the power of a number
void f2() {
    int b, e;

    printf ("Let's calculate the power of a number b!\n");
    printf ("Choose the base b: ");
    scanf ("%d", &b);

    printf ("Choose the exponent e: ");
    scanf ("%d", &e);
    int result = b^e;
    printf ("%d ^ %d = %\n", &b, &e, &result);
}

//f3 draws a square with the edge of a chosen number
void f3() {
    int n = -1;
    while (n <= 0) {
        printf ("Choose a positive number: ");
        scanf ("%d", &n);
        if (n <= 0) {
            printf ("The number must be positive!");
        }
    }

    printf ("Let's draw a square!\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf ("*");
        printf ("\n");
    }

}

//f4 draws an isosceles triangle with the edge of a chosen number
void f4() {
    int n = -1;
    while (n <= 0) {
        printf ("Choose a positive odd number: ");
        scanf ("%d", &n);
        if (n <= 0 || n % 2 == 0) {
            printf ("The number must be positive and odd!");
        }
    }

    printf ("Let's draw a triangle!\n");

    int aux = 1;
    while (aux != n) {
        int calc = (n - aux) / 2;
        for (int i = 0; i < calc; i++) printf (" ");
        for (int j = 0; j < aux; j++) printf ("*");
        for (int k = 0; k < calc; k++) printf (" ");
        printf ("\n");
        aux += 2;
    }
}

//f5 calculates the factorial of a number by input
void f5() {
    int n = -1;

    while (n < 0) {
        printf ("Choose a positive number: ");
        scanf ("%d", &n);
        if (n < 0) {
            printf ("The number must be positive!");
        }
    }

    printf ("The factorial of %d is ", &n);
    int ret = 1;
    if (n != 0 && n != 1) {
        while (n != 1) {
            ret = ret * n;
            n--;
        }
    }
    printf ("%d.\n", &ret);

}