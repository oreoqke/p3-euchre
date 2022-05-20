// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include "Pack.h"

//??????????
Pack::Pack() :next(0) {
	for (int i = 0; i < PACK_SIZE; ++i) {
		Card card_in(RANK_NAMES_BY_WEIGHT[7 + (i % 6)],
			SUIT_NAMES_BY_WEIGHT[i / 6]);
		cards[i] = card_in;
	}
}
Pack::Pack(std::istream& pack_input): next(0) {
	std::string suit;
	std::string rank;
	std::string junk;

	for (int i = 0; i < PACK_SIZE; ++i) {
		pack_input >> rank;
		pack_input >> junk;
		pack_input >> suit;

		Card card_in(rank, suit);
		cards[i] = card_in;
	}
}

Card Pack::deal_one() {
	return cards[next++];
}

void Pack::reset() {
	next = 0;
}

void Pack::shuffle() {
	next = 0;
	std::array<Card, PACK_SIZE> new_cards;

	for (int i = 0; i < 7; ++i) {
		//save shuffle in a temp array
		for (int k = 0; k < PACK_SIZE; ++k) {
			new_cards[(2 * k + 1) % (PACK_SIZE + 1)] = cards[k];
		}

		//copy the shuffled deck back into the original array
		for (int k = 0; k < PACK_SIZE; ++k) {
			cards[k] = new_cards[k];
		}
	}
}

bool Pack::empty() const {
	if (next == PACK_SIZE) { return true;; }
	return false;
}
