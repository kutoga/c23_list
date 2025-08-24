#ifndef __COLLECTIONS_LIST__
#define __COLLECTIONS_LIST__

#include <stddef.h>


// internal macros
#define _lst_get(x)                                                         (&(x)->v)
#define _lst_type(x)                                                        typeof(*(x)->type)
#define _lst_offsetof(st, m)                                                ((size_t)&(((st *)nullptr)->m))
#define _lst_to_lvalue(T, x)                                                ((T[]){x}[0])

struct t_list_type_info {
    size_t lst_el_size;
    size_t lst_el_alignment;
    size_t el_size;
    size_t el_offset;
};

#define _lst_type_info(lst)                                                 \
((struct t_list_type_info) {                                                \
    .lst_el_size      = sizeof(*(lst)->el_type),                            \
    .lst_el_alignment = alignof(*(lst)->el_type),                           \
    .el_size           = sizeof(*(lst)->type),                              \
    .el_offset         = _lst_offsetof(typeof(*(lst)->el_type), value)      \
})

// list element type
struct t_list_element {
    struct t_list_element *next;
    struct t_list_element *prev;
};

#define ListElement(T)                                                      \
struct t_typed_list_element_ ## T {                                         \
    struct t_list_element el;                                               \
    T value;                                                                \
}

// list type
struct t_list {
    size_t count;
    struct t_list_element *first;
    struct t_list_element *last;
};

#define List(T)                                                             \
union t_typed_list_ ## T {                                                  \
    struct t_list v;                                                        \
    ListElement(T) *el_type;                                                \
    T *type;                                                                \
}

// functions used by the API macros
struct t_list_element *_list_append(struct t_list *lst, const void *val, struct t_list_type_info ti);
struct t_list_element *_list_prepend(struct t_list *lst, const void *val, struct t_list_type_info ti);
void _list_remove(struct t_list *lst, struct t_list_element *el);
void _list_clear(struct t_list *lst);

// API macros
#define list_count(lst)                                                     (_lst_get(lst)->count)
#define list_append_p(lst, val)                                             ((typeof((lst)->el_type))_list_append(_lst_get(lst), (val), _lst_type_info(lst)))
#define list_append(lst, val)                                               list_append_p((lst), &_lst_to_lvalue(_lst_type(lst), (val)))
#define list_prepend_p(lst, val)                                            ((typeof((lst)->el_type))_list_prepend(_lst_get(lst), (val), _lst_type_info(lst)))
#define list_prepend(lst, val)                                              list_prepend_p((lst), &_lst_to_lvalue(_lst_type(lst), (val)))
#define list_remove(lst, lst_el)                                            _list_remove(_lst_get(lst), &(lst_el)->el)
#define list_foreach(lst, var_el)                                           for (typeof_unqual((lst)->el_type) var_el = (void *)_lst_get(lst)->first; var_el != nullptr; var_el = (typeof(var_el))var_el->el.next)
#define list_clear(lst)                                                     _list_clear(_lst_get(lst))

#endif /* __COLLECTIONS_LIST__ */
