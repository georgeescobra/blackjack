import re
from enum import Enum
import time
from player import Player
from deck import Deck

config = {
    "multiplier" : 1.5,
    "numOfDecks"  : 3,
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
Value of 10->King is 10, Value of Ace is 11: until value of hand is greater than 21, then it turns into 1
--------------------------------
"""

class status(Enum):
    PLAYING = 0
    NOTPLAYING = 1
    WON = 2
    LOST = 3
    DRAW = 4
    
    def status(self):
        pass


def inputName():
    playerName = ""
    valid = False
    while not playerName or not valid :
        playerName = input("Please Enter Your Name: ")
        valid = True if not re.search(r"^\d+", playerName) else False
        if not valid: print("Please Enter Name with no numbers")
    return playerName

def inputBet(playerMoney):
    playerBet = 0
    valid = False
    while not playerBet or not valid:
        playerBet = input("How Much Would You Like To Bet? $")
        valid = True if re.search(r"^\d+", playerBet) else False
        if valid and float(playerBet) > playerMoney: valid = False
        if not valid: print("Please Enter a Valid Amount")
    return float(playerBet)

def inputHitOrStay():
    playerChoice = ""
    hValid = False
    sValid = False
    while not playerChoice or (not hValid and not sValid) :
        playerChoice = input("Would You Like to Hit(H) or Stay(S): ")
        hValid = True if re.search(r"^[hH]\w*", playerChoice) else False
        sValid = True if re.search(r"^[sS]\w*", playerChoice) else False
        if not sValid and not hValid: print("Please Enter A Valid Choice Hit or Stay")
    return 0 if hValid else 1 

def main():
    print(intro)
    name = inputName()
    newPlayer = Player(name, config.get("startingMoney"))
    playerStatus = status.PLAYING
    dealer = Player()
    deck = Deck(config.get("numOfDecks"))
    deck.shuffle()
    
    while newPlayer.getMoney() and deck.getSize() and playerStatus == status.PLAYING:
        print(newPlayer)
        amountToBet = inputBet(newPlayer.getMoney())
        print("*******STARTING ROUND*******")
        newPlayer.addToHand(deck.drawTwo())
        dealer.addToHand(deck.drawTwo())
        newPlayer.printHand()
        newPlayer.printHandValue()
        dealer.printDealerHand()

        # makes sure no one auto busts
        newPlayer.checkHandForAces() 
        dealer.checkHandForAces()
        playerHandValue = newPlayer.getHandValue()
        dealerHandValue = dealer.getHandValue()

        # initial check
        if playerHandValue == 21 or dealerHandValue == 21:
            if playerHandValue == 21 and dealerHandValue == 21: playerStatus = status.DRAW
            elif playerHandValue < dealerHandValue: playerStatus = status.LOST
            elif playerHandValue > dealerHandValue: playerStatus = status.WON

        # player's choice to hit or stand
        while playerStatus == status.PLAYING:
            if newPlayer.getMoney() <= 0:
                print("You have no more money left")
                playerStatus = playerStatus.NOTPLAYING
            else:
                playerChoice = inputHitOrStay() # 0 -> hit, 1-> stay
                if playerChoice == 0:
                    newPlayer.addToHand(deck.drawOne())
                    newPlayer.checkHandForAces()
                    newPlayer.printHand()
                    newPlayer.printHandValue()
                    playerHandValue = newPlayer.getHandValue()
                    if playerHandValue > 21: playerStatus = status.LOST
                else: playerStatus = status.NOTPLAYING
        playerHandValue = newPlayer.getHandValue()

        # dealers turn
        if playerStatus == status.NOTPLAYING: 
            print("\tDEALER'S TURN")
            print("Dealer Shows: ")
            dealer.printHand()
            dealer.printHandValue()
            time.sleep(1)
        while playerStatus == status.NOTPLAYING:
            dealerHandValue = dealer.getHandValue()
            if dealerHandValue > playerHandValue and dealerHandValue <= 21: playerStatus = status.LOST
            elif dealerHandValue > 21: playerStatus = status.WON
            elif dealerHandValue == playerHandValue: playerStatus = status.DRAW
            else:
                if 17 < dealerHandValue < 21 and (dealerHandValue == playerHandValue): playerStatus = status.DRAW
                # i pretty much force a draw if dealerVal == playerVal
                elif dealerHandValue < 21 and playerStatus == status.NOTPLAYING:
                    print("--Dealer Hits--")
                    dealer.addToHand(deck.drawOne())
                    dealer.checkHandForAces()
                    dealer.printHand()
                    print("\r\tDealer's Hand Value: ", dealer.getHandValue())
            if playerStatus == status.NOTPLAYING: time.sleep(1)


        print(playerStatus)
        # resets the round
        print("*******END OF ROUND*******")
        print()
        newPlayer.clearHand()
        dealer.clearHand()
        playerStatus = status.PLAYING

          
         

if __name__ == "__main__": main()

