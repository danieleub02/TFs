#include <iostream>
#include <functional>
#include <conio.h> 
#include <fstream>
#include <string>
#include <ctime>
#include <array>
#include <list>
#include <vector>
#include <sstream>
using namespace std;

//-----------------------------------------------------------------------------

namespace DataStructure {

    template<class Generico>
    class Nodo_T {
    public:
        Generico elemento;
        Nodo_T<Generico>* izq;
        Nodo_T<Generico>* der;
        Nodo_T(Generico e) {
            elemento = e;
            izq = nullptr;
            der = nullptr;
        }
        void setElemento(Generico g) { elemento = g; }
    };

    template<class Generico>
    class Arbol {
    private:
        Nodo_T<Generico>* raiz;
        size_t cantidad;
        function<void(Generico)> show;
        function<bool(Generico, Generico)> compare;
        function<size_t(Generico, Generico)> doSomething;
    public:
        Nodo_T<Generico>* GetRaiz() { return raiz; }
        void setElemento(Generico a, Nodo_T<Generico>*& tmp) { tmp->elemento; }
        Arbol(function<void(Generico)> show,
            function<bool(Generico, Generico)> compare,
            function<size_t(Generico, Generico)> doSomething) :
            show(show), compare(compare), doSomething(doSomething) {
            raiz = nullptr;
            cantidad = 0;
        }
        void setFunction(function<void(Generico)> a, function<bool(Generico, Generico)> b, function<size_t(Generico, Generico)> c) {
            show = a; compare = b; doSomething = c;
        }
        void insert(Generico e) { insert(e, raiz); }
        void insert(Generico g, Nodo_T<Generico>*& tmp) {
            if (tmp == nullptr)
                tmp = new Nodo_T<Generico>(g);
            else if (compare(g, tmp->elemento))
                insert(g, tmp->der);
            else
                insert(g, tmp->izq);
        }
        void replaceElement(Generico e) { replaceElement(e, raiz); }
        void replaceElement(Generico g, Nodo_T<Generico>*& tmp) {
            if (tmp != NULL)
            {
                if (doSomething(g, tmp->elemento) == 0)
                    setElemento(g, tmp);
                else if (doSomething(g, tmp->elemento) == -1)
                    replaceElement(g, tmp->izq);
                else if (doSomething(g, tmp->elemento) == 1)
                    replaceElement(g, tmp->der);
            }
        }
        void print() { print(raiz); }
        void print(Nodo_T<Generico>* tmp) {//enOrden
            if (tmp == nullptr)return;
            print(tmp->izq);
            show(tmp->elemento);
            print(tmp->der);
        }
        Generico search(Generico g) { return search(g, raiz); }
        Generico search(Generico g, Nodo_T<Generico>*& tmp) {
            if (tmp != NULL)
            {
                if (doSomething(g, tmp->elemento) == 0) {
                    return tmp->elemento;
                }
                else if (doSomething(g, tmp->elemento) == -1) return search(g, tmp->izq);
                else if (doSomething(g, tmp->elemento) == 1) return search(g, tmp->der);
                else {
                    return g;
                }
            }
        }
    };

    template<class Generico>
    class Nodo {
    public:
        Generico elemento;
        Nodo<Generico>* sig;
        Nodo(Generico e) {
            elemento = e;
            sig = nullptr;
        }
    };

    template<class Generico>
    class Lista {
    private:
        Nodo<Generico>* inicio;
        Nodo<Generico>* fin;
        size_t cantidad;
        function<void(Generico)> show;
    public:
        Lista(function<void(Generico)> show) : show(show) {
            inicio = fin = nullptr;
            cantidad = 0;
        }
        Nodo<Generico>* getInicio() { return inicio; }
        void push_front(Generico e) {
            Nodo<Generico>* n = new Nodo<Generico>(e);
            if (cantidad == 0)
                inicio = n;
            else {
                n->sig = inicio;
                inicio = n;
            }
            ++cantidad;
        }
        void push_back(Generico e) {
            Nodo<Generico>* nuevo = new Nodo<Generico>(e);
            if (inicio == nullptr)//cantidad==0
                inicio = fin = nuevo;
            else {
                fin->sig = nuevo;
                fin = nuevo;
            }
            cantidad++;
        }
        void search(size_t n) {
            Nodo<Generico>* aux = inicio;
            size_t c = 0;
            if (inicio == nullptr || n <= 0 || n - 1 >= cantidad)
                return;
            while (c != n - 1)
            {
                aux = aux->sig;
                c++;
            }
            show(aux->elemento);
        }
        void delete_front() {
            if (inicio == nullptr)
                return;
            else
                inicio = inicio->sig;
        }
        void delete_back() {
            Nodo<Generico>* aux = inicio;
            if (inicio == nullptr)
                return;
            if (inicio->sig == nullptr) {
                inicio = nullptr;
                return;
            }
            while (aux->sig->sig != nullptr)
                aux = aux->sig;
            aux->sig = nullptr;
        }
        void delete_by_position(size_t n) {
            Nodo<Generico>* aux = inicio;
            int c = 0;
            while (c != n - 1) {
                aux = aux->sig;
                c++;
            }
            if (aux->sig->sig == nullptr) {
                aux->sig = nullptr;
            }
            else {
                aux->sig = aux->sig->sig;
            }
            cantidad--;
            cout << "Elemento eliminado!" << endl;
            print();
        }
        void print() {
            Nodo<Generico>* aux = inicio;
            while (aux != nullptr) {
                show(aux->elemento);
                aux = aux->sig;
            }
        }
    };

