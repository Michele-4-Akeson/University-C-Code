#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>





void showBoard(int board[8][8]);
void makeMove (char* input, int board[8][8]);
bool isValidMove (char* input, int board[8][8]);

int main () {
	printf("Welcome to Terminal Chess!\n");
	printf("Initializing Board...\n")	;
	int board [8][8] = { {5, 4, 3, 2, 1, 3, 4, 5}
			   , {6, 6, 6, 6, 6, 6, 6, 6}
			   , {0, 0, 0, 0, 0, 0, 0, 0}
			   , {0, 0, 0, 0, 0, 0, 0, 0}
			   , {0, 0, 0, 0, 0, 0, 0, 0} 
			   , {0, 0, 0, 0, 0, 0, 0, 0}
			   , {6, 6, 6, 6, 6, 6, 6, 6}
			   , {5, 4, 3, 2, 1, 3, 4, 5} } ;
  char buf[100];
  bool whitesMove = true;
  printf("Board Initialized!\n") ;
  printf("Enter `q` to quit at any time.\n");
  printf("Moves are entered as co-ordinate pairs, such as \"13-33\" \n");


  do {
    bool flag = false; 
    showBoard(board);
    do { // run do if move is not valid and is not q/Q
        
	if (flag) {
		printf("Move Invalid! Try again! ");
	}
    	if (whitesMove) {
      		printf("White to move.\n");
    	} else {
      		printf("Black to move.\n");
    	}
    	printf("♔ >> ");
	scanf("%s", buf);
	flag = true;

	//printf("1 = True, 0 = False : Outcome: %d", isValidMove(buf, board));
       
    } while ((buf[0] != 'q' && buf[0] != 'Q') && !isValidMove(buf, board));
    if (buf[0] != 'q' && buf[0] != 'Q') {
      makeMove(buf, board);
      whitesMove = !whitesMove;

    }
    
    
  } while (buf[0] != 'q' && buf[0] != 'Q') ;
    
	printf("Terminating...\n") ;
}

