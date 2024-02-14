#include <QCoreApplication>
#include <iostream>

#include "singleton/misingleton.h"
#include "thread"

// Instanciamos el singleton con el valor FOO
void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

// Instanciamos el singleton con el valor BAR
void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

/*
Ejemplo de: (Usando QT 5.12)
https://refactoring.guru/es/design-patterns/singleton/cpp/example#example-1--Output-txt
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "#### INICIO PROGRAMA ####" << std::endl;

    std::cout <<"Si ves los mismos valores el Singleton funciona bien con hilos\n" <<
                "Si ves los valores DIFERENTES VA MAL!!!\n\n" <<
                "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return a.exec();
}
