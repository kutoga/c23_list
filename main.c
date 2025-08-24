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
    list_append(&l, 10);
    ListElement(int) *el = list_prepend(&l, -12);
    printf("el->value=%d\n", el->value);
    print_int_list(&l);
    list_remove(&l, el);
    print_int_list(&l);
    list_clear(&l);
}