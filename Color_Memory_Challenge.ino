/*
 * Color Memory Challenge Game
 * 
 * A Simon-style memory game using Arduino with:
 * - 4 LEDs (different colors)
 * - 4 push buttons
 * - 4 resistors (for the LEDs)
 * - Buzzer
 * 
 * Game rules:
 * - Arduino will flash a sequence of colors
 * - Player must repeat the sequence by pressing the corresponding buttons
 * - Game gets progressively harder by adding one more color to the sequence
 * - Game ends when player makes a mistake
 */

// Define pins for LEDs, buttons, and buzzer
const int RED_LED = 2;
const int GREEN_LED = 3;
const int BLUE_LED = 4;
const int YELLOW_LED = 5;

const int RED_BUTTON = 6;
const int GREEN_BUTTON = 7;
const int BLUE_BUTTON = 8;
const int YELLOW_BUTTON = 9;

const int BUZZER = 10;

// Game variables
int gameSequence[100]; // Stores the sequence of colors
int gameIndex = 0;     // Current position in the sequence
int inputIndex = 0;    // Player's current position in the sequence
int gameLevel = 1;     // Current level (sequence length)
int maxLevel = 20;     // Maximum level to reach

// Tone frequencies for each color
const int RED_TONE = 262;    // C4
const int GREEN_TONE = 330;  // E4
const int BLUE_TONE = 392;   // G4
const int YELLOW_TONE = 494; // B4

// Game state
enum GameState {
  WAITING,
  SEQUENCE_DISPLAY,
  PLAYER_INPUT,
  GAME_OVER,
  GAME_WON
};

GameState currentState = WAITING;

void setup() {
  // Initialize LED pins as outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  
  // Initialize button pins as inputs with pull-up resistors
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  
  // Initialize buzzer pin as output
  pinMode(BUZZER, OUTPUT);
  
  // Initialize random seed for generating random sequences
  randomSeed(analogRead(A0));
  
  // Serial for debugging
  Serial.begin(9600);
  Serial.println("Color Memory Challenge Game");
  Serial.println("Press any button to start the game");
  
  // Turn off all LEDs initially
  allLedsOff();
}

void loop() {
  switch (currentState) {
    case WAITING:
      waitForStart();
      break;
    case SEQUENCE_DISPLAY:
      displaySequence();
      break;
    case PLAYER_INPUT:
      getPlayerInput();
      break;
    case GAME_OVER:
      gameOverAnimation();
      break;
    case GAME_WON:
      gameWonAnimation();
      break;
  }
}

void waitForStart() {
  // Check if any button is pressed to start the game
  if (!digitalRead(RED_BUTTON) || !digitalRead(GREEN_BUTTON) || 
      !digitalRead(BLUE_BUTTON) || !digitalRead(YELLOW_BUTTON)) {
    
    // Welcome tone
    tone(BUZZER, 440, 200);
    delay(200);
    tone(BUZZER, 554, 200);
    delay(200);
    tone(BUZZER, 659, 200);
    delay(200);
    
    // Reset game variables
    gameIndex = 0;
    inputIndex = 0;
    gameLevel = 1;
    
    // Generate the first random color
    gameSequence[0] = random(1, 5); // 1=RED, 2=GREEN, 3=BLUE, 4=YELLOW
    
    Serial.println("Game started!");
    
    delay(1000); // Small delay before showing the sequence
    currentState = SEQUENCE_DISPLAY;
  }
}

void displaySequence() {
  Serial.print("Level ");
  Serial.print(gameLevel);
  Serial.println(" - Watch the sequence");
  
  delay(500); // Small pause before sequence starts
  
  // Show the sequence up to the current level
  for (int i = 0; i < gameLevel; i++) {
    flashLed(gameSequence[i]);
    delay(300); // Delay between colors
  }
  
  // Reset player input index
  inputIndex = 0;
  currentState = PLAYER_INPUT;
  
  Serial.println("Your turn - Repeat the sequence");
}

void getPlayerInput() {
  // Check if any button is pressed
  int pressedButton = checkButtons();
  
  if (pressedButton > 0) {
    // Flash the corresponding LED and play tone
    flashLed(pressedButton);
    
    // Check if the button matches the sequence
    if (pressedButton == gameSequence[inputIndex]) {
      // Correct button pressed
      inputIndex++;
      
      // Check if player completed the current sequence
      if (inputIndex == gameLevel) {
        delay(500);
        
        // Success tone
        tone(BUZZER, 659, 100);
        delay(150);
        tone(BUZZER, 784, 100);
        
        // Move to next level
        gameLevel++;
        inputIndex = 0;
        
        // Check if player won the game
        if (gameLevel > maxLevel) {
          currentState = GAME_WON;
        }
        else {
          // Generate next color in sequence
          gameSequence[gameLevel-1] = random(1, 5);
          delay(1000);
          currentState = SEQUENCE_DISPLAY;
        }
      }
    }
    else {
      // Wrong button pressed, game over
      Serial.println("Wrong button! Game over.");
      currentState = GAME_OVER;
    }
    
    // Small debounce delay
    delay(200);
  }
}

int checkButtons() {
  if (!digitalRead(RED_BUTTON)) return 1;
  if (!digitalRead(GREEN_BUTTON)) return 2;
  if (!digitalRead(BLUE_BUTTON)) return 3;
  if (!digitalRead(YELLOW_BUTTON)) return 4;
  return 0; // No button pressed
}

void flashLed(int color) {
  switch (color) {
    case 1: // RED
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, RED_TONE, 300);
      delay(300);
      digitalWrite(RED_LED, LOW);
      break;
    case 2: // GREEN
      digitalWrite(GREEN_LED, HIGH);
      tone(BUZZER, GREEN_TONE, 300);
      delay(300);
      digitalWrite(GREEN_LED, LOW);
      break;
    case 3: // BLUE
      digitalWrite(BLUE_LED, HIGH);
      tone(BUZZER, BLUE_TONE, 300);
      delay(300);
      digitalWrite(BLUE_LED, LOW);
      break;
    case 4: // YELLOW
      digitalWrite(YELLOW_LED, HIGH);
      tone(BUZZER, YELLOW_TONE, 300);
      delay(300);
      digitalWrite(YELLOW_LED, LOW);
      break;
  }
}

void allLedsOff() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
}

void gameOverAnimation() {
  // Game over sound
  tone(BUZZER, 392, 200);
  delay(200);
  tone(BUZZER, 349, 200);
  delay(200);
  tone(BUZZER, 330, 200);
  delay(200);
  tone(BUZZER, 294, 400);
  
  // Flash all LEDs quickly
  for (int i = 0; i < 5; i++) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    delay(100);
    allLedsOff();
    delay(100);
  }
  
  Serial.print("Game over! You reached level ");
  Serial.println(gameLevel);
  Serial.println("Press any button to start a new game");
  
  delay(1000);
  currentState = WAITING;
}

void gameWonAnimation() {
  Serial.println("Congratulations! You won the game!");
  
  // Victory melody
  int winMelody[] = {392, 392, 392, 311, 466, 392, 311, 466, 392};
  int winDuration[] = {100, 100, 100, 100, 300, 100, 100, 300, 500};
  
  for (int i = 0; i < 9; i++) {
    tone(BUZZER, winMelody[i], winDuration[i]);
    
    // Light show during victory melody
    int ledToLight = i % 4 + 1;
    flashLed(ledToLight);
    delay(winDuration[i]);
  }
  
  delay(1000);
  Serial.println("Press any button to start a new game");
  currentState = WAITING;
}
