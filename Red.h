//
// Created by tsijercic1 on 1/29/2019.
//

#ifndef STEKREDCPP_RED_H
#define STEKREDCPP_RED_H


#include <iostream>
#include "Cvor.h"


template <typename tip>
class Red
{
    Cvor<tip>* pocetak;
    Cvor<tip>* kraj;
    int velicina;
    void dealociraj();
public:
    Red();
    Red(const Red<tip>& a);
    Red(Red<tip>&& a);
    Red<tip>& operator=(const Red<tip>& a);
    Red<tip>& operator=(Red<tip>&& a);
    void brisi();
    void stavi(const tip& a);
    tip skini();
    tip& celo();
    const tip& celo()const;
    int brojElemenata()const;
    ~Red();
    template<class T>
            friend std::ostream& operator<<(std::ostream& tok, const Red<T>& red);
};



template<typename tip>
Red<tip>::Red()
{
    velicina=0;
    pocetak=nullptr;
    kraj=nullptr;
}

template<typename tip>
void Red<tip>::stavi(const tip& a)
{
    auto temp = new Cvor<tip> {a,nullptr};
    if(!pocetak && !kraj) {
        kraj=temp;
        pocetak=temp;
    } else {
        kraj->next=temp;
        kraj=temp;
    }
    velicina++;
}

template<typename tip>
tip Red<tip>::skini()
{
    if(velicina==0)throw "Red je prazan!";
    tip holder = pocetak->element;
    auto temp=pocetak;
    if(kraj==pocetak)pocetak=kraj=nullptr;
    pocetak=temp->next;
    delete temp;
    velicina--;
    return holder;
}

template<typename tip>
tip& Red<tip>::celo()
{
    if(velicina==0)throw "Red je prazan!";
    return pocetak->element;
}

template<typename tip>
const tip& Red<tip>::celo()const
{
    if(velicina==0)throw "Red je prazan!";
    return pocetak->element;
}

template<typename tip>
int Red<tip>::brojElemenata()const
{
    return velicina;
}

template<typename tip>
void Red<tip>::dealociraj()
{
    velicina=0;
    auto temp = pocetak;
    for(; temp;) {
        pocetak=temp->next;
        delete temp;
        temp=pocetak;
    }
    kraj=nullptr;
    pocetak=nullptr;
}

template<typename tip>
void Red<tip>::brisi()
{
    dealociraj();
}

template<typename tip>
Red<tip>::~Red()
{
    dealociraj();
}

template<typename tip>
Red<tip>::Red(const Red<tip> &a)
{
    velicina=a.velicina;
    auto temp = a.pocetak;
    auto klizni = pocetak = nullptr;
    for(; temp;) {
        if(!pocetak) {
            pocetak= new Cvor<tip> {temp->element,nullptr};
            klizni=pocetak;
            temp=temp->next;
            kraj=pocetak;
        } else {
            klizni->next = new Cvor<tip> {temp->element, nullptr};
            klizni=klizni->next;
            kraj=klizni;
            temp=temp->next;
        }
    }
}

template<typename tip>
Red<tip>::Red(Red<tip>&& a)
{
    pocetak=a.pocetak;
    kraj=a.kraj;
    velicina=a.velicina;
    a.pocetak=nullptr;
    a.kraj=nullptr;
    a.velicina=0;;
}

template<typename tip>
Red<tip>& Red<tip>::operator=(const Red<tip>& a)
{
    if(&a==this)return *this;
    Red<tip> b(a);
    auto temp1 = pocetak;
    auto temp2 = kraj;
    auto temp3 = velicina;
    pocetak = b.pocetak;
    kraj = b.kraj;
    velicina = b.velicina;
    b.pocetak = temp1;
    b.kraj = kraj;
    b.velicina = temp3;
    return *this;
}

template<typename tip>
Red<tip>& Red<tip>::operator=(Red<tip>&& a)
{
    if(&a == this )return *this;
    auto temp1 = pocetak;
    auto temp2 = kraj;
    auto temp3 = velicina;
    pocetak = a.pocetak;
    kraj = a.kraj;
    velicina = a.velicina;
    a.pocetak = temp1;
    a.kraj = temp2;
    a.velicina = temp3;
    return *this;
}

template<class T>
std::ostream &operator<<(std::ostream &tok, const Red<T> &red) {
    Cvor<T> *klizni=red.pocetak;
    if(red.brojElemenata()==0){
        tok<<"{}";
        return tok;
    }
    tok<<"{ "<<klizni->element;
    for(klizni=klizni->next;klizni;klizni=klizni->next){
        tok<<", "<<klizni->element;
    }
    tok<<" }";
    return tok;
}


#endif //STEKREDCPP_RED_H
