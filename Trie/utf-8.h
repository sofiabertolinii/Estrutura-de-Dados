// manipulação de caracteres UTF-8

#ifndef UTF8_H
#define UTF8_H

#include <stdint.h>

//decodifica um caractere UTF-8 para um codepoint Unicode (uint32_t)
//retorna quantos bytes foram lidos (varia de 1-4), -1 se for inválido
int utf8_decode(const unsigned char *s, uint32_t *codepoint);

//codifica um codepoint Unicode (uint32_t) para bytes UTF-8
//retorna quantos bytes foram escritos (varia de 1-4), -1 se for inválido
int utf8_encode(uint32_t codepoint, char *out);

//retorna o número de bytes até '\0' de uma string UTF-8
int utf8_len_bytes(const char *s);

//retorna o número de caracteres (codepoints) em uma string UTF-8
int utf8_len_chars(const char *s);

#endif