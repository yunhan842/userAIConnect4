bool getUserAIInput(BoardValue** board, int ydim, int xdim, int *y, int *x, int currentPlayer)
{
    // Check if the current player can win
    for(int i = 0; i < xdim; i++){
        //for loop iterates through each column
        int row = findYValue(board, ydim, i);
        //smallest y value is found for each column
        if(row != -1){
            //hypothetical scenario is created to temporarily set the space to the value of the current player to see if it leads to a win
            board[row][i] = playerToValue[currentPlayer];
            if(hasWon(board, ydim, xdim, row, i, currentPlayer)){
                //if it leads to a win, *x and *y are updated and false is returned
                *x = i;
                *y = row;
                return false;
            }
            //if it doesnt lead to a win, the space is set back to blank
            board[row][i] = BLANK;
        }
    }
    // Check if we need to block
    //  We can greedily play the first blocking location since
    //  if they can win in multiple ways it does not matter which
    //  we choose.
    int opponentPlayer = (currentPlayer + 1) % 2;
    //variable to store the value of the opponent player is set using modulo
    for(int i = 0; i < xdim; i++){
        //same logic applies from previous case with just a few changes
        int row = findYValue(board, ydim, i);
        if(row != -1){
            board[row][i] = playerToValue[opponentPlayer];
            //hypothetical scenario is created to set the space equal to the opponent's value
            if(hasWon(board, ydim, xdim, row, i, opponentPlayer)){
                //if it leads to the opponent winning the game, the space is replaced by the current player's value to prevent the opponent from winning and everything else from the previous part still applies to here
                board[row][i] = playerToValue[currentPlayer];
                *x = i;
                *y = row;
                return false;
            }
            board[row][i] = BLANK;
        }
    }
    // Add any other logic for how to choose a location to play
    // if neither case above occurs

    //if neither one of the above cases happen, the user AI just chooses a random available space

    //will undergo development to play in an optimal way in the future!
    int* possible = new int[xdim];
    int numX = 0;
    bool error = true;
    for(int i = 0; i < xdim; i++){
        if(board[ydim-1][i] == BLANK){
            possible[numX++] = i;
        }
    }
    if(numX != 0){
        *x = possible[rand()%numX];
        *y = findYValue(board, ydim, *x);
        board[*y][*x] = playerToValue[currentPlayer];
        error = false;
    }
    delete [] possible;
    return error;
}