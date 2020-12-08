import random
class Card:
    def __init__(self, suit, rank, val):
        self.rank = rank
        self.suit = suit
        self.value = val

    def __str__(self):
        return f"{self.rank} of {self.suit}s"



kind = ["Heart", "Spade", "Club", "Diamond"]
ranks = [
    ("Two", 2),
    ("Three" , 3),
    ("Four" , 4),
    ("Five" , 5),
    ("Six" , 6),
    ("Seven" , 7),
    ("Eight" , 8),
    ("Nine" , 9),
    ("Ten" , 10),
    ("Jack" , 10),
    ("Queen" ,10),
    ("King" , 10),
    ("Ace" , 10)
]

class Deck:
    # cant use enum because multiple cases where they are the same value
    def __init__(self, numOfDecks):
        self.numOfDecks = numOfDecks
        self.deck = []
        for i in range(self.numOfDecks):
            for suit in range(4):
                for rank in range(13):
                    self.deck.append(Card(kind[suit], ranks[rank][0], ranks[rank][1])) 
    def shuffle(self):
        random.shuffle(self.deck)

    def print(self):
        for card in self.deck: print(card)
