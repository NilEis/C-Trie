#ifndef TRIE_H
#define TRIE_H
#include <stdint.h>
#include <stddef.h>

#ifndef TRIE_NUM_CHILDREN
#define TRIE_NUM_CHILDREN 26
#endif

struct trie_node;

typedef struct
{
    struct trie_node *root;
    unsigned int num_members;
    unsigned int _num_children;
} trie_t;

/**
 * @brief Returns an initialised instance of a trie 
 * 
 * @return trie_t 
 */
trie_t trie_create(void);

/**
 * @brief Sets the value for node of the given str
 * 
 * @param t a pointer to the Trie
 * @param str a Pointer to the '\0' terminated string; the key
 * @param value the value, casted to a void pointer
 */
void trie_add(trie_t *t, char *str, void*value);

/**
 * @brief Returns all the possible paths from the node of the given string
 * 
 * @param t a pointer to the trie instance
 * @param str a Pointer to the '\0' terminated string; the key
 * @param len a pointer to a variable of type size_t that will be set to the amount of the paths
 * @return char** An array of strings which are the keys for all set nodes below the given node (can include the given node). HAS TO BE FREED BY THE CALLER
 */
char **trie_get_keys(trie_t *t, char *str, size_t*len);
/**
 * @brief returns the value of the given node
 * 
 * @param t a trie instance
 * @param str a Pointer to the '\0' terminated string; the key
 * @return void* the saved value or NULL if the given node does not have data or does not exist
 */
void *trie_get(trie_t *t, char *str);

/**
 * @brief removes an entry
 * 
 * @param t a trie instance
 * @param str the path to the node as a '\0' terminated string
 */
void trie_remove(trie_t *t, char *str);

/**
 * @brief free all allocated memory of the trie
 * 
 * @param t the trie
 */
void trie_free(trie_t *t);

#endif // TRIE_H
