#include "list.h"
#include <stdio.h>

void print_int_list(const List(int) *l)
{
    printf("\nList %p has %lu elements:\n", l, list_count(l));
    list_foreach(l, el) {
        printf("- %d\n", el->value);
    }
    printf("\n");
}

int main()
{
    List(int) l = {};
    ListElement(int) *l0 = list_append(&l, 10);
    ListElement(int) *l1 = list_prepend(&l, -12);
    printf("l0->value=%d\n", l0->value);
    printf("l1->value=%d\n", l1->value);
    print_int_list(&l);
    list_remove(&l, l0);
    print_int_list(&l);
    list_clear(&l);
}
