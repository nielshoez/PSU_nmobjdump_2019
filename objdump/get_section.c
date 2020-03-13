/*
** EPITECH PROJECT, 2020
** get_section
** File description:
** get_section
*/

#include "objdump.h"
#include "nm.h"

bool get_tab(uint32_t i)
{
    while (ISHEXA(i)) {
        printf("  ");
        i = -(~i);
        if (!(i % 4))
            printf(" ");
        if (!(ISHEXA(i)))
            printf(" ");
    }
}

void printable_num(Elf64_Ehdr *elf, Elf64_Shdr header, uint32_t i)
{
    size_t size = header.sh_size;
    size_t addr = header.sh_addr;

    while (i < size) {
        printf("%02x", (UCHAR) (((char *) elf) + header.sh_offset)[i]);
        i = -(~i);
        if (!(ISHEXA(i))) {
            printf("  ");
            return ;
        }
        if (!(i % 4))
            printf(" ");
    }
    if (i >= size && ISHEXA(i))
        get_tab(i);
}

void get_info(Elf64_Ehdr *elf, Elf64_Shdr header)
{
    size_t size = header.sh_size;
    size_t addr = header.sh_addr;
    char chara;
    uint32_t i = 0;

    while (i < size) {
        if (!(ISHEXA(i))) {
            printf(" %0*x ", GETPAD(size), addr);
            printable_num(elf, header, i);
            addr += 16;
        }
        chara = (UCHAR) (((char *) elf) + header.sh_offset)[i];
        (isprint(chara)) ? printf("%c", chara) : printf(".");
        i = -(~i);
        if (!(ISHEXA(i)))
            printf("\n");
    }
    if (i >= header.sh_size && ISHEXA(i))
        print_tabs_section(i);
}

void get_section(Elf64_Ehdr *elf)
{
    Elf64_Shdr *header = get_elf_sheader(elf);
    Elf64_Shdr *section = get_elf_section(elf, elf->e_shstrndx);
    char *str = elf_str_table(elf);

    for (int i = 1; i < elf->e_shnum; i++) {
        if (is_print_section(str + header[i].sh_name, header[i])) {
            printf("Contents of section %s:\n", str + header[i].sh_name);
            get_info(elf, header[i]);
        }
    }
}
