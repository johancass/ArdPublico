#include <Adafruit_NeoPixel.h>    // Incluimos la librería Adafruit NeoPixel. Esto se hace para poder ejecutar los comandos pertenecientes a esta librería necesarios para poder gobernar la tira led Neo Pixel.

#define BUTTON_PIN   2    // Pin 2 conectado al botón. (Montaje pull-up).

#define PIXEL_PIN    6    // Pin 6 conectado a la tira led. Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 35    // Número de leds (pixels) de la tira led Neo Pixel.

#define Dig7Seg 1

// Para el comando Adafruit_NeoPixel nos encontramos con las siguientes instrucciones, de la página de Adafruit:
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
// Port tanto seleccionamos para el tercer parámetro las opciones NEO_GRB + NEOKHZ800 ya que son válidas para neopixel stick.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
#define Rojo strip.Color(127,   0,   0)
#define Blanco strip.Color(127, 127, 127)
#define Azul strip.Color(0,0,127)
#define Verde strip.Color(0, 255, 0)
#define Off strip.Color(0, 0, 0)

bool oldState = HIGH;    // definimos la variable de estado oldState de tipo booleana y la inicializamos a HIGH.
int showType = 0;    // definimos la variable entera showType.

void setup() {
  pinMode(BUTTON_PIN, INPUT);    // Definimos el pin asociado a BUTTON_PIN como entrada.
  strip.begin();    // con begin inicializamos la tira led.
  strip.show(); // con show actualizamos toda la tira de una sola vez.
}

void loop() {
   Barrido1A1(Rojo, 300);
    delay(100);
    Barrido1A1(Verde, 200);
     delay(1100);
     Barrido1A1(Azul, 100);
     delay(150);
     BarridoCompleto(Verde, 330);
      delay(100);
     BarridoCompleto(Rojo, 250);
      delay(100);
     BarridoCompleto(Azul, 50);
      delay(100);
  OffSeg();
  barridoSegmento(Azul);
 delay(100);
  ValorAscii("0000110",Rojo);//1
  delay(1000);
  OffSeg();
  ValorAscii("1011011",Verde);//2
  delay(1000);
  OffSeg();
  ValorAscii("1001111",Azul);//3
  delay(1000);
  OffSeg();
   ValorAscii("1100110",Rojo);//4
  delay(1000);
  ValorAscii("1100110",Rojo);//4
  OffSeg();
    ValorAscii("1101101",Rojo);//5
  delay(1000);
  OffSeg();
    ValorAscii("1111101",Verde);//6
  delay(1000);
  OffSeg();
    ValorAscii("0000111",Azul);//7
  delay(1000);
  OffSeg();
  ValorAscii("1111111",Rojo);//8
  delay(1000);
  OffSeg();
  ValorAscii("1101111",Verde);//9
  delay(1000);
  OffSeg();
}


// Enciende los pixels uno tras otro con el color recibido.
// c de color indica el color que irá rellenando la tira y wait son los milisegundos de un encendido a otro.
// uint32_t o uint8_t significa que c o wait son variables del tipo números enteros sin signo u (unsigned) de 32 u 8 bits. Se hace para indicar unívocamente el número de bits empleados para almacenar la variable.
void BarridoCompleto(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) { // Bucle for recorre todos los pixels de la tira con la variable i.
    strip.setPixelColor(i, c);    // i es el pixel actual para cada iteración y c el color.
    strip.show();    // Actualizamos la tira.
    delay(wait);    // Esperamos un tiempo wait de una iteración a otra.
  }
}
void barridoSegmento(uint32_t c) {
  int seg = 7;
  int LedSeg = 35 / 7;
  int DigOn = 0;
  for (int SegCtn = 0; SegCtn < seg; SegCtn++) {
    for (int LedSegCtn = 0; LedSegCtn < LedSeg; LedSegCtn++) { // Bucle for recorre todos los pixels de la tira con la variable i.
      strip.setPixelColor(LedSegCtn + DigOn, c);
    }  // i es el pixel actual para cada iteración y c el color.
    strip.show();
    DigOn = DigOn + 5;
    delay(1000);
  }
  DigOn = 0;
  delay(1500);
  for (int SegCtn = 0; SegCtn < seg; SegCtn++) {
    for (int LedSegCtn = 0; LedSegCtn < LedSeg; LedSegCtn++) { // Bucle for recorre todos los pixels de la tira con la variable i.
      strip.setPixelColor(LedSegCtn + DigOn, Off);
    }  // i es el pixel actual para cada iteración y c el color.
    strip.show();
    DigOn = DigOn + 5;
    delay(500);
  }
}
void OffSeg() {
  int seg = 7;
  int LedSeg = 35 / 7;
  int DigOn = 0;
  delay(1500);
  for (int SegCtn = 0; SegCtn < seg; SegCtn++) {
    for (int LedSegCtn = 0; LedSegCtn < LedSeg; LedSegCtn++) { // Bucle for recorre todos los pixels de la tira con la variable i.
      strip.setPixelColor(LedSegCtn + DigOn, Off);
    }  // i es el pixel actual para cada iteración y c el color.
    strip.show();
    DigOn = DigOn + 5;
    delay(1);
  }
}
void ValorAscii(String CadenaBinaria,uint32_t c)
{
  int seg = 7;
  int LedSeg = 35 / 7;
  int DigOn = 0;
  char Res = 0;
  char Bit;
  for (int Cont = CadenaBinaria.length() - 1; Cont >= 0; Cont--)
  {
    Bit = CadenaBinaria.charAt(Cont);              //Obtengo el bit que estoy manipulando
    if (Bit == '1')  {
      for (int LedSegCtn = 0; LedSegCtn < LedSeg; LedSegCtn++)
      {
        strip.setPixelColor(LedSegCtn + DigOn, c);
      }
      strip.show();
    }
    DigOn = DigOn + 5;
  }
}
// Reproduce unas luces tipo teatro que van moviéndose en persecución hasta quedar fijas.
// c de color indica el color que irá rellenando la tira y wait son los milisegundos de un encendido a otro.
void Barrido1A1(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { // Realiza 10 ciclos de persecución.
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  // Enciende cada tercer pixel.
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      // Apaga cada tercer pixel.
      }
    }
  }
}
