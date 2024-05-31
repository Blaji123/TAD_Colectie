#include "IteratorColectie.h"
#include "Colectie.h"

//Theta(1)
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	st = std::stack<int>{};
    prim();
}

//Theta(1)
TElem IteratorColectie::element() const{
	if(valid())
        return col.Tree[current].val;
    else
        throw std::exception();
}

//Theta(1)
bool IteratorColectie::valid() const {
	return current!=-1;
}

//Theta(logn)
void IteratorColectie::urmator() {
	if(!valid())
        throw std::exception();
    int node = st.top();
    st.pop();
    if(col.Tree[node].right!=-1){
        node = col.Tree[node].right;
        while(node!=-1){
            st.push(node);
            node = col.Tree[node].left;
        }
    }
    if(!st.empty())
        current = st.top();
    else
        current = -1;
}

//Theta(logn)
void IteratorColectie::prim() {
	current = col.root;
    if(!st.empty())
        while(!st.empty())
            st.pop();
    while(current!=-1){
        st.push(current);
        current = col.Tree[current].left;
    }
    if(!st.empty())
        current = st.top();
    else
        current = -1;
}
