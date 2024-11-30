#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 5
#define MAX_PLAYERS 100
#define QUESTION_LENGTH 256
#define OPTION_LENGTH 50
#define NAME_LENGTH 200
#define PF_FILE "PFquestions.txt"
#define AP_FILE "APquestions.txt"
#define CAL_FILE "CALquestions.txt"
#define HIGHEST_SCORE_FILE "highestscore.txt"
#define ALL_SCORES_FILE "scoreboard.txt"

typedef struct 
{
    char question[QUESTION_LENGTH];
    char options[4][OPTION_LENGTH];
    char correct_answer;

} QuizQuestion;

typedef struct 
{
    char user_name[NAME_LENGTH]; 
    int individual_score; 

} Scoreboard;

void LoadQuestionsFromFile(QuizQuestion quiz[], const char *FileName);
void WritePFQuestionsToFile();
void WriteAPQuestionsToFile();
void WriteCALQuestionsToFile();
int GetHighestScore();
void UpdateHighestScore(int new_highest_score); 
void DisplayCurrentQs(QuizQuestion current_qs);
int CheckAnswers(QuizQuestion quiz[], int order_of_questions[], char user_ans[], int total_score);
void PlayQuiz(QuizQuestion quiz[], int num_of_qs, const char *name);
void AllScores(const char *name, int total_score);
int GetScores(Scoreboard player_data[]);
void DisplayScores();

int main() {
    
    QuizQuestion quiz[MAX_QUESTIONS];
    Scoreboard player_data[MAX_PLAYERS]; 

    int choice, option, num_of_qs = MAX_QUESTIONS, attempted_rounds = 0;
    char name[NAME_LENGTH]; 

    FILE *fptr;
    
    if ((fptr = fopen(PF_FILE, "r")) == NULL) 
    {
        WritePFQuestionsToFile();
    } 
    
    else 
    {
        fclose(fptr);
    }
    
    if ((fptr = fopen(AP_FILE, "r")) == NULL) 
    {
        WriteAPQuestionsToFile();
    } 
    
    else 
    {
        fclose(fptr);
    }

    if ((fptr = fopen(CAL_FILE, "r")) == NULL) 
    {
        WriteCALQuestionsToFile();
    } 
    
    else 
    {
        fclose(fptr);
    }

    srand(time(NULL));  
    
    printf("\n\t\t\t\t\t\033[38;5;44mWELCOME TO THE QUIZ GAME!!\033[0m");
    printf("\n\t\t\t\t\t\033[38;2;216;191;216mARE YOU READY TO SHOWCASE YOUR SKILLS?\033[0m\n\t\t\t\t\t\033[38;5;214mWE WISH YOU THE BEST OF LUCK :)\033[0m\n");
    printf("\033[38;2;106;5;114m____________________________________________________________________________________________________________________________________________________\033[0m\n\n");
    
    printf("Enter your name: ");
    fgets(name, NAME_LENGTH, stdin); 
    name[strcspn(name, "\n")] = '\0';
    printf("\033[38;2;106;5;114m____________________________________________________________________________________________________________________________________________________\033[0m\n\n");

    while (1)
    {  
        printf("\033[38;2;255;255;224mMENU:\033[0m\n");
        printf("\033[38;2;106;5;114m___________________________________\033[0m\n\n");
        printf("\033[38;2;144;238;144m1. Play the Quiz Game\033[0m\n");
        printf("\033[38;5;44m2. View the Highest Score\033[0m\n"); 
        printf("\033[38;2;216;191;216m3. View the Scoreboard\033[0m\n"); 
        printf("\033[38;2;231;111;81m4. Exit the Program!!\033[0m\n"); 
        printf("\033[38;2;106;5;114m___________________________________\033[0m\n\n");

        printf("Enter your choice (1-3): ");
        scanf("%d", &option);
        

        switch (option) 
        {
            case 1:
            
            printf("\nChoose a subject for your quiz:\n");
            printf("\033[38;2;106;5;114m_________________________________________\033[0m\n\n");
            printf("\033[38;5;44m1. Programming Fundamentals (PF)\033[0m\n");
            printf("\033[38;2;144;238;144m2. Applied Physics (AP)\033[0m\n");
            printf("\033[38;5;214m3. Calculus (CAL)\033[0m\n");
            printf("\033[38;2;106;5;114m_________________________________________\033[0m\n\n");

            printf("Enter your choice (1-3): ");
            scanf("%d", &choice);

            switch (choice) 
            {
                case 1:
                LoadQuestionsFromFile(quiz, PF_FILE);
                printf("\nYou selected Programming Fundamentals!\n\n");
                break;                   
                
                case 2:
                LoadQuestionsFromFile(quiz, AP_FILE);
                printf("\nYou selected Applied Physics.\n\n");
                break;
        
                case 3:
                LoadQuestionsFromFile(quiz, CAL_FILE);
                printf("\nYou selected Calculus.\n\n");
                break;
            
                default:
                printf("\nInvalid subject choice!! Returning to menu...\n\n");
                continue; 
            }
                attempted_rounds++;

                printf("\033[38;2;106;5;114m______________________________\033[0mOn your marks, get set, GO!!\033[38;2;106;5;114m_______________________________________\033[0m\n\n"); 
                printf("\033[38;2;106;5;114m--------------------------------------\033[0mROUND %d\033[38;2;106;5;114m---------------------------------------------------\033[0m\n\n", attempted_rounds);
                PlayQuiz(quiz, num_of_qs, name);
                break;

            case 2:
            
            if (attempted_rounds == 0 && GetHighestScore() == 0) 
            {
                printf("\nNo games played yet!! No highest score to display.\n\n");
            } 
            
            else 
            {
                printf("\nThe highest score is: %d\n\n", GetHighestScore());
            }
                break;

            
            case 3:
            
            DisplayScores(); 
            break;

            case 4:
            
            printf("\nThank you for playing! Exiting the program...\n");
            exit(0);

            default:
            printf("\nInvalid menu option! Please select a valid option.\n\n");
            continue; 
        }
    }
    
    return 0;
}

