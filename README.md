README

--------------------------------------------------------------------
The object of the game is to beat the dealer in the following way:
- Reach a final score higher than the dealer without exceeding 21
- Let the dealer draw additional cards until his or her hand exceeds 21

Card values:
- Ace is worth 11 points, unless it causes the hand to exceed 21, in which case it is worth 1 point
- Face cards are worth 10 points
- Other cards are worth the number on the card

Game order
- Player is dealt an initial hand of two cards
- Dealer is dealt an initial hand of one card
- Player must choose whether to 'hit' (take a card) or 'stand' (stand on current score)
- Player can 'hit' as many times as he/she wishes.
- If player's score exceeds 21 points, it busts, and player immediately loses
- Otherwise Dealer's hand is resolved by drawing cards until the score is higher or equal than player's score
- If dealer's score exceeds 21 points, it busts, and the player immediately wins

The game is played by the command line using keyboard interactions declared in the game.
--------------------------------------------------------------------

