#include <stdio.h>

typedef struct rational_number {
    int num;
    int deno;
}rational;

// read the Rational Number from stdin
void getRationalNumber(rational *number){
    printf("Enter Numerator: ");
    scanf("%d", &number->num);

    printf("Enter Denominator: ");
    scanf("%d", &number->deno);
}

// Get the Reduction Factor for the division with numerator and denominator
int getReductionFactor(int larger, int smaller){
    if(smaller == 0)
        return larger;
    return getReductionFactor(smaller, larger % smaller);
}

// Get the fraction to its lowest form
void getReducedFraction(rational *number){
    int red_factor;

    red_factor = (number->num > number->deno) ? getReductionFactor(number->num, number->deno) : getReductionFactor(number->deno, number->num);

    number->num /= red_factor;
    number->deno /= red_factor;

    printf("The Reduced fraction is: %d / %d\n", number->num, number->deno);
}

int main() {
    rational number;

    getRationalNumber(&number);

    getReducedFraction(&number);

    return 0;

}