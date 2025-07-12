/* Casino Game:
    Coded by
    Ravi Kasaudhan (19BCE2659)
    Enhanced by Copilot: Leaderboard and Game Stats
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

#define N 10

void drawLine(int, char);
void help();
int chooseDifficulty();
void SinglePlayer();
void startGame(int);
void startMultiPlayer(int);
void MultiPlayer();
void welcome();
void showLeaderboard(int n);
void showGameStats();
void resetGameStats();

struct Player{
    int currAmount, initialAmount, bettingAmount, age;
    string name;
    int guess;
    bool playable;

    Player(){
        currAmount = 0;
        initialAmount = 0;
        age = 0;
        name = "";
        guess = 0;
        bettingAmount = 0;
        playable = true;
    }
};

Player _player[N];

// ----------- Statistics Variables -----------
struct GameStats {
    int roundsPlayed = 0;
    int biggestWin = 0;
    int biggestLoss = 0;
    string biggestWinner = "";
    string biggestLoser = "";
    long long totalMoneyWon = 0;
    long long totalMoneyLost = 0;
};

GameStats stats;

void updateStatsWin(const string& playerName, int winAmount) {
    stats.totalMoneyWon += winAmount;
    if(winAmount > stats.biggestWin) {
        stats.biggestWin = winAmount;
        stats.biggestWinner = playerName;
    }
}

void updateStatsLoss(const string& playerName, int lossAmount) {
    stats.totalMoneyLost += lossAmount;
    if(lossAmount > stats.biggestLoss) {
        stats.biggestLoss = lossAmount;
        stats.biggestLoser = playerName;
    }
}

void showGameStats() {
    cout << "\n\n====== GAME STATISTICS ======\n";
    cout << "Total rounds played: " << stats.roundsPlayed << endl;
    cout << "Biggest single win: $" << stats.biggestWin;
    if (!stats.biggestWinner.empty()) cout << " by " << stats.biggestWinner; 
    cout << endl;
    cout << "Biggest single loss: $" << stats.biggestLoss;
    if (!stats.biggestLoser.empty()) cout << " by " << stats.biggestLoser;
    cout << endl;
    cout << "Total money won by all players: $" << stats.totalMoneyWon << endl;
    cout << "Total money lost by all players: $" << stats.totalMoneyLost << endl;
    cout <<   "=============================\n";
}

void resetGameStats() {
    stats = GameStats();
}

// ----------- Leaderboard Function -----------
void showLeaderboard(int n) {
    // Prepare list of active players
    vector<pair<int, string>> ranking;
    for(int i = 0; i < n; ++i) {
        ranking.push_back({_player[i].currAmount, _player[i].name});
    }
    sort(ranking.rbegin(), ranking.rend()); // Descending order

    cout << "\n\n====== LEADERBOARD ======\n";
    cout << "Rank\tPlayer\t\tBalance\n";
    for(size_t i = 0; i < ranking.size(); ++i) {
        cout << (i+1) << "\t" << ranking[i].second << "\t\t$" << ranking[i].first << endl;
    }
    cout <<   "=========================\n";
}

// ----------- Main Game Code -----------

int main() {
   welcome();
}

void drawLine(int n, char symbol) {
    for (int i = 0; i < n; i++)
        cout << symbol;
    cout << "\n";
}

void help() {
    system("cls");
    cout << "\n\n";
    drawLine(80, '-');
    cout << "\t\tRULES OF THE GAME\n";
    drawLine(80, '-');
    cout << "\t1.) Age must be greater than 17\n";
    cout << "\t2.) Choose any number between 1 to 10\n";
    cout << "\t3.) If you win you will get 10 times of money you bet\n";
    cout << "\t4.) If you bet on wrong number you will lose your betting amount\n\n";
    drawLine(80, '-');
    system("pause");
}

int chooseDifficulty() {
    cout << "\n\nChoose a mode : \n\n";
    cout << "1. Easy Mode\n2. Hard Mode\n";
    int difficulty;
    cin >> difficulty;

    if(difficulty != 1 && difficulty != 2) {
        cout << "\nEnter a valid Choice";
        return chooseDifficulty();
    }
    else return difficulty;
}

void SinglePlayer() {
    help();
    resetGameStats();
    int max_range = (chooseDifficulty() == 1 ? 5 : 10);
    string playerName;
    int amount;
    int bettingAmount;
    int guess;
    int dice;
    char choice;

    srand(time(0));

    cout << "\n\nEnter Your Name : ";
    cin >> ws;
    getline(cin, playerName);
    int a;
    cout << "Enter your age : ";
    cin >> a;
    if (a >= 18) {
        label:
        cout << "\n\nEnter Deposit amount to play game : $";
        cin >> amount;
        if(amount <= 0) {
            cout << "You need to Deposit atleast $1\n";
            goto label;
        }
        do {
            system("cls");
            cout << "\n\nYour current balance is $ " << amount << "\n";

            // Get player's betting amount
            do {
                cout << playerName << ", enter money to bet : $";
                cin >> bettingAmount;
                if (bettingAmount > amount)
                    cout << "Your betting amount is more than your current balance\n" <<
                    "\nRe-enter data\n ";
            } while (bettingAmount > amount);

            // Get player's numbers
            do {
                printf("Guess your number to bet between 1 to %d :", max_range);
                cin >> guess;
                if (guess <= 0 || guess > max_range) {
                    printf("\nPlease check the number!! should be between 1 to %d\n", max_range);
                    cout << "\nRe-enter data\n ";
                }
            } while (guess <= 0 || guess > max_range);

            dice = rand() % max_range + 1;

            ++stats.roundsPlayed;

            if (dice == guess) {
                int won = bettingAmount * max_range;
                cout << "\n\nGood Luck!! You won Rs." << won;
                amount = amount + won;
                updateStatsWin(playerName, won);
            } else {
                cout << "Bad Luck this time !! You lost $ " << bettingAmount << "\n";
                amount = amount - bettingAmount;
                updateStatsLoss(playerName, bettingAmount);
            }

            cout << "\nThe winning number was : " << dice << "\n";
            cout << "\n" << playerName << ", You have $ " << amount << "\n";
            if (amount == 0) {
                cout << "You have no money to play ";
                break;
            }
            cout << "\n\n-->Do you want to play again (y/n)? ";
            cin >> choice;
        } while (choice == 'Y' || choice == 'y');

        cout << "\n\n\n";
        drawLine(70, '=');
        cout << "\n\nThanks for playing game. Your balance amount is $ " << amount << "\n\n";
        drawLine(70, '=');
        showGameStats();
        cout << "\n";
        system("pause");
    } else {
        cout << "\tYou are underage to play this game " << endl;
        int s = 18 - a;
        cout << "\tCome back after " << s << " years\n\n";
        system("pause");
    }
}

void startGame(int n) {
    do {
        int dice;
        system("cls");
        cout << "\n\nThe current balance of players:\n\n";

        for(int i = 0; i < n; i++) {
            if(_player[i].playable)
                cout << _player[i].name << " : $" << _player[i].currAmount << "\n";
        }

        for(int i = 0; i < n; i++) {
            if(!_player[i].playable) continue;
            cout << "\n\n" << _player[i].name << ", enter money to bet : $";
            bool flag = 1;
            while(flag) {
                flag = 0;
                cin >> _player[i].bettingAmount;
                if(_player[i].bettingAmount > _player[i].currAmount) {
                    cout << "Your betting amount is more than your current balance\n" <<
                    "\nRe-enter data\n ";
                    flag = 1;
                }
            }
            do {
                cout << "\nGuess your number to bet between 1 to 10 : ";
                cin >> _player[i].guess;
                if (_player[i].guess <= 0 || _player[i].guess > 10) {
                    cout << "Please check the number!! should be between 1 to 10\n" <<
                    "\nRe-enter data\n ";
                }
            } while (_player[i].guess <= 0 || _player[i].guess > 10);
        }

        dice = rand() % 10 + 1;
        cout << "\nThe winning number is : " << dice << "\n";
        int winnersOfRound = 0, totalLostAmount = 0;

        ++stats.roundsPlayed;

        for(int i = 0; i < n; ++i) {
            if(!_player[i].playable) continue;
            if (dice == _player[i].guess) {
                ++winnersOfRound;
            } else {
                totalLostAmount += _player[i].bettingAmount;
            }
        }

        int winAmount = (winnersOfRound == 0 ? 0 : totalLostAmount/winnersOfRound);

        cout << "\n\n";
        for(int i = 0; i < n; ++i) {
            if(!_player[i].playable) continue;

            cout << _player[i].name << " , ";

            if (dice == _player[i].guess) {
                cout << "You won : $" << winAmount;
                _player[i].currAmount += winAmount;
                updateStatsWin(_player[i].name, winAmount);
            } else {
                cout << "Bad Luck this time !! You lost $ " << _player[i].bettingAmount << "\n";
                _player[i].currAmount -= _player[i].bettingAmount;
                updateStatsLoss(_player[i].name, _player[i].bettingAmount);
            }
            cout << "\n";
        }

        for(int i = 0; i < n; ++i) {
            if (_player[i].currAmount == 0 && _player[i].playable) {
                cout << _player[i].name << ", You lost : $" << _player[i].initialAmount << "\nYou have no money to play. You are out of the game\n\n";
                _player[i].playable = 0;
            }
        }

        int playersRemaining = 0;

        for(int i = 0; i < n; ++i) {
            if(_player[i].playable) ++playersRemaining;
        }

        if(playersRemaining == 1) {
            for(int i = 0; i < n; ++i) {
                if(_player[i].playable) {
                    cout << _player[i].name << " You have won the game. Congratulations!!!\n";
                    int balance = _player[i].currAmount - _player[i].initialAmount;
                    if(balance >= 0) {
                        cout << ", And You won : $ " << balance;
                    }
                    else {
                        cout << ", But You lost : $" << abs(balance);
                    }
                }
            }
            break;
        }

        for(int i = 0; i < n; ++i) {
            if(!_player[i].playable) continue;
            char choice;
            int balance;
            cout << "\n\n" << _player[i].name << "-->Do you want to play again (y/n)? ";
            cin >> choice;
            switch(choice) {
                case 'N':
                case 'n':   _player[i].playable = 0;
                            balance = _player[i].currAmount - _player[i].initialAmount;
                            if(balance >= 0) {
                                cout << _player[i].name << ", You won : $ " << balance;
                            }
                            else {
                                cout << _player[i].name << ", You lost : $" << abs(balance);
                            }
                            break;
                default: cout << "...\n";
            }
        }
        playersRemaining=0;
        for(int i = 0; i < n; ++i) {
            if(_player[i].playable) ++playersRemaining;
        }

        if(playersRemaining > 1) {
            continue;
        }
        else if(playersRemaining == 1) {
            for(int i = 0; i < n; ++i) {
                if(_player[i].playable) {
                    cout << _player[i].name << "You have won the game. Congratulations!!!\n";
                    int balance = _player[i].currAmount - _player[i].initialAmount;
                    if(balance >= 0) {
                        cout << _player[i].name << ", And You won : $ " << balance;
                    }
                    else {
                        cout << _player[i].name << ", But You lost : $" << abs(balance);
                    }
                    break;
                }
            }
        }
        else {
            cout << "\n\n\nAll the players are out of balance or decided to quit. The Game ends here\n\n";
            drawLine(70, '=');
            cout << "\n\nThanks for playing the game\n\n";
            drawLine(70, '=');
            showLeaderboard(n);
            showGameStats();
            system("pause");
            break;
        }
    }while(1);

    // Show leaderboard and stats at end of multiplayer session
    showLeaderboard(n);
    showGameStats();
    cout << "\n";
}

void startMultiPlayer(int n) {
    system("cls");
    help();
    resetGameStats();
    system("cls");
    for(int i = 0; i < n; ++i) {
        label:
        cout << "\n\nEnter the details of player " << i+1 << ": \n";
        cout << "Name : ";
        cin >> ws;
        getline(cin, _player[i].name);
        label1:
        cout << "Age : ";
        cin >> _player[i].age;
        if(_player[i].age < 1) {
            cout << "Enter a valid age\n";
            goto label1;
        }
        else if(_player[i].age >= 1 && _player[i].age < 18) {
            cout << "Players below age of 18 cannot play.\n";
            goto label;
        }
        label2:
        cout << "Enter Deposit amount to play game : $";
        cin >> _player[i].initialAmount;
        if(_player[i].initialAmount <= 0) {
            cout << "You need to Deposit atleast $1\n";
            goto label2;
        }
        _player[i].currAmount = _player[i].initialAmount;
        _player[i].playable = 1;
    }
    startGame(n);
}

void MultiPlayer() {
    cout << "\n\nEnter the number of Players (Max : 10)\n";
    int numberOfPlayers = 0;
    do {
        cin >> numberOfPlayers;
        if(numberOfPlayers < 0 || numberOfPlayers > 10) {
            cout << "\nPlease enter a valid number\n";
        }
        else if(numberOfPlayers == 1) {
            SinglePlayer();
        }
        else {
            assert(numberOfPlayers > 1 && numberOfPlayers <= 10);
            startMultiPlayer(numberOfPlayers);
            break;
        }
    }while(1);
}

void welcome() {
    system("cls");
    drawLine(240, '_');
    cout << "\n\n\n\t\tCASINO GAME";
    cout << "\n\n\t\t*WELCOME TO VIT CASINO*\n\n\n\n";
    drawLine(240, '_');
    cout << "\n\nChoose an option\n";
    do {
        cout << "1. Single Player Mode\n";
        cout << "2. Multi Player Mode\n";
        cout << "3. Help\n";
        cout << "4. Exit\n\n";
        int choice;
        cin >> choice;
        switch(choice) {
            case 1: SinglePlayer();
                    welcome();
                    break;
            case 2: MultiPlayer();
                    welcome();
                    break;
            case 3: help();
                    welcome();
                    break;
            case 4: exit(1);
            default:    cout << "Choose a valid option between 1-3\n";
        }
    }while(1);
}