
#include "BST.h"
//#include "Bitacora.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;

BST::BST() //current->data = current->lista.getHead()->data
{
    size=0;
    root=nullptr;
}

void BST::leer()
{
    ifstream archivo;
    string linea;
    string mes;
    int dia;
    string hora;
    string IP;
    string razon;
    Nodo* ptr;
    //string key;

    archivo.open("bitacora2.txt",ios::in);
    if(archivo.fail()){
        //cout<<"El archivo no se pudo abrir";
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
            ptr->lista->insertLast(dato);
            //ptr->count=(ptr->count)+1;
            ptr->count += 1;

            /*key=getKey(dato);
            IPsRep[key].push_back(dato);*/
        } else {
            bool inserted=insert(dato); //! comprobación
            if (!inserted) {
                //cout<<"Se encontro un elemento repetido en el arbol (no se aumento el counter)."<<endl;
                break;
            }
        }
    }
    archivo.close();
}

void BST::archivoOrdenado()
{
    ofstream archivo;
    //Registro aux;
    //int cont=0;

    /*for (auto& par : IPsRep) {
        cont++;
        //cout << par.first << " " << par.second.getIP() << endl;  // Salida: uno dos tres
        // first es la clave
    }
    cout<<"Elementos en el mapa: "<<cont<<endl;*/

    archivo.open("bitacoraOrdenadaIP-Eq3-BST.txt",ios::out);
    if(archivo.fail()){
        //cout<<"El archivo no se pudo abrir";
        exit(1);
    }

    /*for (auto& par : IPsRep) {
        archivo << par.first << " " << par.second.getIP() << endl;  // Salida: uno dos tres
        // first es la clave
    }*/

    
    inorder(root, archivo);

    archivo.close();
}

bool BST::insert(Registro data)
{
    Bitacora* lista=new Bitacora();
    lista->insertLast(data);
    Nodo* current=root;
    Nodo* nvo=new Nodo(lista);
    Nodo* padre=nullptr;

    if (root==nullptr) {
        root=nvo;
        size++;
        return true;
    }

    while (current!=nullptr) {
        padre=current;

        if (data<current->lista->getHead()->data){
            current=current->left;
        }else if (current->lista->getHead()->data<data){
            current=current->right;
        } else {
            delete nvo;
            return false;
        }
    }
 
    if (data<padre->lista->getHead()->data){
        padre->left=nvo;
    } else {
        padre->right=nvo;
    }
    size++;

    return true;
}

Nodo* BST::search(Registro data)
{
    return search(data, root);
}

Nodo* BST::search(Registro data, Nodo* current)
{
    if (current==nullptr || data==current->lista->getHead()->data){
        return current;
    }

    else if (current->lista->getHead()->data<data){
        return search(data, current->right);
    }
    else {
        return search(data, current->left);
    }
}

void BST::inorder(Nodo* current, ofstream& archivo)
{
    //Bitacora* listaAux;

    if (current!=nullptr) {
        inorder(current->left, archivo);

        if(current->lista!=nullptr){
            current->lista->mergeSort();
            current->lista->recorrer(archivo);
        }else{
            //cout<<"Error: lista vacia"<<endl;
        }

       /*listaAux=current->lista;
        listaAux->mergeSort();
        listaAux->recorrer(archivo);*/

        /*if (current->count>1) {
            /*key=getKey(current->data);
            aux2=IPsRep[key];
            ordenarVec(aux2);END
            for (int i=0;i<aux2.size();i++) {
                archivo<<aux2[i].getMes()<<" "<<aux2[i].getDia()<<" "<<aux2[i].getHora()<<" "<<aux2[i].getIP()<<" "<<aux2[i].getRazon()<<" REPS "<<current->count<<endl;
            }
            /*for (int i=2;i<=(current->count);i++) {
                key=getKey(current->data,i);
                aux2=IPsRep[key];
                //aux2=IPsRep[aux.getIP()+"-"+to_string(i)];
                //cout<<(aux.getIP()+"-"+to_string(i))<<endl;
                archivo<<aux2.getMes()<<" "<<aux2.getDia()<<" "<<aux2.getHora()<<" "<<aux2.getIP()<<" "<<aux2.getRazon()<<" REPS "<<current->count<<endl;
            }END
        }*/

        inorder(current->right, archivo);
    }
}

void BST::TopIPs(int n){
    const int IPsImprimir=5;
    vector<pair<string, int>> topIPs;

    function<void(Nodo*)> recorrerArbol = [&](Nodo* current) {
        if (current != nullptr) {
            recorrerArbol(current->left);
            topIPs.push_back({current->lista->getHead()->data.getIPnum(), current->count});
            recorrerArbol(current->right);
        }
    };

    recorrerArbol(root);

    //cout << "IPs registradas: " << topIPs.size() << endl;

    sort(topIPs.begin(), topIPs.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    //cout << IPsImprimir << endl;
    for (int i = 0; i < min(IPsImprimir, (int)topIPs.size()); ++i) {
        cout << topIPs[i].first << " " << topIPs[i].second << endl;
    }
}
