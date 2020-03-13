/*
** EPITECH PROJECT, 2020
** get_struct
** File description:
** get_struct
*/

#include "nm.h"
#include "objdump.h"

void *get_elf(char *file)
{
    int fd = open(file, O_RDONLY);
    void *buf;
    struct stat s;
    Elf64_Ehdr *elf = NULL;

    if (fd !=  -1) {
        fstat(fd, &s);
        buf = mmap(NULL , s.st_size , PROT_READ , MAP_PRIVATE , fd, 0);
        if (buf !=  (void *)-1)
            elf = buf;
        else
            perror("mmap");
        close(fd);
        if (strncmp(elf->e_ident, ELFMAG, 4) != 0) {
            fprintf(stderr, "objdump: %s: file format not recognized\n", file);
            return NULL;
        }
    } else
        fprintf(stderr, "objdump: '%s': No such file\n", file);
    return (elf);
}

char *get_archi(int type)
{
    static const map archi[] = {{EM_NONE, "None"}, {EM_M32, "WE32100"},
                       {EM_SPARC, "Sparc"}, {EM_386, "Intel 80386"},
                       {EM_68K, "MC68000"}, {EM_88K, "MC88000"},
                       {EM_860, "Intel 80860"}, {EM_MIPS, "MIPS R3000"},
                       {EM_PARISC, "HPPA"}, {EM_SPARC32PLUS, "Sparc v8+"},
                       {EM_PPC, "PowerPC"}, {EM_PPC64, "PowerPC64"},
                       {EM_S390, "IBM S/390"}, {EM_ARM, "ARM"},
                       {EM_SH, "Renesas / SuperH SH"}, {EM_SPARCV9, "Sparc v9"},
                       {EM_IA_64, "Intel IA-64"}, {EM_X86_64, "i386:x86-64"}};
    for (int i = 0; i != SLEN(archi); i++) {
        if (archi[i].key == type)
            return (archi[i].data);
    }
    return ("i386:x86-64");
}

unsigned int get_syms(Elf64_Ehdr *elf)
{
    Elf64_Shdr *slf = (Elf64_Shdr *) ((char *)elf + elf->e_shoff);

    for (int i = 0; i < elf->e_shnum; i++) {
        if (slf[i].sh_type == SHT_SYMTAB || slf[i].sh_type == SHT_DYNSYM) {
            return (HAS_SYMS);
        }
    }
    return (0);
}

unsigned int get_flags(Elf64_Ehdr *elf)
{
    unsigned int flags = BFD_NO_FLAGS;

    switch (elf->e_type) {
    case ET_EXEC:
        flags += (EXEC_P + D_PAGED);
        break;
    case ET_DYN:
        flags += (DYNAMIC + D_PAGED);
        break;
    case ET_REL:
        flags += (HAS_RELOC);
        break;
    }
    flags += get_syms(elf);
    return (flags);
}

void print_flags(unsigned int flags)
{
    static const map flags_map[] = {{BFD_NO_FLAGS, "BFD_NO_FLAGS"},
       {HAS_RELOC, "HAS_RELOC"}, {EXEC_P, "EXEC_P"}, {HAS_DEBUG, "HAS_DEBUG"},
       {HAS_SYMS, "HAS_SYMS"}, {HAS_LOCALS, "HAS_LOCALS"}, {DYNAMIC, "DYNAMIC"},
       {D_PAGED, "D_PAGED"}};

    for (int i = 0; i != SLEN(flags_map); i = -(~i)) {
        if (flags & flags_map[i].key) {
            printf("%s", flags_map[i].data);
            flags -= flags_map[i].key;
            if (flags != BFD_NO_FLAGS)
                printf(", ");
            else
                printf("\n");
        }
    }
}
