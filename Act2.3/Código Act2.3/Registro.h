#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <ctime>
#include <vector>
#include <fstream>

class Registro{

    private:
        std::string mes, dia, horas, minutos, segundos, direccionIp, puerto, error;
        std::vector<std::string> meses{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        struct tm estructuraFecha;
        time_t tiempoTranscurrido;

    public:
        /*
         * Constructor sin parámetros de la clase Registro.
         * Crea un registro vacío sin asignar valores específicos.
         *
         * No posee parámetros.
         *
         * No retorna ningún valor.
         *
         * Complejidad Temporal: O(1)
         */
        Registro();

        /*
         * Constructor con parámetros de la clase. Realiza la inicialización de un objeto
         * de la clase Registro, asignando valores a sus variables miembro, convirtiendo
         * ciertos camposs a formatos numéricos y calculando el tiempo transcurrido
         * correspndiente a la fecha y hora proporcionados..
         *
         * Parámetros:
         * - pMes: El mes del registro.
         * - pDia: El día del registro.
         * - pHoras: Las horas del registro.
         * - pMinutos: Los minutos del registro.
         * - pSegundos: Los segundos del registro.
         * - pDireccionIp: La dirección IP del registro.
         * - pPuerto: El puerto del registro.
         * - pError: El error del registro.
         *
         * No retorna ningún valor.
         *
         * Complejidad Temporal: O(1)
         */
        Registro(std::string pMes, std::string pDia, std::string pHoras, std::string pMinutos, std::string pSegundos, std::string pDireccionIp, std::string pPuerto, std::string pError);

        /*
         * Obtiene el tiempo transcurrido del registro en formato de tiempo UNIX.
         *
         * No posee parámetros.
         *
         * Retorna:
         * - El tiempo transcurrido del registro en formato de tiempo UNIX.
         *
         * Complejidad Temporal: O(1)
         */
        time_t obtenerTiempo();

        /*
         * Imprime los datos del registro en formato de cadena.
         *
         * No posee parámetros.
         *
         * Retorna:
         * - Los datos del registro en formato de cadena.
         *
         * Complejidad Temporal: O(1)
         */
        std::string imprimirDatos();

      /*
       * Sobrecarga de diversos operadores que permite comparar dos objetos 
       * de la clase Registro basándose en el atributo tiempoTranscurrido.
       * 
       * @other, su único parámetro es una referencia constante a otro objeto de la
       * clase Registro, y se utiliza para comparar el atributo tiempoTranscurrrido
       * del objeto actual con el del objeto pasado como argumento other.
       * 
       * Complejidad temporal de cada uno: O(1)
       */
        bool operator==(const Registro &other) const;
        bool operator!=(const Registro &other) const;
        bool operator>(const Registro &other) const;
        bool operator<(const Registro &other) const;
        bool operator>=(const Registro &other) const;
        bool operator<=(const Registro &other) const;
};

Registro::Registro(){  
    mes = "";
    dia = "";
    horas = "";
    minutos = "";
    segundos = "";
    direccionIp = "";
    puerto = "";
    error = "";
    tiempoTranscurrido = 0;
}

Registro::Registro(std::string pMes, std::string pDia, std::string pHoras, std::string pMinutos, std::string pSegundos, std::string pDireccionIp, std::string pPuerto, std::string pError){
    mes = pMes;
    dia = pDia;
    horas = pHoras;
    minutos = pMinutos;
    segundos = pSegundos;
    direccionIp = pDireccionIp;
    puerto = pPuerto;
    error = pError;

    estructuraFecha.tm_hour = std::stoi(horas);
    estructuraFecha.tm_min = std::stoi(minutos);
    estructuraFecha.tm_sec = std::stoi(segundos);
    estructuraFecha.tm_mday = std::stoi(dia);
    estructuraFecha.tm_isdst = 0;

    for (int i = 0; i < (int)meses.size(); i++){

        if (meses[i] == mes)
            estructuraFecha.tm_mon = i;
    }

    estructuraFecha.tm_year = 2023 - 1900;
    tiempoTranscurrido = mktime(&estructuraFecha);
}

time_t Registro::obtenerTiempo(){
    return tiempoTranscurrido;
}

std::string Registro::imprimirDatos(){
    return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + direccionIp + ":" + puerto + " " + error;
}

bool Registro::operator==(const Registro &other) const{
    return this->tiempoTranscurrido == other.tiempoTranscurrido;
}

bool Registro::operator!=(const Registro &other) const{
    return this->tiempoTranscurrido != other.tiempoTranscurrido;
}

bool Registro::operator>(const Registro &other) const{
    return this->tiempoTranscurrido > other.tiempoTranscurrido;
}

bool Registro::operator<(const Registro &other) const{
    return this->tiempoTranscurrido < other.tiempoTranscurrido;
}

bool Registro::operator>=(const Registro &other) const{
    return this->tiempoTranscurrido >= other.tiempoTranscurrido;
}

bool Registro::operator<=(const Registro &other) const{
    return this->tiempoTranscurrido <= other.tiempoTranscurrido;
}

#endif //_REGISTRO_H_
