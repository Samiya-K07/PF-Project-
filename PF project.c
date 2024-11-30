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
