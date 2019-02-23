#include <iostream>
#include "Red.h"
#include "Stek.h"

int ispreplitaniRedovi(Stek<Red<int>>& stek, Red<int> &red);

void radi(Stek<Red<int>> &stek, Red<int> &red);

void preplitanje(Red<int>& glavni, Red<int>& iznad, Red<int> &zamjena);

int main() {
    Stek<Red<int>> glavni;
    Red<int>a,b,c,zamjena;
    zamjena.stavi(3);
    zamjena.stavi(7);
    zamjena.stavi(11);
    a.stavi(1);
    b.stavi(6);
    c.stavi(2);
    c.stavi(5);
    c.stavi(9);
    c.stavi(12);
    c.stavi(14);
    c.stavi(16);
    glavni.stavi(a);
    glavni.stavi(b);
    glavni.stavi(c);

    std::cout<<glavni<<"\n";
    ispreplitaniRedovi(glavni,zamjena);
    std::cout<<glavni;

    return 0;
}


int ispreplitaniRedovi(Stek<Red<int>> &stek, Red<int> &red) {
    radi(stek,red);
    Red<int> x = stek.skini();
    Red<int> y;
    preplitanje(x,y,red);
    stek.stavi(x);
    return 0;
}

void radi(Stek<Red<int>> &stek, Red<int> &red) {

    if(stek.brojElemenata()>0){
        auto x = stek.skini();
        Red<int> y ;
        if(stek.brojElemenata()>0){
            y = stek.skini();
            stek.stavi(y);
            radi(stek,red);
            preplitanje(y,x,red);
            stek.skini();
            stek.stavi(y);
        }
        stek.stavi(x);
    }


}

void preplitanje(Red<int>& glavni, Red<int>& iznad, Red<int> &zamjena) {
    int n = glavni.brojElemenata();
    int m = iznad.brojElemenata();
    int l = zamjena.brojElemenata();
    int i=0,j=0,k=0;
    while(i<n  || k<l) {
        int x=0,y=0,z=0;
        if(i<n) {
            x = glavni.skini();
            i++;
        }else if(j<m){
            y = iznad.skini();
            j++;
            x=-1;
        }
        if(k<l){
            z = zamjena.skini();
            k++;
        }else if(j<m){
            y = iznad.skini();
            j++;
            z=-1;
        }

        if(x==-1){
            glavni.stavi(y);
            if(y!=0){
                iznad.stavi(y);
            }
        }else{
            glavni.stavi(x);
        }
        if(z==-1){
            glavni.stavi(y);
            if(y!=0){
                iznad.stavi(y);
            }
        }else{
            if(i<n || k<l || z!=0)glavni.stavi(z);
            if(z!=0)zamjena.stavi(z);
        }

    }
    while(j<m){
        iznad.stavi(iznad.skini());
        j++;
    }
}
