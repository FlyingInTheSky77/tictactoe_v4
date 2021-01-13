#include "View.h"

const std::string View::m_Score_Line = "Game score:";
const std::string View::m_First_Player = "First player";
const std::string View::m_Second_Player = "Second player";
const std::string View::m_Comp_Player = "Computer";
const std::string View::m_Your_Move_Line = " - your move: ";

const int View::m_X_start = 5;
const int View::m_Y_start = 2;
const int View::m_Y_Two_Lines_Down = m_Y_start;
const int View::m_X_Size_Message_Area = 50;
const int View::m_Number_Two_Important_Messages_Lines = 6;

const int View::m_X_Size_Score_Line = m_Score_Line.length();
const int View::m_X_Position_Shift = (m_Second_Player + m_Your_Move_Line).length();

const std::string View::m_Dash_Line = std::string(m_X_Size_Message_Area, '-');
const std::string View::m_Clear_Line = std::string(m_X_Size_Message_Area + 1, ' ');

View::View():
    m_Board_Size_To_Show(0),
    m_Board_Side_To_Show(0)
{ 
    m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void View::DrawBoard(const Board_Struct& Current_Board_Struct) {
    int Current_Y_Position = m_Y_start + m_Y_Two_Lines_Down;
    MoveCoursorToPosition(m_X_start+ m_X_Size_Message_Area/2, Current_Y_Position);
    for (int i = 0; i < m_Board_Size_To_Show; ++i) {
        std::cout << Current_Board_Struct.Cells_Char[i] << "   ";
        if ((i + 1) % m_Board_Side_To_Show == 0) {
            Current_Y_Position++;
            MoveCoursorToPosition(m_X_start+ m_X_Size_Message_Area/2, Current_Y_Position);
        }
    }
}

void View::SetBoardInfo(Board_Info Current_Board_Info) {
    m_Board_Size_To_Show = Current_Board_Info.size;
    m_Board_Side_To_Show = Current_Board_Info.side;

}

void View::ShowScore(int First_Player_Score, int Second_Player_Score) {
    MoveCoursorToPosition(m_X_Size_Message_Area + m_First_Player.length() / 2, 3*m_Y_start);
    std::cout << First_Player_Score;
    MoveCoursorToPosition(m_X_Size_Message_Area + static_cast<int>(m_First_Player.length() * 2.5) - 1, 3*m_Y_start);
    std::cout << Second_Player_Score;
}

void View::DrawWikiBoardAndSectionHeaders(Game_Type Current_Game_Type) {
    MoveCoursorToPosition(m_X_start, m_Y_start);
    std::cout << "Cell numbers:";

    MoveCoursorToPosition(m_X_start + m_X_Size_Message_Area/2, m_Y_start);
    std::cout << "Game board:";
    
    int Y_Go_To_Next_Line = m_Y_start+ m_Y_Two_Lines_Down;
    //MoveCoursorToPosition(x, y);
    MoveCoursorToPosition(m_X_start, Y_Go_To_Next_Line);

    for (int i = 0; i < m_Board_Size_To_Show; ++i) {
        std::cout << i << "   ";
        if ((i + 1) % m_Board_Side_To_Show == 0) {
            Y_Go_To_Next_Line++;
            MoveCoursorToPosition(m_X_start, Y_Go_To_Next_Line);
        }
    }
    MoveCoursorToPosition(m_X_start + (m_First_Player.length() / 2) + m_X_Size_Message_Area, m_Y_start);
    std::cout << m_Score_Line;
    //if (Current_Game_Type == Game_Type::TwoPlayersOnOneKeyboard) {
        MoveCoursorToPosition(m_X_Size_Message_Area, m_Y_start + m_Y_Two_Lines_Down);
        std::cout << m_First_Player;
        MoveCoursorToPosition(m_X_Size_Message_Area + static_cast<int>(4.5 * m_X_start), m_Y_start + m_Y_Two_Lines_Down);
        std::cout << m_Second_Player;
    //}
    //else {
    //    MoveCoursorToPosition(m_X_Size_Message_Area, m_Y_start + m_Y_Two_Lines_Down);
    //    std::cout << m_First_Player<<"( You )";
    //    MoveCoursorToPosition(m_X_Size_Message_Area + static_cast<int>(4.5 * m_X_start), m_Y_start + m_Y_Two_Lines_Down);
    //    std::cout << m_Second_Player<<"( "<< m_Comp_Player<<" )";
    //}
}

void View::DrawScoreHeadersGameWithComp() {
    MoveCoursorToPosition(m_X_Size_Message_Area, m_Y_start + m_Y_Two_Lines_Down);
    std::cout << m_First_Player << " (You)";
    MoveCoursorToPosition(m_X_Size_Message_Area + static_cast<int>(4.5 * m_X_start), m_Y_start + m_Y_Two_Lines_Down);
    std::cout << m_Second_Player << " (" << m_Comp_Player << ")";
}


void View::MoveCoursorToPosition(int x, int y) {
    COORD dwCursorPosition;
    dwCursorPosition.Y = y;
    dwCursorPosition.X = x;
    SetConsoleCursorPosition(m_hStdOut, dwCursorPosition);
}

int View::EnterTheDigit() {
    std::string Cell_Move_Entered_Line;
    MoveCoursorToPosition(m_X_start + m_X_Position_Shift, m_Y_start+ static_cast<int>(4.5 * m_Y_Two_Lines_Down));
    getline(std::cin, Cell_Move_Entered_Line, '\n');
    ClearEnteredMovePosition(Cell_Move_Entered_Line);
    int number;
    if (Cell_Move_Entered_Line == "0") {
        number = 0;
        return number;
    }
    else if (!(number = atoi(Cell_Move_Entered_Line.c_str()))) {
        throw("you entered not number");
    }
    else if ((number > 8) || (number < 0)) {
        throw("you should enter one digit from 0 to 8");
    }
    else {
        return number;
    }
}

int View::GetCellNumberToMove()
{
    bool Move_Done = false;
    int number;
    do {
        try {

            number = EnterTheDigit();
            ClearImportantMessageIfExist();
            Move_Done = true;

        }
        catch (const char* message) {
            ClearImportantMessageIfExist();
            PrintImportantMessage(message);
        }
    } while (!Move_Done);
    return number;
}

void View::PrintShouldPlayerMove(Player Current_Player)
{
    MoveCoursorToPosition(m_X_start, m_Y_start + static_cast<int>(4.5 * m_Y_Two_Lines_Down));
    if (Current_Player == Player::first) {
        std::cout << m_First_Player << m_Your_Move_Line;
    }
    else if (Current_Player == Player::second) {
        std::cout << m_Second_Player << m_Your_Move_Line;
    }
}

void View::CompThinkingAndMove() {
    
    ClearMessagePlayerShouldMove();
    MoveCoursorToPosition(m_X_start, m_Y_start + static_cast<int>(4.5 * m_Y_Two_Lines_Down));
    std::cout << "Computer thinking ...";
    Sleep(2000);
}

void View::ClearMessagePlayerShouldMove()
{
    MoveCoursorToPosition(m_X_start, m_Y_start + static_cast<int>(4.5 * m_Y_Two_Lines_Down));
    std::string EmptyLine((m_First_Player + m_Your_Move_Line).length(), ' ');
    std::cout << EmptyLine;
}

void View::ClearEnteredMovePosition(std::string cell_Move_Entered_Line) {
    MoveCoursorToPosition(m_X_start + m_X_Position_Shift, m_Y_start + static_cast<int>(4.5 * m_Y_Two_Lines_Down));
    int Size_Move_Entered_Line = cell_Move_Entered_Line.length();
    for (int i = 0; i < Size_Move_Entered_Line; ++i) {
        std::cout << ' ';
    }
}

int View::NextMove(const Player& Current_Player) {
    PrintShouldPlayerMove(Current_Player);
    return GetCellNumberToMove();
}

void View::ShowWinner(const Player& current_player) {
    ClearMessagePlayerShouldMove();
    if (current_player == Player::first) {
        PrintImportantMessage("First player win! This game is over.");
    }
    else {
        PrintImportantMessage("Second player win! This game is over.");
    }
}

void View::ShowDrawStatus() {
    ClearMessagePlayerShouldMove();
    PrintImportantMessage("It's draw! This Game over.");
}

void View::PrintImportantMessage(const std::string& message) {
    int X_Position = m_X_start;
    int Y_Position = 7 * m_Y_start;
    MoveCoursorToPosition(X_Position, Y_Position);
    PrintMessage(message, X_Position, Y_Position);
}

void View::PrintWannaPlayOrExitGameMessage(const std::string& message) {
    int X_Position = m_X_start;
    int Y_Position = 7 * m_Y_start + 3;
    MoveCoursorToPosition(X_Position, Y_Position);
    PrintMessage(message, X_Position, Y_Position);
    std::cout << std::endl;
}

void View::PrintMessage(const std::string& message, int X_Position, int Y_Position) {
    m_Current_Important_Message = message;
    int X_NEW_Size_Message_Area = m_Current_Important_Message.length() + 2 * m_X_start;
    m_NEW_Clear_Line = std::string(X_NEW_Size_Message_Area+1, ' ');
    m_NEW_Dash_Line = std::string(X_NEW_Size_Message_Area, '-');
    std::cout << m_NEW_Dash_Line;
    std::cout << std::endl;
    MoveCoursorToPosition(X_Position, Y_Position + 1);
    std::cout << '|';
    int X_Middle_of_Message_Area = X_Position + X_NEW_Size_Message_Area / 2 - message.length() / 2;
    MoveCoursorToPosition(m_X_start + X_Middle_of_Message_Area, Y_Position + 1);
    std::cout << m_NEW_Clear_Line;
    MoveCoursorToPosition(X_Middle_of_Message_Area, Y_Position + 1);
    std::cout << message;
    MoveCoursorToPosition(X_Position + X_NEW_Size_Message_Area, Y_Position + 1);
    std::cout << '|' << std::endl;
    MoveCoursorToPosition(X_Position, Y_Position + 2);
    std::cout << m_NEW_Dash_Line;
    m_X_Input_Select_Position = X_NEW_Size_Message_Area + m_X_start + 2 * m_X_start;
}

void View::ClearImportantMessageIfExist() {
    if (m_Current_Important_Message.empty()) {
        return;
    }
    m_Current_Important_Message.clear();
    for (int j = 0; j < m_Number_Two_Important_Messages_Lines; ++j) {
        MoveCoursorToPosition(m_X_start, 7 * m_Y_start + j);
        //std::cout << m_Clear_Line;
        std::cout << m_NEW_Clear_Line;
    }
}

void View::ClearInputWannaPlayEnteredSymbols(std::string EnterenWannaPlayLine) {
    std::string ClearStreang(EnterenWannaPlayLine.length(), ' ');
    //MoveCoursorToPosition(m_X_Size_Message_Area + 2 * m_X_start, 9 * m_Y_start);
    MoveCoursorToPosition(m_X_Input_Select_Position, 9 * m_Y_start);
    std::cout << ClearStreang;
}

bool View::PlayOneMoreTimeFunction() {
    MoveCoursorToPosition(m_X_Input_Select_Position, 9 * m_Y_start);
    std::string Cell_Move_Entered_Line;
    getline(std::cin, Cell_Move_Entered_Line, '\n');
    char correct_answer = '1';
    ClearImportantMessageIfExist();
    ClearInputWannaPlayEnteredSymbols(Cell_Move_Entered_Line);
    if ((Cell_Move_Entered_Line[0] == '1') && (Cell_Move_Entered_Line.length() == 1)) {
        return true;
    }
    else {
        return false;
    }
}

Game_Type View::PlayerSelectGameType() {    
    PrintWannaPlayOrExitGameMessage("Select:1 - play with computer, else - two players one keyboard");
    if (PlayOneMoreTimeFunction()) {        
        return Game_Type::PlayerVSComputer;
    }
    else {
        return Game_Type::TwoPlayersOnOneKeyboard;
    }
}
