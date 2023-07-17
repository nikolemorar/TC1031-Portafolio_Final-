#ifndef _DOUBLELINKEDLIST_H_
#define _DOUBLELINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "DLLNode.h"
#include "Registro.h"

template <class T>
class DLinkedList{

private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;
    void quicksort(DLLNode<T> *low, DLLNode<T> *high);
    void swap(T *a, T *b);
    DLLNode<T> *particion(DLLNode<T> *low, DLLNode<T> *high);
    DLLNode<T> *medio(DLLNode<T> *start, DLLNode<T> *last);

public:
    /*
     * Constructor sin parámetros de la clase DLinkedList.
     * Crea una lista enlazada doble vacía.
     *
     * No posee parámetros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(1)
     */
    DLinkedList();

    /*
     * Destructor de la clase DLinkedList.
     * Libera la memoria ocupada por los nodos de la lista enlazada.
     *
     * No posee parámetros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(n), donde n es el número de nodos en la lista.
     */
    ~DLinkedList();

    /*
     * Agrega un nuevo nodo al inicio de la lista enlazada.
     *
     * Parámetros:
     * - value: El valor a agregar al nuevo nodo.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(1)
     */
    void addFirst(T value);


    /*
     * Agrega un nuevo nodo al final de la lista enlazada.
     *
     * Parámetros:
     * - value: El valor a agregar al nuevo nodo.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(1)
     */
    void addLast(T value);

    /*
     * Obtiene el número de elementos en la lista enlazada.
     *
     * No posee parámetros.
     *
     * Retorna:
     * - El número de elementos en la lista.
     *
     * Complejidad: O(1)
     */
    int getNumElements();

    /*
     * Imprime los elementos de la lista enlazada.
     *
     * No posee parámetros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(n), donde n es el número de nodos en la lista.
     */
    void printList();


    /*
     * Guarda los elementos de la lista enlazada en un archivo.
     *
     * Parámetros:
     * - nombreArch: El nombre del archivo donde se guardarán los elementos.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(n), donde n es el número de nodos en la lista.
     */
    void saveList(std::string nombreArch);

    /*
     * Realiza una búsqueda binaria en la lista enlazada para encontrar un valor específico.
     *
     * Parámetros:
     * - fechaBuscada: El valor a buscar en la lista.
     *
     * Retorna:
     * - Un puntero al nodo que contiene el valor buscado, o nullptr si no se encuentra.
     *
     * Complejidad: O(log n), donde n es el número de nodos en la lista.
     */
    DLLNode<T>* binarySearch(T fechaBuscada);

    /*
     * Ordena los elementos de la lista enlazada utilizando el algoritmo de ordenación QuickSort.
     *
     * No posee parámetros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(n log n), donde n es el número de nodos en la lista.
     */
    void sort();

    /*
     * Obtiene una sublista de la lista enlazada entre dos nodos dados.
     *
     * Parámetros:
     * - newList: La lista enlazada donde se almacenarán los nodos de la sublista.
     * - fechaInicio: El nodo de inicio de la sublista.
     * - fechaFin: El nodo de fin de la sublista.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(k), donde k es el número de nodos en la sublista.
     */
    void getSublist(DLinkedList<T> &newList, DLLNode<T> *fechaInicio, DLLNode<T> *fechaFin);
};

