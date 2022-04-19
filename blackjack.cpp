/*
    File:           BlackJack.cpp
    Author:         Santeri Levo
    Description:    BlackJack assignment
*/

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <functional>

enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum Suit { SPADES, HEARTS, DIAMONDS, CLUBS };

struct Card {
    Rank rank;
    Suit suit;
};

struct Deck {
    std::vector<Card> cards;
    int const MAX_DECK_SIZE = 52;
    int const NUM_SUITS = 4;
    int const NUM_RANKS = 13;
};

void initialize(Deck& deck)
{
    for (int suit = 0; suit < deck.NUM_SUITS; ++suit)
    {
        for (int rank = 1; rank < deck.NUM_RANKS + 1; ++rank)
        {
            Card card;
            card.suit = Suit(suit);
            card.rank = Rank(rank);
            deck.cards.push_back(card);
        }
    }
}

std::string card_value(const Card& card)
{
    std::string rank = "";
    switch(card.rank){
        case ACE:
            rank = "A";
            break;
        case TWO:
            rank = std::to_string(TWO);
            break;
        case THREE:
            rank = std::to_string(THREE);
            break;
        case FOUR:
            rank = std::to_string(FOUR);
            break;
        case FIVE:
            rank = std::to_string(FIVE);
            break;
        case SIX:
            rank = std::to_string(SIX);
            break;
        case SEVEN:
            rank = std::to_string(SEVEN);
            break;
        case EIGHT:
            rank = std::to_string(EIGHT);
            break;
        case NINE:
            rank = std::to_string(NINE);
            break;
        case TEN:
            rank = std::to_string(TEN);
            break;
        case JACK:
            rank = "J";
            break;
        case QUEEN:
            rank = "Q";
            break;
        case KING:
            rank = "K";
            break;
    }

    switch(card.suit){
        case SPADES:
            rank += " of Spades     ";
            break;
        case HEARTS:
            rank += " of Hearts     ";
            break;
        case DIAMONDS:
            rank += " of Diamonds   ";
            break;
        case CLUBS:
            rank += " of Clubs      ";
            break;
    }
    return rank;
}

void shuffle(Deck& deck)
{
    std::random_shuffle(deck.cards.begin(), deck.cards.end());
}

void deal_card(Deck& deck, std::vector<Card>& toWho)
{
    toWho.push_back(deck.cards.front());
    deck.cards.erase(deck.cards.begin());
}

int add_score(std::vector<Card>& hand)
{
    int score = 0;
    for (const Card& c : hand)
    {
        std::cout << card_value(c) << std::endl;
    }
    std::sort(hand.begin(), hand.end(),[](Card card1, Card card2){return card1.rank > card2.rank;});
    for (const Card& c : hand)
    {
        switch (c.rank){
            case ACE:
                if (score <= 10)
                {
                    score += 11;
                }
                else
                {
                    score += 1;
                }
                break;
            case TWO:
                score += TWO;
                break;
            case THREE:
                score += THREE;
                break;
            case FOUR:
                score += FOUR;
                break;
            case FIVE:
                score += FIVE;
                break;
            case SIX:
                score += SIX;
                break;
            case SEVEN:
                score += SEVEN;
                break;
            case EIGHT:
                score += EIGHT;
                break;
            case NINE:
                score += NINE;
                break;
            case TEN:
            case JACK:
            case QUEEN:
            case KING:
                score += TEN;
                break;
        }
    }
    std::cout << "Score is: " << score << std::endl;
    return score;
}

