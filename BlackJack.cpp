/*
    Author: Matas Kimtys
    Start Date: 13/06/2023
*/

#include <iostream>
#include "BlackJack.h"
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

using namespace std;

BlackJack::BlackJack()
    : state{ INIT_STATE },
    time_started{
        []()->std::string
        {
            time_t current_time;
            time(&current_time);
            tm* tr = std::localtime(&current_time);
            char datetime[_TIME_CREATED_LENGTH];
            strftime(datetime, 13, "%Y-%m-%d %H:%M:%S", tr);
            return datetime;
        }()
    }
{
    std::cout << "Welcome to BlackJack!\n";
    Tick();
}

BlackJack::~BlackJack(void)
{

}

void BlackJack::Tick(void)
{
    static int sleep_time;
    while (sleep_time >= 0)
    {
        sleep_time = StateEngine();
        std::this_thread::sleep_for(chrono::milliseconds(sleep_time));
    }
}

int BlackJack::StateEngine(void)
{
    int waiting{ 100 }; //ms
    switch(state)
    {
    case INIT_STATE:
    {
        std::cout << "Please enter dealers' name:";
        std::string dealer_name;
        std::cin >> dealer_name;
        player_pool.emplace_back(Player(dealer_name)); 
        system("CLS");


        unsigned int bot_count;
        bot_select:
        std::cout << "\nPlease select the amount of players you wish to play against (5 is max): ";
        std::cin >> bot_count;
        if (bot_count < 0 && bot_count > 6)
        {
            std::cout << "Type from 0 to 5\n";
            goto bot_select;
        }
        system("CLS");

        std::cout << "\nBest of luck!" << std::endl;

        for (unsigned int i = 0; i <= bot_count; ++i)
        {
            player_pool.emplace_back(Player());
        }
        state = DRAWING_STATE;
    }
    break;

    case DRAWING_STATE:
    {
        static Deck deck;

        for (size_t i = 0; i < deck.cards.size(); ++i)
        {
            
        }

        for (auto &&player : player_pool)
        {
            if (player.GetHit())
            {
            Card pull{ deck.PullCard() };
                player.DrawCard(pull);
                if (player.GetCardsInHands().size() < 2)
                    player.SetHit(true);
                else
                    player.SetHit(false);
            }
        }
        state = DISPLAY_STATE;
        waiting = 5000;
    }
    break;

    case DISPLAY_STATE:
    {
        system("CLS"); 
        std::cout.width(20);
        std::cout << left <<  "NAME" << "|";
        std::cout.width(20);
        std::cout << "CARDSDRAWN" << "|";

        std::cout.width(10);
        std::cout << "POINTS" << std::endl;

        std::cout.width(55);
        std::cout.fill('-');
        std::cout << '-';
        std::cout.fill(' ');
        std::cout << std::endl;

        for (auto player : player_pool)
        {
            std::cout.width(20);
            std::cout << ((player.GetNameSurname()).first + " " + (player.GetNameSurname()).second) << "|";

            std::cout.width(20);
            std::string card_str{ "" };
            //std::cout << player.GetCardsInHands().back().GetRankString() << " " << player.GetCardsInHands().back().GetSuitString() << std::endl;
            std::vector<Card> cards_in_hands{ player.GetCardsInHands() };
            for (auto card : cards_in_hands)
            {
                if (card_str.length() == 0)
                {
                    card_str += card.GetRankString() + card.GetSuitString();
                }
                else
                {
                    card_str += "," + card.GetRankString() + card.GetSuitString();
                }
            }
            std::cout << card_str << "|";

            std::cout.width(10);
            std::string points_str{ "" };
            for (auto point : player.GetPoints())
            {
                if (points_str.length() == 0)
                    points_str += std::to_string((std::roundf(point) * 100 / 100));
                else
                    points_str += "," + std::to_string((std::roundf(point) * 100 / 100));
            }
            std::cout << points_str << std::endl;
        }
        for (auto player : player_pool)
        {
            if (player.GetHit() == true)
            {
                state = DRAWING_STATE;
                break;
            }
        }

        if (state == DISPLAY_STATE)
            state = RESULT_STATE;

        /*if (player_pool.front().GetCardsInHands().size() > 0)
        {
            std::cout << "player0 card:" << player_pool.front().GetCardsInHands().back().GetRankString() << std::endl;
        }*/

        waiting = 3000;

    }
    break;

    case RESULT_STATE:
    {
        waiting = -1;
        unsigned int top_points{ 0 }, top_index{ 0 };
        for (unsigned int i = 0; i < player_pool.size(); ++i)
        {
            if ((player_pool.at(i).GetPoints().back() < 22) && player_pool.at(i).GetPoints().back() > top_points)
            {
                top_index = i;
                top_points = player_pool.at(i).GetPoints().back();
            }
        }       

        std::cout << "The Winner is: " << player_pool.at(top_index).GetNameSurname().first << " " << player_pool.at(top_index).GetNameSurname().second << " with " << top_points << " points!" << std::endl;

    }
    break;

    default:
    {
        std::cout << "Catastropic failure, current state is impossible" << std::endl;
    }
        break;
    }
    return waiting;
}







int main()
{
    BlackJack game;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
