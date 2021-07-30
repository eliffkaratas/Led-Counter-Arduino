#define led1 6
#define led2 5
#define led3 4
#define led4 3 // define pins 
#define button 2
int button_state=0; // button state for button controls, initial value is 0

void setup()
{
  pinMode(led1,OUTPUT); // input, output modes
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(button,INPUT); 
}

void binaryConverter(int a[], int number){ // 4 bits binary converter for counting numbers 
  for(int i=0; i<4; i++)    
  {    
    a[i] = number % 2;    
    number = number / 2;    
  }    
}

void loop() // loop is running throughout program
{
  if(digitalRead(button) == LOW && (button_state == 0 || button_state == 4 || button_state == 5)){ // if the button is pressed in other operations (button state is 4 or 5) or starting of the program (button state is 0)
    button_state=1; // beginning of the first operation, buton state is 1
    while(button_state == 1){ // contiunity...
      int a[4]; // array for binary converting
      int count1 = 0; // take count for 0-15 and number to use in binary converter
      while(count1<16){ // counting...
        binaryConverter(a,count1); // count is number for binary converter
        digitalWrite(led1,a[0]); // led1 is a[0]
        digitalWrite(led2,a[1]); // led2 is a[1]
        digitalWrite(led3,a[2]); // led3 is a[2]
        digitalWrite(led4,a[3]); // led4 is a[3]
        count1++; // increasing...
        delay(500); // waiting...
        if(digitalRead(button) == LOW && button_state == 1){ // if the button is pressed and program is in first operation
          button_state = 2; // button state is 2
          break; // leave the first operation, break from while
        }
      }
    }
  }
  else if(digitalRead(button) == HIGH && button_state == 2){ // if the button is pressed and the program has just leaved the first operation 
    button_state = 3; // button state is 3
    while(button_state == 3){ // contiunity...
      int a[4]; // array for binary converting
      digitalWrite(led1,0); // turning off all leds before starting second operation
      digitalWrite(led2,0);
      digitalWrite(led3,0);
      digitalWrite(led4,0);
      for(int i = 1; i <= 8; i = i*2){ // for loop to binary converting. Count as 1-2-4-8
        binaryConverter(a,i); // i is number for binary converter
        digitalWrite(led1,a[0]); // led1 is a[0]
        digitalWrite(led2,a[1]); // led2 is a[1]
        digitalWrite(led3,a[2]); // led3 is a[2]
        digitalWrite(led4,a[3]); // led4 is a[3]
        delay(200); // waiting...
        if(digitalRead(button) == LOW && button_state == 3){ // if the button is pressed and program is in second operation's first for loop
          button_state = 4; // button state is 4 to turn back first operation, break from while and for loop
          break; // leave the second operation
        }
      }
      for(int i = 4; i>=2; i = i/2){ // for loop to binary converting. Count as 4-2
        binaryConverter(a,i); // i is number for binary converter
        digitalWrite(led1,a[0]); // led1 is a[0]
        digitalWrite(led2,a[1]); // led2 is a[1]
        digitalWrite(led3,a[2]); // led3 is a[2]
        digitalWrite(led4,a[3]); // led4 is a[3]
        delay(200); // waiting...
        if(digitalRead(button) == LOW && button_state == 3){ // if the button is pressed and program is in second operation's second for loop
          button_state = 5; // button state is 5 to turn back first operation, break from while and for loop
          break; // leave the second operation
        }
      }    
    }
  }
}
