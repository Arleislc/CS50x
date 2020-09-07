// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

//declara um interio sem sinal
unsigned int dictionary_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *list = table[hash(word)];
    
    for(node *n = list; n != NULL; n = n->next)
    {
        if(strcasecmp(n->word,word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    //processamento de carga do dicionário

    //define uma variável word que guardará a palavra e passa o comprimento máximo + 1 pois
    //já conhecemos tal comprimento e o +1 é necessário para caber o \0
    char word[LENGTH+1];

    //faz os scan do arquivo e colcoa a palavra na variável word, caso termine o arquivo a função retorna um EOF (end of file)
    //e isso faz o while parar
    while(fscanf(file, "%s", word) != EOF)
    {
        //cria um node na memory
        node *n = malloc(sizeof(node));
        //se n for igual a NULL é pq a tentiva de criação do node falhou
        if(n == NULL)
        {
            //informa a falha na criação do node
            printf("Could not allocate memory.\n");
            return false;
        }
        //copia uma string para o node
        strcpy(n->word, word);

        //incluindo a nova palavra no ínicio da lista
        unsigned int word_hash = hash(word);
        n->next = table[word_hash];
        table[word_hash] = n;

        dictionary_size++;

    }
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", dictionary);
        return false;
    }

    //

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
