#include <jni.h>
#include <string>
#include "Log.h"

using namespace std;

#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>

#include "BinaryTree.hpp"
#include "BinarySortTree.hpp"
#include "AVLTree.hpp"
#include "AVLMap.hpp"

#include <set>
#include <map>
#include <algorithm>
#include <list>

extern "C" {


    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test0(JNIEnv *env, jobject /* this */) {
        TreeNode<char> *a = new TreeNode<char>('A');
        TreeNode<char> *b = new TreeNode<char>('B');
        TreeNode<char> *c = new TreeNode<char>('C');
        TreeNode<char> *d = new TreeNode<char>('D');
        TreeNode<char> *e = new TreeNode<char>('E');
        TreeNode<char> *f = new TreeNode<char>('F');
        TreeNode<char> *g = new TreeNode<char>('G');
        TreeNode<char> *h = new TreeNode<char>('H');
        TreeNode<char> *i = new TreeNode<char>('I');



        a->left = b; a->right = c;
        b->left = d;
        d->right = e; e->left = f;
        c->left = g; c->right = h;
        h->left = i;

        string str;
        BinaryTree::preOrderSerializer(a, str);
        LOGD("preOrder: %s", str.c_str());
        char *serializerStr = const_cast<char*>(str.c_str());
        TreeNode<char> *root = BinaryTree::deOrderSerializer(serializerStr);
        string cstr;
        BinaryTree::preOrderSerializer(root, cstr);
        LOGD("deOrderSerializer: %s", cstr.c_str());
        delete root;
        str.clear();

        BinaryTree::middleOrderSerializer(a, str);
        LOGD("middleOrder: %s", str.c_str());
        str.clear();

        BinaryTree::backOrderSerializer(a, str);
        LOGD("backOrder: %s", str.c_str());
        delete a;
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test1(JNIEnv *env, jobject /* this */) {
        BinarySortTree tree;
        tree.add(17);
        tree.add(17);
        tree.add(10);
        tree.add(16);
        tree.add(5);
        tree.add(30);
        tree.add(35);
        tree.add(19);
        tree.add(11);
        tree.add(8);
        tree.add(22);
        tree.add(18);

        tree.remove(5);

        tree.remove(30);
        tree.remove(10);
        tree.levelShow();

        LOGD("size: %d", tree.size());
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test2(JNIEnv *env, jobject /* this */) {
        AVLTree tree;
        tree.add(15);
        tree.add(8);
        tree.add(2);
        tree.add(40);
        tree.add(19);
        tree.add(4);
        tree.add(33);
        tree.add(22);
        tree.add(16);
        tree.add(7);
        tree.remove(8);
        tree.remove(15);
        tree.levelShow();
        LOGD("size: %d", tree.size());

    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test3(JNIEnv *env, jobject /* this */) {
        AVLTree tree;
        tree.add(20);
        tree.add(10);
        tree.add(40);
        tree.add(1);
        tree.add(15);
        tree.add(25);
        tree.add(50);
        tree.add(21);
        tree.add(30);

        tree.levelShow();

        tree.remove(20);

        tree.levelShow();

        tree.remove(21);
        tree.levelShow();

        map<string, string> ss;
        int va = ss.erase("abc");

        auto acc = ss.find("abc");

        ss.end();

    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test4(JNIEnv *env, jobject /* this */) {
        AVLMap<int, int> mapp;
        mapp.put(15, 16);
        mapp.put(16, 15);

        LOGD("AVLMap size %d", mapp.size());
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test5(JNIEnv *env, jobject /* this */) {


    }

    void test2() {
        
    }


    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test6(JNIEnv *env, jobject /* this */) {

    }

}

