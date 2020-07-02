#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <stdio.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

class countries{
    string country;
    vector<string> sports;
    int total_sports;
    public:
    void getInfo(string coun, queue<string> q, int totalSps){
        country = coun;
        total_sports = totalSps;
        for(int i=0; i<totalSps; i++){
            sports.push_back(q.front());
            q.pop();
        }
    }
    void display(){
        cout << country << " ";
        vector<string>::iterator starting = sports.begin();
        vector<string>::iterator end = sports.end();
        for(starting; starting != end; starting++){
            cout << *starting << "\n";
        }
    }
    void showAns(){
        vector<string>::iterator starting = sports.begin();
        vector<string>::iterator index = sports.begin();
        vector<string>::iterator end = sports.end();

        while(index != end){
            if(index != starting){
                cout << " , ";
            }
            cout << *index;
            index++;
        }

    }

    void displayCountry(){
        cout << country;
    }

    string getSport(){
        srand((unsigned int)time(NULL));
        int random = (rand() % total_sports);
        return sports[random];
    }

    bool compareSports(string sport){
        transform(sport.begin(), sport.end(), sport.begin(), ::tolower);
        vector<string>::iterator starting = sports.begin();
        vector<string>::iterator end = sports.end();
        for(starting; starting != end; starting++){
            transform((*starting).begin(), (*starting).end(), (*starting).begin(), ::tolower);
            if(*starting == sport)
                return true;
            
        }
    }

};
// global variables
countries * couns;
string * sportsList;
vector<int> previousRandoms;
vector<string> users;
int total_sports=0, total_countries=0, previousScores, totalPoints=0;
bool userExists = false, breaking = false;
string ans;
char mcq_ans;
condition_variable cv;

#include "functions.cpp"

int main(){
    // displaying rules and getting username
    int method;
    string username;
    method = displayRules(&username);
    // displaying rules and username ends here

    ifstream infile, sportsFile;

    // getting informations about countries and sports from country.txt and sports.txt
    openFiles(&infile, &sportsFile, &total_countries, &total_sports);
    couns = new countries[total_countries];
    sportsList = new string[total_sports];
    infile.seekg(0, ios::beg);
    sportsFile.seekg(0, ios::beg);
    getInfos(&infile, &sportsFile);
    infile.close();
    sportsFile.close();
    // getting file infos ends here

    if(method == 1)
        mcqQuestionsMain();
    else
        oneWordQuestionsMain();

    cout << "-------------------------------------------------Game Over-----------------------------------------------\n\n";

    cout << "Your Score : " << totalPoints << "\n";
    addUsers(&username, totalPoints);
    showFeedback(totalPoints);

    return 0;
}

