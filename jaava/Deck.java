package jaava;

import java.util.Random;

/**
 *
 * @author georgeescobarjr.
 */
public class Deck {
    //array of cards in the deck
    private Card[] myCards;
    //number of cards currently in the deck
    private int numCards;
    
    public Deck(){
        //call the other constructor, defining one deck without shuffling
        
        this(1, false);
        
    }
    
    //constructor that defines the number of decks o.e., how many sets of 52 cards
    //are in the deck
    
    //@param numDeck number of individual decks in this deck
    //@param shuffle whether or not we want to shuffle the cards
    public Deck(int numDecks, boolean shuffle){
        
        this.numCards = numDecks * 52;
        this.myCards = new Card[this.numCards];
        
            //initialize card index
            int c=0;
        
            //for each deck
        for(int i=0; i< numDecks; i++){
            //for each suit
            for(int j=0; j<4; j++){
                //for each card
                for(int k=1; k<=13;k++){
                    this.myCards[c] = new Card(Suit.values()[j], k);
                    c++;
                }
            
            }
        }
        //shuffling if necessary
        if(shuffle){
            this.shuffle();
        }
        
       
        
        
        
    }
    
    public int getNumOfCards(){
        int numOfCard = 0;
        numCards = numOfCard;
        return numOfCard;
        
    }
 
    public void shuffle(){
        //init random number generator
        
        Random rng = new Random();
        //temporary card
        
        Card temp;
        int j;
        for (int i=0; i<this.numCards; i++){
            //get a random card j to swap i's vlaue with
            
           j = rng.nextInt(this.numCards);
           //do swap
           
           temp = this.myCards[i];
           this.myCards[i] = this.myCards[j];
           this.myCards[j] = temp;
        }
        
    }
    
   
    public Card dealNextCard(){
        //get the top card
        
        Card top = this.myCards[0];
        
        //need to shift all cards to the left
        for (int c=1; c<this.numCards; c++){
            this.myCards[c-1] = this.myCards[c];
        }
        this.myCards[this.numCards-1] = null;
        this.numCards--;
        return top;//returning the dealt card
        
    }
    public void printDeck(int numToPrint){
        
        for(int c=0;c<numToPrint; c++){
            System.out.printf("% 3d/%d %s\n", c+1, this.numCards, this.myCards[c].toString()); 
            
        }
        
        System.out.printf("\t[%d other]\n", this.numCards-numToPrint);
        
    }
}
