#pragma once

#include <windows.h>
#include <string>

#include "EnumVariables.h"

class View
{
public:
    View();
    void DrawBoard( const Board_Struct& Current_Board_Struct );
    void PrintImportantMessage( const std::string& message );
    void PrintWannaPlayOrExitGameMessage( const std::string& message );
    int  NextMove( const Player& Current_Player );
    
    void ShowWinner( const Player& current_player );
    void ShowDrawStatus();
    void ShowScore( int first_player_score, int second_player_score );
    
    void ClearImportantMessageIfExist();
    bool PlayOneMoreTimeFunction();
    void ClearMessagePlayerShouldMove();
    
    void DrawWikiBoardAndSectionHeaders( Game_Type Current_Game_Type );
    Game_Type PlayerSelectGameType();
    void DrawScoreHeadersGameWithComp();
    void CompThinkingAndMove();

private:
    void PrintShouldPlayerMove( Player Current_Player );
    int  GetCellNumberToMove();
    int  EnterTheDigit();
    void MoveCoursorToPosition( int x, int y );
    void ClearEnteredMovePosition( const std::string cell_Move_Entered_Line );
    void ClearInputWannaPlayEnteredSymbols( std::string EnterenWannaPlayLine );
    void PrintMessage( const std::string& message, int X_Position, int Y_Position );

    char ConvertCellToChar( const Cell& cell );
    Cell ConvertCharToCell( const char cell_char );

    HANDLE m_hStdOut;
    
    std::string m_Current_Important_Message;
    int m_Board_Size_To_Show;
    int m_Board_Side_To_Show;
    std::string m_NEW_Clear_Line;
    std::string m_NEW_Dash_Line;
    int m_X_Input_Select_Position;
    
    const int m_X_start;
    const int m_Y_start;
    const int m_Y_Two_Lines_Down;
    const int m_X_Size_Message_Area;
    const int m_X_Size_Score_Line;
    int m_X_Position_Shift;
    const int m_Number_Two_Important_Messages_Lines;

    const std::string m_Score_Line;
    const std::string m_First_Player;
    const std::string m_Second_Player;
    const std::string m_Comp_Player;
    const std::string m_Your_Move_Line;
    const std::string m_Dash_Line;
    const std::string m_Clear_Line;
};



