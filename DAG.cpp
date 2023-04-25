//
//  main.c
//  DAG
//
//  Created by Anshu Aaron Varma on 19/04/23.
//

#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
class DAG
{   public:
    char label;
    char data;
    DAG* left;
    DAG* right;
    
    DAG(char x){
      label='_';
      data=x;
      left=NULL;
      right=NULL;
    }
    DAG(char lb, char x, DAG* lt, DAG* rt){
      label=lb;
      data=x;
      left=lt;
      right=rt;
    }
};

int main(){
    int n;
    n=3;
    string st[n];//C=((x+y)*z)/x
    st[0]="E=x+y";
    st[1]="F=E*z";
    st[2]="G=F/x";
    unordered_map<char, DAG*> labelDAGNode;
    
    for(int i=0;i<3;i++){
        string stemp=st[i];
        for(int j=0;j<5;j++){
            char tempLabel = stemp[0];
            char templeft = stemp[2];
            char tempdata = stemp[3];
            char tempright = stemp[4];
            DAG* leftPtr;
            DAG* rightPtr;
            if(labelDAGNode.count(templeft) == 0){
                leftPtr = new DAG(templeft);
            }
            else{
                leftPtr = labelDAGNode[templeft];
            }
            if(labelDAGNode.count(tempright) == 0){
                rightPtr = new DAG(tempright);
            }
            else{
                rightPtr = labelDAGNode[tempright];
            }
            DAG* nn = new DAG(tempLabel,tempdata,leftPtr,rightPtr);
            labelDAGNode.insert(make_pair(tempLabel,nn));
        }
    }
    cout<<"Label |     ptr    |  leftPtr |    rightPtr"<<endl;
    for(int i=0;i<n;i++){
        DAG* x=labelDAGNode[st[i][0]];
        cout<<st[i][0]<<"     |      "<<x->data<<"     |     ";
        if(x->left->label=='_')cout<<x->left->data;
        else cout<<x->left->label;
        cout<<"    |       ";
        if(x->right->label=='_')cout<<x->right->data;
        else cout<<x->right->label;
        cout<<endl;
    }
    return 0;
}