    template<class Generico1, class Generico2>
    class Entity {
        Generico1 key;
        Generico2 value;
    public:
        Entity(Generico1 k, Generico2 v) : key(k), value(v) {}
        Generico1 getG1() { return key; }
        Generico2 getG2() { return value; }
    };

    template<class Generico1, class Generico2>
    class HT {
        array < list<Entity<Generico1, Generico2>>, 5 > container;
        function<void(Generico1, Generico2)> show;
        function<int(Generico1)> index;
    public:
        HT(function<void(Generico1, Generico2)> show, function<int(Generico1)> index) : show(show), index(index) { }
        int getIndex(Generico1 key) { return index(key); }
        array < list<Entity<Generico1, Generico2>>, 5 > getContainer() { return container; }
        void setContainer(array < list<Entity<Generico1, Generico2>>, 5 > c) { container = c; }
        void add(Generico1 key, Generico2 value) {
            container[getIndex(key)].push_back(Entity<Generico1, Generico2>(key, value));
        }
        void display() {
            for (size_t i = 0; i < container.size(); ++i) {//recorre el array
                for (auto it : container[i]) {
                    cout << "\t\t\t";
                    show(it.getG1(), it.getG2());
                }
            }
        }
        void deleteg(Generico1 key) {
            HT<Generico1, Generico2> aux(show, index);
            for (size_t i = 0; i < container.size(); ++i) {//recorre el array
                for (auto it : container[i]) {
                    if (it.getG1() != key)
                    {
                        aux.add(it.getG1(), it.getG2());
                    }
                }
            }
            this->setContainer(aux.getContainer());
        }
    };

    template<class Generico1, class Generico2>
    class Map {
        vector<Entity<Generico1, Generico2>> Diccionary;
        function<void(Generico1, Generico2)> show;
    public:
        Map(function<void(Generico1, Generico2)> show) : show(show) { }
        void insert(Generico1 a, Generico2 b) {

            Entity<Generico1, Generico2> aux(a, b);
            Diccionary.push_back(aux);

        }

        void deleteByKey(Generico1 a) {
            for (size_t i = 0; i < Diccionary.size(); i++)
            {
                if (a == Diccionary.at(i).getG1())
                {
                    Diccionary.erase(Diccionary.begin() + i);
                }
            }
        }
        void print() {
            for (size_t i = 0; i < Diccionary.size(); i++)
                show(Diccionary.at(i).getG1(), Diccionary.at(i).getG2());
        }
        void showValue(Generico1 key) {
            for (size_t i = 0; i < Diccionary.size(); i++)
            {
                if (key == Diccionary.at(i).getG1())
                    show(Diccionary.at(i).getG1(), Diccionary.at(i).getG2());
            }
        }
    };

    template<class Generico>
    class Set2 {
    private:
        vector<Generico> x;
    public:
        Set2() {}
        //CLASS ITERATOR-------------------------
        class iterator {
            int i;
            vector<Generico> xd;
        public:
            iterator(int i = 0) : i(i) {}
            iterator(int i, vector<Generico> arr) : i(i), xd(arr) {}
            void operator ++ () { i++; }
            Generico operator * () { return xd[i]; }
            bool operator != (iterator b) { return this->i != b.i; }
        };
        //---------------------------------------

        //ITERATOR
        iterator begin() { return iterator(0, x); }
        iterator end() { return iterator(x.size()); }

        Generico element_by_position(int pos) {
            return x[pos];
        }
        void insertionSort(vector<Generico>& data, int  n) {
            int i, j;
            Generico tmp;

            for (i = 1; i < n; i++) {
                j = i;
                tmp = data[i];
                while (j > 0 && tmp < data[j - 1]) {
                    data[j] = data[j - 1];
                    j--;
                }
                data[j] = tmp;
            }
        }
        void merge2(vector<Generico>& arr1, vector<Generico>& arr2, vector<Generico>& arr3, int n) {
            size_t i = 0, j = 0, k = 0;
            size_t mitad = n / 2;
            while (i < mitad && j < n - mitad) {
                if (arr1[i] < arr2[j]) {
                    arr3[k] = arr1[i];
                    i++; k++;
                }
                else {
                    arr3[k] = arr2[j];
                    j++; k++;
                }
            }
            while (i < mitad) {
                arr3[k] = arr1[i];
                i++; k++;
            }
            while (j < n - mitad) {
                arr3[k] = arr2[j];
                j++; k++;
            }
        }
        void Tim_Sort() {
            int mitad = size() / 2;
            int mitad2 = size() - mitad;

            vector<Generico> arr1;
            vector<Generico> arr2;

            for (int i = 0; i < mitad; i++)
                arr1.push_back(x[i]);

            for (int i = 0; i < mitad2; i++)
                arr2.push_back(x[i + mitad]);

            insertionSort(arr1, arr1.size());
            insertionSort(arr2, arr2.size());
            merge2(arr1, arr2, x, x.size());
        }

