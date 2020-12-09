from deck import Deck
class Player:
    def __init__(self, name="Dealer", money=0):
        self.name = name
        self.money = money
        self.hand = []

    def __str__(self):
        return f"{self.name} has ${self.money}"

    def getName(self):
        return self.name

    def getMoney(self):
        return self.money

    def addToHand(self, cards):
        for card in cards:
            self.hand.append(card)

    def printHand(self):
        print(f"{self.name}'s Cards:")
        for card in self.hand: print(f"\t{card}")

    def printDealerHand(self):
        if self.name == "Dealer":
            i = 0
            for card in self.hand:
                if i == 0: 
                    print("\t[hidden]")
                    i += 1
                else: print(f"\t{card}")

    def getHandValue(self):
        value = 0
        for card in self.hand: value += card.value
        return value

    def printHandValue(self):
        print(f"{self.name}'s hand value: {self.getHandValue()}")
