#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
};

void insertTerm(struct Term** poly, int coeff, int exp) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coefficient = coeff;
    newTerm->exponent = exp;
    newTerm->next = NULL;

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

struct Term* multiplyPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;

    while (poly1 != NULL) {
        struct Term* temp = poly2;
        while (temp != NULL) {
            int coeff = poly1->coefficient * temp->coefficient;
            int exp = poly1->exponent + temp->exponent;
            insertTerm(&result, coeff, exp);
            temp = temp->next;
        }
        poly1 = poly1->next;
    }

    struct Term* current = result;
    while (current != NULL) {
        struct Term* temp = current->next;
        while (temp != NULL) {
            if (current->exponent == temp->exponent) {
                current->coefficient += temp->coefficient;
                // Remove the temp term from the result
                // (similar to deleting a node in a linked list)
                struct Term* toDelete = temp;
                current->next = temp->next;
                free(toDelete);
            }
            temp = temp->next;
        }
        current = current->next;
    }

    return result;
}

struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;

    while (poly1 != NULL || poly2 != NULL) {
        if (poly1 == NULL) {
            insertTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else if (poly2 == NULL) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else {
            if (poly1->exponent > poly2->exponent) {
                insertTerm(&result, poly1->coefficient, poly1->exponent);
                poly1 = poly1->next;
            } else if (poly1->exponent < poly2->exponent) {
                insertTerm(&result, poly2->coefficient, poly2->exponent);
                poly2 = poly2->next;
            } else {
                int coeff = poly1->coefficient + poly2->coefficient;
                insertTerm(&result, coeff, poly1->exponent);
                poly1 = poly1->next;
                poly2 = poly2->next;
            }
        }
    }

    return result;
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    struct Term* resultProduct = NULL;
    struct Term* resultSum = NULL;

    int n1;
    printf("Enter the number of terms for the first polynomial: ");
    scanf("%d", &n1);
    printf("Enter the terms for the first polynomial (coeff exponent):\n");
    for (int i = 0; i < n1; i++) {
        int coeff, exp;
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly1, coeff, exp);
    }

    int n2;
    printf("Enter the number of terms for the second polynomial: ");
    scanf("%d", &n2);
    printf("Enter the terms for the second polynomial (coeff exponent):\n");
    for (int i = 0; i < n2; i++) {
        int coeff, exp;
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }

    printf("\nFirst polynomial:\n");
    displayPolynomial(poly1);
    printf("\nSecond polynomial:\n");
    displayPolynomial(poly2);

    resultProduct = multiplyPolynomials(poly1, poly2);
    printf("\nProduct of the two polynomials:\n");
    displayPolynomial(resultProduct);

    resultSum = addPolynomials(poly1, poly2);
    printf("\nSum of the two polynomials:\n");
    printf("Resultant polynomial: ");
    displayPolynomial(resultSum);

    free(poly1);
    free(poly2);
    free(resultProduct);
    free(resultSum);

    return 0;
}

