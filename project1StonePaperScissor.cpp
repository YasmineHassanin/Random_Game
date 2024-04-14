#include <iostream>
#include<cstdlib>
#include<string>
#include<cmath>
using namespace std;
enum en_ToolsofGame{stone=1,paper=2,scissor=3};
enum en_winner {player=1,computer=2,no_winner=3};
struct st_Roundinfo
{
    short Roundnumber = 0;
    en_ToolsofGame choiceofplayer1;
    en_ToolsofGame choiceofcomputer;
    en_winner winner;
    string Nameofwinner;

};
struct st_Gameinfo
{
    short gameRounds = 0;
    short timesofplayer1won =0;
    short timesofcomputerwon=0 ;
    short drawtimes=0;
    en_winner finalwinner;
    string winnername="";


};


int rondomChoiceOfComputer(int  from, int to)
{
    int rondomnumber = rand() % (to - from + 1) + from;
    return rondomnumber;
}
en_ToolsofGame choiceOfComputer()
{
    return (en_ToolsofGame)rondomChoiceOfComputer(1, 3);
}
en_ToolsofGame choiceOfPlayer()
{
    int choice;
   do
   {
        cout << "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors\n";
        cin >> choice;

    } while (choice < 1 || choice >3);
     
      return  (en_ToolsofGame)choice;
}
en_winner WhowonInRound(st_Roundinfo roundinfo)
{
    if (roundinfo.choiceofcomputer== roundinfo.choiceofplayer1)
    {
        return en_winner::no_winner;
    }
    switch (roundinfo.choiceofplayer1)
    {
    case en_ToolsofGame::stone:
        if (roundinfo.choiceofcomputer == en_ToolsofGame::paper)
            return en_winner::computer;
        break;

    case en_ToolsofGame::paper:
        if (roundinfo.choiceofcomputer == en_ToolsofGame::scissor)
            return en_winner::computer;
        break;

    case en_ToolsofGame::scissor:
        if (roundinfo.choiceofcomputer == en_ToolsofGame::stone)
            return en_winner::computer;
        break;   
    }
    return en_winner::player;
}
void SetColorOfScreen(en_winner winner)
{
    switch (winner)
    {
    case en_winner::player:
        system("color 2F");//green
        break;
    case en_winner::computer:
        system("color 4F");//red
        cout << "\a";
        break;
    case en_winner::no_winner:
        system("color 6F");
        break;
    }
}
string NameWinner(en_winner winner)
{
    string arrNameWinner[3] = { "Player1","Computer","Draw"};
    return arrNameWinner[winner - 1];
}
string choiceOfGame(en_ToolsofGame choice)
{
    string arrchoice[3] = { "Stone","Paper","Scissor" };
    return arrchoice[choice - 1];
}

void PrintRoundResult(st_Roundinfo roundresult)
{
            cout << "--------------------Round[" << roundresult.Roundnumber << "]--------------------\n";
            cout << "Player1 choice:" << choiceOfGame(roundresult.choiceofplayer1) << endl;
            cout << "Computer choice:" << choiceOfGame(roundresult.choiceofcomputer) << endl;
            cout << "Round winner:" << roundresult.Nameofwinner<< endl;
            cout << "------------------------------------------------------------\n";
            SetColorOfScreen(roundresult.winner);
}
en_winner WhoWinTheGame(short winTimesofPlayer,short wintimesofcomputer)
{
    if (winTimesofPlayer > wintimesofcomputer)
        return en_winner::player;
    else if (winTimesofPlayer < wintimesofcomputer)
        return en_winner::computer;
    else
        return en_winner::no_winner;
}
st_Gameinfo fillGameResult(int gameround,int playerwintimes,int computerwintimes,int Drawtimes)
{
    st_Gameinfo Gameresults;
    Gameresults.gameRounds = gameround;
    Gameresults.timesofplayer1won = playerwintimes;
    Gameresults.timesofcomputerwon = computerwintimes;
    Gameresults.drawtimes = Drawtimes;
    Gameresults.finalwinner = WhoWinTheGame(playerwintimes, computerwintimes);
    Gameresults.winnername = NameWinner(Gameresults.finalwinner);
    return Gameresults;
}




st_Gameinfo PlayGame(short howmanyRounds)
{
    st_Roundinfo roundinfo;
    short playerwintimes = 0, computerwintimes = 0, Drawtimes = 0;
    for (int Gameround = 1; Gameround <= howmanyRounds; Gameround++)
    {
        cout << "\nRound[" << Gameround << "] begins:\n";
        roundinfo.Roundnumber = Gameround;
        roundinfo.choiceofplayer1 = choiceOfPlayer();
        roundinfo.choiceofcomputer = choiceOfComputer();
        roundinfo.winner = WhowonInRound(roundinfo);
        roundinfo.Nameofwinner = NameWinner(roundinfo.winner);

        if (roundinfo.choiceofplayer1 == en_winner::player)
            playerwintimes++;
        else if (roundinfo.choiceofcomputer == en_winner::computer)
            computerwintimes++;
        else
            Drawtimes++;
        PrintRoundResult(roundinfo);
    }
    return fillGameResult(howmanyRounds, playerwintimes, computerwintimes, Drawtimes);
}

string Tabs(short NumberofTabs)
{
    string tab = "";
    for (int i = 1; i < NumberofTabs; i++)
    {
        tab = tab + "\t";
    }
    return tab;
}
void showGameOver()
{
    cout << Tabs(2) << "----------------------------------------------------\n";
    cout << Tabs(2) << "+ + + Game Over + + +" << endl;
    cout << Tabs(2) << "----------------------------------------------------\n";
}
void showfinalgameresults(st_Gameinfo Gameresults)
{
    cout << Tabs(2) << "--------------------[Game Result]--------------------\n\n";
    cout << Tabs(2) << "Game Rounds:" << Gameresults.gameRounds << endl;
    cout << Tabs(2) << "Player1WinTimes:" << Gameresults.timesofplayer1won << endl;
    cout << Tabs(2) << "computerWinTimes:" << Gameresults.timesofcomputerwon << endl;
    cout << Tabs(2) << "DrawTimes :" << Gameresults.drawtimes << endl;
    cout << Tabs(2) << "winnerName :" << Gameresults.winnername << endl;

    cout << Tabs(2) << "---------------------------------------------------------\n";
    SetColorOfScreen(Gameresults.finalwinner);
}
short ReadHowManyrounds()
{
    short Gameround=1;
    do
    {
        cout << "how many rounds you want to play from 1 to 10\n";
        cin >> Gameround;
    } while (Gameround < 1 || Gameround > 10);
        

    return Gameround;

}
void ResetScreen()
{
    system("cls");
    system("color 0F");

}
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        st_Gameinfo gameResult = PlayGame(ReadHowManyrounds());
        showGameOver();
        showfinalgameresults(gameResult);
        cout << endl << Tabs(2) << "Do you want play again Y/N";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
   
   srand((unsigned)time(NULL));
   StartGame();
   return 0;
  
}