        void insert(Generico e) {
            bool existe = false;;
            for (size_t i = 0; i < x.size(); i++) {
                if (x[i] == e) {
                    existe = true;
                }
            }
            if (existe == false) {
                x.push_back(e);
            }
            Tim_Sort();
        }
        void erase(Generico e) {
            for (size_t i = 0; i < x.size(); i++) {
                if (x[i] == e) {
                    x.erase(x.begin() + i-1);
                }
            }
        }
        void print(function<void(Generico)> f) {
            for (size_t i = 0; i < x.size(); i++) {
                f(x[i]);
            }
        }
        size_t size() {
            return x.size();
        }

    };

    template <typename T>
    class Vector
    {
        T* arr;
        int capacity;
        int current;
        function<void(T)> show;
    public:
        Vector(function<void(T)> show) : show(show) {
            arr = new T[1];
            capacity = 1;
            current = 0;
        }
        void push(T data) {
            if (current == capacity) {
                T* temp = new T[capacity + 1];
                for (int i = 0; i < capacity; i++) {
                    temp[i] = arr[i];
                }
                delete[] arr;
                capacity += 1;
                arr = temp;
            }
            arr[current] = data;
            current++;
        }
        void push(T data, int index) {
            if (index == capacity)
                push(data);
            else
                arr[index] = data;
        }
        T get(int index) {
            if (index <= current)
                return arr[index];
        }
        int size() { return current; }
        int getcapacity() { return capacity; }
        void print() {
            for (int i = 0; i < current; i++) {
                show(arr[i]);
            }
        }
        void setT(T t, int index) {
            if (index < current)
                arr[index] = t;
        }
    };
}


//-----------------------------------------------------------------------------
using namespace DataStructure;
namespace Clases {

    class PlanMensual {
        int plan;
        float monto;
        float descuento;
        float pago;
        int meses;
    public:
        PlanMensual(int plan = 0, float monto = 0, float descuento = 0, float pago = 0, int meses = 0) : plan(plan), monto(monto), descuento(descuento), pago(pago), meses(meses) { }
        void establecerPlan(int a) {
            plan = a;
            switch (plan)
            {
            case 1: monto = 3.99;
                break;
            case 2: monto = 4.99;
                break;
            }
        }
        void avanzarMes() {
            meses++;
            if (meses >= 7)
            {
                descuento = 1.5;
                pago = monto - descuento;
            }
        }
        void print() {
            cout << "\tInformacion del Plan Mensual: \n\n";
            cout << "\t\tTipo de plan: ";
            switch (plan)
            {
            case 1: cout << "Personal" << endl;
                break;
            case 2: cout << "Empresarial" << endl;
                break;
            }
            cout << "\t\tCosto mensual del servicio: " << monto << "\n";
            cout << "\t\tMeses pagando el servicio: " << meses << "\n";
            if (meses >= 7)
            {
                cout << "\t\tPor tu tiempo con nosotros te ofrecemos un descuento de: " << descuento << "\n";
                cout << "\t\tEl pago final este mes es de: " << pago << "\n";
            }
        }
    };

    class Contrasena {
    private:
        size_t empresa;
        string contrasena;
        Set2<string> empresas;
    public:
        Contrasena(size_t e = 0, string  c = "") :empresa(e), contrasena(c) {}
        Contrasena(Set2<string> a) {
            empresas = a;
            empresa = 0;
            contrasena = "";
        }
        string  getcontrasena() { return contrasena; }
        void    setcontrasena(string x) { contrasena = x; }
        size_t  getempresa() { return empresa; }
        void    setempresa(size_t x) { empresa = x; }
        void  print() {
            cout << empresas.element_by_position(empresa - 1) << "::" << contrasena << endl;
        }
        bool seguridadContrasena(string x) {

            bool    largo = false;
            bool    mayus = false;
            int     Cmayus = 0;
            bool    numer = false;
            int     Cnumero = 0;

            //valida longitud (MINIMO 4)
            if (x.length() >= 4) { largo = true; }

            for (int i = 0; i < x.length(); i++) {

                if (isupper(x[i])) {//valida mayuscula (MINIMO 2)
                    Cnumero++;
                    if (Cnumero >= 2) { mayus = true; }
                }

                if (isdigit(x[i])) {//valida numero (MINIMO 2)
                    Cnumero++;
                    if (Cnumero >= 2)
                        numer = true;
                }
            }
            if (largo && mayus && numer)    return true;
            else    return false;
        }
        void crear() {
            char caracter;
            string contra;
            cout << "\tIngrese contrasena: ";
            caracter = _getch();

            while (caracter != 13) {
                if (caracter != 8) {
                    contra.push_back(caracter);
                    cout << "*";
                }
                else {
                    if (contra.length() > 0) {
                        cout << "\b \b";
                        contra.pop_back();
                    }
                }
                caracter = _getch();
            }

            bool comprobacion;
            comprobacion = seguridadContrasena(contra);

            if (comprobacion) {
                int a;
                cout << "\n\tLa contrasena es segura";
                cout << "\n\tAgregado!" << endl;
                contrasena = contra;
            }
            else {
                cout << "\nLa contrasena no es segura" << endl;
            }
        }
        bool apta() {
            bool a = true;
            if (empresa != 0 && contrasena != "") a = false;
            return a;
        }
    };

