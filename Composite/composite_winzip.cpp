#include<bits/stdc++.h>
using namespace std;

class CompressibleComponent{
    public:
    string name;
    virtual void zip(CompressibleComponent* ptr)=0;
};

class Folder : public CompressibleComponent{
    private:
    vector<CompressibleComponent*> items;
    public:
    string name;
    void zip(CompressibleComponent* ptr){
        cout<<"Compressing "<<ptr->name<<"..."<<endl;
        for(int i=0;i<items.size();i++){
            items[i]->zip(items[i]);
        }
    }
    void addComponent(CompressibleComponent *ptr, string name){
        items.push_back(ptr);
        ptr->name=name;
    }
};

class File : public CompressibleComponent{
    public:
    string name;
    void zip(CompressibleComponent* ptr){
        cout<<"Compressing "<<ptr->name<<"..."<<endl;
    }
};

int main(){
    Folder CDrive;
    CompressibleComponent* ptr;
    ptr=&CDrive;
    ptr->name="CDrive";
    Folder A;
    Folder B;
    Folder C;
    File file1;
    File file2;
    File file3;
    File file4;
    File file5;
    CDrive.addComponent(&A,"A");
    CDrive.addComponent(&B,"B");
    CDrive.addComponent(&C,"C");
    CDrive.addComponent(&file1,"file1");
    CDrive.addComponent(&file2,"file2");
    A.addComponent(&file3,"file3");
    B.addComponent(&file4,"file4");
    C.addComponent(&file5,"file5");
    CDrive.zip(&CDrive);
}