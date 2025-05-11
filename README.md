# Color-Memory-Challenge
## Step-by-Step Wiring Guide for Arduino Color Memory Game

Let me walk you through the process of wiring up this project step-by-step:

### Step 1: Gather Components

First, make sure you have all the necessary components:

- Arduino Uno or compatible board  
- Breadboard  
- 4 LEDs (Red, Green, Blue, Yellow)  
- 4 Push buttons  
- 4 × 220Ω resistors (for LEDs)  
- 1 Piezo buzzer  
- Jumper wires  

### Step 2: Position Components

- Place your Arduino and breadboard side by side  
- Arrange the LEDs on one end of the breadboard, leaving enough space between them  
- Position the four push buttons on another area of the breadboard  
- Keep the buzzer handy for later placement  

### Step 3: Power Connections

Set up power rails:

- Connect Arduino 5V pin to the breadboard's positive (+) rail using a red wire  
- Connect Arduino GND pin to the breadboard's negative (-) rail using a black wire  

This provides power for your components.

### Step 4: LED Connections

Wire up each LED one by one:

#### Red LED:

- Insert the LED into the breadboard with the longer leg (anode) and shorter leg (cathode) in separate rows  
- Connect the anode (longer leg) to **Arduino pin 2**  
- Connect the cathode (shorter leg) to one end of a 220Ω resistor  
- Connect the other end of the resistor to the **GND rail**  

#### Green LED:

- Anode to **Arduino pin 3**  
- Cathode through 220Ω resistor to **GND rail**

#### Blue LED:

- Anode to **Arduino pin 4**  
- Cathode through 220Ω resistor to **GND rail**

#### Yellow LED:

- Anode to **Arduino pin 5**  
- Cathode through 220Ω resistor to **GND rail**

### Step 5: Button Connections

For each push button:

#### Red Button:

- Place on the breadboard so it straddles the center gap  
- One terminal to **Arduino pin 6**  
- Diagonally opposite terminal to **GND**

#### Green Button:

- Arduino pin: **7**  
- GND on diagonally opposite pin  

#### Blue Button:

- Arduino pin: **8**  
- GND on diagonally opposite pin  

#### Yellow Button:

- Arduino pin: **9**  
- GND on diagonally opposite pin  

### Step 6: Buzzer Connection

- Positive terminal (marked with "+" or longer lead) to **Arduino pin 10**  
- Negative terminal to **GND rail**

### Step 7: Final Check

Before powering up:

- Double-check LED orientation: longer leg to Arduino, shorter to resistor  
- Verify all resistors connect LED cathodes to GND  
- Confirm button connections: one to Arduino, one to GND  
- Ensure buzzer polarity: + to pin 10, - to GND  
- Make sure there are no loose wires or shorts  

### Step 8: Upload Code and Test

- Connect Arduino to your computer  
- Upload the game code  
- Press any button to start the game  
- You should see an LED light up and hear a tone  
- Press the matching button to continue the game  

### Troubleshooting Tips:

- **LED not lighting**: Check orientation and resistor wiring  
- **Button not responding**: Double-check pin connections  
- **No sound from buzzer**: Verify polarity and wiring  
- **Multiple LEDs lighting**: Check for shorts or miswiring  
"""
