#pragma once

#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include <vector>

#define _DECK_SIZE 54

enum States
{
	INIT_STATE,
	DRAWING_STATE,
	DISPLAY_STATE,
	RESULT_STATE
};


class BlackJack
{
private:
	int state;
	std::string time_started;
	std::string time_ended;
	std::vector<Player> player_pool;
	
public:

public:
	BlackJack(void);
	~BlackJack(void);
	void Tick(void);
	int StateEngine(void);
};
