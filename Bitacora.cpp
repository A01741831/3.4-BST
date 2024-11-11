/*                               Act 3.4 - Actividad Integral de BST
                                  (Evidencia en equipo Competencia)
                                Anna Sofía Ramírez Castro - A00574296
                                Vanessa Cerda Carrillo - A01612852
                                Ana Maria Rodriguez Peña - A01741831

                                                                                                4/11/2024 */
#include "Bitacora.h"
#include "Registro.h"
#include <fstream>

Bitacora::Bitacora()
{
    size=0;
    head=tail=nullptr;
}

NodoLL* Bitacora::getHead()
{
    return head;
}

void Bitacora::insertLast(Registro data)
{
    NodoLL* nvo=new NodoLL(data);

    if (size==0) {
        head=nvo;
        tail=nvo;
    } else {
        tail->next=nvo;
        tail=nvo;
    }

    size++;
}

void Bitacora::mergeSort() {
    mergeIterativo(head);
}

NodoLL* Bitacora::mergeIterativo(NodoLL* head) {
    if (!head || !head->next) {
        return head;
    }

    NodoLL* dummy = new NodoLL(Registro());
    //dummy->next = head;

    /*int listLength = 0;
    for (NodoLL* current = head; current != nullptr; current = current->next) {
        listLength++;
    }*/

    for (int step = 1; step < size; step *= 2) {
        NodoLL* prev = dummy;
        NodoLL* current = dummy->next;

        while (current) {
            NodoLL* left = current;
            NodoLL* right = split(left, step);
            current = split(right, step);
            prev = mergeLists(prev, left, right);
        }
    }

    head = dummy->next;
    delete dummy;
    return head;
}

NodoLL* Bitacora::split(NodoLL* head, int step) {
    if (!head) return nullptr;
    NodoLL* current = head;
    for (int i = 1; head->next && i < step; i++) {
        head = head->next;
    }
    NodoLL* next = head->next;
    current->next=nullptr;
    //head->next = nullptr;
    return next;
}

NodoLL* Bitacora::mergeLists(NodoLL* prev, NodoLL* left, NodoLL* right) {
    NodoLL* current = prev;
    while (left && right) {
        if (left->data < right->data) {
            current->next = left;
            left = left->next;
        } else {
            current->next = right;
            right = right->next;
        }
        current = current->next;
    }
    current->next = (left)?left:right;

    while (current->next) {
        current = current->next;
    }
    return current;
}

void Bitacora::recorrer(ofstream& archivo)
{
    NodoLL* current=head;
    Registro aux;
    int count=0;

    while (current!=nullptr) {
        aux=current->data;
        archivo<<aux.getMes()<<" "<<aux.getDia()<<" "<<aux.getHora()<<" "<<aux.getIP()<<" "<<aux.getRazon()<<endl;
        current=current->next;
        count++;
    }

    //cout << "Registros recorridos: " << count << endl;
}

bool Bitacora::operator==(Registro val)
{
    NodoLL* current=head;

    while (current!=nullptr) {
        if (current->data==val) {
            return true;
        }
        current=current->next;
    }

    return false;
}

Bitacora::~Bitacora()
{
    while (head!=nullptr) {
        NodoLL* temp=head;
        head=head->next;
        delete temp;
    }

    tail=nullptr;
    size=0;
}
