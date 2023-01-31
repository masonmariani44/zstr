/**
 * Mason Mariani
 * 
 * zstr is used to represent char arrays. Given a char array, a zstr will be built, representing the length of the char array and the allocated
 * size that it uses in the 8 bytes (2 ints) before the pointer to the zstr. Various operations can be performed on the zstrs; including appending two
 * zstrs together, retrieving the index of a zstr within another zstr, retrieving the number of times a zstr is used in another zstr, comparing two
 * zstrs similar to strcmp, printing a zstr, and creating a new zstr based on a substring.
*/

#ifndef _ZSTR_H
#define _ZSTR_H

typedef char* zstr;
typedef int zstr_code;

//zstr status codes
#define ZSTR_OK 0
#define ZSTR_ERROR 100
#define ZSTR_GREATER 1
#define ZSTR_LESS -1
#define ZSTR_EQUAL 0
extern zstr_code zstr_status;

/**
 * paramater - takes a pointer to a char array which will be used to create the corresponding zstr
 * 
 * returns - the corresponding zstr representing the char array. Returns NULL if there was an issue with allocation, and sets zstr_status to ZSTR_ERROR
 * 
 * Given the head of a char array, zstr_create will allocate space for a zstr, copy the char array's contents, store its length and allocated size 
 * two and one ints respecivley behind the head of the zstr pointer.
*/
zstr zstr_create(char* initial_data);

/**
 * paramater - takes a zstr to be deallocated
 * 
 * returns - void
 * 
 * Deallocates the space used by the given zstr
*/
void zstr_destroy(zstr to_destroy);

/**
 * paramaters - takes a pointer to a zstr as the base, and another zstr that will be appended
 * 
 * returns - void
 * 
 * Appends the contents of the second zstr to the base zstr; updating the pointer accordingly. 
*/
void zstr_append(zstr * base, zstr to_append);

/**
 * paramaters - takes a base zstr and a zstr that is being searched for in the base
 * 
 * returns - an int representing the starting index of the first found instance of to_search
 * 
 * Searches for the first instance of to_search in base and returns its starting index
*/
int zstr_index (zstr base, zstr to_search);

/**
 * paramaters- a base zstr and a zstr that will be searched for
 *
 * returns - an int representing the number of instances of to_search within base
 * 
 * Given two zstrs, will search base for the number of occurences of to_search
*/
int zstr_count(zstr base, zstr to_search);

/**
 * paramaters - two zstrs to be compared
 * 
 * returns - ZSTR_EQUAL (0) if equal, ZSTR_LESS (-1) if x < y and ZSTR_GREATER (1) if x > y
 * 
 * Performs a string comparison operation similar to strcmp; alphabetically lower strings are less than alphabetically higher strings.
*/
int zstr_compare(zstr x, zstr y);

/**
 * paramaters - a zstr to be printed
 * 
 * returns - void 
 * 
 * Prints the length, allocated space, and contents of a zstr
*/
void zstr_print_detailed(zstr data);

/**
 * paramaters - a bse zstr, a starting int and ending int
 * 
 * returns - a newly created zstr
 * 
 * Given a base zstr and a starting an ending index; creates and returns a new zstr based on the substring within the given index bounds
*/
zstr zstr_substring(zstr base, int begin, int end);

#endif