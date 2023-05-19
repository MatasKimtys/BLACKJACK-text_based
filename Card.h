#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>

#define _TIME_CREATED_LENGTH 14

enum Suit
{
	CLUB = 0,
	DIAMOND,
	HEART,
	SPADE,
	_SUIT_TOTAL,
	BLACK = 5,
	RED = 6
};

enum Rank
{
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	_RANK_TOTAL,
	JOKER
};

enum Special_Rank
{
};

enum Special_Suit
{

};



class Card
{
private:
	std::string time_created;
	Suit suit;
	Rank rank;
	bool is_hidden;
	
public:
	Card(Suit suit_input, Rank rank_input, bool is_hidden_input);
	~Card(void);
	const std::string GetTimeCreated(void);
	const Suit GetSuit(void);
	const Rank GetRank(void);
	const bool GetIsHidden(void);
	const std::string GetSuitString(void);
	const std::string GetRankString(void);

};

Card::Card(Suit suit_input, Rank rank_input, bool is_hidden_input)
	: time_created
	{
		[]()->std::string
		{
			time_t current_time;
			time(&current_time);
			tm* tr = std::localtime(&current_time);
			char datetime[_TIME_CREATED_LENGTH];
			strftime(datetime, 13, "%Y-%m-%d %H:%M:%S", tr);
			return datetime;
		}()
	},
	suit{ suit_input },
	rank{ rank_input },
	is_hidden{ is_hidden_input }
{

}

Card::~Card(void)
{

}

const std::string Card::GetTimeCreated(void)
{
	return time_created;
}

const Suit Card::GetSuit(void)
{
	return suit;
}

const Rank Card::GetRank(void)
{
	return rank;
}

const bool Card::GetIsHidden(void)
{
	return is_hidden;
}

const std::string Card::GetSuitString(void)
{
	switch (suit)
	{
	case CLUB:    return "C";
	case DIAMOND: return "D";
	case HEART:   return "H";
	case SPADE:   return "S";
	case RED:     return "R";
	case BLACK:   return "B";
	default:      return "Unknown Suit";
	}
}

const std::string Card::GetRankString(void)
{
	switch (rank)
	{
	case TWO:   return "2";
	case THREE: return "3";
	case FOUR:  return "4";
	case FIVE:  return "5";
	case SIX:   return "6";
	case SEVEN: return "7";
	case EIGHT: return "8";
	case NINE:  return "9";
	case TEN:   return "10";
	case JACK:  return "J";
	case QUEEN: return "Q";
	case KING:  return "K";
	case ACE:   return "A";
	case JOKER: return "JJ";
	default:    return "Unknown Rank";
	}
}