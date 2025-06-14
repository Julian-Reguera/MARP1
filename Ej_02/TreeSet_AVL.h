﻿//
//  TreeSet_AVL.h
//
//  Implementaci�n de conjuntos mediante �rboles de b�squeda AVL
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef TREESET_AVL_H_
#define TREESET_AVL_H_

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>


template <class T, class Comparator = std::less<T>>
class Set {
protected:

    /*
     Nodo que almacena internamente el elemento (de tipo T),
     punteros al hijo izquierdo y derecho, que pueden ser
     nullptr si el hijo es vac�o, y la altura.
     */
    struct TreeNode;
    using Link = TreeNode*;
    struct TreeNode {
        T elem;
        Link iz, dr;
        int altura;
        int tam_i;
        int numNodos;
        TreeNode(T const& e, Link i = nullptr, Link d = nullptr,
            int alt = 1, int tam = 1, int numHi = 1) : elem(e), iz(i), dr(d), altura(alt), tam_i(tam), numNodos(numHi) {}
    };

    // puntero a la ra�z de la estructura jer�rquica de nodos
    Link raiz;

    // n�mero de elementos (cardinal del conjunto)
    int nelems;

    // objeto funci�n que compara elementos (orden total estricto)
    Comparator menor;

public:

    // constructor (conjunto vac�o)
    Set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

    // constructor por copia
    Set(Set const& other) {
        copia(other);
    }

    // operador de asignaci�n
    Set& operator=(Set const& that) {
        if (this != &that) {
            libera(raiz);
            copia(that);
        }
        return *this;
    }

    ~Set() {
        libera(raiz);
    };

    bool insert(T const& e) {
        return inserta(e, raiz);
    }

    bool empty() const {
        return raiz == nullptr;
    }

    int size() const {
        return nelems;
    }

    bool contains(T const& e) const {
        return pertenece(e, raiz);
    }

    bool erase(T const& e) {
        return borra(e, raiz);
    }

    T const& kesimo(int k) const {

        return kesimoRec(k, raiz);
    }

protected:

    T const& kesimoRec(int k, Link a) const {
        if (a == nullptr) throw std::runtime_error("Error en parametro de entrada");
        else if (a->tam_i == k) return a->elem;
        else if (a->tam_i > k) return kesimoRec(k, a->iz);
        else if (a->tam_i < k) return kesimoRec(k - a->tam_i, a->dr);
    }

    void copia(Set const& other) {
        raiz = copia(other.raiz);
        nelems = other.nelems;
        menor = other.menor;
    }

