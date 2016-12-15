#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "ai_util.h"

void getAllPossibleMoves(Point* moves, int* numberOfMoves, 
												Board* board, bool blackMove);
												
Result minimax(Board board, bool player, int depth);

void getMoveWithBestCoefficient(Board board, Point* move);

void getComputerMove(Board* board, Point *move) {
	Point possibleMoves[BOARD_SIZE * BOARD_SIZE - NUMBER_OF_FIELDS_AT_START];
	int numberOfPossibleMoves = 0;
	
	getAllPossibleMoves(possibleMoves, &numberOfPossibleMoves, board, false);
	
	// Program uses minimax algorithm to choose the best move for computer.
	// It's also possible to use heuristic function to get the best move
	// based on sum of scores computer will get for a move pluss value of a
	// field that will be occupied by the move. To change the way of choosing 
	// best move simply uncomment next line and comment out two folling lines.
	
	// getMoveWithBestCoefficient(*board, move);
	Result result = minimax(*board, false, 3);
	*move = result.move;
}

void getAllPossibleMoves(Point* moves, int* numberOfMoves, 
												Board* board, bool blackMove) {
	
	Field piece = blackMove ? BLACK : WHITE;
	int numberOfPossibleMoves = 0;
	
	Point emptyFields[BOARD_SIZE * BOARD_SIZE - NUMBER_OF_FIELDS_AT_START];
	int numberOfEmptyFields = 0;
	
	// check if there are no empty fields
	for(int y = 0; y < BOARD_SIZE; y++) {
		for(int x = 0; x < BOARD_SIZE; x++) {
			if(board->fields[x][y] == EMPTY) {
				emptyFields[numberOfEmptyFields].x = x;
				emptyFields[numberOfEmptyFields++].y = y;
			} 
		}
	}
	
	if(numberOfEmptyFields == 0) {
		*numberOfMoves = 0;
		return;
	}
	
	// get all possible moves
	for(int i = 0; i < numberOfEmptyFields; i++) {
		Point neighborsWithOtherColor[8];
		int numberOfNeighbors = 0;
		
		getNeighborsWithOtherColor(neighborsWithOtherColor, &numberOfNeighbors, 
						emptyFields[i], blackMove, board);
											
		for(int n = 0; n < numberOfNeighbors; n++) {
			
			Point validLine[BOARD_SIZE - 1];
			int lineLength = 0;
		
			getValidLine(validLine, neighborsWithOtherColor[n], board, 
						&lineLength, emptyFields[i], piece);
													
			if(lineLength != 0) moves[numberOfPossibleMoves++] = emptyFields[i];
		}
	}
	
	// remove duplicates from all possible moves
	if(numberOfPossibleMoves != 0) {
		int i, j, numberOfMovesWithouDuplicates = 1;

		for(i = 1; i < numberOfPossibleMoves; i++){

		   	for(j = 0; j < numberOfMovesWithouDuplicates ; j++) {

				if(moves[i].x == moves[j].x && moves[i].y == moves[j].y) break;
			  
		   	}

			if (j == numberOfMovesWithouDuplicates) 
				moves[numberOfMovesWithouDuplicates++] = moves[i];
		}
	
		*numberOfMoves = numberOfMovesWithouDuplicates;
	} else {
		*numberOfMoves = 0;
	}
}

int getScoreForMove(Board board, Point move, bool blackMove) {
	
	makeMove(&board, blackMove, move);
	
	int score = 0;
	
	for(int y = 0; y < BOARD_SIZE; y++) {
		for(int x = 0; x < BOARD_SIZE; x++) {
			if((blackMove && board.fields[x][y] == BLACK) || 
				(!blackMove && board.fields[x][y] == WHITE)) {
				score++;
			}
		}
	}
	
	return score;
}

int getScoreForPlayer(Board board, bool blackMove) {
	
	int score = 0;
	
	for(int y = 0; y < BOARD_SIZE; y++) {
		for(int x = 0; x < BOARD_SIZE; x++) {
			if((blackMove && board.fields[x][y] == BLACK) || 
				(!blackMove && board.fields[x][y] == WHITE)) {
				score++;
			}
		}
	}
	
	return score;
}

