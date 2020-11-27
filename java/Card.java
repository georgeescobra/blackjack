public class Card {
    //private means data is only available in this class Card
   private Suit mySuit;
  
   private int myNumber;
   
   //number of hits card, where Ace: 1, J-K : 11-13
   
   
   //Card constructor
   public Card(Suit aSuit, int aNumber){
    // this is in there emphasizes that we are accessing property of the class
    //we can take out this and it will still work
        this.mySuit = aSuit;
        
        if (aNumber >=1 &&aNumber <=13){
            this.myNumber = aNumber;
            
        }else {
            System.err.println(aNumber + "is not a vlid card number");
            System.exit(1);
        }
        
        this.myNumber = aNumber;
}
   public int getNumber(){
       //this returns number of the card
       return myNumber;
   }
   
   //return the name of the card
   public String toString(){
       
       String numStr = "Error";
       switch(this.myNumber){
           case 2:
               numStr = "Two ";
               break;
           case 3: 
               numStr = "Three ";
               break;
           case 4: 
               numStr = "Four ";
               break;
           case 5:
               numStr = "Five ";
               break;
           case 6:
               numStr = "Six ";
               break;
           case 7: 
               numStr = "Seven ";
               break;
           case 8:
               numStr = "Eight ";
               break;
           case 9:
               numStr = "Nine ";
               break;
           case 10:
               numStr ="Ten ";
               break;
           case 11:
               numStr = "Jack ";
               break;
           case 12:
               numStr ="Queen ";
               break;
           case 13: 
               numStr = "King ";
               break;
           case 1:
               numStr = "Ace ";
               break;
               
            
            
       }
       return numStr + "of " + mySuit.toString();
   }
    
}

