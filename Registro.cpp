/*                               Act 3.4 - Actividad Integral de BST
                                  (Evidencia en equipo Competencia)
                                Anna Sofía Ramírez Castro - A00574296
                                Vanessa Cerda Carrillo - A01612852
                                Ana Maria Rodriguez Peña - A01741831

                                                                                                4/11/2024 */
#include "Registro.h"
#include <iostream>
#include <vector>
#include <algorithm>


Registro::Registro()
{
    mes="";
    dia=0;
    hora="";
    IP="";
    razon="";
    for (int i=0;i<5;i++) {
        IPnum[i]=0;
    }
}

Registro::Registro(string mes,int dia,string hora,string IP,string razon)
{
    this->mes=mes;
    this->dia=dia;
    this->hora=hora;
    this->IP=IP;
    this->razon=razon;
    IPANum(IP);
}

string Registro::getMes()
{
    return mes;
}

int Registro::getDia()
{
    return dia;
}

string Registro::getHora()
{
    return hora;
}

string Registro::getIP()
{
    return IP;
}

string Registro::getRazon()
{
    return razon;
}

string Registro::getIPnum()
{
    return to_string(IPnum[0])+"."+to_string(IPnum[1])+"."+to_string(IPnum[2])+"."+to_string(IPnum[3]);
}

void Registro::IPANum(string IPTemp)
{
    size_t IPsep[5];

    IPsep[0]=IPTemp.find(".");
    for (int i=1;i<3;i++) {
        IPsep[i]=IPTemp.find(".",IPsep[i-1]+1);
    }
    if (IPTemp.find(":")!=string::npos) {
        IPsep[3]=IPTemp.find(":");
    } else {
        IPsep[3]=0;
    }

    IPnum[0]=stoi(IPTemp.substr(0, IPsep[0]));
    for (int i=1;i<4;i++) {
        IPnum[i]=stoi(IPTemp.substr(IPsep[i-1]+1, IPsep[i]-IPsep[i-1]-1));
    }
    IPnum[4]=stoi(IPTemp.substr(IPsep[3]+1));
}

bool Registro::operator<(Registro val)
{
        for (int i=0;i<5;i++) {
            if (IPnum[i]!=val.IPnum[i]) {
                return IPnum[i]<val.IPnum[i];
            }
        }
    return false;
}

bool Registro::operator==(Registro val)
{
    for (int i=0;i<4;i++) {
        if (IPnum[i]!=val.IPnum[i]) {
            return false;
        }
    }
    return true;
}
