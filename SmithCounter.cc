//SmithCounter.cpp
//Y00794471 - Rabin Thapa

#include "SmithCounter.h"

using namespace std;

//constructor with default state value 0
SmithCounter::SmithCounter(): state(0) {

}

// return current state
int SmithCounter::getState() {
    return state;
}

//change state when brach is taken
void SmithCounter::branchTakenUpdate() {
    state++;
    if(state > 3)
        state = 3;
}

//change state when branch is not taken
void SmithCounter::branchNotTakenUpdate() {
    state--;
    if(state < 0)
        state = 0;
}

//calls branchTakenUpdate() or branchNotTakenUpdate()
void SmithCounter::updateState(char outcome) {
    if(outcome == 'T')
        branchTakenUpdate();
    else if(outcome == 'N') {
        branchNotTakenUpdate();
    }
}

//return prediction (T/F) depending on current state
char SmithCounter::getPrediction() {
    if(state <= 1) 
        return 'N';
    else 
        return 'T';
}
