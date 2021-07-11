#include <bits/stdc++.h>
class symbolTable{
    public:
        // var_map = {var_ID:{data_type, value},...}
        map< string, pair< string, string> > var_map;
        // func_declmap = {func_ID:[{data_type},...],...}
        map< string, vector<string>> func_declmap;
        // func_retmap = {func_ID:{data_type},...}
        map<string, string> func_retmap;
        symbolTable* parent;
        symbolTable() {
            parent= nullptr;
        }
};