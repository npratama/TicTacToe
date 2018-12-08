#include "GameEngine.h"
#include <iostream>
#include <ctime>
#include <string>

GameEngine::GameEngine()
{
	this->player_avatar = 'X';
	this->ai_avatar = 'O';
	for (int i = 0;i < 3;i++)
		for (int k = 0;k < 3;k++)
			this->game_field[i][k] = ' ';
	/*
	Game Field Map
				[0,0] | [1,0] | [2,0]
				[0,1] | [1,1] | [2,1]
				[0,2] | [1,2] | [2,2]
	*/
}

GameEngine::~GameEngine()
{
}

void GameEngine::RenderBoard() {
	std::cout << "\n";
	std::cout << "\tPlaying Field\t\t Placement Guidance Map\n\n";
	std::cout << "\t    |   |  \t\t      |     |      \n";
	std::cout << "\t  " << game_field[0][0] << " | " << game_field[1][0] << " | " << game_field[2][0] << " \t\t [0,0]|[1,0]|[2,0] \n";
	std::cout << "\t____|___|____\t\t______|_____|______\n";
	std::cout << "\t    |   |  \t\t      |     |      \n";
	std::cout << "\t  " << game_field[0][1] << " | " << game_field[1][1] << " | " << game_field[2][1] << " \t\t [0,1]|[1,1]|[2,1]\n";
	std::cout << "\t____|___|____\t\t______|_____|______\n";
	std::cout << "\t    |   |  \t\t      |     |   \n";
	std::cout << "\t  " << game_field[0][2] << " | " << game_field[1][2] << " | " << game_field[2][2] << " \t\t [0,2]|[1,2]|[2,2]\n";
	std::cout << "\t    |   |  \t\t      |     |   \n";


}