    class Dispositivo {
        long serialnumber;
        size_t tipo;
        HT<size_t, Contrasena>* ht;
    public:
        Dispositivo(long serialnumer = 0, size_t tipo = 0) : serialnumber(serialnumber), tipo(tipo) {
            auto show = [](int a, Contrasena b) -> void { b.print(); };
            auto index = [](int a) -> int { return a % 5; };
            ht = new HT<size_t, Contrasena>(show, index);
        }
        void setContra(int a, Contrasena b) {
            ht->add(a, b);
        }
        void setElem(long a, size_t b) { serialnumber = a; tipo = b; }
        void print() {
            cout << "\t\tSerial Number: " << serialnumber << endl;
            cout << "\t\tTipo: ";
            switch (tipo)
            {
            case 1: cout << "PC" << endl;
                break;
            case 2: cout << "Celular" << endl;
                break;
            case 3: cout << "Tablet" << endl;
                break;
            case 4: cout << "Laptop" << endl;
                break;
            case 5: cout << "Smart TV" << endl;
                break;
            case 6: cout << "Tablet" << endl;
                break;
            }
            ht->display();
        }
        long getSN() { return serialnumber; }
        size_t getTipo() { return tipo; }
    };

    class Formulario {
        int pregunta;
        string respuesta;
    public:
        Formulario(int p = 0, string r = "") :pregunta(p), respuesta(r) { }
        void setPregunta(int a) { pregunta = a; }
        void setRespuesta(string a) { respuesta = a; }
        void print() {
            cout << "\tPregunta: ";
            switch (pregunta)
            {
            case 1: cout << "[1] ¿Cual fue la marca de su primer carro?";
                break;
            case 2: cout << "[2] ¿Cual fue el nombre de su primera mascota?";
                break;
            case 3: cout << "[3] ¿Donde vivio durante su infancia?";
                break;
            case 4: cout << "[4] ¿Cual era el colegio donde estudio su primaria?";
                break;
            case 5: cout << "[5] ¿Cual es su comida favorita?";
                break;
            }
            cout << " Respuesta: " << respuesta << endl;

        }
        void agregarFormulario() {
            int aux;
            string aux2;
            do {
                cout << "\tIngrese pregunta:\n";
                cout << "\t[1] ¿Cual fue la marca de su primer carro?\n";
                cout << "\t[2] ¿Cual fue el nombre de su primera mascota?\n";
                cout << "\t[3] ¿Donde vivio durante su infancia?\n";
                cout << "\t[4] ¿Cual era el colegio donde estudio su primaria?\n";
                cout << "\t[5] ¿Cual es su comida favorita?\n";
                cout << "\tIngrese opcion: ";
                cin >> aux;
            } while (aux < 1 || aux > 5);
            cout << "\tIngrese respuesta: ";
            cin >> aux2;
            setPregunta(aux); setRespuesta(aux2);
        }
    };

    class CuentaBancaria {
        string contrasena;
        float saldo;
        long tarjeta;
    public:
        CuentaBancaria(string contrasena = "", float saldo = 0, long tarjeta = 0) : contrasena(contrasena), saldo(saldo), tarjeta(tarjeta) { }
        void setContrasena(string a) { contrasena = a; }
        void setSaldo(float a) { saldo = a; }
        void setTarjeta(long a) { tarjeta = a; }
        string getContrasena() { return contrasena; }
        void print() {
            cout << "\t\t\tNumero de la tarjeta: " << tarjeta << endl;
            cout << "\t\t\tSaldo en la tarjeta: " << saldo << endl;
            cout << "\t\t\tContrasena: " << contrasena << endl;
        }
        void agregarCuenta() {
            long aux;
            float aux2;
            string aux3;
            cout << "\t\t\tNueva Cuenta Bancaria: \n";
            cout << "\tIngrese el numero de su tarjeta: "; cin >> aux;
            cout << "\tIngrese el saldo de su tarjeta: "; cin >> aux2;
            cout << "\tIngrese la contrasena asociada a esta tajeta: "; cin >> aux3;
            cout << "\tCuenta bancaria anadida!\n";
            setContrasena(aux3); setSaldo(aux2); setTarjeta(aux);
        }
    };

    class Usuario {
        string Nombre;
        string Apellido;
        long DNI;
        long Celular;
        size_t Edad;
    public:
        Usuario(string Nombre = "", string Apellido = "", long DNI = 0, long Celular = 0, size_t Edad = 0) : Nombre(Nombre), Apellido(Apellido), DNI(DNI), Celular(Celular), Edad(Edad) { }
        void print() {
            cout << "\tInformacion Personal: \n";
            cout << "\t\tNombre: " << Nombre << "\n";
            cout << "\t\tApellido: " << Apellido << "\n";
            cout << "\t\tDNI: " << DNI << "\n";
            cout << "\t\tCelular: " << Celular << "\n";
            cout << "\t\tEdad: " << Edad << "\n";
        }
        string getNombre() { return Nombre; }
        string getApellido() { return Apellido; }
        long getDNI() { return DNI; }
        long getCelular() { return Celular; }
        size_t getEdad() { return Edad; }
        void setNombre(string a) { Nombre = a; }
        void setApellido(string a) { Apellido = a; }
        void setDNI(long a) { DNI = a; }
        void setCelular(long a) { Celular = a; }
        void setEdad(size_t a) { Edad = a; }
    };

