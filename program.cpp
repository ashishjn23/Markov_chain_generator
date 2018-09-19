#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class markov{
public:
    void create(string file){
        ifstream fpt(file.c_str(), ios_base::in);
        buff = string( istreambuf_iterator<char>( fpt ), istreambuf_iterator<char>());
        fpt.close();
        if(buff.length() < 1){
            return;
        }
        create_dict();
        create_markov_text();
        
    }
    
private:
    void create_markov_text(){
        int len = 265;
        string key, output, temp1, temp;
        vector<string>::iterator it;
        it = firsts.begin();
        advance(it, rand() % firsts.size());
        key = *it;
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
            
            if (len < output.length()){
                break;
            }
            key = key.substr(key.find_first_of(" ", 0) + 1) + " " + temp;
        }
            //cout << output << endl;
            cout << output << endl;
            cout << output.length() << endl;
    }
    
    void create_dict(){
        size_t next1, next2, x, z, y, c = 0;
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
        firsts.push_back(key);
        while(true){
            next1 = buff.find_first_not_of(" ", next2 + 1);
            if(next1 == -1) break;
            next2 = buff.find_first_of(" ", next1);
            temp = buff.substr(next1, next2 - next1);
            if(temp.length() < 1) break;
            
            x = temp.find(".");
            if (x > 0){
                if (x == (temp.length() - 1)){
                    y = buff.find_first_of(" ", next2 + 1);
                    z = buff.find_first_of(" ", y + 1);
                    if (buff.substr((next2 + 1), (z - next2 + 1)).length() > 1 ){
                        firsts.push_back(buff.substr((next2 + 1), (z - next2 - 1)));
                    }
                }
            }
            dict[key].push_back(temp);
            key = key.substr(key.find_first_of(" ", 0) + 1) + " " + temp;
        }
        //print(dict);
        //print_vector(firsts);
    }
    void print_map(map<std::string, vector<string>> dict){
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
    
    void print_vector(vector<string> v){
        vector<string>::iterator itr;
        for (itr = v.begin(); itr != v.end() ; itr++){
            cout << *itr << "*" << endl;
        }

    }
    
    
    string buff;
    map<string, vector<string>> dict;
    vector<string> firsts;
};


int main(){
    srand( unsigned( time( 0 ) ) );
    markov mark;
    mark.create("input.txt");
}