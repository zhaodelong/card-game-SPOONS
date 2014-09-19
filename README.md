card-game-SPOONS
================
This program is intended to familiarize you with process synchronization using the
pthread library. You can find a tutorial on multithreaded programming at website
http://www.llnl.gov/computing/tutorials/pthreads.

In this assignment, you will write a program that simulates the card game called
SPOONS.

The game of SPOONS is played by a group of N people sitting in a circle around a pile of
(N – 1) spoons. Initially each player is dealt 5 cards. The remaining cards are divided
into N piles with each pile placed between two players. Each player first discards a card
from his hand to the left pile and then picks up a card from the right pile. When a
player's hand contains all cards of the same color, he grabs a spoon. At this point, each
one of the other players also attempts to grab a spoon. The player who is unable to get a
spoon is the loser.

The action of each player will be somewhat as follows:

  player (i) {
    …
    …
    repeat {
      discard a card to the left pile;
      pickup a card from the right pile;
    } until ((hand contains all cards of same color) or
      (someone has grabbed a spoon));
    pickup a spoon if there is one;
    loser := found-no-spoon;
  }
  
Write the program to play with four players. For each player print the cards he/she is
holding, the card discarded, and the card picked up. Finally, print whether the player is a
loser or not.

(If you like you can continue the game by leaving out the loser each time until you are
left with a single player.)
