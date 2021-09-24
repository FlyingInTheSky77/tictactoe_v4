

#include <iostream>
#include "View.h"
#include "Game_Board.h"
#include "Control.h"
#include "EnumVariables.h"

int main()
{
    View Game_View;
    Game_Type Game_Type = Game_View.PlayerSelectGameType();
    Control Game_Control(Game_Type, Game_View);
    Game_View.DrawWikiBoardAndSectionHeaders(Game_Type);

    bool Wanna_Play_More{ true };
    do {
        Game_Control.CurrentGameFunction();
        Game_View.PrintWannaPlayOrExitGameMessage("Wanna play more - press \"1\", else - any key");
        Wanna_Play_More = Game_View.PlayOneMoreTimeFunction();
    } while (Wanna_Play_More);

    Game_View.ClearImportantMessageIfExist();
    Game_View.PrintWannaPlayOrExitGameMessage("EXIT THE GAME");
}

