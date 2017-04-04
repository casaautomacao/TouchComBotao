#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;      
#include <TouchScreen.h>

uint8_t YP = A1;  
uint8_t XM = A2;  
uint8_t YM = 7;   
uint8_t XP = 6;   
uint8_t SwapXY = 0;

uint16_t TS_LEFT = 913;
uint16_t TS_RT  = 174;
uint16_t TS_TOP = 831;
uint16_t TS_BOT = 209;

int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 1; 

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;
#define MINPRESSURE 1
#define MAXPRESSURE 1000

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

bool valor_botao1 = 0;
bool valor_botao2 = 0;
bool valor_botao3 = 0;
bool valor_botao4 = 0;
const int ledPin = 53;
const int ledPin1 = 51;
const int ledPin2= 49;

void show_tft(void)
{
    tft.setCursor(50, 10);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.print(F("Testando LCD"));
    
    tft.setCursor(20,65);
    tft.setTextColor(BLUE);
    tft.setTextSize(3);
    tft.print("LAMPADA 1");
    tft.drawRoundRect(5, 50, 312, 50, 5, BLUE);

    tft.setCursor(20,129);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.print("LAMPADA 2");
    tft.drawRoundRect(5, 114, 312, 50, 5, GREEN);

    tft.setCursor(20,193);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.print("LAMPADA 3");
    tft.drawRoundRect(5, 180, 312, 50, 5, RED);

    // Preenchimento OFF

  tft.setTextColor(WHITE);
  tft.fillRoundRect(250, 50, 67, 50, 5, RED);
  tft.fillRoundRect(250, 114, 67, 50, 5, RED); 
  tft.fillRoundRect(250, 180, 67, 50, 5, RED);
  tft.setCursor(260, 65);
  tft.println("OFF");
  tft.setCursor(260, 129);
  tft.println("OFF");
  tft.setCursor(260, 193);
  tft.println("OFF");
          
    }

void setup(void) {

    uint16_t tmp;
    tft.begin(9600);
    tft.reset();
    identifier = tft.readID();

    ts = TouchScreen(XP, YP, XM, YM, 300); 
    tft.begin(identifier);
    tft.setRotation(Orientation);
    tft.fillScreen(WHITE);
    show_tft();
    
    pinMode(ledPin, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
}

void loop() {

   uint16_t xpos, ypos;  
    tp = ts.getPoint(); 
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);

   if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
      xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
      ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());

      if (ypos > 200 & ypos < 300)
      {
      
      // Teste da Lampada 1
      
      if (xpos > 90 & xpos < 150)
      {
        if (valor_botao1 == 0)
        {
          tft.fillRoundRect(250, 50, 67, 50, 5, GREEN);
          mostra_on(269, 65);
          valor_botao1 = !valor_botao1;
          digitalWrite(ledPin, HIGH);
        }
        else
        {
          tft.fillRoundRect(250, 50, 67, 50, 5, RED);
          mostra_off(260, 65);
          valor_botao1 = !valor_botao1;
          digitalWrite(ledPin, LOW);
        }
      }

      // Teste da Lampada 2

      if (xpos > 180 & xpos < 220)
      {
        if (valor_botao2 == 0)
        {
          tft.fillRoundRect(250, 114, 67, 50, 5, GREEN);
          mostra_on(269, 128);
          valor_botao2 = !valor_botao2;
          digitalWrite(ledPin1, HIGH);
        }
        else
        {
          tft.fillRoundRect(250, 114, 67, 50, 5, RED);
          mostra_off(260, 128);
          valor_botao2 = !valor_botao2;
          digitalWrite(ledPin1, LOW);
        }
      }

    // Teste da Lampada 3
      if (xpos > 240 & xpos < 320)
      {
        if (valor_botao3 == 0)
        {
          tft.fillRoundRect(250, 180, 67, 50, 5, GREEN);
          mostra_on(269, 190);
          valor_botao3 = !valor_botao3;
          digitalWrite(ledPin2, HIGH);
        }
        else
        {
          tft.fillRoundRect(250, 180, 67, 50, 5, RED);
          mostra_off(260, 190);
          valor_botao3 = !valor_botao3;
          digitalWrite(ledPin2, LOW);
        }
      }


      
      }
    }
}

void mostra_on(int x, int y)
{
  tft.setTextColor(BLACK);
  tft.setCursor(x, y);
  tft.println("ON");
  delay(100);
}
  
void mostra_off(int x, int y)
{
  tft.setTextColor(WHITE);
  tft.setCursor(x, y);
  tft.println("OFF");
  delay(100);
}
