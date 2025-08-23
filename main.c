#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <immintrin.h>

void print_int_lst(const List(int) *l)
{
    list_foreach(l, el) {
        printf("XX %d\n", el->value);
    }
}

int main()
{
    List(int) a = {};
    List(int) b = {};
    List(double) d = {};
    a = b;

    list_append(&a, 12);
    ListElement(int) *x = list_prepend(&a, 9);

    ListElement(double) *y = list_append(&d, 12.9);

    printf("## 1 ##\n");
    list_foreach(&a, el) {
        printf("val=%d\n", el->value);
    }

    list_remove(&a, x);

    printf("\n\n## 2 ##\n");
    list_foreach(&a, el) {
        printf("val=%d\n", el->value);
    }



    printf("%lu\n", list_count(&a));
}
