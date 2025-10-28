// #Project 2 Abo Hadhod 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
using namespace std;
enum enOperationType {Add = 1 , Sul = 2 , Mul = 3 , Div = 4 , OpMix = 5};
enum enLevel { Easy = 1 , Mid = 2 , Hard = 3 , Mix = 4};
struct stQuestion
{
    short Number1 = 0;
    short Number2 = 0;
    short QuestionNumber = 0;
    enOperationType QuestionOpType;
    enLevel QuestionLevel;
    short CorrectAnswer = 0;
    short PlayerAnswer = 0;
    bool ResultAnswer = false;
};
struct stQuiz
{
    stQuestion Question[100];
   enLevel  QuizLevel;
   enOperationType  OpType;
    short NumberQuestions = 0;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = true;
};
short RandomNumber(short From, short To)
{
    short RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;
}
short ReadHowManyQuestions()
{
    short Num;
    cout << "How Many questions do you want ? ---->";
    cin >> Num;
    return Num;
}
enOperationType ReadOpType()
{
    short Num;
    do
    {
        cout << "Choose Operation Type ? [1]:Add , [2]:Sul , [3]:Mul , [4]:Div , [5]:Mix? ---->";
        cin >> Num;
    } while (Num < 1 || Num > 5);
    return (enOperationType)Num;
    
}
enLevel ReadLevel()
{
    short Num;
    do
    {
        cout << "Choose The Level ? [1]:Easy , [2]:Mid , [3]:Hard , [4]:Mix ? ---->";
        cin >> Num;
    }while (Num < 1 || Num >4);
    return (enLevel)Num;
}
enOperationType GetMixOpType()
{
    short Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}
short SimpleCalculate(short Num1, short Num2, enOperationType OpType)
{
    switch (OpType)
    {
    case (enOperationType::Add):
            return Num1 + Num2;
    case (enOperationType::Sul):
            return Num1 - Num2;
    case (enOperationType::Mul):
            return Num1 * Num2;
    case (enOperationType::Div):
            return Num1 / Num2;
    default:
            return Num1 + Num2;
    }
}
stQuestion QuestionFunction(enLevel Level , enOperationType OpType)
{
    stQuestion Question;
    if (Level == enLevel::Mix)
    {
        Level = (enLevel)RandomNumber(1, 3);
    }
    if (OpType ==  enOperationType::OpMix)
    {
        OpType =  GetMixOpType() ;
    }
    Question.QuestionOpType = OpType;
    
    switch (Level)
    {
    case enLevel::Easy:
    {
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculate(Question.Number1, Question.Number2, Question.QuestionOpType);
        Question.QuestionLevel = Level;
        return Question;
    }
    case enLevel::Mid:
    {
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculate(Question.Number1, Question.Number2, Question.QuestionOpType);
        Question.QuestionLevel = Level;
        return Question;

    }
    case enLevel::Hard:
    {
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculate(Question.Number1, Question.Number2, Question.QuestionOpType);
        Question.QuestionLevel = Level;
        return Question;

    }
    }
}
void CollectData( stQuiz &Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberQuestions; QuestionNumber++)
    {
        Quiz.Question[QuestionNumber] = QuestionFunction(Quiz.QuizLevel, Quiz.OpType);
    }
}
string OpTypeSymblo(enOperationType OpType)
{
    switch (OpType)
    {
    case (enOperationType::Add):
        return "+";
    case (enOperationType::Sul):
        return "-";
    case (enOperationType::Mul):
        return "*";
    case (enOperationType::Div):
        return "/";
    default:
        return "Mix";
    }
}
short PlayerAnswer()
{
    short Answer;
    cin >> Answer;
    return Answer;
}
void PrintQuesion(short QuestionNumber , stQuiz &Quiz)
{
    cout << "Question [" << QuestionNumber +1 << "/" << Quiz.NumberQuestions << "]\n\n";
    cout << Quiz.Question[QuestionNumber].Number1 << endl;
    cout << Quiz.Question[QuestionNumber].Number2 << " " << OpTypeSymblo(Quiz.Question[QuestionNumber].QuestionOpType) << endl;
    cout << "___________\n";
    Quiz.Question[QuestionNumber].PlayerAnswer = PlayerAnswer() ;
}
void SelectScreenColor(bool Result)
{
    if (Result == true)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}
void CorrectAnswer(short QuestionNumber,stQuiz &Quiz)
{
    if (Quiz.Question[QuestionNumber].PlayerAnswer != Quiz.Question[QuestionNumber].CorrectAnswer)
    {
        Quiz.Question[QuestionNumber].ResultAnswer = false;
        Quiz.NumberOfWrongAnswers++;
        cout << "\nWrong Answer :-(\n";
        cout << "the right answer is : " << Quiz.Question[QuestionNumber].CorrectAnswer << "\n\n";
    }
    else
    {
       Quiz.Question[QuestionNumber].ResultAnswer = true;
        Quiz.NumberOfRightAnswers++;
        cout << "\nRight Answer :-)\n\n";
    }
    SelectScreenColor(Quiz.Question[QuestionNumber].ResultAnswer);
}
void AskAndCorrectAnswer(stQuiz &Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberQuestions; QuestionNumber++)
    {
        PrintQuesion(QuestionNumber, Quiz);
        CorrectAnswer(QuestionNumber, Quiz);
    }
    Quiz.IsPass = Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers;

}
string WriteQuizLevel(enLevel Level)
{
    string Arr[4] = { "Easy" , "Mid" , "Hard" , "Mix" };
    return Arr[Level - 1];
}
void FinalResult(stQuiz Quiz)
{
    cout << "________________________________\n\n";
    cout << " Final Result Is ";
    if (Quiz.IsPass)
        cout << "Pass :-)\n\n";
    else
    {
        cout << "Fail :-(\n\n";
    }
    cout << "________________________________\n\n";
    cout << "Number of Questions     :" << Quiz.NumberQuestions << endl;
    cout << "Questions Level         :" << WriteQuizLevel(Quiz.QuizLevel) << endl;
    cout << "OpType                  :" << OpTypeSymblo(Quiz.OpType)<<endl;
    cout << "Number of Right Answers :" << Quiz.NumberOfRightAnswers<<endl;
    cout << "Number of Wrong Answers :" << Quiz.NumberOfWrongAnswers<<endl;
    cout << "________________________________\n\n";
    SelectScreenColor(Quiz.IsPass);
}

void PlayMathGame()
{
    stQuiz Quiz;
    Quiz.NumberQuestions = ReadHowManyQuestions();
    Quiz.QuizLevel = ReadLevel();
    Quiz.OpType = ReadOpType();

    CollectData(Quiz);
    AskAndCorrectAnswer(Quiz);
    FinalResult(Quiz);

}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void StartQuiz()
{
    char PlayAgian = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();

        cout << "Do you want play agian ? Y/N ---->";
        cin >> PlayAgian;
    } while (PlayAgian == 'y' || PlayAgian == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartQuiz();
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
