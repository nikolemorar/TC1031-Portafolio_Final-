#ifndef _ADMINISTRAREGISTROS_H_
#define _ADMINISTRAREGISTROS_H_

#include "DLinkedList.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <limits>

template <class T>
class AdministraRegistros{
  private:
    DLinkedList<Registro> listaRegistros;
    DLinkedList<Registro> subListaRegistros;
    
  public:
    /*
     * Constructor sin parámetros de la clase AdministraRegistros.
     * Crea un objeto AdministraRegistros vacío.
     *
     * No posee parámetros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(1)
     */
        AdministraRegistros();

    /*
     * Constructor de la clase AdministraRegistros.
     * Carga los registros desde un archivo y los almacena en la lista de registros.
     *
     * Parámetros:
     * - direccionArch: La dirección del archivo que contiene los registros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(n), donde n es el número de registros en el archivo.
     */
        AdministraRegistros(std::string nombreArch);

    /*
     * Ordena los registros en la lista de registros.
     *
     * No posee parámetros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(n log n), donde n es el número de registros en la lista.
     */
        void sort();

    /*
     * Guarda los registros en una lista (la lista principal o la sublista) en un archivo.
     *
     * Parámetros:
     * - nombreArch: El nombre del archivo donde se guardarán los registros.
     * - tipoLista: Indica si se debe guardar la lista principal (valor 1) o la sublista (valor distinto de 1).
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(n), donde n es el número de registros en la lista seleccionada.
         */
        void saveList(std::string nombreArch, int tipoLista);

    /*
     * Imprime los registros de la sublista.
     *
     * No posee parámetros.
     *
     * No retorna ningún valor.
     *
     * Complejidad: O(k), donde k es el número de registros en la sublista.
     */
        void printList();

     /*
      * Obtiene una sublista de registros entre dos fechas dadas.
      *
      * Parámetros:
      * - fechaInicio: El nodo de inicio de la sublista.
      * - fechaFin: El nodo final de la sublista.
      *
      * No retorna ningún valor
      *
      * Complejidad: O(k), donde k es el número de registros en la sublista.
      */
        void getSublist(DLLNode<T> *fechaInicio, DLLNode<T> *fechaFin);


    /*
     * Solicita al usuario ingresar fechas y busca los nodos correspondientes en la lista de registros.
     *
     * Parámetros:
     * - intervalo: El número de intervalo de tiempo para el que se ingresa la fecha (1 para la primera fecha, 2 para la segunda).
     *
     * Retorna:
     * - Un puntero al nodo que contiene la fecha ingresada.   
     *
     * Complejidad: O(log n), donde n es el número de registros en la lista.
     */
        DLLNode<T>* ingresarDatos(int intervalo);
};

template <class T>
AdministraRegistros<T>::AdministraRegistros(){
}

template <class T> 
AdministraRegistros<T>::AdministraRegistros(std::string direccionArch){

    std::string mes, dia, horas, minutos, segundos, direccionIp, puerto, error;
    std::ifstream archivo(direccionArch);

    try{

        if (!archivo.is_open()){
            throw std::invalid_argument("No fue posible acceder al archivo. Verifique su existencia y comience de nuevo.");
        }

        else{

            while (std::getline(archivo, mes, ' ') &&
                   std::getline(archivo, dia, ' ') &&
                   std::getline(archivo, horas, ':') &&
                   std::getline(archivo, minutos, ':') &&
                   std::getline(archivo, segundos, ' ') &&
                   std::getline(archivo, direccionIp, ':') && 
                   std::getline(archivo, puerto, ' ') &&
                   std::getline(archivo, error))
            {
                Registro registroTemp(mes, dia, horas, minutos, segundos, direccionIp, puerto, error);
                listaRegistros.addLast(registroTemp);
            }

            archivo.close();
        }
    }

     catch (const std::exception &e){
        archivo.close();
        std::cout << "Error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <class T>
void AdministraRegistros<T>::sort(){
    listaRegistros.sort();
}

template <class T>
void AdministraRegistros<T>::saveList(std::string nombreArch, int tipoLista){
    if (tipoLista == 1){
        listaRegistros.saveList(nombreArch);
    }

    else{
        subListaRegistros.saveList(nombreArch);
    }
}

template <class T>
void AdministraRegistros<T>::printList(){
    subListaRegistros.printList();
}

template <class T>
void AdministraRegistros<T>::getSublist(DLLNode<T> *fechaInicio, DLLNode<T> *fechaFin){
    listaRegistros.getSublist(subListaRegistros, fechaInicio, fechaFin);

}

  
template <class T>
DLLNode<T>* AdministraRegistros<T>::ingresarDatos(int intervalo){
    std::string fechaIn, mesIn, diaIn, horasIn, minutosIn, segundosIn;

    if (intervalo == 1){
        std::cout << "******************************************************" << std::endl;
        std::cout << "* BUSQUEDA DE INFORMACION POR INTERVALO DE TIEMPO *" << std::endl;
        std::cout << "******************************************************" << std::endl;
        std::cout << "Instrucciones: ingrese la primera fecha como el siguiente ejemplo (Jun 01 00:22:36) ---> (mes dia hora:min:seg)" << std::endl;
    }

    else{
        std::cout << "\nIngrese la segunda fecha exactamente como se observa en el siguiente ejemplo (Jun 01 00:22:36) ---> (mes dia hora:min:seg)" << std::endl;
    }

    while (true) {

        try {
            std::cout << "Fecha numero " << intervalo << ": ";
            std::getline(std::cin, fechaIn);
            std::cout << std::endl;

            std::istringstream iss(fechaIn);

            if (!(std::getline(iss, mesIn, ' ') &&
                std::getline(iss, diaIn, ' ') &&
                std::getline(iss, horasIn, ':') &&
                std::getline(iss, minutosIn, ':') &&
                std::getline(iss, segundosIn))) {
                throw std::invalid_argument("Formato de fecha inválido.");
            }

            int dia = std::stoi(diaIn);
            int horas = std::stoi(horasIn);
            int minutos = std::stoi(minutosIn);
            int segundos = std::stoi(segundosIn);

            Registro fechaRegistrada(mesIn, diaIn, horasIn, minutosIn, segundosIn, "", "", "");
            DLLNode<T>* fechaNodo = listaRegistros.binarySearch(fechaRegistrada);

            if (fechaNodo == nullptr) {
                throw std::invalid_argument("Fecha no existente.");
            }

            return fechaNodo;
        }

        catch (const std::invalid_argument &e) {
            std::string errorMessage = e.what();

            if (errorMessage.compare("Formato de fecha inválido.") == 0) {
                std::cout << "Error: El formato de la fecha ingresada es inválido." << std::endl;
            }
            else if (errorMessage.compare("Fecha no existente.") == 0) {
                std::cout << "Error: La fecha ingresada no se encuentra en la bitácora." << std::endl;
            }
            else {
                std::cout << "Error: Ciertos valores de fecha ingresados no son numéricos." << std::endl;
            }

            std::cout << "\nIntente de nuevo. Presione enter para continuar... ";
            std::cin.ignore(); 

            for (int i = 0; i < 40; i++) {
                std::cout << std::endl;
            }
        }
  
    }
}

#endif //_ADMINISTRAREGISTROS_H_