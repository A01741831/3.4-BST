/*                               Act 3.4 - Actividad Integral de BST
                                  (Evidencia en equipo Competencia)
                                Anna Sofía Ramírez Castro - A00574296
                                Vanessa Cerda Carrillo - A01612852
                                Ana Maria Rodriguez Peña - A01741831

                                                                                                4/11/2024 */
#ifndef REGISTRO_H
#define REGISTRO_H
#include <iostream>

using namespace std;

class Registro
{
    private:
        string mes;
        int dia;
        string hora;
        string IP;
        int IPnum[5];
        string razon;

    public:
        Registro();
        Registro(string mes,int dia,string hora,string IP,string razon);

        //gets
        string getMes();
        int getDia();
        string getHora();
        string getIP();
        string getRazon();
        string getIPnum();

        void IPANum(string IPTemp);
        bool operator<(Registro val);
        bool operator==(Registro val);

};

#endif // REGISTRO_H