int getMoveValue(Point move) {
	int values[8][8] = {
		{20, -3, 11, 8, 8, 11, -3, 20},
		{-3, -7, -4, 1, 1, -4, -7, -3},
		{11, -4, 2, 2, 2, 2, -4, 11},
    	{8, 1, 2, -3, -3, 2, 1, 8},
    	{8, 1, 2, -3, -3, 2, 1, 8},
    	{11, -4, 2, 2, 2, 2, -4, 11},
    	{-3, -7, -4, 1, 1, -4, -7, -3},
    	{20, -3, 11, 8, 8, 11, -3, 20},
	};
	
	return values[move.y][move.x];
}

// 1. Get all possible moves for computer
// 2. Make all possible moves and get all possible moves for player
// 3. For each possible player's move get all computer's move
// 4. Find the worst move computer can make 
// 5. Save player's move that trigged this worst computer move
// 6. Through all player's moves that trig worst computer moves find the one
// that will give most score to computer. 
Result minimax(Board board, bool player, int depth) {
	Point possibleMoves[BOARD_SIZE * BOARD_SIZE - NUMBER_OF_FIELDS_AT_START];
	int numberOfPossibleMoves = 0;
	getAllPossibleMoves(possibleMoves, &numberOfPossibleMoves, &board, player);
	
	int bestScore = player ? INT_MAX : INT_MIN;
	int currentScore = 0;
	Point bestMove = { -1, -1 };
	
	// it's impossible to make a move or the program reached the limit of number
	// of moves in the game to check
	if(numberOfPossibleMoves == 0 || depth == 0) {
		bestScore = getScoreForPlayer(board, player);
	} else { // computer/player can make move(s)
		for(int i = 0; i < numberOfPossibleMoves; i++) {
			Board newBoard = board; // create a new board
									// and make a move on it
			makeMove(&newBoard, player, possibleMoves[i]); 
			
			if(!player) { // computer looks for max moves
				currentScore = minimax(newBoard, player, depth - 1).score;
				if(currentScore > bestScore) {
					bestScore = currentScore;
					bestMove = possibleMoves[i];
				}
			} else { // player looks for min moves
				currentScore = minimax(newBoard, !player, depth - 1).score;
				if(currentScore < bestScore) {
					bestScore = currentScore;
					bestMove = possibleMoves[i];
				}
			}
		}
	}
	
	Result result;
	result.score = bestScore;
	result.move = bestMove;
	return result;
}

void getMoveWithBestCoefficient(Board board, Point* move) {
	Point possibleMoves[BOARD_SIZE * BOARD_SIZE - NUMBER_OF_FIELDS_AT_START];
	int numberOfPossibleMoves = 0, bestMoveCoefficient = 0;
	Point bestMove = { -1, -1 };
	
	getAllPossibleMoves(possibleMoves, &numberOfPossibleMoves, &board, false);
	// program can come here only if computer can make a move (it was checked in
	// main function in game.c) so it's safe to initialize best move, score and
	// move value using first element of possibleMoves array. 
	bestMove = possibleMoves[0];
	int score = getScoreForMove(board, possibleMoves[0], false);
	int moveValue = getMoveValue(possibleMoves[0]);
	bestMoveCoefficient = score + moveValue;
	
	// Check all moves if any other exept the first one to find the one 
	// with the highest coefficient
	for(int i = 0; i < numberOfPossibleMoves; i++) {
		score = getScoreForMove(board, possibleMoves[i], false);
		moveValue = getMoveValue(possibleMoves[i]);
		int moveCoefficient = score + moveValue;
		if(moveCoefficient > bestMoveCoefficient) {
			bestMoveCoefficient = moveCoefficient;
			bestMove = possibleMoves[i];
		}
	}
	
	*move = bestMove;
}
