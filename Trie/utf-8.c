//implementação da manipulação dos caracteres UTF-8

#include "utf-8.h"

//decodifica um caractere UTF-8 para número Unicode (codepoint)
//retorna bytes lidos 
int utf8_decode(const unsigned char *s, uint32_t *codepoint) {
    // 1 byte (ASCII simples)
    if (s[0] < 0x80) {
        *codepoint = s[0];
        return 1;
    }

    // 2 bytes
    else if ((s[0] & 0xE0) == 0xC0) {
        *codepoint = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
        return 2;
    }

    else if ((s[0] & 0xF0) == 0xE0) {
        *codepoint = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
        return 3;
    }
    // 4 bytes 
    else if ((s[0] & 0xF8) == 0xF0) {
        *codepoint = ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
        return 4;
    }
    // sequência inválida
    return -1;
}

//codifica um número Unicode (codepoint) para caractere UTF-8
int utf8_encode(uint32_t codepoint, char *out) {
    // 1 byte (ASCII)
    if (codepoint <= 0x7F) {
        out[0] = codepoint;
        out[1] = '\0';
        return 1;
    }

    // 2 bytes: 110xxxxx 10xxxxxx (para U+0080 a U+07FF)
    else if (codepoint <= 0x7FF) {
        out[0] = 0xC0 | (codepoint >> 6);
        out[1] = 0x80 | (codepoint & 0x3F);
        out[2] = '\0';
        return 2;
    }

    // 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx (para U+0800 a U+FFFF)
    else if (codepoint <= 0xFFFF) {
        out[0] = 0xE0 | (codepoint >> 12);
        out[1] = 0x80 | ((codepoint >> 6) & 0x3F);
        out[2] = 0x80 | (codepoint & 0x3F);
        out[3] = '\0';
        return 3;
    }

    // 4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx (para U+10000 a U+10FFFF)
    else if (codepoint <= 0x10FFFF) {
        out[0] = 0xF0 | (codepoint >> 18);
        out[1] = 0x80 | ((codepoint >> 12) & 0x3F);
        out[2] = 0x80 | ((codepoint >> 6) & 0x3F);
        out[3] = 0x80 | (codepoint & 0x3F);
        out[4] = '\0';
        return 4;
    }
    // inválido
    return -1;
}

//bytes totais da string
int utf8_len_bytes(const char *s) {
    int len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

//caracteres totais da string
int utf8_len_chars(const char *s) {
    int count = 0;
    const unsigned char *p = (const unsigned char *)s;
    uint32_t cp;  // codepoint temporário
    int n;        // número de bytes lidos

    while (*p) {
        n = utf8_decode(p, &cp);
        if (n < 0)
            return -1; // erro de decodificação
        p += n;
        count++;
    }
    return count;
}
