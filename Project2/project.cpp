/**
 * @file project.cpp
 * @author Rajaditya Shrikishan Bajaj
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
using std::stringstream;
using std::cout;
using std::string;
using std::cin;
using std::set;
using std::map;
using std::pair;
using std::endl;
using std::vector;
using std::istringstream;
using std::for_each;
using std::sort;

/**
 * Class is used to store the name of the product, its quantity available and its cost.
 * **/
struct ItemList{
    string product;
    string quantity;
    string cost;
};

vector<string> CommaSplit(const string &s) {
    //Splits a string with comma.//
    vector<string> elems;
    char sep = ',';
    istringstream iss(s);
    string item;
    while(getline(iss, item, sep)){
        elems.push_back(item);
    }
    return elems;
}

vector<string> ProductVector (const string & s){
    //Converts a string to a vector where name of the product, its quantity, and the cost can be stores.//
    vector<string> product_vector;
    vector<string> split_vector = CommaSplit(s);
    for (int i = 0; i < static_cast<int>(split_vector.size());++i){
        string c = split_vector[i];
        string g;
        if (i != 2){
            product_vector.push_back(c);
        }
        else {
            for (int j = 1; j < static_cast<int>(c.size());++j){
                g += c[j];
            }
            product_vector.push_back(g);
        }
        c = "";
    }
    return product_vector;
}



vector<ItemList> ItemAddVector (const string & input_str){
    //Makes a new vector that is of the class ItemList.//
    vector<ItemList> out_vec;
    vector<string> input_vec = ProductVector(input_str);
    ItemList item;
    item.product  = input_vec[0];
    item.quantity = input_vec[1];
    item.cost = input_vec[2];
    out_vec.push_back(item);
    return out_vec;
}

/**
 * This function is used to take the input and store it in a isstream form that is later converted to string to help with data later on.
 * **/
string InputFunction(){
    string s;
    stringstream input_string;
    int if_store_line = 0, num_of_stores = 0, newline_num = 0;
    int to_break = 1;

    while (getline(cin, s)) {
        if(if_store_line==0){
            num_of_stores=stoi(s);
            to_break += num_of_stores;
            if_store_line += 1;
        }
        input_string << s << '\n';
        if(s==""){
            newline_num += 1;
            if(newline_num == to_break){
                break;
            }
        }
        s="";
    }
    return input_string.str();
}

map<string,vector<ItemList>> StoreInformation(const string & input_string){
    //Stores the information of the store with store name and location as its key and the vector of ItemList as its value.
    stringstream input_stream(input_string);
    int if_store_line = 0, num_of_stores = 0,newline_num = 0;
    stringstream store;
    string store_inf;
    map<string,vector<ItemList>> all_store_inf;

    for(string line;getline(input_stream,line);){
        if(if_store_line == 0){
            num_of_stores=stoi(line);
            if_store_line += 1;
            continue;
        }
        if(newline_num != num_of_stores){
            if(line != ""){
                store_inf += line+'\n';
            }
            else{
                stringstream loop(store_inf);
                ItemList item;
                vector<ItemList> inv_inf;

                string store_name,store_addr,store_loc_name;
                getline(loop,store_name);  //get the name of the store.

                getline(loop,store_addr);  //get the address of the store.
                store_loc_name = store_name + ',' + store_addr;

                for(string line1;getline(loop,line1);){ //from this loop, we can take the product line and then it can be mutated later.
                    vector<string> v;
                    v.push_back(line1);
                    vector<ItemList> g = ItemAddVector(v[0]);
                    inv_inf.push_back(g[0]);
                }
                all_store_inf.insert(pair<string,vector<ItemList>>(store_loc_name,inv_inf));
                store_inf = "";
                newline_num += 1;
            }
        }
    }
    return all_store_inf;
}

vector<string> PrintingPurpose(const string & input_string){
    //This function helps in printing purpose.
    stringstream input_stream(input_string);
    int if_store_line = 0, newline_num = 0;
    int num_of_stores;
    stringstream store;
    string store_inf;
    vector<string> print;
    for(string line;getline(input_stream,line);){
        if(if_store_line == 0){
            num_of_stores = stoi(line);
            if_store_line += 1;
            continue;
        }
        if(newline_num != num_of_stores){
            if(line != ""){
                store_inf += line+'\n';
            }
            else{
                stringstream loop(store_inf);
                string store_name, store_addr;
                getline(loop,store_name);
                getline(loop,store_addr);
                int counting = 0;
                for(string line1;getline(loop,line1);){
                    counting += 1;
                }
                stringstream print_inf;
                print_inf << counting;
                store_name = print_inf.str() + store_name;
                print.push_back(store_name);
                store_inf = "";
                newline_num += 1;
            }
        }
    }
    return print;
}

