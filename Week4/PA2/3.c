class Array2{
    private:
        int size1, size2;
        int index1,index2;
        int** ptr;

    public:
        Array2(int _size1=0, int _size2=0);
        Array2(const Array2& b);
        Array2& operator=(int ele);
        Array2& operator=(const Array2& b);
        Array2& operator[](int index); 
        Array2& operator()(int i, int j);
        friend ostream& operator<<(ostream& os, const Array2& c);
        void changeIndex(int _index1, int _index2);
        int getEle(){
            return ptr[index1][index2];
        }
        int id1(){return index1;}
        int id2(){return index2;}
        ~Array2(){
            if(!ptr){
                for(int i=0; i<size1; i++){
                    delete [] ptr[i];
                }
                delete [] ptr;
            }
        }
};

void Array2::changeIndex(int _index1, int _index2){
    index1 = _index1;
    index2 = _index2;
}

Array2& Array2::operator()(int i, int j){
    index1 = i;
    index2 = j;
    return *this;
}

Array2::Array2(int _size1, int _size2){
    size1 = _size1;
    size2 = _size2;
    index1 = -1; index2 = -1;
    if( _size1 == 0 || _size2 == 0){
        ptr = NULL;
    }
    else{
        ptr = new int*[size1];
        for (int i=0; i<size1; i++){
            ptr[i] = new int[size2];
        }
    }
}

Array2::Array2(const Array2& b){
    size1 = b.size1;
    size2 = b.size2; 
    index1 = b.index1;
    index2 = b.index2;
    if (!b.ptr){
        if(ptr){ 
            for(int i=0; i<size1;i++){
                delete [] ptr[i];
            }
            delete [] ptr;
        }
    }
    else{ 
        if(ptr){
            for(int i=0; i<size1;i++){
                delete [] ptr[i];
            }
            delete [] ptr;
        }
     
        ptr = new int*[size1];
        for (int i=0; i<size1; i++){
            ptr[i] = new int[size2];
            memcpy(ptr[i],b.ptr[i],sizeof(int)*size2);
        }
    }

}


Array2& Array2::operator=(const Array2& b){
    size1 = b.size1;
    size2 = b.size2; 
    index1 = b.index1;
    index2 = b.index2;
    if (!b.ptr){
        if(ptr){ 
            for(int i=0; i<size1;i++){
                delete [] ptr[i];
            }
            delete [] ptr;
        }
    }
    else{ 
        if(ptr){
            for(int i=0; i<size1;i++){
                delete [] ptr[i];
            }
            delete [] ptr;
        }
     
        ptr = new int*[size1];
        for (int i=0; i<size1; i++){
            ptr[i] = new int[size2];
            memcpy(ptr[i],b.ptr[i],sizeof(int)*size2);
        }
    }
    return *this;
}

Array2& Array2::operator=(int ele){
    if (index1 == -1 || index2 == -1){
        cout<<"INSUFFICIENT INDEXING"<<endl;
    }
    ptr[index1][index2] = ele;
    index1 = -1;
    index2 = -1;
    return *this;
}

Array2& Array2::operator[](int index){
    if(index1 == -1){
        index1 = index;
    }
    else if(index2 == -1){
        index2 = index;
    }
    else{
        cout<<"REDUNDANT INDEXING!!!"<<endl;
    }
    return *this; 
}


ostream& operator<<(ostream& os, Array2& c){
    os<<c.getEle();
    c.changeIndex(-1,-1);
    return os;
}


