import re
from player import Player
from deck import Deck
config = {
    "multiplier" : 1.5,
    "numOfDecks"  : 1,
    "startingMoney"  : 500.0
}
intro = """
--------------------------------
The Goal of the game is to beat the Dealer with either a 21 count or higher sum card number.
There could be multiple decks in this game, so don't be startled with repeating cards.
There are {config["numOfDecks"]} this game.
If you go over the sum of 21 you bust, and automatically lose the bet you put in.
If you beat the dealer you will win the bet x{config["multiplier"]}
Conversely: You lose the round you lose the x{config["multiplier"]} bet
Once cards are dealt, you are given the option of either H: Hit or S: Stay
If you choose to Hit you are given another card until you either reach 21, stay, or Bust
If you Stay, round ends dealer flips his card.
If you bust, you automatically lose the round.
If you go even with the Dealer no money is gained nor lost.
Value of 10->King is 10, Value of Ace is 11L: until value of hand is greater than 21, then it turns into 1
--------------------------------
"""

def inputName():
    playerName = ""
    valid = False
    while not playerName or not valid :
        playerName = input("Please Enter Your Name: ")
        valid = True if not re.search(r"\d+", playerName) else False
        if not valid: print("Please Enter Name with no numbers")
    return playerName

def inputBet():
    playerBet = 0
    valid = False
    while not playerBet or not valid:
        playerBet = input("How Much Would You Like To Bet? $")
        valid = True if not re.search(r"\w+", playerBet) else False
        if not valid: print("Please Enter a Valid Amount")
    return float(playerBet)

def inputHitOrStay():
    pass

def main():
    print(intro)
    name = inputName()
    newPlayer = Player(name, config.get("startingMoney"))
    deck = Deck(config.get("numOfDecks"))
    deck.print()

if __name__ == "__main__": main()

