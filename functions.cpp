#include "functions.h"

void mcqRules(void){
    cout << "------------------------------------------------------------------------------------------------------------------------";
    cout << "\n";
    cout << "|   Rules are as follows :                                                                                             |\n";
    cout << "|   1. You will be asked MCQs.                                                                                         |\n";
    cout << "|   2. You will be asked 15 questions.                                                                                 |\n";
    cout << "|   3. 2 chances will be given for each Question.                                                                      |\n";
    cout << "|   4. 3 points will be given for each correct answer and 1 marks will be deducted for each incorrect answer.          |\n";
    cout << "|   5. You will be given 5 minutes to complete the quiz                                                                |\n";
    cout << "|   6. Game will be over after 5 incorrect answers                                                                     |\n";
    cout << "|                                                                                                                      |\n";
    cout << "|                                                 All the very best :)                                                 |\n";
    cout << "------------------------------------------------------------------------------------------------------------------------";
    cout << "\n\n";
    cout << "..........Press Enter to get started.........";
    getch();
    cout << "\n\n";
}

void oneWordRules(void){
    cout << "------------------------------------------------------------------------------------------------------------------------";
    cout << "\n";
    cout << "|   Rules are as follows :                                                                                             |\n";
    cout << "|   1. You will be asked One Word Questions.                                                                           |\n";
    cout << "|   2. You will be asked 15 questions.                                                                                 |\n";
    cout << "|   3. 2 chances will be given for each Question.                                                                      |\n";
    cout << "|   4. 3 points will be given for each correct answer and 1 marks will be deducted for each incorrect answer.          |\n";
    cout << "|   5. You will be given 10 minutes to complete the quiz                                                               |\n";
    cout << "|   6. Game will be over after 5 incorrect answers                                                                     |\n";
    cout << "|                                                                                                                      |\n";
    cout << "|                                                 All the very best :)                                                 |\n";
    cout << "------------------------------------------------------------------------------------------------------------------------";
    cout << "\n\n";
    cout << "..........Press Enter to get started.........";
    getch();
    cout << "\n\n";
}

void oneWordQuestions(void){
    int rightOrWrong, chance, incorrectAnswers=0;
    for(int i = 0; ((i<15) && (incorrectAnswers < 5)); i++){
        srand((unsigned int)time(NULL));
        int random_number = rand() % 66;
        while(count(previousRandoms.begin(), previousRandoms.end(), random_number)){
            srand((unsigned int)time(NULL));
            random_number = rand() % 66;
        }
        previousRandoms.push_back(random_number);
        cout << (i+1) << ". What is the national sports of ";
        couns[random_number].displayCountry();
        cout << " ?\n";
        chance = 1;

        while(chance <= 2){
            cout << "Ans :  ";
            fflush(stdin);
            getline(cin, ans);
            if(breaking == true)
                return;
            rightOrWrong = couns[random_number].compareSports(ans);
            if(rightOrWrong == 1){
                cout << "Correct answer.";
                totalPoints += 3;
                break;
            }

            else{
                cout << "Wrong answer.";
                if(chance == 1)
                    cout << "Try again.\n\n";
                else{
                    totalPoints -= 1;
                    cout << "\n\nAnswer :  ";
                    couns[random_number].showAns();
                    incorrectAnswers++;
                }
                chance++;
            }

        }
        cout << "\n\n..........Press Enter.........";
        getch();
        cout << "\n\n";
    }
    cv.notify_one();
}

void mcqQuestions(void){
    int chance, incorrectAnswers = 0;
    string input;
    for(int i = 0; ((i<15) && (incorrectAnswers < 5)); i++){
        if(breaking == true)
            return;
        srand((unsigned int)time(NULL));
        int random_number = rand() % 66;
        while(count(previousRandoms.begin(), previousRandoms.end(), random_number)){
            srand((unsigned int)time(NULL));
            random_number = rand() % 66;
        }
        previousRandoms.push_back(random_number);
        cout << i << ". What is the national sports of ";
        couns[random_number].displayCountry();
        cout << " ?\n";

        chance = 1;
        int options_index, answer_index, random_sport_index, mcq_ans_number;
        char mcq_ans;
        string sport_answer, sport_answer2, random_sport_name;
        sport_answer = couns[random_number].getSport();
        sport_answer2 = sport_answer;
        transform(sport_answer.begin(), sport_answer.end(), sport_answer.begin(), ::tolower);
        srand((unsigned int)time(NULL));
        answer_index = rand() % 4;
        
        // if user chooses to give answer to mcqs
        srand((unsigned int)time(NULL));
        for(options_index = 0; options_index < 4; options_index++){
            cout << "(" << (char(97 + options_index)) << ").  ";
            if(options_index == answer_index)
                cout << sport_answer2 << "\n";

            else{
                do{
                    random_sport_index = rand() % total_sports;
                    random_sport_name = sportsList[random_sport_index];
                    transform(random_sport_name.begin(), random_sport_name.end(), random_sport_name.begin(), ::tolower);
                }while(sport_answer == random_sport_name);
                cout << sportsList[random_sport_index] << "\n";
            }
        }

        while(chance <= 2){
            cout << "Ans :  ";
            cin >> mcq_ans;
            if(breaking == true)
                return;

            mcq_ans_number = int((mcq_ans-1) % 4);         
            if(mcq_ans_number == answer_index){
                cout << "Correct answer";
                totalPoints += 3;
                break;
            }

            else{
                cout << "Wrong answer.";
                if(chance == 1)
                    cout << "Try again.\n\n";
                else{
                    totalPoints -= 1;
                    cout << "\nCorrect Ans : " << sport_answer << "\n";
                    incorrectAnswers++;
                }
                chance++;
            }
        }
        cout << "\n\n..........Press Enter.........";
        getch();
        cout << "\n\n";
    }
    cv.notify_one();
}

