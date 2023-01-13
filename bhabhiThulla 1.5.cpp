//  ADIL ZAFAR       FA21-BSE-004
// MUNEEB ZAHID      FA21-BSE-091
//TALHA SHAFIQUE     FA21-BSE-152

#include<iostream>
#include<string>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<fstream>

using namespace std;

enum Turn{
    PLAYER1,PLAYER2,PLAYER3,PLAYER4
};
Turn highestCardHolder = (Turn)0, prevHighestCardHolder = (Turn)0;
enum Face{
    TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING,ACE
};
enum Suits{
    DIAMOND,HEART,CLUBS,SPADES
};
struct players{ //for players' circular linked list
    Turn turn;
    players* nextTurn;
    players* prev;
};

struct Card{
    Face value;
    Suits suit;
};
Card *highestCard = NULL;
struct P1{
    Card card;
    P1* next;
};

struct P2{
    Card card;
    P2* next;
};
struct P3{
    Card card;
    P3* next;
};
struct P4{
    Card card;
    P4* next;
};
struct pile{
    Card pileCard[4];
    int top = -1;
}pile;
struct P1 *P1first,*P1last,*P1temp,*P1n;
struct P2 *P2first,*P2last,*P2temp,*P2n;
struct P3 *P3first,*P3last,*P3temp,*P3n;
struct P4 *P4first,*P4last,*P4temp,*P4n;

bool thulla_1 = false;
bool thulla_2 = false;
bool thulla_3 = false;
bool thulla_4 = false;

void setupDeck();
void shuffleDeck();
void displayDeck();
void distributeCards();
void insertCardP1(Card c);
void insertCardP2(Card c);
void insertCardP3(Card c);
void insertCardP4(Card c);
void showCardsP1();
void showCardsP2();
void showCardsP3();
void showCardsP4();
string stringPlayer(Turn turn);
string checkSuit(Suits a);
string checkFace(Face f);
int lengthOfP1();
int lengthOfP2();
int lengthOfP3();
int lengthOfP4();
Face peekCardValueP1();
Face peekCardValueP2();
Face peekCardValueP3();
Face peekCardValueP4();
Card removeCardP1(int index);
Card removeCardP2(int index);
Card removeCardP3(int index);
Card removeCardP4(int index);
Card popCardFromStack();
void pushCardToStack(Card c);
void trashPile();
void emptyPileToPlayer();
void pileTopCardPrint();
Card peekTopCard();
void viewStack();
void checkhighestCard();
void computerTurn(Turn turn);
bool checkThulla();
void userTurn(Turn turn);
void gotoxy(int column,int line);
string getStatus(players* p);
void welcomeScreen();
void chooseGame();
void instructionScreen();
void noOfPlayers();
void gameoverScreen(Turn player);
void gameScreen(players *p);
void allHuman(players *first);
void oneVthree(players *first);
void twoVtwo(players *first);
void threeVone(players *first);
void allCPU(players *first);
void playGame();
bool compareSuits(Card b);
Turn stringToPlayer(string s);
Suits stringToSuit(string s);
Face stringToFace(string s);
void endGame();
void saveGame(Turn turn);
bool checkCardFromFile(string face,string suit);
void readSavedGame();
void encryptSavedGame();
void decryptSavedGame();
void switchUserPlayer(players* p);

Card arrCards[52];
bool gameover = false;
bool thulla = false;
Card thrownCard;
Turn gameTurn;
string player1Name = "Player1";
string player2Name = "Player2";
string player3Name = "Player3";
string player4Name = "Player4";
int noOfUsers;