    class Cliente {
        Usuario c;
        long id;
        string maestra;
        int plan;
        HT<size_t, Contrasena>* ht;
        Vector<Dispositivo>* d;
        Lista<Formulario>* f;
        Map<string, CuentaBancaria>* boveda;
        PlanMensual p;
        Set2<string> e;
    public:
        Cliente(long id = 0, string nombre = "", string maestra = "", int plan = 0) :
            id(id), maestra(maestra), plan(plan) {
            auto show = [](int a, Contrasena b) -> void { b.print(); };
            auto index = [](int a) -> int { return a % 5; };
            ht = new HT<size_t, Contrasena>(show, index);
            auto show2 = [](Dispositivo b) -> void { b.print(); };
            d = new Vector<Dispositivo>(show2);
            auto show3 = [](Formulario b) -> void { b.print(); };
            f = new Lista<Formulario>(show3);
            auto show4 = [](string a, CuentaBancaria b) -> void { b.print(); };
            boveda = new  Map<string, CuentaBancaria>(show4);
        }
        void setUsuario(string aux, string aux2, long aux3, long aux4, size_t aux5) {
            c.setNombre(aux); c.setApellido(aux2); c.setDNI(aux3); c.setCelular(aux4); c.setEdad(aux5);
        }
        long getId() { return id; }
        string getContrasena() { return maestra; }
        int getPlan() { return plan; }
        void setId(long a) { id = a; }
        void setMaestra(string m) { maestra = m; }
        void setPlan(int n) { plan = n; }
        void mostrar() {
            cout << "ID: " << id << " - Contrasena: " << maestra << " - Plan: ";
            switch (plan)
            {
            case 1: cout << "Personal" << endl;
                break;
            case 2: cout << "Empresarial" << endl;
                break;
            }
        }
        void IngresarContrasena() {
            int opc;
            int c = 0;
            ofstream escritura;
            ifstream lectura;
            string guardado;
            string texto;
            lectura.open("empresas.txt");
            system("cls");
            cout << "\t\t\t\t\tIngrese datos de la contrasena\n\n";
            cout << "\t\tIngresar empresa para asociar la contrasena: \n";
            while (!lectura.eof()) {
                c++;
                getline(lectura, texto);
                guardado = guardado + texto + "\n";
                e.insert(texto);
            }
            for (int i = 0; i < e.size(); i++)
                cout << "\t[" << i + 1 << "]\t" << e.element_by_position(i) << endl;
            cout << "\t[" << ++c << "]\tOtro" << endl;
            do {
                cout << "\tOpcion: "; cin >> opc;
                if (opc == c) {
                    string nueva;
                    cout << "Agregue empresa:"; cin >> nueva;
                    e.insert(nueva);
                    if (e.size() != c - 1) {
                        escritura.open("empresas.txt");
                        escritura << guardado << nueva;
                    }
                    system("pause");
                }
                else {
                    Contrasena aux2(e);
                    aux2.crear();
                    aux2.setempresa(opc);
                    if (aux2.apta() == false)
                        ht->add(opc, aux2);

                }
            } while (opc < 1 && opc > c);

            system("pause");
            lectura.close();
            escritura.close();
        }
        void EliminarContrasena() {
            system("cls");
            int opc;
            int c = 0;
            ifstream lectura;
            string texto;
            lectura.open("empresas.txt");
            cout << "\t\t\t\t\tEliminar contrasena\n\n";
            cout << "\tSelecciona una empresa a eliminar: \n";
            while (!lectura.eof()) {
                c++;
                getline(lectura, texto);
                e.insert(texto);
            }
            for (int i = 0; i < e.size(); i++)
                cout << "\t[" << i + 1 << "]\t" << e.element_by_position(i) << endl;
            cout << "\tOpcion: ";
            cin >> opc;
            ht->deleteg(opc);
            ht->display();
            system("pause");
        }
        void AdministrarContrasenas() {
            int opcP;
            do
            {
                do {
                    system("cls");
                    cout << "\t\t\t\t\tAdministrador de contraseña\n\n";
                    cout << "\t[1] Mostrar Contraseña\n";
                    cout << "\t[2] Eliminar Contraseña\n";
                    cout << "\t[3] Atras\n";
                    cout << "\tOpcion: ";
                    cin >> opcP;
                } while (opcP < 1 || opcP > 3);
                switch (opcP)
                {
                case 1: ht->display(); system("pause");
                    break;
                case 2: EliminarContrasena();
                    break;
                }
            } while (opcP != 3);
        }
        Formulario agregarformulario() {
            Formulario x;
            x.agregarFormulario();
            return x;
        }
        void AdministraFormularios() {
            int opcP;
            int x;
            do
            {
                do {
                    system("cls");
                    cout << "\t\t\t\t\tAdministrador de formulario\n\n";
                    cout << "\t[1] Agregar pregunta\n";
                    cout << "\t[2] Mostrar \n";
                    cout << "\t[3] Eliminar ultimo formulario\n";
                    cout << "\t[4] Eliminar primer formulario\n";
                    cout << "\t[5] Atras\n";
                    cout << "\tOpcion: ";
                    cin >> opcP;
                } while (opcP < 1 || opcP > 5);
                switch (opcP)
                {
                case 1:
                    f->push_back(agregarformulario());
                    break;
                case 2: f->print(); system("pause");
                    break;
                case 3:
                    f->delete_back();
                    f->print();
                    system("pause");
                    break;
                case 4:
                    f->delete_front();
                    f->print();
                    system("pause");
                    break;
                }
            } while (opcP != 5);
        }
        void NuevoDispositivo() {
            Dispositivo aux;
            long aux2;
            size_t aux3;
            system("cls");
            cout << "\t\t\t\t\tNuevo Dispositivos\n\n";
            cout << "\tIngrese los siguiente sdatos: \n";
            cout << "\tNumero de serie: "; cin >> aux2;
            cout << "\tIngrese el tipo de dispositivo: \n";
            cout << "\t[1] PC\n";
            cout << "\t[2] Celular\n";
            cout << "\t[3] Tablet\n";
            cout << "\t[4] Laptop\n";
            cout << "\t[5] Smart TV\n";
            cout << "\t[6] Tablet\n";
            cout << "\tOpcion: "; cin >> aux3;
            aux.setElem(aux2, aux3);
            d->push(aux);
            d->print();
            system("pause");
        }
        void NuevaContraD() {
            int aux;
            int index;
            system("cls");
            cout << "\t\t\t\t\tIngrese datos de la contrasena\n\n";
            cout << "\t\tIngresar empresa para asociar la contrasena: \n";
            cout << "\t[1] Google (gmail)\n";
            cout << "\t[2] Microsoft (outlook)\n";
            cout << "\t[3] Twitter\n";
            cout << "\t[4] Instagram\n";
            cout << "\t[5] Facebook\n";
            cout << "\t[6] Discord\n";
            cout << "\t[7] Spotify\n";
            cout << "\t[8] Netflix\n";
            cout << "\t[9] Facebook\n";
            cout << "\t[10] WhatsApp\n";
            cout << "\t[11] Twitch\n";
            do
            {
                cout << "\tOpcion: "; cin >> aux;
            } while (aux < 1 && aux > 11);
            Contrasena aux2;
            aux2.setempresa(aux);
            aux2.crear();
            cout << "\tSeleccione dispositivo a ingresar la contrasena: \n";
            cout << "\tActualmente hay " << d->size() << " Asociados a esta cuenta\n";
            cout << "\tOcpicion: "; cin >> index;
            Dispositivo aux3 = d->get(index - 1);
            aux3.setContra(index - 1, aux2);
            aux3.print();
            system("pause");
        }
        void AdministrarDispositivo() {
            int opcP;
            do
            {
                do {
                    system("cls");
                    cout << "\t\t\t\t\tDispositivos\n\n";
                    cout << "\t[1] Ingresar nuevo dipositivo\n";
                    cout << "\t[2] Ingresar nueva contraseña en un dispositivo\n";
                    cout << "\t[3] Mostrar dispositivos y Contrasenas\n";
                    cout << "\t[4] Atras\n";
                    cout << "\tOpcion: ";
                    cin >> opcP;
                } while (opcP < 1 || opcP > 4);
                switch (opcP)
                {
                case 1: NuevoDispositivo();
                    break;
                case 2: NuevaContraD();
                    break;
                case 3: d->print(); system("pause");
                    break;
                }
            } while (opcP != 4);
        }
        void CrearBoveda() {
            CuentaBancaria aux;
            system("cls");
            aux.agregarCuenta();
            boveda->insert(aux.getContrasena(), aux);
            cout << "\tSe le mostraran las cuentas bancarias actuales: \n";
            boveda->print();
            system("pause");
        }
        void EliminarBoveda() {
            string aux;
            cout << "\t\t\t\t\tEliminar Cuenta Bancaria\n\n";
            cout << "\tIngrese una contrasena: "; cin >> aux;
            boveda->deleteByKey(aux);
            cout << "\tCuenta eliminada correctamente\n";
            cout << "\tSe le mostraran las cuentas bancarias actuales: \n";
            boveda->print();

            system("pause");
        }
        void AdministrarBoveda() {
            int opcP;
            do
            {
                do {
                    system("cls");
                    cout << "\t\t\t\t\tBoveda Bancaria\n\n";
                    cout << "\t[1] Crear nueva Boveda Bancaria\n";
                    cout << "\t[2] Eliminar boveda bancaria\n";
                    cout << "\t[3] Mostrar Todas la bovedas y contrasenas\n";
                    cout << "\t[4] Atras\n";
                    cout << "\tOpcion: ";
                    cin >> opcP;
                } while (opcP < 1 || opcP > 4);
                switch (opcP)
                {
                case 1: CrearBoveda();
                    break;
                case 2: EliminarBoveda();
                    break;
                case 3: boveda->print(); system("pause");
                    break;
                }
            } while (opcP != 4);
        }
        void AdministrarPlanMensual() {
            int opcP;
            do
            {
                do {
                    system("cls");
                    cout << "\t\t\t\t\tPlan Mensual\n\n";
                    cout << "\t[1] Establecer el plan\n";
                    cout << "\t[2] Avanzar Mes\n";
                    cout << "\t[3] Mostrar Plan Mesual\n";
                    cout << "\t[4] Atras\n";
                    cout << "\tOpcion: ";
                    cin >> opcP;
                } while (opcP < 1 || opcP > 4);
                switch (opcP)
                {
                case 1:
                    p.establecerPlan(this->getPlan());
                    p.print();
                    system("pause");
                    break;
                case 2:
                    p.avanzarMes();
                    break;
                case 3:
                    p.print();
                    system("pause");
                    break;
                }
            } while (opcP != 4);
        }
        void AgregarDatosPersonales() {
            string Nombre, Apellido;
            long DNI, Celular;
            size_t Edad;
            cout << "\tInformacion Personal: \n";
            cout << "\t\tPor favor ingre sus datos personales \n";
            cout << "\t\tNombre: "; cin >> Nombre;
            cout << "\t\tApellido: "; cin >> Apellido;
            cout << "\t\tDNI: "; cin >> DNI;
            cout << "\t\tCelular: "; cin >> Celular;
            cout << "\t\tEdad: "; cin >> Edad;
            c.setNombre(Nombre); c.setApellido(Apellido); c.setDNI(DNI); c.setCelular(Celular); c.setEdad(Edad);
            c.print();
        }
        void AdministrarDatosPersonales() {
            int opcP;
            do
            {
                do {
                    system("cls");
                    cout << "\t\t\t\t\tDatos Personales\n\n";
                    cout << "\t[1] Establecer datos Personales\n";
                    cout << "\t[2] Mostrar Datos Personales\n";
                    cout << "\t[3] Atras\n";
                    cout << "\tOpcion: ";
                    cin >> opcP;
                } while (opcP < 1 || opcP > 3);
                switch (opcP)
                {
                case 1:
                    AgregarDatosPersonales();
                    system("pause");
                    break;
                case 2:
                    c.print();
                    system("pause");
                    break;
                }
            } while (opcP != 3);
        }
        void Menu() {
            int opcP;
            do
            {
                do {
                    system("cls");
                    cout << "\t\t\t\t\tBienvenido " << c.getNombre() << "\n\n";
                    cout << "\t[1] Ingresar Contrasena\n";
                    cout << "\t[2] Administrar Contrasenas\n";
                    cout << "\t[3] Administrar Dispositivos\n";
                    cout << "\t[4] Administrar Formularios\n";
                    cout << "\t[5] Administrar Boveda Bancaria\n";
                    cout << "\t[6] Administrar Plan Mensual\n";
                    cout << "\t[7] Administrar Datos personales\n";
                    cout << "\t[8] Cerrar Sesion\n\n";
                    cout << "\tOpcion: ";
                    cin >> opcP;
                } while (opcP < 1 || opcP > 8);
                switch (opcP)
                {
                case 1: IngresarContrasena();
                    break;
                case 2: AdministrarContrasenas();
                    break;
                case 3: AdministrarDispositivo();
                    break;
                case 4: AdministraFormularios();
                    break;
                case 5: AdministrarBoveda();
                    break;
                case 6: AdministrarPlanMensual();
                    break;
                case 7: AdministrarDatosPersonales();
                    break;
                }
            } while (opcP != 8);
        }
    };
}

