#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M_KEYS 97 // Number of hash table keys, prime and odd

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

// Prototype
// Criação
FILE* openFile(char*, char*);
TableHash* createTableHash();
List* createList();
Element* createElement();

// Inserção e Remoção
int toAsc(char);
int hashCode(char*);
int insertElement(List*, Element*);
int length(char*);
char* removeElement(List*, Element*);

void newInsertTableHash(TableHash*);
void removeElementTableHash(TableHash*);

// Hashing
void hashing(char*, TableHash []);
void displayHashingById(TableHash*, int);
void displayHashing(TableHash*);
void displayList(List*);
void clearHashing(TableHash*);
void clearList(List*);

// Ordenação
void sortedTableHash(TableHash*);
void quickSort(Element*, Element*);
void swap(int*, int*);
Element* partition(Element*, Element*);

// Busca
void searchElement(TableHash* tableHash);

int main() {
    char* input_file = "../database/nomes.txt";
    
    // Gerando chaves e criando tabela hash
    TableHash* tableHash = createTableHash();
    
    for (int i = 0; i < M_KEYS; i++) {
        tableHash[i].list = createList();
        tableHash[i].key = i;
    }

    // função de espalhamento
    hashing(input_file, tableHash);

    // Exibindo todos elementos da Tabela Hash
    // displayHashing(tableHash);

    // Realizando uma nova inserção na table Hash
    // newInsertTableHash(tableHash);

    // Ordenanando a Tabela Hash
    sortedTableHash(tableHash);

    // Deleta um determinado Elemento
    // removeElementTableHash(tableHash);
    
    // Realizando uma Busca na Table Hash
    // searchElement(tableHash);

    // imprimindo uma lista da table hash pelo seu id
    displayHashingById(tableHash, 0);

    //limpando tableHash
    clearHashing(tableHash);

    printf("\n\n");
    system("pause");

    return EXIT_SUCCESS;
}

FILE* openFile(char* path, char* mode) {
    FILE* f = fopen(path, mode);
    if (!f) {
        perror("Ocorreu algum erro enquanto ao tentar abrir o Arquivo!\n");
        exit(EXIT_FAILURE);
    }
    return f;
}