void mcqQuestionsMain(void){
    mcqRules();
    thread th(mcqQuestions);
    mutex mtx;
    unique_lock<mutex> lck(mtx);
    breaking = false;
    while(cv.wait_for(lck, chrono::seconds(300)) == cv_status::timeout){
        cout << "\n\nTIME OUT";
        th.detach();
        breaking = true;
        break;
    }

    if(breaking == false)
        th.join();

    cout << "\n\n..........Press Enter.........";
    getch();
}

void oneWordQuestionsMain(void){
    oneWordRules();
    thread th(oneWordQuestions);
    mutex mtx;
    unique_lock<mutex> lck(mtx);
    breaking = false;
    while(cv.wait_for(lck, chrono::seconds(600)) == cv_status::timeout){
        fflush(stdin);
        cout << "\n\nTIME OUT";
        th.detach();
        breaking = true;
        break;
    }

    if(breaking == false)
        th.join();

    cout << "\n\n..........Press Enter.........";
    getch();
}

// getting info of countries and their respective sports from 'country.txt'
void getInfos(ifstream * infile, ifstream * sportsFile){
    int i = 0, index, length, previousIndex, no_of_chars, total_words;
    string sport, coun, word;
    queue<string> q1;
    while(!infile->eof()){
        getline(*infile, coun);
        index = coun.find(':');
        length = coun.length();
        sport = coun.substr(index+2, (length-index)-2);
        coun = coun.substr(0, index-1);

        // converting string into array

        length = sport.length();
        index = sport.find(',');
        previousIndex = 0;
        no_of_chars = index;
        total_words = 1;

        // finding no. of sports from string

        while(index >=0 && index <= length){
            word = sport.substr(previousIndex, no_of_chars);
            q1.push(word);
            previousIndex = index+1;
            index = sport.find(',', previousIndex);
            no_of_chars = index - previousIndex;
            total_words++;
        }
        
        word = sport.substr(previousIndex, no_of_chars);
        q1.push(word);

        couns[i].getInfo(coun, q1, total_words);
        while(!q1.empty())
            q1.pop();
        i++;
    }

    i = 0;
    while(!sportsFile->eof()){
        getline(*sportsFile, sport);
        sportsList[i] = sport;
        i++;
    }
}
// getting info of countries and sports ends here

// opening 'country.txt' and returning total number of countries
void openFiles(ifstream * infile, ifstream * sportsFile, int * total_countries, int * total_sports){
    string coun, sport;
    infile->open("country.txt");
    while(!infile->eof()){
        getline(*infile, coun);
        (*total_countries)++;
    }

    sportsFile->open("sports.txt");
    while(!sportsFile->eof()){
        getline(*sportsFile, sport);
        (*total_sports)++;
    }
}

// displaying welcome message and rules of games from this function
int displayRules(string * username){
    // string username;
    int method;

    cout << "\n\n############################ QUIZ ############################\n";
    cout << "########## Welcome to Quiz on Countries and Sports ###########\n\n";
    cout << "Have a good knowledge of countries and their sports? Test here !!\n\n";
    cout << "..........Press Enter to get started.........";
    getch();
    cout << "\n\n";

    cout << "Enter username : ";
    getline(cin, *username);

    doesUserExists(username);
    if(userExists == false)
        cout << "Welcome " << *username;

    cout << "\n\n------------------------------------------------------------------------------------------------------------------------\n";
    cout << "|   You can play this game by two methods. The methods are :                                                           |\n";
    cout << "|   [1] MCQ's(Yuou will be given 4 options from which you will have to choose one correct option)                      |\n";
    cout << "|   [2] One word answer(You will have to write the sport name)                                                         |\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
    while(1){
        cout << "Your Choice(1/2) : ";
        cin >> method;
        if(method == 1 || method == 2)
            break;
        cout << "Incorrect option\n";
    }
    cout << "\n";
    return method;
}

void doesUserExists(string * username){
    fstream file;
    file.open("QuizUsers.txt",ios::in|ios::out|ios::app);
    string line, name, scoreString;
    int length, semiColonIndex = 0;
    bool found = false;
    while(!file.eof()){
        getline(file, line);
        length = line.length();
        if(length > 2){
            semiColonIndex = line.find(';');
            name = line.substr(0, semiColonIndex);
        }
        else
            continue;
        if((name == *username) && (found == false)){
            found = true;
            userExists = true;
            scoreString = line.substr(semiColonIndex+1, (length-semiColonIndex)-2);
            stringstream convertIntoInt(name);
            convertIntoInt >> previousScores;
            cout << "Welcome Again " << *username;
        }
        else{
            users.push_back(line);
        }
    }
    file.close();
}

void addUsers(string * username, int totalPoints){
    fstream file;
    file.open("QuizUsers.txt", ios::in|ios::out|ios::trunc);
    int i = 0;
    int size = users.size();
    while(i < size){
        file << users[i] << "\n";
        i++;
    }
    file << *username << ";" << totalPoints << ";" << "\n";
}

void showFeedback(int totalPoints){
    if((userExists == true) && (totalPoints > previousScores)){
        cout << "Congratulations! You scored better than before.\n";
    }
    else if(previousScores > 30)
        cout << "You played very very well.\n";
    else if(previousScores > 15)
        cout << "You played very well.\n";
    else
        cout << "You need to improve.\n";

}
