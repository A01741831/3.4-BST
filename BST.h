

#ifndef BST_H
#define BST_H
class Bitacora;

#include "Bitacora.h"
#include "Registro.h"

struct Nodo {
    int count;
    Bitacora* lista;
    Nodo *left,
         *right;

    Nodo(Bitacora* lista){ //! Complejidad: O(1) (constante) ??????????????????????????????????????????????????????????????????????
        count=1;
        this->lista=lista;
        this->left=this->right=nullptr;
    }
};

class BST
{
    private:
        int size;
        Nodo* root;
        void inorder(Nodo* current, ofstream& archivo);
        Nodo* search(Registro data, Nodo* current);

    public:
        BST();

        void leer();
        void archivoOrdenado();
        bool insert(Registro data);
        Nodo* search(Registro data);
        void TopIPs(int n);

};

#endif // BST_H
