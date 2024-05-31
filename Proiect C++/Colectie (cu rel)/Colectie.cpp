#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <unordered_map>

using namespace std;

//complexity : Theta(1)
bool rel(TElem e1, TElem e2) {
	return e1<=e2;
}

//complexity : Theta(1)
Colectie::Colectie() {
	root = -1;
    numberOfElements = 0;
    capacity = 16;
    firstFree = 0;
    Tree = new Node[capacity];
}

//complexity: avg: Theta(logn)
//            worst case: Theta(n) *cand arborele este degenerat*
void Colectie::adauga(TElem e) {
	if(firstFree>=capacity){
        resize();
    }
    //adaugam elementul pe first free
    Tree[firstFree].val = e;
    Tree[firstFree].left = -1;
    Tree[firstFree].right = -1;
    // cautam pozitia pe care adaugam nodul
    int current = root, parent = -1;
    while(current!=-1){
        parent = current;
        if(rel(e, Tree[current].val))
            current = Tree[current].left;
        else
            current = Tree[current].right;
    }
    //cazul in care nu avem radacina
    if(root==-1)
        root = firstFree;
    //cazul in care trebuie sa adauga in fiul stang
    else if(rel(e, Tree[parent].val))
        Tree[parent].left = firstFree;
    else
    //altfel se adauga in fiul drept
        Tree[parent].right = firstFree;
    updateFirstFree();
    numberOfElements++;
}

//Theta(capacity)
void Colectie::updateFirstFree() {
    ++firstFree;
    while (firstFree < capacity && !Tree[firstFree].isNull())
        ++firstFree;
}

//complexity: avg: Theta(logn)
//            worst case: Theta(n) *cand arborele este degenerat*
bool Colectie::sterge(TElem e) {
	bool removed = false;
    root = removeRecursively(root, e, removed);
    if(removed)
        numberOfElements--;
    return removed;
}

//complexity: avg: Theta(logn)
//            worst case: Theta(n) *cand arborele este degenerat*
bool Colectie::cauta(TElem elem) const {
	int current = root;
    while(current!=-1){
        if(Tree[current].val == elem)
            return true;
        if(rel(elem, Tree[current].val))
            current = Tree[current].left;
        else
            current = Tree[current].right;
    }
    return false;
}

//complexity: avg: Theta(logn)
//            worst case: Theta(n) *cand arborele este degenerat*
int Colectie::nrAparitii(TElem elem) const {
    int current = root;
    int cnt = 0;

    while (current != -1) {
        if (Tree[current].val == elem)
            cnt++;
        if (rel(elem, Tree[current].val)) {
            current = Tree[current].left;
        }
        else {
            current = Tree[current].right;
        }
    }
    return cnt;
}

//complexity: Theta(1)
int Colectie::dim() const {
	return numberOfElements;
}

//complexity: Theta(1)
bool Colectie::vida() const {
    return numberOfElements==0;
}

//complexity: Theta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//complexity: Theta(1)
Colectie::~Colectie() {
	delete[] Tree;
}

/*
 * Functie eliminaToateDuplicate()
 *      daca vida() atunci
 *          @std::exception()
 *      sfDaca
 *      elementCount;
 *      numRemoved <- 0;
 *      it <- iterator();
 *      cat timp it.valid() executa
 *          elem <- it.element()
 *          elementCount[elem] <- elementCount[elem] + 1
 *          it.urmator()
 *      sfCatTimp
 *      it2 <- iterator();
 *      cat timp it2.valid() executa
 *          elem <- it.element();
 *          daca elementCount[elem] > 1 atunci
 *              cat timp cauta(elem) executa
 *                  sterge(elem)
 *                  numRemoved <- numRemoved + 1
 *              sfCatTimp
 *          sfDaca
 *          it2.urmator()
 *      sfCatTimp
 *      eliminaToateDuplicate<-numRemoved
 * sfFunctie
 * complexity : Theta(n)
 */
int Colectie::eliminaToateDuplicate() {
    if(this->vida()){
        throw std::exception();
    }
    unordered_map<TElem, int> elementCount;
    int numRemoved = 0;

    // Traverse the tree to count occurrences
    IteratorColectie it = this->iterator();
    while (it.valid()) {
        TElem elem = it.element();
        elementCount[elem]++;
        it.urmator();
    }

    // Traverse the tree to remove duplicates
    IteratorColectie it2 = this->iterator();
    while (it2.valid()) {
        TElem elem = it2.element();
        if (elementCount[elem] > 1) {
            while (cauta(elem)) {
                sterge(elem);
                numRemoved++;
            }
        }
        it2.urmator();
    }

    return numRemoved;
}

//Theta(capacity)
void Colectie::resize() {
    Node* newTree = new Node[2 * capacity];
    for(int i=0;i<capacity;i++){
        newTree[i].val = Tree[i].val;
        newTree[i].left = Tree[i].left;
        newTree[i].right = Tree[i].right;
    }
    delete[] Tree;
    Tree = newTree;
    firstFree = capacity;
    capacity*=2;
}

//Theta(logn)
TElem Colectie::getMaximum(int startingRoot) {
    int currentNode = startingRoot, maxNode = startingRoot;

    while (currentNode != -1) {
        maxNode = currentNode;
        currentNode = Tree[currentNode].right;
    }
    return maxNode;
}

//Theta(logn)
int Colectie::removeRecursively(int node, TElem e, bool &removed) {
    if(node==-1)
        return node;
    //cazul in care am gasit elementul
    if(e==Tree[node].val){
        removed = true;
        //daca nu exista fiu stang, inseamna ca mutam subarborele care incepe in fiul drept
        //peste cel determinat de node
        if(Tree[node].left == -1){
            int right = Tree[node].right;
            Tree[node] = Node{};
            return right;
        //daca nu exista fiu drept, inseamna ca mutam subarborele care incepe in fiul stang
        //peste cel determinat de node
        }else if(Tree[node].right == -1){
            int left = Tree[node].left;
            Tree[node] = Node{};
            return left;
        }
        int maxNode = getMaximum(Tree[node].left);
        Tree[node].val = Tree[maxNode].val;
        Tree[node].left = removeRecursively(Tree[node].left, Tree[maxNode].val, removed);
    }else if(rel(e, Tree[node].val)){
        Tree[node].left = removeRecursively(Tree[node].left, e, removed);
    }else{
        Tree[node].right = removeRecursively(Tree[node].right, e, removed);
    }
    return node;
}