vector<string> VectorList(const string & s){
    //this vector Converts a string to a vector of strings with each word as different objects.
    stringstream iss(s);
    string word;
    vector<string> v;
    while (iss >> word){
        v.push_back(word);
    }
    if (v.size() > 2){
        string a = v[1] + " " + v[2];
        string b = v[0];
        vector<string> vec;
        vec.push_back(b);
        vec.push_back(a);
        return vec;
    }
    else{
        return v;
    }
}

vector<vector<string>> OrderList(const string & input_str){
    // this function creates a 2d vector with the inner vector storing the quantity and the product that is to be ordered.
    int if_store_line = 0, num_of_stores = 0;
    int newline_num = 0, if_shop_heading = 0;
    stringstream iss(input_str);
    vector<vector<string>> order_list;

    for (string line; getline(iss, line);) {
        if (if_store_line == 0) {
            num_of_stores = stoi(line);
            if_store_line += 1;
            continue;
        }
        if(line == ""){
            newline_num += 1;
            if(newline_num == num_of_stores){
                continue;
            }
        }
        if(newline_num == num_of_stores){
            string product_name , num_order;
            if(if_shop_heading == 0){
                if_shop_heading += 1;
                continue;
            }
            vector<string> v1 = VectorList(line);
            order_list.push_back(v1);
        }
        line = "";
    }
    return order_list;
}

/**
 * This function is used to remove the spaces between two words.
 * **/
void RemoveSpaces(string & input_str){
    size_t pos = input_str.find_first_not_of(" \t");
    input_str.erase(0, pos);
    pos = input_str.find_last_not_of(" \t");
    if (std::string::npos != pos)
        input_str.erase(pos+1);
}

void Split(const std::string &input_str, std::vector<std::string> &input_vec, char delim) {
    std::size_t s;
    std::size_t a = 0;
    while ((s=input_str.find_first_not_of(delim, a))!=std::string::npos) {
        a = input_str.find(delim, s);
        input_vec.push_back(input_str.substr(s, a - s));
    }
}

map<string,vector<vector<string>>> StoreListInMap(map<string,vector<ItemList>> store_inf){
    //This function outputs a map that has store name and 2d vector containing the ItemList.
    map<string,vector<vector<string>>> inv_information;
    for (auto itr = store_inf.begin(); itr != store_inf.end(); ++itr){
        vector<string> store_name_loc;
        string num_of_item, item_name, price;
        string store_name=(itr->first);
        Split(store_name,store_name_loc,',');
        RemoveSpaces(store_name_loc[1]);
        string store_loc_name=store_name_loc[0] + ' ' + 'i' + 'n' + ' ' + store_name_loc[1];
        auto inner_itr = (itr -> second);
        for(int i = 0; i <static_cast<int>(inner_itr.size()); ++i){
            vector<string> v;
            vector<vector<string>> two_d_vec;
            num_of_item = inner_itr[i].quantity;
            item_name=inner_itr[i].product;
            price=inner_itr[i].cost;
            v.push_back(num_of_item);
            v.push_back(price);
            v.push_back(store_loc_name);
            if(inv_information.count(item_name)!=1){
                two_d_vec.push_back(v);
                inv_information.insert(pair<string,vector<vector<string>>>(item_name,two_d_vec));
            }else{
                std::map<string, vector<vector<string>>>::iterator it = inv_information.find(item_name);
                auto v1 = it->second;
                v1.push_back(v);
                inv_information[item_name] = v1;
            }
        }
    }
    return inv_information;
}

void SortVector(vector<vector<string>> & input_vec){
    sort(input_vec.begin(), input_vec.end(),[](const vector<string> & a, const std::vector<string>& b) {
        return stod(a[1]) < stod(b[1]); });
}

