#pragma once

#include "Card.h"
#include <vector>
#include <algorithm>  
#include <array>      
#include <random>     
#include <chrono>     
#include <random>

#define _DECK_SIZE 54

class Deck
{
private:

public:
	std::vector<Card> cards;

public:
	Deck()
		: cards
		{
			[]() -> std::vector<Card>
			{
				std::vector<Card> cards;
				cards.reserve(54);
				for (unsigned int j, i = TWO; i < _RANK_TOTAL; ++i)
					for (j = 0; j < _SUIT_TOTAL; ++j)
						cards.push_back(Card((Suit)j, (Rank)i, false));
				//cards.push_back(Card(BLACK, JOKER, false));
				//cards.push_back(Card(RED, JOKER, false));
				unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
				std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
				return cards;
			}()
		} {};
	~Deck() {};

	const Card PullCard()
	{
		srand(time(NULL));
		const unsigned int pick_a_number{ rand() % cards.size()};
		const Card drawn_card{ cards.at(pick_a_number) };
		cards.erase(std::next(cards.begin()) + pick_a_number-1);
		return drawn_card;
	};
};
