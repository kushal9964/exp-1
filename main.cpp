#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cctype>
using namespace std;

class Database{
    private:
        unordered_map< string, string > map;
        string filename = "database.txt";
    
    public:

        Database(){
            LOAD();
        }

        void PUT(const string& key, const string& value){
            map[key] = value;
        }

        string GET(const string& key){
            auto it = map.find(key);

            if (it != map.end())
                return it->second;
            return "NIL";
        }

        void DEL(const string& key){
                map.erase(key);
        }

        void CLEAR(){
            map.clear();
        }

        bool EXISTS(const string& key){
            return map.find(key) != map.end();
        }

        void LOAD(){

            map.clear();

            ifstream inFile(filename);
            if(inFile.is_open()){
                string line;
                while(getline(inFile,line)){
                    size_t pos = line.find(' ');
                    if(pos != string::npos){
                        string key = line.substr(0,pos);
                        string value = line.substr(pos+1);
                        PUT(key,value);
                    }
                }
            }
            inFile.close();
        }

        void SAVE(){
            ofstream outFile(filename);

            for(auto it = map.begin();it!=map.end();++it){
                outFile << it->first << " " << it->second << "\n";
            }
            outFile.close();
        }
        
        void SHOW(){
            for(auto pairs:map){
                cout<<pairs.first<<"-->"<<pairs.second<<"\n";
            }

        }
};


int main(){

    Database db;

    while(true){
 
        string cmd;
        vector<string> tokens;
        string row;
        
        cout<<">>";
        getline(cin,cmd);

        for(int i=0;i<cmd.size();i++){
            if(cmd[i]==' '){
                if(!row.empty()){
                    tokens.push_back(row);
                    row.clear();
                }
            }
            else{
                row += toupper(cmd[i]);
            }
        }

        if(!row.empty()){
            tokens.push_back(row);
        }

        if(tokens.empty()){
            continue;
        }

        if(tokens[0] == "PUT"){
            if(tokens.size()!=3){
                continue;
            }
            db.PUT(tokens[1],tokens[2]);
        }

        else if(tokens[0] == "GET"){
            if(tokens.size()!=2){
                continue;
            }
            cout << db.GET(tokens[1]) << endl;
        }

        else if(tokens[0] == "DEL"){
            if(tokens.size()!=2){
                continue;
            }
            db.DEL(tokens[1]);
        }

        else if(tokens[0] == "CLEAR"){
            if(tokens.size()!=1){
                continue;
            }
            db.CLEAR();
        }
        
        else if(tokens[0] == "EXISTS"){
            if(tokens.size()!=2){
                continue;
            }
            cout << (db.EXISTS(tokens[1]) ? "true" : "false") << endl;
        }

        else if(tokens[0] == "SHOW"){
            db.SHOW();
        }

        else if(tokens[0] == "SAVE"){
            db.SAVE();
        }

        else if(tokens[0] == "EXIT"){
            db.SAVE();
            break;
        }
    }
    return 0;
}