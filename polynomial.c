#include <stdio.h>
#include <stdlib.h>

struct element {
    int coeff;
    int exp;
};
typedef struct element element;


element *inp_pol (element *, int *);
element *add (element *, element *, element *, int *, int *, int *);
void display (element *, int *);


int main ()
{
    element *p1=NULL, *p2=NULL, *p3=NULL;
    int size1=0, size2=0, size3=0;

    printf ("FIRST POLYNOMIAL :\n");
    p1 = inp_pol(p1, &size1);
    printf ("\nSECOND POLYNOMIAL :\n");
    p2 = inp_pol(p2, &size2);

	printf ("\nFIRST POLYNOMIAL :\n");
    display (p1, &size1);
    
    printf ("\nSECOND POLYNOMIAL :\n");
    display (p2, &size2);
    p3 = add (p1, p2, p3, &size1, &size2, &size3);
    
    printf ("\nSUM :\n");
    display (p3, &size3);

	if (p1 != NULL)
		free(p1);
	if (p2 != NULL)
		free(p2);
	if (p1 != NULL && p2 != NULL) {
	if (p3 != NULL)
		free(p3);
	}


    return 0;
}


element *inp_pol (element *p, int *size)
{
    int i, tmp_coeff, deg=0;
    *size = 0;

    printf ("Enter degree of polynomial : ");
    scanf ("%d", &deg);
    for (i=deg; i>=0; i--) {
        printf ("Enter coefficient of x^%d : ", i);
        scanf ("%d", &tmp_coeff);
        if (tmp_coeff != 0) {
            (*size)++;
            p = (element *) realloc(p, (*size)*sizeof(element));
            if (p == NULL){
                printf ("Memory Allocation Error!\n");
                exit(1);
            }
            p[(*size)-1].coeff = tmp_coeff;
            p[(*size)-1].exp = i;
        }
    }
    return p;
}


void display (element *p, int *size)
{
    int i=0;
    if (p == NULL) {
        printf ("0\n");
    } else {
        for (i=0; i<(*size); i++) {
            if (i==0) {
                printf ("%d", p[i].coeff);
            } else {
                printf ("%d", abs(p[i].coeff));
            }
            if (p[i].exp != 1 && p[i].exp != 0) {
                printf("x^%d", p[i].exp);
            } else if (p[i].exp == 1) {
            printf ("x");
            }

            if (i != ((*size)-1)) {
                if (p[i+1].coeff < 0) {
                    printf (" - ");
                } else {
                    printf (" + ");
                }
            }
        }

        printf ("\n");
    }
}


element *add (element *p1, element *p2, element *p3, int *size1, int *size2, int *size3)
{
    int i = 0, j = 0, k = 0, tmp=0;
    if (p1 == NULL) {
        *size3 = *size2;
        //p3 = realloc(p3, (*size3)*sizeof(element));
        //p3 = p2;
        return p2;
    } else if (p2 == NULL) {
        *size3 = *size1;
        //p3 = realloc(p3, (*size3)*sizeof(element));
        //p3 = p1;
        return p1;
    } else {
        while (1) {
				
            if (i < (*size1) && j < (*size2)) {
				if (p1[i].exp > p2[j].exp) {
					p3 = (element *) realloc (p3, (k+1)*(sizeof(element)));
					if (p3 == NULL) {
						printf ("Memory allocation error.\n");
						exit(1);
					}
					p3[k++] = p1[i++];
					//(*size3)++;
				} else if (p1[i].exp < p2[j].exp) {
					p3 = (element *) realloc (p3, (k+1)*(sizeof(element)));
					if (p3 == NULL) {
						printf ("Memory allocation error.\n");
						exit(1);
					}
					p3[k++] = p2[j++];
					//(*size3)++;
				} else {
					tmp = p1[i].coeff + p2[j].coeff;
					if (tmp != 0) {
						p3 = (element *) realloc (p3, (k+1)*(sizeof(element)));
						if (p3 == NULL) {
							printf ("Memory allocation error.\n");
							exit(1);
						}
						p3[k].coeff = tmp;
						p3[k].exp = p1[i].exp;
						k++;
						//(*size3)++;
					}		
					i++;
					j++;	
				}
			}
            if (i==(*size1) && j==(*size2)) {
                break;
            }
            if (i==(*size1)) {
				p3 = (element *) realloc (p3, (k+1)*(sizeof(element)));
				if (p3 == NULL) {
					printf ("Memory allocation error.\n");
					exit(1);
				}
                p3[k++] = p2[j++];
                //(*size3)++;
                if (j==(*size2)) {
                    break;
                }
            }
            if (j==(*size2)) {
				p3 = (element *) realloc (p3, (k+1)*(sizeof(element)));
				if (p3 == NULL) {
					printf ("Memory allocation error.\n");
					exit(1);
				}
                p3[k++] = p1[i++];
                //(*size3)++;
                if (i==(*size1)) {
                    break;
                }
            }
		}
	}
	*size3 = k;

	return p3;
}