void WritePFQuestionsToFile() 
{
    FILE *fptr = fopen(PF_FILE, "w");
    
    if (!fptr) 
    {
        printf("Error opening file for writing: %s. Exiting the program....\n", PF_FILE);
        exit(1);
    }

    fprintf(fptr, "Which of the following is used to declare a variable in C?\n");
    fprintf(fptr, "var\nint\nlet\nstring\n");
    fprintf(fptr, "b\n");

    fprintf(fptr, "Which of the following is the correct syntax for a for loop in C?\n");
    fprintf(fptr, "for (int i = 0; i < 10; i++)\nfor i = 0; i < 10; i++\nfor (i = 0; i < 10; i++)\nfor (int i; i < 10; i++)\n");
    fprintf(fptr, "a\n");

    fprintf(fptr, "What is the correct way to declare a pointer in C?\n");
    fprintf(fptr, "int ptr;\nptr int;\nint* ptr;\nptr* int;\n");
    fprintf(fptr, "c\n");

    fprintf(fptr, "What does the following code do? 'printf(\"Hello World!\");'\n");
    fprintf(fptr, "Prints 'Hello World!'\nDefines a function 'Hello World!'\nDeclares a variable\nLoops through the array\n");
    fprintf(fptr, "a\n");

    fprintf(fptr, "Which keyword is used to define a constant in C?\n");
    fprintf(fptr, "const\ndefine\nstatic\nfinal\n");
    fprintf(fptr, "a\n");

    fclose(fptr);
}

