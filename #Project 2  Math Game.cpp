// #Project 2  Math Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
using namespace std;
enum enLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOpType = 5 };
struct stQuestionInfo
{
    short Num1 , Num2 , Result;
    enLevel  QuestionLevel;
    enOpType QuestionOpType;
    string SignopType;

};
struct stFinalResults
{
    short NumberOfQuestions;
    enLevel Level;
    enOpType OpType;
    short RightAnswers;
    short WrongAnswers;
};
short ReadNumberOfQuestions()
{
    short Num;
    cout << "How Many Questions do you want to answer ? ---->";
    cin >> Num;
    return Num;
}
enLevel ReadQuestionLevel()
{
    short Level;
    do
    {
        cout << "Enter Questions Level [1]:Easy , [2]:Mid , [3]:Hard , [4]:Mix ? ---->";
        cin >> Level;
    } while (Level < 1 || Level >4);
    
    return (enLevel)Level;
}
enOpType ReadOpType()
{
    short OpType;
    do
    {
        cout << "Enter Operation Type [1]:Add , [2]:Sub , [3]:Mul , [4]:Div , [5]:Mix ---->";
        cin >> OpType;
    } while (OpType < 1 || OpType >5);
    return (enOpType)OpType;     
}
short RandomNumber(short From, short To)
{
    short RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;
}
enOpType GetMixOpType()
{
    return (enOpType)RandomNumber(1, 4);
}
enLevel GetMixLevel()
{
    return (enLevel)RandomNumber(1, 3);
}

short QuestionsLevel(short Num, enLevel Level)
{
    short Arr[3] = { RandomNumber(1, 10),RandomNumber(10,50) ,RandomNumber(50,100) };
   
    switch (Level)
    {
    case enLevel::MixLevel:
        return Num = Arr[GetMixLevel() - 1];
        break;
    default:
        return Num = Arr[Level - 1];
    }
}

short ResultOpType(short Num1, short Num2, enOpType OpType)
{
    short Arr[4] = { Num1 + Num2 ,Num1 - Num2 ,Num1 * Num2,Num1 / Num2 };    
     return Arr[OpType - 1];
       
}
string signOpType(enOpType OpType )
{
    string Arr[4] = { "+","-","*","/" };    
        return Arr[OpType - 1];
    
   
}
void FillQuestionAsnwer(stQuestionInfo QuestionInfo, short&Count1 ,short&Count2)
{
    short MyAnswer;
    cout << QuestionInfo.Num1 << endl;;
    cout << QuestionInfo.Num2 << "  " << QuestionInfo.SignopType << "\n\n";
    cout << "_________\n";
    cin >> MyAnswer;
    if (MyAnswer == QuestionInfo.Result)
    {
        Count1++;
        cout << "Your Answer Is Right :-)\n\n\n";
        system("color 2F");
    }
    else
    {
        Count2++;
        cout << "Wrong answer :-(\n";
        cout << "the right answer is " << QuestionInfo.Result << "\n\n\n";
        system("color 4F");
        cout << "\a";
    }
       
}
stFinalResults FinalResult(short HowManyQuestions, enLevel QuestionLevel, enOpType OpType, short CountRightAnswer, short CountWrongAnswer)
{
    stFinalResults Result;
    Result.NumberOfQuestions = HowManyQuestions;
    Result.Level = QuestionLevel;
    Result.OpType = OpType;
    Result.RightAnswers = CountRightAnswer;
    Result.WrongAnswers = CountWrongAnswer;
    return Result;
}
void FillFinalResult(stFinalResults Result)
{
    cout<< "_________________________________\n\n";
    if (Result.RightAnswers >= Result.WrongAnswers)
    {
        cout << "\tFinal Result Is Pass\n";
        system("color 2F");
    }
    else
    {
        cout << "\tFinal Result Is Fail\n";
        system("color 4F");
        cout << "\a";
    }
    cout << "_________________________________\n\n";
    cout << "Number Of Question      : " << Result.NumberOfQuestions<< endl;
    cout << "Questions Level         : " << Result.Level<< endl;
    cout << "Operation Type          : " << Result.OpType<< endl;
    cout << "Number Of Right Answers : " << Result.RightAnswers << endl;
    cout << "Number Of Wrong Answers : " << Result.WrongAnswers<< endl;
    cout << "_________________________________\n\n";
}
stFinalResults PlayMathGame(short HowManyQuestions ,enLevel QuestionLevel , enOpType OpType)
{
    enOpType FinalOpType;
    enLevel LevelQues ;
    stQuestionInfo QuestionInfo;
    short Num1 = 0, Num2 = 0;
    short CountRightAnswer = 0, CountWrongAnswer = 0;
    for (int QuestionNum = 1; QuestionNum <= HowManyQuestions; QuestionNum++)
    {
        FinalOpType = GetMixOpType();
        LevelQues = GetMixLevel();
        cout << "\n\nQuesion [" << QuestionNum << "/" << HowManyQuestions << "]\n\n";
        if (QuestionLevel == enLevel::MixLevel)
        {
            QuestionInfo.Num1 = QuestionsLevel(Num1, LevelQues);
            QuestionInfo.Num2 = QuestionsLevel(Num2, LevelQues);
        }
        else
        {
            QuestionInfo.Num1 = QuestionsLevel(Num1, QuestionLevel);
            QuestionInfo.Num2 = QuestionsLevel(Num2, QuestionLevel);
        }
       
        if (OpType == enOpType::MixOpType)
        {
            QuestionInfo.SignopType = signOpType(FinalOpType);
            QuestionInfo.Result = ResultOpType(QuestionInfo.Num1, QuestionInfo.Num2, FinalOpType);
        }
        else
        {
            QuestionInfo.SignopType = signOpType(OpType);
            QuestionInfo.Result = ResultOpType(QuestionInfo.Num1, QuestionInfo.Num2, OpType);
        }
    
        FillQuestionAsnwer(QuestionInfo, CountRightAnswer, CountWrongAnswer);
    }
    return     FinalResult(HowManyQuestions, QuestionLevel, OpType, CountRightAnswer, CountWrongAnswer);
}
void NewScreen()
{
    system("cls");
    system("color 0F");
}
void StartGame()
{
    char PlayAgian = 'y';
    do
    {
        NewScreen();
        stFinalResults FinalResult = PlayMathGame(ReadNumberOfQuestions(), ReadQuestionLevel(), ReadOpType());
        FillFinalResult(FinalResult);

        cout << " Do you want To play agian? Y/N ---->";
        cin >> PlayAgian;

    } while (PlayAgian == 'y' || PlayAgian == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
