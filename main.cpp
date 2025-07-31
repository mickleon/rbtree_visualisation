#include <iostream>

#include "tree.h"

int main() {
    using std::cin;
    Tree tr;
    printf("Number of nodes: ");
    int n, x;
    cin >> n;
    if (n > 0) {
        printf("Nodes: ");
        for (int i = 0; i < n; i++) {
            cin >> x;
            tr.insert(x);
        }
    }
    
    tr.print();
    char c;
    while (true) {
        printf("1. Insert\n2. Erase\n3. Quit\n> ");
        cin >> c;
        switch (c) {
            case '1': {
                printf("Node to insert: ");
                cin >> x;
                tr.insert(x);
                tr.print();
                break;
            }
            case '2': {
                printf("Node to erase: ");
                cin >> x;
                Node *y = tr.find(x);
                if (y)
                    tr.erase(y);
                tr.print();
                break;
            }
            case '3': return 0;
            case 'q': return 0;
            case 'Q': return 0;
            default: break;
        }
    }
}

/*
18
9 6 17 3 8 16 20 1 4 7 12 19 21 2 5 11 14 18
*/
