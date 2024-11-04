/*                               Act 3.4 - Actividad Integral de BST
                                  (Evidencia en equipo Competencia)
                                Anna Sofía Ramírez Castro - A00574296
                                Vanessa Cerda Carrillo - A01612852
                                Ana Maria Rodriguez Peña - A01741831

                                                                                                4/11/2024 */

#include "Bitacora.h"
#include "Registro.h"
#include <iostream>

using namespace std;

int main()
{
    Bitacora datos;
    cout << "Leyendo datos." << endl;
    datos.leer();
    cout << "Creando archivo ordenado." << endl;
    datos.archivoOrdenado();
    cout << "Archivo ordenado listo." << endl;

    //Imprimir las 5 IPs con m�s accesos
    cout << "Las 5 IPs con más accesos son:" << endl;
    datos.TopIPs(5);

    return 0;
}
