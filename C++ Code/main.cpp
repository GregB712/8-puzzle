#include <iostream>
#include "State.h"
//#include <chrono>

using namespace std;
//using namespace std::chrono;
/*Breadth First Search Algorithm*/
template <typename myState>
bool BFS(const myState &goal,queue<myState> &agenda, set<myState> &closed,myState &solution){
    myState s;
    while(!(s==goal)){
        if (agenda.empty())
            return false;
        s=agenda.front();
        agenda.pop();
        if (s==goal){
            solution = s;
            return true;
        }
        if (closed.empty() || (closed.find(s)==closed.end())){
            vector<myState> children;
            children=s.expand();
            closed.insert(s);
            for (unsigned int i=0;i<children.size();i++)
                agenda.push(children.at(i));
        }
    }
    return true;
}

/*Depth First Search Algorithm*/
template <typename myState>
bool DFS(const myState &goal,stack<myState> &agenda, set<myState> &closed,myState &solution){
    myState s;
    if (agenda.empty()){
        return false;
    }
    s=agenda.top();
    agenda.pop();
    if (s==goal){
        solution = s;
        return true;
    }
    if (closed.empty() || (closed.find(s)==closed.end())){
        vector<myState> children;
        children=s.expand();
        closed.insert(s);
        for (unsigned int i=0;i<children.size();i++){
            agenda.push(children.at(i));
        }
    }
    return DFS(goal,agenda,closed,solution);
}

/*Structure that, with the operator <, helps in the right emplacement of states in the priority queue,
 * arranged by the ranking they got from the heuristic function.
 * */
struct evaluate{
    State state;
    int rating;
    evaluate(State n_state, int n_rating){
        state = std::move(n_state);
        rating = n_rating;
    }
};

bool operator < (const evaluate& a, const evaluate& b){
    return a.rating > b.rating;
}

/*Best First Search Algorithm*/
template <typename myState>
bool BestFS(const myState &goal,priority_queue<evaluate> &agenda, set<myState> &closed,myState &solution){
    myState s;
    while(!(s==goal)){
        unsigned int i=0;
        if (agenda.empty()){
            return false;
        }
        s=agenda.top().state;
        agenda.pop();
        if (s==goal){
            solution = s;
            return true;
        }
        if (closed.empty() || (closed.find(s)==closed.end())){
            vector<myState> children;
            children=s.expand();
            closed.insert(s);

            for (i=0;i<children.size();i++){
                int priority = children.at(i).getRating();
                evaluate eval(children.at(i), priority);
                agenda.push(eval);
            }
        }
    }
    return true;
}


int main(){
    int init[9]={6,7,1,
                 0,3,2,
                 8,5,4};

    int go[9]={1,2,3,
               4,5,6,
               7,8,0};

    /*The initial state and the goal*/
    State initial(init);
    State goal(go);

    /*The algoriths' agendas and sets*/
    stack <State> DFS_agenda;
    queue <State> BFS_agenda;
    priority_queue<evaluate> BestFS_agenda;
    int init_priority = initial.getRating();
    evaluate in(initial, init_priority);

    DFS_agenda.push(init);
    BFS_agenda.push(init);
    BestFS_agenda.push(in);

    set <State> DFS_closed;
    set <State> BFS_closed;
    set<State> BestFS_closed;

    State DFS_solution;
    State BFS_solutionQ;
    State BestFS_solution;

    cout<<initial.toString()<<" -> "<<goal.toString()<<endl;

    cout<<endl;

    cout<<"BestFS Solution: "<<endl;
    //auto start1 = high_resolution_clock::now();
    BestFS(goal,BestFS_agenda,BestFS_closed,BestFS_solution);
    //auto stop1 = high_resolution_clock::now();
    //auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    cout<<BestFS_solution.getPath();
    //cout << "Time taken by BestFS: " << duration1.count() << " milliseconds" << endl;

    cout<<endl;

    cout<<"BFS Solution: "<<endl;
    //auto start2 = high_resolution_clock::now();
    BFS(goal,BFS_agenda,BFS_closed,BFS_solutionQ);
    //auto stop2 = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    cout<<BFS_solutionQ.getPath();
    //cout << "Time taken by BFS: " << duration2.count() << " milliseconds" << endl;

    cout<<endl;

    cout <<"DFS Solution: "<<endl;
    //auto start3 = high_resolution_clock::now();
    DFS(goal,DFS_agenda,DFS_closed,DFS_solution);
    //auto stop3 = high_resolution_clock::now();
    //auto duration3 = duration_cast<milliseconds>(stop3 - start3);
    cout<<DFS_solution.getPath();
    //cout << "Time taken by DFS: " << duration3.count() << " milliseconds" << endl;

    return 0;
}
