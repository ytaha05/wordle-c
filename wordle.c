#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER 50
#define WC 2315
#define GUESS_WC 14855

#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define RED "\e[0;31m"
#define RESET "\e[0m"

int letter_count(char word[], char letter) {
    int i;
    int count = 0;
    
    for (i = 0; i < 5; i++) {
        if (letter == word[i]) {
            count++;
        }
    }
    return count;
}

char* wordle_loop(char answer[], char (*dictionary)[6]) {
    int i;
    char buffer[BUFFER];
    char guess[6]; // what the user guesses
    char* output = (char*)malloc(6 * sizeof(char));

    int valid = 0;
    while (valid == 0) {    
        fgets(buffer, BUFFER, stdin);
        sscanf(buffer, "%5s", guess);
        
        for (i = 0; i < GUESS_WC; i++) {
            if (strcmp(guess, dictionary[i]) == 0) {
                valid = 1;
                break;
            }
        }
        if (valid == 0) {
            printf("That word isn't in of the word list! Try again.\n");
        }
    }
    
    char letter;
    int guess_lc;
    int answer_lc;
    int output_lc;
    int output32_lc;
    
    /* GREEN LETTERS LOOP */
    for (i = 0; i < 5; i++) {
        letter = guess[i];
        
        if (letter == answer[i]) {
            output[i] = letter;
        } else {
            output[i] = letter + 32; /* YELLOW LETTER */
        }
    }
    
    /* RED LETTERS LOOP */
    for (i = 0; i < 5; i++) {
        letter = guess[i];
        guess_lc = letter_count(guess, letter);
        answer_lc = letter_count(answer, letter);
        output_lc = letter_count(output, letter);
        output32_lc = letter_count(output, letter + 32);

        if ((output_lc + output32_lc > answer_lc) && (letter != answer[i])) {
            output[i] = '#';
        }
    }
    
    /* COLORING LOOP */
    for (i = 0; i < 5; i++) {
        letter = guess[i];
        if (output[i] >= 'A' && output[i] <= 'Z') {
            printf(GREEN "%c" RESET, letter);
        } else if (output[i] >= 'a' && output[i] <= 'z') {
            printf(YELLOW "%c" RESET, letter);
        } else {
            printf(RED "%c" RESET, letter);
        }
    }
    printf("\n");

    output[5] = '\0';
    return output;
}

char (*dictionary_maker(FILE* word_list, int word_count))[6] {
    int i;
    char buffer[BUFFER];
    char (*dictionary)[6] = (char(*)[6])malloc(6 * word_count);

    for (i = 0; i < word_count; i++) {
        fgets(buffer, BUFFER, word_list);
        sscanf(buffer, "%5s", dictionary[i]);
    }
    return dictionary;
}

int main() {
    srand(time(NULL));
    int random_num = rand() % WC;
    
    FILE *txt_word = fopen("wordle_solutions.txt", "r");
    FILE *txt_guesses = fopen("wordle_guesses.txt", "r");
    
    char (*guess_dict)[6];
    char (*word_dict)[6];
    
    guess_dict = dictionary_maker(txt_guesses, GUESS_WC);
    word_dict = dictionary_maker(txt_word, WC);
    
    char wordle[6];
    char buffer[BUFFER];
    int i; 
    
    strcpy(wordle, word_dict[random_num]);
    
    char* wordle_o;
    char play_again = 'y';
    
    while (play_again == 'y' || play_again == 'Y') {
        printf("Welcome to Wordle!\n\n");
        printf("RULES:\n");
        printf("1. Guess the 5-letter word.\n");
        printf("2. You have 6 tries.\n");
        printf("3. Your guesses must be in ALL CAPS.\n");
        printf("4. A " RED "red" RESET " letter means the letter is not in the word.\n");
        printf("5. A " YELLOW "yellow" RESET " letter means the letter is in the word but in the wrong position.\n");
        printf("6. A " GREEN "green" RESET " letter means you've guessed the letter correctly in the correct position.\n\n");

        int won = 0;
        for (i = 0; i < 6; i++) {
            printf("\nGuess #%d \n", i + 1);
            wordle_o = wordle_loop(wordle, guess_dict);
            
            if (strcmp(wordle_o, wordle) == 0) { 
                free(wordle_o);
                printf("\nYou guessed correct!\n");
                printf("GUESSES: %d", i + 1);
                won = 1;
		break;
            }
        }
        
        if (won != 1) {
            printf("\nYou lost!");
            printf("\nThe word was" GREEN " %s" RESET, wordle);
        }
        
        printf("\nWould you like to play again? (Y/N): ");
        fgets(buffer, BUFFER, stdin);
        sscanf(buffer, "%1s", &play_again);

        if (play_again == 'y' || play_again == 'Y') {
            random_num = rand() % WC;
            strcpy(wordle, word_dict[random_num]);
        }
        printf("\n\n\n");
    } 
    
    free(wordle_o);
    free(guess_dict);
    free(word_dict);
    fclose(txt_word);
    fclose(txt_guesses);
    
    return 0;
}
