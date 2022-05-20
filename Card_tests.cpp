// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_default_ctor) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_get_suit_with_trump) {
    Card j_h(Card::RANK_JACK, Card::SUIT_HEARTS);

    ASSERT_EQUAL(Card::SUIT_HEARTS, j_h.get_suit(Card::SUIT_HEARTS));
    ASSERT_EQUAL(Card::SUIT_HEARTS, j_h.get_suit(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, j_h.get_suit(Card::SUIT_DIAMONDS));

    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);

    ASSERT_EQUAL(Card::SUIT_CLUBS, k_c.get_suit(Card::SUIT_HEARTS));
    ASSERT_EQUAL(Card::SUIT_CLUBS, k_c.get_suit(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_CLUBS, k_c.get_suit(Card::SUIT_DIAMONDS));
}

TEST(test_is_face) {
    Card t_h(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card j_h(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);
    Card n_d(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(!t_h.is_face());
    ASSERT_TRUE(!n_d.is_face());
    ASSERT_TRUE(j_h.is_face());
    ASSERT_TRUE(k_c.is_face());
}

TEST(test_is_right_bower) {
    Card t_h(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card j_h(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);
    Card n_d(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card j_s(Card::RANK_JACK, Card::SUIT_SPADES);
    Card j_d(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(j_h.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(!j_h.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(!j_h.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(!j_h.is_right_bower(Card::SUIT_CLUBS));
    //Never true
    ASSERT_TRUE(!t_h.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(!t_h.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(!t_h.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(!t_h.is_right_bower(Card::SUIT_CLUBS));
}

TEST(test_is_left_bower) {
    Card t_h(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card j_h(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);
    Card n_d(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card j_s(Card::RANK_JACK, Card::SUIT_SPADES);
    Card j_d(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(j_d.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(!j_d.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(!j_d.is_left_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(!j_d.is_left_bower(Card::SUIT_CLUBS));
    //Never true
    ASSERT_TRUE(!n_d.is_left_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(!n_d.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(!n_d.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(!n_d.is_left_bower(Card::SUIT_CLUBS));
}

TEST(test_is_trump) {
    Card t_h(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card j_h(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);
    Card n_d(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card j_s(Card::RANK_JACK, Card::SUIT_SPADES);
    Card j_d(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(j_h.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(j_h.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(!j_h.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(!j_h.is_trump(Card::SUIT_CLUBS));
 
    ASSERT_TRUE(!t_h.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(t_h.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(!t_h.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(!t_h.is_trump(Card::SUIT_CLUBS));

    ASSERT_TRUE(!k_c.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(!k_c.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(!k_c.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(k_c.is_trump(Card::SUIT_CLUBS));
}

TEST(test_comparison_operators) {
    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);
    Card j_s(Card::RANK_JACK, Card::SUIT_SPADES);
    Card j_h(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card j_d(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card t_h(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card n_d(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(k_c > j_s);
    ASSERT_TRUE(j_s < k_c);
    ASSERT_TRUE(j_s <= k_c);
    ASSERT_TRUE(k_c >= j_s);
    ASSERT_TRUE(j_s != k_c);
    ASSERT_FALSE(j_s == k_c);

    ASSERT_TRUE(j_d > j_s);
    ASSERT_TRUE(j_s < j_d);
    ASSERT_TRUE(j_s <= j_d);
    ASSERT_TRUE(j_d >= j_s);
    ASSERT_TRUE(j_s != j_d);
    ASSERT_FALSE(j_s == j_d);

    ASSERT_FALSE(n_d > n_d);
    ASSERT_FALSE(n_d < n_d);
    ASSERT_TRUE(n_d >= n_d);
    ASSERT_TRUE(n_d <= n_d);
    ASSERT_FALSE(n_d != n_d);
    ASSERT_TRUE(n_d == n_d);

    ASSERT_FALSE(k_c < j_s);
    ASSERT_FALSE(j_s > k_c);
    ASSERT_FALSE(j_s >= k_c);
    ASSERT_FALSE(k_c <= j_s);
}

TEST(test_insertion_operator) {
    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);

    stringstream out;
    stringstream correct;

    out << k_c;
    correct << "King of Clubs";

    ASSERT_EQUAL(out.str(), correct.str());
}

TEST(test_Card_less) {
    Card k_c(Card::RANK_KING, Card::SUIT_CLUBS);
    Card k_d(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card k_s(Card::RANK_KING, Card::SUIT_SPADES);
    Card k_h(Card::RANK_KING, Card::SUIT_HEARTS);

    Card j_s(Card::RANK_JACK, Card::SUIT_SPADES);
    Card j_h(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card j_c(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card j_d(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    Card t_h(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card n_d(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(Card_less(j_s, k_c, Card::SUIT_HEARTS));
    ASSERT_TRUE(!Card_less(j_s, k_c, Card::SUIT_SPADES));
    ASSERT_TRUE(!Card_less(j_s, j_c, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(j_c, j_s, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(n_d, k_c, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(n_d, k_c, Card::SUIT_CLUBS));
    ASSERT_TRUE(!Card_less(n_d, k_c, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(!Card_less(n_d, n_d, Card::SUIT_SPADES));

    
    ASSERT_TRUE(Card_less(j_s, k_c, n_d, Card::SUIT_HEARTS));
    ASSERT_TRUE(!Card_less(t_h, k_c, n_d, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(j_c, j_h, n_d, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(k_s, k_d, n_d, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(k_d, k_h, n_d, Card::SUIT_HEARTS));
    ASSERT_TRUE(!Card_less(n_d, k_c, n_d, Card::SUIT_HEARTS));
    //ASSERT_TRUE(Card_less());
}


TEST_MAIN()
