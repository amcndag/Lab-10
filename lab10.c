#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
typedef struct Trie
{

    int count;
    struct Trie* next[26]; // pointers to the children

} trie;


// prototypes:
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);



// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{

    trie* temp = pTrie;

    for (int i = 0; i < strlen(word); i++){

        int index = word[i] - 'a';

        if (temp->next[index] == NULL){

            temp->next[index] = createTrie();

        }

        temp = temp->next[index];

    }

    temp->count++;

}


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{

    trie* temp = pTrie;

    for (int i = 0; i < strlen(word); i++){

        int index = word[i] - 'a';

        if (temp->next[index] == NULL){

            return 0;

        }

        temp = temp->next[index];

    }

    return temp->count;

}


// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{

    for(int i = 0; i < 26; i++){

        if (pTrie->next[i] != NULL){

            deallocateTrie(pTrie->next[i]);

        }

    }

    free(pTrie);

    pTrie = NULL;

    return pTrie;

}


// Initializes a trie structure
struct Trie *createTrie()
{

    trie* newTrie = (trie*)malloc(sizeof(trie));

    newTrie->count = 0;

    for (int i = 0; i < 26; i++){

        newTrie->next[i] = NULL;

    }

    return newTrie;

}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{

    int wordCount = 0;

    FILE* fp = fopen(filename, "r");

    fscanf(fp, "%d", &wordCount);

    for (int i =0; i < wordCount; i++){

        pInWords[i] = (char*)malloc(sizeof(char) * 50);

        fscanf(fp, "%s", pInWords[i]);

    }

    return wordCount;

}


int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;

}