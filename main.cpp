/*
 program: Lesson 9 Program 2
 Programmer: Mike Cuddy
 Date: 12 October 2016
 Other: N/A
 */

/*
 
 Explanation: Write a program which will aid an individual playing MineSweeper.
 
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Global Constants
const int ROWS = 100;
const int COLS = 100;

//*******************************
//Prototype Functions
//*******************************

void buildArray(ifstream &, char [][COLS], int, int, int);
void showArray(ifstream &, ofstream &, char [][COLS], int, int, int);

//******************************
//Main Function
//******************************

int main(){
    
    //Declaring all of the variables that I will be using in the program.
    ifstream inputFile;
    ofstream outputFile;

    char mines[ROWS][COLS];
    //Variables to keep track of the number of rows and columns.
    int n, m;
    //variable to keep track of the number of fields
    int count = 1;
    
    //Opening the file
    inputFile.open("inputdata.txt");
    
    //Opening/creating the file to which store the information in this program.
    outputFile.open("outputdata.txt");
    
    //Checking for errors in the file.
    if (inputFile.fail())
    {
        cout << "Error opening data file. Progam will now close. \n\n";
        //system("pause"); //This line is for Microsoft Visual studio users.
        exit(0);
    }
    
    //This loop will read the information from the file until it is empty.
    while (!inputFile.eof()){
        
        //These two lines will read the numerical values in each file and then they will be used as a counter
        //for the loop.
        inputFile >> n;
        inputFile >> m;

        //If the both values are zero, the program knows to break the while loop. Also, if the values are out of range then
        //the loop will break as well.
        if (n == 0 && m == 0){
            break;
        }else if (n <= 0){
            outputFile << "Sorry, the number of rows you have is less than 0!" << endl;
            break;
        }else if (m > 100){
            outputFile << "Sorry, the number of columns you have is greater than 100!" << endl;
            break;
        }
        
        //Calling the function to build each of the 2D arrays
        buildArray(inputFile, mines, ROWS, n, m);
        
        //This line is simply to display the field for each array in the txt document.
        outputFile << "Field #" << count << endl;
        
        //This function will build the new arrays.
        showArray(inputFile, outputFile, mines, ROWS, n, m);
        
        //These lines ensure that there is a space between each array.
        cout << endl;
        outputFile << endl;
        
        //The count is incremented each pass to keep track of the field number.
        count++;
   }


    //Closing the input file.
    inputFile.close();
    //Closing the output file.
    outputFile.close();
    
    //system("pause"); //This line is for Microsoft Visual users.
    
    return 0;
    
}//End of main function

//******************************
//Functions
//******************************

//This function will build the array from the inputdata.txt file.
void buildArray(ifstream &file, char values[][COLS], int rows, int n, int m){
        char row;
    
        //This for loop goes through the document to build the array.
        for (int r = 0; r < n; r++){
            for (int c = 0; c < m; c++){
                file >> row;
                values[r][c] = row;
            }
    }
} // End of buildArray Function

//This function will find all the mines and then output what it finds to the outputdata.txt file.
void showArray(ifstream &file, ofstream &outFile, char values[][COLS], int rows, int n, int m){
    
    //Creating an array to hold the numbers for the mines. Each position
    //Will be set to 0 at the start.
    int mineSpots[n][m];
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            mineSpots[r][c] = 0;
        }
    }
    
    //This for loop is what will actually find the locations of the mines. It uses a counter to go through every position around
    //a spot that has an '*' and counts to determine the correct number of mines around that location.
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (values[row][col] == '*') {
                if ((row - 1 >= 0) && (col - 1 >= 0) ){
                    mineSpots[row - 1][col - 1]++;
                }
                if (row - 1 >= 0){
                    mineSpots[row - 1][col]++;
                }
                if ( (col < m - 1) && (row > 0)){
                    mineSpots[row - 1][col + 1]++;
                }
                if (col - 1 >= 0){
                    mineSpots[row][col - 1]++;
                }
                if (!(col >= m - 1)){
                    mineSpots[row][col + 1]++;
                }
                
                if (col - 1 >= 0){
                    mineSpots[row + 1][col - 1]++;
                }
                if ((row < n - 1) && (col < m - 1)){
                    mineSpots[row + 1][col + 1]++;
                }
                mineSpots[row + 1][col]++;
            }
        }
    }
    
    //This for loop displays the array.
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            if (values[r][c] == '*'){
                outFile << '*';
            }else{
                outFile << mineSpots[r][c];
                }
            }
            cout << endl;
            outFile << endl;
    }
}// End of showArray Function
