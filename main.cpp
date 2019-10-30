/*
 * 2048.cpp
 * COMP11 Project 1, Spring 2019, Tufts University
 * Modified by: Tim White
 * Date: 03/09/2019
 */
#include <iostream>
#include <iostream>
#include <time.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Constants
const int array_length = 4;
const string leftm = "a";
const string rightm = "d";
const string upm = "w";
const string downm = "s";
const string quit = "q";


// Function prototypes
int string2int(string s);
string int2string(int num);
void print_padded_string(string s);
void pop_array(string game_array[][4], int array_length);
void play();
void move_array_down(string game_array[][4]);
void move_array_up(string game_array[][4]);
void move_array_right(string game_array[][4]);
void move_array_left(string game_array[][4]);
int add_array_values_left(string game_array[][4], int array_length);
int add_array_values_right(string game_array[][4]);
int add_array_values_up(string game_array[][4], int array_length);
int add_array_values_down(string game_array[][4]);
void print_game_array(string game_array[][4], int array_length);
void input_new_value(string game_array[][4]);
int execute_move_horizntl(string input_move, string game_array[][4]);
int execute_move_vertical(string input_move, string game_array[][4]);
bool game_over(string game_array[][4], int array_length);
bool check_empty_tiles(string game_array[][4], int array_length);




int main() {
    play();
    return 0; 
}

void play() {
    srand(time(NULL));
    int curr_score = 0;
    string game_array[4][4];
    cout << "Current Score: " << curr_score << endl;
    pop_array(game_array, array_length);
    print_game_array(game_array, array_length);
    while(game_over(game_array, array_length) == false) {
        string input_move;
        cin >> input_move;
        curr_score += execute_move_horizntl(input_move, game_array);
        curr_score += execute_move_vertical(input_move, game_array);
        if (input_move == quit){
             cout << "Game Over! " << endl;
             return;
        }
        else if ((input_move != downm) and (input_move != upm) and 
                (input_move != rightm) and (input_move != leftm)) {
            cout << " Command not recognized. Please try again. ";
        }
        cout << "Current score: " << curr_score << endl;
        print_game_array(game_array, array_length);
    }
    cout << "Game over! Your score is " << curr_score << endl;
}

/* Name: string2int
 * Purpose: Convert string to an int. 
 * Return: The int form of the given string.
 * Paramater: string 
 * Throw logic error if the string is not numerical. 
 */
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* Name: int2string
 * Purpose: Converts an int to string.
 * Return: Returns the string form of the given int
 * Paramater: int
 */
string int2string(int num) {
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}

/* Name: print_padded_string
 * Purpose: Print a string (persumably an int in the form of a string) with 
 * right paddings of up to 5 spaces
 * Return: Nothing
 * Parameter: string
 */
void print_padded_string(string s) {
    printf("%-6s", s.c_str());
}

/* Name: pop_array
 * Purpose: Populate the array with 0's and 2's.
 * Return: Nothing
 * Parameters: string, int
 */
void pop_array(string game_array[][4], int array_length) {
    for (int i = 0; i < array_length; i++){
        for (int j = 0; j < array_length; j++){
            game_array[i][j] = "-";
        }
    }
    srand(time(NULL));
    int rand_index_1 = rand() % 4;
    int rand_index_2 = rand() % 4;
    while (rand_index_1 == rand_index_2){
        rand_index_2 = rand() % 4;
    }
    game_array[rand_index_1][rand_index_2] = "2";
    game_array[rand_index_2][rand_index_1] = "2";

}
/* Name: print_game_array
 * Purpose: Print out the current array's padded values 
 * Return: Nothing
 * Parameters: string, int
 */
void print_game_array(string game_array[][4], int array_length) {
    for (int i = 0; i < array_length; i++){
        for (int j = 0; j < array_length; j++){
                print_padded_string(game_array[i][j]);
        }
    cout << "" << endl;
    }
}
/* Name: add_array_values_left
 * Purpose: Add array values (to the left) if adjacent values are equal
 * Return: Return the calculated current score
 * Parameters: string, int
 */
