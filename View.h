#pragma once
#include "stdafx.h"
#include <windows.h>
#include "EnumVariables.h"

class View
{
public:
    View();
    void DrawBoard(const Board_Struct& Current_Board_Struct);
    void PrintImportantMessage(const std::string& message);
    void PrintWannaPlayOrExitGameMessage(const std::string& message);
    int  NextMove(const Player& Current_Player);
    void ShowWinner(const Player& current_player);
    void ShowDrawStatus();
    void ShowScore(int First_Player_Score, int Second_Player_Score);
    void ClearImportantMessageIfExist();
    bool PlayOneMoreTimeFunction();
    void ClearMessagePlayerShouldMove();
    void SetBoardInfo(Board_Info Current_Board_Info);
    void DrawWikiBoardAndSectionHeaders(Game_Type Current_Game_Type);
    Game_Type PlayerSelectGameType();
    void DrawScoreHeadersGameWithComp();
    void CompThinkingAndMove();
private:
    void PrintShouldPlayerMove(Player Current_Player);
    int  GetCellNumberToMove();
    int  EnterTheDigit();
    void MoveCoursorToPosition(int x, int y);
    void ClearEnteredMovePosition(std::string cell_Move_Entered_Line);
    void ClearInputWannaPlayEnteredSymbols(std::string EnterenWannaPlayLine);
    void PrintMessage(const std::string& message, int X_Position, int Y_Position);

    HANDLE m_hStdOut;
    
    std::string m_Current_Important_Message;
    int m_Board_Size_To_Show;
    int m_Board_Side_To_Show;
    std::string m_NEW_Clear_Line;
    std::string m_NEW_Dash_Line;
    int m_X_Input_Select_Position;
    
    static const int m_X_start;
    static const int m_Y_start;
    static const int m_Y_Two_Lines_Down;
    static const int m_X_Size_Message_Area;
    static const int m_X_Size_Score_Line;
    static const int m_X_Position_Shift;
    static const int m_Number_Two_Important_Messages_Lines;

    static const std::string m_Score_Line;
    static const std::string m_First_Player;
    static const std::string m_Second_Player;
    static const std::string m_Comp_Player;
    static const std::string m_Your_Move_Line;
    static const std::string m_Dash_Line;
    static const std::string m_Clear_Line;

};



