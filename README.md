# C23 Generic List

This repo contains a simple generic double-linked which is implemented in C23.

## API
Function-macros:
```C++
size_t list_count(const List(T) *lst);
ListElement(T) *list_append_p(List(T) *lst, const T *val);
ListElement(T) *list_append(List(T) *lst, T val);
ListElement(T) *list_prepend_p(List(T) *lst, const T *val);
ListElement(T) *list_prepend(List(T) *lst, T val);
void list_remove(List(T) *lst, ListElement(T) *el);
void list_clear(List(T) *lst);
```

Loop-macros:
```C++
list_foreach (List(T) *, el_name)
```

Important fields on structs:
```C++
struct ListElement(T) {
    T value
};
```

## Example

The following example can be executed by `make && ./main`:

```C++
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
```

