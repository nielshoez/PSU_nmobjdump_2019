/*
** EPITECH PROJECT, 2020
** sort_list
** File description:
** sort_list
*/

#include "objdump.h"
#include "nm.h"

int my_strcoll(char *s1, char *s2, char type1, char type2)
{
    char *tmp1 = strdup(s1);
    char *tmp2 = strdup(s2);
    int j = 0;

    for (int i = 0; s1[i]; i++)
        if (isalpha(s1[i]))
            tmp1[j++] = tolower(s1[i]);
    tmp1[j] = '\0';
    j = 0;
    for (int i = 0; s2[i]; i++)
        if (isalpha(s2[i]))
            tmp2[j++] = tolower(s2[i]);
    tmp2[j] = '\0';
    j = strcoll(tmp1, tmp2);
    if (j == 0)
        j = tolower(type1) - tolower(type2);
    free(tmp1);
    free(tmp2);
    return (j);
}

void my_swap(char *tmp_name, uint8_t type, uint64_t addr, symbols_t *tmp)
{
    tmp_name = tmp->name;
    type = tmp->type;
    addr = tmp->addr;
    tmp->name = tmp->next->name;
    tmp->type = tmp->next->type;
    tmp->addr = tmp->next->addr;
    tmp->next->name = tmp_name;
    tmp->next->type = type;
    tmp->next->addr = addr;
}

symbols_t *sort_symlist(symbols_t *list)
{
    symbols_t *tmp = list;
    char *tmp_name;
    uint8_t type;
    uint64_t addr;

    if (!tmp->next)
        printf("LOPES\n");
    while (tmp->next) {
            if (my_strcoll(tmp->name, tmp->next->name,
                           tmp->type, tmp->next->type) > 0) {
                my_swap(tmp_name, type, addr, tmp);
                return (sort_symlist(list));
            }
            tmp = tmp->next;
        }
        return (list);
}