    static Link copia(Link a) {
        if (a == nullptr) return nullptr;
        else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura, a->tam_i, a->numNodos);
    }

    static void libera(Link a) {
        if (a != nullptr) {
            libera(a->iz);
            libera(a->dr);
            delete a;
        }
    }

    bool pertenece(T const& e, Link a) const {
        if (a == nullptr) {
            return false;
        }
        else if (menor(e, a->elem)) {
            return pertenece(e, a->iz);
        }
        else if (menor(a->elem, e)) {
            return pertenece(e, a->dr);
        }
        else { // e == a->elem
            return true;
        }
    }

    bool inserta(T const& e, Link& a) {
        bool crece;
        if (a == nullptr) { // se inserta el nuevo elemento e
            a = new TreeNode(e);
            ++nelems;
            crece = true;
        }
        else if (menor(e, a->elem)) {
            crece = inserta(e, a->iz);
            if (crece) reequilibraDer(a);
        }
        else if (menor(a->elem, e)) {
            crece = inserta(e, a->dr);
            if (crece) reequilibraIzq(a);
        }
        else // el elemento e ya est� en el �rbol
            crece = false;
        return crece;
    }

    int altura(Link a) {
        if (a == nullptr) return 0;
        else return a->altura;
    }

    int tamanoIz(Link a) {
        if (a == nullptr) return 0;
        else return a->tam_i;
    }

    int numNodos(Link a) {
        if (a == nullptr) return 0;
        else return a->numNodos;
    }

    void rotaDer(Link& k2) {
        Link k1 = k2->iz;
        k2->iz = k1->dr;
        k1->dr = k2;
        k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
        k2->tam_i = numNodos(k2->iz) + 1;
        k2->numNodos = numNodos(k2->iz) + numNodos(k2->dr) + 1;
        k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
        k1->tam_i = numNodos(k1->iz) + 1;
        k1->numNodos = numNodos(k1->iz) + numNodos(k1->dr) + 1;
        k2 = k1;
    }

    void rotaIzq(Link& k1) {
        Link k2 = k1->dr;
        k1->dr = k2->iz;
        k2->iz = k1;
        k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
        k1->tam_i = numNodos(k1->iz) + 1;
        k1->numNodos = numNodos(k1->iz) + numNodos(k1->dr) + 1;
        k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
        k2->tam_i = numNodos(k2->iz) + 1;
        k2->numNodos = numNodos(k2->iz) + numNodos(k2->dr) + 1;
        k1 = k2;
    }

    void rotaIzqDer(Link& k3) {
        rotaIzq(k3->iz);
        rotaDer(k3);
    }

    void rotaDerIzq(Link& k1) {
        rotaDer(k1->dr);
        rotaIzq(k1);
    }

    void reequilibraIzq(Link& a) {
        if (altura(a->dr) - altura(a->iz) > 1) {
            if (altura(a->dr->iz) > altura(a->dr->dr))
                rotaDerIzq(a);
            else rotaIzq(a);
        }
        else {
            a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
            a->tam_i = numNodos(a->iz) + 1;
            a->numNodos = numNodos(a->iz) + numNodos(a->dr) + 1;
        }
    }

    void reequilibraDer(Link& a) {
        if (altura(a->iz) - altura(a->dr) > 1) {
            if (altura(a->iz->dr) > altura(a->iz->iz))
                rotaIzqDer(a);
            else rotaDer(a);
        }
        else {
            a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
            a->tam_i = numNodos(a->iz) + 1;
            a->numNodos = numNodos(a->iz) + numNodos(a->dr) + 1;
        }
    }

    // devuelve y borra el m�nimo del �rbol con ra�z en a
    T borraMin(Link& a) {
        if (a->iz == nullptr) {
            T min = a->elem;
            a = a->dr;
            --nelems;
            return min;
        }
        else {
            T min = borraMin(a->iz);
            reequilibraIzq(a);
            return min;
        }
    }

    bool borra(T const& e, Link& a) {
        bool decrece = false;
        if (a != nullptr) {
            if (menor(e, a->elem)) {
                decrece = borra(e, a->iz);
                if (decrece) reequilibraIzq(a);
            }
            else if (menor(a->elem, e)) {
                decrece = borra(e, a->dr);
                if (decrece) reequilibraDer(a);
            }
            else { // e == a->elem
                if (a->iz == nullptr || a->dr == nullptr) {
                    Link aux = a;
                    a = (a->iz == nullptr) ? a->dr : a->iz;
                    --nelems;
                    delete aux;
                }
                else { // tiene dos hijos
                    T min = borraMin(a->dr);
                    a->elem = min;
                    reequilibraDer(a);
                }
                decrece = true;
            }
        }
        return decrece;
    }

public:
    // iteradores que recorren los elementos del conjunto de menor a mayor
    class const_iterator {
    public:
        T const& operator*() const {
            if (act == nullptr)
                throw std::out_of_range("No hay elemento a consultar");
            return act->elem;
        }

        T const* operator->() const {
            return &operator*();
        }

        const_iterator& operator++() {  // ++ prefijo
            next();
            return *this;
        }

        bool operator==(const_iterator const& that) const {
            return act == that.act;
        }

        bool operator!=(const_iterator const& that) const {
            return !(this->operator==(that));
        }

    protected:
        friend class Set;
        Link act;
        std::stack<Link> ancestros;  // antecesores no visitados

        // construye el iterador al primero
        const_iterator(Link raiz) { act = first(raiz); }

        // construye el iterador al �ltimo
        const_iterator() : act(nullptr) {}

        Link first(Link ptr) {
            if (ptr == nullptr) {
                return nullptr;
            }
            else { // buscamos el nodo m�s a la izquierda
                while (ptr->iz != nullptr) {
                    ancestros.push(ptr);
                    ptr = ptr->iz;
                }
                return ptr;
            }
        }

        void next() {
            if (act == nullptr) {
                throw std::out_of_range("El iterador no puede avanzar");
            }
            else if (act->dr != nullptr) { // primero del hijo derecho
                act = first(act->dr);
            }
            else if (ancestros.empty()) { // hemos llegado al final
                act = nullptr;
            }
            else { // podemos retroceder
                act = ancestros.top();
                ancestros.pop();
            }
        }
    };

    const_iterator begin() const {
        return const_iterator(raiz);
    }

    const_iterator end() const {
        return const_iterator();
    }
};


#endif