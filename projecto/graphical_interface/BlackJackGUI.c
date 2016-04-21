  #include <SDL2/SDL.h>
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_image.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <time.h>
  #include <stdbool.h>

  #define STRING_SIZE 100       // max size for some strings
  #define WIDTH_WINDOW 900      // window width
  #define HEIGHT_WINDOW 525     // window height
  #define MAX_DECK_SIZE 52      // number of max cards in the deck
  #define MAX_CARD_HAND 11      // 11 cards max. that each player can hold
  #define CARD_WIDTH 67         // card width
  #define CARD_HEIGHT 97        // card height
  #define WINDOW_POSX 500       // initial position of the window: x
  #define WINDOW_POSY 250       // initial position of the window: y
  #define EXTRASPACE 150
  #define MARGIN 5
  #define MAX_PLAYERS 4         // number of maximum players

  // declaration of the functions related to graphical issues
  void InitEverything(int , int , TTF_Font **, SDL_Surface **, SDL_Window ** , SDL_Renderer ** );
  void InitSDL();
  void InitFont();
  SDL_Window* CreateWindow(int , int );
  SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
  int RenderText(int , int , const char* , TTF_Font *, SDL_Color *, SDL_Renderer * );
  int RenderLogo(int , int , SDL_Surface *, SDL_Renderer * );
  void RenderTable(int ,int [], int [], int [], TTF_Font *, SDL_Surface **, SDL_Renderer * );
  void RenderCard(int , int , int , SDL_Surface **, SDL_Renderer * );
  void RenderHouseCards(int [], int , SDL_Surface **, SDL_Renderer * );
  void RenderPlayerCards(int [][MAX_CARD_HAND], int [], SDL_Surface **, SDL_Renderer * );
  void LoadCards(SDL_Surface **);
  void UnLoadCards(SDL_Surface **);

  // Config, init and game reset
  void setConfig(int *, int *, int *); //Set the config params
  void beginGame(int [], int * , int [], int [], int [][MAX_CARD_HAND], int , int [], int , int , int [], int *);
  void resetGame(int *, int [], int [], int [][MAX_CARD_HAND], int *, int [], int *, int [], int *, int *, int []); //RESETS the game
  // Deck ops
  void createDeck(int [], int); //Creates a deck with 52*numDecks elements
  void shuffleDeck(int [], int); //Shuffles the deck
  // Card ops
  void dealCards(int [], int * , int *, int []); //Deal cards to the players
  int getCardValue(int , int []);
  int getHandValue(int [], int , int []);
  // Player actions
  void stand(int *);
  void hit(int [], int * , int * , int [], int * , int [], int []);
  // Check cases and attribute functions
  int checkSpecialCase(int [], int , int []);
  int checkBlackjack(int [], int , int []);
  int getHigherScore(int []);
  int countPlayersAtr(int []);
  // File/Stats functions
  void writeStats(const char *[], int [][3], int [], int []);

  //Graphical functions
  void RenderPlayerBox(int [], char [],int , int , SDL_Renderer* , SDL_Color , SDL_Color , TTF_Font *);
  void RenderHouseBox(int , char [], int , int ,  SDL_Renderer* , SDL_Color , SDL_Color , TTF_Font *);
  void RenderPlayerValue(int [][MAX_CARD_HAND], int [], int [], SDL_Renderer* , TTF_Font *);
  void RenderHouseValue(int [], int , int [], SDL_Renderer* , TTF_Font *);

  // definition of some strings: they cannot be changed when the program is executed !
  const char myName[] = "Miguel Borges Freire";
  const char myNumber[] = "IST425445";
  const char * playerNames[] = {"Player 1", "Player 2", "Player 3", "Player 4"};


  /**
   * main function: entry point of the program
   * only to invoke other functions !
   */
  int main( int argc, char* args[] )
  {
      SDL_Window *window = NULL; //SDL Window
      SDL_Renderer *renderer = NULL;//Renderer
      TTF_Font *serif = NULL; // Text font
      SDL_Surface *cards[MAX_DECK_SIZE+1], *imgs[2]; //Card texture
      SDL_Event event; //Event var
      SDL_Color winnersColor = {255,255,255,255}; //Winners text color
      SDL_Color bustColor = {255,0,0,255}; //Bust text color
      SDL_Color winnersBoxColor = {0,255,0,255}; //Winners box color
      SDL_Color bustBoxColor = {164,164,164,255}; //Bust box color
      int delay = 300; //Delay
      int quit = 0; //Quit game?
      int money[MAX_PLAYERS] = {110, 110, 110, 110}; //Players Money array
      int house_money[MAX_PLAYERS] = {0}; //House that money earns/lost to each player
  	  int player_cards[MAX_PLAYERS][MAX_CARD_HAND] = {{0}}; //Players cards
      int house_cards[MAX_CARD_HAND] = {0}; //House cards
      int pos_house_hand = 0; //House hand
      int pos_player_hand[MAX_PLAYERS] = {0}; //Players' Hands
      int turn = 0; //Check who's playing
      int playersBust[MAX_PLAYERS] = {0}; //Player Bust array
      int houseBust = 0; // House bust var
      int playersHandValue[MAX_PLAYERS] = {0}; //Players hand value
      int houseHandValue = 0; //House hand value
      int playersOut[MAX_PLAYERS] = {0}; //Players out of the game
      int winners[MAX_PLAYERS+1] = {0}; //Winners: (0:3) -> players, 4 -> house
      int higher_score = 0; // The most valuable hand in the game
      int tied=0; // Are house and player tied?
      /*Player stats:
      [i][0] -> Games Won,
      [i][1] -> Games Tied,
      [i][2] -> Games Lost
      */
      int stats[4][3] = {{0}};

      int cardsValue[52] = {2,3,4,5,6,7,8,9,10,10,10,10,11, //Array with the value for each card. Ace can value 1 or 11 but
                           2,3,4,5,6,7,8,9,10,10,10,10,11,  //thats only evaluated on the dealing function
                           2,3,4,5,6,7,8,9,10,10,10,10,11,
                           2,3,4,5,6,7,8,9,10,10,10,10,11};

      int numDecks=0 , SeedMoney=0, BetValue=0; //Game settings
      srand(456); //Set the shuffle seed
      setConfig(&numDecks, &SeedMoney, &BetValue); //Setting of user configs

      int deck[52*numDecks]; //Create the deck array
      int deckCounter=0; //Deck Counter, it counts the cards dealt
      createDeck(deck, numDecks);    //Create house deck, it fills the deck array from 0 to 51 numDecks times
      for(int m = 0; m < MAX_PLAYERS; m++) {
        money[m] = SeedMoney; //Set the initial money for each player
      }
      beginGame(deck, &pos_house_hand, house_cards, pos_player_hand, player_cards, SeedMoney, money, BetValue, numDecks, playersOut, &deckCounter); //Starts the game!

  	  //initialize graphics
  	  InitEverything(WIDTH_WINDOW, HEIGHT_WINDOW, &serif, imgs, &window, &renderer);
      // loads the cards images
      LoadCards(cards);

   	  while( quit == 0 ) {
        /*************
        The game flows through a variable called turn.
        Turn can have values between 0 and 7, each value represents a different stage in the game:
        0 -> Player 1 turn to play
        1 -> Player 2 turn to play
        2 -> Player 3 turn to play
        3 -> Player 4 turn to play
        4 -> House turn to play
        5 -> Checks who is the winner and handles the bets
        6 -> Waiting stage. It starts a new game (turn=0) when the user presses the N key
        7 -> Game Over Stage. When all the players are out of money and none of them can play the house wins
        *************/
        if(countPlayersAtr(playersOut) == 4) turn = 7; //If all players are out -> GAME OVER!
        if(turn < 4 && playersOut[turn]) turn++; //If the player is out of the game pass the turn to the next player

        //TURN 4: House turn to play
        if(turn==4) {
          if(pos_house_hand == 1) pos_house_hand=2; //Turns house's face down card up
          houseHandValue = getHandValue(house_cards, pos_house_hand, cardsValue);

          if(houseHandValue >= 17) { // If the house has a hand value >= than 17 it stands
          if(houseHandValue > 21) houseBust=1; //If it's > 21 it busts
          stand(&turn);
        }
        else if(houseHandValue <= 16) { // If house has a hand value <= to 16, hit until => 17
          dealCards(house_cards, &pos_house_hand, &deckCounter, deck);
          houseHandValue = getHandValue(house_cards, pos_house_hand, cardsValue);
        }
        else if(checkSpecialCase(house_cards, pos_house_hand, cardsValue)) { //If house has 1 ace plus cards that value 6, hit once!
          dealCards(house_cards, &pos_house_hand, &deckCounter, deck);
        }
      }
       //TURN 5: Check who wins and updates money
      if(turn==5) {
        for(int i = 0; i < MAX_PLAYERS; i++) { //Get the players hand value
          if(playersOut[i]) continue; //If the player is out of the game, just grab the next one
          playersHandValue[i] = getHandValue(player_cards[i], pos_player_hand[i], cardsValue);
        }

        if(houseBust) { //if house has bust, every non-bust player recieves twice the bet value.
          for(int v = 0; v < MAX_PLAYERS; v++) {
            if(!(playersBust[v] || playersOut[v])) {
              money[v] += 2*BetValue;
              winners[v] = 1;
              house_money[v] -= BetValue;
              stats[v][0]++;
            }
          }
        }
        else { //House does not has bust, we need to compare to the players to see who wins
          if(!checkBlackjack(house_cards, pos_house_hand, cardsValue)) { //If house doenst have blackjack
            for(int j = 0; j < MAX_PLAYERS; j++) {
              //if the player has blackjack in the 1st 2 cards he recieves 1.5 times the bet value
              if(checkBlackjack(player_cards[j], 2, cardsValue) && !playersBust[j] && !playersOut[j]) {
                money[j] += 1.5*BetValue;
                house_money[j] -= 1.5*BetValue;
                winners[j] = 1;
              }
            }
           } else { //If house has blackjack
             for(int j = 0; j < MAX_PLAYERS; j++) {
               //And the player doenst have blackjack, house collects the bet
               if(!checkBlackjack(player_cards[j], pos_player_hand[j], cardsValue) && !playersOut[j]) {
                 house_money[j] += BetValue;
               }
             }
           }

           for(int m = 0; m < MAX_PLAYERS; m++) {
             higher_score = getHigherScore(playersHandValue);
             if(playersHandValue[m] == higher_score && higher_score > houseHandValue && !playersOut[m]) {
               money[m] += BetValue;
               stats[m][0]++; //Player Won!
               winners[m] = 1;
             }
             else if((playersHandValue[m] < higher_score && !playersOut[m]) || playersBust[m]) {
               house_money[m] += BetValue;
               stats[m][2]++; //Player Lost!
             }
             else if(playersHandValue[m] == houseHandValue && !playersBust[m] && !playersOut[m]) {
               tied=1;
               stats[m][1]++; //Player Tied!
             }
             if((houseHandValue >= higher_score) && !houseBust && !tied) winners[4] = 1;
           }

         }

         SDL_Delay(delay*2);

         turn++;
       }

        while( SDL_PollEvent( &event ) )
        {
    			if( event.type == SDL_QUIT )
                {
                    quit = 1;
                }
    			else if ( event.type == SDL_KEYDOWN )
    			{
    				switch ( event.key.keysym.sym )
    				{
    					case SDLK_s: //When the player press the S key (stand)
                if(turn > 3 || (turn < 4 && playersOut[turn])) break; //After all players have played disable stand control
                stand(&turn);
                break;
    					case SDLK_h: //When the player press the H key (hit)
                if(turn > 3 || (turn < 4 && playersOut[turn])) break; //After all players have played disable hit control
                hit(player_cards[turn], &pos_player_hand[turn], &turn, playersBust, &deckCounter, deck, cardsValue);
    						break;
              case SDLK_n: //When the player press the N key (new game)
                if(turn < 5 || turn == 7) break; //The player can only start a new game when all cards have been dealt and there are players in game
                  for(int i = 0; i <= MAX_PLAYERS; i++) { //Check if a player has money to bet for next round if not is out!
                    if(money[i] < BetValue) {
                      playersOut[i]=1;
                    }
                 }
                //Reset all game vars!
                resetGame(&pos_house_hand, house_cards, pos_player_hand, player_cards, &turn, playersBust, &houseBust, playersHandValue, &houseHandValue, &deckCounter, winners);
                //Start new game!
                beginGame(deck, &pos_house_hand, house_cards, pos_player_hand, player_cards, SeedMoney, money, BetValue, numDecks, playersOut, &deckCounter);
                break;
              case SDLK_q: //When the player presses Q, he quits the game
                quit = 1;
                break;
    					default:
    						break;
    				}
    			}
        }
          // render game table
          RenderTable(turn, winners, money, playersOut, serif, imgs, renderer);
          // render house cards
          RenderHouseCards(house_cards, pos_house_hand, cards, renderer);
          // render player cards
          RenderPlayerCards(player_cards, pos_player_hand, cards, renderer);
          // render player boxes: bust and winner
          RenderPlayerBox(playersBust, "BUST", 55, 12, renderer, bustBoxColor, bustColor, serif);
          RenderPlayerBox(winners, "WINNER!", 42, 12, renderer, winnersBoxColor, winnersColor, serif);
          // render house box: bust and winner
          RenderHouseBox(houseBust, "BUST", 55, 12, renderer, bustBoxColor, bustColor, serif);
          RenderHouseBox(winners[4], "WINNER!", 42, 12, renderer, winnersBoxColor, winnersColor, serif);
          //render player and house hand values
          RenderPlayerValue(player_cards, pos_player_hand, cardsValue, renderer, serif);
          RenderHouseValue(house_cards, pos_house_hand, cardsValue, renderer, serif);
          // render in the screen all changes above
          SDL_RenderPresent(renderer);
      	  // add a delay
  		    SDL_Delay( delay );
      }
      // free memory allocated for images and textures and close everything including fonts
    UnLoadCards(cards);
    TTF_CloseFont(serif);
    SDL_FreeSurface(imgs[0]);
    SDL_FreeSurface(imgs[1]);
    SDL_DestroyRenderer(renderer);
  	SDL_DestroyWindow(window);
  	SDL_Quit();
    writeStats(playerNames, stats, money, house_money); //Write stats on exit
  	return EXIT_SUCCESS;
  }
  /**
   * [Sets the config of the game]
   * @param numDecks  [number of decks using in the game]
   * @param SeedMoney [starting money for each player]
   * @param BetValue  [bet value]
   * @return void
   */
  void setConfig(int *numDecks, int *SeedMoney, int *BetValue) {
      printf("Número de baralhos?\n");
      int temp;
      while(!scanf("%d", numDecks) || *numDecks < 1 || *numDecks > 6) {
        while((temp=getchar()) != EOF && temp != '\n'); // fixes infinite loop
        printf("Número de decks invalido. Não pode haver mais do que 6 baralhos e menos que 1!\n");
        printf("Número de baralhos?\n");
      }

      printf("Valor de dinheiro inicial?\n");
      while(!scanf("%d", SeedMoney) || *SeedMoney < 10) {
        while((temp=getchar()) != EOF && temp != '\n'); // fixes infinite loop
        printf("O valor do dinheiro inicial não pode ser inferior a 10!\n");
        printf("Valor de dinheiro inicial?\n");
      }

      printf("Valor de aposta?\n");
      while(!scanf("%d", BetValue) || *BetValue < 1 || *BetValue > (0.20 * *SeedMoney)) {
        while((temp=getchar()) != EOF && temp != '\n'); // fixes infinite loop
        printf("Valor de cada aposta não pode ser inferior a 1 nem superior 20%% do dinheiro inicial (%.2f)!\n", 0.20**SeedMoney);
        printf("Valor de aposta?\n");
        scanf("%d", BetValue);
      }

      printf("A iniciar jogo...\n");
  }
  /**
  * Starts a new game
  * @param deck            [game deck]
  * @param pos_house_hand  [house pos_had]
  * @param house_cards     [house cards]
  * @param pos_player_hand [players pos_hand array]
  * @param player_cards    [players' cards array]
  * @param SeedMoney       [Initial money]
  * @param money           [Players' money array]
  * @param BetValue        [Bet value]
  * @param numDecks        [number of decks]
  * @param playersOut      [players' out array]
  * @param deckCounter     [counter of the deck]
  * @return void
  */
  void beginGame(int deck[], int * pos_house_hand, int house_cards[], int pos_player_hand[], int player_cards[][MAX_CARD_HAND], int SeedMoney, int money[], int BetValue, int numDecks, int playersOut[], int *deckCounter)
  {
    shuffleDeck(deck, numDecks);
    for(int i = 0; i < 2; i++) {
          //Set players money and give all of them 1 card
          for(int p = 0; p < MAX_PLAYERS; p++) {
            if(playersOut[p]) continue; //If player is out pass to the next
              if(!i) {
                money[p] -= BetValue;
              }
              dealCards(player_cards[p], &pos_player_hand[p], deckCounter, deck);
          }

          dealCards(house_cards, pos_house_hand, deckCounter, deck);
      }
      if(countPlayersAtr(playersOut)==4) *pos_house_hand=0; //If the players are all out, set the pos_house_hand to 0
      else *pos_house_hand = 1;
  }
  /**
   * Fills the deck array from 0 to 51 numDecks times!
   * @param deck     [house deck]
   * @param numDecks [number of decks]
   * @return void
   */
  void createDeck(int deck[], int numDecks) {
    for(int m = 0; m < numDecks*MAX_DECK_SIZE ; m++) {
        deck[m] = m % MAX_DECK_SIZE;
    }
  }
  /**
   * Shuffles the deck (randomize array)
   * @param deck     [house deck]
   * @param numDecks [number of decks]
   * @return void
   */
  void shuffleDeck(int deck[], int numDecks) {
    int j = 0;
    for(int i = 0; i < numDecks*52; i++) {
      j = rand() % (i+1);
      int t = deck[j];
      deck[j] = deck[i];
      deck[i] = t;
    }
  }
  /**
   * Gives a card to a player or to the house
   * @param cards       [player or house cards array]
   * @param hand        [player or house pos_hand]
   * @param deckCounter [Deck counter]
   * @param deck        [game deck]
   * @return void
   */
  void dealCards(int cards[], int * hand, int *deckCounter, int deck[]) {
      cards[*hand] = deck[*deckCounter];
      (*hand)++;
      (*deckCounter)++;
   }
  /**
  * Resets the game
  * @param pos_house_hand   [house pos_had]
  * @param house_cards      [house cards]
  * @param pos_player_hand  [players pos_hand array]
  * @param player_cards     [players' cards array]
  * @param turn             [game's turn var]
  * @param playersBust      [player's bust array]
  * @param houseBust        [house bust var]
  * @param playersHandValue [player's hand value array]
  * @param houseHandValue   [house hand value]
  * @param deckCounter      [counter of the deck]
  * @param winners          [winners array]
  * @return void
  */
  void resetGame(int *pos_house_hand, int house_cards[], int pos_player_hand[], int player_cards[][MAX_CARD_HAND], int *turn, int playersBust[], int *houseBust, int playersHandValue[], int *houseHandValue, int *deckCounter, int winners[]) {
     for(int i = 0; i < MAX_PLAYERS; i++) {
       for(int j = 0; j < MAX_CARD_HAND; j++) {
         player_cards[i][j] = 0;
         house_cards[j] = 0;
       }
       playersBust[i] = 0;
       playersHandValue[i] = 0;
       pos_player_hand[i] = 0;
      winners[i] = 0;
     }
     winners[4]=0;
     *houseHandValue = 0;
     *pos_house_hand = 0;
     *turn = 0;
     *houseBust = 0;
     *deckCounter=0;
   }
   /**
    * Gets the value of a card
    * @param  card       [card number]
    * @param  cardsValue [cards value array]
    * @return int        [2 <= value of the card <= 11]
    */
  int getCardValue(int card, int cardsValue[]) {
     return cardsValue[card];
   }
  /**
   * Get the value of someones hand
   * @param  hand       [hand/cards of a player or the house]
   * @param  pos_hand   [pos_hand of player/house]
   * @param  cardsValue [cards value array]
   * @return int        [value of the hand]
   */
  int getHandValue(int hand[], int pos_hand, int cardsValue[]) {
     int value = 0;
     int aces = 0;
     int t;
     //Hand total value with ace valuing 11 points
     for(int i = 0; i < pos_hand; i++) {
       t = getCardValue(hand[i], cardsValue);
       if(t == 11) aces++;
       value += t;
       }
    //If bust and if there's aces, turn aces into 1 until value <= 21
     if(aces > 0 && value > 21) {
       for(int k=1; k <= aces; k++) {
         if(value <= 21) break;
         value -= 10;
       }
     }
     return value;
   }
   /**
    * Action: stand!
    * @param turn [players/house turn]
    * @return void
    */
   void stand(int *turn) {
     (*turn)++;
   }
   /**
    * Action: hit!
    * @param cards       [cards of a player/house]
    * @param pos_hand    [pos_hand of a player/house]
    * @param turn        [turn var]
    * @param playersBust [player's bust array]
    * @param deckCounter [deck counter]
    * @param deck        [game deck array]
    * @param cardsValue  [cards value array]
    * @return void
    */
   void hit(int cards[], int * pos_hand, int * turn, int playersBust[], int * deckCounter, int deck[], int cardsValue[]) {
     dealCards(cards, pos_hand, deckCounter, deck);
       if(getHandValue(cards, *pos_hand, cardsValue) > 21) {
         playersBust[*turn] = 1;
         stand(turn);
       }
   }

   /**
    * Checks if the house has one ace and other cards that value 6 points
    * @param  house_cards    [house cards array]
    * @param  pos_house_hand [house's pos_hand]
    * @param  cardsValue     [cards' value array]
    * @return int/bool       [0 -> false, 1 -> true]
    */
   int checkSpecialCase(int house_cards[], int pos_house_hand, int cardsValue[]) {
     if(getHandValue(house_cards, pos_house_hand, cardsValue) == 16) {
       for(int i = 0; i <= pos_house_hand; i++) {
         if(getCardValue(house_cards[i], cardsValue) == 11) return 1;
       }
     }
     return 0;
   }
   /**
    * Check if someone has blackjack
    * @param  cards      [players/house cards array]
    * @param  pos_hand   [players/house pos_hand]
    * @param  cardsValue [cards' value array]
    * @return int/bool      [0 -> false, 1 -> true]
    */
   int checkBlackjack(int cards[], int pos_hand, int cardsValue[]) {
     if(getHandValue(cards, pos_hand, cardsValue) == 21) return 1;
     return 0;
   }
   /**
    * Get the higher score from all players' hands
    * @param  handValue [player's hand value array]
    * @return  int      [the higher value in a players' hand]
    */
   int getHigherScore(int handValue[]) {
     int higher=0;
     for(int i = 0; i < MAX_PLAYERS; i++) {
       if(handValue[i] > higher && handValue[i] <= 21) {
         higher = handValue[i];
       }
     }
     return higher;
   }
   /**
   * Write the game stats to file
   * @param playerNames [array with the name of the players]
   * @param stats_file  [players' stats matrix]
   * @param money       [player's money array]
   * @param house_money [money that house earn/lost from each player]
   * @return void
   */
   void writeStats(const char *playerNames[], int stats[][3], int money[], int house_money[] ) {
     FILE * stats_file;
     stats_file = fopen("stats.txt", "w");
     if(!stats_file) {
       printf("Impossivel abrir o ficheiro!\n");
     }
     for(int i = 0; i < MAX_PLAYERS; i++) {
       fprintf(stats_file, "Player Name: %s\n Games Won/Tied/Lost: %d/%d/%d\n Final money: %d\n House money earned or lost: %d\n\n", playerNames[i], stats[i][0], stats[i][1], stats[i][2], money[i], house_money[i]);
     }
     fclose(stats_file);
   }
   /**
    * Counts how many players have an attribute=1
    * @param  playersAtr [players attribute array]
    * @return int        [number of players with that attribute]
    * eg: players bust is saved in playersBust array, it counts how many players have bust=1
    */
   int countPlayersAtr(int playersAtr[]) {
     int num=0;
     for(int i=0; i < MAX_PLAYERS; i++) {
       if(playersAtr[i]) num++;
     }
     return num;
   }
   /**
   * Render player hand value and if that value = 21 draws BLACKJACK
   * @param cards       [players' cards]
   * @param pos_hand    [players' pos_hand array]
   * @param cardsValue  [cards' values array]
   * @param _renderer   [SDL renderer]
   * @param _font       [SDL font]
   * @return void
   */
   void RenderPlayerValue(int cards[][MAX_CARD_HAND], int pos_hand[], int cardsValue[], SDL_Renderer* _renderer, TTF_Font *_font) {
     SDL_Color white = { 255, 255, 255 }; // black
     SDL_Color red = {255,0,0};
     SDL_Rect bjRect;
     char handValueStr[STRING_SIZE];
     int separatorPos = (int)(0.95f*WIDTH_WINDOW);
     for ( int i = 0; i < MAX_PLAYERS; i++)
     {
       int value = getHandValue(cards[i], pos_hand[i], cardsValue);
         bjRect.x = i*(separatorPos/4-5)+10;
         bjRect.y = (int) (0.55f*HEIGHT_WINDOW);
         bjRect.w = separatorPos/4-5;
         bjRect.h = (int) (0.42f*HEIGHT_WINDOW);
         sprintf(handValueStr,"Value: %d", value);

         RenderText(bjRect.x+20, bjRect.y-50, handValueStr, _font, &white, _renderer);
         if(checkBlackjack(cards[i], pos_hand[i], cardsValue)) RenderText(bjRect.x+100, bjRect.y-50, "BLACKJACK", _font, &red, _renderer);


     }
   }
   /**
   * Render house hand value and if that value = 21 draws BLACKJACK
   * @param cards       [house's cards]
   * @param pos_hand    [house's pos_hand array]
   * @param cardsValue  [cards' values array]
   * @param _renderer   [SDL renderer]
   * @param _font       [SDL font]
   * @return void
   */
   void RenderHouseValue(int cards[], int pos_hand, int cardsValue[], SDL_Renderer* _renderer, TTF_Font *_font) {
     SDL_Color white = { 255, 255, 255 }; // black
     SDL_Color red = {255,0,0};
     SDL_Rect bjRect;
     char handValueStr[STRING_SIZE];
     int value = getHandValue(cards, pos_hand, cardsValue);

     bjRect.x = ((int)(0.95f*WIDTH_WINDOW)/4-5)-120;
     bjRect.y = (int) (0.26f*HEIGHT_WINDOW)+15;
     bjRect.w = 150;
     bjRect.h = 50;
     sprintf(handValueStr,"Value: %d", value);
     RenderText(bjRect.x+590, bjRect.y-15, handValueStr, _font, &white, _renderer);
     if(checkBlackjack(cards, pos_hand, cardsValue)) RenderText(bjRect.x+590, bjRect.y+5, "BLACKJACK", _font, &red, _renderer);

   }
   /**
   * Render a box with a message in the middle of the players' box if some attribute is true
   * @param attributeVector       [players' attribute array to test]
   * @param message               [message to write in the box]
   * @param msgX                  [message X coordinate]
   * @param msgY                  [message Y coordinate]
   * @param _renderer             [SDL renderer]
   * @param boxColor              [color of the box]
   * @param messageColor          [font color/ color of the message]
   * @param _font                 [SDL font]
   * @return void
   */
   void RenderPlayerBox(int attributeVector[], char message[], int msgX, int msgY, SDL_Renderer* _renderer, SDL_Color boxColor, SDL_Color messageColor, TTF_Font *_font) {
     SDL_Rect playerRect;
     int separatorPos = (int)(0.95f*WIDTH_WINDOW);
     for ( int i = 0; i < MAX_PLAYERS; i++)
     {
       if(attributeVector[i]) {
         playerRect.x = i*(separatorPos/4-5)+37;
         playerRect.y = (int) (0.55f*HEIGHT_WINDOW)+80;
         playerRect.w = 150;
         playerRect.h = 50;
         SDL_SetRenderDrawColor(_renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);

         // Render rect
         SDL_RenderFillRect(_renderer, &playerRect);
         RenderText(playerRect.x+msgX, playerRect.y+msgY, message, _font, &messageColor, _renderer);
       }
     }
    }

   /**
   * Render a box with a message in the middle of the players' box if some attribute is true
   * @param attributeVar          [house's attribute to test]
   * @param message               [message to write in the box]
   * @param msgX                  [message X coordinate]
   * @param msgY                  [message Y coordinate]
   * @param _renderer             [SDL renderer]
   * @param boxColor              [color of the box]
   * @param messageColor          [font color/ color of the message]
   * @param _font                 [SDL font]
   * @return void
   */
   void RenderHouseBox(int attributeVar, char message[], int msgX, int msgY,  SDL_Renderer* _renderer, SDL_Color boxColor, SDL_Color messageColor, TTF_Font *_font) {
     SDL_Rect houseRect;
     if(attributeVar) {
         houseRect.x = ((int)(0.95f*WIDTH_WINDOW)/4-5)+120;
         houseRect.y = (int) (0.26f*HEIGHT_WINDOW)+15;
         houseRect.w = 150;
         houseRect.h = 50;
         SDL_SetRenderDrawColor(_renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);

         // Render rect
         SDL_RenderFillRect(_renderer, &houseRect);
         RenderText(houseRect.x+msgX, houseRect.y+msgY, message, _font, &messageColor, _renderer);
     }
   }


  /**
   * RenderTable: Draws the table where the game will be played, namely:
   * -  some texture for the background
   * -  the right part with the IST logo and the student name and number
   * -  squares to define the playing positions of each player
   * -  names and the available money for each player
   * \param _money amount of money of each player
   * \param _img surfaces where the table background and IST logo were loaded
   * \param _renderer renderer to handle all rendering in a window
   */

  void RenderTable(int turn, int winners[], int _money[],int playersOut[], TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer)
  {
      SDL_Color black = { 0, 0, 0 }; // black
      SDL_Color white = { 255, 255, 255 }; // white
      SDL_Color red = { 255, 0, 0 }; //red
      char name_money_str[STRING_SIZE];
      SDL_Texture *table_texture;
      SDL_Rect tableSrc, tableDest, playerRect, outRect, gameOverRect;
      int separatorPos = (int)(0.95f*WIDTH_WINDOW); // seperates the left from the right part of the window
      int height;
      // set color of renderer to some color
      SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );
      // clear the window
      SDL_RenderClear( _renderer );

      tableDest.x = tableSrc.x = 0;
      tableDest.y = tableSrc.y = 0;
      tableSrc.w = _img[0]->w;
      tableSrc.h = _img[0]->h;

      tableDest.w = separatorPos;
      tableDest.h = HEIGHT_WINDOW;

      table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
      SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);
      // render the IST Logo
      height = RenderLogo(separatorPos, 0, _img[1], _renderer);
      // render the student name
      height += RenderText(separatorPos+3*MARGIN, height, myName, _font, &black, _renderer);
      // this renders the student number
      RenderText(separatorPos+3*MARGIN, height, myNumber, _font, &black, _renderer);
      // renders the squares + name for each player
      // Render the rect to the screen
      // renders the areas for each player: names and money too !
      for ( int i = 0; i < MAX_PLAYERS; i++)
      {
        if(turn == i) SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255 );
        else if(winners[i]) SDL_SetRenderDrawColor(_renderer, 201, 151, 40, 255 );
        else SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 150 );
          playerRect.x = i*(separatorPos/4-5)+10;
          playerRect.y = (int) (0.55f*HEIGHT_WINDOW);
          playerRect.w = separatorPos/4-5;
          playerRect.h = (int) (0.42f*HEIGHT_WINDOW);

          if(playersOut[i]) { //Render Players' Out
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(_renderer, playerRect.x, playerRect.y, playerRect.x + playerRect.w, playerRect.y + playerRect.h);
            SDL_RenderDrawLine(_renderer, playerRect.x + playerRect.w, playerRect.y, playerRect.x, playerRect.y + playerRect.h);

            outRect.x = i*(separatorPos/4-5)+37;
            outRect.y = (int) (0.55f*HEIGHT_WINDOW)+80;
            outRect.w = 150;
            outRect.h = 50;
            SDL_SetRenderDrawColor(_renderer, 164, 164, 164, 255 );

            // Render rect
            SDL_RenderFillRect(_renderer, &outRect);
            RenderText(outRect.x+60, outRect.y+12, "OUT", _font, &red, _renderer);
          }

          sprintf(name_money_str,"%s -- %d euros", playerNames[i], _money[i]);
          RenderText(playerRect.x+20, playerRect.y-30, name_money_str, _font, &white, _renderer);
          SDL_RenderDrawRect(_renderer, &playerRect);

      }

      if(turn==7) { //Render Game OVER!
        gameOverRect.x = (tableDest.x + tableDest.w)/2.7;
        gameOverRect.y = (tableDest.y + tableDest.h)/2;
        gameOverRect.w = 215;
        gameOverRect.h = 50;
        SDL_SetRenderDrawColor(_renderer, 164, 164, 164, 255 );

        // Render rect
        SDL_RenderFillRect(_renderer, &gameOverRect);
        RenderText(gameOverRect.x+60, gameOverRect.y+12, "GAME OVER", _font, &red, _renderer);
      }

      // destroy everything
      SDL_DestroyTexture(table_texture);
  }

  /**
   * RenderHouseCards: Renders cards of the house
   * \param _house vector with the house cards
   * \param _pos_house_hand position of the vector _house with valid card IDs
   * \param _cards vector with all loaded card images
   * \param _renderer renderer to handle all rendering in a window
   */
  void RenderHouseCards(int _house[], int _pos_house_hand, SDL_Surface **_cards, SDL_Renderer* _renderer)
  {
      int card, x, y;
      int div = WIDTH_WINDOW/CARD_WIDTH;

      // drawing all house cards
      for ( card = 0; card < _pos_house_hand; card++)
      {
          // calculate its position
          x = (div/2-_pos_house_hand/2+card)*CARD_WIDTH + 15;
          y = (int) (0.26f*HEIGHT_WINDOW);
          // render it !
          RenderCard(x, y, _house[card], _cards, _renderer);
      }
      // just one card ?: draw a card face down
      if (_pos_house_hand == 1)
      {
          x = (div/2-_pos_house_hand/2+1)*CARD_WIDTH + 15;
          y = (int) (0.26f*HEIGHT_WINDOW);
          RenderCard(x, y, MAX_DECK_SIZE, _cards, _renderer);
      }
  }

  /**
   * RenderPlayerCards: Renders the hand, i.e. the cards, for each player
   * \param _player_cards 2D array with the player cards, 1st dimension is the player ID
   * \param _pos_player_hand array with the positions of the valid card IDs for each player
   * \param _cards vector with all loaded card images
   * \param _renderer renderer to handle all rendering in a window
   */
  void RenderPlayerCards(int _player_cards[][MAX_CARD_HAND], int _pos_player_hand[], SDL_Surface **_cards, SDL_Renderer* _renderer)
  {
      int pos, x, y, num_player, card;

      // for every card of every player
      for ( num_player = 0; num_player < MAX_PLAYERS; num_player++)
      {
          for ( card = 0; card < _pos_player_hand[num_player]; card++)
          {
              // draw all cards of the player: calculate its position: only 4 positions are available !
              pos = card % 4;
              x = (int) num_player*((0.95f*WIDTH_WINDOW)/4-5)+(card/4)*12+15;
              y = (int) (0.55f*HEIGHT_WINDOW)+10;
              if ( pos == 1 || pos == 3) x += CARD_WIDTH + 30;
              if ( pos == 2 || pos == 3) y += CARD_HEIGHT+ 10;
              // render it !
              RenderCard(x, y, _player_cards[num_player][card], _cards, _renderer);
          }
      }
  }

  /**
   * RenderCard: Draws one card at a certain position of the window, based on the card code
   * \param _x X coordinate of the card position in the window
   * \param _y Y coordinate of the card position in the window
   * \param _num_card card code that identifies each card
   * \param _cards vector with all loaded card images
   * \param _renderer renderer to handle all rendering in a window
   */
  void RenderCard(int _x, int _y, int _num_card, SDL_Surface **_cards, SDL_Renderer* _renderer)
  {
      SDL_Texture *card_text;
      SDL_Rect boardPos;

      // area that will be occupied by each card
      boardPos.x = _x;
      boardPos.y = _y;
      boardPos.w = CARD_WIDTH;
      boardPos.h = CARD_HEIGHT;

      // render it !
      card_text = SDL_CreateTextureFromSurface(_renderer, _cards[_num_card]);
      SDL_RenderCopy(_renderer, card_text, NULL, &boardPos);

      // destroy everything
      SDL_DestroyTexture(card_text);
  }

  /**
   * LoadCards: Loads all images of the cards
   * \param _cards vector with all loaded card images
   */
  void LoadCards(SDL_Surface **_cards)
  {
      int i;
      char filename[STRING_SIZE];

       // loads all cards to an array
      for (i = 0 ; i < MAX_DECK_SIZE; i++ )
      {
          // create the filename !
          sprintf(filename, ".//cartas//carta_%02d.png", i+1);
          // loads the image !
          _cards[i] = IMG_Load(filename);
          // check for errors: deleted files ?
          if (_cards[i] == NULL)
          {
              printf("Unable to load image: %s\n", SDL_GetError());
              exit(EXIT_FAILURE);
          }
      }
      // loads the card back
      _cards[i] = IMG_Load(".//cartas//carta_back.jpg");
      if (_cards[i] == NULL)
      {
          printf("Unable to load image: %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
      }
  }


  /**
   * UnLoadCards: unloads all card images of the memory
   * \param _cards vector with all loaded card images
   */
  void UnLoadCards(SDL_Surface **_array_of_cards)
  {
      // unload all cards of the memory: +1 for the card back
      for (int i = 0 ; i < MAX_DECK_SIZE + 1; i++ )
      {
          SDL_FreeSurface(_array_of_cards[i]);
      }
  }

  /**
   * RenderLogo function: Renders the IST Logo on the window screen
   * \param x X coordinate of the Logo
   * \param y Y coordinate of the Logo
   * \param _logoIST surface with the IST logo image to render
   * \param _renderer renderer to handle all rendering in a window
   */
  int RenderLogo(int x, int y, SDL_Surface *_logoIST, SDL_Renderer* _renderer)
  {
  	SDL_Texture *text_IST;
  	SDL_Rect boardPos;

      // space occupied by the logo
  	boardPos.x = x;
  	boardPos.y = y;
  	boardPos.w = _logoIST->w;
  	boardPos.h = _logoIST->h;

      // render it
  	text_IST = SDL_CreateTextureFromSurface(_renderer, _logoIST);
  	SDL_RenderCopy(_renderer, text_IST, NULL, &boardPos);

      // destroy associated texture !
  	SDL_DestroyTexture(text_IST);
  	return _logoIST->h;
  }

  /**
   * RenderText function: Renders the IST Logo on the window screen
   * \param x X coordinate of the text
   * \param y Y coordinate of the text
   * \param text string where the text is written
   * \param font TTF font used to render the text
   * \param _renderer renderer to handle all rendering in a window
   */
  int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
  {
  	SDL_Surface *text_surface;
  	SDL_Texture *text_texture;
  	SDL_Rect solidRect;

  	solidRect.x = x;
  	solidRect.y = y;
      // create a surface from the string text with a predefined font
  	text_surface = TTF_RenderText_Blended(_font,text,*_color);
  	if(!text_surface)
  	{
  	    printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
  	    exit(EXIT_FAILURE);
  	}
      // create texture
  	text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
      // obtain size
  	SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
      // render it !
  	SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);

  	SDL_DestroyTexture(text_texture);
  	SDL_FreeSurface(text_surface);
  	return solidRect.h;
  }

  /**
   * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
   * \param width width in px of the window
   * \param height height in px of the window
   * \param _img surface to be created with the table background and IST logo
   * \param _window represents the window of the application
   * \param _renderer renderer to handle all rendering in a window
   */
  void InitEverything(int width, int height, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer)
  {
      InitSDL();
      InitFont();
      *_window = CreateWindow(width, height);
      *_renderer = CreateRenderer(width, height, *_window);

      // load the table texture
      _img[0] = IMG_Load("table_texture.png");
      if (_img[0] == NULL)
      {
          printf("Unable to load image: %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
      }

      // load IST logo
      _img[1] = SDL_LoadBMP("ist_logo.bmp");
      if (_img[1] == NULL)
      {
          printf("Unable to load bitmap: %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
      }
      // this opens (loads) a font file and sets a size
      *_font = TTF_OpenFont("FreeSerif.ttf", 16);
      if(!*_font)
      {
          printf("TTF_OpenFont: %s\n", TTF_GetError());
          exit(EXIT_FAILURE);
      }
  }

  /**
   * InitSDL: Initializes the SDL2 graphic library
   */
  void InitSDL()
  {
      // init SDL library
  	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
  	{
  		printf(" Failed to initialize SDL : %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
  	}
  }

  /**
   * InitFont: Initializes the SDL2_ttf font library
   */
  void InitFont()
  {
  	// Init font library
  	if(TTF_Init()==-1)
  	{
  	    printf("TTF_Init: %s\n", TTF_GetError());
          exit(EXIT_FAILURE);
  	}
  }

  /**
   * CreateWindow: Creates a window for the application
   * \param width width in px of the window
   * \param height height in px of the window
   * \return pointer to the window created
   */
  SDL_Window* CreateWindow(int width, int height)
  {
      SDL_Window *window;
      // init window
  	window = SDL_CreateWindow( "BlackJack", WINDOW_POSX, WINDOW_POSY, width+EXTRASPACE, height, 0 );
      // check for error !
  	if ( window == NULL )
  	{
  		printf("Failed to create window : %s\n", SDL_GetError());
  		exit(EXIT_FAILURE);
  	}
  	return window;
  }

  /**
   * CreateRenderer: Creates a renderer for the application
   * \param width width in px of the window
   * \param height height in px of the window
   * \param _window represents the window for which the renderer is associated
   * \return pointer to the renderer created
   */
  SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
  {
      SDL_Renderer *renderer;
      // init renderer
  	renderer = SDL_CreateRenderer( _window, -1, 0 );

  	if ( renderer == NULL )
  	{
  		printf("Failed to create renderer : %s", SDL_GetError());
          exit(EXIT_FAILURE);
  	}

  	// set size of renderer to the same as window
  	SDL_RenderSetLogicalSize( renderer, width+EXTRASPACE, height );

  	return renderer;
  }
