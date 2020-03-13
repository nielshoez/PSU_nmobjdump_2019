/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <inttypes.h>
#include <stdint.h>
#include <elf.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ar.h>

#define SLEN(a) 		(sizeof(a) / sizeof(*a))
#define ISHEXA(i) 		(i % 16)
#define UCHAR 			unsigned char
#define GETPAD(i)	((int)strlen(my_itoa(i)) > 4 ? (int)strlen(my_itoa(i)) : 4)
#define BFD_NO_FLAGS    0x00
#define HAS_RELOC       0x01
#define EXEC_P          0x02
#define HAS_DEBUG       0x08
#define HAS_SYMS        0x10
#define HAS_LOCALS      0x20
#define DYNAMIC         0x40
#define D_PAGED         0x100

static inline Elf64_Shdr *get_elf_sheader(Elf64_Ehdr *ehdr) {
	return (Elf64_Shdr *)((uint64_t)ehdr + ehdr->e_shoff);
}

static inline Elf64_Shdr *get_elf_section(Elf64_Ehdr *ehdr, int idx) {
	return &get_elf_sheader(ehdr)[idx];
}

static inline char *elf_str_table(Elf64_Ehdr *hdr) {
	if(hdr->e_shstrndx == SHN_UNDEF) 
        return NULL;
	return (char *)hdr + get_elf_section(hdr, hdr->e_shstrndx)->sh_offset;
}
 
static inline char *elf_lookup_string(Elf64_Ehdr *hdr, int offset) {
	char *strtab = elf_str_table(hdr);
	if(strtab == NULL) 
        return NULL;
	return strtab + offset;
}

typedef struct map
{
    int key;
    char *data;
} map;

void *get_elf(char *filename);
char *get_archi(int type);
unsigned int get_flags(Elf64_Ehdr *elf);
void print_flags(unsigned int flags);
void get_section(Elf64_Ehdr *elf);
bool is_print_section(const char *to_print, Elf64_Shdr header);
void print_tabs_section(unsigned int i);
char *my_itoa(int number);
#endif /* !OBJDUMP_H_ */
