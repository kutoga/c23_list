#include "list.h"
#include <stdlib.h>
#include <string.h>

static inline struct t_list_element *_list_alloc(struct t_list_type_info ti)
{
    return aligned_alloc(ti.lst_el_alignment, ti.lst_el_size);
}

struct t_list_element *_list_append(struct t_list *lst, const void *val, struct t_list_type_info ti)
{
    struct t_list_element *el = _list_alloc(ti);
    memcpy((char *)el + ti.el_offset, val, ti.el_size);
    el->prev = lst->last;
    el->next = nullptr;
    if (lst->count == 0) {
        lst->first = el;
    } else {
        lst->last->next = el;
    }
    lst->last = el;
    ++lst->count;
    return el;
}

struct t_list_element *_list_prepend(struct t_list *lst, const void *val, struct t_list_type_info ti)
{
    struct t_list_element *el = _list_alloc(ti);
    memcpy((char *)el + ti.el_offset, val, ti.el_size);
    el->prev = nullptr;
    el->next = lst->first;
    if (lst->count == 0) {
        lst->last = el;
    } else {
        lst->first->prev = el;
    }
    lst->first = el;
    ++lst->count;
    return el;
}

void _list_remove(struct t_list *lst, struct t_list_element *el)
{
    if (el->next != nullptr) {
        el->next->prev = el->prev;
    } else {
        lst->last = el->prev;
    }
    if (el->prev != nullptr) {
        el->prev->next = el->next;
    } else {
        lst->first = el->next;
    }
    free(el);
    --lst->count;
}

void _list_clear(struct t_list *lst)
{
    while (lst->first != nullptr) {
        struct t_list_element *el = lst->first;
        lst->first = el->next;
        free(el);
    }
    lst->count = 0;
}
