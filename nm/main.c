/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include "objdump.h"
#include "nm.h"

int do_all( Elf64_Ehdr *elf, symbols_t *list)
{
    if (elf == NULL)
        return (1);
    list = get_symbols(elf, list);
    list = sort_symlist(list);
    print_every(list);
}

int main(int ac, char **av)
{
    Elf64_Ehdr *elf;
    symbols_t *list = NULL;

    if (ac == 1) {
        elf = get_elf("a.out");
        do_all(elf, list);
    }
    for (int i = 1; i != ac; i++) {
        elf = get_elf(av[i]);
        if (ac > 2 && elf != NULL)
            printf("\n%s:\n", av[i]);
        do_all(elf, list);
    }
}
