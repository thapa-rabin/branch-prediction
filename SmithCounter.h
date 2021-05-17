//SmithCounter.h
//Y00794471 - Rabin Thapa

#ifndef SMITHCOUNTER_H
#define SMITHCOUNTER_H

class SmithCounter {
    private:
        int state;	// 0, 1, 2, or 3
        
    public:
        SmithCounter();

        //get state 
        int getState();


        //update methods
        void updateState(char ); 
      	void branchTakenUpdate();
        void branchNotTakenUpdate();

        //get prediction
        char getPrediction();
};

#endif
