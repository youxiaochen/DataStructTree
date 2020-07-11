//
// Created by 77991 on 2018/6/19.
//

#ifndef DATASTRUCTTREE_AVLTREE_HPP
#define DATASTRUCTTREE_AVLTREE_HPP

#include <string>
#include "Log.h"
#include "ArrayDeque.hpp"
using namespace std;

struct AVLTreeNode {
    int data;
    int height = 1;
    AVLTreeNode *left = NULL;
    AVLTreeNode *right = NULL;

    AVLTreeNode(int data) {
        this->data = data;
    }

    static int getNodeHeight(AVLTreeNode *node) {
        return node == NULL ? 0 : node->height;
    }

    //重新计算高度
    void calculateHeight() {
        this->height = max(getNodeHeight(left), getNodeHeight(right)) + 1;
    }

    //检测右旋
    AVLTreeNode* checkRightRotate() {
        if (getNodeHeight(this->left) - getNodeHeight(this->right) > 1) {//左孩子>右孩子, 左孩子必不NULL
            if (getNodeHeight(this->left->right) > getNodeHeight(this->left->left)) {
                return leftRightRotate();
            }
            return rightRotate();
        }
        return this;
    }

    //检测左旋
    AVLTreeNode* checkLeftRotate() {
        if (getNodeHeight(this->right) - getNodeHeight(this->left) > 1) {//左孩子>右孩子, 左孩子必不NULL
            if (getNodeHeight(this->right->left) > getNodeHeight(this->right->right)) {
                return rightLeftRotate();
            }
            return leftRotate();
        }
        return this;
    }

    //左旋转
    AVLTreeNode* leftRotate() {
        AVLTreeNode *rotateRight = this->right;
        this->right = rotateRight->left;
        rotateRight->left = this;
        this->calculateHeight();
        rotateRight->calculateHeight();
        return rotateRight;
    }

    //右节点先右旋,再左旋转
    AVLTreeNode* rightLeftRotate() {
        this->right = this->right->rightRotate();
        return this->leftRotate();
    }

    //右旋转
    AVLTreeNode* rightRotate() {
        AVLTreeNode *rotateLeft = this->left;
        this->left = rotateLeft->right;
        rotateLeft->right = this;
        this->calculateHeight();
        rotateLeft->calculateHeight();
        return rotateLeft;
    }

    //左节点先左旋,再右旋
    AVLTreeNode* leftRightRotate() {
        this->left = this->left->leftRotate();
        return this->rightRotate();
    }
};

class AVLTree {

private:
    AVLTreeNode *root = NULL;
    int len = 0;
    //释放节点及其所有子节点
    void freeNode(AVLTreeNode *node);
    //添加新节点
    AVLTreeNode* addNode(AVLTreeNode *node, int data);
    //删除节点
    AVLTreeNode* removeNode(AVLTreeNode *node, int data);
    /**
     * 获取右节点中最小的节点,并移除该节点
     * @param node
     * @param successor
     * @return 需要旋转时返回旋转后的节点
     */
    AVLTreeNode* removeLeftMinNode(AVLTreeNode *node, AVLTreeNode **successor);
    /**
     * 获取左节点中最大的节点,并移除该节点
     * @param node
     * @param successor
     * @return 需要旋转时返回旋转后的节点
     */
    AVLTreeNode* removeRightMaxNode(AVLTreeNode *node, AVLTreeNode **successor);
public:
    ~AVLTree();

    int size();

    void add(int data);

    void remove(int data);
    //层级打印
    void levelShow();
};

AVLTree::~AVLTree() {
    freeNode(root);
    root = NULL;
}

void AVLTree::freeNode(AVLTreeNode *node) {
    if (node) {
        freeNode(node->left);
        freeNode(node->right);
        delete node;
    }
}

AVLTreeNode* AVLTree::addNode(AVLTreeNode *node, int data) {
    if (node == NULL) {
        len++;
        return new AVLTreeNode(data);
    }
    if (node->data <= data) {//允许有相同值, 若是在Map中要另处理
        node->right = addNode(node->right, data);
        node = node->checkLeftRotate();
    } else {
        node->left = addNode(node->left, data);
        node = node->checkRightRotate();
    }
    node->calculateHeight();
    return node;
}

AVLTreeNode* AVLTree::removeRightMaxNode(AVLTreeNode *node, AVLTreeNode **successor) {
    if (node->right) {
        node->right = removeRightMaxNode(node->right, successor);
        node = node->checkRightRotate();
        node->calculateHeight();
        return node;
    } else {
        *successor = node;
        return node->left;
    }
}

AVLTreeNode* AVLTree::removeLeftMinNode(AVLTreeNode *node, AVLTreeNode **successor) {
    if (node->left) {
        node->left = removeLeftMinNode(node->left, successor);
        node = node->checkLeftRotate();
        node->calculateHeight();
        return node;
    } else {
        *successor = node;
        return node->right;
    }
}

AVLTreeNode* AVLTree::removeNode(AVLTreeNode *node, int data) {
    if (!node) return NULL;
    if (node->data > data) {
        node->left = removeNode(node->left, data);
        node = node->checkLeftRotate();
    } else if (node->data < data) {
        node->right = removeNode(node->right, data);
        node = node->checkRightRotate();
    } else {
        len--;
        if (!node->left && !node->right) {
            delete node;
            return NULL;
        }
        if (!node->left) {
            AVLTreeNode *right = node->right;
            delete node;
            return right;
        }
        if (!node->right) {
            AVLTreeNode *left = node->left;
            delete node;
            return left;
        }
        AVLTreeNode *successor;
        if (AVLTreeNode::getNodeHeight(node->right) < AVLTreeNode::getNodeHeight(node->left)) {
            node->left = removeRightMaxNode(node->left, &successor);
        } else {
            node->right = removeLeftMinNode(node->right, &successor);
        }
        node->data = successor->data;
        delete successor;
    }
    node->calculateHeight();
    return node;
}

int AVLTree::size() {
    return len;
}

void AVLTree::add(int data) {
    root = addNode(root, data);
}

void AVLTree::remove(int data) {
    root = removeNode(root, data);
}

void AVLTree::levelShow() {
    if (!root) {
        LOGD("LevelTree: NULL");
        return;
    }
    std::string logStr;
    ArrayDeque<AVLTreeNode*> deque;
    deque.push(root);
    while (!deque.isEmpty()) {
        AVLTreeNode *node = deque.pop();
        logStr += std::to_string(node->data);
        logStr += "(L:";
        if (node->left) {
            deque.push(node->left);
            logStr += to_string(node->left->data);
        } else {
            logStr +="#";
        }
        logStr += ",R:";
        if (node->right) {
            deque.push(node->right);
            logStr += to_string(node->right->data);
        } else {
            logStr +="#";
        }
        logStr += ')';
    }
    LOGD("levelTree: %s", logStr.c_str());
}

#endif //DATASTRUCTTREE_AVLTREE_HPP
