#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    fstream quiz_file; //txt file with questions and answers

    /*this block of code will iterate through quiz file and check how many lines (except topic) is in the file
    thanks to that it is possible to set array size for questions and answers and user can create as many question as he wants
    */
    quiz_file.open("questions.txt", ios::in);
    int how_many_questions = -1; //this var will contain the number of all rows in a file -1 (the first one is the topic of the quiz)
    string line;
    while(getline(quiz_file,line))
    {
        how_many_questions++;
    }
    quiz_file.close();
    quiz_file.clear();

    const int que_pos=5, lines_per_question = 6;
    //que pos = there's always 1 question and 4 possible answers, that's always 5 rows
    //lines_per_question = there's always 1 question, 4 possible answers an 1 correct answer, that's why 6
    string quiz_topic, questions[(how_many_questions/lines_per_question)*que_pos], answers[how_many_questions/lines_per_question], user_answer;
    int points=0;

    if (!quiz_file.good()) //ends program if file doesn't exist or return any errors
    {
        exit(0);
    }

    quiz_file.open("questions.txt", ios::in); //open file for reading

    getline(quiz_file,line);//get first line of tile to assign topic
    quiz_topic = line;

    int question_line=0, answer_line=0, nxt_question=0;
    while(getline(quiz_file,line)) //this loop fulfils arrays with proper questions and answer values
    {
        questions[question_line] = line;
        question_line++;
        answer_line++;

        if (answer_line==que_pos) //answer is only 6th row, so it's possible to use que_pos const
        {
            getline(quiz_file,line);
            answers[nxt_question] = line;
            answer_line=0;
            nxt_question++;
        }
    }
    quiz_file.close();

    for(int i=0; i<(sizeof(answers)/sizeof(*answers)); i++)
    {
        for(int j=0+(que_pos*i); j<que_pos+(que_pos*i); j++) //we add que_pos(equal to 5)*i to show questions in correct order
        {
            cout<<questions[j]<<endl;
        }
        cout<<endl<<"Your answer: ";

        cin >> user_answer;
        transform(user_answer.begin(), user_answer.end(), user_answer.begin(), ::tolower); //this function converts user input to lowercase
        //block below just ensures that user gives "a", "b", "c" or "d" answer
        while(true)
        {
            if((user_answer=="a" || user_answer=="b" || user_answer=="c" || user_answer=="d"))
            {
                break;
            }
            else
            {
                cout<<endl<<"Wrong value, please type \"a\", \"b\", \"c\" or \"d\"";
                cout<<endl<<"Your answer: ";
                cin >> user_answer;
                transform(user_answer.begin(), user_answer.end(), user_answer.begin(), ::tolower);
            }
        }

        if(user_answer==answers[i])
        {
            cout<<endl<<"Right answer!"<<endl;
            points++;
            system("cls");
        }
        else
        {
            cout<<endl<<"Wrong answer!"<<endl;
            system("cls");
        }
    }

    cout<<"Thank's for playing! Your score is: "<<points<<endl;
    return 0;
}
