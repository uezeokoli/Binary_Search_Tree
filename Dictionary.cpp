// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA7
// *  Dictionary.cpp
// *  Implementation file for Dictionary ADT
// *****************************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#include<ctype.h>

// Class Constructors & Destructors ----------------------------------------

//Node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    num_pairs = 0;

    Node* R = D.root;
    this->preOrderCopy(R);
}

// Destructor
Dictionary::~Dictionary(){
    this->clear();
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    Node* F = root; // Find
    while (F != nil){
        if ((k == F->key)){
            return true;
        }
        else if (k < F->key){
            F = F->left;
        }
        else{ // k > x.key
            F = F->right;
        }
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if (!this->contains(k)){
        throw std::invalid_argument("Dictionary getValue(): key does not exist");
    }
    Node* F = root; // Find
    while (F != nil){
        if ((k == F->key)){
            return F->val;
        }
        else if (k < F->key){
            F = F->left;
        }
        else{ // k > x.key
            F = F->right;
        }
    }
    return F->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return (current != nullptr);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if (!this->hasCurrent()){
        throw std::invalid_argument("Dictionary currentKey(): current is undefined");
    }
    
    return current->key;

}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if (!this->hasCurrent()){
        throw std::invalid_argument("Dictionary currentVal(): current is undefined");
    }

    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){

    while (num_pairs > 0){
        this->remove(root->key);
    }

}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* T = root; //traverse
    Node* P = nullptr; //parent
    while(T != nil){
        P = T;
        if (k == T->key){
            T->val = v;
            return;
        }
        else if(k < T->key){
            T = T->left;
        }
        else{
            T = T->right;
        }
    }
    //exits while loop means new pair added
    Node* I = new Node(k,v); // insert
    num_pairs++;
    I->parent = P;
    if (P == nil){ //tree empty
         root = I;
    }
    else if (I->key < P->key){
        P->left = I;
    }
    else{
        P->right = I;

    }

    //PSUEDO CODE
    // y = NIL
    // x = T.root
    // while x != NIL
    //     y = x
    //     if z.key < x.key
    //         x = x.left
    //     else 
    //         x = x.right
    // z.parent = y
    // if y == NIL             // T was empty
    //     T.root = z    
    // else if z.key < y.key
    //     y.left = z
    // else 
    //     y.right = z
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if (!this->contains(k)){
        throw std::invalid_argument("Dictionary remove(): key does not exist");
    }

    // if current is pair then current undefined
    if (current != nil){
        if (this->currentKey() == k){
            current = nullptr;
        }
    }

    if (num_pairs == 1){
        delete root;
        root = nullptr;
        current = nullptr;
        num_pairs = 0;
        return;
    }

    Node* F = root; // Find
    while (F != nil){
        if ((k == F->key)){
            this->Delete(F);
            delete F;
            num_pairs--;
            return;
        }
        else if (k < F->key){
            F = F->left;
        }
        else{ // k > x.key
            F = F->right;
        }
    }


}

void Dictionary::Transplant(Dictionary::Node *U, Dictionary::Node *V){
// Transplant(T, u, v)
    // if u.parent == NIL
    //     T.root = v
    // else if u == u.parent.left
    //     u.parent.left = v
    // else 
    //     u.parent.right = v
    // if v != NIL
    //     v.parent = u.parent

    if (U->parent == nullptr){
        root = V;
    }
    else if (U == U->parent->left){
        U->parent->left = V;
    }
    else{
        U->parent->right = V;
    }
    if (V != nullptr){
        V->parent = U->parent;
    }
}

void Dictionary::Delete(Dictionary::Node *Z){
    // Delete(T, z)
    // if z.left == NIL               // case 1  or case 2.1 (right only)
    //     Transplant(T, z, z.right)
    // else if z.right == NIL         // case 2.2 (left only)
    //     Transplant(T, z, z.left)
    // else                           // case 3
    //     y = TreeMinimum(z.right)
    //     if y.parent != z
    //         Transplant(T, y, y.right)
    //         y.right = z.right
    //         y.right.parent = y
    //     Transplant(T, z, y)
    //     y.left = z.left
    //     y.left.parent = y
    Node* Y;
    if (Z->left == nullptr){
        this->Transplant(Z,Z->right);
    }
    else if (Z->right == nullptr){
        this->Transplant(Z,Z->left);
    }
    else{
        Y = this->findMin(Z->right);
        if (Y->parent != Z){
            this->Transplant(Y,Y->right);
            Y->right = Z->right;
            Y->right->parent = Y;
        }
        this->Transplant(Z,Y);
        Y->left = Z->left;
        Y->left->parent = Y;
        

    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if (num_pairs == 0){
        return;
    }
 
    current = root;
    while(current->left != nullptr){
        current = current->left;
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if (num_pairs == 0){
        return;
    }

    current = root;
    while(current->right != nullptr){
        current = current->right;
    }

}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if (!this->hasCurrent()){
        throw std::invalid_argument("Dictionary next(): current is undefined");
    }

    // TreeSuccessor(x)
    // if x.right != NIL                 // case 1
    //     return TreeMinimum(x.right)
    // y = x.parent                      // case 2
    // while y != NIL and x == y.right
    //     x = y
    //     y = y.parent
    // return y


    Node* dummy;
    if(current->right != nullptr){
        current = current->right;
        while(current->left != nullptr){
            current = current->left;
        }
    }
    else{
        dummy = current->parent;
        while((dummy != nullptr) && (current == dummy->right)){
            current = dummy;
            dummy = dummy->parent;
        }
        current = dummy;
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if (!this->hasCurrent()){
        throw std::invalid_argument("Dictionary prev(): current is undefined");
    }

    Node* dummy;
    if(current->left != nullptr){
        current = current->left;
        while(current->right != nullptr){
            current = current->right;
        }
    }
    else{
        dummy = current->parent;
        while((dummy != nullptr) && (current == dummy->left)){
            current = dummy;
            dummy = dummy->parent;
        }
        current = dummy;
    }
}


// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Dictionary::Node* R) const{
    std::string str_val;
    if (R != nil){
        inOrderString(s,R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s,R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    std::string str_val;
    if (R != nil){
        s += R->key + "\n";
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Dictionary::Node *R){
    if (R != nil){
        this->setValue(R->key,R->val);
        preOrderCopy(R->left);
        preOrderCopy(R->right);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Dictionary::Node *R){
// PSUEDO
// TreeMinimum(x) Pre: x != NIL
//    while x.left != NIL
//       x = x.left
//    return x
    while(R->left != nullptr){
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Dictionary::Node *R){
// Pseudo
// TreeMaximum(x) Pre: x != NIL
//    while x.right != NIL
//       x = x.right
//    return x
    while(R->right != nullptr){
        R = R->right;
    }
    return R;

}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s;
    this->inOrderString(s,root);
    return s;

}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s;
    this->preOrderString(s,root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    Dictionary Copy_T = *this;
    Dictionary Copy_D = D;
    if (this->num_pairs != D.num_pairs){
        return false;
    }
    Copy_T.begin();
    Copy_D.begin();
    while (Copy_T.hasCurrent()){
        if (Copy_T.currentKey() != Copy_D.currentKey()){
            return false;
        }

        if (Copy_T.currentVal() != Copy_D.currentVal()){
            return false;
        }
        Copy_T.next();
        Copy_D.next();
    }
    return true;

}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    nil = nullptr;

    Dictionary Copy_D = D;
    for(Copy_D.begin(); Copy_D.hasCurrent(); Copy_D.next()){
        this->setValue(Copy_D.currentKey(),Copy_D.currentVal());
    }
    return *this;
}
