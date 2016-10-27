#ifndef FPTREE_H
#define FPTREE_H

#include <vector>
#include <unordered_map>

typedef struct FPNode {
    int name;
    int count;
    FPNode * nodelink;
    FPNode * parent;
    std::vector<FPNode *> children;
} FPNode;

typedef struct HeadItem {
    int name;
    int count;
    FPNode * nodelink;
} HeadItem;

class FPTree {
private:
    FPNode * m_root;
    std::vector<HeadItem> m_headlist;
    std::unordered_map<int, int> m_headmap;
    std::unordered_map<int, int> m_mapnametoindex;
    int m_minsup;

public:
    FPTree(int minSup);
    virtual ~FPTree();
    void createHead(std::vector<std::vector<int>> & affairs,
            int affairsize,
            std::vector<int> * affairsnum = NULL);
    void createTree(std::vector<std::vector<int>> & affairs,
            int affairsize,
            std::vector<int> * affairsnum = NULL);
    void displayTree();
    void getFrequentItemset(std::vector<std::vector<int>> & freqis, 
            std::vector<int> & freq);
    
private:
    void destructTree(FPNode * root);
    void insertItem(std::vector<int> & item, int iitem,
            int affairnum, FPNode * root);
    void displayrecur(FPNode * root, int ind = 1);
    void findPrefixPath(FPNode * node, 
            std::vector<std::vector<int>> & path, 
            std::vector<int> & pathnum);
    std::vector<int> findParentrecur(FPNode * node);
    void getFrequentItemsetrecur(std::vector<std::vector<int>> & freqis,
            std::vector<int> & freq,
            std::vector<int> & prefix);
};

#endif