template <class T>
DLinkedList<T>::DLinkedList(){
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

template <class T>
DLinkedList<T>::~DLinkedList(){

    DLLNode<T> *p, *q;
    p = head;

    while (p != nullptr){
        q = p->next;
        delete p;
        p = q;
    }

    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

template <class T>
void DLinkedList<T>::addFirst(T value){

    DLLNode<T> *newNode = new DLLNode<T>(value);

    if (head == nullptr && tail == nullptr){
        head = newNode;
        tail = newNode;
    }

    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    numElements++;
}

template <class T>
void DLinkedList<T>::addLast(T value){

    if (head == nullptr && tail == nullptr){
        addFirst(value);
    }

    else{
        DLLNode<T> *newNode = new DLLNode<T>(value);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        numElements++;
    }
}

template <class T>
int DLinkedList<T>::getNumElements(){
    return numElements;
}

template <class T>
void DLinkedList<T>::printList(){

    if (head == nullptr && tail == nullptr){
        std::cout << "La lista esta vacia" << std::endl;
    }

    else{
        std::cout << "Presione [ENTER] para mostrar el contenido de la lista... ";
        std::cin.ignore();
        DLLNode<T> *p = head;

        while (p != nullptr){
            std::cout << p -> data.imprimirDatos() << std::endl;
            p = p -> next;
        }

        std::cout << std::endl;
    }
}

template <class T>
void DLinkedList<T>::saveList(std::string nombreArch){
    std::ofstream archivo(nombreArch);

    try{
        if (!archivo.is_open()){
            throw std::invalid_argument("No fue posible acceder al archivo.");
        }

        else{
            DLLNode<T> *p = head;

            while (p != nullptr){
                archivo << p -> data.imprimirDatos() << std::endl;
                p = p->next;
            }

            archivo.close();
            std::cout << "La bitacora ha sido guardada con exito en el archivo " << nombreArch << std::endl;
        }
    }

    catch (const std::exception &e){
        archivo.close();
        std::cout << "Error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <class T>
DLLNode<T>* DLinkedList<T>::binarySearch(T fechaBuscada){
    DLLNode<T> *start = head;
    DLLNode<T> *last = nullptr;

    do{
        DLLNode<T> *mid = medio(start, last);
        if (mid == nullptr){
            return nullptr;
        }
           
        if (mid->data ==fechaBuscada){
            std::cout << "¡Se encontro con exito la entrada ingresada!" << std::endl;
            return mid;
        }

        else if (mid->data < fechaBuscada){

            start = mid->next;
        }

        else{
            last = mid;
        }

    } while (last == nullptr || last != start);

    return nullptr;
}

template <class T>
DLLNode<T> *DLinkedList<T>::medio(DLLNode<T> *start, DLLNode<T> *last){
   
    if (start == nullptr){
        return nullptr;
    }

    DLLNode<T> *slow = start;
    DLLNode<T> *fast = start->next;

    while (fast != last){
        fast = fast->next;

        if (fast != last){
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

template <typename T>
void DLinkedList<T>::swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <class T>
void DLinkedList<T>::quicksort(DLLNode<T> *low, DLLNode<T> *high){

    if (high != nullptr && low != high && low != high->next){
        DLLNode<T> *pivot = particion(low, high);
        quicksort(low, pivot->prev);
        quicksort(pivot->next, high);
    }
}

template <class T>
void DLinkedList<T>::sort(){
    quicksort(head, tail);
}

template <class T>
DLLNode<T>* DLinkedList<T>::particion(DLLNode<T> *low, DLLNode<T> *high){
    T pivot = high->data;
    DLLNode<T> *i = low->prev;

    for (DLLNode<T> *j = low; j != high; j = j->next){

        if (j->data <= pivot){
            i = (i == nullptr) ? low : i->next;
            swap(&(i->data), &(j->data));
        }
    }

    i = (i == nullptr) ? low : i->next;
    swap(&(i->data), &(high->data));
    return i;
}


template <class T>
void DLinkedList<T>::getSublist(DLinkedList<T> &newList, DLLNode<T> *fechaInicio, DLLNode<T> *fechaFin){
    DLLNode<T> *p = fechaInicio;
    int registros = 0;

    while (p != nullptr && p -> data <= fechaFin -> data){
        DLLNode<T> *q = p->next;
        newList.addLast(p -> data);
        registros++;
        p = q;
    }

    std::cout << "\nSe encontraron " << registros << " registros en la bitacora.\n" << std::endl;

}
#endif // _DOUBLELINKEDLIST_H_
