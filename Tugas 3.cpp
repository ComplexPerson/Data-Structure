#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define TABLE_SIZE 10

struct node
{
	char data[100];
	struct node *next;
}*hashTable[26], *curr;

//First Character
int hashFunction(char data[])
{
	int hashKey = -1;
	char firstChar;
	
	//ambil karakter pertama
	firstChar = data[0];
	//A -> a (97) - 97 = 0;
	hashKey = tolower(firstChar) - 97;
	return hashKey;
}

//METHOD DIVISION
int divHash(int key)
{
	return key % TABLE_SIZE;
}

//METHOD FOLDING
int foldingHash(int key)
{
	int part1 = key/1000; //ambil 4 digit pertama
	int part2 = key%1000; //ambil 4 digit terakhir
	
	return (part1 + part2) % TABLE_SIZE;
}

int midSquareHash(int key) {
    int squared = key * key;
    int mid = (squared / 100) % 1000; //ambil 3 digit tengah
    return mid % TABLE_SIZE;
}

int digitExtractionHash(int key) {
    int sum = 0;
    while (key > 0) {
        sum += key % 10;
        key /= 10;
    }
    return sum % TABLE_SIZE;
}

int rotationHash(int key) {
    int lastDigit = key % 10;
    key = key / 10 + lastDigit * 1000; // rotasi digit terakhir ke depan
    return key % TABLE_SIZE;
}

void pushBack(int hashKey, char data[])
{
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	strcpy(newNode->data, data);
	newNode->next = NULL;
	
	//if the index is still empty
	if(hashTable[hashKey] == NULL)
	{
		hashTable[hashKey] = newNode;
	}
	//if the index not empty
	else
	{
		curr = hashTable[hashKey];
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = newNode;
	}
}

void rehash() {
    struct node* oldTable[26];
    memcpy(oldTable, hashTable, sizeof(hashTable));
    memset(hashTable, 0, sizeof(hashTable));

    for (int i = 0; i < 26; i++) {
        curr = oldTable[i];
        while (curr != NULL) {
            pushBack(hashFunction(curr->data), curr->data);
            struct node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}

void viewHashTable()
{
	//access all index
	for(int i=0; i<26; i++)
	{
		//cek index null atau tidak
		if(hashTable[i] != NULL)
		{
			printf("Hash Table Index [%d] :\n", i);
			curr = hashTable[i];
			
			while(curr!=NULL)
			{
				printf("%s ", curr->data);
				curr = curr->next;
			}
			printf("\n");
		}
	}
}

void pushBackLinearProbing(int hashKey, char data[]) {
    int originalHashKey = hashKey;
    while (hashTable[hashKey] != NULL) {
        hashKey = (hashKey + 1) % TABLE_SIZE;
        if (hashKey == originalHashKey) {
            printf("Hash table is full, rehashing...\n");
            rehash();
            pushBackLinearProbing(hashFunction(data), data);
            return;
        }
    }
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    hashTable[hashKey] = newNode;
}

void pushBackWithCollisionHandling(int hashKey, char data[], int collisionMethod) {
    if (collisionMethod == 1) { // Linear Probing
        pushBackLinearProbing(hashKey, data);
    } else if (collisionMethod == 2) { // Rehashing
        rehash();
        pushBack(hashFunction(data), data);
    } else if (collisionMethod == 3) { // Chaining
        pushBack(hashKey, data);
    }
}

void clearHashTable() {
    for (int i = 0; i < 26; i++) {
        curr = hashTable[i];
        while (curr != NULL) {
            struct node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main()
{
    char data[100];
    memset(hashTable, 0, sizeof(hashTable));
    int run = 1;
    int (*hashFunc)(int) = divHash; // default hash function
    int collisionMethod = 1; // default collision handling method

    while (run != 0)
    {
        printf("Welcome !\n");
        printf("1. Set Hashing Method\n");
        printf("2. Set Collision Handling Method\n");
        printf("3. Input Data\n");
        printf("4. View Hash Table\n");
        printf("5. Clear Hash Table\n");
        printf("6. Exit\n");
        printf("Option: ");
        scanf("%d", &run); getchar();

        switch (run)
        {
        case 1:
            {
                int hashMethod;
                printf("1. Mid-Square Hashing\n");
                printf("2. Division Hashing\n");
                printf("3. Folding Hashing\n");
                printf("4. Digit Extraction Hashing\n");
                printf("5. Rotation Hashing\n");
                printf("Choose Hashing Method:\n");
                scanf("%d", &hashMethod); getchar();
                switch (hashMethod)
                {
                    case 1:
                        hashFunc = midSquareHash;
                        break;
                    case 2:
                        hashFunc = divHash;
                        break;
                    case 3:
                        hashFunc = foldingHash;
                        break;
                    case 4:
                        hashFunc = digitExtractionHash;
                        break;
                    case 5:
                        hashFunc = rotationHash;
                        break;
                    default:
                        printf("Invalid choice\n");
                        continue;
                }
            }
            break;
        
        case 2:
            {
                printf("Choose Collision Handling Method:\n");
                printf("1. Linear Probing\n");
                printf("2. Rehashing\n");
                printf("3. Chaining\n");
                scanf("%d", &collisionMethod); getchar();
            }
            break;

        case 3:
            do
            {
                printf("Input Data: ");
                scanf("%s", data); getchar();

                if (strcmpi(data, "exit") == 0) break;
                int key = 0;
                for (int i = 0; data[i] != '\0'; i++) {
                    key += data[i];
                }
                pushBackWithCollisionHandling(hashFunc(key), data, collisionMethod);

            } while (true);
            break;

        case 4:
            viewHashTable();
            break;

        case 5:
            clearHashTable();
            break;

        case 6:
            printf("Goodbye & have a nice day !\n");
            run = 0;
            break;

        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}