void WriteAPQuestionsToFile() 
{
    FILE *fptr = fopen(AP_FILE, "w");
    
    if (!fptr) 
    {
        printf("Error opening file for writing: %s\n", AP_FILE);
        exit(1);
    }

    fprintf(fptr, "What is the SI unit of force?\n");
    fprintf(fptr, "Joule\nNewton\nPascal\nWatt\n");
    fprintf(fptr, "b\n");

    fprintf(fptr, "What is the acceleration due to gravity on Earth?\n");
    fprintf(fptr, "8.9 m/s^2\n9.8 m/s^2\n10 m/s^2\n11 m/s^2\n");
    fprintf(fptr, "b\n");

    fprintf(fptr, "What is the formula for kinetic energy?\n");
    fprintf(fptr, "mv\nmv^2\nmgh\nFd\n");
    fprintf(fptr, "b\n");

    fprintf(fptr, "What does Ohms Law state?\n");
    fprintf(fptr, "V = IR\nV = I/R\nR = IV\nI = VR\n");
    fprintf(fptr, "a\n");

    fprintf(fptr, "What is the speed of light in vacuum?\n");
    fprintf(fptr, "3 x 10^8 m/s\n3 x 10^6 m/s\n2 x 10^8 m/s\n3 x 10^5 m/s\n");
    fprintf(fptr, "a\n");

    fclose(fptr);
}

void WriteCALQuestionsToFile() 
{
    FILE *fptr = fopen(CAL_FILE, "w");
    
    if (fptr == NULL) 
    {
        printf("Error!! File cannot be opened for writing: %s\n", CAL_FILE);
        exit(1);
    }

    fprintf(fptr, "What is the derivative of x^2?\n");
    fprintf(fptr, "x\n2x\n2\nx^2\n");
    fprintf(fptr, "b\n");

    fprintf(fptr, "What is the integral of 1/x dx?\n");
    fprintf(fptr, "x^2\nln(x)\ne^x\n1/x^2\n");
    fprintf(fptr, "b\n");

    fprintf(fptr, "What is the derivative of sin(x)?\n");
    fprintf(fptr, "cos(x)\n-cos(x)\nsin(x)\n-sin(x)\n");
    fprintf(fptr, "a\n");

    fprintf(fptr, "What is the integral of e^x dx?\n");
    fprintf(fptr, "x\ne^x\nln(x)\n1/x\n");
    fprintf(fptr, "b\n");

    fprintf(fptr, "What is the derivative of tan(x)?\n");
    fprintf(fptr, "sec^2(x)\ncsc^2(x)\nsec(x)\ntan(x)\n");
    fprintf(fptr, "a\n");

    fclose(fptr);
}

void LoadQuestionsFromFile(QuizQuestion quiz[], const char *FileName) 
{
    FILE *fptr = fopen(FileName, "r");
    
    if (!fptr) 
    {
        printf("Error opening file: %s\n", FileName);
        exit(1);
    }
    
    for ( int i = 0; i < MAX_QUESTIONS; i++)
    {
        fgets(quiz[i].question, QUESTION_LENGTH, fptr); 
        quiz[i].question[strcspn(quiz[i].question, "\n")] = '\0';

        for (int j = 0; j < 4; j++) 
        {
            fgets(quiz[i].options[j], OPTION_LENGTH, fptr);
            quiz[i].options[j][strcspn(quiz[i].options[j], "\n")] = '\0';
        }

        char temp_array[10];
        fgets(temp_array, sizeof(temp_array), fptr);
        quiz[i].correct_answer = temp_array[0];
        
    }

    fclose(fptr);

    return;
}

void DisplayCurrentQs(QuizQuestion current_qs)
{
    printf("%s\n", current_qs.question);

    for (int i = 0; i < 4; i++)
    {
        printf("%c) %s\n", ('a' + i), current_qs.options[i]); 
    }
    
}

