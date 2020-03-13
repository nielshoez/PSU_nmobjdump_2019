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
            fprintf(stderr, "nm: %s: file format not recognized\n", file);
            return NULL;
        }
    } else
        fprintf(stderr, "nm: '%s': No such file\n", file);
    return (elf);
}
