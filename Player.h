#pragma once
#include "Card.h"
#include <vector>
#include <map>
#include "PlayerNameMap.h"
#include <random>


#define _PLAYER_NAME_LENGTH 10;
#define _PLAYER_SURNAME_LENGTH 10;

class Player
{
private:
	std::pair<std::string, std::string> name_surname;
	bool hit;
	std::vector<double> points;
	std::vector<Card> cards_in_hands;

public:
	Player(void)
		: name_surname
		{
			[]()->std::pair<std::string, std::string>
			{
				auto it1 = PlayerName::name_map.begin();
				auto it2 = PlayerName::name_map.begin();
				std::advance(it1, rand() % PlayerName::name_map.size());
				std::advance(it2, rand() % PlayerName::name_map.size());
				std::string name{ it1->first }, surname{ it2->second };
				const std::pair<std::string, std::string> name_surname{name, surname};
				return name_surname;
			}()
		},
		hit{true}
	{}
	Player(const std::string& dealer_name)
		: name_surname
		{
			[&dealer_name]()->std::pair<std::string, std::string>
			{
				const std::pair<std::string, std::string> name_surname{"Dealer", dealer_name};
				return name_surname;
			}()
		},
		hit{ true }
	{}

	void CalculatePoints(void)
	{
		//std::cout << "CalculatePoints() call" << std::endl;
		points.clear();
		for (auto card : cards_in_hands)
		{
			points.emplace_back(((double)card.GetRank() + (((double)card.GetSuit()) / 10)));
		}
	}

	void DrawCard(const Card card_draw) 
	{ 
		//std::cout << "DrawCard() call" << std::endl;
		cards_in_hands.emplace_back(card_draw);
		CalculatePoints();
	}

	const std::pair<std::string, std::string> GetNameSurname(void) const
	{
		//std::cout << "GetNameSurname() call" << std::endl;
		return name_surname;
	}

	std::vector<Card> GetCardsInHands(void) const
	{
		//std::cout << "GetCardsInHands() call" << std::endl;
		return cards_in_hands;
	}

	const std::vector<double> GetPoints(void) const
	{
		//std::cout << "GetPoints() call" << std::endl;
		return points;
	}

	const bool GetHit() const
	{
		//std::cout << "GetHit() call" << std::endl;
		return hit;
	}

	void SetHit(const bool hit_input)
	{
		//std::cout << "SetHit() call" << std::endl;
		hit = hit_input;
	}
};