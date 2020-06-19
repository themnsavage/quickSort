#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
#include<vector>
#include<sstream>
#include<iomanip>
#include<string.h>
using namespace std;
class Object{
    private:
    vector <string>data;
    public:
    Object(vector<string>data){//makes the object by setting data
        this->data=data;
    }
    vector <string> get_vect(){//returns the objects data
        return data;
    }
    void print_object(){//prints the object data
        for(int i=0;i<data.size();i++){
            if(i==data.size()-1){
                cout<<data.at(i);
            }
            else{
            cout<<data.at(i)<<",";
            }
        }
    }
    void out_file(ofstream &file){
          for(int i=0;i<data.size();i++){
            if(i==data.size()-1){
                file<<data.at(i);
            }
            else{
            file<<data.at(i)<<",";
            }
        }
    }
    string get_data_at_index(int index){//returns specific data based on index
        return data.at(index);
    }
};
string remove_white_space_end(string str){
    string new_str="";
    bool found=false;
    for(int i=0;i<str.size();i++){
        if(str[i]!=' '){
            found=true;
        }
        if(found==true){
            new_str+=str[i];
        }   
    }
    found=false;
    string str2="";
    for(int z=new_str.size()-1;z>-1;z--){
        if(new_str[z]!=' '){
            found=true;
        }
        if(found==true){
            str2+=new_str[z];
        }   
    }
    string str3="";
    for(int j=str2.size()-1;j>-1;j--){
        str3+=str2[j];
    }
    return str3;
}
bool compare_objects(Object object1,Object object2,vector< vector <string> > compare,vector <string>header){//compares the two classes data
    int index;
    string category,order,type;
    for(int i=0;i<compare.size();i++){//goes through compare vector
        category=compare[i][0];
        order=compare[i][1];
        type=compare[i][2];
      for(int z=0;z<header.size();z++){//find index 
        if(category.compare(header[z])==0){
           index=z; 
           break;
        }
      }
      if(type.compare("string")==0 || type.compare("string")==-1 || type.compare("string")==1){//see if compare type is string
            string str_data1=object1.get_data_at_index(index);
            string str_data2=object2.get_data_at_index(index);
            int str_compare_num;
        if(str_data1.compare(str_data2)!=0){//make sure the two string are no the same
            if(order.compare("ascend")==0){//see if order is ascend
                str_compare_num=str_data1.compare(str_data2);
                if(str_compare_num<0)return true;
                else if(str_compare_num>0)return false;
            }
            else if(order.compare("descend")==0){//see  if order is descend
                str_compare_num=str_data1.compare(str_data2);
                if(str_compare_num>0)return true;
                else if(str_compare_num<0)return false;
            }
        }
      }
      if(type.compare("int")==0 ||type.compare("int")==1 || type.compare("int")==-1){// see if the compare type is int
            int int_data1=stoi(object1.get_data_at_index(index));
            int int_data2=stoi(object2.get_data_at_index(index));
          if(int_data1!=int_data2){//make sure the two int are not equal
            if(order.compare("ascend")==0){//see if ascend order
                return int_data1<int_data2;
            }
            else if(order.compare("descend")==0){//see if descend order
                return int_data1>int_data2;
            }
          }
      }
      if(type.compare("float")==0 || type.compare("float")==1 || type.compare("float")==-1){//see if the compare type is a float
            float float_data1=stof(object1.get_data_at_index(index));
            float float_data2=stof(object2.get_data_at_index(index));
          if(float_data1!=float_data2){  
            if(order.compare("ascend")==0){//see if order is ascend
                    return float_data1<float_data2;
            }
            else if(order.compare("descend")==0){//see if order is descend
                    return float_data1>float_data2;
            }
          }
      }
    }
    return true;
}
void print_objects(vector <Object> o){//prints the data from object vector
    for(int i=0;i<o.size();i++){
        o.at(i).print_object();
        cout<<endl;
    }
}

void swap(vector<Object> &objects,int i,int j){
    Object temp=objects.at(i);
    objects.at(i)=objects.at(j);
    objects.at(j)=temp;
}
 void quicksort(vector<Object> &objects,int low,int high,vector< vector <string> > compare,vector <string> header){//sorts objects with quicksort algorithm
    if(low>=high){
        return;
    }
    int pivot_index=(low+high)/2;
    Object pivot_object=objects[pivot_index];
    swap(objects,high,pivot_index);
    pivot_index=low;
    pivot_object=objects[high];
    for(int i=low;i<high;i++){
        if(compare_objects(objects[i],pivot_object,compare,header)){
            swap(objects,i,pivot_index);
            pivot_index++;
        }
    }
    swap(objects,pivot_index,high);
    quicksort(objects,low,pivot_index-1,compare,header);
    quicksort(objects,pivot_index+1,high,compare,header);
 }
void bubble(vector<Object> &objects,vector< vector <string> > compare,vector <string> header){
    for(int i=0;i<objects.size()-1;i++){
        for(int j=0;j<objects.size()-i-1;j++){
            if(compare_objects(objects[j+1],objects[j],compare,header)){
                swap(objects,j,j+1);
            }
        }
    }
}
void compare_all_objects(vector <Object> objects,vector< vector <string> > compare,vector <string>header){
    for(int i=0;i<objects.size();i++){
        for(int z=0;z<objects.size();z++){
            if(i!=z){
                objects[i].print_object();
                cout<<" compare ";
                objects[z].print_object();
                cout<<boolalpha<<compare_objects(objects[i],objects[z],compare,header)<<endl;

            }
        }
    }
}

int main(int argc,char*argv[]){//main funtion
    vector<string>header;
    vector<Object>objects;
    vector<string>temp_vec;
    vector< vector <string> >compare;
    ifstream file1,file2;
    string line,item;
    file1.open(argv[1]);
    getline(file1,line);
    stringstream iss(line);
    while(getline(iss,item,',')){//get the header
        item=remove_white_space_end(item);
        header.push_back(item);
    }
    while(getline(file1,line)){//makes objects and push back in objects vector
        stringstream iss(line);
        while(getline(iss,item,',')){
            item=remove_white_space_end(item);
            temp_vec.push_back(item);
        }
        Object new_object=Object(temp_vec);//makes object
        objects.push_back(new_object);
        temp_vec.clear();
    }
    file1.close();
    file2.open(argv[2]);
    while(getline(file2,line)){//gets compare statements
        stringstream iss(line);
        while(getline(iss,item,',')){
            item=remove_white_space_end(item);
            temp_vec.push_back(item);
        }
        compare.push_back(temp_vec);
        temp_vec.clear();
    }
    quicksort(objects,0,objects.size()-1,compare,header);
    ofstream file3;
    file3.open(argv[3]);
    for(int z=0;z<header.size();z++){//prints header file
        if(z==header.size()-1){
            file3<<header[z]<<endl;
        }
        else{
            file3<<header[z]<<",";
        }
    }
    for(int i=0;i<objects.size();i++){//prints objects to file
        objects[i].out_file(file3);
        file3<<endl;
    }
    return 0;
}