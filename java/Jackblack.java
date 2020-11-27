import java.util.Scanner;


/**
 *this is my first ever self java project 
 * @author georgeescobarjr.
 */
public class Jackblack {

    /**
     * @param args the command line arguments
     */
  
    public static void main(String[] args) {
       
        
        //init
        //this is the 3rd version
        //initializing needed variables
        double Bet = 500;
        double betSize;
        String Continue;
        boolean meDone = false;
        boolean dealerDone =false;
        boolean keepGoing =true;
        
        //This is the explanation of the game
        System.out.println("Welcome to Tsing's BlackJack Table!");
        System.out.println("This is your starting money " + Bet + "$");
        System.out.println("The Goal of this game is to beat the Dealer with either a 21 or higher sum card number");
        System.out.println("There are three decks in this game, so don't be startled with repeating cards");
        System.out.println("If you go over the sum of 21 you bust, and you will lose the bet you put in");
        System.out.println("If you beat the dealer you will win x1.5 the bet");
        System.out.println("Convesrsely: If you lose the round, you will lose x1.5 the bet");
        System.out.println("Once the cards are dealt, you are given the option of either H: Hit or S: Stay");
        System.out.println("If you choose to Hit you are given another card until you either reach 21, you Stay, or  Bust");
        System.out.println("If you decide to Stay, then it is the dealers turn");
        System.out.println("If you Bust, you automatically lose the round.");
        System.out.println("If you go even with the Dealer no money is lost");
        System.out.println("Let's Get Started!!");
        System.out.println("Values of 10-King is 10, Value of Ace is 11: until value of Hand is greater than 21, then it turns into 1");
        System.out.println("___________________________________");
        System.out.println("");
        System.out.println("");
       
        
        //this is to have a user name input
        Scanner sc = new Scanner(System.in);
        Scanner newName = new Scanner(System.in);
        System.out.print("Please enter your name: ");
        
        String name = newName.next();
        
        //this initializes the Deck and the cards inside the Deck
        Deck theDeck = new Deck(3, true);
        do{
        Player me = new Player(name);
        Player dealer = new Player("Dealer");
        
        //This gets the sums of the hands of each player
        int mySum = me.getHandSum();
        int dealerSum = dealer.getHandSum();
        
        
        //deals the hand of user and dealer
        me.addCard(theDeck.dealNextCard());
       boolean first = dealer.addCard(theDeck.dealNextCard());
        me.addCard(theDeck.dealNextCard());
        dealer.addCard(theDeck.dealNextCard());
        
        //print initial hands
       
        System.out.println("Cards are dealt \n");
        
        //this is user input for the bet size
        Scanner toBet = new Scanner(System.in);
        System.out.println("This is the amount of money you can bet: $" + Bet);
        System.out.print("Please enter the amount of money you want to bet: $");
        betSize = toBet.nextDouble();
        
        //this makes sure that the bet size is valid
        if(betSize > 0 && betSize <= Bet){
            
           
            me.printHand(true);
             System.out.print("Hand Value:");
            System.out.print(me.getHandSum());
            System.out.println();
            System.out.println();
            dealer.printHand(false);
                
                //this makes sure that player auto wins if he draws a 21 from start
                if (me.getHandSum() == 21){
                System.out.println("You got a natural 21, You Win!");
                Bet = Bet + ((1.5)*betSize);
                me.printHand(true);
                System.out.println(mySum);
                //this makes sure that turns for each player is ended
                meDone = true;
                dealerDone = true;
                
                //prints out the amount of money left after the win
                System.out.println("Amount of money left: $" + Bet);
                
                //this makes sure that the dealer auto wins if he drawrs a 21 from the start
                 } else if(dealer.getHandSum() ==21){
                    System.out.println("Dealer got a natural 21, Dealer Wins!");
                    System.out.println(" ");
                    dealer.printHand(true);
                    Bet = Bet - ((1.5)*betSize);
                    System.out.println("Amount of money left: $" + Bet);
                    //ends the player's and dealerss turn
                    meDone = true;
                    dealerDone = true;
                
    }
        
                
        System.out.println(" ");
        
        //creates the variable string needed for the user input in the next loop
        String ans;
        //will always run if player still has a turn
        while(!meDone){
           
            
            //user's turn
            //will make sure that this runs in a loop as long as user doesn't stay or bust
                while(!meDone){
                    System.out.println("");
                    System.out.println("___________________________________");
                    System.out.print("Hit or Stay? (Enter H or S): ");
                    ans =sc.next();
                    System.out.println();
                    // will make sure that it can either be lower case or upper case
                    if(ans.compareToIgnoreCase("H")==0){
                        //add next card in the deck and store whether player is busted

                        meDone = !me.addCard(theDeck.dealNextCard());
                        
                        me.printHand(true);
                        //user friendly tells the value of their current hand
                        System.out.print("Hand Value:");
                        System.out.print(me.getHandSum());
                       //this code ensures that if I Hit, and if I were to get 21 or above
                       //the code exits and stops right here
                        if(me.getHandSum() == 21){
                            Bet = ((1.5) * betSize) + Bet;
                            System.out.println("");
                            System.out.println("You Win!");
                            
                            meDone = true;
                            dealerDone = true;
                            

                        }else if(me.getHandSum() > 21){
                            System.out.println("");
                            System.out.println("You bust, so Dealer Wins");
                            Bet = Bet - ((1.5) * betSize);
                            
                            meDone= true;
                            dealerDone = true;
                                if(betSize ==0){
                                    System.out.println("");
                                    System.out.println("You ran out of money. :(");
                                }
                        }

                    }else {
                        meDone = true;
                        dealer.printHand(false);
                    }
                }
            
            System.out.println("___________________________________");
            //dealer's turn
                    while(!dealerDone){
                        System.out.println("___________________________________");
                        if(dealer.getHandSum() <17){
                            System.out.println("The Dealer hits \n");
                            dealerDone = !dealer.addCard(theDeck.dealNextCard());
                            dealer.printHand(false);
                            dealerDone = false;
                            if(dealerSum ==21){
                                System.out.println("");
                                System.out.println("The Dealer Wins!");
                                dealer.printHand(true);
                                Bet = Bet - ((1.5) * betSize);
                                
                                dealerDone = true;
                                if(betSize <=0){
                                        System.out.println("You ran out of money. :(");
                                    }

                            }else if(dealer.getHandSum() > 21){
                                dealer.printHand(true);
                                System.out.println("");
                                System.out.println("The Dealer bust, so you win!");
                                System.out.println("");
                                System.out.println("___________________________________");
                                dealerDone = true;
                                meDone =true;
                                Bet = ((1.5) * betSize) + Bet;
                                

                            }
                        }else if(dealer.getHandSum()>= 17){
                            System.out.println("");
                            System.out.println("The Dealer stays \n");
                            dealerDone =true;
                            if(dealer.getHandSum() ==21){
                                System.out.println("");
                                System.out.println("The Dealer Wins!");
                                
                                Bet = Bet - ((1.5) * betSize);
                                
                                dealerDone = true;
                                
                            }
                        }
                    
                    }
                        if(dealerDone && meDone){
                            
                                    me.printHand(true);
                                    
                                    System.out.print("Hand Value:");
                                    System.out.print(me.getHandSum());
                                    System.out.println("");
                                   System.out.println("");
                                   
                                    dealer.printHand(true);
                                    System.out.print("Hand Value:");
                                    System.out.print(dealer.getHandSum());

                        if(dealer.getHandSum() < me.getHandSum() && me.getHandSum()<21){
                           System.out.println("");
                           System.out.println("");
                            System.out.println("You win!");
                             Bet = ((1.5) * betSize) + Bet;
                                
                                
                                     
                        }else if(dealer.getHandSum() > me.getHandSum() && dealer.getHandSum()<21){
                            System.out.println("");
                            System.out.println("");
                            System.out.println("Dealer Wins!");
                             Bet = Bet - ((1.5) * betSize) ;
                                
                        }else if(dealer.getHandSum() == me.getHandSum() && dealer.getHandSum()<21){
                            System.out.println("");
                            System.out.println("");
                            System.out.println("It is a draw");
                            System.out.println("This is the amount of money you have left: $" + Bet);
                                 
                        }
                        }
          
        }
         //outputs if the user inputs invalid responses 
        }else if(betSize > 0){
            System.out.println("You tried to bet more than you have.");
        }else if(betSize <0){
            System.out.println("You can't have a negative bet :S ");
        }   
        //these are flags to rest the turns of the player in order for the game to reset properly
        dealerDone = false;
        meDone = false;
        System.out.println("");
        System.out.println("___________________________________");
        System.out.println("Amount of money left: " + Bet);
        System.out.println("___________________________________");
        Scanner input = new Scanner(System.in);
          //this prompts the user whether or not they want to continue playing
          //I want it in the same line for aesthetics
            System.out.println("Would you like to continue? (Enter Y or N) ");
            System.out.print("Enter Y for Yes or N for No: ");
            Continue = input.next();
          
        }while(Continue.compareToIgnoreCase("Y")==0 && Bet > 0);
            if(Bet < 0 ){
                System.out.println("Thanks for playing "+ name + "! Unfortunately you ran out of money. :(");
            }else{
            System.out.println("Thanks for playing "+ name + "!! You ended with $" + Bet );
        
        }
    
    }        
        //May or may not decide to implement this so this will just be here for now
        //this makes sure that the Deck will constantly have cards and if not then the game will exit
        public void checkDeckSize(int Bet){
            Deck numOfCards = new Deck();
            numOfCards.getNumOfCards();
      
        if(numOfCards.getNumOfCards() <= 0){
            System.out.println("The Table has ran out of Cards.");
            System.out.println("Thanks for playing!! You ended with " + Bet + "$");
            System.exit(0);
        } 

    
    
    }
     
}
          
