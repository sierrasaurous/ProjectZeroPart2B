//
//  main.cpp
//  ProjectZeroPartTwoB
//
//  Created by Sierra on 8/24/15.
//  Copyright (c) 2015 Sierra Adibi. All rights reserved.
//
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class machine{  // this is like the type, which is why can define the vector machines using this below.
    
public:
    double average; // current defined average
    double range; // current defined range
    vector<double> winnings;
    double total;
    int count;
    double calcAverage; // calculated average from previous winnings and count
    double calcDeviation; // calculated standard deviation from winnings
    vector<double>* pwinnings;
    
    void initialize();
    void printvalues();
    void calcs();
};

void machine::initialize(){
    average = rand()%10;
    range = rand()%10;
    total = 0;
    count = 0;
    calcAverage = 0;
    calcDeviation = 0;
    pwinnings = &winnings;
}

void machine::printvalues(){
    cout << "\t\t\t" << total << "\t\t\t" << calcAverage;
    
    cout << "\t\t\t\t"<< calcDeviation << "\t\t\t\t"  <<count <<endl << endl;
    
    
}

void machine::calcs(){
    total = 0;
    for (int i=0; i<winnings.size(); i++) {
        total = total + winnings.at(i);
    }
    calcAverage = total/winnings.size();
    double calcDeviationIntermediate = 0;
    for (int i=0;i<winnings.size();i++){
        calcDeviationIntermediate = calcDeviationIntermediate + pow(winnings.at(i)-calcAverage, 2);
    }
    calcDeviation = sqrt(calcDeviationIntermediate/winnings.size());
}

class casino{
public:
    int numofmachines;
    vector<machine> stats;
    
    void initialize();
};

void casino::initialize(){
    numofmachines = 3;
    
    for(int i=0; i<numofmachines;i++){
        machine m;
        m.initialize();
        
        stats.push_back(m);
    }
    
}

double pull(double median, double range){
    double r1 = ((double)rand()/RAND_MAX)*range;
    double r2 = ((double)rand()/RAND_MAX)*range;
    double pullValue = median+r1-r2;
    
    return pullValue;
};

void printheader(){
    cout << "\n The results of your first 10 rounds are below: \n";
    
    cout << "Machine Number | Total Winnings | Average Pull Value | Standard Deviation | Number of Pulls  \n";
    cout << "----------------------------------------------------------------------------------------------------\n";
};


int main(){
    
    
    srand(time(NULL));
    
    vector<casino> southlake;
    int numofcasinos = 3;
    int epsilon = 10;
    int greedy = 90;
    
    for (int i=0;i<numofcasinos; i++){
        
        casino c;
        c.initialize();
        southlake.push_back(c);
        
    }
    

    
    cout << "Welcome to the Multi-Armed Bandit Game!  Today we are playing with " << numofcasinos << " casinos." << endl;
    cout << "We will start by playing 10 rounds on each " << endl << endl;
    
    for(int p=0; p<10;p++){
    for (int i=0; i<numofcasinos; i++){
        
        for (int j=0; j<southlake.at(i).stats.size();j++){
            
            double win = pull(southlake.at(i).stats.at(j).average, southlake.at(i).stats.at(j).range);
            
            southlake.at(i).stats.at(j).winnings.push_back(win);
            southlake.at(i).stats.at(j).count++;
        }
    }
    }


    
    for (int i=0; i<numofcasinos; i++){
        
        cout << "Casino Number " << i << ":" << endl;
            printheader();
        
        for (int j=0; j<southlake.at(i).stats.size();j++){
            
            southlake.at(i).stats.at(j).calcs();
            
            cout << "\t\t" << j;
            
            southlake.at(i).stats.at(j).printvalues();
        }
    }
    
    for( int r=0; r<20; r++){
        
        int state = rand()%3;
        
        for( int i=0; i<southlake.at(state).stats.size();i++)
            for (int j = i+1;j<southlake.at(state).stats.size();j++){
                if(southlake.at(state).stats.at(i).average>=southlake.at(state).stats.at(j).average){
                    double win = pull(southlake.at(state).stats.at(i).average, southlake.at(state).stats.at(i).range);
                    southlake.at(state).stats.at(i).winnings.push_back(win);
                    southlake.at(state).stats.at(i).count++;
                }else{
                    double win = pull(southlake.at(state).stats.at(j).average, southlake.at(state).stats.at(j).range);
                    southlake.at(state).stats.at(j).winnings.push_back(win);
                    southlake.at(state).stats.at(j).count++;
                }
            }
    }
    for (int i=0; i<numofcasinos; i++){
        
        cout << "Casino Number " << i << ":" << endl;
        printheader();
        
        for (int j=0; j<southlake.at(i).stats.size();j++){
            
            southlake.at(i).stats.at(j).calcs();
            
            cout << "\t\t" << j;
            
            southlake.at(i).stats.at(j).printvalues();
        }
    }
    
    return 0;
}