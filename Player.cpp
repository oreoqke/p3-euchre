// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include <string>
#include <vector>
#include <cassert>


#include <algorithm>

using namespace std;
//--------------------
//iplementing a dereived class simple player
class SimplePlayer : public Player {
public:

	SimplePlayer() {}

	SimplePlayer(const string& in_name) : name(in_name) {}

	const string& get_name() const override {
		return name;
	}

	void add_card(const Card& c) override {
		assert(num_cards < MAX_HAND_SIZE);
		hand.push_back(c);
		++num_cards;
	}




	bool make_trump(const Card& upcard, bool is_dealer,
		int round, string& order_up_suit) const override {

		assert(round == 1 || round == 2);

		int num_face_trump = 0;

		//determine the number of face trump cards
		for (int i = 0; i < num_cards; ++i) {
			if (hand[i].is_face() && hand[i].is_trump(order_up_suit)) {
				++num_face_trump;
			}
		}

		//During round 1
		if (round == 1 && num_face_trump >= 2) {
			return true;
		}

		if (round == 2 && num_face_trump >= 1) {
			return true;
		}

		return false;
	}


	//helper for add_and_discard
	Card *least_card(const string &trump) {
		Card *min_card = &hand[0];

		//find the minimum card in hand given trump
		for (int i = 0; i < num_cards; ++i) {
			if (Card_less(hand[i], *min_card, trump)) {
				min_card = &hand[i];
			}
		}

		return min_card;

	}

	//helper for lead card max_card in hand
	const Card *max_card(const string& trump) const {
		const Card *max_card = &hand[0];

		for (int i = 0; i < num_cards; ++i) {
			if (Card_less(*max_card, hand[i], trump)) {
				max_card = &hand[i];
			}
		}
		return max_card;
	}

	bool only_trump(const string &trump) const {
		for (int i = 0; i < num_cards; ++i) {
			if (!hand[i].is_trump(trump)) {
				return false;
			}
		}

		return true;
	}




	void add_and_discard(const Card& upcard) override { 
		assert(num_cards >= 1);

		//sort the cards
		//sort(hand.begin(), hand.begin() + num_cards - 1);//????


		if (Card_less(upcard, *least_card(upcard.get_suit()), upcard.get_suit())) { 
			return;
		}
		else {
			*least_card(upcard.get_suit()) = upcard;
			return;
		}
	}

	Card lead_card(const string& trump) override { 
		
//		if (only_trump(trump)) {
	//		Card lead_card = *max_card(trump);
		//}
		//Card lead_card = 
		
		
		assert(false);
		return Card();
	}

	Card play_card(const Card& led_card, const string& trump) override { 
		assert(false);
		return Card();
	}

private:
	string name;
	int num_cards;
	vector<Card> hand;
};


class HumanPlayer : public Player {
public:

	//constructors
	SimplePlayer() {}

	SimplePlayer(const string& in_name) : name(in_name) {}


	const string& get_name() const override {
		return name;
	}

	void add_card(const Card& c) override {
		assert(num_cards < MAX_HAND_SIZE);
		hand.push_back(c);
		++num_cards;
	}

	bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) {
		assert(round == 1 || round == 2);

		string response;
		cin >> response;
		if (response == "pass") {return false}

		else {
			order_up_suit = response;
			return true;
		}
	}




};







//----outside of the class functions
Player* Player_factory(const string &name, const string &strategy) {
	if (strategy == "Simple") { return new SimplePlayer(name); }
	//if (strategy == "Human") { return new HumanPlayer(name); }

	//invalid strategy if we get here.
	assert(false);
	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.get_name();
	return os;
}