#include "binTree.h"

int main() {
    system("chcp 1251");
    int to_add_1[21] = {9, 17, 6, 8, 3, 20, 16, 19, 18, 21, 12, 11, 10, 14, 7, 4, 1, 2, 13, 15, 5};
    int to_add_2[7] = { 10, 8, 4, 1, 9, 2, 11 };
    binTree tree1 = binTree();
    binTree tree2 = binTree();

    for (int i = 0; i < 21; ++i) {
        tree1.addNode(new Node(to_add_1[i]));
    }

    for (int i = 0; i < 7; ++i) {
        tree2.addNode(new Node(to_add_2[i]));
    }
    
    cout << "Введите искомое значение: ";
    int a;
    cin >> a;

    tree1.print(tree1.root);
    //cout << "Среднее арифметическое бинарного дерева: " << tree1.mean() << endl;
    //cout << "Количество узлов в дереве: " << tree1.count(tree1.root) << endl;
    cout << "Уровень узла с заданным значением: " << tree1.getLevel(tree1.root, a) << endl;
    //tree1.deleteLeft();
    //tree1.print(tree1.root);

    cout << "Введите искомое значение: ";
    int b; // 15
    cin >> b; // 100

    tree2.print(tree2.root);
    //cout << "Среднее арифметическое бинарного дерева: " << tree2.mean() << endl;
    //cout << "Количество узлов в дереве: " << tree2.count(tree2.root) << endl;
    cout << "Уровень узла с заданным значением: " << tree2.getLevel(tree2.root, b) << endl;
    //tree2.deleteLeft();
    //tree2.print(tree2.root);
}