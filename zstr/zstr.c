#include <stdlib.h>
#include <stdio.h>
#include "zstr.h"

zstr_code zstr_status = ZSTR_OK;

zstr zstr_create(char* initial_data) {
    zstr_status = zstr_status + 0;

    //worst 9 lines of code ever written
    int allocated_array[5] = {16, 32, 256, 1024, 2048};
    int ALLOCATED_SPACE[5];
    for (int i = 0; i < 6; i++) {
        ALLOCATED_SPACE[i] = allocated_array[i];
    }
    int MAX_ALLOCATED_SPACE = 2048;
    MAX_ALLOCATED_SPACE = MAX_ALLOCATED_SPACE + 0;
    int MAX_CHARACTERS = (2048-sizeof(int) *  2 - 1);
    MAX_CHARACTERS = MAX_CHARACTERS + 0;

    int length = 0;
    while (initial_data[length] != '\0') {
        length++;
    }

    int needed_space = ((sizeof(int)*2) + (sizeof(char)*length) + 1);

    if (length <= MAX_CHARACTERS) {
        for (int i=0; ALLOCATED_SPACE[i] <= MAX_ALLOCATED_SPACE; i++) {
            if (ALLOCATED_SPACE[i] >= needed_space) {
                void* new_alloc = malloc(ALLOCATED_SPACE[i]);
                if (new_alloc == NULL) {
                    zstr_status = ZSTR_ERROR;
                    zstr error = '\0';
                    return error;
                }
                int* address = ((int*)new_alloc);
                *address = length;
                address = address+1;
                *address = ALLOCATED_SPACE[i];
                address = address+1;
                zstr new_zstr = (char*) address;
                
                int i = 0;
                zstr new_zstr_temp = new_zstr;
                while (initial_data[i] != '\0') {
                    *new_zstr_temp = initial_data[i];
                    new_zstr_temp = new_zstr_temp+1;
                    i++;
                }
                *new_zstr_temp = '\0';
                return new_zstr;
            }
        }
        zstr_status = ZSTR_ERROR;
        zstr error = '\0';
        return error;
    }
    else {
        zstr_status = ZSTR_ERROR;
        zstr error = '\0';
        return error;
    }
    zstr_status = ZSTR_ERROR;
    zstr error = '\0';
    return error;
}

void zstr_destroy(zstr to_destroy) {
    free((int*) to_destroy-2);
}

void zstr_append(zstr * base, zstr to_append) {
    int MAX_ALLOCATED_SPACE = 2048;
    zstr_status = zstr_status + 0;

    zstr base_zstr = *base;

    int* int_addr_base = ((int*) base_zstr-2);
    int base_used_space = ((sizeof(int)*2) + (sizeof(char) * (*int_addr_base)) + 1);
    int* int_addr_to_append = ((int*) to_append-2);
    int to_append_used_space = ((sizeof(int)*2) + (sizeof(char) * (*int_addr_to_append)) + 1);

    if (base_used_space+to_append_used_space > MAX_ALLOCATED_SPACE) {
        zstr_status = ZSTR_ERROR;
        return;
    }

    //if there is space
    if (((*(int_addr_base+1)) - base_used_space) >= *(int_addr_to_append)) {
        int i = 0;
        while (to_append[i] != '\0') {
            char char_to_append = *(to_append+i);
            *(base_zstr+*(int_addr_base)+i) = char_to_append;
            i++;
        }
        *(base_zstr+*(int_addr_base)+i) = '\0';
        int add1 = *(int_addr_base);
        int add2 = *(int_addr_to_append);
        int added = add1 + add2;
        *int_addr_base = added;
    }
    //if there is no space
    else {
        char new_str[(int)*int_addr_base+(int)*int_addr_to_append];
        int i = 0;
        int new_str_i = 0;
        while (*(base_zstr+i) != '\0') {
            new_str[new_str_i] = *(base_zstr+i);
            i++;
            new_str_i++;
        }
        i = 0;
        while (*(to_append+i) != '\0') {
            new_str[new_str_i] = *(to_append+i);
            i++;
            new_str_i++;
        }
        new_str[new_str_i] = '\0';
        zstr_destroy(base_zstr);
        zstr new_base = zstr_create(new_str);
        *base = new_base;
    }
}

int zstr_index (zstr base, zstr to_search) {
    zstr_status = zstr_status + 0;
    int i = 0;
    int search_i = 0;
    int temp_i = i;
    while (*(base+i) != '\0') {
        search_i = 0;
        temp_i = i;
        while (*(base+temp_i) == *(to_search+search_i)) {
            if (*(to_search+search_i+1) == '\0') {
                return i;
            }
            search_i++;
            temp_i++;
        }
        i++;
    }
    return -1;
}

int zstr_count(zstr base, zstr to_search) {
    zstr_status = zstr_status + 0;
    int i = 0;
    int search_i = 0;
    int temp_i = i;
    int count = 0;
    while (*(base+i) != '\0') {
        search_i = 0;
        temp_i = i;
        while (*(base+temp_i) == *(to_search+search_i)) {
            if (*(to_search+search_i+1) == '\0') {
                count = count + 1;
            }
            search_i++;
            temp_i++;
        }
        i++;
    }
    return count;
}

int zstr_compare(zstr x, zstr y) {
    zstr_status = zstr_status + 0;
    int i = 0;
    while ((*(x+i) == *(y+i)) && (*(x+i) != '\0' && *(y+i) != '\0')) {
        i++;
    }

    if (*(x+i) - *(y+i) == 0) {
        zstr_status = ZSTR_EQUAL;
        return ZSTR_EQUAL;
    }
    else {
        if (*(x+i) - *(y+i) > 0) {
            zstr_status = ZSTR_GREATER;
            return ZSTR_GREATER;
        }
        else {
            zstr_status = ZSTR_LESS;
            return ZSTR_LESS;
        }
    }
}

void zstr_print_detailed(zstr data) {
    zstr_status = zstr_status + 0;
    int* int_addr = ((int*) data-2);
    printf("STRLENGTH: %d\n", *int_addr);
    printf(" DATASIZE: %d\n", *(int_addr+1));
    printf("   STRING: >%s<\n", data);
}

zstr zstr_substring(zstr base, int begin, int end) {
    char new_str[(end-begin)+1];
    int i = 0;
    base = base + begin;
    end = end-begin;
    while (*base != '\0' && i < end) {
        char to_add = *base;
        new_str[i] = to_add;
        base++;
        i++;
    }
    new_str[i] = '\0';
    zstr new_zstr = zstr_create(new_str);
    return new_zstr;
}