TableHash* createTableHash() {
    TableHash* t = NULL;
    t = malloc(M_KEYS * sizeof(TableHash));
    if (!t) {
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
    if (!l) {
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
    if (!e) {
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
    int err = 0;
    int success = 0;

    char* row = malloc(bytes);
    while (getline(&row, &bytes, in) > 0) {
        int key = hashCode(row);
        // Gerando novo Elemento
        Element* e = createElement();
        strcpy(e->name, row);

        // Inserindo elemento na respectiva key
        insertElement(tableHash[key].list, e) == 0 
        ? success++
        : err++;

    }
    printf("\n\nInseridos com sucesso : %d\n\n", success);
    printf("\n\nErros totais ao inserir: %d\n\n", err);

    free(row);
    fclose(in);
}

int insertElement(List* list, Element* e) {
    Element* pivo = list->tail;

    if (pivo == NULL && list->size > 0) {
        free(e);
        return 1;
    }
    
    if (list->size == 0) {
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

int hashCode(char* row) { 
    int len = strlen(row);
    int hash = 0;
    for (int i = 0; i < len; i++) {
        int asc = toAsc(row[i]);
        hash = (hash * 31 + asc) % M_KEYS; 
    }
    return hash;
}

void displayHashingById(TableHash* tableHash, int id) {
    Element* e = tableHash[id].list->head;

    if (tableHash[id].list->size > 0) {
        printf ("\nLista[%d]\n", id);
        while(e != NULL) {
            if(e) printf("Name: %s", e->name);
            e = e->next;
        }
    } else {
        printf("Lista Vazia!");
    }
}

void displayHashing(TableHash* t) {
    for (int i = 0; i < M_KEYS; i++) {
        // Exibindo elementos das Listas
        printf("\nList->Key::%d\n", t[i].key);
        displayList(t[i].list);
    }
}

void displayList(List* l) {
    Element* e = l->head;
    
    if (l->size > 0) {
        while(e != NULL) {
            if(e) printf("Name: %s", e->name);
            e = e->next;
        }
    } else {
        printf("Lista Vazia!\n");
    }
}

void clearHashing(TableHash* t) {
    for (int i = 0; i < M_KEYS; i++) {
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
    if (l->size == 0){
        printf("Lista Vazia!\n");
        return;
    }
    while (l->size > 0) {
        del = removeElement(l, l->head);
        // printf("Elemento Removido: %s", del);
        free(del);
        del = NULL;
    }
}

void sortedTableHash(TableHash* tableHash) {
    List* list;
    for (int i = 0; i < M_KEYS; i++) {
        list = tableHash[i].list;
        quickSort(list->head, list->tail);
    }
}

void quickSort(Element* low, Element* high) { 
	if (high != NULL && low != high && low != high->next) {       
        // Calculando o pi
		Element* pi = partition(low, high); 
        
		quickSort(low, pi->prev); 
		quickSort(pi->next, high); 
	} 
} 

Element* partition (Element* low, Element* high) { 
	Element* i = low->prev; 
    int pivo;
    int jASC;
    
	for (Element* j = low; j != high;j = j->next) {
        int k = 0;
        do {

            // Definindo valores de acordo com a tabela ASCII
            pivo = toAsc(high->name[k]);
            jASC = toAsc(j->name[k]);

            if (jASC < pivo) {
                i = (i == NULL) ? low : i->next;
                swap(&(i->name), &(j->name));      
            }
            k++;
        } while (jASC == pivo);
    }

    // faz um swap final no proxímo elemento do ultimo elemento trocado
    i = (i == NULL) ? low : i->next;
	swap(&(i->name), &(high->name)); 
	return i; 
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void searchElement(TableHash* tableHash) {
    size_t bytes = 100;
    char* aux = malloc(bytes);

    printf("Digite o nome que deseja encontrar (TUDO MAIUSCULO): ");
    scanf(" %[^\n]", aux);
    int count = 0;
    // Concatenando string lida com a quebra de linha
    strcat(aux, "\n");

    int key = hashCode(aux);
    printf("Key: %d\n", key);
    Element* e = tableHash[key].list->head;
    
    while (e != NULL) {
        if (e) {
            if (strcmp(e->name, aux) == 0) {
                printf("Nome Encontrado: %s", e->name);
                count++;
            } 
        }
        e = e->next;    
    }

    printf("Esse nome foi encontrado %d vezes.\n", count);
    free(aux);
}

void newInsertTableHash(TableHash* tableHash) {
    Element* e = createElement();
    
    printf("Digite o novo nome a ser inserido: ");
    scanf(" %[^\n]", e->name);
    strcat(e->name, "\n");

    int key = hashCode(e->name);
    insertElement(tableHash[key].list, e) == 0
    ? printf("Insercao realizada com sucesso\n")
    : printf("Ocorreu algum erro ao inserir\n");
}

void removeElementTableHash(TableHash* tableHash) {
    size_t bytes = 100;
    char* aux = malloc(bytes);

    printf("Digite o nome que deseja remover: ");
    scanf(" %[^\n]", aux);
    strcat(aux, "\n");

    int key = hashCode(aux);
    int count = 0;
    int len; 
    Element* e = tableHash[key].list->head;

    while(e != NULL) {
        if (e) {
            if (strcmp(e->name, aux) == 0 && count == 0) {
                // Removendo caracter de quebra da linha
                char* del = removeElement(tableHash[key].list, e);
                len = strlen(del) - 1;
                del[len] = ' ';
                del == " " ? printf("Erro ao Remover Elemento\n") :
                printf("Elemento %s removido com sucesso\n", del);
                count++;
                free(del);
            }
        }
        e = e->next;
    }
    if (count == 0) {
        printf("Elemento Nao Encontrado!\n");
    }

    free(aux);
}

// int length(char* row) {
//     int i = 0;
//     while(row[i] != '\0') {
//         i++;
//     }
//     return i - 1;
// }