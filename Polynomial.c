#include <stdio.h>
#include <stdlib.h>

// Define a structure for a term in a polynomial
struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
};

// Function to create a new term
struct Term* createTerm(int coefficient, int exponent) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a term into a polynomial
void insertTerm(struct Term** poly, int coefficient, int exponent) {
    struct Term* newTerm = createTerm(coefficient, exponent);

    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        struct Term* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTerm;
    }
}

// Function to display a polynomial
void displayPolynomial(struct Term* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;

    while (poly1 != NULL || poly2 != NULL) {
        int coef1 = (poly1 != NULL) ? poly1->coefficient : 0;
        int exp1 = (poly1 != NULL) ? poly1->exponent : 0;

        int coef2 = (poly2 != NULL) ? poly2->coefficient : 0;
        int exp2 = (poly2 != NULL) ? poly2->exponent : 0;

        int sum_coef = coef1 + coef2;

        insertTerm(&result, sum_coef, exp1);

        if (poly1 != NULL) {
            poly1 = poly1->next;
        }
        if (poly2 != NULL) {
            poly2 = poly2->next;
        }
    }

    return result;
}

// Function to multiply two polynomials
struct Term* multiplyPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;

    while (poly1 != NULL) {
        struct Term* tempPoly2 = poly2;

        while (tempPoly2 != NULL) {
            int coef = poly1->coefficient * tempPoly2->coefficient;
            int exp = poly1->exponent + tempPoly2->exponent;

            // Add the term to the result
            insertTerm(&result, coef, exp);

            tempPoly2 = tempPoly2->next;
        }

        poly1 = poly1->next;
    }

    return result;
}

// Function to free the memory allocated for a polynomial
void freePolynomial(struct Term* poly) {
    struct Term* temp;

    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    struct Term* result;

    // Reading and storing polynomials
    int n1, n2; // Number of terms in each polynomial
    int coef, exp;

    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &n1);
    printf("Enter the terms of the first polynomial (coefficient exponent): ");
    for (int i = 0; i < n1; ++i) {
        scanf("%d %d", &coef, &exp);
        insertTerm(&poly1, coef, exp);
    }

    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &n2);
    printf("Enter the terms of the second polynomial (coefficient exponent): ");
    for (int i = 0; i < n2; ++i) {
        scanf("%d %d", &coef, &exp);
        insertTerm(&poly2, coef, exp);
    }

    // Displaying the polynomials
    printf("\nFirst Polynomial: ");
    displayPolynomial(poly1);

    printf("Second Polynomial: ");
    displayPolynomial(poly2);

    // Multiplication of polynomials
    result = multiplyPolynomials(poly1, poly2);
    printf("\nProduct of the two polynomials: ");
    displayPolynomial(result);

    // Addition of polynomials
    result = addPolynomials(poly1, poly2);
    printf("\nSum of the two polynomials: ");
    displayPolynomial(result);

    // Freeing allocated memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
