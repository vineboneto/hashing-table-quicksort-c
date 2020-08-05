#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M_KEYS 11 // numero de keys primo e impar

typedef struct sElement {
    char* name;
    struct sElement *next;
    struct sElement *prev;
} Element;

typedef struct sList {
    struct sElement *head;
    struct sElement *tail;
    int size;
} List;

typedef struct sTableHash {
    struct sList *list;
    int key;
} TableHash;

// prototype
FILE* openFile(char*, char*);
TableHash* createTableHash();
List* createList();
Element* createElement();

int toAsc(char);
int hashCode(int, char*);
int insertElement(List*, Element*);
char* removeElement(List*, Element*);

void hashing(char*, TableHash []);
void displayHashing(TableHash*);
void displayList(List*);
void clearHashing(TableHash*);
void clearList(List*);

int main() {
    char* input_file = "../database/nomes.txt";
    
    // Gerando chaves e criando tabela hash
    TableHash* tableHash = createTableHash();
    int i;
    for(i = 0; i < M_KEYS; i++) {
        tableHash[i].list = createList();
        tableHash[i].key = i;
    }

    // função de espalhamento
    hashing(input_file, tableHash);

    // Exibindo elementos da Tabela Hash
    displayHashing(tableHash);
    
    //limpando tableHash
    clearHashing(tableHash);


    return 0;
}

FILE* openFile(char* path, char* mode) {
    FILE* f = fopen(path, mode);
    if(!f) {
        perror("Ocorreu algum erro enquanto ao tentar abrir o Arquivo!\n");
        exit(EXIT_FAILURE);
    }
    return f;
}

TableHash* createTableHash() {
    TableHash* t = NULL;
    t = malloc(M_KEYS * sizeof(TableHash));
    if(!t) {
        perror("Memoria nao alocada\n");
        exit(EXIT_FAILURE);
    }
    t->list = NULL;
    t->key = -1;
    return t;
}

List* createList() {
    List* l = NULL;
    l = malloc(sizeof(List));
    if(!l) {
        perror("Memoria nao alocada\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

Element* createElement() {
    Element* e = NULL;
    size_t bytes = 256;
    e = malloc(sizeof(Element));
    if(!e) {
        perror("Memoria nao alocada\n");
        exit(EXIT_FAILURE);
    }
    e->next = NULL;
    e->prev = NULL;
    e->name = malloc(bytes);
    return e;
}

void hashing(char* input_file, TableHash* tableHash) {
    FILE* in = openFile(input_file, "r");
    size_t bytes = 256; 

    char* row = malloc(bytes);
    while(getline(&row, &bytes, in) > 0) {
        char firstLetter = row[0];
        int asc = toAsc(firstLetter);
        int key = hashCode(asc, row);

        // Gerando novo Elemento
        Element* e = createElement();
        strcpy(e->name, row);

        // Inserindo elemento na respectiva key
        insertElement(tableHash[key].list, e) == 0 ? printf("Inserido com sucesso\n") 
        : printf("Erro ao inserir\n");

    }

    fclose(in);
}

int insertElement(List* list, Element* e) {
    Element* pivo = list->tail;

    if(pivo == NULL && list->size > 0) {
        free(e);
        return 1;
    }
    
    if(list->size == 0) {
        list->head = e;
        list->tail = e;
    } else {
        e->next = pivo->next;
        e->prev = pivo;

        if(pivo->next == NULL) {
            list->tail = e;
        } else {
            pivo->next->prev = e;
        }
        pivo->next = e;
    }
    list->size++;
    return 0;
}

char* removeElement(List* list, Element* e) {

    char* del = e->name;
    if(e != NULL && list->size > 0) {
        if(e == list->head) {
            list->head = e->next;
            if(list->head == NULL) {
                list->tail = NULL;
            } else {
                e->next->prev = NULL;
            }
        } else {
            e->prev->next = e->next;
            if(e->next == NULL) {
                list->tail = e->prev;
            } else {
               e->next->prev = e->prev; 
            }
        }
        free(e);
        e = NULL;
        list->size--;

        return del; 
    }
    return " ";
}

int toAsc(char letter) { return (int)letter; }

int hashCode(int value , char* row) { 

    return value % M_KEYS; 
}

void displayHashing(TableHash* t) {
    int i;
    for(i = 0; i < M_KEYS; i++) {
        // Exibindo elementos das Listas
        printf("\nList->Key::%d\n", t[i].key);
        displayList(t[i].list);
    }
}

void displayList(List* l) {
    Element* e = l->head;
    
    if(l->size > 0) {
        while(e != NULL) {
            if(e) 
                printf("Name: %s", e->name);
            e = e->next;
        }
    } else {
        printf("Lista Vazia!\n");
    }
}

void clearHashing(TableHash* t) {
    int i;
    for(i = 0; i < M_KEYS; i++) {
        printf("\nRemovendo lista[%d]\n", i);
        printf("Size: %d\n", t[i].list->size);
        clearList(t[i].list);
        free(t[i].list);
        t[i].list = NULL;
    }

    free(t);
    t = NULL;
    printf("\nTableHash Vazia!!\n");
}

void clearList(List* l) {
    char* del;
    if(l->size == 0){
        printf("Lista Vazia!\n");
        return;
    }
    while(l->size > 0) {
        del = removeElement(l, l->head);
        // printf("Elemento Removido: %s", del);
        free(del);
        del = NULL;
    }
}