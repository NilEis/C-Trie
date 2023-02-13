#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

typedef struct trie_node
{
    struct trie_node *children[TRIE_NUM_CHILDREN];
    void *value;
} trie_node_t;

static void add_to_trie(trie_t *t, char *str, void *value);
static void free_trie_node_t(trie_node_t *n);
static void get_keys_rec(trie_node_t *n, char *prefix, size_t prefix_len, char ***keys, size_t *keys_len);
static uint_fast8_t get_num_children(trie_node_t *n);

trie_t trie_create(void)
{
    return (trie_t){.num_members = 0, .root = calloc(1, sizeof(trie_node_t))};
}

void trie_add(trie_t *t, char *str, void *value)
{
    char *tmp_str = (char *)calloc(strlen(str) + 1, sizeof(char));
    strcpy(tmp_str, str);
    add_to_trie(t, tmp_str, value);
    free(tmp_str);
}

static void add_to_trie(trie_t *t, char *str, void *value)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
    i = 0;
    trie_node_t *last = t->root;
    while (str[i] != '\0')
    {
        trie_node_t *current = last->children[str[i] - 'a'];
        if (current == NULL)
        {
            last->children[str[i] - 'a'] = calloc(1, sizeof(trie_node_t));
        }
        last = last->children[str[i] - 'a'];
        i++;
    }
    last->value = value;
}

char **trie_get_keys(trie_t *t, char *str, size_t *len)
{
    char **res = NULL;
    get_keys_rec(t->root, "", 0, &res, len);
    return res;
}

static void get_keys_rec(trie_node_t *n, char *prefix, size_t prefix_len, char ***keys, size_t *keys_len)
{
    if (n->value != NULL)
    {
        (*keys_len)++;
        if (*keys == NULL)
        {
            *keys = (char **)calloc(*keys_len, sizeof(char **));
        }
        else
        {
            *keys = (char **)realloc(*keys, (*keys_len) * sizeof(char **));
        }
        if (*keys == NULL)
        {
            return;
        }
        (*keys)[(*keys_len) - 1] = (char *)calloc(prefix_len + 1, sizeof(char));
        strcpy((*keys)[(*keys_len) - 1], prefix);
    }
    if (get_num_children(n) == 0)
    {
        return;
    }
    for (int i = 0; i < TRIE_NUM_CHILDREN; i++)
    {
        if (n->children[i] != NULL)
        {
            char *tmp = (char *)calloc(prefix_len + 2, sizeof(char));
            strcpy(tmp, prefix);
            tmp[prefix_len] = 'a' + i;
            get_keys_rec(n->children[i], tmp, prefix_len + 1, keys, keys_len);
            free(tmp);
        }
    }
}

void *trie_get(trie_t *t, char *str)
{
    int i = 0;
    trie_node_t *current = t->root;
    while (str[i] != '\0')
    {
        if (current->children[tolower(str[i]) - 'a'] == NULL)
        {
            return NULL;
        }
        current = current->children[tolower(str[i]) - 'a'];
        i++;
    }
    return current->value;
}

void trie_remove(trie_t *t, char *str)
{
    int i = 0;
    trie_node_t *last = NULL;
    trie_node_t *current = t->root;
    while (str[i] != '\0')
    {
        if (current->children[tolower(str[i]) - 'a'] == NULL)
        {
            return;
        }
        last = current;
        current = current->children[tolower(str[i]) - 'a'];
        i++;
    }
    current->value = NULL;
    if (get_num_children(current) == 0)
    {
        free(current);
        last->children[tolower(str[i - 1]) - 'a'] = NULL;
    }
}

void trie_free(trie_t *t)
{
    if (t->root == NULL)
    {
        return;
    }
    free_trie_node_t(t->root);
}

static void free_trie_node_t(trie_node_t *n)
{
    uint_fast8_t num_children = get_num_children(n);
    if (num_children == 0)
    {
        free(n);
        return;
    }
    for (int i = 0; i < TRIE_NUM_CHILDREN && num_children != 0; i++)
    {
        if (n->children[i] != NULL)
        {
            free_trie_node_t(n->children[i]);
            num_children--;
        }
    }
    free(n);
}

static uint_fast8_t get_num_children(trie_node_t *n)
{
    uint_fast8_t res = 0;
    for (int i = 0; i < TRIE_NUM_CHILDREN; i++)
    {
        if (n->children[i] != NULL)
        {
            res++;
        }
    }
    return res;
}