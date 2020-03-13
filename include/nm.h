/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_


#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gelf.h>

typedef struct symbols_s
{
    uint64_t addr;
    uint8_t type;
    char *name;
    struct symbols_s *next;
} symbols_t;

typedef struct header_s
{
    Elf64_Shdr *head;
    Elf64_Shdr header;
} header_t;

symbols_t *get_symbols(Elf64_Ehdr *elf, symbols_t *list);

void print_list(symbols_t *head);
void add_list(symbols_t *head, uint64_t addr, uint8_t c, char *n);
symbols_t *init_list(symbols_t *head, uint64_t addr, uint8_t c, char *n);
symbols_t *sort_symlist(symbols_t *list);
void print_every(symbols_t *list);




static inline char print_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char  c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
    {
        c = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'w';
    }
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
    {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    }
    else if (sym.st_shndx == SHN_UNDEF)
      c = 'U';
    else if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else
        c = '?';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}
#endif /* !NM_H_ */
