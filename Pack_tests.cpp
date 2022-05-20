// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

    first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

    for (int i = 0; i < 10; ++i) {
        first = pack.deal_one();
    }
    ASSERT_EQUAL(Card::RANK_ACE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, first.get_suit());

    for (int i = 0; i < 4; ++i) {
        first = pack.deal_one();
    }
    ASSERT_EQUAL(Card::RANK_QUEEN, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, first.get_suit());
}

TEST(test_pack_input) {
    ifstream pack_input("pack.in");
    assert(pack_input.is_open());

    Pack pack(pack_input);
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

    first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

    for (int i = 0; i < 10; ++i) {
        first = pack.deal_one();
    }
    ASSERT_EQUAL(Card::RANK_ACE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, first.get_suit());

    for (int i = 0; i < 4; ++i) {
        first = pack.deal_one();
    }
    ASSERT_EQUAL(Card::RANK_QUEEN, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, first.get_suit());

    pack_input.close();


}

TEST(test_reset) {
    Pack pack;
    Card card_dealt = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, card_dealt.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, card_dealt.get_suit());

    pack.reset();
    card_dealt = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, card_dealt.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, card_dealt.get_suit());

    for (int i = 0; i < 10; ++i) {
        card_dealt = pack.deal_one();
    }
    ASSERT_EQUAL(Card::RANK_KING, card_dealt.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, card_dealt.get_suit());

    pack.reset();
    card_dealt = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, card_dealt.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, card_dealt.get_suit());


}

TEST(test_shuffle) {
    Pack pack;

    ifstream in("right_pack.in.txt");
    //THIS INPUT IS VALIUD ONLY WHEN THE CARDS ARE SHUFFLED ONCE.
    //MAKE SURE TO EDIT THIS FUNCTION BEFORE RUNNING THE TEST OR IT WILL
    //FAIL
    assert(in.is_open());

    Pack right_pack(in);

    pack.shuffle();

    Card card1;
    Card card2;

    for (int i = 0; i < 24; ++i) {
        card1 = pack.deal_one();
        card2 = right_pack.deal_one();

        ASSERT_TRUE(card1 == card2);

    }



    in.close();
}
TEST(test_empty) {
    Pack pack;
    Card card;

    for (int i = 0; i < 24; ++i) {
        card = pack.deal_one();
    }

    ASSERT_TRUE(pack.empty());
    pack.reset();
    ASSERT_FALSE(pack.empty());
}

// Add more tests here

TEST_MAIN()
