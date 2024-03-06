#include <iostream>
#include <stack>

class Node {
public:

    Node* lchild;
    int data;
    Node* rchild;

    Node(){
        this->lchild = NULL;
        this->data = 0;
        this->rchild = NULL;
    }

    Node(int data){
        this->lchild = NULL;
        this->data = data;
        this->rchild = NULL;
    }
};

class Tree {
private:
    Node* root;

public:
    Tree(){
        root = NULL;
    }
    void insert(int key);
    Node* Rinsert(Node* root, int key);
    Node* search(int key);
    void inorder(Node* root);
    void preorder();
    int height(Node* root);
    Node* Tdelete(Node* root, int key);
    Node* inPre(Node* root);
    Node* inSuc(Node* root);
    Node* getRoot(){
        return root;
    }

};

void Tree::insert(int key){
    
    Node* t = new Node(key);
    Node* p = root;
    Node* q = NULL;
    
    if(p == NULL){
        root = t;
        return;
    }

    while(p) {
        q = p;
        if(p->data == key){
            std::cout<<"Same key allready exist"<<std::endl;
            return;
        }
        else if(p->data < key){
            p = p->rchild;
        } else {
            p = p->lchild;
        }
    }

    if(q->data < key){
        q->rchild = t;
    } else {
        q->lchild = t;
    }

}

Node* Tree::Rinsert(Node* p, int key){
    

    
    if(!p){
        return new Node(key);
    }

    if(key > p->data){
        p->rchild = Rinsert(p->rchild, key);
    } else if(key < p->data){
        p->lchild = Rinsert(p->lchild, key);
    }

    return p;
    
}


Node* Tree::search(int key) {

    Node* p = root;
    
    if(root == NULL){
        return NULL;
    }

    while(p) {

        if(p->data == key){
            return p;
        }
        else if(p->data < key){
            p = p->rchild;
        } else {
            p = p->lchild;
        }
    }
    return NULL;
}

void Tree::inorder(Node* p){

    
    std::stack<Node*> st;

    while(p || !st.empty()){
        if(p){
            st.push(p);
            p = p->lchild;
        } else {
            p = st.top();
            st.pop();
            std::cout<<p->data<<" ";
            p = p->rchild;
        }
    }
}

void Tree::preorder(){

    Node* p = root;
    std::stack<Node*> st;

    while(p || !st.empty()){
        if(p){
            st.push(p);
            std::cout<<p->data<<" ";
            p = p->lchild;
        } else {
            p = st.top();
            st.pop();
            p = p->rchild;
        }
    }
}

int Tree::height(Node* root){
    if(!root) {
        return  0;
    }

    int lh = height(root->lchild);
    int rh = height(root->rchild);

    return lh>rh? lh+1 : rh+1;
}

Node* Tree::inPre(Node* p) {
    
    while(p && p->rchild) {
        p = p->rchild;
    }

    return p;
}

Node* Tree::inSuc(Node* p) {
    
    while(p && p->lchild) {
        p = p->lchild;
    }

    return p;
}

Node* Tree::Tdelete(Node* root, int key){

    Node* q = NULL;
    if(!root){
        return NULL;
    }

    if(!root->lchild && !root->rchild){
        
        if(root == this->getRoot()){
            root = NULL;
        }
        delete root;
        return NULL;
    }

    if(key > root->data){
        root->rchild = Tdelete(root->rchild, key);
    } else if(key < root->data){
        root->lchild = Tdelete(root->lchild, key);
    } else {
        if(height(root->lchild) > height(root->rchild)){
            q = inPre(root->lchild);
            root->data = q->data;
            root->lchild = Tdelete(root->lchild, q->data);
        } else {
            q = inSuc(root->rchild);
            root->data = q->data;
            root->rchild = Tdelete(root->rchild, q->data);
        }
    }
    return root;
}


int main() {

    Tree t;
    Node* root = NULL;
    root = t.Rinsert(root, 1);
    t.Rinsert(root, 4);
    t.Rinsert(root, 6);
    t.Rinsert(root, 2);
    t.Rinsert(root, 3);
    t.Rinsert(root, 7);
    t.Rinsert(root, 9);
    t.Rinsert(root, 0);
    t.Rinsert(root, 8);
    
    
    // t.insert( 1);
    // t.insert( 4);
    // t.insert( 6);
    // t.insert( 2);
    // t.insert( 3);
    // t.insert( 7);
    // t.insert( 9);
    // t.insert( 0);
    // t.insert( 8);
 
    t.inorder(root);
    std::cout<<std::endl;

    t.Tdelete(root, 1);
    t.inorder(root); 
    std::cout<<std::endl;
    t.preorder();
    return 0;
}