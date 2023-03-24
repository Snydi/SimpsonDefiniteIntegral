#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

double f(double x) {
    return sin(x); // change this to the function you want to integrate
}

double integrate(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);

#pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * f(x);
        }
        else {
            sum += 4 * f(x);
        }
    }

    return (h / 3) * sum;
}

int main() {
    double a = 0; // lower limit of integration
    double b = 1; // upper limit of integration
    int n = 100000000; // number of intervals

    double integral = integrate(a, b, n);

    cout << "The definite integral of sin(x) from " << a << " to " << b << " is " << integral << endl;

    return 0;
}