void wait()
{
    for (int i = 0; i < 31; ++i)
    {

        std::cout << "-";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void welcome()
{
    wait();
    std::cout << '\n';
    std::string welcome = "-- Welcome to play BlackJack --";
    for (int i = 0; i < int(welcome.length()); ++i)
    {
        std::cout << welcome[i];
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << '\n';
    wait();
    std::cout << '\n' << std::endl;
    std::cout << "\nDo you want to see the instructions? 1 = Yes, 0 = No" << std::endl;
    int instructions = 0;
    std::cin >> instructions;
    switch(instructions){
        case 1:
            std::cout << "--------------------------------------------------------------------" << std::endl;
            std::cout << "The object of the game is to beat the dealer in the following way:" << std::endl;
            std::cout << "Reach a final score higher than the dealer without exceeding 21" << std::endl;
            std::cout << "Let the dealer draw additional cards until his or her hand exceeds 21" << std::endl;
            std::cout << "\nCard values:" << std::endl;
            std::cout << "Ace is worth 11 points, unless it causes the hand to exceed 21,\n" <<
                         "in which case it is worth 1 point" << std::endl;
            std::cout << "Face cards are worth 10 points" << std::endl;
            std::cout << "Other cards are worth the number on the card" << std::endl;
            std::cout << "\nGame order" << std::endl;
            std::cout << "Player is dealt an initial hand of two cards" << std::endl;
            std::cout << "Dealer is dealt an initial hand of one card" << std::endl;
            std::cout << "Player must choose whether to 'hit' (take a card) or 'stand'\n" <<
                         "(stand on current score)" << std::endl;
            std::cout << "Player can 'hit' as many times as he/she wishes." << std::endl;
            std::cout << "If player's score exceeds 21 points, it busts, and player immediately loses;\n" <<
                         "otherwise Dealer's hand is resolved by drawing cards until the score\n" <<
                         "is higher or equal than player's score" << std::endl;
            std::cout << "If dealer's score exceeds 21 points, it busts, and the player immediately wins;\n" <<
                         "otherwise declare winner or tie" << std::endl;
            std::cout << "--------------------------------------------------------------------" << std::endl;
            break;
        case 0:
            break;
        default:
            std::cout << "\n\nInvalid action. I guess not then!" << std::endl;
    }
}

void play()
{
    Deck my_deck;
    initialize(my_deck);
    shuffle(my_deck);
    std::vector<Card> dealer;
    std::vector<Card> player;
    deal_card(my_deck, player);
    deal_card(my_deck, dealer);
    deal_card(my_deck, player);

    std::cout << "\nDealers hand is: " << std::endl;
    int dealer_score = add_score(dealer);
    std::cout << "\nPlayers hand is: " << std::endl;
    int player_score = add_score(player);
    bool a_true = true;
    while(a_true)
    {
        std::cout << "\nSelect action: 1 = HIT, 2 = STAND, 0 = QUIT" << std::endl;
        int action = 0;
        std::cin >> action;
        switch(action)
        {
            case 1:
                wait();
                std::cout << "\n";
                deal_card(my_deck, player);
                std::cout << "\nDealers hand is: " << std::endl;
                add_score(dealer);
                std::cout << "\nPlayers hand is: " << std::endl;
                player_score = add_score(player);
                if (player_score > 21)
                {
                    a_true = false;
                }
                break;
            case 2:
                a_true = false;
                break;
            case 0:
                exit(0);
            default:
                std::cout << "\n\nInvalid action." << std::endl;
        }
    }

    if (player_score > 21)
    {
        std::cout << "\n\nPlayer busted.\n\n" << std::endl;
    }
    else
    {
        while (dealer_score < 17)
        {
            wait();
            std::cout << "\n\nDealer hits." << std::endl;
            deal_card(my_deck, dealer);
            std::cout << "\nDealers hand is: " << std::endl;
            dealer_score = add_score(dealer);
        }
        std::cout << "\nPlayers hand is: " << std::endl;
        add_score(player);


        if (dealer_score > 21)
        {
            std::cout << "\n\nDealer busted, player wins.\n\n" << std::endl;
        }
        else if (dealer_score > player_score)
        {
            std::cout << "\n\nDealer wins.\n\n" << std::endl;
        }
        else if (dealer_score < player_score)
        {
            std::cout << "\n\nPlayer wins.\n\n";
        }
        else
        {
            std::cout << "\n\nIts a push.\n\n";
        }
    }
}

int main()
{
    srand(time(NULL));

    welcome();
    bool go_on = true;
    while(go_on)
    {
        play();
        std::cout << "\n-------------------------------" << std::endl;
        std::cout << "-- Do you want to play again --" << std::endl;
        std::cout << "------- 1 = YES, 0 = NO -------" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        int answer = 0;
        std::cin >> answer;
        std::cout << "\n\n";
        switch(answer)
        {
            case 1:
                break;
            case 0:
                go_on = false;
                break;
            default:
                std::cout << "\n\nInvalid action. Let's play again!" << std::endl;
        }
    }

    wait();
    std::cout << '\n';
    std::string thx = "---- Thank you for playing ----";
    for (int i = 0; i < int(thx.length()); ++i)
    {
        std::cout << thx[i];
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << '\n';
    wait();
    std::cout << '\n' << std::endl;

    return 0;
}
