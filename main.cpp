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

//*******************************
//Prototype Functions
//*******************************

//Global Constants
const int ROWS = 100;
const int COLS = 100;

void buildArray(ifstream &, char [][COLS], int, int, int);
void showArray(ifstream &, ofstream &, char [][COLS], int, int, int);



//******************************
//Main Function
//******************************

int main(){
    
    //Declaring all of the variables that I will be using in the program.
    ifstream inputFile;
    ofstream outputFile;

    //char row;
    char mines[ROWS][COLS];
    //loop counters
    //int r, c;
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
        }else if (n <= 0 || m > 100){
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
        
        //The count is incremented each pass to keep track of the field.
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


void showArray(ifstream &file, ofstream &outFile, char values[][COLS], int rows, int n, int m){
    
    //Creating an array to hold the numbers for the mines. Each position
    //Will be set to 0 at the start.
    int mineSpots[n][m];
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            mineSpots[r][c] = 0;
        }
    }
    
    for (int row = 0; row < n + 1; row++) {
        for (int col = 0; col < m + 1; col++) {
            if (values[row][col] == '*') {
                mineSpots[row - 1][col - 1]++;
                mineSpots[row - 1][col]++;
                mineSpots[row - 1][col + 1]++;
                mineSpots[row][col - 1]++;
                mineSpots[row][col + 1]++;
                mineSpots[row + 1][col - 1]++;
                mineSpots[row + 1][col]++;
                mineSpots[row + 1][col + 1]++;
            }
        }
    }
    
//    for (int row = 0; row < n + 1; row++) {
//        for (int col = 0; col < m + 1; col++) {
//            if (values[row - 1][col] == -1) {
//                mineSpots[row - 1][col]++;
//            }
//            if (values[row - 1][col - 1] != -1){
//                mineSpots[row-1][col-1]++;
//            }
//            if (values[row - 1][col + 1] != -1){
//                mineSpots[row-1][col+1]++;
//            }
//            if (values[row][col - 1] != -1) {
//                mineSpots[row][col - 1]++;
//            }
//            if (values[row + 1][col] != -1) {
//                mineSpots[row + 1][col]++;
//            }
//            if (values[row + 1][col + 1] != -1) {
//               mineSpots[row + 1][col + 1]++;
//            }
//            if (values[row+1][col-1] != -1) {
//                mineSpots[row+1][col-1]++;
//            }
//            if (values[row][col+1] != -1) {
//                mineSpots[row][col+1]++;
//            }
//        }
//    }
    
    //This for loop displays the array.
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            if (values[r][c] == '*'){
                outFile << '*';
                cout << '*';
            }else{
                outFile << mineSpots[r][c];
                cout << mineSpots[r][c];
                }
            }
            cout << endl;
            outFile << endl;
    }



    
    //This for loop displays the array in the outputdata file. It will also place the correct number of mines
    //at each location that is near a mine.
//    for (int r = 0; r < n; r++){
//        for (int c = 0; c < m; c++){
//            if (values[r][c] == '*'){
//                outFile << '*';
//                cout << '*';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r - 1][c - 1] == '*')){
//                outFile << '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r - 1][c] == '*')){
//                outFile<< '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r - 1][c + 1] == '*')){
//                outFile << '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r][c - 1] == '*')){
//                outFile << '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r][c + 1] == '*')){
//                outFile << '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r + 2][c - 1] == '*')){
//                outFile << '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r + 2][c] == '*')){
//                outFile << '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r + 1][c + 1] == '*')){
//                outFile << '1';
//                cout << '1';
//            }else if (((values[r][c] == '.') || (values[r][c] == '0')) && (values[r + 2][c] == '*') && (values[r - 1][c - 1] == '*')){
//                outFile << '2';
//                cout << '2';
//            }else if(values[r][c] == '.'){
//                outFile << '0';
//                cout << '0';
//            }
//        }
//        cout << endl;
//        outFile << endl;
//    }
}// End of showArray Function












