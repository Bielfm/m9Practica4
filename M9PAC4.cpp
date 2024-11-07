#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

// Estructura animales
struct Animal {
    string nombre;
    int velocidadBase;
    int posicion;
    thread* hilo;
};

// Funcion para mover un animal
void moverAnimal(Animal& animal, int meta, int tiempoPausa) {
    random_device rd;
    mt19937 gen(rd()); 

    // Distribuciones personalizadas para los animales
    uniform_int_distribution<> disTortuga(1, 2);  
    uniform_int_distribution<> disLeon(0, 3);  
    uniform_int_distribution<> disPuma(0, 4);  

    while (animal.posicion < meta) {
        if (animal.nombre == "Tortuga") {
            animal.posicion += disTortuga(gen);
        }
        else if (animal.nombre == "Leon") {
            animal.posicion += disLeon(gen);
        }
        else {
            animal.posicion += disPuma(gen);
        }

        this_thread::sleep_for(chrono::milliseconds(tiempoPausa));
    }
}

// Muestra la posición de los animales
void mostrarPosiciones(const vector<Animal>& animales, int meta) {
    system("cls"); // Limpia la pantalla
    for (int i = 0; i < meta; ++i) {
        cout << "-";
    }
    cout << endl;

    for (const Animal& animal : animales) {
        for (int i = 0; i < animal.posicion; ++i) {
            cout << " ";
        }
        cout << animal.nombre[0] << endl;
    }
}

int main() {
    const int meta = 50;
    const int tiempoPausa = 500; 

    vector<Animal> animales = { //Inicializamos con vector y velocidad inicial
        {"Tortuga", 1, 0},
        {"Leon", 5, 0},
        {"Puma", 3, 0}
    };

    // Crear los hilos
    for (Animal& animal : animales) {
        animal.hilo = new thread(moverAnimal, ref(animal), meta, tiempoPausa);
    }

    // Muestra la carrera
    while (true) {
        bool todosHanTerminado = true;
        for (const Animal& animal : animales) {
            if (animal.posicion < meta) {
                todosHanTerminado = false;
                break;
            }
        }
        if (todosHanTerminado) {
            break;
        }
        mostrarPosiciones(animales, meta);
        this_thread::sleep_for(chrono::milliseconds(tiempoPausa));
    }

    int maxPosicion = 0;
    string ganador;
    for (const Animal& animal : animales) {
        if (animal.posicion > maxPosicion) {
            maxPosicion = animal.posicion;
            ganador = animal.nombre;
        }
    }

    cout << "El ganador ha sido: " << ganador << endl;

    return 0;
}