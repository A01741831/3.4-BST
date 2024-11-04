/*                               Act 3.4 - Actividad Integral de BST
                                  (Evidencia en equipo Competencia)
                                Anna Sofía Ramírez Castro - A00574296
                                Vanessa Cerda Carrillo - A01612852
                                Ana Maria Rodriguez Peña - A01741831

                                                                                                4/11/2024 */
#include "Bitacora.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

Bitacora::Bitacora()
{
    size=0;
    root=nullptr;
}

string Bitacora::getKey(Registro dato, int count) {
    return dato.getIPnum()+"-"+to_string(count);
}

void Bitacora::leer()
{
    ifstream archivo;
    string linea;
    string mes;
    int dia;
    string hora;
    string IP;
    string razon;
    Nodo* ptr;
    string key;

    archivo.open("bitacora2.txt",ios::in);
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir";
        exit(1);
    }

    while (getline(archivo, linea)) {
        istringstream iss(linea);
        iss>>mes>>dia>>hora>>IP;
        getline(iss, razon);
        razon=razon.substr(1);
        Registro dato(mes,dia,hora,IP,razon);
        ptr=search(dato);
        if (ptr!=nullptr) { //si se repite
            ptr->count=(ptr->count)+1;
            key=getKey(dato,ptr->count);
            IPsRep[key]=dato;
            //IPsRep[dato.getIP()+"-"+to_string(ptr->count)]=dato;
        } else {
            bool inserted=insert(dato); //! comprobaci�n
            if (!inserted) {
                cout<<"Se encontro un elemento repetido en el arbol (no se aumento el counter)."<<endl;
                break;
            }
        }
    }

    archivo.close();
}

void Bitacora::archivoOrdenado()
{
    ofstream archivo;
    Registro aux;

    /*for (auto& par : IPsRep) {
        cout << par.first << " " << par.second.getIP() << endl;  // Salida: uno dos tres
        // first es la clave
    }*/

    archivo.open("bitacoraOrdenadaIP-Eq3-BST.txt",ios::out);
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir";
        exit(1);
    }

    inorder(root, archivo);

    archivo.close();
}

bool Bitacora::insert(Registro data)
{
    Nodo* current=root;
    Nodo* nvo=new Nodo(data);
    Nodo* padre;

    if (root==nullptr) {
        root=nvo;
        size++;
        return true;
    }

    while (current!=nullptr) {
        padre=current;
        if (data<current->data) {
            current=current->left;
        } else if (current->data<data) {
            current=current->right;
        } else {
            delete nvo;
            return false;
        }
    }

    if (data<padre->data) {
        padre->left=nvo;
    } else {
        padre->right=nvo;
    }
    size++;

    return true;
}

Nodo* Bitacora::search(Registro data)
{
    return search(data, root);
}

Nodo* Bitacora::search(Registro data, Nodo* current)
{
    if (current==nullptr || data==current->data) {
        return current;
    }
    else if (current->data<data) {
        return search(data, current->right);
    }
    else {
        return search(data, current->left);
    }
}

void Bitacora::inorder(Nodo* current, ofstream& archivo)
{
    Registro aux, aux2;
    string key;

    if (current!=nullptr) {
        inorder(current->left, archivo);

        aux=current->data;
        archivo<<aux.getMes()<<" "<<aux.getDia()<<" "<<aux.getHora()<<" "<<aux.getIP()<<" "<<aux.getRazon()<<" REPS "<<current->count<<endl; //! borrar cout<<count y el de abajo
        if (current->count>1) {
            for (int i=2;i<=(current->count);i++) {
                key=getKey(current->data,i);
                aux2=IPsRep[key];
                //aux2=IPsRep[aux.getIP()+"-"+to_string(i)];
                //cout<<(aux.getIP()+"-"+to_string(i))<<endl;
                archivo<<aux2.getMes()<<" "<<aux2.getDia()<<" "<<aux2.getHora()<<" "<<aux2.getIP()<<" "<<aux2.getRazon()<<" REPS "<<current->count<<endl;
            }
        }

        inorder(current->right, archivo);
    }
}

void Bitacora::TopIPs(int n){
    const int IPsImprimir=5;
    vector<pair<string, int>> topIPs;

    function<void(Nodo*)> recorrerArbol = [&](Nodo* current) {
        if (current != nullptr) {
            recorrerArbol(current->left);
            topIPs.push_back({current->data.getIPnum(), current->count});
            recorrerArbol(current->right);
        }
    };

    recorrerArbol(root);

    cout << "IPs registradas: " << topIPs.size() << endl;

    sort(topIPs.begin(), topIPs.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    cout << IPsImprimir << endl;
    for (int i = 0; i < min(IPsImprimir, (int)topIPs.size()); ++i) {
        cout << topIPs[i].first << " " << topIPs[i].second << endl;
    }
}

Bitacora::~Bitacora()
{
    /*while (head!=nullptr) {
        Nodo* temp=head;
        head=head->next;
        delete temp;
    }

    tail=nullptr;
    size=0;*/
}
