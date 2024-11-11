/*                               Act 3.4 - Actividad Integral de BST
                                  (Evidencia en equipo Competencia)
                                Anna Sofía Ramírez Castro - A00574296
                                Vanessa Cerda Carrillo - A01612852
                                Ana Maria Rodriguez Peña - A01741831

                                                                                                4/11/2024 */

#ifndef BITACORA_H
#define BITACORA_H
#include "Registro.h"
#include "BST.h"
//#include "LinkedList.h"
#include <unordered_map>
#include <vector>

struct NodoLL {
    Registro data;
    NodoLL* next;

    NodoLL(Registro data, NodoLL* next) {
        this->data=data;
        this->next=next;
    }

    NodoLL(Registro data):NodoLL(data, nullptr) {}
};

class Bitacora
{
     private:
        int size;
        NodoLL* head;
        NodoLL* tail;
        NodoLL* mergeIterativo(NodoLL* head);
        NodoLL* split(NodoLL* head, int step);
        NodoLL* mergeLists(NodoLL* prev, NodoLL* left, NodoLL* right);

    public:
        Bitacora();

        NodoLL* getHead();
        void insertLast(Registro data);
        void mergeSort();
        int busqueda();
        void recorrer(ofstream& archivo);
        bool operator==(Registro val);

        virtual ~Bitacora();
};


#endif // BITACORA_H
