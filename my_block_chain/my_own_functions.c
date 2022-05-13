//
// Created by Leticia Mejia/Marcel Ghisi.
//

#include "functions_structures.h"

//////////// my atoi
int my_atoi(char* str) {
    int sign = 1;
    int i = 0;
    int ret = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        ret = (ret * 10) + (str[i] - '0');
        i++;
    }
    return ret * sign;
}

////////////// my itoa
char *my_itoa(int n, char *dest, int len) {
    int i = 0;

    if (n < 0) {
        dest[i++] = '-';
    }
    while (n > 0 && len-- > 0) {
        dest[i++] = n % 10 + '0';
        n /= 10;
    }
    dest[i] = '\0';
    my_strrev(dest);
    return 0;
}

////////////////// my memset
void my_memset(char *s, int c, int size) {
    int i = 0;

    while (size--) {
        s[i++] = c;
    }
}

////////////////// my putnbr
void my_putnbr(int nbr) {
    char ret;

    if (nbr < 0) {
        write(1, "-", 1);
        nbr *= -1;
    }
    if (nbr >= 10) {
        my_putnbr(nbr / 10);
    }
    ret = nbr % 10 + '0';
    write(1, &ret, 1);
}

///////////////// my string compare
int my_strcmp(char *s1, char *s2) {
    int i = 0;

    while (s1[i] && s2[i]) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

///////////////// my string copy
void my_strcpy(char *dest, char *src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

//////////////// my string duplicate
char* my_strdup(char* str) {
    char* new;
    int i;

    new = (char*)malloc(my_strlen(str) + 1);
    for (i = 0; str[i] != '\0'; i++) {
        new[i] = str[i];
    }
    new[i] = '\0';
    return new;
}

/////////////// my string len
int my_strlen(char* str) {
    int i;

    for (i = 0; str[i] != '\0'; i++);
    return  i;
}

////////////// my string compare
int my_strncmp(char* s1, char* s2, int n) {
    int i = 0;

    while (--n && s1[i] && s2[i]) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

///////////////////
char* my_strnstr(char* big, char* little, int n) {
    int i;
    for (i = 0; big[i] && little[i] && n; i++) {
        if (big[i] != little[i]) {
            return NULL;
        }
        n--;
    }
    return big[i] == little[i] ? big : NULL;
}

/////////////////
void my_strrev(char *str) {
    int i = 0;
    int j = my_strlen(str) - 1;
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
