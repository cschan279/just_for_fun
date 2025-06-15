#include <stdio.h>
#include <stdlib.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

/* Define precision (50 digits) */
#define PRECISION 50
typedef boost_multiprecision_cpp_dec_float_50 mp_float;

/* Function to compute factorial: n! */
mp_float factorial(int n) {
    mp_float result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

/* Function to compute Pochhammer symbol: (x)_n = x(x+1)...(x+n-1) */
mp_float pochhammer(mp_float x, int n) {
    mp_float result = 1.0;
    for (int i = 0; i < n; ++i) {
        result *= (x + i);
    }
    return result;
}

/* Saha-Sinha formula for pi */
mp_float compute_pi(mp_float lambda, int terms) {
    mp_float pi = 4.0; /* Initial term */
    mp_float sum = 0.0;

    for (int n = 1; n <= terms; ++n) {
        /* First part: (1/(n+lambda) - 4/(2n+1)) */
        mp_float term1 = (1.0 / (n + lambda)) - (4.0 / (2 * n + 1));

        /* Second part: ((2n+1)^2 / (4(n+lambda)) - n)_{n-1} */
        mp_float temp = (2 * n + 1);
        mp_float term2 = (temp * temp) / (4.0 * (n + lambda)) - n;
        term2 = pochhammer(term2, n - 1);

        /* Combine: term1 * term2 / n! */
        mp_float term = (term1 * term2) / factorial(n);
        sum += term;
    }

    pi += sum;
    return pi;
}

int main(int argc, char *argv[]) {
    /* Set lambda and number of terms */
    mp_float lambda = 3.0; /* Faster convergence with lambda = 3 */
    int terms = 30;        /* Enough for ~10 decimal places */

    if (argc > 1) {
        lambda = atof(argv[1]);
    }
    if (argc > 2) {
        terms = atoi(argv[2]);
    }

    /* Compute pi */
    mp_float pi = compute_pi(lambda, terms);

    /* Print result with high precision */
    printf("Computed pi (lambda=%.2f, terms=%d): %.50f\n", 
           (double)lambda, terms, (double)pi);
    printf("Reference pi: 3.14159265358979323846264338327950288419716939937510\n");

    return 0;
}