int add_array_values_left(string game_array[][4], int array_length) {
    int curr_score = 0;
    for (int i = 0; i < array_length; i++){
        for (int j = 0; j < array_length -1; j++){
            if ((game_array[i][j] == game_array[i][j + 1]) and 
            (game_array[i][j] != "-")){
                game_array[i][j] = int2string(string2int(game_array[i][j])
                                             * 2);
                game_array[i][j + 1] = "-";
                curr_score = string2int(game_array[i][j]) + curr_score;
            }
        }
    }
    return curr_score;
}
/* Name: add_array_values_up
 * Purpose: Add array values (upward) if adjacent values are equal
 * Return: Return the calculated current score 
 * Parameters: string, int
 */
int add_array_values_up(string game_array[][4], int array_length) {
    int curr_score = 0;
    for (int i = 0; i < array_length; i++){
        for (int j = 0; j < array_length; j++){
            if ((game_array[i][j] == game_array[i + 1][j]) and 
            (game_array[i][j] != "-")){
                game_array[i][j] = int2string(string2int(game_array[i][j])
                                             * 2);
                game_array[i + 1][j] = "-";
                curr_score = string2int(game_array[i][j]) + curr_score;
            }
        }
    }
    return curr_score;
}
/* Name: add_array_values_right
 * Purpose: Add array values (to the right) if adjacent values are equal
 * Return: Return the calculated current score
 * Parameter: string
 */
int add_array_values_right(string game_array[][4]) {
    int curr_score = 0;
    for (int i = 3; i >= 0; i--){
        for (int j = 3; j > 0; j--){
            if ((game_array[i][j] == game_array[i][j-1]) and 
            (game_array[i][j] != "-")){
                game_array[i][j] = int2string(string2int(game_array[i][j])
                                             * 2);
                game_array[i][j - 1] = "-";
                curr_score = string2int(game_array[i][j]) + curr_score;
            }
        }
    }
    return curr_score;
}
/* Name: add_array_values_down
 * Purpose: Add array values (downward) if adjacent values are equal
 * Return: Return the calculated current score
 * Parameters: string
 */
int add_array_values_down(string game_array[][4]) {
    int curr_score = 0;
    for (int i = 3; i > 0; i--){
        for (int j = 3; j >= 0; j--){
            if ((game_array[i][j] == game_array[i-1][j]) and 
            (game_array[i][j] != "-")){
                game_array[i][j] = int2string(string2int(game_array[i][j])
                                             * 2);
                game_array[i-1][j] = "-";
                curr_score = string2int(game_array[i][j]) + curr_score;
            }
        }
    }
    return curr_score;
}
/* Name: move_array_down
 * Purpose: Move array values to the southmost position 
 * Return: Return nothing
 * Parameter: string
 */
void move_array_down(string game_array[][4]) { 
    for(int j = 3; j >= 0; j--){
        for (int i = 3; i >= 0; i--){
            if (game_array[i][j] != "-"){
                int m = 3;
                while((game_array[m][j] != "-") and (m > i)){
                    m--;
                }
                string k = game_array[i][j];
                game_array[i][j] = "-";
                game_array[m][j] = k;
            }
        }
    }
}
/* Name: move_array_right
 * Purpose: Move array values to the rightmost position 
 * Return: Nothing
 * Parameter: string
 */
void move_array_right(string game_array[][4]) { 
    for(int i = 3; i >= 0; i--){
        for (int j = 3; j >= 0; j--){
            if (game_array[i][j] != "-"){
                int m = 3;
                while((game_array[i][m] != "-") and (m > j)){
                    m--;
                }
                string k = game_array[i][j];
                game_array[i][j] = "-";
                game_array[i][m] = k;
            }
        }
    }
}
/* Name: move_array_up
 * Purpose: Move array values to the upmost position 
 * Return: Nothing
 * Parameter: string
 */
