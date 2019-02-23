//
// Created by tsijercic1 on 1/29/2019.
//

#ifndef STEKREDCPP_STEK_H
#define STEKREDCPP_STEK_H


#include <iostream>
#include "Cvor.h"

template <typename tip>
class Stek
{
    Cvor<tip>* top;
    int velicina;
public:
    Stek() {
        velicina=0;
        top = nullptr;
    }
    //treba mi konstruktor kopije
    Stek(const Stek<tip>& a);
    Stek(Stek<tip>&& a);
    Stek<tip>& operator =( const Stek<tip>& b)
    {
        if(&b == this)return *this;
        Stek<tip> a(b);
        auto temp = top;
        top=a.top;
        a.top=temp;
        auto temp2 = velicina;
        velicina = a.velicina;
        a.velicina = temp2;
        return *this;
    }
    Stek<tip>& operator=( Stek<tip>&& a)
    {
        auto temp = top;
        top=a.top;
        a.top=temp;
        auto temp2 = velicina;
        velicina = a.velicina;
        a.velicina = temp2;
        return *this;
    }
    //treba mi operator dodjele
    //i ono sto dolazi uz njih
    void brisi();
    void stavi(const tip &a);
    tip skini();
    tip& vrh();
    const tip& vrh()const;
    const int brojElemenata()const
    {
        return velicina;
    }

    ~Stek()
    {
        brisi();
    }
    template <class T>
    friend std::ostream& operator<<(std::ostream& tok, const Stek<T>& stek);
};


template <typename tip>
Stek<tip>::Stek(const Stek<tip> &a)
{
    if (a.velicina == 0) {
        top=nullptr;
        velicina=0;
    } else {
        top=new Cvor<tip> {a.top->element,nullptr};
        auto temp=a.top;
        temp=a.top->next;
        auto klizni=top;

        for(; temp;) {
            klizni->next=new Cvor<tip> {temp->element,nullptr};
            klizni=klizni->next;
            temp=temp->next;
        }
        velicina=a.velicina;
    }
}

template <typename tip>
Stek<tip>::Stek(Stek<tip>&& a)
{
    top = a.top;
    a.top=nullptr;
    velicina=a.velicina;
    a.velicina=0;
}

template <typename tip>
void Stek<tip>::stavi(const tip& a)
{
    try {
        auto temp = new Cvor<tip> {a,top};
        top = temp;
        velicina++;
    } catch(...) {
        auto x=top;
        for(; top;) {
            x= top;
            top=top->next;
            delete x;
        }
        throw "No memory";
    }
}

template <typename tip>
void Stek<tip>::brisi()
{
    auto x=top;
    for(; top;) {
        x=top;
        top=top->next;
        delete x;
    }
    velicina = 0;
}

template <typename tip>
tip Stek<tip>::skini()
{
    if(velicina==0)throw "Stek je prazan!";
    tip a = top->element;
    auto temp = top;
    top = top -> next;
    delete temp;
    velicina--;
    return a;
}

template <typename tip>
tip& Stek<tip>::vrh()
{
    if(velicina==0)throw "Stek je prazan!";
    return top->element;
}

template <typename tip>
const tip& Stek<tip>::vrh()const
{
    if(velicina==0)throw "Stek je prazan!";
    return top->element;
}


template<typename tip>
std::ostream &operator<<(std::ostream &tok, const Stek<tip>& stek) {
    Cvor<tip> *klizni=stek.top;
    if(stek.brojElemenata()==0){
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


#endif //STEKREDCPP_STEK_H