bool GameEngine::CheckWin(char field[3][3])
{
	if (
		//left vertical win
		(field[0][0] == field[0][1]) && (field[0][1] == field[0][2]) && (field[0][0] == field[0][2]) && (field[0][0] != ' ') && (field[0][1] != ' ') && (field[0][2] != ' ') ||
		//middle vertical win
		(field[1][0] == field[1][1]) && (field[1][1] == field[1][2]) && (field[1][0] == field[1][2]) && (field[1][0] != ' ') && (field[1][1] != ' ') && (field[1][2] != ' ') ||
		//right vertical win
		(field[2][0] == field[2][1]) && (field[2][1] == field[2][2]) && (field[2][0] == field[2][2]) && (field[2][0] != ' ') && (field[2][1] != ' ') && (field[2][2] != ' ') ||
		//top vertical win
		(field[0][0] == field[1][0]) && (field[1][0] == field[2][0]) && (field[0][0] == field[2][0]) && (field[0][0] != ' ') && (field[0][0] != ' ') && (field[0][0] != ' ') ||
		//middle vertical win
		(field[0][1] == field[1][1]) && (field[1][1] == field[2][1]) && (field[0][1] == field[2][1]) && (field[0][1] != ' ') && (field[1][1] != ' ') && (field[2][1] != ' ') ||
		//bottom vertical win
		(field[0][2] == field[2][1]) && (field[1][2] == field[2][2]) && (field[0][2] == field[2][2]) && (field[0][2] != ' ') && (field[1][2] != ' ') && (field[2][2] != ' ') ||
		// Diagonal \ win
		(field[0][0] == field[1][1]) && (field[1][1] == field[2][2]) && (field[0][0] == field[2][2]) && (field[0][0] != ' ') && (field[1][1] != ' ') && (field[2][2] != ' ') ||
		// Diagonal / win
		(field[0][2] == field[1][1]) && (field[1][1] == field[2][0]) && (field[0][2] == field[2][0]) && (field[0][2] != ' ') && (field[1][1] != ' ') && (field[2][0] != ' ')
		)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool GameEngine::CheckDraw(char board[3][3])
{
	if ((board[0][0] != ' ') && (board[0][1] != ' ') && (board[0][2] != ' ') && (board[1][0] != ' ') && (board[1][1] != ' ') && (board[1][2] != ' ') && (board[2][0] != ' ') && (board[2][1] != ' ') && (board[2][2] != ' '))
	{
		return true;
	}
	else
		return false;
}

void GameEngine::FindWinningMove(char avatar, int &row, int &col) {
	//Winning move are concluded when there are 2 avatar (x or o) placed side by side, OR horizonally, OR vertically, OR diagonally AND it's on their turn to move
		/*
		example :
		horizontal winning move
			x	|	x	| <empty>  <--- winning move for X avatar
			o	|<empty>| <empty>
			o	|<empty>| <empty>
		*/

	//define how many avatar (x or o) present on the loop
	int avatar_count;
	//define empty collumn within the loop
	int empty_col;
	//define empty row within the row
	int empty_row;


	//find possible winning move horizontally
	
	for (int i = 0;i < 3;i++)
	{
		//reset the value of the avatar_count
		avatar_count = 0;
		//reset the value of empty_count
		empty_col = -1;
		//search to right
		for (int k = 0;k < 3;k++)
		{
			// If the a avatar is occupying the cell, add to avatar_count
			if (game_field[i][k] == avatar)
				avatar_count++;
			// If specified cell are unoccupied, mark the column as empty
			else if (game_field[i][k] == ' ')
				empty_col = k;
			//if two side by side same avatar and one empty space beside found horizontally, means there are possible winning move
			/*
	 		     a_cnt=1; a_cnt=2; empty_col=1
				   i=0		i=0		i=0
				   k=0		k=1		k=2
					|		|		|
					v		V		V
					o |		o	| <empty>
					x | <empty> | <empty>
					x | <empty> | <empty>
			*/
			if (avatar_count == 2 && empty_col != -1)
			{
				//fill the x axis
				row = i;
				//fill the y axis
				col = empty_col;
				return;
			}
		}
	}

	//find possibility of finding winning move vertically
	for (int k = 0; k < 3; k++)
	{
		//reset the value of the avatar_count
		avatar_count = 0;
		//reset the value of empty_count
		empty_row = -1;

		//search from index 0 to 3 vertically
		for (int i = 0; i < 3; i++)
		{
			// If the a avatar is occupying the cell, add to avatar_count
			if (game_field[i][k] == avatar)
				avatar_count++;
			// If specified cell are unoccupied, mark the row as empty
			else if (game_field[i][k] == ' ')
				empty_row = i;
		}
		//if two side by side same avatar and one empty space beside found vertically, means there are possible winning move
		if (avatar_count == 2 && empty_row != -1)
		{
			//fill the x axis
			row = empty_row;
			//fill the y axis
			col = k;
			return;
		}
	}

	// search possipility to win diagonally from top left to bottom right	
	/*
		[0,0] |		o	| <empty>
		x	  | [1,1]   | <empty>
		x	  | <empty> | [2,2]
	*/
	avatar_count = 0;
	empty_row = -1;
	empty_col = -1;
	// Loop through the diagonal line
	for (int i = 0; i < 3; i++)
	{
		// If the a avatar is occupying the cell, add to avatar_count
		if (game_field[i][i] == avatar)
			avatar_count++;
		// If specified cell are unoccupied, mark the cell as empty
		else if (game_field[i][i] == ' ')
			empty_row = empty_col = i;
	}
	//if two side by side same avatar and one empty space beside found diagonally, means there are possible winning move
	if (avatar_count == 2 && empty_row != -1 && empty_col != -1)
	{
		row = empty_row;
		col = empty_col;
		return;
	}
	// search possipility to win diagonally from top right to bottom left	
	avatar_count = 0;
	empty_row = -1;
	empty_col = -1;
	// Loop through the diagonal
	for (int i = 0; i < 3; i++)
	{
		// If the a avatar is occupying the cell, add to avatar_count
		if (game_field[i][2 - i] == avatar)
			avatar_count++;
		// If specified cell are unoccupied, mark the cell as empty
		else if (game_field[i][2 - i] == ' ')
		{
			empty_row = i;
			empty_col = 2 - i;
		}
	}
	//if two side by side same avatar and one empty space beside found diagonally, means there are possible winning move
	if (avatar_count == 2 && empty_row != -1 && empty_col != -1)
	{
		row = empty_row;
		col = empty_col;
		return;
	}
}

bool GameEngine::PlayerMove(int x, int y, char avatar)
{
	//convert char to in, 0 ASCII code is 48
	x = x - '0'; y = y - '0';
	if (game_field[x][y] == ' ' || game_field[x][y] == '1' || game_field[x][y] == '2' || game_field[x][y] == '3' || game_field[x][y] == '4' || game_field[x][y] == '5' || game_field[x][y] == '6' || game_field[x][y] == '7' || game_field[x][y] == '8' || game_field[x][y] == '9')
	{
		//put the move to the game field
		game_field[x][y] = avatar;
		return true;
	}
	else
	{
		std::cout << "invalid move\n";
		return false;
	}

}

void GameEngine::AIMove()
{
	// Check if AI can win in this move
	//set variable to store x and y
	int x = -1, y = -1;
	//search possibility to find find
	FindWinningMove(ai_avatar, x, y);
	// if AI can win, play the winning move
	if (x != -1 && y != -1)
	{
		game_field[x][y] = ai_avatar;
		return;
	}
	x = y = -1;
	// see if player can win next move and block
	// if possible
	FindWinningMove(player_avatar, x, y);
	if (x != -1 && y != -1)
	{
		game_field[x][y] = ai_avatar;
		return;
	}
	// check if the centre can be played
	if (game_field[1][1] == ' ')
	{
		game_field[1][1] = ai_avatar;
		return;
	}
	// define 'corner' positions
	/*
			   corner 			corner
				 |				  |
				 v				  V
				[0,0] | [1,0] | [2,0]
				[0,1] | [1,1] | [2,1] 
				[0,2] | [1,2] | [2,2]
				  ^				  ^
				  |				  |
				 corner			corner
	*/
	int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
	// If any one or more corners are blank
	if (game_field[0][0] == ' ' || game_field[0][2] == ' ' || game_field[2][0] == ' ' || game_field[2][2] == ' ')
	{
		// randomly select corner
		while (1)
		{
			int corner = rand() % 4;
			x = corners[corner][0];
			y = corners[corner][1];
			if (game_field[x][y] == ' ')
			{
				game_field[x][y] = ai_avatar;
				return;
			}
		}
	}
	// define 'edge' positions
	/*
						 edge
						  |
						  v
				[0,0] | [1,0] | [2,0]
		edge->  [0,1] | [1,1] | [2,1] <- edge
				[0,2] | [1,2] | [2,2]
						  ^
						  |
						 edge
	*/
	int edges[4][2] = { {0, 1}, {1, 0}, {1, 2}, {2, 1} };
	// if any one or more edges are blank
	if (game_field[0][1] == ' ' || game_field[1][0] == ' ' || game_field[1][2] == ' ' || game_field[2][1] == ' ')
	{
		// randomly select edge 
		while (1)
		{
			int edge = rand() % 4;
			x = edges[edge][0];
			y = edges[edge][1];
			if (game_field[x][y] == ' ')
			{
				game_field[x][y] = ai_avatar;
				return;
			}
		}
	}

}

bool GameEngine::Init()
{
	//seed rng
	srand(time(0));
	//generate rng out of 1 or 2, toss the coin
	int randomval = rand() % 2 == 0;
	/*if random val is 0 then player's go first*/
	std::cout << "Your avatar : X \n";
	std::cout << "AI's avatar : O \n";

	std::cout << "Toss the coin \n";
	if (randomval == 0)
	{
		this->is_player_turn = false;
		std::cout << "Result : AI's Turn \n";
	}
	else
	//if random val is 1 then AI go first
	{
		this->is_player_turn = true;
		std::cout << "Result : Player's Turn \n";

	}
	//send signal that this scene done
	return true;
}

bool GameEngine::GamePlay() {
	int k = 0;
	for (;;)
	{
		k++;
		std::cout << "> Turn number #" << k << "\n";
		//draw the playing field
		RenderBoard();
		//toggle turn
		if (is_player_turn)
		{
			char move_x, move_y;
			std::cout << "Your Turn\n";
			std::cout << "Insert X index :";std::cin >> move_x;
			std::cout << "Insert Y index :";std::cin >> move_y;
			//do player move
			if (PlayerMove(move_x, move_y, player_avatar))
			{
				//if the move is valid, then toggle the turn
				is_player_turn = false;
			}			
		}
		//toggle turn
		if (!is_player_turn)
		{
			//tell the AI to move
			AIMove();
			//if the move is valid, then toggle the turn
			is_player_turn = true;
		}


		if (CheckWin(game_field))
		{
			std::cout << "Game Over!\n";
			//send signal that this scene not done
			return true;
		}
		else
		//check if the game are stalled beacause all fields are occupied
		if (CheckDraw(game_field))
		{
			std::cout << "Its a tie\n";
			//send signal that this scene not done
			return true;
		}
		
	}
	//send signal that this scene done
	return false;
}

void GameEngine::Start() 
{
	//init scene will return true to signal its done
	if(this->Init())
		//GamePlay scene will return true to signal its done
		if(this->GamePlay())
			//End scene will return true to signal its done
			if(this->End());
}

bool GameEngine::End()
{
	char a;
	std::cin >> a;
	return true;
}