int main(){
    welcomeScreen();
    //setupDeck();
    //saveGame(highestCardHolder);
    //readSavedGame();
    playGame();
    //saveGame(highestCardHolder);
    //noOfPlayers();
}
void setupDeck(){ // create an array of cards that will be distributed to players
    int j=0;
    for(int i=(int)Suits::DIAMOND ; i<=(int)Suits::SPADES ; i++){
        for(int k=(int)Face::TWO ; k<=(int)Face::ACE ; k++){
            Card c;
            c.suit = (Suits)i;
            c.value = (Face)k;
            arrCards[j] = c;
            j++;
        }
    }
    shuffleDeck(); // shuffle the array of cards
    distributeCards(); // add cards to each player's list
}
void shuffleDeck(){ // shuffle deck by using rand and a second array
    int index;
    Card temp[52] = {};
    for(int i=0 ; i<52 ; i++){
        srand(time(0));
        tryagain:
        index = rand()%52;
        if(temp[index].value == NULL && temp[index].suit == NULL){
            temp[index].value = arrCards[i].value;
            temp[index].suit = arrCards[i].suit;
        }
        else{
            goto tryagain;
        }
    }
    for(int i=0 ; i<52 ; i++){
        arrCards[i].value = temp[i].value;
        arrCards[i].suit = temp[i].suit;
    }
}
void displayDeck(){ // only for testing
    string suit,Face;
    int j=0;
    for(int i=(int)Suits::DIAMOND ; i<=(int)Suits::SPADES ; i++){
        for(int k=(int)Face::TWO ; k<=(int)Face::ACE ; k++){
            if(arrCards[j].suit == Suits::DIAMOND){suit = "Diamonds";}
            else if(arrCards[j].suit == Suits::CLUBS){suit = "Clubs";}
            else if(arrCards[j].suit == Suits::HEART){suit = "Hearts";}
            else if(arrCards[j].suit == Suits::SPADES){suit = "Spades";}

            if(arrCards[j].value == Face::ACE){Face = "Ace";}
            else if(arrCards[j].value == Face::TWO){Face = "2";}
            else if(arrCards[j].value == Face::THREE){Face = "3";}
            else if(arrCards[j].value == Face::FOUR){Face = "4";}
            else if(arrCards[j].value == Face::FIVE){Face = "5";}
            else if(arrCards[j].value == Face::SIX){Face = "6";}
            else if(arrCards[j].value == Face::SEVEN){Face = "7";}
            else if(arrCards[j].value == Face::EIGHT){Face = "8";}
            else if(arrCards[j].value == Face::NINE){Face = "9";}
            else if(arrCards[j].value == Face::TEN){Face = "10";}
            else if(arrCards[j].value == Face::JACK){Face = "Jack";}
            else if(arrCards[j].value == Face::QUEEN){Face = "Queen";}
            else if(arrCards[j].value == Face::KING){Face = "King";}
            cout<<j+1<<". "<<Face<<" of "<<suit<<endl;
            j++;
        }
    }
}
string checkSuit(Suits a){ // returns string of suit to be displayed on cli
    string ret;
    if(a == Suits::CLUBS){
        ret = "Clubs";
    }
    else if(a == Suits::DIAMOND){
        ret = "Diamonds";
    }
    else if(a == Suits::HEART){
        ret = "Hearts";
    }
    else if(a == Suits::SPADES){
        ret = "Spades";
    }
    else{
        ret = "";
    }
    return ret;
}
string checkFace(Face f){ // returns string of face to be displayed in cli
    string re;
    if(f == Face::ACE){re = "Ace";}
    else if(f == Face::TWO){re = "2";}
    else if(f == Face::THREE){re = "3";}
    else if(f == Face::FOUR){re = "4";}
    else if(f == Face::FIVE){re = "5";}
    else if(f == Face::SIX){re = "6";}
    else if(f == Face::SEVEN){re = "7";}
    else if(f == Face::EIGHT){re = "8";}
    else if(f == Face::NINE){re = "9";}
    else if(f == Face::TEN){re = "10";}
    else if(f == Face::JACK){re = "Jack";}
    else if(f == Face::QUEEN){re = "Queen";}
    else if(f == Face::KING){re = "King";}
    else{
        re = "";
    }
    return re;
}
string stringPlayer(Turn turn){ // returns string of player to be displayed in cli
    string ret;
    if(turn == Turn::PLAYER1){
        ret = player1Name;
    }
    else if(turn == Turn::PLAYER2){
        ret = player2Name;
    }
    else if(turn == Turn::PLAYER3){
        ret = player3Name;
    }
    else if(turn == Turn::PLAYER4){
        ret = player4Name;
    }
    else{
        ret = "";
    }
    return ret;
}
void distributeCards(){ //add cards from array to list of each player
    for(int i=0 ; i<52 ; i++){
        if(i>=0 && i<13){
            insertCardP1(arrCards[i]);
        }
        else if(i>=13 && i<26){
            insertCardP2(arrCards[i]);
        }
        else if(i>=26 && i<39){
            insertCardP3(arrCards[i]);
        }
        else if(i>=39 && i<52){
            insertCardP4(arrCards[i]);
        }
    }
}
//------------------------------------------------------------------------
//                          Linked List Functions
//------------------------------------------------------------------------

//  INSERT

void insertCardP1(Card c){ // linked list insert function
    if(P1first == NULL){
		P1n = new P1();
		P1n->card = c;
		P1n->next = NULL;
		P1first = P1last = P1n;
	}
	else{
		P1n = new P1();
		P1n->card = c;
		P1n->next = P1first;
		P1first = P1n;
	}
}

void insertCardP2(Card c){
    if(P2first == NULL){
		P2n = new P2();
		P2n->card = c;
		P2n->next = NULL;
		P2first = P2last = P2n;
	}
	else{
		P2n = new P2();
		P2n->card = c;
		P2n->next = P2first;
		P2first = P2n;
	}
}

void insertCardP3(Card c){
    if(P3first == NULL){
		P3n = new P3();
		P3n->card = c;
		P3n->next = NULL;
		P3first = P3last = P3n;
	}
	else{
		P3n = new P3();
		P3n->card = c;
		P3n->next = P3first;
		P3first = P3n;
	}
}

