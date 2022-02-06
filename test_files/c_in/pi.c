#include <stdio.h>

int main(){
    double numerator = 4.0;
    double denominator = 1.0;
    double fraction = 1.0;
    double pi = 0.0;
    long terms = 2000000;

    for (int i=1; i<terms; i++){
        fraction = numerator/denominator;
        if(i % 2)
            pi += fraction;
        else
            pi -= fraction;
        denominator += 2;
    }

    printf("%lf", pi);
} 