void ShoppingDisplay(vector<vector<string>> order_list, map<string,vector<vector<string>>> map_list){

    vector<double> total_price;
    cout<<"Shopping:"<<endl;
    for (auto itr = order_list.begin(); itr != order_list.end(); ++itr){
        string item_name = (*itr)[1];
        double price= 0;
        int num_of_items=stoi((*itr)[0]);
        if(num_of_items==0){
            continue;
        }
        cout<<"Trying to order "<<num_of_items<<" "<<item_name<<"(s)."<<endl;
        vector<string> order_vec;
        for(auto inner_itr = map_list.begin();inner_itr!=map_list.end();++inner_itr){
            if(num_of_items==0){
                continue;
            }
            if(inner_itr->first==item_name){
                cout<<(inner_itr->second).size()<<" store(s) sell "<<item_name<<'.'<<endl;
                for(auto i : inner_itr->second){
                    if(num_of_items==0){
                        continue;
                    }
                    int count_ord=0;
                    while(i[0] != "0"){
                        if(num_of_items==0){
                            break;
                        }
                        count_ord += 1;
                        int current_stock = stoi(i[0])-1;
                        stringstream ab;
                        price+=stod(i[1]);
                        ab<<current_stock;
                        i[0]=ab.str();
                        num_of_items -= 1;
                        if(i[0]=="0"||num_of_items==0){
                            stringstream ab;
                            ab<<"Order "<<count_ord<<" from "<<i[2]<<'\n';
                            order_vec.push_back(ab.str());
                        }
                    }
                }
            }
        }
        cout<< std::fixed<<std::setprecision(2)<<"Total price: $"<<price<<endl;
        for_each(order_vec.begin(),order_vec.end(),[](auto v1){cout<<v1;});
        total_price.push_back(price);
        cout<<'\n';
        if(num_of_items==0){
            continue;
        }
    }
    double required_mon=0;
    for_each(total_price.begin(),total_price.end(),[&required_mon](auto v1)mutable{
        required_mon+=v1; });
    cout<<std::fixed<<std::setprecision(2)<<"Be sure to bring $"<<required_mon<<" when you leave for the stores.";
}


map<string,int> StoreStock(map<string,vector<vector<string>>> map_list){
    map<string,int> store_stock;
    for(auto itr=map_list.begin(); itr!= map_list.end(); ++itr){
        string store_name =itr->first;
        int num_of_item = 0;
        for (auto inner_itr = (itr->second).begin(); inner_itr != (itr->second).end(); ++inner_itr){
            vector <string> v;
            num_of_item += stoi((*inner_itr)[0]);
        }
        store_stock.insert(pair<string,int>(store_name,num_of_item));
    }
    return store_stock;
}

void StoreDisplay(map<string,vector<ItemList>> store_map,vector<string> & print){
    cout<<"Store Related Information (ordered by in-file order):"<<endl;
    cout<<"There are "<<store_map.size()<<" store(s)."<<endl;
    for_each(print.begin(),print.end(),[](auto v){
        string store,item;
        const char *quote = "'";
        for(auto i:v){
            if(isalpha(i) || i==' '||i==*quote){
                store += i;
            }else{
                item += i;
            }
        }
        cout<<store<<" has "<<item<<" distinct items."<<endl;
    });
}

void ItemDisplay (map<string,vector<vector<string>>> string_map){
    cout<<endl<<"Item Related Information (ordered alphabetically):"<<endl;
    cout<<"There are "<<string_map.size()<<" distinct item(s) available for purchase."<<endl;
    map<string,int> store_stock = StoreStock(string_map);

    for(auto itr=store_stock.begin();itr!= store_stock.end();++itr){
        cout<<"There are "<<(itr->second)<<" "<<(itr->first)<<"(s)."<<endl;
    }
    cout<<endl;
}

int main() {

    string s = InputFunction();
    vector<string> print = PrintingPurpose(s);
    map<string,vector<ItemList>> store_inf = StoreInformation(s);
    vector<vector<string>> order_list=OrderList(s);
    map<string,vector<vector<string>>> map_list=StoreListInMap(store_inf);

    for(auto itr = map_list.begin();itr!=map_list.end();++itr){
        SortVector(itr->second);
    }
    StoreDisplay(store_inf,print);
    ItemDisplay(map_list);
    ShoppingDisplay(order_list,map_list);
    cout<<endl;
}


 