void insertCardP4(Card c){
    if(P4first == NULL){
		P4n = new P4();
		P4n->card = c;
		P4n->next = NULL;
		P4first = P4last = P4n;
	}
	else{
		P4n = new P4();
		P4n->card = c;
		P4n->next = P4first;
		P4first = P4n;
	}
}
void showCardsP1(){// display cards on console
    P1temp = P1first;
    int i=1;
	while(P1temp->next != NULL){
		cout<<i<<". "<<checkFace(P1temp->card.value)<<" of "<<checkSuit(P1temp->card.suit)<<endl;
		P1temp = P1temp->next;
		i++;
		if(i == 21){
            break;
		}
	}
	cout<<i<<". "<<checkFace(P1temp->card.value)<<" of "<<checkSuit(P1temp->card.suit)<<endl;
}
void showCardsP2(){
    P2temp = P2first;
	int i=1;
	while(P2temp->next != NULL){
		cout<<i<<". "<<checkFace(P2temp->card.value)<<" of "<<checkSuit(P2temp->card.suit)<<endl;
		P2temp = P2temp->next;
		i++;
		if(i == 21){
            break;
		}
	}

	cout<<i<<". "<<checkFace(P2temp->card.value)<<" of "<<checkSuit(P2temp->card.suit)<<endl;
}
void showCardsP3(){
    P3temp = P3first;
	int i=1;
	while(P3temp->next != NULL){
		cout<<i<<". "<<checkFace(P3temp->card.value)<<" of "<<checkSuit(P3temp->card.suit)<<endl;
		P3temp = P3temp->next;
		i++;
		if(i == 21){
            break;
		}
	}
	cout<<i<<". "<<checkFace(P3temp->card.value)<<" of "<<checkSuit(P3temp->card.suit)<<endl;
}
void showCardsP4(){
    P4temp = P4first;
    int i=1;
	while(P4temp->next != NULL){
		cout<<i<<". "<<checkFace(P4temp->card.value)<<" of "<<checkSuit(P4temp->card.suit)<<endl;
		P4temp = P4temp->next;
		i++;
		if(i == 21){
            break;
		}
	}
	cout<<i<<". "<<checkFace(P4temp->card.value)<<" of "<<checkSuit(P4temp->card.suit)<<endl;
}
int lengthOfP1(){ // to display how many cards a player holds
    P1* p = P1first;
	int total = 1;
	while(p->next != NULL)
	{
		total++;
		p=p->next;
	}
	return total;
}
int lengthOfP2(){
    P2* p = P2first;
	int total=1;
	while(p->next != NULL)
	{
		total++;
		p=p->next;
	}
	return total;
}
int lengthOfP3(){
    P3* p = P3first;
	int total=1;
	while(p->next != NULL)
	{
		total++;
		p=p->next;
	}
	return total;
}
int lengthOfP4(){
    P4* p = P4first;
	int total=1;
	while(p->next != NULL)
	{
		total++;
		p=p->next;
	}
	return total;
}
Card removeCardP1(int index){//used to remove cards from a player
    P1temp = P1first;
    P1* p = P1first;
    Card ret;
    int i=0;
    if(index == 1){
        ret = P1first->card;
        P1first = P1first->next;
    }
    else{
        for(int i=0 ; i<index-2 ; i++){
            P1temp = P1temp->next;
        }
        for(int i=0 ; i<=index-2 ; i++){
            p = p->next;
        }
        ret = p->card;
        P1temp->next = p->next;
    }
    return ret;
}
Card removeCardP2(int index){
    P2temp = P2first;
    P2* p = P2first;
    Card ret;
    int i=0;
    if(index == 1){
        ret = P2first->card;
        P2first = P2first->next;
    }
    else{
        for(int i=0 ; i<index-2 ; i++){
            P2temp = P2temp->next;
        }
        for(int i=0 ; i<=index-2 ; i++){
            p = p->next;
        }
        ret = p->card;
        P2temp->next = p->next;
    }
    return ret;
}
Card removeCardP3(int index){
    P3temp = P3first;
    P3* p = P3first;
    Card ret;
    int i=0;
    if(index == 1){
        ret = P3first->card;
        P3first = P3first->next;
    }
    else{
        for(int i=0 ; i<index-2 ; i++){
            P3temp = P3temp->next;
        }
        for(int i=0 ; i<=index-2 ; i++){
            p = p->next;
        }
        ret = p->card;
        P3temp->next = p->next;
    }
    return ret;
}
Card removeCardP4(int index){
    P4temp = P4first;
    P4* p = P4first;
    Card ret;
    int i=0;
    if(index == 1){
        ret = P4first->card;
        P4first = P4first->next;
    }
    else{
        for(int i=0 ; i<index-2 ; i++){
            P4temp = P4temp->next;
        }
        for(int i=0 ; i<=index-2 ; i++){
            p = p->next;
        }
        ret = p->card;
        P4temp->next = p->next;
    }
    return ret;
}
Card peekCardP1(int index){// see card from list but not remove it
    P1* p = P1first;
    for(int i=1 ; i<index ; i++){p = p->next;}
    return p->card;
}
Card peekCardP2(int index){
    P2* p = P2first;
    for(int i=1 ; i<index ; i++){p = p->next;}
    return p->card;
}
Card peekCardP3(int index){
    P3* p = P3first;
    for(int i=1 ; i<index ; i++){p = p->next;}
    return p->card;
}
Card peekCardP4(int index){
    P4* p = P4first;
    for(int i=1 ; i<index ; i++){p = p->next;}
    return p->card;
}
//------------------------------------------------------------------------
//                          Stack Functions
//------------------------------------------------------------------------
Card popCardFromStack(){// to pop card from stack
    Card ret;
    if(pile.top > -1){
        ret = pile.pileCard[pile.top];
        pile.top--;
    }
    return ret;
}
void pushCardToStack(Card c){// insert card in stack
    if(pile.top < 3){
        pile.top++;
        pile.pileCard[pile.top] = c;
    }
}
void trashPile(){ //empty pile
    pile.top=-1;
}
void emptyPileToPlayer(){// empty the stack into a player
    cout<<"empty pile start";
    if(thulla_1){
        while(pile.top > -1){
            cout<<"player 1 check";
            insertCardP1(popCardFromStack());
        }
    }
    else if(thulla_2){
        while(pile.top > -1){
                cout<<"player 2 check";
            insertCardP2(popCardFromStack());
        }
    }
    else if(thulla_3){
        while(pile.top > -1){
                cout<<"player 3 check";
            insertCardP3(popCardFromStack());
        }
    }
    else if(thulla_4){
        while(pile.top > -1){
                cout<<"player 4 check";
            insertCardP4(popCardFromStack());
        }
    }
    cout<<"empty pile end";
}
Card peekTopCard(){
    return pile.pileCard[pile.top];
}
void pileTopCardPrint(){
    cout<<checkFace(pile.pileCard[pile.top].value)<<" of "<<checkSuit(pile.pileCard[pile.top].suit)<<endl;
}
void viewStack(){
    int tempTop = pile.top;
    int i = 0;
    while(tempTop > -1){
        i++;
        gotoxy(55,10+(i-1));
        cout<<i<<". "<<checkFace(pile.pileCard[tempTop].value)<<" of "<<checkSuit(pile.pileCard[tempTop].suit)<<endl;
        tempTop--;
    }
}
//--------------------------------------------------------------------
//                          Game Functions
//--------------------------------------------------------------------
void checkhighestCard(){
    if(pile.top == 0){
        highestCard = &pile.pileCard[pile.top];
    }
    else if(pile.top>=1 && pile.top<=3){
        if(highestCard->value < pile.pileCard[pile.top].value){
            highestCard = &pile.pileCard[pile.top];
        }
    }
}
void computerTurn(Turn turn){
    int possibleCardIndex = -1;
    int index = 1;
    bool firstTurn = false;
    Card tempHighCard;
    if(turn == Turn::PLAYER1){
        P1* p = P1first;
        tempHighCard.value = p->card.value;
        while(p != NULL)
        {
            if(pile.top == -1){
                srand(time(0));
                possibleCardIndex = rand()%lengthOfP1() + 1;
                firstTurn = true;
                break;
            }
            else{
                if(p->card.value > tempHighCard.value){ //checking highest card held
                    tempHighCard.value = p->card.value;
                }
                if(highestCard->suit == p->card.suit){
                    if(p->card.value < highestCard->value){
                        possibleCardIndex = index;
                    }
                    else if(possibleCardIndex == -1 && p->card.value > highestCard->value){
                        possibleCardIndex = index;
                    }
                }
            }
            p = p->next;
            index++;
        }
        if(!firstTurn){
            if(possibleCardIndex == -1){
                p = P1first;
                index = 1;
                while(p != NULL){
                    if(tempHighCard.value == p->card.value){
                        possibleCardIndex = index;
                        break;
                    }
                    p=p->next;
                    index++;
                }
            }
            if(!compareSuits(peekCardP1(possibleCardIndex))){
                prevHighestCardHolder = highestCardHolder;
            }
            else if(peekCardP2(possibleCardIndex).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER1;
            }
        }
        if(firstTurn){
            prevHighestCardHolder = Turn::PLAYER1;
            highestCardHolder = Turn::PLAYER1;
        }
        thrownCard = peekCardP1(possibleCardIndex);
        pushCardToStack(removeCardP1(possibleCardIndex));
    }
    else if(turn == Turn::PLAYER2){
        P2* p = P2first;
        tempHighCard.value = p->card.value;
        while(p != NULL)
        {
            if(pile.top == -1){
                srand(time(0));
                possibleCardIndex = rand()%lengthOfP2() + 1;
                firstTurn = true;
                break;
            }
            else{
                if(p->card.value > tempHighCard.value){ //checking highest card held
                    tempHighCard.value = p->card.value;
                }
                if(highestCard->suit == p->card.suit){
                    if(p->card.value < highestCard->value){
                        possibleCardIndex = index;
                    }
                    else if(possibleCardIndex == -1 && p->card.value > highestCard->value){
                        possibleCardIndex = index;
                    }
                }
            }
            p = p->next;
            index++;
        }
        if(!firstTurn){
            if(possibleCardIndex == -1){
                p = P2first;
                index = 1;
                while(p != NULL){
                    if(tempHighCard.value == p->card.value){
                        possibleCardIndex = index;
                        break;
                    }
                    p=p->next;
                    index++;
                }
            }
            if(!compareSuits(peekCardP2(possibleCardIndex))){
                prevHighestCardHolder = highestCardHolder;
            }
            else if(peekCardP2(possibleCardIndex).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER2;
            }
        }
        if(firstTurn){
            prevHighestCardHolder = Turn::PLAYER2;
            highestCardHolder = Turn::PLAYER2;
        }
        thrownCard = peekCardP2(possibleCardIndex);
        pushCardToStack(removeCardP2(possibleCardIndex));
    }
    else if(turn == Turn::PLAYER3){
        P3* p = P3first;
        tempHighCard.value = p->card.value;
        while(p != NULL)
        {
            if(pile.top == -1){
                srand(time(0));
                possibleCardIndex = rand()%lengthOfP3() + 1;
                firstTurn = true;
                break;
            }
            else{
                if(p->card.value > tempHighCard.value){ //checking highest card held
                    tempHighCard.value = p->card.value;
                }
                if(highestCard->suit == p->card.suit){
                    if(p->card.value < highestCard->value){
                        possibleCardIndex = index;
                    }
                    else if(possibleCardIndex == -1 && p->card.value > highestCard->value){
                        possibleCardIndex = index;
                    }
                }
            }
            p=p->next;
            index++;
        }
        if(!firstTurn){
            if(possibleCardIndex == -1){
                p = P3first;
                index = 1;
                while(p != NULL){
                    if(tempHighCard.value == p->card.value){
                        possibleCardIndex = index;
                        break;
                    }
                    p=p->next;
                    index++;
                }
            }
            if(!compareSuits(peekCardP3(possibleCardIndex))){
            prevHighestCardHolder = highestCardHolder;
            }
            else if(peekCardP3(possibleCardIndex).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER3;
            }
        }
        if(firstTurn){
            prevHighestCardHolder = Turn::PLAYER3;
            highestCardHolder = Turn::PLAYER3;
        }
        thrownCard = peekCardP3(possibleCardIndex);
        pushCardToStack(removeCardP3(possibleCardIndex));
    }
    else if(turn == Turn::PLAYER4){
        P4* p = P4first;
        tempHighCard.value = p->card.value;
        while(p != NULL)
        {
            if(pile.top == -1){
                srand(time(0));
                possibleCardIndex = rand() % lengthOfP4() + 1;
                firstTurn = true;
                break;
            }
            else{
                if(p->card.value > tempHighCard.value){ //checking highest card held
                    tempHighCard.value = p->card.value;
                }
                if(highestCard->suit == p->card.suit){
                    if(p->card.value < highestCard->value){
                        possibleCardIndex = index;
                    }
                    else if(possibleCardIndex == -1 && p->card.value > highestCard->value){
                        possibleCardIndex = index;
                    }
                }
            }
            p=p->next;
            index++;
        }
        if(!firstTurn){
            if(possibleCardIndex == -1){
                p = P4first;
                index = 1;
                while(p != NULL){
                    if(tempHighCard.value == p->card.value){
                        possibleCardIndex = index;
                        break;
                    }
                    p=p->next;
                    index++;
                }
            }
            if(!compareSuits(peekCardP4(possibleCardIndex))){
                prevHighestCardHolder = highestCardHolder;
            }
            else if(peekCardP4(possibleCardIndex).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER4;

            }
        }
        if(firstTurn){
            prevHighestCardHolder = Turn::PLAYER4;
            highestCardHolder = Turn::PLAYER4;
        }
        thrownCard = peekCardP4(possibleCardIndex);
        pushCardToStack(removeCardP4(possibleCardIndex));
    }
}
bool checkThulla(){
    bool ret = false;
    if(pile.top == 0){
        ret = false;
    }
    else if(pile.pileCard[pile.top].suit != pile.pileCard[pile.top-1].suit){
        ret = true;
        if(highestCardHolder == Turn::PLAYER1){
            thulla_1 = true;
        }
        else if(highestCardHolder == Turn::PLAYER2){
            thulla_2 = true;
        }
        else if(highestCardHolder == Turn::PLAYER3){
            thulla_3 = true;
        }
        else if(highestCardHolder == Turn::PLAYER4){
            thulla_4 = true;
        }
    }
    return ret;
}
bool compareSuits(Card b){
    if(b.suit == highestCard->suit){
        return true;
    }
    else{
        return false;
    }
}
void userTurn(Turn turn){
    Card c;
    bool haveCard = false;
    int index=1;
    if(turn == Turn::PLAYER1){
        gotoxy(0,26);
        cout<<"\nEnter the Index of the card you want to throw : ";
        cin>>index;
        if(index < 1 || index > lengthOfP1()){
            userTurn(turn);
        }
        if(highestCard != NULL){
            for(int i=0 ; i<lengthOfP1() ; i++){
                if(compareSuits(peekCardP1(i))){
                    haveCard = true;
                    break;
                }
                else{
                    haveCard = false;
                }
            }
            c = peekCardP1(index);
            if(haveCard){
                if(c.suit != highestCard->suit){
                    userTurn(turn);
                }
            }
        }
        if(highestCard == NULL){
            c = peekCardP1(index);
            highestCard = &c;
            highestCardHolder = Turn::PLAYER1;
        }
        if(!compareSuits(peekCardP1(index))){
            prevHighestCardHolder = highestCardHolder;
        }
        else{
            if(peekCardP1(index).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER1;
            }
        }
        thrownCard = peekCardP1(index);
        pushCardToStack(removeCardP1(index));
    }
    else if(turn == Turn::PLAYER2){
        again2:
        gotoxy(0,26);
        cout<<"\nEnter the Index of the card you want to throw : ";
        cin>>index;
        if(index < 1 || index > lengthOfP2()){
            userTurn(turn);
        }
        if(highestCard != NULL){
            for(int i=0 ; i<lengthOfP2() ; i++){
                if(compareSuits(peekCardP2(i))){
                    haveCard = true;
                    break;
                }
                else{
                    haveCard = false;
                }
            }
            c = peekCardP2(index);
            if(haveCard){
                if(c.suit != highestCard->suit){
                    userTurn(turn);
                }
            }
        }
        if(highestCard == NULL){
            c = peekCardP2(index);
           highestCard = &c;
           highestCardHolder = Turn::PLAYER2;
        }
        if(!compareSuits(peekCardP2(index))){
            prevHighestCardHolder = highestCardHolder;
        }
        else{
            if(peekCardP2(index).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER2;
            }
        }
        thrownCard = peekCardP2(index);
        pushCardToStack(removeCardP2(index));
    }
    else if(turn == Turn::PLAYER3){
        again3:
        gotoxy(0,26);
        cout<<"\nEnter the Index of the card you want to throw : ";
        cin>>index;
        if(index < 1 || index > lengthOfP3()){
            userTurn(turn);
        }
        if(highestCard != NULL){
            for(int i=0 ; i<lengthOfP3() ; i++){
                if(compareSuits(peekCardP3(i))){
                    haveCard = true;
                    break;
                }
                else{
                    haveCard = false;
                }
            }
            c = peekCardP3(index);
            if(haveCard){
                if(c.suit != highestCard->suit){
                    userTurn(turn);
                }
            }
        }
        if(highestCard == NULL){
            c = peekCardP3(index);
           highestCard = &c;
           highestCardHolder = Turn::PLAYER3;
        }
        if(!compareSuits(peekCardP3(index))){
            prevHighestCardHolder = highestCardHolder;
        }
        else{
            if(peekCardP3(index).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER3;
            }
        }
        thrownCard = peekCardP3(index);
        pushCardToStack(removeCardP3(index));
    }
    else if(turn == Turn::PLAYER4){
        again4:
        gotoxy(0,26);
        cout<<"\nEnter the Index of the card you want to throw : ";
        cin>>index;
        if(index < 1 || index > lengthOfP4()){
            userTurn(turn);
        }
        if(highestCard != NULL){
            for(int i=0 ; i<lengthOfP4() ; i++){
                if(compareSuits(peekCardP4(i))){
                    haveCard = true;
                    break;
                }
                else{
                    haveCard = false;
                }
            }
            c = peekCardP4(index);
            if(haveCard){
                if(c.suit != highestCard->suit){
                    userTurn(turn);
                }
            }
        }
        if(highestCard == NULL){
            c = peekCardP4(index);
           highestCard = &c;
           highestCardHolder = Turn::PLAYER4;
        }
        if(!compareSuits(peekCardP4(index))){
            prevHighestCardHolder = highestCardHolder;
        }
        else{
            if(peekCardP4(index).value > highestCard->value){
                prevHighestCardHolder = highestCardHolder;
                highestCardHolder = Turn::PLAYER4;
            }
        }
        thrownCard = peekCardP4(index);
        pushCardToStack(removeCardP4(index));
    }
}
void gotoxy(int column,int line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
void welcomeScreen(){
    system("cls");
    int i=5;
    gotoxy(25,3);
    cout<<"Bhabhi Thulla";
    gotoxy(27,i);
    cout<<"Made By:";
    gotoxy(26,i+1);
    cout<<"Adil Zafar";
    gotoxy(25,i+2);
    cout<<"Muneeb Zahid";
    gotoxy(24,i+3);
    cout<<"Talha Shafique";
    gotoxy(20,11);
    cout<<"Press 1 to play game.";
    gotoxy(18,12);
    cout<<"Press 2 for instructions.";
    char input;
    input = getch();
    if(input == '1'){
        noOfPlayers();
        setupDeck();
    }
    else if(input == '2'){
        instructionScreen();
    }
    else{
        welcomeScreen();
    }
}
void instructionScreen(){
    system("cls");
    cout<<"\n\n\t\tInstructions:\n";
    cout<<"\n1. All 4 Players will be dealt 13 Cards.";
    cout<<"\n\n2. First Turn Will be yours.";
    cout<<"\n\n3. In each round of turns, Players will throw card of the same suit as the first card.";
    cout<<"\n\n4. Whoever throws the largest card, will throw the first card in the next round.";
    cout<<"\n\n5. If a player does not have a card of the same suit, they can throw any other card\n   and the person who had thrown the highest card will pickup the pile.";
    cout<<"\n\n6. The player who picks up the pile will throw the first card in the next round.";
    cout<<"\n\n7. Whoever throws all their cards first will win";
    cout<<"\n\n8. If you are playing MULTIPLAYER, pass the computer to the next player after you\n   have entered the index of your card.";
    cout<<"\n\nPress 1 to go back to main screen.";

    char in;
    in = getch();
    if(in == '1'){
        welcomeScreen();
    }
    else{
        instructionScreen();
    }
}
void noOfPlayers(){
    system("cls");
    int n;
    gotoxy(20,10);
    cout<<"Please enter the number of Human Players(0-4): ";
    cin>>n;
    if(n<0 || n>4){
        noOfPlayers();
    }
    else{
        noOfUsers = n;
    }
    system("cls");
    gotoxy(20,10);
    if(n == 1){
        cout<<"Enter name of Player 1: ";
        cin>>player1Name;
    }
    else if(n == 2){
        cout<<"Enter name of Player 1: ";
        cin>>player1Name;
        system("cls");
        gotoxy(20,10);
        cout<<"Enter name of Player 2: ";
        cin>>player2Name;
    }
    else if(n == 3){
        cout<<"Enter name of Player 1: ";
        cin>>player1Name;
        system("cls");
        gotoxy(20,10);
        cout<<"Enter name of Player 2: ";
        cin>>player2Name;
        system("cls");
        gotoxy(20,10);
        cout<<"Enter name of Player 3: ";
        cin>>player3Name;
    }
    else if(n == 4){
        cout<<"Enter name of Player 1: ";
        cin>>player1Name;
        system("cls");
        gotoxy(20,10);
        cout<<"Enter name of Player 2: ";
        cin>>player2Name;
        system("cls");
        gotoxy(20,10);
        cout<<"Enter name of Player 3: ";
        cin>>player3Name;
        system("cls");
        gotoxy(20,10);
        cout<<"Enter name of Player 4: ";
        cin>>player4Name;
    }
}
void gameoverScreen(Turn player){
    system("cls");
    gotoxy(20,8);
    cout<<"GAME OVER!!!";
    gotoxy(20,10);
    cout<<stringPlayer(player)<<" WON";
    Sleep(3000);
    gotoxy(0,15);
}
void gameScreen(players *p){
    gotoxy(42,0);
    if(highestCard ==NULL){
        cout<<"Highest Card: ";
    }
    else{cout<<"Highest Card: "<<checkFace(highestCard->value)<<" of "<<checkSuit(highestCard->suit);}
    gotoxy(42,1);
    cout<<"Highest Card Holder: "<<stringPlayer(highestCardHolder);
    gotoxy(42,3);
    cout<<player1Name<<" Cards: "<<lengthOfP1();
    gotoxy(42,4);
    cout<<player2Name<<" Cards: "<<lengthOfP2();
    gotoxy(42,5);
    cout<<player3Name<<" Cards: "<<lengthOfP3();
    gotoxy(42,6);
    cout<<player4Name<<" Cards: "<<lengthOfP4();
    gotoxy(42,10);
    if(pile.top == -1){
        cout<<"Card on Top: No card in Stack";
    }
    else{
        //cout<<"Card on Top: "<<checkFace(peekTopCard().value)<<" of "<<checkSuit(peekTopCard().suit);
        cout<<"Card on Top: ";
        viewStack();
    }
    gotoxy(42,15);
    cout<<"Status: ";
    gotoxy(42,16);
    cout<<getStatus(p);
    gotoxy(0,2);
    if(noOfUsers == 1){
        cout<<player1Name<<" Cards: \n";
        showCardsP1();
    }
    else if(noOfUsers == 2){
        if(p->turn == Turn::PLAYER1){
            cout<<player1Name<<" Cards: \n";
            showCardsP1();
        }
        else if(p->turn == Turn::PLAYER2){
            cout<<player2Name<<" Cards: \n";
            showCardsP2();
        }
    }
    else if(noOfUsers == 3){
        if(p->turn == Turn::PLAYER1){
            cout<<player1Name<<" Cards: \n";
            showCardsP1();
        }
        else if(p->turn == Turn::PLAYER2){
            cout<<player2Name<<" Cards: \n";
            showCardsP2();
        }
        else if(p->turn == Turn::PLAYER3){
            cout<<player3Name<<" Cards: \n";
            showCardsP3();
        }
    }
    else if(noOfUsers == 4 || noOfUsers == 0){
        if(p->turn == Turn::PLAYER1){
            cout<<player1Name<<" Cards: \n";
            showCardsP1();
        }
        else if(p->turn == Turn::PLAYER2){
            cout<<player2Name<<" Cards: \n";
            showCardsP2();
        }
        else if(p->turn == Turn::PLAYER3){
            cout<<player3Name<<" Cards: \n";
            showCardsP3();
        }
        else if(p->turn == Turn::PLAYER4){
            cout<<player4Name<<" Cards: \n";
            showCardsP4();
        }
    }
    for(int i=0 ; i<25 ; i++){
        gotoxy(40,i);
        cout<<"|";
    }
    gotoxy(0,25);
    cout<<"Turn : "<<stringPlayer(p->turn);
}
string getStatus(players* p){
    string ret;
    if(thulla){
        ret = stringPlayer(prevHighestCardHolder) + " ko thulla par gaya";
    }
    else if(pile.top == -1){
        ret = "Pile Trashed";
    }
    else{
        ret = stringPlayer(p->prev->turn)+ " threw " + checkFace(thrownCard.value) + " of " + checkSuit(thrownCard.suit);
    }
    return ret;
}
void allHuman(players *first){
    int turn = 0;
        while(turn !=4){
            gameTurn = first->turn;

            switchUserPlayer(first);

            userTurn(first->turn);

            checkhighestCard();
            first = first->nextTurn;
            if(checkThulla()){
                emptyPileToPlayer();
                thulla = true;
                break;
            }
            turn++;
            cout<<"\nPress any key to continue";
            char c = getch();
            if(c == 27){
                endGame();
            }
        }
        if(!thulla){
            trashPile();
        }
        else{
            emptyPileToPlayer();
        }
}
void oneVthree(players *first){
    int turn = 0;
        while(turn !=4){
            gameTurn = first->turn;
            if(first->turn == Turn::PLAYER1){
                switchUserPlayer(first);
                userTurn(first->turn);
            }
            else{
                system("cls");
                gameScreen(first);

                computerTurn(first->turn);
            }
            checkhighestCard();
            first = first->nextTurn;
            if(checkThulla()){
                emptyPileToPlayer();
                thulla = true;
                break;
            }
            turn++;
            cout<<"\nPress any key to continue";
            char c = getch();
            if(c == 27){
                endGame();
            }
        }
        if(!thulla){
            trashPile();
        }
}
void twoVtwo(players *first){
    int turn = 0;
        while(turn !=4){
            gameTurn = first->turn;
            if(first->turn == Turn::PLAYER1 || first->turn == Turn::PLAYER2){
                switchUserPlayer(first);
                userTurn(first->turn);
            }
            else{
                system("cls");
                gameScreen(first);
                computerTurn(first->turn);
            }
            checkhighestCard();
            first = first->nextTurn;
            if(checkThulla()){
                emptyPileToPlayer();
                thulla = true;
                break;
            }
            turn++;
            cout<<"\nPress any key to continue";
            char c = getch();
            if(c == 27){
                endGame();
            }
        }
        if(!thulla){
            trashPile();
        }
}
void threeVone(players *first){
    int turn = 0;
        while(turn !=4){
            gameTurn = first->turn;
            if(first->turn == Turn::PLAYER4){
                system("cls");
                gameScreen(first);
                computerTurn(first->turn);
            }
            else{
                switchUserPlayer(first);
                gameScreen(first);
                userTurn(first->turn);
            }
            checkhighestCard();
            first = first->nextTurn;
            if(checkThulla()){
                emptyPileToPlayer();
                thulla = true;
                break;
            }
            turn++;
            cout<<"\nPress any key to continue";
            char c = getch();
            if(c == 27){
                endGame();
            }
        }
        if(!thulla){
            trashPile();
        }
}
void allCPU(players *first){
    int turn = 0;
        while(turn !=4){
            gameTurn = first->turn;

            system("cls");
            gameScreen(first);

            computerTurn(first->turn);

            checkhighestCard();
            first = first->nextTurn;
            if(checkThulla()){
                emptyPileToPlayer();
                thulla = true;
                break;
            }
            turn++;

            system("cls");
            gameScreen(first);

            cout<<"\nPress any key to continue";
            char c = getch();
            if(c == 27){
                endGame();
            }
        }
        if(!thulla){
            trashPile();
        }
}
void playGame(){
    players play1,play2,play3,play4;
    players *first ,*temp;
    play1.turn = Turn::PLAYER1;
    play1.nextTurn = &play2;
    play1.prev = &play4;
    play2.turn = Turn::PLAYER2;
    play2.nextTurn = &play3;
    play2.prev = &play1;
    play3.turn = Turn::PLAYER3;
    play3.nextTurn = &play4;
    play3.prev = &play2;
    play4.turn = Turn::PLAYER4;
    play4.nextTurn = &play1;
    play4.prev = &play3;

    first = &play1;
    char c;

    while(!gameover){
        cout<<"\nPress any key to continue";
        c = getch();
        if(c == 27){
            endGame();
        }
        thulla = false;
        prevHighestCardHolder = highestCardHolder;

        if(noOfUsers == 1){
            oneVthree(first);
        }
        else if(noOfUsers == 2){
            twoVtwo(first);
        }
        else if(noOfUsers == 3){
            threeVone(first);
        }
        else if(noOfUsers == 4){
            allHuman(first);
        }
        else{
            allCPU(first);
        }

        thulla_1 = false;
        thulla_2 = false;
        thulla_3 = false;
        thulla_4 = false;

        highestCard = NULL;
        if(highestCardHolder == Turn::PLAYER1){first = &play1;}
        else if(highestCardHolder == Turn::PLAYER2){first = &play2;}
        else if(highestCardHolder == Turn::PLAYER3){first = &play3;}
        else if(highestCardHolder == Turn::PLAYER4){first = &play4;}

        if(lengthOfP1() == 0){gameover = true; gameoverScreen(PLAYER1);}
        else if(lengthOfP2() == 0){gameover = true; gameoverScreen(PLAYER2);}
        else if(lengthOfP3() == 0){gameover = true; gameoverScreen(PLAYER3);}
        else if(lengthOfP4() == 0){gameover = true; gameoverScreen(PLAYER4);}
    }
}
Turn stringToPlayer(string s){
    if(s == "Player1"){
        return Turn::PLAYER1;
    }
    else if(s == "Player2"){
        return Turn::PLAYER2;
    }
    else if(s == "Player3"){
        return Turn::PLAYER3;
    }
    else if(s == "Player4"){
        return Turn::PLAYER4;
    }
}
Suits stringToSuit(string s){
    if(s == "Diamonds"){
        return Suits::DIAMOND;
    }
    else if(s == "Hearts"){
        return Suits::HEART;
    }
    else if(s == "Clubs"){
        return Suits::CLUBS;
    }
    else if(s == "Spades"){
        return Suits::SPADES;
    }
}
Face stringToFace(string s){
    if(s == "2"){return Face::TWO;}
    else if(s == "3"){return Face::THREE;}
    else if(s == "4"){return Face::FOUR;}
    else if(s == "5"){return Face::FIVE;}
    else if(s == "6"){return Face::SIX;}
    else if(s == "7"){return Face::SEVEN;}
    else if(s == "8"){return Face::EIGHT;}
    else if(s == "9"){return Face::NINE;}
    else if(s == "10"){return Face::TEN;}
    else if(s == "Jack"){return Face::JACK;}
    else if(s == "Queen"){return Face::QUEEN;}
    else if(s == "King"){return Face::KING;}
    else if(s == "Ace"){return Face::ACE;}
}
void endGame(){
    cout<<"Are you sure you want to end the game. ";
    cout<<"Press ESC again to end";
    char c = getch();
    if(c == 27){
        exit(0);
    }
}
void switchUserPlayer(players* p){
    system("cls");
    gotoxy(15,10);
    cout<<"Please pass the computer to "<<stringPlayer(p->turn);
    getch();
    system("cls");
    gameScreen(p);
}
