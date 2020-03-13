/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include "objdump.h"
#include "nm.h"

char *my_itoa(int number)
{
    int lenght = 0;
    char *buffer;

    for (int temp = number; temp > 0; temp = temp / 10)
        lenght++;
    buffer = malloc(lenght + 1);
    buffer = memset(buffer, '\0', lenght + 1);
    while (lenght--) {
        buffer[lenght] = number % 10  + '0';
        number = number / 10;
    }
    return (buffer);
}

bool is_print_section(const char *to_print, Elf64_Shdr header)
{
    char section[5][20] = {".bss", ".shstrtab", ".symtab", ".strtab", ".rela"};

    if (!strcmp(to_print, ".rela.dyn") || !strcmp(to_print, ".rela.plt"))
        return (true);
    for (int i = 0; i < SLEN(section); i++) {
        if (header.sh_size <= 0 ||
            !strncmp(section[i], to_print, strlen(section[i])))
            return (false);
    }
    return (true);
}

void print_tabs_section(unsigned int i)
{
    while (ISHEXA(i)) {
        printf(" ");
        i = -(~i);
    }
    printf("\n");
}

int print_all(Elf64_Ehdr *elf, char *filename)
{
    if (elf == NULL)
        return (1);
    unsigned int flags = get_flags(elf);
    printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: %s, flags 0x%08x:\n", get_archi(elf->e_machine),
           flags);
    print_flags(flags);
    printf("start address 0x");
    printf("%016" PRIxPTR "\n\n", (uintptr_t)elf->e_entry);
    get_section(elf);
    return (0);
}

int main(int ac, char **av)
{
    Elf64_Ehdr *elf;

    for (int i = 1; i != ac; i++) {
        elf = get_elf(av[i]);
        print_all(elf, av[i]);
    }
}
