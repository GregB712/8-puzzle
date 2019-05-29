#include "State.h"
#include <iostream>

State::State(){}
/*The constructor sends the values of the my_Array to array and locates the 0(blank).*/
State::State(const int my_Array[]) {
    for(int i = 0; i<array_size; i++){
        array[i] = my_Array[i];
        if(array[i] == 0){
            hereIAm = i;
        }
    }
}

bool State::operator==(const State& s) const
{
    int i;
    for(i = 0; i<array_size; i++){
        if((array[i]) != s.array[i]){
            return false;
        }
    }
    return true;
}

/*Number of misplaced tiles*/
/*bool State::rate() {
    rating=0;
    for(int i=0;i<array_size-1;i++){
        if(array[i]==i+1)
            rating++;
    }
    return true;
}*/

/*Manhattan heuristic function*/
bool State::rate() {
    rating=0;
    /*Convert the 1D array to a 2D array.*/
    int array_2d[3][3];
    int idx = 0;
    for(int i=0; i<3; i++) {
        for (int j = 0; j < 3 && idx < 9; j++)
            array_2d[i][j] = array[idx++];
    }

    /*Use of manhattan distance to rate the state.*/
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            int value = array_2d[x][y];
            int targetX = (int)(value-1) / 3; //Target X coordinate.
            int targetY = (value-1) % 3; //Target Y coordinate.
            int distX = abs(x - targetX);
            int distY = abs(y - targetY);
            rating = rating + distX + distY;
        }
    }
    return true;
}

int State::getRating(){
    rate();
    return rating;
}

string State::toString () const
{
    stringstream ot;
    for(int i=0; i<array_size; i++){
        ot<<array[i]<<" ";
    }
    return ot.str();
}

bool operator< (const State& a, const State& o)
{
    return (a.toString() < o.toString());
}

/*Depending on which transition factor we apply we change the positions of the values (0-any_number).*/
void State::swap(int a){
    switch (a){
        case 1:
            array[hereIAm] = array[hereIAm-3];
            array[hereIAm-3] = 0;
            hereIAm = hereIAm-3;
            break;
        case 2:
            array[hereIAm] = array[hereIAm+3];
            array[hereIAm+3] = 0;
            hereIAm = hereIAm+3;
            break;
        case 3:
            array[hereIAm] = array[hereIAm-1];
            array[hereIAm-1] = 0;
            hereIAm = hereIAm-1;
            break;
        case 4:
            array[hereIAm] = array[hereIAm+1];
            array[hereIAm+1] = 0;
            hereIAm = hereIAm+1;
            break;
    }

}

bool State::up(State &n) {
    if (hereIAm != 0 &&  hereIAm != 1 && hereIAm != 2){
        n=*this;
        n.swap(1);
        n.path.push_back("Up");
        return true;
    }
    return false;
}

bool State::down(State &n) {
    if (hereIAm != 6 &&  hereIAm != 7 && hereIAm != 8){
        n=*this;
        n.swap(2);
        n.path.push_back("Down");
        return true;
    }
    return false;
}

bool State::left(State &n) {
    if (hereIAm != 0 &&  hereIAm != 3 && hereIAm != 6){
        n=*this;
        n.swap(3);
        n.path.push_back("Left");
        return true;
    }
    return false;
}

bool State::right(State &n) {
    if (hereIAm != 2 &&  hereIAm != 5 && hereIAm != 8){
        n=*this;
        n.swap(4);
        n.path.push_back("Right");
        return true;
    }
    return false;
}

string State::getPath()
{
    unsigned i;
    string s;
    if (!path.empty()){
        for (i=0;i<path.size()-1;i++)
            s+=path.at(i)+", ";
        s+=path.at(i)+ "\n";
    }
    return s;
}

/*Checking if any of the transition factors can be applied, and if it is possible
 * then saves these new states and return them.
 * */
vector <State> State::expand(){
    vector <State> children;
    State child;

    if (up(child))
        children.push_back(child);
    if (down(child))
        children.push_back(child);
    if (left(child))
        children.push_back(child);
    if (right(child))
        children.push_back(child);

    return children;
}
