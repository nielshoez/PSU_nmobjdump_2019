/*
** EPITECH PROJECT, 2020
** fill_list.c
** File description:
** fill_list
*/

#include "objdump.h"
#include "nm.h"

symbols_t *init_list(symbols_t *head, uint64_t addr, uint8_t c, char *n)
{
    head = calloc(1, sizeof(symbols_t));

    if (head == NULL)
        return (NULL);
    head->addr = addr;
    head->type = c;
    head->name = n;
    head->next = NULL;
    return (head);
}

void add_list(symbols_t *head, uint64_t addr, uint8_t c, char *n)
{
    symbols_t *current = head;

    while (current != NULL && current->next != NULL)
        current = current->next;
    current->next = calloc(1, sizeof(symbols_t));
    if (current->next == NULL)
        return;
    current->next->addr = addr;
    current->next->type = c;
    current->next->name = n;
    current->next->next = NULL;
}

void print_list(symbols_t *head)
{
    symbols_t *current = head;

    if (current == NULL)
        printf("repasdechance\n");
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}
