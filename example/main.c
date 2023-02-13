#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    trie_t t = trie_create();
    trie_add(&t, "abc", "abc");
    trie_add(&t, "ab", "ab");
    trie_add(&t, "abcd", "abcd");
    trie_add(&t, "bsa", "bsa");
    trie_add(&t, "acd", "acd");
    trie_add(&t, "acdsadfdasf", "acdsadfdasf");
    trie_add(&t, "acdsad", "acdsad");
    size_t len = 0;
    char **strs = trie_get_keys(&t, "a", &len);
    for (int i = 0; i < len; i++)
    {
        printf("- : %s\n", strs[i]);
        free(strs[i]);
    }
    free(strs);
    printf("abc = %s\n", (char *)trie_get(&t, "abc"));
    printf("ab = %s\n", (char *)trie_get(&t, "ab"));
    printf("abcd = %s\n", (char *)trie_get(&t, "abcd"));
    printf("bsa = %s\n", (char *)trie_get(&t, "bsa"));
    printf("acd = %s\n", (char *)trie_get(&t, "acd"));
    printf("acdsadfdasf = %s\n", (char *)trie_get(&t, "acdsadfdasf"));
    printf("acdsad = %s\n", (char *)trie_get(&t, "acdsad"));
    trie_remove(&t, "acdsad");
    printf("acdsad = %s\n", (char *)trie_get(&t, "acdsad"));
    printf("acdsa = %s\n", (char *)trie_get(&t, "acdsa"));
    trie_free(&t);
    return 0;
}
