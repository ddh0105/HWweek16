#include<bits/stdc++.h>
using namespace std;



struct avlNode{
    int key;
    int height;//chieu cao cua nut
    avlNode *left, *right;
    avlNode(int k, int h, avlNode *l, avlNode *r): key(k), height(h), left(l), right(r){}
};

typedef avlNode avl;

//ham tra ve chieu cao cua nut
int getheight(avl* t){
    return t == NULL?-1: t->height;
}

//PHEP XOAY DON

//phep xoay don (xoay phai voi con trai)
void rotateWithLeftChild(avl *& k2){
    avl * k1 = k2->left; // khai bao k1 gan voi con trai cua k2
    k2->left = k1->right; //k2 tro den cay con phai k1
    k1->right = k2; //k1 thanh cha cua k2
    k2->height = max(getheight(k2->left), getheight(k2->right))+1;
    k1->height = max(getheight(k1->left), (k2->height))+1;
    k2 = k1; //k1 tro thanh nut goc moi
}

//Phep xoay trai voi con phai
void rotateWhithRightChild(avl *& k2){
    avl* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = max(getheight(k2->left), getheight(k2->right))+1;
    k1->height = max(getheight(k1->right), k2->height)+1;

    k2 = k1;
}

//PHEP XOAY KEP
//phep xoay trai-phai: xoay trai o con trai sau do xoay phai o nut goc
void doubleRotateWithLeftChild(avl *& k3){
    rotateWhithRightChild(k3->left);//xoay trai o con trai
    rotateWithLeftChild(k3);//xoay phai o nut goc

}

//phep xoay phai-trai: xoay phai o con phai, sau do xoay trai o nut goc
void doubleRotateWithRightChild(avl *& k3){
    rotateWithLeftChild(k3->right);//xoay phai o con phai
    rotateWhithRightChild(k3);//xoay trai o nut goc
}

//ham can bang cay avl
void balance(avl *& t){
    if (t == NULL){
        return ;
    }
    if ((getheight(t->left)-getheight(t->right))>1){
        if (getheight(t->left->left)>= getheight(t->left->right)) 
            rotateWithLeftChild(t);
        else 
            doubleRotateWithLeftChild(t);
    }
    else if ((getheight(t->right))-getheight(t->left)>1){
        if (getheight(t->right->right)>=getheight(t->right->left)){
            rotateWhithRightChild(t);
        }
        else 
            doubleRotateWithRightChild(t);
    }
    t->height = max(getheight(t->left), getheight(t->right))+1;
}

//ham nhap node moi
avl* insert(int k, avl*& t){
    if (t == NULL){
        t = new avl(k, 0, NULL, NULL);
    }
    else if (k < t->key) insert(k, t->left);
    else if (k > t->key) insert(k, t->right);
    balance(t);
    return t;
}

//ham findMin
avl* findMin(avl* t) {
    if (t == NULL) return NULL;//cay rong
    while (t->left != NULL) {
        t = t->left; // di toi nut trai nhat
    }
    return t; //tra ve nut co gia tri nho nhat
}


//ham xoa node
void remove(int k, avl *& t){
    if (t == NULL) return;//dung ham
    if ( k < t->key){
        remove(k, t->left);
    }
    else if (k > t->key){
        remove (k, t->right);
    }
    else if (t->left != NULL && t->right != NULL){
        //nut 2 con
        t->key = findMin(t->right)->key;
        remove(t->key, t->right);
    }
    else {
        //nut 1 con hoac nut la
        avl * old = t;
        t = (t->left != NULL) ? t->left:t->right;
        delete old;
    }
    balance (t);//can bang cay sau khi xoa
}

//in cay theo thu tu duyet

//thu tu truoc
void preOrder(avl *t){
    if (t){
        cout << t->key<<" ";
        preOrder(t->left);
        preOrder(t->right);
    }
}

//thu tu giua
void inOrder(avl *t){
    if(t){
        inOrder(t->left);
        cout << t->key<<" ";
        inOrder(t->right);
    }
}
//thu tu sau
void postOrder(avl *t){
    if (t){
        postOrder(t->left);
        postOrder(t->right);
        cout << t->key<<" ";
    }
}

//ham nhap day so, xay dung cay avl
avl* Input(const int arr[], int n){
    avl* root = NULL;
    for (int i = 0; i <n; i++){
        root = insert(arr[i], root);
        cout <<"Cay avl sau lan chen '"<<arr[i]<<"' (duyet theo thu tu giua): "<<" ";
        inOrder(root);
        cout << endl;
        cout <<"Cay avl sau lan chen '"<<arr[i]<<"' (duyet theo thu tu truoc): "<<" ";
        preOrder(root);
        cout <<endl;
        cout <<"Cay avl sau lan chen '"<<arr[i]<<"' (duyet theo thu tu sau): "<<" ";
        postOrder(root);
        cout << endl<<"------------------------"<<endl;
    }
    return root;
}

int main(){
    int arr[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};
    int n = sizeof(arr)/sizeof(arr[0]);

    avl* root = Input(arr, n);



    return 0;

}
