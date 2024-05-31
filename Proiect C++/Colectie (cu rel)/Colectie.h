#pragma once;

typedef int TElem;
const int NULL_TCOMP = -99999999;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Node{
public:
    TElem val;
    int left;
    int right;
    Node(){
        val = NULL_TCOMP;
        left = -1;
        right = -1;
    }
    Node(TElem val, int left, int right):val{val},left{left},right{right}{}
    bool isNull(){
        return val == NULL_TCOMP;
    }
    ~Node()=default;
};

class Colectie {

	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
    Node* Tree;
    int root;
    int numberOfElements;
    int capacity;
    int firstFree;

    void updateFirstFree();
    void resize();
    int removeRecursively(int node, TElem e, bool &removed);
    TElem getMaximum(int startingRoot);
    int removeDuplicatesRecursively(int node, TElem lastSeen);
public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;

        int eliminaToateDuplicate();

		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();


};

