//
// Created by 77991 on 2018/6/16.
//

#include <string>
#include "Log.h"
#include "AVLTree.hpp"
#include "BinarySortTree.hpp"

#ifndef DATASTRUCTTREE_BINARYTREE_H
#define DATASTRUCTTREE_BINARYTREE_H
using namespace std;

template <class E>
struct TreeNode {
    E data;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
    TreeNode(const E &data) : data(data) {
    }
    ~TreeNode() {
        if (left) {
            delete left;
            left = NULL;
        }
        if (right) {
            delete right;
            right = NULL;
        }
    }
};

class BinaryTree {

private:
    static const char NODE_NULL = '#';

public:

    /**
     * 前序序列化
     * @param root
     * @return
     */
    static void preOrderSerializer(TreeNode<char> *root, string &str) {
        if (!root) {
            str += NODE_NULL;
            return;
        }
        str += root->data;
        preOrderSerializer(root->left, str);
        preOrderSerializer(root->right, str);
    }

    /**
     * 反序列化
     * @param str
     * @return
     */
    static TreeNode<char>* deOrderSerializer(char *&str) {
        if (*str == '#') {
            str++;
            return NULL;
        }
        TreeNode<char> *node = new TreeNode<char>(*str);
        str++;
        node->left = deOrderSerializer(str);
        node->right = deOrderSerializer(str);
        return node;
    }

    /**
     * 中序列化
     * @param root
     * @return
     */
    static void middleOrderSerializer(TreeNode<char> *root, string &str) {
        if (!root) {
            str += NODE_NULL;
            return;
        }
        middleOrderSerializer(root->left, str);
        str += root->data;
        middleOrderSerializer(root->right, str);
    }

    /**
     * 后序列化
     * @param root
     * @return
     */
    static void backOrderSerializer(TreeNode<char> *root, string &str) {
        if (!root) {
            str += NODE_NULL;
            return;
        }
        backOrderSerializer(root->left, str);
        backOrderSerializer(root->right, str);
        str += root->data;
    }

};
#endif //DATASTRUCTTREE_BINARYTREE_H
