from deck import Deck
class Player:
    def __init__(self, name, money=100):
        self.name = name
        self.money = money
        self.hand = []

    def __str__(self):
        return f"{self.name} has ${self.money}"

    def getName(self):
        return self.name

    def getMoney(self):
        return self.money

