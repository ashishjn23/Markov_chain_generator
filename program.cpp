#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class markov{
public:
    void create(string file, int len){
        ifstream fpt(file.c_str(), ios_base::in);
        buff = string( istreambuf_iterator<char>( fpt ), istreambuf_iterator<char>());
        fpt.close();
        if(buff.length() < 1){
            return;
        }
        create_dict();
        create_markov_text(len - 2);
        
    }
    
private:
    void create_markov_text(int len){
        int c = len;
        string key, output, temp1, temp;
        map<string, vector<string> >::iterator it;
        it = dict.begin();
        advance(it, rand() % dict.size());
        key = it->first;
        output = key + " ";
        while(true){
            vector<string> vic = dict[key];
            if (vic.size() < 1){
                break;
            }
            temp = vic[rand() % vic.size()];
            if (temp.size() < 1){
                break;
            }
        //print(dict);
            output += temp + " ";
            if (c < 1){
                break;
            }
            key = key.substr(key.find_first_of(" ", 0) + 1) + " " + temp;
            c--;
        }
            //cout << output << endl;
            cout << output << endl;
    }
    
    void create_dict(){
        size_t next1, next2, c = 0;
        string key, temp;
        
        
        next1 = buff.find_first_not_of(" ", 0);
        if(next1 == -1) return;
        while(c < 2){
            next2 = buff.find_first_of(" ", next1);
            temp = buff.substr(next1,next2 - next1);
            key = key + temp + " ";
            next1 = buff.find_first_not_of(" ", next2 + 1);
            if(next1 == -1) return;
            c++;
        }
        key = key.substr(0, key.length()-1);
        while(true){
            next1 = buff.find_first_not_of(" ", next2 + 1);
            if(next1 == -1) break;
            next2 = buff.find_first_of(" ", next1);
            temp = buff.substr(next1, next2 - next1);
            if(temp.length() < 1) break;
            dict[key].push_back(temp);
            key = key.substr(key.find_first_of(" ", 0) + 1) + " " + temp;
        }
        //print(dict);
    }
    void print(map<string, vector<string>> dict){
        map<string, vector<string> >::iterator it;
        vector<string>::iterator itr;
        for (it = dict.begin(); it!= dict.end(); it++){
            cout << "Key: " << it->first << " ";
            for (itr = (it->second).begin(); itr != (it->second).end() ; itr++){
                cout << *itr << "*";
            }
            cout << endl;
        }
    }
    string buff;
    map<string, vector<string>> dict;
};


int main(){
    srand( unsigned( time( 0 ) ) );
    markov mark;
    mark.create("input.txt",300);
}