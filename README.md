# Bhabhi Thulla - Card Game

A console-based implementation of the popular Pakistani card game "Bhabhi Thulla" written in C++.

## About the Game

Bhabhi Thulla is a traditional Pakistani trick-taking card game played with a standard 52-card deck. The objective is to be the first player to get rid of all your cards. The game involves strategy, as players must follow suit when possible, and the concept of "thulla" (penalty) adds an exciting twist to the gameplay.

## Features

- **Multiple Game Modes**: Support for 0-4 human players (remaining slots filled by AI)
- **AI Opponents**: Intelligent computer players with strategic decision-making
- **Console Interface**: Text-based UI with positioned output using Windows console functions
- **Game State Management**: Track cards, turns, and game statistics
- **Interactive Gameplay**: Clear prompts and game status updates

## Game Rules

1. All 4 players are dealt 13 cards each from a standard 52-card deck
2. The first player starts by throwing any card
3. Other players must throw a card of the same suit if they have one
4. The player with the highest card of the leading suit wins the round
5. If a player doesn't have the required suit, they can throw any card (this creates a "thulla")
6. The player who threw the winning card starts the next round
7. When a "thulla" occurs, the previous round winner collects all cards in the pile
8. The first player to empty their hand wins the game

## System Requirements

- **Operating System**: Windows (uses Windows-specific console functions)
- **Compiler**: C++ compiler with support for C++11 or later
- **Dependencies**: 
  - `windows.h` (for console manipulation)
  - `conio.h` (for keyboard input)
  - Standard C++ libraries

## Compilation and Execution

### Using g++ (MinGW)
```bash
g++ -o bhabhi_thulla "bhabhiThulla 1.5.cpp"
./bhabhi_thulla.exe
```

### Using Visual Studio
1. Create a new C++ project
2. Add the source file to the project
3. Build and run (Ctrl+F5)

### Using Dev-C++
1. Open the .cpp file
2. Press F9 to compile and run

## How to Play

1. **Start the Game**: Run the executable and choose option 1 from the main menu
2. **Select Players**: Choose the number of human players (0-4)
3. **Enter Names**: Provide names for human players
4. **Game Interface**: 
   - Your cards are displayed on the left
   - Game status and other players' card counts on the right
   - Enter the index number of the card you want to play
5. **Pass and Play**: In multiplayer mode, pass the computer to the next player after your turn
6. **Win Condition**: First player to play all cards wins

## Game Controls

- **Numbers (1-13)**: Select card to play by entering its index
- **Any Key**: Continue to next turn
- **ESC**: Pause/exit game (press twice to confirm)
- **1/2**: Navigate main menu (Play/Instructions)

## Code Structure

### Key Components

- **Card Structure**: Represents individual playing cards with Face and Suit
- **Player Lists**: Separate linked lists for each player's cards (P1-P4)
- **Game Stack**: Array-based stack for the current round's played cards
- **Turn Management**: Circular linked list for managing player turns
- **AI Logic**: Computer players with strategic card selection

### Main Functions

- `setupDeck()`: Initialize and shuffle the deck
- `distributeCards()`: Deal cards to all players
- `userTurn()`: Handle human player input
- `computerTurn()`: AI decision making
- `checkThulla()`: Detect penalty conditions
- `playGame()`: Main game loop

## Authors

- **Adil Zafar** (FA21-BSE-004)
- **Muneeb Zahid** (FA21-BSE-091)  
- **Talha Shafique** (FA21-BSE-152)

## Technical Notes

- Uses Windows console API for cursor positioning and screen clearing
- Implements custom linked lists for card management
- Strategic AI considers suit requirements and card values
- Memory management through dynamic allocation for card nodes

## Known Limitations

- Windows-only compatibility due to console API usage
- Text-based interface only
- No save/load game functionality (code exists but is commented out)
- Fixed to 4 players total (human + AI combination)

---

*This project was developed as part of an academic assignment demonstrating data structures (linked lists, stacks) and game programming concepts in C++.*
