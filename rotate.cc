// Solution to "Rotate" from Google's Code Jam, by Ian K. Lee
// https://code.google.com/codejam/contest/544101/dashboard

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    
    // T is the number of test cases
    int T;
    
    ifstream inputFile;
    inputFile.open(argv[1]);

    inputFile >> T;
    
    // for each game of connect-K
    for (int i = 0; i < T; i++) {
        
        // N is the number of rows, and characters per row
        // K is the number of pieces in a row that need to be formed
        int N, K;
        vector<string> rows;
        
        inputFile >> N >> K;
        
        // for each row, with N rows...
        for (int j = 0; j < N; j++) {
            string row;
            inputFile >> row;
            rows.push_back(row);
        }
        
        // rotate the table
        char rotatedTable[N][N];
        for (int ii = 0; ii < N; ii++) 
            for (int jj = 0; jj < N; jj++) 
                rotatedTable[ii][jj] = rows[N-jj-1][ii];
        
        // let gravity happen
        for (int ii = N-2; ii >= 0; ii--) {
            for (int jj = 0; jj < N; jj++) {
                
                int rowDroppedTo = ii;
                for (int ii2 = ii+1; ii2 < N; ii2++) 
                    if (rotatedTable[ii2][jj] == '.')
                        rowDroppedTo = ii2;
                    else 
                        break;
                
                char value = rotatedTable[ii][jj];
                rotatedTable[ii][jj] = '.';
                rotatedTable[rowDroppedTo][jj] = value;
            }
        }
        
        // who's the winner?
        bool redHasWin = false, blueHasWin = false;
        int red, blue;
        
        // horizontal scan
        red = 0;
        blue = 0;
        for (int ii = 0; ii < N; ii++)
            for (int jj = 0; jj < N; jj++) {
                char value = rotatedTable[ii][jj];
                if (value == 'R') {
                    red++;
                    blue = 0;
                } else if (value == 'B') {
                    blue++;
                    red = 0;
                } else {
                    red = 0; 
                    blue = 0;
                }
                
                if (red == K)
                    redHasWin = true;
                if (blue == K)
                    blueHasWin = true;
            }
        
        // vertical scan
        red = 0;
        blue = 0;
        for (int jj = 0; jj < N; jj++)
            for (int ii = 0; ii < N; ii++) {
                char value = rotatedTable[ii][jj];
                if (value == 'R') {
                    red++;
                    blue = 0;
                } else if (value == 'B') {
                    blue++;
                    red = 0;
                } else {
                    red = 0; 
                    blue = 0;
                }
                
                if (red == K)
                    redHasWin = true;
                if (blue == K)
                    blueHasWin = true;
            }
        
        // create a shifted table for the left-right diagonal scan
        char leftDiagonalTable[N][2*N-1];
        memset(leftDiagonalTable, 0, sizeof(leftDiagonalTable));
        int shift = 0;
        for (int ii = 0; ii < N; ii++) {
            for (int jj = 0; jj < N; jj++)
                leftDiagonalTable[ii][jj+shift] = rotatedTable[ii][jj];
            shift++;
        }
        
        // left-right diagonal scan
        red = 0;
        blue = 0;
        for (int jj = 0; jj < 2*N-1; jj++)
            for (int ii = 0; ii < N; ii++) {
                char value = leftDiagonalTable[ii][jj];
                if (value == 0) {
                    red = 0;
                    blue = 0;
                    continue;
                }
                
                if (value == 'R') {
                    red++;
                    blue = 0;
                } else if (value == 'B') {
                    blue++;
                    red = 0;
                } else {
                    red = 0; 
                    blue = 0;
                }
                
                if (red == K) 
                    redHasWin = true;
                if (blue == K)
                    blueHasWin = true;
            }
            
        // create a shifted table for the right-left diagonal scan
        char rightDiagonalTable[N][2*N-1];
        memset(rightDiagonalTable, 0, sizeof(rightDiagonalTable));
        shift = 0;
        for (int ii = N-1; ii >= 0; ii--) {
            for (int jj = 0; jj < N; jj++)
                rightDiagonalTable[ii][jj+shift] = rotatedTable[ii][jj];
            shift++;
        }
            
        // right-left diagonal scan
        red = 0;
        blue = 0;
        for (int jj = 0; jj < 2*N-1; jj++)
            for (int ii = 0; ii < N; ii++) {
                char value = rightDiagonalTable[ii][jj];
                if (value == 0) {
                    red = 0;
                    blue = 0;
                    continue;
                }
                
                if (value == 'R') {
                    red++;
                    blue = 0;
                } else if (value == 'B') {
                    blue++;
                    red = 0;
                } else {
                    red = 0; 
                    blue = 0;
                }
                
                if (red == K) 
                    redHasWin = true;
                if (blue == K)
                    blueHasWin = true;
            }
                
        string winner;
        if (redHasWin && blueHasWin)
            winner = "Both";
        else if (redHasWin)
            winner = "Red";
        else if (blueHasWin)
            winner = "Blue";
        else
            winner = "Neither";
        
        cout << "Case #" << i+1 << ": " << winner << endl;
    }

}