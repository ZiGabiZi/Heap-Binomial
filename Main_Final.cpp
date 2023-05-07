#include <iostream>
#include <list>
using namespace std;
class Nod{
    int valoare, ordin;
    Nod* copil_stanga;
    Nod* frate;

public:
    int getOrdin() const {
        return ordin;
    }

    void setOrdin(int ordin) {
        Nod::ordin = ordin;
    }


    Nod(int valaore){
        this->valoare = valoare;
        copil_stanga = nullptr;
        frate = nullptr;
        ordin = 0;
    }

    int getValoare() const {
        return valoare;
    }

    Nod *getCopilStanga() const {
        return copil_stanga;
    }

    Nod *getFrate() const {
        return frate;
    }

    void setValoare(int valoare) {
        Nod::valoare = valoare;
    }

    void setCopilStanga(Nod *copilStanga) {
        copil_stanga = copilStanga;
    }

    void setFrate(Nod *frate) {
        Nod::frate = frate;
    }


    void add_copil(Nod* aux){
        aux->setFrate(this->getCopilStanga());
        this->setCopilStanga(aux);
        aux->ordin = ordin+1;
    }





};

class Heap{
    list<Nod*> radacina;
    Nod* mergeHeap2(Nod* h1, Nod* h2){
        if(h1->getValoare() < h2->getValoare()) {
            h2->add_copil(h1);
            return h2;

        }
        else{
            h1->add_copil(h2);
            return h1;
        }

    }

public:




    void Erase(){
        radacina.clear();
    }


    Heap merge(Heap h1, Heap h2){
        auto i = h1.radacina.begin();
        auto j = h2.radacina.begin();

        list<Nod*> h;
        while (i!=h1.radacina.end() && j!=h2.radacina.end()){
            if((*i)->getOrdin() <= (*j)->getOrdin()){
                h.push_back(*i);
                i++;
            }
            else{
                h.push_back(*j);
                j++;
            }


        }
        while (i!=h1.radacina.end()){
            h.push_back(*i);
            i++;
        }
        while (j!=h2.radacina.end()){
            h.push_back(*j);
            j++;
        }

    }

    list<Nod*> Elim_Min_Arb(Nod* aux){
        Nod* aux2 = aux->getCopilStanga();
        list<Nod*> h;
        Nod* aux3;

        while(aux2){
            aux3 = aux2;
            aux2 = aux2->getFrate();
            aux3->setFrate(nullptr);
            h.push_back(aux3);
        }

        return h;
    }




    list<Nod*> repara(list<Nod*> aux){
        if(aux.size() <= 1)
            return aux;
        list<Nod*>::iterator i,j,k;
        i = j = k = aux.begin();

        if(aux.size() == 2){
            j = i;
            j++;
            k = aux.end();
        }
        else{
            j++;
            k = j;
            k++;
        }

        while (i!=aux.end()){
            if(j == aux.end())
                i++;
            else if((*i)->getOrdin() < (*j)->getOrdin()){
                i++;
                j++;
                if(k!=aux.end())
                    k++;
            }
            else if(k!=aux.end() && (*i)->getOrdin() == (*j)->getOrdin() && (*i)->getOrdin() == (*k)->getOrdin()){
                i++;
                j++;
                k++;
            }

            else if((*i)->getOrdin() == (*j)->getOrdin()){
                *i = mergeHeap2(*i,*j);
                j = aux.erase(j);
                if(k!=aux.end())
                    k++;
            }
        }

        return aux;

    }







//    void push(int aux){
//        Nod* aux2 = radacina->getFrate(); ///
//        radacina->setFrate(new Nod(aux));
//        radacina->getFrate()->setFrate(aux2);
//
//    }



    list<Nod*> Adaug_Arbore(Heap h, Nod* arbore){
        list<Nod*> aux;
        aux.push_back(arbore);
        aux = merge(h,aux);
        return repara(aux);
    }



    list<Nod*> Pop_max(list<Nod*> h){
        list<Nod*> rez;
        list<Nod*> aux;
        Nod* aux2;

        aux2 = Afis_Max(h);
        for(auto i = h.begin();i <= h.end();i++){
            if(*i != aux2)
                rez.push_back(*i);

        }

        aux = Elim_Min_Arb(aux2);
        rez = mergeHeap2(rez,aux);
        rez = repara(rez);
        return rez;

    }


    Nod* Afis_Max(list<Nod*> h){
        auto i = h.begin();
        Nod* aux = *i;
        while (i!=h.end()){
            if((*i)->getValoare() > aux->getValoare())
                aux = *i;
            i++;

        }
        return aux;

    }


    list<Nod*> Adaugare_Nod(list<Nod*> k,int cheie){
        Nod* aux  = Nod(cheie);
        return Adaug_Arbore(k,aux);
    }


};













int main()
{
    int n,nr;
    cin >> n >> nr;
    Heap* heapuri =new Heap[n];
    for(int i =0; i<=nr;i++){
        int operatie;
        cin >> operatie;
        switch (operatie) {
            case 1:{
                int x, val;
                cin >> x >> val;
                heapuri[x].Adaugare_Nod(heapuri[x].radacina, val);
            }
            case 2:{
                int x;
                cin >> x;
                heapuri[x].Afis_Max(heapuri[x].getRadacina());
                cout << *i.getVal();
                heapuri[x] = Pop_max(heapuri[x].radacina);
            }

            case 3:{
                int x,y;
                cin >> x >> y;
                heapuri[x] = Merge(heapuri[x].radacina, heapuri[x].radacina);
                heapuri[x].repara();
                heapuri[y].erase()
            }


        }
    }