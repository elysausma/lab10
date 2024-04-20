#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  int count; 
};

// Trie structure
struct Trie {
  struct TrieNode *root;
};

// trie node birth 
struct TrieNode* createTrieNode() {
  struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    
  if (node) {
        node->count = 0;
        
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
  struct TrieNode *crawler = pTrie->root;
  
  int len = strlen(word);
  
  for (int i = 0; i < len; ++i) {
    int index = word[i] - 'a';
    
    if (!crawler->children[index]) {
      crawler->children[index] = createTrieNode();
    }
    
    crawler = crawler->children[index];
  }
    
    crawler->count++;
}

// computes the number of occurrances of the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {
  
  struct TrieNode *crawler = pTrie->root;
  
  int len = strlen(word);
    
  for (int i = 0; i < len; ++i) {
    
    int index = word[i] - 'a';
    
    if (!crawler->children[index]) {
      return 0; // Word not found
    }
    
    crawler = crawler->children[index];
  }
  return crawler->count;
}

// deallocate the trie structure
void deallocateTrieNode(struct TrieNode *node) {
    if (node) {
    
      for (int i = 0; i < ALPHABET_SIZE; ++i) {
        deallocateTrieNode(node->children[i]);
      
      }
      
      free(node);
  }
}

// Initializes a trie structure
struct Trie* createTrie() {
  
  struct Trie *pTrie = (struct Trie*)malloc(sizeof(struct Trie));
  
  if (pTrie) {
    pTrie->root = createTrieNode();
    
  }
    
  return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
  
  FILE *file = fopen(filename, "r");
  
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  int numWords = 0;
  char word[100];
    
  while (fscanf(file, "%s", word) != EOF && numWords < 256) {
    pInWords[numWords] = strdup(word);
    numWords++;
  }

  fclose(file);
  return numWords;
}

int main(void) {
    char *inWords[256];
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
      printf("%s\n", inWords[i]);
   }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    deallocateTrieNode(pTrie->root);
    free(pTrie);

    return 0;
}
