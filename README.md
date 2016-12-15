## Reversi game

### Realization
The game contains 6 components:

1. "game.c" with main method that controll interactions with users, runs game loop
and save results in a log file ("logfile.txt")
2. "board.c" that contains mehtods to print and update the game board.
3. "game_util.c" whith all necessary game related functions as function to make
a move or check if it's posiible for players to make moves.
4. "input.c" that implemets all functions necessary for interactions with user,
i.e. make prompt for user names, moves they want to make and validate their input.
5. "logging.c" with methods for logging the game events in a log file. When game
starts the programm save info about players (name and color of pieces) and time
when the game started. Program also saves all players' moves with specification 
if the move was correct or wrong and time when the move was made. When the game
is over, the program save the result and time in the log file. If the log file
was deleted or it's a first time the program was started, the program creates a
log file. 
6. "ai_util.c" with realization of functions necessary for ai to find a best
move. There are two different methods that were used: heuristic function and
minimax algorithm. As default the ai uses minimax algorithm but it's also 
possible two change default settings by following instructions in the "ai_util.c".

### Game for 2 players or player vs. computer.
A user can choose if (s)he wants to play with another person or with computer. 
This extention was made to satisfy requirements for “independence” and was 
approved by associate professor Kjetil Raaen. 