int CheckAnswers(QuizQuestion quiz[], int order_of_question[], char user_ans[], int total_score) 
{  
    printf("\033[38;2;106;5;114m-----------------------------------------------\033[0mQuiz has ended!!\033[38;2;106;5;114m-----------------------------------------------\033[0m\n\n");
    
    for (int i = 0; i < MAX_QUESTIONS; i++)
    {
        int qs_order = order_of_question[i];
        QuizQuestion current_qs = quiz[qs_order]; 

        DisplayCurrentQs(current_qs);   
        printf("\n\033[32mAnswer = %c\033[0m\n\n", current_qs.correct_answer); 

        if (user_ans[i] == current_qs.correct_answer)
        {
            printf("\033[32mYour Answer = %c\tCorrect!!\033[0m\n\n", user_ans[i]);
            total_score++; 
        }

        else
        {
            printf("\033[31mYour Answer = %c\tIncorrect!!\033[0m\n\n", user_ans[i]); 
        }
            
    }

    printf("Your final score: %d out of %d\n", total_score, MAX_QUESTIONS);

    if (total_score <= 2)
        {
            printf("\nNo time to waste!! Work harder!!\n"); 
        }

    else if (total_score > 2 && total_score < MAX_QUESTIONS)
    {
        printf("\nAlmost there!! You can do it!!\n"); 
    }
        
    else
    {
        printf("\n\033[32mCONGRATULATIONS!! You have mastered your skill in the subject!!\033[0m\n");
    }

    return total_score; 
}

void PlayQuiz(QuizQuestion quiz[], int num_of_qs, const char *name)
{
    int total_score = 0; 
    num_of_qs = MAX_QUESTIONS;

    char user_ans[MAX_QUESTIONS];
    int order_of_question[MAX_QUESTIONS];

    for (int i = 0; i < MAX_QUESTIONS; i++) 
    {
        order_of_question[i] = i;
    }

    for (int i = MAX_QUESTIONS - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        
        int temp = order_of_question[i];
        order_of_question[i] = order_of_question[j];
        order_of_question[j] = temp;
    }

    for (int i = 0; i < MAX_QUESTIONS; i++)
    {
        int random_index = order_of_question[i];
        QuizQuestion current_qs = quiz[random_index];

        printf("\n");
        DisplayCurrentQs(current_qs);
        printf("\n"); 

        char user_answer; 
        printf("Enter your answer (a, b, c, or d): ");
        scanf(" %c", &user_answer);
        
        while ((user_answer != 'a') && (user_answer != 'b') && (user_answer != 'c') && (user_answer != 'd'))
        {
            printf("\nInvalid option!! Enter the option again!!\n");
            printf("\033[38;2;106;5;114m_______________________________________________________________________________________________________________________________\033[0m\n\n"); 
            DisplayCurrentQs(current_qs);
            printf("\n"); 
            printf("Enter your answer (a, b, c, or d): ");
            scanf(" %c", &user_answer);        
        }
        
        user_ans[i] = user_answer; 

    }

    total_score = CheckAnswers(quiz, order_of_question, user_ans, total_score);
    AllScores(name, total_score);

    int highest_score = GetHighestScore();

    if (total_score > highest_score)
    {
        printf("\n\033[38;2;106;5;114m-----------------------------------------\033[0m\033[32mCONGRATULATIONS!! You have set a new highscore!!\033[0m\033[38;2;106;5;114m----------------------------------------\033[0m\n\n"); 
        UpdateHighestScore(total_score); 
    }
    
    else if (total_score == highest_score)
    {
        printf("\n\033[38;2;106;5;114m----------------------------------------\033[0m\033[32mCONGRATULATIONS!! You have matched the current highscore!!\033[0m\033[38;2;106;5;114m-------------------------------\033[0m\n\n"); 
    }

    else
    {
        printf("\n\033[38;2;106;5;114m----------------------------------------\033[0mThe highest score remains: %d. Better Luck Next Time!!\033[38;2;106;5;114m----------------------------------------\033[0m\n\n", highest_score); 
    }

    return;
}

void AllScores(const char *name, int total_score)
{
    FILE *fptr = fopen(ALL_SCORES_FILE, "a"); 
    
    if (fptr == NULL) 
    {
        printf("Error!! File cannot be opened for writing: %s\n", ALL_SCORES_FILE);
        exit(1);
    }

    fprintf(fptr, "%d\n%s\n", total_score, name); 
    fclose(fptr);

}
