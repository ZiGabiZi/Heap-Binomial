#include <iostream>
using namespace std;
#include <vector>
#include <fstream>

ifstream f("C:\\Users\\User\\CLionProjects\\BinomHeap\\mergeheap.in");
ofstream g("C:\\Users\\User\\CLionProjects\\BinomHeap\\mergeheap.out");

class Nod{
public:
    int valoare;
    int grad;
    Nod* tata;
    vector<Nod*> fii;

public:
    int getValoare() const {
        return valoare;
    }

    Nod(int valoare, int grad, Nod *tata, const vector<Nod *> &fii) : valoare(valoare), grad(grad), tata(tata),
                                                                      fii(fii) {};
    Nod(){
        valoare = -1;
        grad = 0;
        tata = nullptr;

    }
    void display(){
        if (grad == 0)
            cout << endl <<"Valoare nod: " << valoare << " nu are fii" <<endl;
        if(grad > 0) {
            cout <<  "Valoare nod: " << valoare << endl;
            cout << "Valori fii nod " << valoare << ": ";
            for (int i = 0; i < grad; i++) {
                cout << fii[i]->valoare << " ";
            }
            for (int i = 0; i < grad; i++)
                fii[i]->display();
            cout << endl;
        }
        cout << endl;
    }

    void setValoare(int valoare) {
        Nod::valoare = valoare;
    }




};
class Heap{
public:
    vector<Nod*> radacini;
    Nod* max_nod = new Nod();

    Heap(const Heap &h)
    {
        radacini = h.radacini;
        max_nod = h.max_nod;
    }

    Heap(){
        max_nod = NULL;
    }

    void delete_heap ()
    {
        radacini.clear();
        max_nod = NULL;
    }

    void insert(int valoare){
        Nod *nod = new Nod();
        nod->valoare = valoare;
        if(radacini.size() == 0)
        {
            radacini.push_back(nod);
            radacini.push_back(NULL);
            max_nod = nod;
        }
        else
        {
            if(max_nod->valoare < nod->valoare)
                max_nod = nod;
            int i = 0;
            Nod* radacina = nod;
            Nod* aux = radacini[0];
            while (aux != NULL)
            {
                if (aux->valoare > radacina->valoare)
                {
                    aux->fii.push_back(radacina);
                    radacina->tata = aux;
                    aux->grad ++;
                    radacina = aux;
                }
                else{
                    radacina->fii.push_back(aux);
                    aux->tata = radacina;
                    radacina->grad ++;
                }
                if(radacina->grad == radacini.size())
                    radacini.push_back(NULL);
                radacini[i] = NULL;
                i++;
                aux = radacini[i];
            }
            radacini[i] = radacina;
        }
    }

    int get_nod_max() {return max_nod->valoare;}

    Heap& operator + (Heap &h)
    {
        int i;
        if (h.radacini.size() > radacini.size())
        {
            i = h.radacini.size() - radacini.size();
            while (i)
            {
                radacini.push_back(NULL);
                i --;
            }
        }
        for (int j = 0; j < h.radacini.size(); j++)
        {
            if (h.radacini[j] != NULL) {
                if (max_nod->valoare < h.radacini[j]->valoare)
                    max_nod = h.radacini[j];
                int i = h.radacini[j]->grad;
                Nod *radacina = h.radacini[j];
                Nod *aux = radacini[h.radacini[j]->grad];
                while (aux != NULL) {
                    if (aux->valoare > radacina->valoare) {
                        aux->fii.push_back(radacina);
                        radacina->tata = aux;
                        aux->grad++;
                        radacina = aux;
                    } else {
                        radacina->fii.push_back(aux);
                        aux->tata = radacina;
                        radacina->grad++;
                    }
                    if (radacina->grad == radacini.size())
                        radacini.push_back(NULL);
                    radacini[i] = NULL;
                    i++;
                    aux = radacini[i];
                }
                radacini[i] = radacina;
            }
        }
        h.delete_heap();
    }

    Heap& operator + (Nod* &n)
    {
        if (n->tata != NULL)
            n->tata = NULL;
        if (radacini.size() < n->grad)
        {
            while(radacini.size() <= n->grad)
                radacini.push_back(NULL);
            radacini[radacini.size()-1] = n;
        }
        else
        {
            int i = n->grad;
            Nod* radacina = n;
            Nod* aux = radacini[i];
            while (aux != NULL)
            {
                if (aux->valoare > radacina->valoare)
                {
                    aux->fii.push_back(radacina);
                    radacina->tata = aux;
                    aux->grad ++;
                    radacina = aux;
                }
                else{
                    radacina->fii.push_back(aux);
                    aux->tata = radacina;
                    radacina->grad ++;
                }
                if(radacina->grad == radacini.size())
                    radacini.push_back(NULL);
                radacini[i] = NULL;
                i++;
                aux = radacini[i];
            }
            radacini[i] = radacina;
        }
    }

    void display(){
        int nr_radacini = 0;
        cout << "Heapul binomial: " << endl;
        cout << radacini.size() << endl;
        for(int i = 0; i < radacini.size(); i++)
        {
            if(radacini[i] != NULL) {
                nr_radacini ++;
                cout << "\t" << "Radacina " << nr_radacini << " cu valoarea " << radacini[i]->valoare << ": " << endl;
                radacini[i]->display();
            }
        }
        cout << endl << "Numar radacini: " << nr_radacini;

    }

    void eliminare_maxim(){
        Heap h(*this);
        cout << "Maximul: " << h.max_nod->valoare << endl;
        h.radacini[h.max_nod->grad] = NULL;
        for (int i = 0; i < h.max_nod->fii.size(); i++) {
            h + h.max_nod->fii[i];
        }
        Nod* new_max = new Nod();
        for (int i = 0; i < h.radacini.size(); i++) {
            if (h.radacini[i]->valoare > new_max->valoare)
                new_max = h.radacini[i];
        }
        h.max_nod = new_max;
    }


};

int main() {
    Heap h;
    h.insert(3);
    h.insert(1);
    h.insert(2);
    h.insert(5);
    h.insert(9);
    h.insert(8);
    h.insert(12);
    h.insert(4);
    h.insert(69);
    h.insert(11);
    h.insert(14);
    h.insert(23);
    h.insert(58);
    h.insert(91);
    h.insert(80);
    h.insert(12);
    //h.insert(5);
//    Nod* n = new Nod();
//    n->valoare = 3;
//    h+n;
//    Nod* m = new Nod();
//    m->valoare = 4;
//    h+m;



    h.display();

    int operatii, obiecte;
    vector<Heap> heapuri;
    f >> obiecte >> operatii;
    for(int i=1;i<=obiecte;i++){
        Heap h2;
        heapuri.push_back(h2);
    }


    int operatie;
    while(f>> operatie) {
        switch (operatie) {
            case 1: {
                int nr_heap, element;
                f >> nr_heap >> element;
                heapuri[nr_heap].insert(element);
                break;
            }

            case 2:{
                int nr_heap;
                f >> nr_heap;
                g << heapuri[nr_heap].get_nod_max();
                heapuri[nr_heap].eliminare_maxim();
                break;
            }

            case 3:{
                int nr_heap1, nr_heap2;
                f >> nr_heap1 >> nr_heap2;
                heapuri[nr_heap1] + heapuri[nr_heap2];
                break;
            }
            default:{
                cout << "IDK";
            }

          

        }
    }
    f.close();
    g.close();

    return 0;
}
