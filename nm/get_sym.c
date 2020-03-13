/*
** EPITECH PROJECT, 2020
** get_syms
** File description:
** get_sym
*/

#include "nm.h"
#include "objdump.h"

char true_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char c = print_type(sym, shdr);

    if (c == '?')
        c = 't';
    return (c);
}

symbols_t *print_address(Elf64_Sym *sym_list, header_t headers,
                         Elf64_Ehdr *elf, symbols_t *list)
{
    Elf64_Shdr *strtab = &headers.head[headers.header.sh_link];

    for (uint32_t i = 0; i < headers.header.sh_size / headers.header.sh_entsize;
         i = -(~i)) {
        if (strcmp((char *)elf + strtab->sh_offset + sym_list[i].st_name, "")
            && sym_list[i].st_info != STT_FILE
            && sym_list[i].st_info != STT_SECTION) {
            if (list == NULL) {
                list = init_list(list, sym_list[i].st_value,
                                 true_type(sym_list[i], headers.head),
                (char *)elf + strtab->sh_offset + sym_list[i].st_name);
            } else
                add_list(list, sym_list[i].st_value,
                         true_type(sym_list[i], headers.head),
                         (char *)elf + strtab->sh_offset + sym_list[i].st_name);
        }
    }
    return (list);
}

void print_every(symbols_t *list)
{
    symbols_t *current = list;
    
    if (current == NULL)
        printf("pasdevhace\n");
    while (current != NULL) {
        if (current->type != 0 && current->name != NULL)
            if (current->addr == 0)
                printf("%016c %c %s\n", ' ', current->type, current->name);
            else
                printf("%016x %c %s\n", current->addr,
                       current->type, current->name);
        current = current->next;
    }
}

symbols_t *get_symbols(Elf64_Ehdr *elf, symbols_t *list)
{
    Elf64_Shdr *header = get_elf_sheader(elf);
    Elf64_Sym *sym_list;
    char *symmaddr;
    char *str = elf_str_table(elf);
    header_t headers;

    for (int i = 0; i < elf->e_shnum; i++) {
        if (header[i].sh_type == SHT_SYMTAB) {
            sym_list = (Elf64_Sym *)((char *)elf + header[i].sh_offset);
            headers.head = header;
            headers.header = header[i];
        list = print_address(sym_list, headers, elf, list);
        break;
        }
    }
    return (list);
}
