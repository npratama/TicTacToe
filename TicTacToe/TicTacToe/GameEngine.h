#pragma once
class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	//method to trigger the whole scene start
	void Start();
	//initializion scene
	//consist of 'wellcome screen' and randomize who get to go first
	bool Init();
	//gameplay scene
	bool GamePlay();
	//scene after gameplay scene ends, just to stop the screen from closing
	bool End();
	  
	//method to check if there are winner 
	bool CheckWin(char field[3][3]);
	//method to check if there are no move can be made anymore 
	bool CheckDraw(char board[3][3]);
	//method to register player move to game field
	bool PlayerMove(int x, int y, char sign);
	//method to find 'winning move', check the method to see the details
	void FindWinningMove(char sign, int &row, int &col);
	//method to register AI move
	void AIMove();
	//method to render the game field
	void RenderBoard();

private:
	char player_avatar;
	char ai_avatar;
	bool is_player_turn;
	char game_field[3][3];

};

