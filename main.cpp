#include <QCoreApplication>
#include <iostream>
#include <vector>
using namespace std;
vector<pair<int , int> > opened_nodes;
vector<pair<int , int> > visited;
pair<int,int> cur_node;
int my_x;
int my_y;
int goal_x = 5;
int goal_y = 0;
char my_world[5][6] = {
    {' ',' ','#',' ',' ','*'},
    {' ',' ',' ',' ','#','#'},
    {' ','#',' ',' ',' ',' '},
    {' ',' ','#','#','#',' '},
    {' ',' ',' ',' ',' ',' '}
};
void init_pos();
void add_nodes();
bool is_in_list(pair<int,int> node);
void greedy();
void brute_force();
void show_path(vector<pair<int , int> > p);
vector <pair<int , int> > sort_vec(vector <pair<int , int> >my_list);
int main()
{
    init_pos();
    //greedy();
    brute_force();
    return 0;
}
vector <pair<int , int> > sort_vec(vector <pair<int , int> >my_list){
    for(int i = 0 ; i < my_list.size() ; i++){
        for(int j = 0 ; j < my_list.size() - 1 ; j++){
            int first_dist = abs(my_list.at(j).first - goal_x) + abs(my_list.at(j).second - goal_y);
            int second_dist = abs(my_list.at(j+1).first - goal_x) + abs(my_list.at(j+1).second - goal_y);
            if(second_dist < first_dist){
                pair<int,int> tmp = my_list.at(j);
                my_list.at(j) = my_list.at(j+1);
                my_list.at(j+1) = tmp;
            }
        }
    }
    return my_list;
}

void init_pos(){
    my_x = 1;
    my_y = 4;
}
void greedy(){
    cur_node.first = my_x;
    cur_node.second = my_y;
    opened_nodes.push_back(cur_node);
    while(opened_nodes.size() != 0){
        visited.push_back(cur_node);
        add_nodes();
        cout << cur_node.first << ","<<cur_node.second<<endl;
        if(my_world[cur_node.second][cur_node.first] == '*'){
            cout << "found !"<<endl;
            break;
        }
        opened_nodes = sort_vec(opened_nodes);
        cur_node = opened_nodes.at(0);
        opened_nodes.erase(opened_nodes.begin());
        int a;
        cin >> a;
        //opened_nodes.pop_back();
        //cur_node = opened_nodes.back();
    }

}
void add_nodes(){
    if(cur_node.first - 1 >= 0){
        pair<int,int> tmp;
        tmp = cur_node;
        tmp.first -= 1;
        if(!is_in_list(tmp)){
            opened_nodes.push_back(tmp);
        }
    }
    if(cur_node.first + 1 < 6){
        pair<int,int> tmp;
        tmp = cur_node;
        tmp.first += 1;
        if(!is_in_list(tmp)){
            opened_nodes.push_back(tmp);
        }
    }
    if(cur_node.second - 1 >= 0){
        pair<int,int> tmp;
        tmp = cur_node;
        tmp.second -= 1;
        if(!is_in_list(tmp)){
            opened_nodes.push_back(tmp);
        }
    }
    if(cur_node.second + 1 < 5){
        pair<int,int> tmp;
        tmp = cur_node;
        tmp.second += 1;
        if(!is_in_list(tmp)){
            opened_nodes.push_back(tmp);
        }
    }
}
bool is_in_list(pair<int,int> node){

    if(my_world[node.second][node.first] == '#'){
        return true;
    }
    for(int i = 0 ; i < visited.size() ; i++){
        if(visited.at(i).first == node.first && visited.at(i).second == node.second){
            return true;
        }
    }
    return false;
}
void brute_force(){
    vector<vector<pair<int , int> > > all_paths;
    vector<pair<int , int> > path;
    vector<vector<pair<int,int> > > correct_paths;
    cur_node.first = my_x;
    cur_node.second = my_y;
    path.push_back(cur_node);
    all_paths.push_back(path);
    while(all_paths.size() != 0){
        path = all_paths.at(0);
        //show_path(path);
        all_paths.erase(all_paths.begin());
        pair<int,int> end_point = path.at(path.size() - 1);
        if(end_point.first==goal_x && end_point.second==goal_y){
            correct_paths.push_back(path);
            continue;
        }
        if(end_point.first - 1 >= 0){
            pair<int,int> tmp;
            tmp = end_point;
            tmp.first -= 1;
            if(my_world[tmp.second][tmp.first] != '#'){
                bool is_in_path = false;
                for(int i = 0 ; i < path.size() ; i++){
                    if(path.at(i).first == tmp.first && path.at(i).second == tmp.second){
                        is_in_path = true;
                    }
                }
                if(!is_in_path){
                    vector<pair<int, int > > tmp_path = path;
                    tmp_path.push_back(tmp);
                    all_paths.push_back(tmp_path);
                }
            }
        }
        if(end_point.first + 1 < 6){
            pair<int,int> tmp;
            tmp = end_point;
            tmp.first += 1;
            if(my_world[tmp.second][tmp.first] != '#'){
                bool is_in_path = false;
                for(int i = 0 ; i < path.size() ; i++){
                    if(path.at(i).first == tmp.first && path.at(i).second == tmp.second){
                        is_in_path = true;
                    }
                }
                if(!is_in_path){
                    vector<pair<int, int > > tmp_path = path;
                    tmp_path.push_back(tmp);
                    all_paths.push_back(tmp_path);
                }
            }
        }
        if(end_point.second - 1 >= 0){
            pair<int,int> tmp;
            tmp = end_point;
            tmp.second -= 1;
            if(my_world[tmp.second][tmp.first] != '#'){
                bool is_in_path = false;
                for(int i = 0 ; i < path.size() ; i++){
                    if(path.at(i).first == tmp.first && path.at(i).second == tmp.second){
                        is_in_path = true;
                    }
                }
                if(!is_in_path){
                    vector<pair<int, int > > tmp_path = path;
                    tmp_path.push_back(tmp);
                    all_paths.push_back(tmp_path);
                }
            }
        }
        if(end_point.second + 1 < 5){
            pair<int,int> tmp;
            tmp = end_point;
            tmp.second += 1;
            if(my_world[tmp.second][tmp.first] != '#'){
                bool is_in_path = false;
                for(int i = 0 ; i < path.size() ; i++){
                    if(path.at(i).first == tmp.first && path.at(i).second == tmp.second){
                        is_in_path = true;
                    }
                }
                if(!is_in_path){
                    vector<pair<int, int > > tmp_path = path;
                    tmp_path.push_back(tmp);
                    all_paths.push_back(tmp_path);
                }
            }
        }

    }
    cout << "size : " << correct_paths.size() << endl;
    cout << "-------------------------------"<<endl;
    vector<pair<int , int > > best_path;
    int min_size = 999;
    for(int i = 0 ; i < correct_paths.size() ; i++){
        show_path(correct_paths.at(i));
        cout << "-------------"<<endl;
        if(correct_paths.at(i).size() < min_size){
            min_size = correct_paths.at(i).size();
            best_path = correct_paths.at(i);
        }
    }
    cout << "best path is :"<<endl;
    show_path(best_path);

}
void show_path(vector<pair<int , int> > p){
    for(int i = 0 ; i < p.size() ; i++){
        cout << p.at(i).first << " , "<<p.at(i).second<<endl;
    }
}






















