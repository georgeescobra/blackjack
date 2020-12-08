import re




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
    name = inputName()

if __name__ == "__main__": main()