//-----------------------------------------------------------------------------

using namespace Clases;
class Controladora {
    Arbol<Cliente>* c;
public:
    Controladora() {
        auto show = [](Cliente a) -> void { a.mostrar(); };
        auto compare = [](Cliente a, Cliente b) -> bool {
            if (a.getId() >= b.getId()) return true; else return false; };
        auto dosomething = [](Cliente a, Cliente b) -> size_t {
            if (a.getId() == b.getId() && a.getContrasena() == b.getContrasena())
                return 0;
            else if (a.getId() < b.getId()) return -1;
            else if (a.getId() > b.getId()) return 1;
        };
        c = new Arbol<Cliente>(show, compare, dosomething);
    }
    void MenuPrincipal() {
        int opcP;
        do
        {
            do {
                system("cls");
                cout << "\t\t\t\t\tMenu Principal\n\n";
                cout << "\t[1] Ingresar\n";
                cout << "\t[2] Registrase\n";
                cout << "\t[3] Depurador\n";
                cout << "\t[4] Salir\n\n";
                cout << "\tOpcion: ";
                cin >> opcP;
            } while (opcP < 1 || opcP > 4);
            switch (opcP)
            {
            case 1: Ingresar_Menu();
                break;
            case 2: Registrarse_Menu();
                break;
            case 3: Depurador();
                break;
            }
        } while (opcP != 4);
    }
    void Ingresar_Menu() {
        int opcP;
        do
        {
            do {
                system("cls");
                cout << "\t\t\t\t\tIngresar - Tipo de cuenta:\n\n";
                cout << "\t[1] Cuenta Personal\n";
                cout << "\t[2] Cuenta Empresarial\n";
                cout << "\t[3] Atras\n";
                cout << "\tOpcion: ";
                cin >> opcP;
            } while (opcP < 1 || opcP > 3);
            switch (opcP)
            {
            case 1: VerificarCuentaPersonal();
                break;
            case 2: VerificarCuentaEmpresarial();
                break;
            }
        } while (opcP != 3);
    }
    void VerificarCuentaPersonal() {
        system("cls");
        long aux;
        string aux2;
        cout << "\t\t\t\t\tIngrese sus datos\n";
        cout << "\tIngrese su id: ";
        cin >> aux;
        cout << "\tIngrese su contrasena: ";
        cin >> aux2;
        Cliente aux3(aux, "", aux2, 1);
        Cliente aux4 = c->search(aux3);
        if (aux3.getId() == aux4.getId() && aux3.getContrasena() == aux4.getContrasena() && aux3.getPlan() == aux4.getPlan()) {
            cout << "\n\tHaz accedido con exito!\n" << endl;
            aux4.Menu();
            c->replaceElement(aux4);
        }
        else
            cout << "\n\tNo se encontro cliente. Intentelo de nuevo\n" << endl;
        system("pause");
    }
    void VerificarCuentaEmpresarial() {
        system("cls");
        long aux;
        string aux2;
        cout << "\t\t\t\t\tIngrese sus datos\n";
        cout << "\tIngrese su id: ";
        cin >> aux;
        cout << "\tIngrese su contrasena: ";
        cin >> aux2;
        Cliente aux3(aux, "", aux2, 2);
        Cliente aux4 = c->search(aux3);
        if (aux3.getId() == aux4.getId() && aux3.getContrasena() == aux4.getContrasena() && aux3.getPlan() == aux4.getPlan()) {
            cout << "\n\tHaz accedido con exito!\n" << endl;
            aux4.Menu();
            c->replaceElement(aux4);
        }
        else
            cout << "\n\tNo se encontro cliente. Intentelo de nuevo\n" << endl;
        system("pause");
    }
    void Registrarse_Menu() {
        int opcP;
        do
        {
            do {
                system("cls");
                cout << "\t\t\t\t\tRegistarse - Tipo de cuenta:\n\n";
                cout << "\t[1] Cuenta Personal\n";
                cout << "\t[2] Cuenta Empresarial\n";
                cout << "\t[3] Atras\n";
                cout << "\tOpcion: ";
                cin >> opcP;
            } while (opcP < 1 || opcP > 3);
            switch (opcP)
            {
            case 1: RegistrarCuentaPersonal();
                break;
            case 2: RegistrarCuentaEmpresarial();
                break;
            }
        } while (opcP != 3);
    }
    void RegistrarCuentaPersonal() {
        system("cls");
        string nombre, apellido, aux2;
        long DNI, celular, aux;
        size_t Edad;
        cout << "\t\t\t\t\tRegistre sus datos\n";
        cout << "\tIngrese su nombre: "; cin >> nombre;
        cout << "\tIngrese su apellido: "; cin >> apellido;
        cout << "\tIngrese su DNI: "; cin >> DNI;
        cout << "\tIngrese su Celular: "; cin >> celular;
        cout << "\tIngrese su Edad: "; cin >> Edad;
        cout << "\tIngrese su ID: "; cin >> aux;
        cout << "\tIngrese una contrasena maestra: "; cin >> aux2;
        Cliente a(aux, "", aux2, 1);
        a.setUsuario(nombre, apellido, DNI, celular, Edad);
        c->insert(Cliente(aux, "", aux2, 1));
        cout << "\tCliente registrado correctamente!\n";
        c->print();
        system("pause");
    }
    void RegistrarCuentaEmpresarial() {
        system("cls");
        string nombre, apellido, aux2;
        long DNI, celular, aux;
        size_t Edad;
        cout << "\t\t\t\t\tRegistre sus datos\n";
        cout << "\tIngrese su nombre: "; cin >> nombre;
        cout << "\tIngrese su apellido: "; cin >> apellido;
        cout << "\tIngrese su DNI: "; cin >> DNI;
        cout << "\tIngrese su Celular: "; cin >> celular;
        cout << "\tIngrese su Edad: "; cin >> Edad;
        cout << "\tIngrese su ID: "; cin >> aux;
        cout << "\tIngrese una contrasena maestra: "; cin >> aux2;
        Cliente a(aux, "", aux2, 2);
        a.setUsuario(nombre, apellido, DNI, celular, Edad);
        c->insert(Cliente(aux, "", aux2, 2));
        cout << "\tCliente registrado correctamente!\n";
        c->print();
        system("pause");
    }
    void loadData() {
        string linea;
        long id;
        int plan;
        std::ifstream archivo("dataset.txt");
        char delimitador = ',';
        while (getline(archivo, linea))
        {
            stringstream stream(linea);
            string nombre, contrasena, idaux, planaux;
            getline(stream, idaux, ',');
            getline(stream, nombre, ',');
            getline(stream, contrasena, ',');
            getline(stream, planaux, ',');
            id = std::stol(idaux);
            plan = std::stol(planaux);
            c->insert(Cliente(id, nombre, contrasena, plan));
        }
        archivo.close();
        c->print();
        system("pause");
    }
    void Depurador() {
        int opcP;
        do
        {
            do {
                system("cls");
                cout << "\t\t\t\t\tFunciones Utiles\n\n";
                cout << "\t[1] Cargar Ejemplo\n";
                cout << "\t[2] Cargar Dataset\n";
                cout << "\t[3] Atras\n";
                cout << "\tOpcion: ";
                cin >> opcP;
            } while (opcP < 1 || opcP > 3);
            switch (opcP)
            {
            case 1:
                c->insert(Cliente(12345, (""), ("abcde"), 1));
                c->insert(Cliente(47583, (""), ("edwfsf"), 2));
                c->insert(Cliente(23467, (""), ("fgrtgg"), 2));
                c->insert(Cliente(48859, (""), ("btbyyh"), 1));
                c->print();
                system("pause");
                break;
            case 2: loadData();
                break;
            }
        } while (opcP != 3);
    }
};

//-----------------------------------------------------------------------------

int main() {
    Controladora c;
    c.MenuPrincipal();
    return 0;
}