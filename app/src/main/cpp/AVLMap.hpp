//
// Created by 77991 on 2018/7/26.
//

#include "Comparable.hpp"
#include <string>

#ifndef DATASTRUCTTREE_AVLMAP_HPP
#define DATASTRUCTTREE_AVLMAP_HPP


template <class K, class V, class C = Comparable<K>>
class AVLMap {

private:

    struct AVLMapEntry {
        K key;
        V value;
        int height = 1;
        AVLMapEntry *left = NULL;
        AVLMapEntry *right = NULL;

        AVLMapEntry(K key, V value) : key(key), value(value) {
        }

        static int getEntryHeight(AVLMapEntry *entry) {
            return entry == NULL ? 0 : entry->height;
        }

        //重新计算高度
        void calculateHeight() {
            this->height = max(getEntryHeight(left), getEntryHeight(right)) + 1;
        }

        //检测右旋
        AVLMapEntry* checkRightRotate() {
            if (getEntryHeight(this->left) - getEntryHeight(this->right) > 1) {//左孩子>右孩子, 左孩子必不NULL
                if (getEntryHeight(this->left->right) > getEntryHeight(this->left->left)) {
                    return leftRightRotate();
                }
                return rightRotate();
            }
            return this;
        }

        //检测左旋
        AVLMapEntry* checkLeftRotate() {
            if (getEntryHeight(this->right) - getEntryHeight(this->left) > 1) {//左孩子>右孩子, 左孩子必不NULL
                if (getEntryHeight(this->right->left) > getEntryHeight(this->right->right)) {
                    return rightLeftRotate();
                }
                return leftRotate();
            }
            return this;
        }

        //左旋转
        AVLMapEntry* leftRotate() {
            AVLMapEntry *rotateRight = this->right;
            this->right = rotateRight->left;
            rotateRight->left = this;
            this->calculateHeight();
            rotateRight->calculateHeight();
            return rotateRight;
        }

        //右节点先右旋,再左旋转
        AVLMapEntry* rightLeftRotate() {
            this->right = this->right->rightRotate();
            return this->leftRotate();
        }

        //右旋转
        AVLMapEntry* rightRotate() {
            AVLMapEntry *rotateLeft = this->left;
            this->left = rotateLeft->right;
            rotateLeft->right = this;
            this->calculateHeight();
            rotateLeft->calculateHeight();
            return rotateLeft;
        }

        //左节点先左旋,再右旋
        AVLMapEntry* leftRightRotate() {
            this->left = this->left->leftRotate();
            return this->rightRotate();
        }
    };


    //typedef typename AVLMap<K, V, C>::AVLMapEntry* _AVLMapEntry;

    AVLMapEntry *root = NULL;
    C comparator;
    int len = 0;
private:

    void freeMap(AVLMapEntry *entry);

    //添加新节点
    AVLMapEntry* addEntry(AVLMapEntry *entry, const K &key, const V &value);

    //删除节点
    AVLMapEntry* removeEntry(AVLMapEntry *entry, const K &key);

    /**
     * 获取右节点中最小的节点,并移除该节点
     * @param node
     * @param successor
     * @return 需要旋转时返回旋转后的节点
     */
    AVLMapEntry* removeLeftMinEntry(AVLMapEntry *entry, AVLMapEntry **successor);

    /**
     * 获取左节点中最大的节点,并移除该节点
     * @param node
     * @param successor
     * @return 需要旋转时返回旋转后的节点
     */
    AVLMapEntry* removeRightMaxEntry(AVLMapEntry *entry, AVLMapEntry **successor);

public:

    ~AVLMap();

    int size();

    bool isEmpty();

    void put(const K &key, const V &value);

    V remove(const K &key);

    /* 我没时间,没时间...

    V get(V key);

    bool containsKey(K key);

    void clear();*/

};

template <class K, class V, class C>
AVLMap<K, V, C>::~AVLMap() {
    freeMap(root);
    root = NULL;
    len = 0;
}

template <class K, class V, class C>
void AVLMap<K, V, C>::freeMap(AVLMap::AVLMapEntry *entry) {
    if (entry) {
        freeMap(entry->left);
        freeMap(entry->right);
        delete entry;
    }
}

template <class K, class V, class C>
typename AVLMap<K, V, C>::AVLMapEntry* AVLMap<K, V, C>::addEntry(AVLMapEntry *entry, const K &key, const V &value) {
    if (!entry) {
        len++;
        return new AVLMapEntry(key, value);
    }
    int compare = comparator(entry->key, key);
    if (compare == 0) {
        entry->value = value;
    } else if (compare > 0) {
        entry->left = addEntry(entry->left, key, value);
        entry = entry->checkRightRotate();
    } else {
        entry->right = addEntry(entry->right, key, value);
        entry = entry->checkLeftRotate();
    }
    entry->calculateHeight();
    return entry;
}

template <class K, class V, class C>
typename AVLMap<K, V, C>::AVLMapEntry* AVLMap<K, V, C>::removeEntry(AVLMapEntry *entry, const K &key) {
    if (!entry) return NULL;
    int compare = comparator(entry->key, key);
    if (compare > 0) {
        entry->left = removeEntry(entry->left, key);
        entry = entry->checkLeftRotate();
    } else if (compare < 0) {
        entry->right = removeEntry(entry->right, key);
        entry = entry->checkRightRotate();
    } else {
        len--;
        if (!entry->left && !entry->right) {
            delete entry;
            return NULL;
        }
        if (!entry->left) {
            AVLMapEntry *right = entry->right;
            delete entry;
            return right;
        }
        if (!entry->right) {
            AVLMapEntry *left = entry->left;
            delete entry;
            return left;
        }
        AVLMapEntry *successor;
        if (AVLMapEntry::getEntryHeight(entry->right) < AVLMapEntry::getEntryHeight(entry->left)) {
            entry->left = removeRightMaxEntry(entry->left, &successor);
        } else {
            entry->right = removeLeftMinEntry(entry->right, &successor);
        }
        entry->key = successor->key;
        entry->value = successor->value;
        delete successor;
    }
    entry->calculateHeight();
    return entry;
}

template <class K, class V, class C>
typename AVLMap<K, V, C>::AVLMapEntry* AVLMap<K, V, C>::removeRightMaxEntry(AVLMapEntry *entry, AVLMapEntry **successor) {
    if (entry->right) {
        entry->right = removeRightMaxEntry(entry->right, successor);
        entry = entry->checkRightRotate();
        entry->calculateHeight();
        return entry;
    } else {
        *successor = entry;
        return entry->left;
    }
}

template <class K, class V, class C>
typename AVLMap<K, V, C>::AVLMapEntry* AVLMap<K, V, C>::removeLeftMinEntry(AVLMapEntry *entry, AVLMapEntry **successor) {
    if (entry->left) {
        entry->left = removeLeftMinEntry(entry->left, successor);
        entry = entry->checkLeftRotate();
        entry->calculateHeight();
        return entry;
    } else {
        *successor = entry;
        return entry->right;
    }
}

template <class K, class V, class C>
int AVLMap<K, V, C>::size() {
    return len;
}

template <class K, class V, class C>
bool AVLMap<K, V, C>::isEmpty() {
    return len <= 0;
}

template <class K, class V, class C>
void AVLMap<K, V, C>::put(const K &key, const V &value) {
    root = addEntry(root, key, value);
}

template <class K, class V, class C>
V AVLMap<K, V, C>::remove(const K &key) {
    root = removeEntry(root, key);
}

#endif //DATASTRUCTTREE_AVLMAP_HPP
