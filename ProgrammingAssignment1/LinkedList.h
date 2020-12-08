#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: 
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T>& obj);

    ~LinkedList();

    Node<T>* getFirstNode() const;
    Node<T>* getLastNode() const;
    Node<T>* getNode(const T& data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T>* node) const;

    void insertAtTheHead(const T& data);
    void insertAtTheTail(const T& data);
    void insertSorted(const T& data);

    void removeNode(Node<T>* node);
    void removeNode(const T& data);
    void removeAllNodes();

    void print() const;

    T* toArray() const;

    LinkedList<T>& operator=(const LinkedList<T>& rhs);

private: 

private: 
    Node<T>* head;
    Node<T>* tail;
};

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize) {
    head = nullptr;
    tail = nullptr;
    for (int i = 0; i < arrSize; ++i) {
        insertAtTheTail(arr[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& obj) {


    head = nullptr;
    tail = nullptr;

    if (obj.head != nullptr) {
        Node<T>* traverse;
        traverse = obj.head;
        while (traverse) {
            insertAtTheTail(traverse->data);
            traverse = traverse->next;
        }
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    removeAllNodes();
}

template<class T>
Node<T>* LinkedList<T>::getFirstNode() const {
    return head;
}

template<class T>
Node<T>* LinkedList<T>::getLastNode() const {
    return tail;
}

template<class T>
Node<T>* LinkedList<T>::getNode(const T& data) const {
    T dat = data;
    Node<T>* current;
    current = head;

    while (current) {
        if (current->data == dat) {
            return current;
        }
        current = current->next;
    }
    return nullptr;

}

template<class T>
int LinkedList<T>::getNumberOfNodes() const {

    Node<T>* current = head;
    int count = 0;
    while (current) {
        count += 1;
        current = current->next;
    }
    current = nullptr;
    return count;



}

template<class T>
bool LinkedList<T>::isEmpty() const {
    if (head == nullptr)
        return true;
    return false;
}

template<class T>
bool LinkedList<T>::contains(Node<T>* node) const {
    T dat = node->data;
    Node<T>* current;
    current = head;

    while (current) {
        if (current->data == dat) {
            return true;
        }
        current = current->next;
    }
    return false;


}

template<class T>
void LinkedList<T>::insertAtTheHead(const T& data) {
    Node<T>* current;
    current = new Node<T>(data, nullptr, nullptr);

    if (head == nullptr) {
        head = current;
        tail = current;
        return;
    }

    current->next = head;
    head->prev = current;
    head = current;

}

template<class T>
void LinkedList<T>::insertAtTheTail(const T& data) {

    Node<T>* current;
    current = new Node<T>(data, nullptr, nullptr);

    if (head == nullptr) {
        head = current;
        tail = current;
        return;
    }

    current->prev = tail;
    tail->next = current;
    tail = current;
}

template<class T>
void LinkedList<T>::insertSorted(const T& data) {
    Node<T>* newNode, * current, * cur;
    current = nullptr;

    if (head == nullptr) {
        newNode = new Node<T>(data, nullptr, nullptr);
        head = newNode;
        tail = newNode;
        return;
    }

    if (head->data > data) {
        insertAtTheHead(data);
        return;
    }

    if (tail->data < data) {
        insertAtTheTail(data);
        return;
    }
    current = head;
    while (current->next) {

        if ((current->next->data) >= data) {
            newNode = new Node<T>(data, current, current->next);
            cur = current->next;
            cur->prev = newNode;
            current->next = newNode;
            return;
        }
        current = current->next;
    }

}

template<class T>
void LinkedList<T>::removeNode(Node<T>* node) {

    Node<T>* cur;
    cur = head;
    while (cur) {
        if (cur == node) {
            if (cur == head) {

                if (head == tail) {
                    delete cur;
                    head = nullptr;
                    tail = nullptr;
                    return;
                }
                else {
                    cur->next->prev = nullptr;
                    head = cur->next;
                    delete cur;
                    return;
                }
            }
            if (cur == tail) {
                cur->prev->next = nullptr;
                tail = cur->prev;
                delete cur;
                return;
            }
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
            return;
        }
        cur = cur->next;
    }
    return;


}

template<class T>
void LinkedList<T>::removeNode(const T& data) {

    Node<T>* cur;
    cur = head;
    while (cur) {
        if (cur->data == data) {

            if (cur == head) {
                if (head == tail) {

                    delete cur;
                    head = nullptr;
                    tail = nullptr;
                    return;
                }
                else {
                    (cur->next)->prev = nullptr;
                    head = (cur->next);
                    delete cur;
                    return;
                }
            }
            if (cur == tail) {
                (cur->prev)->next = nullptr;
                tail = (cur->prev);
                delete cur;
                return;
            }
            (cur->prev)->next = cur->next;
            (cur->next)->prev = cur->prev;
            delete cur;
            return;
        }
        cur = cur->next;
    }
    return;

}



template<class T>
void LinkedList<T>::removeAllNodes() {
    Node<T>* temp;

    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;

}

template<class T>
void LinkedList<T>::print() const {
    std::cout << "Printing the linked list ..." << std::endl;

    if (this->isEmpty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    Node<T>* node = this->head;

    while (node) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
T* LinkedList<T>::toArray() const {
    if (head == nullptr) {
        return nullptr;
    }
    int x = getNumberOfNodes(), i = 0;
    T* arr;
    arr = new T[x];
    Node<T>* cur;
    cur = head;
    while (cur) {
        arr[i++] = cur->data;
        cur = cur->next;
    }

    return arr;

}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    removeAllNodes();
    if (rhs.head == nullptr) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        head = nullptr;
        tail = nullptr;
        Node<T>* tmp;
        tmp = rhs.head;
        while (tmp) {
            insertAtTheTail(tmp->data);
            tmp = tmp->next;
        }
    }


}






















#endif //LINKEDLIST_H