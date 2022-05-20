// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//Default constructor initialized to two of spades
Card::Card(): rank(RANK_TWO), suit(SUIT_SPADES) {}

//Constructor checks if the entered type is allowed.
Card::Card(const std::string& rank_in, const std::string& suit_in)
	: rank(rank_in), suit(suit_in) {
	//checking the suit
	assert (suit_in == SUIT_SPADES || 
		   suit_in == SUIT_HEARTS ||
		   suit_in == SUIT_CLUBS ||
		   suit_in == SUIT_DIAMONDS);
	//checking the rank
	assert (rank_in == RANK_TWO ||
		   rank_in == RANK_THREE ||
		   rank_in == RANK_FOUR ||
		   rank_in == RANK_FIVE ||
		   rank_in == RANK_SIX ||
		   rank_in == RANK_SEVEN ||
		   rank_in == RANK_EIGHT ||
		   rank_in == RANK_NINE ||
		   rank_in == RANK_TEN ||
		   rank_in == RANK_JACK || 
		   rank_in == RANK_QUEEN || 
	 	   rank_in == RANK_KING || 
		   rank_in == RANK_ACE );
}

std::string Card::get_rank() const {
	return rank;
}

std::string Card::get_suit() const {
	return suit;
}

std::string Card::get_suit(const std::string& trump) const {
	//Checking if trump os the valid suit
		//checking the suit
	assert (trump == SUIT_SPADES ||
		trump == SUIT_HEARTS ||
		trump == SUIT_CLUBS ||
		trump == SUIT_DIAMONDS);
	/*the only case when the card in the game is not the same suit as
	what is on the card is when the card is a left bower*/
	if ((*this).is_left_bower(trump)) { return trump; }
	else { return suit; }
}

bool Card::is_face() const {
	if (get_rank() == RANK_JACK ||
		get_rank() == RANK_QUEEN ||
		get_rank() == RANK_KING ||
		get_rank() == RANK_ACE) {

		return true;
	}
	else { return false; }
}

bool Card::is_right_bower(const std::string &trump) const {
	if (get_suit() == trump && get_rank() == RANK_JACK) {
		return true;
	}

	return false;
}

bool Card::is_left_bower(const std::string& trump) const {
	if (get_rank() == RANK_JACK && get_suit() == Suit_next(trump)) { 
		return true;
	}
	return false;
}

bool Card::is_trump(const std::string& trump) const {
	if (get_suit(trump) == trump) { return true; }
	return false;
}

//-----------------operators

bool operator<(const Card &lhs, const Card &rhs) {
	int lhs_val;
	int rhs_val;
	//finding the place of the lhs card in the array
	for (int i = 0; i < NUM_RANKS; ++i) {
		if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
			lhs_val = i;
		}
	}
	//finding the palce of the rhs in the array
	for (int i = 0; i < NUM_RANKS; ++i) {
		if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
			rhs_val = i;
		}
	}
	//the card that is farther in the array will be more improtant
	if (lhs_val < rhs_val) { return true; }

	//In case of a tie, look at the suits
	if (lhs_val == rhs_val) {
		int lhs_suit_val;
		int rhs_suit_val;
		
		for (int i = 0; i < NUM_RANKS; ++i) {
			if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
				lhs_suit_val = i;
			}
			if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
				rhs_suit_val = i;
			}
		}

		if (lhs_suit_val < rhs_suit_val) {
			return true;
		}

	}

	return false;
}

bool operator<=(const Card& lhs, const Card& rhs) {
	if (lhs > rhs) { return false; }
	return true;
}

bool operator>(const Card& lhs, const Card& rhs) {
	if (rhs < lhs) { return true; }
	return false;
}

bool operator>=(const Card& lhs, const Card& rhs) {
	if (lhs < rhs) { return false; }
	return true;
}

bool operator==(const Card& lhs, const Card& rhs) {
	if (lhs > rhs || lhs < rhs) { return false; }
	return true;
}

bool operator!=(const Card& lhs, const Card& rhs) {
	if (lhs == rhs) { return false; }
	return true;
}

//------------------
std::string Suit_next(const std::string& suit) {
	if (suit == Card::SUIT_CLUBS) { return Card::SUIT_SPADES; }
	if (suit == Card::SUIT_DIAMONDS) { return Card::SUIT_HEARTS; }
	if (suit == Card::SUIT_SPADES) { return Card::SUIT_CLUBS; }
	if (suit == Card::SUIT_HEARTS) { return Card::SUIT_DIAMONDS; }
	return "";
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
	os << card.get_rank() << " of " << card.get_suit();
	return os;
}


bool Card_less(const Card& a, const Card& b, const std::string& trump) {
	//taking care of the case when one of the cards is the right bower
	if (b.is_right_bower(trump)) { return true; }
	if (a.is_right_bower(trump)) { return false; }
	//taking care of the case when one of the cards is the left bower
	if (b.is_left_bower(trump)) { return true; }
	if (a.is_left_bower(trump)) { return false; }
	//Now taking care of the case when b is trump
	if (b.is_trump(trump)) {
		if (a.is_trump(trump)) { return (a < b); }
		return true;
	}
	//b is not trump
	if (a.is_trump(trump)) { return false; }
	else { return (a < b); }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const Card& led_card,
	const std::string& trump) {
	//if led card is trump, same case as when no led card is present
	if (led_card.is_trump(trump)) {
		return Card_less(a, b, trump);
	}

	//taking care of the case when one of the cards is the right bower
	if (b.is_right_bower(trump)) { return true; }
	if (a.is_right_bower(trump)) { return false; }
	//taking care of the case when one of the cards is the left bower
	if (b.is_left_bower(trump)) { return true; }
	if (a.is_left_bower(trump)) { return false; }
	//Now taking care of the case when b is trump
	if (b.is_trump(trump)) {
		if (a.is_trump(trump)) { return (a < b); }
		return true;
	}
	//b is not trump. a still might be trump
	if (a.is_trump(trump)) { return false; }

	//neither b nor a trump
	//if b is the same suit as led card
	if (b.get_suit() == led_card.get_suit()) {
		if (a.get_suit() == led_card.get_suit()) { return (a < b); }
		return true;
	}
	//a is the same suit as led card but b is not
	if (a.get_suit() == led_card.get_suit()) { return false; }

	return (a < b);
}
