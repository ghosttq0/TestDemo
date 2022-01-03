//
//  algorithm.cpp
//  cplusplus_test_ios
//
//  Created by 田奇 on 2021/12/22.
//  Copyright © 2021 tianqi. All rights reserved.
//

#include "algorithm.hpp"
#include <map>
#include <unordered_map>
#include <iostream>

void swap(int a[], int i, int j) {
    if (i >= j) {
        return;
    }
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
void QuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int tmp = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= tmp)     // 从右向左找第一个小于k的数
            {
                j--;
            }
 
            if (i < j) {
                arr[i] = arr[j];
                i++;
            }
            while(i < j && arr[i] < tmp)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }
            if (i < j) {
                arr[j] = arr[i];
                j--;
            }
        }
        arr[i] = tmp;
 
        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}

void algorithm_quick_sort() {
    int a[8] = {1,9,2,8,3,7,4,6};
    printf("a = {%d, %d, %d, %d, %d, %d, %d, %d}\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
    QuickSort(a, 0, 7);
    printf("a = {%d, %d, %d, %d, %d, %d, %d, %d}\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
}

void algorithm_colum_row() {
    int N = 5;
    int M = 3;
    long long sum = N*N;
    int colNum = 0;
    int rowNum = 0;
    int col[5] = {0};
    int row[5] = {0};
    int x = 0;
    int y = 0;
    int m = M;
    while (m--) {
        x = m;
        y = m;
        if (!row[x]) {
            sum -= N - rowNum;
        }
        if (!col[y]) {
            sum -= N - colNum;
        }
        if (!row[x] && !col[y]) {
            sum++;
        }
        if (!row[x]) {
            rowNum++;
            row[x] = 1;
        }
        if (!col[y]) {
            colNum++;
            col[y] = 1;
        }
    }
    printf("N = %d, M = %d, col*row = %lld", N, M, sum);
}

struct Node {
    int data;
    struct Node* next;
    Node():data(0),next(nullptr) {
        
    }
    Node(int val):data(val),next(nullptr){
        
    };
};

Node* link_merge(Node* h1, Node*h2) {
    if (!h1) {
        return h2;
    }
    if (!h2) {
        return h1;
    }
    
    Node* head = nullptr;
    Node* tail = nullptr;
    if (h1->data < h2->data) {
        head = h1;
        tail = head;
        h1 = h1->next;
    } else {
        head = h2;
        tail = head;
        h2 = h2->next;
    }
    
    while (h1 && h2) {
        if (h1->data < h2->data) {
            tail->next = h1;
            tail = h1;
            h1 = h1->next;
        } else {
            tail->next = h2;
            tail = h2;
            h2 = h2->next;
        }
    }
    
    if (!h1) {
        tail->next = h2;
    }
    if (!h2) {
        tail->next = h1;
    }
    
    return head;
}

void print_link(Node* h) {
    if (h == nullptr) {
        return;
    }
    while (h) {
        printf("->data = %d\n", h->data);
        h = h->next;
    }
}

void delete_link(Node *h) {
    
}

void algorithm_sortlink_merge() {
    Node* h1 = new Node(2);
    h1->next = new Node(4);
    h1->next->next = new Node(6);
    h1->next->next->next = new Node(8);
    Node* h2 = new Node(1);
    h2->next = new Node(3);
    h2->next->next = new Node(5);
    h2->next->next->next = new Node(7);
    Node* head = link_merge(h1, h2);
    print_link(head);
    delete_link(head);
}

Node* link_cross(Node* h1, Node* h2) {
    int count1 = 0;
    int count2 = 0;
    Node* p1 = h1;
    Node* p2 = h2;
    while (p1) {
        p1 = p1->next;
        count1++;
    }
    while (p2) {
        p2 = p2->next;
        count2++;
    }
    int step1 = 0, step2 = 0;
    if (count1 > count2) {
        step1 = count1 - count2;
    } else {
        step2 = count2 - count1;
    }
    
    p1 = h1;
    if (step1 > 0) {
        while (step1--) {
            p1 = p1->next;
        }
    }
    
    p2 = h2;
    if (step2 > 0) {
        while (step2--) {
            p2 = p2->next;
        }
    }
    
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    
    return p1;
}

void algorithm_link_cross() {
    Node* h1 = new Node();
    h1->next = new Node(5);
    Node* h2 = new Node();
    h2->next = new Node();
    h2->next->next = h1->next;
    Node* cross_link = link_cross(h1, h2);
    printf("cross link = %d\n", cross_link->data);
}

class LRUCache {
public:
    struct DLinkedNode {
        DLinkedNode():key(0), value(-1), pre(nullptr), post(nullptr) {
        };
        int key;
        int value;
        DLinkedNode* pre;
        DLinkedNode* post;
    };
public:
    LRUCache(int capacity):capacity_(capacity), count_(0) {
        header_ = new DLinkedNode();
        tail_ = new DLinkedNode();
        header_->post = tail_;
        tail_->pre = header_;
    }
    void put(int key, int value) {
        DLinkedNode* node = cache_[key];
        if (node) {
            node->value = value;
            moveToHeader(node);
            return;
        }
        
        node = new DLinkedNode();
        node->key = key;
        node->value = value;
        
        cache_[key] = node;
        addNode(node);
        if (count_ > capacity_) {
            popTail();
        }
    }
    int get(int key) {
        DLinkedNode* dNode = cache_[key];
        if (!dNode) {
            printf("Finde key = %d failed!\n",key);
            return -1;
        }
        moveToHeader(dNode);
        return dNode->value;
    }
    void print_all() {
        DLinkedNode* cur = header_->post;
        printf("Header->");
        while (cur != tail_) {
            printf("node(%d,%d)->",cur->key,cur->value);
            cur = cur->post;
        }
        printf("Tailer\n");
    }
private:
    void addNode(DLinkedNode* node) {
        DLinkedNode* post = header_->post;
        node->post = post;
        post->pre = node;
        node->pre = header_;
        header_->post = node;
        count_++;
        printf("add node %d\n", node->value);
    }
    void removeNode(DLinkedNode* node) {
        DLinkedNode* post = node->post;
        DLinkedNode* pre = node->pre;
        post->pre = pre;
        pre->post = post;
        count_--;
        printf("remove node %d\n", node->value);
    }
    void moveToHeader(DLinkedNode* node) {
        removeNode(node);
        addNode(node);
    }
    void popTail() {
        DLinkedNode* pre = tail_->pre;
        removeNode(pre);
    }
    
    int capacity_;
    int count_;
    std::unordered_map<int, DLinkedNode*> cache_;
    DLinkedNode* header_;
    DLinkedNode* tail_;
};

void algorithm_lru() {
    LRUCache* cache = new LRUCache(5);
    cache->get(1);
    cache->get(2);
    cache->put(1, 31);
    cache->print_all();
    cache->put(1, 21);
    cache->print_all();
    cache->put(2, 32);
    cache->print_all();
    cache->put(3, 33);
    cache->print_all();
    cache->put(4, 34);
    cache->print_all();
    cache->put(5, 35);
    cache->print_all();
    cache->put(6, 36);
    cache->print_all();
}

int bit_1_count(uint8_t num) {
    int count = 0;
    while (num) {
        num &= num - 1;
        count++;
    }
    return count;
}

void algorithm_bit_1_count() {
    int8_t num = 0xff;
    int count = bit_1_count(num);
    printf("Bit 1 count = %d\n",count);
}