bool isValidMove (char* input, int board[8][8]) {
	int start_y = input[0] - 48;
	int start_x = input[1] - 48;
	int end_y = input[3] - 48;
	int end_x = input[4] - 48;

	// For the testing logic
	int x1 = start_x;
	int x2 = end_x;
	int y1 = start_y;
	int y2 = end_y;

	
	// out of bounds check
	if (start_x > 7 || start_x < 0) {
		return false;
	} else if (start_y > 7 || start_y < 0) {
		return false;
	} else if (end_x > 7 || end_x < 0) {
		return false;
	} else if (end_y > 7 || end_y < 0) {
		return false;
	}

	//printf("\nCoordinates on Board");
	
	// piece move checks 
	int xcheck = start_x;
	int ycheck = start_y;
	int piecesInWay = 0;

	// retrieves piece at (x1, y1) => piece to be moved
	switch (board[start_x][start_y]) {
		case 0: // moving a blank spot is never valid
		  // printf("Blank");
			return false;
		case 1: // King
		  // printf("King");
		  if (abs(start_x - end_x) <= 1 && abs(start_y-end_y) <= 1) {
			return true;
		  }

		  break;
		  
		case 2: // Queen
		  //printf("Queen");
			while (true) {
				xcheck += (start_x > end_x)? -1 : 1;
				ycheck += (start_y > end_y)? -1 : 1;
				if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
					break;
				}
				if (board[xcheck][ycheck] != 0) {
					piecesInWay += 1;
				} 
				if (piecesInWay == 2) {
					break;
				}
				if (xcheck == end_x && ycheck == end_y) {
					return true;
				}
			}

			xcheck = start_x;
			ycheck = start_y;
			piecesInWay = 0;
			// code block is also used for Rook
			while (true) {
				//printf("Calculating Rook Movement at %d, %d\n", ycheck, xcheck);
				if (start_y == end_y) {
					//printf("Horzontal!\n");
					xcheck += (start_x > end_x)? -1 : 1;
				} else if (start_x == end_x) {
					//printf("Vertical!\n");
					ycheck += (start_y > end_y)? -1 : 1;
				} 
				//printf("Now checking %d, %d\n", ycheck, xcheck);
			
				if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
					//printf("Out of bounds!\n");
					break;
				}
				if (board[xcheck][ycheck] != 0) {
					//printf("Hit Piece: %d\n", board[xcheck][ycheck]);
					piecesInWay += 1;
				} 	
				if (piecesInWay == 2) {
					//printf("Hit Second Piece: %d\n", board[xcheck][ycheck]);
					break;
				}	
				if (xcheck == end_x && ycheck == end_y) {
					return true;
				}
			}	
			break;
	        	       
			
		case 3: // Bishop
		  // printf("Bishop");
		  while (true) {
			xcheck += (start_x > end_x)? -1 : 1;
			ycheck += (start_y > end_y)? -1 : 1;
		 	if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
				break;
			}
			if (board[xcheck][ycheck] != 0) {
				piecesInWay += 1;
			} 
			if (piecesInWay == 2) {
				break;
			}
			if (xcheck == x2 && ycheck == y2) {
				return true;
			}
		  }
			break;
		case 4 : // Knight
		  // printf("Knight");
		  if (abs(x1 - x2) == 1) {
			if (abs(y2 - y1) == 2) {
				return true;
			}
		} else if (abs(x1 - x2) == 2) {
			if (abs(y2 - y1) == 1) {
				return true;
			}
		}
			break;
		case 5 : // Rook
		  // printf("Rook");
		  	while (true) {
			  //	printf("Calculating Rook Movement at %d, %d\n", ycheck, xcheck);
				if (start_y == end_y) {
				  //	printf("Horzontal!\n");
					xcheck += (start_x > end_x)? -1 : 1;
				} else if (start_x == end_x) {
				  //	printf("Vertical!\n");
					ycheck += (start_y > end_y)? -1 : 1;
				} 
				//	printf("Now checking %d, %d\n", ycheck, xcheck);
			
				if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
				  //printf("Out of bounds!\n");
					break;
				}
				if (board[xcheck][ycheck] != 0) {
				  // printf("Hit Piece: %d\n", board[xcheck][ycheck]);
					piecesInWay += 1;
				} 	
				if (piecesInWay == 2) {
				  //	printf("Hit Second Piece: %d\n", board[xcheck][ycheck]);
					break;
				}	
				if (xcheck == end_x && ycheck == end_y) {
					return true;
				}
			}
			break;
		case 6 : // Pawn
		  //printf(" Pawn ");
		  //printf("Pawn Selected\n");
		  //printf("Moving in column %d \n", y1);
		  //printf("y1-y2=%d\n", x1-x2);
		if (x1 - x2 == 1 && y1 == y2) { // forward one
		  //	printf("Detected forward move by 1\n");
			if (board[x2][y2] == 0) {
				return true;
			}
		} else if (x1 - x2 == 2 && y1 == y2) { // forward two
//			printf("Detected forward move by 2\n");
			if (board[x2][y2] == 0 && board[x2+1][y2] == 0 && x1 == 6) {
				return true;
			}
		} else if (abs(y1 - y2) == 1 && x1-x2 == 1) { // capture left or right
			//printf("Detected Capture\n");
			if (board[x2][y2] != 0) {
				return true;
			}
		}
		  break;
	}
	return false;
}


void makeMove (char* input, int board[8][8]) {
	int start_y = input[0] - 48;
	int start_x = input[1] - 48;
	int end_y = input[3] - 48;
	int end_x = input[4] - 48;
	
	board[end_x][end_y] = board[start_x][start_y];
	board[start_x][start_y] = 0;
}

/*
 ♔ ♕ ♖ ♗ ♘ ♙

├ ┤ ┬ ┴
 
─ │ ┼
 
 might need these...
 
 ╟ ╢ ╧ ╤
 
*/
void showBoard (int board[8][8]) {
        printf("\n");
        printf("   0 1 2 3 4 5 6 7\n");
	printf("  ╔═╤═╤═╤═╤═╤═╤═╤═╗\n");
       
	for (int i = 0; i < 8; i++) {
	        printf("%d ", i);
		printf("║");

		bool flag = true;
		for (int j = 0; j < 8; j++) {
		  if (!flag) {
				printf("│"); 
			}
			flag = false;
			
			if (board[i][j] == 0) {
				if ((i + j) % 2 == 0) {
				  // black square
					printf(" ");
				} else {
				  // white square
					printf("▒");
				}
			} else if (board[i][j] == 1) {
				printf("♔");
 			} else if (board[i][j] == 2) {
				printf("♕");
			} else if (board[i][j] == 3) {
				printf("♗");
			} else if (board[i][j] == 4) {
				printf("♘");
			} else if (board[i][j] == 5) {
				printf("♖");
			} else if (board[i][j] == 6) {
				printf("♙");
			}
		}
		
		printf("║\n") ; // prints board end
		if (i < 7) {
		  printf("  ╟─┼─┼─┼─┼─┼─┼─┼─╢\n") ; // prints grid
		}
	}
        
	printf("  ╚═╧═╧═╧═╧═╧═╧═╧═╝\n");
}
