#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#define array_size 9

using namespace std;

class State{
    int array[array_size]; //Array that has the board.
    int hereIAm; //The position of 0 (blank).
    int rating; //The rating of the state.
    vector <string> path; //Vector of the moves.

public:
    //The constructors.
    State();
    State(const int my_Array[array_size]);

    //Overloading operators that will be useful.
    bool operator==(const State& o) const ;
    friend bool operator< (const State& a, const State& o);

    //Function that returns a string format of the array.
    string toString () const;

    //Getter for path.
    string getPath();

    //Function that rates the state and a getter.
    bool rate();
    int getRating();

    //Transition factors.
    bool up(State &n);
    bool down(State &n);
    bool left(State &n);
    bool right(State &n);

    //Function that swap the value in the array.
    void swap(int a);

    //Function that creates the tree.
    vector <State> expand();
};