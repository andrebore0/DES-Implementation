# (En) DES-Implementation

This is a GitHub repository for an implementation of the Data Encryption Standard (DES) algorithm in C++20.\
DES is a symmetric-key block cipher algorithm that was widely used for encryption of electronic data in the 1970s and 1980s.

**The project is not a library and only provides binaries when built.**

## Building

To build with [CMake](https://cmake.org), follow these steps:

### Windows
* Clone the repository:
```
git clone https://github.com/andrebore04/DES-Implementation.git
cd DES-Implementation
```
* Create a folder inside the repository and cd into it:
```
mkdir build
cd build
```
* Configure and generate the buildfiles with CMake-gui or from the terminal:
```
[MinGW]
cmake ../ -G "MinGW Makefiles"

[Visual Studio]
cmake ../ -G "Visual Studio 17 2022"
```
* \[Visual Studio\] Open the project -> (Menu)Build -> Build Solution.
* \[MinGW\] From the terminal, build the project with make:
```
mingw32-make
```

### Linux
* Clone the repository:
```
git clone https://github.com/andrebore04/DES-Implementation.git
cd DES-Implementation
```
* Create a folder inside the repository and cd into it:
```
mkdir build
cd build
```
* Configure and generate the buildfiles:
```
cmake ../
```
* Build the project with make:
```
make
```

## Usage
The binaries can be executed with or without parameters, and you can pass parameters like so:
```
.\DES-Implementation (-encrypt|-decrypt) (-hex|-str) <input> <key>
```

## Acknowledgments
The DES algorithm was originally designed by *IBM* and was adopted by the *National Institute of Standards and Technology* (NIST) in 1977 as a federal standard for encryption.\
The implementation in this project is based on the description of the algorithm found at https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm.

---

# (It) Implementazione DES
Questa è una repository per un'implementazione dell'algoritmo Data Encryption Standard (DES) in C++20.\
Il DES è un'algoritmo di cifratura a blocchi a chiave simmetrica ampiamente utilizzato per la crittografia di dati elettronici negli anni '70 e '80.

**Il progetto non è una libreria e fornisce solo file binari quando viene compilato.**

## Compilazione
Per compilare il progetto con [CMake](https://cmake.org), seguire questi passaggi:

### Windows
* Clona la repository:
```
git clone https://github.com/andrebore04/DES-Implementation.git
cd DES-Implementation
```
* Crea una cartella ed entraci:
```
mkdir build
cd build
```
* Configura e genera i buildfiles con CMake-gui o dal terminale esegui:
```
[MinGW]
cmake ../ -G "MinGW Makefiles"

[Visual Studio]
cmake ../ -G "Visual Studio 17 2022"
```
* \[Visual Studio\] Apri il progetto -> (Menu)Compila -> Compila Soluzione.
* \[MinGW\] Dal terminale, compila il progetto con make:
```
mingw32-make
```

### Linux
* Clona la repository:
```
git clone https://github.com/andrebore04/DES-Implementation.git
cd DES-Implementation
```
* Crea una cartella ed entraci:
```
mkdir build
cd build
```
* Configura e genera i buildfiles:
```
cmake ../
```
* Compila il progetto con make:
```
make
```

## Utilizzo
Il file eseguibile può essere utilizzato con o senza parametri, l'ordine dei parametri è il seguente:
```
.\DES-Implementation (-encrypt|-decrypt) (-hex|-str) <input> <chiave>
```

## Riconoscimenti
L'algoritmo DES è stato originariamente progettato da *IBM* e adottato dal *National Institute of Standards and Technology* (NIST) nel 1977 come standard federale per la crittografia.\
L'implementazione in questo progetto si basa sulla descrizione dell'algoritmo trovata su https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm. 
