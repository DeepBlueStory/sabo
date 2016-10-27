#include <iostream>
#include <vector>
#include "FPTree.h"
#include "json.h"

using namespace std;

int main() {
    vector<vector<int>> data = {
        {'r', 'z','h','j','p'},
        {'z', 'y', 'x', 'w', 'v', 'u', 't', 's'},
        {'z'},
        {'r','x','n','o','s'},
        {'y','r','x','z','q','t','p'},
        {'y','z','x','e','q','s','t','m'}};
    FPTree tree(3);
    tree.createHead(data, data.size());
    tree.createTree(data, data.size());
    //tree.displayTree();
    vector<vector<int>> frequentitemset;
    vector<int> frequent;
    tree.getFrequentItemset(frequentitemset, frequent);
    vector<string>label(200, "xxx");
    convertToJson(frequentitemset, frequent, label);
    return 0;
}
