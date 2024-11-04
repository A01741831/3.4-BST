/*                               Act 3.4 - Actividad Integral de BST
                                  (Evidencia en equipo Competencia)
                                Anna Sofía Ramírez Castro - A00574296
                                Vanessa Cerda Carrillo - A01612852
                                Ana Maria Rodriguez Peña - A01741831

                                                                                                4/11/2024 */
#include "Registro.h"
#include <unordered_map>
#include <vector>
#ifndef BITACORA_H
#define BITACORA_H

struct Nodo {
    int count;
    Registro data;
    Nodo *left,
         *right;

    Nodo(Registro data){ // Complejidad: O(1) (constante)
        count=1;
        this->data=data;
        this->left=this->right=nullptr;
    }
};

class Bitacora
{
    private:
        int size;
        Nodo* root;
        unordered_map<string,Registro> IPsRep;
        string getKey(Registro dato, int count);
        void inorder(Nodo* current, ofstream& archivo);
        Nodo* search(Registro data, Nodo* current);

    public:
        Bitacora();

        void leer();
        void archivoOrdenado();
        bool insert(Registro data);
        Nodo* search(Registro data);
        void TopIPs(int n);

        virtual ~Bitacora(); //! es necesario?
};

#endif // BITACORA_H
