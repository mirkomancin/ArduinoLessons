**
* Uses internal pullups to read 4 pushbutton states,
* Comunicate the state of the buttons using serial interface
*/

#define IN1 2  // fire 
#define IN2 3  // right
#define IN3 4  // up
#define IN4 5  // left
#define IN5 6  // down

int state1 = HIGH;
int state2 = HIGH;
int state3 = HIGH;
int state4 = HIGH;
int state5 = HIGH;

void setup() {
  Serial.begin(9600);
  
  pinMode(IN1, INPUT);
  digitalWrite(IN1, HIGH); // enable pullup resitor
  
  pinMode(IN2, INPUT);
  digitalWrite(IN2, HIGH); // enable pullup resitor
  
  pinMode(IN3, INPUT);
  digitalWrite(IN3, HIGH); // enable pullup resitor
  
  pinMode(IN4, INPUT);
  digitalWrite(IN4, HIGH); // enable pullup resitor
  
  pinMode(IN5, INPUT);
  digitalWrite(IN5, HIGH); // enable pullup resitor
}

void loop() {
  delay(10); // debounces switches
  
  int val1 = digitalRead(IN1);
  int val2 = digitalRead(IN2);
  int val3 = digitalRead(IN3);
  int val4 = digitalRead(IN4);
  int val5 = digitalRead(IN5);
  
  // check if we had a change in state
  if(state1 != val1 || state2 != val2 || state3 != val3 || state4 != val4 || state5 != val5) { 
    state1 = val1; 
    state2 = val2;
    state3 = val3; 
    state4 = val4;
    state5 = val5;
    
    /* 
    we create a 8 bit word (1 byte) whose 5 right bit represent
    from right to left buttons fire, right, up, left, down status: 
    0 if pressed, 1 if not pressed
    remaining bits are unused
    
    I'm not that expert in bit operations, there's probably a
    better way (faster) to do the following.
    */
    unsigned int state = (val5 << 4) | (val4 << 3) | (val3 << 2) | (val2 << 1) | val1 ;
    
    Serial.print(state, BYTE);
  }
}