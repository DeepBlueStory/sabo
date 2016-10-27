#include "FPTree.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

FPTree::FPTree(int minSup) {
    m_root = new FPNode;
    m_root -> name = 0;
    m_root -> count = 0;
    m_root -> nodelink = NULL;
    m_root -> parent = NULL;
    m_minsup = minSup;
}

FPTree::~FPTree() {
    destructTree(m_root);
}

void FPTree::destructTree(FPNode * root) {
    if(root->children.empty()) {
        delete root;
    }else {
        for(auto children : root->children) {
            destructTree(children);
        }
    }
}

void FPTree::createHead(std::vector<std::vector<int>> & affairs,
        int affairsize,
        std::vector<int> *affairsnum) {
    if(affairsnum == NULL) {
        affairsnum = new std::vector<int>(affairsize, 1);
    }
    for(int i = 0; i < affairsize; i++) {
        for(int item : affairs[i]) {
            if(m_headmap.find(item) == m_headmap.end())
                m_headmap[item] = (*affairsnum)[i];
            else 
                m_headmap[item] += (*affairsnum)[i];
        }
    }
    
    for(auto item = m_headmap.begin(); item != m_headmap.end();) {
        if(item->second < m_minsup) 
            m_headmap.erase(item++);
        else 
            item++;
    }
    

    for(auto item : m_headmap) {
        HeadItem h;
        h.name = item.first;
        h.count = item.second;
        h.nodelink = NULL;
        m_headlist.push_back(h);
    }

    sort(m_headlist.begin(), m_headlist.end(), 
            [&] (const HeadItem a, const HeadItem b) {
            return a.count > b.count;
            });
    for(int i = 0; i < m_headlist.size(); i++) {
        m_mapnametoindex[m_headlist[i].name] = i;
    }
}

void FPTree::createTree(std::vector<std::vector<int>> & affairs, 
        int affairsize,
        std::vector<int> * affairsnum) {
    if(affairsnum == NULL) {
        affairsnum = new std::vector<int>(affairsize, 1);
    }
    for(int i = 0; i < affairsize; i++) {
        std::vector<int> vitem;
        for(auto item : affairs[i]) {
            if(m_headmap.find(item) != m_headmap.end()) 
                vitem.push_back(item);
        }
        sort(vitem.begin(), vitem.end(), 
            [&](const int a, const int b) {
                return m_headmap[a] > m_headmap[b];
            });
        insertItem(vitem, 0, (*affairsnum)[i],  m_root);
    }
}

void FPTree::insertItem(std::vector<int> & item, int iitem, 
        int affairnum, FPNode * root) {
    if(iitem >= item.size()) return ;
    bool find = false;
    FPNode * children = NULL;
    for(FPNode * child : root->children) {
        if(!find && child->name == item[iitem]) {
            child->count += affairnum;
            find = true;
            children = child;
        }
    }
    if(!find) {
        children = new FPNode;
        children->name = item[iitem];
        children->count = affairnum;
        children->parent = root;
        int i = m_mapnametoindex[item[iitem]];
        children->nodelink = m_headlist[i].nodelink;
        m_headlist[i].nodelink = children;
        root->children.push_back(children);
    }
    insertItem(item, iitem+1, affairnum, children);
}

void FPTree::displayrecur(FPNode * root, int ind) {
    for(int i = 0; i < ind; i++) {
        std::cout << ' ';
    }
    std::cout << (char)root->name << ' ' << root->count << std::endl;
    for(auto child : root->children) {
        displayrecur(child, ind+1);
    }
}

void FPTree::displayTree() {
    displayrecur(m_root);
}

std::vector<int> FPTree::findParentrecur(FPNode * node) {
    std::vector<int> res;
    node = node->parent;
    while(node->parent != NULL) {
        res.push_back(node->name);
        node = node->parent;
    }
    return res;
}

void FPTree::findPrefixPath(FPNode * node,
        std::vector<std::vector<int>> & path, 
        std::vector<int> & pathnum) {
    while(node != NULL) {
        path.push_back(findParentrecur(node));
        pathnum.push_back(node->count);
        node = node->nodelink;
    }
}

void FPTree::getFrequentItemsetrecur(std::vector<std::vector<int>> & freqis, 
        std::vector<int> & freq,
        std::vector<int> & prefix) {
    if(m_root->children.empty()) return;
    for(auto head : m_headlist) {
        prefix.push_back(head.name);
        freqis.push_back(prefix);
        freq.push_back(head.count);
        std::vector<std::vector<int>> path;
        std::vector<int> pathnum;
        findPrefixPath(head.nodelink, path, pathnum);
        FPTree tree(m_minsup);
        tree.createHead(path, path.size(), &pathnum);
        tree.createTree(path, path.size(), &pathnum);
        tree.getFrequentItemsetrecur(freqis, freq, prefix);
        prefix.pop_back();
    }
}

void FPTree::getFrequentItemset(std::vector<std::vector<int>> &freqis, 
        std::vector<int> &freq) {
    std::vector<int> prefix;
    getFrequentItemsetrecur(freqis, freq, prefix);
}
