//
// Created by 77991 on 2018/6/17.
//

#ifndef DATASTRUCTTREE_BINARYSORTTREE_CPP
#define DATASTRUCTTREE_BINARYSORTTREE_CPP

#include <string>
#include "Log.h"
#include "ArrayDeque.hpp"

using namespace std;

struct BinarySortTreeNode {
    int data;
    BinarySortTreeNode *left = NULL;
    BinarySortTreeNode *right = NULL;
    BinarySortTreeNode(int data) {
        this->data = data;
    }
};

//二叉排序树
class BinarySortTree {
private:
    BinarySortTreeNode *root = NULL;
    int len = 0;
    //添加新节点
    BinarySortTreeNode* addNode(BinarySortTreeNode *node, int data);
    //移除节点
    BinarySortTreeNode* removeNode(BinarySortTreeNode *node, int data);
    //移除节点中最小的节点
    BinarySortTreeNode* removeLeftMinNode(BinarySortTreeNode *node, BinarySortTreeNode **successor);
    //释放节点及其所有子节点
    void freeNode(BinarySortTreeNode *node);
public:
    ~BinarySortTree();

    int size();

    void add(int data);

    void remove(int data);
    //层级打印
    void levelShow();
};

BinarySortTree::~BinarySortTree() {
    freeNode(root);
    root = NULL;
}

void BinarySortTree::freeNode(BinarySortTreeNode *node) {
    if (node) {
        freeNode(node->left);
        freeNode(node->right);
        delete node;
    }
}

BinarySortTreeNode* BinarySortTree::addNode(BinarySortTreeNode *node, int data) {
    if (!node) {
        len++;
        return new BinarySortTreeNode(data);
    }
    if (node->data > data) {
        node->left = addNode(node->left, data);
    } else {
        node->right = addNode(node->right, data);
    }
    return node;
}

BinarySortTreeNode* BinarySortTree::removeLeftMinNode(BinarySortTreeNode *node, BinarySortTreeNode **successor) {
    if (node->left) {
        node->left = removeLeftMinNode(node->left, successor);
        return node;
    } else {
        *successor = node;
        return node->right;
    }
}

BinarySortTreeNode* BinarySortTree::removeNode(BinarySortTreeNode *node, int data) {
    if (!node) return NULL;
    if (node->data > data) {
        node->left = removeNode(node->left, data);
    } else if (node->data < data) {
        node->right = removeNode(node->right, data);
    } else {  //相等
        len--;
        if (!node->left && !node->right) {
            delete node;
            return NULL;
        }
        if (!node->left) {
            BinarySortTreeNode *right = node->right;
            delete node;
            return right;//right not null
        }
        if (!node->right) {
            BinarySortTreeNode *left = node->left;
            delete node;
            return left; //left not null
        }
        //node right left都不为空
        BinarySortTreeNode *successor;
        node->right = removeLeftMinNode(node->right, &successor);
        node->data = successor->data;
        delete successor;
    }
    return node;
}

int BinarySortTree::size() {
    return this->len;
}

void BinarySortTree::add(int data) {
    root = addNode(root, data);
}

void BinarySortTree::remove(int data) {
    root = removeNode(root, data);
}

void BinarySortTree::levelShow() {
    std::string str;
    if (root) {
        ArrayDeque<BinarySortTreeNode*> nodeDeque;
        nodeDeque.push(root);
        while (!nodeDeque.isEmpty()) {
            BinarySortTreeNode *node = nodeDeque.pop();
            str += std::to_string(node->data);
            str += "(L:";
            if (node->left) {
                nodeDeque.push(node->left);
                str += to_string(node->left->data);
            } else {
                str +="#";
            }
            str += ",R:";
            if (node->right) {
                nodeDeque.push(node->right);
                str += to_string(node->right->data);
            } else {
                str +="#";
            }
            str += ')';
        }
    }
    LOGD("levelTree: %s", str.c_str());
}

#endif //DATASTRUCTTREE_BINARYSORTTREE_CPP
