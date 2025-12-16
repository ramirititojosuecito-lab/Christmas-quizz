#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


int Contrast = 150; //depends on your screen

int Do = 262;
int re = 294;
int mi = 330;
int fa = 349;
int sol = 392;
int la = 440;
int si = 494;
int do_alto = 523;

// Melodía completa de "Silent Night" adaptada a la escala de Do
int melody[] = {
  Do, Do, sol, sol, la, la, sol,    // "Silent night"
  fa, fa, mi, mi, re, re, Do,      // "Holy night"
  sol, sol, la, la, sol, fa, mi,    // "All is calm"
  re, re, Do, re, mi, fa, Do,      // "All is bright"
  
  sol, sol, sol, fa, mi, re, mi,   // "Round yon Virgin"
  fa, fa, mi, mi, re, re, Do,      // "Mother and child"
  sol, sol, sol, fa, mi, re, mi,   // "Holy infant so tender and mild"
  fa, fa, mi, mi, re, re, Do,      // "Sleep in heavenly peace"
  
  sol, sol, sol, fa, mi, re, mi,   // "Sleep in heavenly peace"
  fa, fa, mi, mi, re, re, Do       // Final
};

int noteDurations[] = {
  400, 400, 400, 400, 400, 400, 600,  // "Silent night"
  400, 400, 400, 400, 400, 400, 600,  // "Holy night"
  400, 400, 400, 400, 400, 400, 600,  // "All is calm"
  400, 400, 400, 400, 400, 400, 600,  // "All is bright"
  
  400, 400, 400, 400, 400, 400, 600,  // "Round yon Virgin"
  400, 400, 400, 400, 400, 400, 600,  // "Mother and child"
  400, 400, 400, 400, 400, 400, 600,  // "Holy infant"
  400, 400, 400, 400, 400, 400, 600,  // "Sleep in heavenly peace"
  
  400, 400, 400, 400, 400, 400, 600,  // "Sleep in heavenly peace"
  400, 400, 400, 400, 400, 400, 600   // Final
};

boolean buttonLeft;
boolean buttonRight;

//Verb forms: PS Past Simple - PP Part Participle - T Translation
String topQuestions[] = {"Te portas bien?", "Te drogas?", "Eres grosero?", "Haces las tareas?", "Compartes?"};
String bottomQuestions[] = {"A)SI  B)NO", "A)SI  B)NO", "A)SI  B)NO", "A)SI  B)NO", "A)SI  B)NO"};
int maxNumQuestions = 5;
int Touch = 8;
int buzzer = 9;
int NumQuestions = 0;
int answers[] = {1, 0, 0, 1, 1};    //1 is correct - 0 is wrong
int score = 0;
int iniciar;
int jugando = 0;
int switch_pin = 2;
int LED1 = 4;
int LED2 = 5;
int switch_state;

void setup()
{
    lcd.backlight();
    pinMode(switch_pin,INPUT);
    pinMode(Touch, INPUT);
    pinMode(9, OUTPUT);  
    pinMode(6, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);             //Introduction welcome
    lcd.print("FELIZ NAVIDAD!");
    lcd.setCursor(0, 1);
    lcd.print("Eres nino bueno?");
    delay(3000);
    lcd.clear();
    lcd.print("Preparate");
    delay(3000);
    lcd.clear();
    lcd.print("Generando");
    lcd.setCursor(0, 1);
    lcd.print("preguntas...");
  for (int i = 0; i < sizeof(melody)/sizeof(int); i++) {
    tone(buzzer, melody[i]);  // Reproducir la nota
    delay(noteDurations[i]);     // Duración de la nota
    noTone(buzzer);           // Detener el sonido
    delay(50);                   // Pequeña pausa entre notas
  }
    lcd.clear();
}

void correctAnswer()
{                                   //Function for correct answers
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sigue asi!");
    delay(2000);
    lcd.clear();
}

void wrongAnswer()
{                                      //Function for Wrong answers
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Trata de mejorar!");
    delay(2000);
    lcd.clear();
}

void showScore()                        //Score on screen
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tu regalo...");
    if (score > 4)                      //LED according to score
    { 
    lcd.setCursor(0, 1);
    lcd.print("Es oro!");
    }
    else if (score = 4)
    {
    lcd.setCursor(0, 1);
    lcd.print("Robux");
    }
     else if (score = 3)
    {    
    lcd.setCursor(0, 1);
    lcd.print("Pizza!");
    }
    else if (score < 3)
    {
    lcd.setCursor(0, 1);
    lcd.print("Carbón :(");
    }
    delay(10000);                       //end of game
}

void loop()
{
    
    buttonLeft = digitalRead(7);         //False button
    buttonRight = digitalRead(13);       //True button

    if (NumQuestions != maxNumQuestions)
    {
        lcd.setCursor(0, 0);                        //display question
        lcd.print(topQuestions[NumQuestions]);
        lcd.setCursor(0, 1);                        //display possible answer
        lcd.print(bottomQuestions[NumQuestions]);

        if (buttonRight == HIGH)                     //if True button is clicked
        {
            if ((answers[NumQuestions]) == 1)       
            {
                digitalWrite(LED1, HIGH);
                tone(buzzer, 200);
                delay(300);
                tone(buzzer, 500);
                correctAnswer();
                NumQuestions++;
                score++;
                delay(1000);
                noTone(buzzer);
                digitalWrite(LED1, LOW);
            }
            else if ((answers[NumQuestions]) == 0)
            {
                digitalWrite(LED2, HIGH);
               tone(buzzer, 400);
                delay(300);
                tone(buzzer, 200);
                wrongAnswer();
                NumQuestions++;
                delay(1000);
                noTone(buzzer);
                digitalWrite(LED2, LOW);
            }
        }
        if (buttonLeft == HIGH)                     //if False button is clicked
        {
            if ((answers[NumQuestions]) == 0)
            {
                 digitalWrite(LED1, HIGH);
              tone(buzzer, 200);
                delay(300);
                tone(buzzer, 500);
                correctAnswer();
                NumQuestions++;
                score++;
                delay(1000);
                noTone(buzzer);
                digitalWrite(LED1, LOW);
            }
            else if ((answers[NumQuestions]) == 1)
            {
                 digitalWrite(LED2, HIGH);
                 tone(buzzer, 400);
                delay(300);
                tone(buzzer, 200);
                wrongAnswer();
                NumQuestions++;
                delay(1000);
                noTone(buzzer);
                digitalWrite(LED2, LOW);
            }
        }
    }
    if (NumQuestions == maxNumQuestions)            //5 questions solved? --> score
    {
        showScore();
    }
}