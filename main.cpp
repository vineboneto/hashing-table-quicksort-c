#include <iostream>
#include <fstream>

using namespace std;

typedef struct sElement {
    int id;
    string name;
    struct sElement *next;
    struct sElement *prev;
} Element;

typedef struct sList {
    struct sElement *head;
    struct sElement *tail;
    int size;
} List;

//prototype


int main() {

    string line;
    ifstream input ("database/nomes.txt");
    
    if (input.is_open()) {
        while (getline (input, line)) {
            cout << line << endl;
        }
        input.close();
    } else {
        cout << "Unable to open file";  
    }

    return 0;
}

