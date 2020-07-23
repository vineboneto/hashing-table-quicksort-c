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

    string line[10];
    ifstream input ("database/nomes.txt");
    int i = 0;

    if (input.is_open()) {
        while (getline (input, line[i]) && i < 10) {
            char asc = line[i].at(0);
            cout << "[" << i << "] " << line[i] << " First char: " << line[i].at(0) << " ASC:: " << (int)asc << endl;
            i++;
        }
        input.close();
    } else {
        cout << "Unable to open file";  
    }

    return 0;
}