void move_array_up(string game_array[][4]) {
    for(int j = 0; j <= 3; j++){
        for (int i = 0; i <= 3; i++){
            if (game_array[i][j] != "-"){
                int m = 0;
                while((game_array[m][j] != "-") and (m != i)){
                    m++;
                }
                string k = game_array[i][j];
                game_array[i][j] = "-";
                game_array[m][j] = k;
            }
        }  
    }
}
/* Name: move_array_left
 * Purpose: Move array values to the leftmost position 
 * Return: Nothing
 * Parameter: string
 */
void move_array_left(string game_array[][4]) {
    for(int i = 0; i <= 3; i++){
        for (int j = 0; j <= 3; j++){
            if (game_array[i][j] != "-"){
                int m = 0;
                while((game_array[i][m] != "-") and (m < j)){
                    m++;
                }

                string k = game_array[i][j];
                game_array[i][j] = "-";
                game_array[i][m] = k;
            }
        }  
    }
}
/* Name: input_new_value
 * Purpose: Input a new values (2 or 4) into two empty spots in the array 
 * Return: Nothing
 * Parameter: string
 */
void input_new_value(string game_array[][4]) {
    if (check_empty_tiles(game_array, array_length) == false){
        return;
    }
    int rand_index_3 = rand() % 4;
    int rand_index_4 = rand() % 4;
    while(game_array[rand_index_3][rand_index_4] != "-"){
        rand_index_3 = rand() % 4;
        rand_index_4 = rand() % 4;
    }
    int rand_num_2_or_4 = rand() % 9;
    if (rand_num_2_or_4 == 0){
        game_array[rand_index_3][rand_index_4] = "4";
    }
    if (rand_num_2_or_4 != 0){
        game_array[rand_index_3][rand_index_4] = "2";
    }
}
/* Name: game_over
 * Purpose: End the game if no more moves are available
 * Return: Return true if board is full and no values can combine. Return
 * false otherwise.
 * Parameter: string, int
 */
bool game_over(string game_array[][4], int array_length) {
    for (int i = 0; i < array_length; i++){
        for (int j = 0; j < array_length - 1; j++){
            if ((game_array[i][j] == game_array[i][j+1]) or 
               (game_array[i][j] == "-") or (game_array[i][j+1] == "-")){
                    return false;
            }
        }
    }
    for (int i = 0; i < array_length - 1; i++){
        for (int j = 0; j < array_length; j++){    
            if ((game_array[i][j] == game_array[i+1][j]) or 
               (game_array[i][j] == "-") or (game_array[i+1][j] == "-")){
                    return false;
            }
        }
    }
    cout << " " << endl;
    return true;

}
/* Name: execute_move_horizntl
 * Purpose: Execute move action (horizontally)
 * Return: Return the calculated score change
 * Parameter: string
 */
int execute_move_horizntl(string input_move, string game_array[][4]) {
    int score_change = 0;
    if (input_move == rightm){
        move_array_right(game_array);
        score_change = add_array_values_right(game_array);
        move_array_right(game_array);
        input_new_value(game_array);
    }
    if (input_move == leftm){
        move_array_left(game_array);
        score_change = add_array_values_left(game_array, array_length);
        move_array_left(game_array);
        input_new_value(game_array);
    }
    return score_change;
}
/* Name: execute_move_vertical
 * Purpose: Execute move action (vertically)
 * Return: Return the calculated score change
 * Parameters: string, string
 */
int execute_move_vertical(string input_move, string game_array[][4]) {
    int score_change = 0;
    if (input_move == downm){
        move_array_down(game_array);
        score_change = add_array_values_down(game_array);
        move_array_down(game_array);
        input_new_value(game_array);
    }
    if (input_move == upm){
        move_array_up(game_array);
        score_change = add_array_values_up(game_array, array_length);
        move_array_up(game_array);
        input_new_value(game_array);
    }
    return score_change;
}
/* Name: check_empty_tiles
 * Purpose: Check the board for any empty tiles
 * Return: Return true if at least one tile is empty. Return false if array
 * is full.
 * Parameters: string, int
 */
bool check_empty_tiles(string game_array[][4], int array_length) {
    for (int i = 0; i < array_length; i++){
        for (int j = 0; j < array_length; j++){
            if (game_array[i][j] == "-"){
                return true;
            }
        }
    }
    return false;
}
