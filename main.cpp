//
// GIF player example project
// written by Larry Bank Dec 17, 2025
// Utilizes my bb_spi_lcd and AnimatedGIF libraries
// to allow the user to select from different animations
// with the use of the HAT joystick (GPIO input)
//
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <bb_spi_lcd.h>
#include <AnimatedGIF.h>
#include <time.h>
AnimatedGIF gif; // static instance of the GIF decoder library
BB_SPI_LCD lcd; // static instance of the LCD library
int iCurrentFile = 0;

// The list of GIF files to navigate
#define NUM_FILES 4
const char *szFiles[NUM_FILES] = {"buddy_bear_240x240.gif", "badger_240x240.gif", "this_is_fine_240x240.gif", "eggyolk_covid_240x240.gif"};

// Definitions for the Waveshare 1.3" 240x240 HAT
#define LCD_TYPE LCD_ST7789_240
#define DC_PIN 25
#define RESET_PIN 27
#define CS_PIN 8
#define LED_PIN 24
#define SPI_NUM 0
#define SPI_CE 0
#define GPIO_CHIP 0
#define UP_BUTTON 6

int main(int argc, char *argv[])
{
  int w, h;
  int bChange = 0; // switch to next file
  uint8_t *pStart;
  uint8_t u8, u8Old = 1; // active low
  int iDelay; // Frame delay in milliseconds

  printf("hat_gif by Larry Bank\nPress the UP button to switch animations.\nPress ctrl-c to exit\n");

// Configure the UP button as a GPIO input (I created an Arduino-like API)
  pinMode(UP_BUTTON, INPUT);

// Some devices may need the SPI clock slowed down. The source freq is 250MHz
// so the next division would be 31.25MHZ (31250000)
  lcd.begin(LCD_TYPE, FLAGS_NONE, 62500000, CS_PIN, DC_PIN, RESET_PIN, LED_PIN, GPIO_CHIP, SPI_NUM, SPI_CE);
  lcd.setRotation(90); // Make sure we're in landscape orientation
  lcd.fillScreen(TFT_BLACK);

  gif.begin(BIG_ENDIAN_PIXELS); // bb_spi_lcd expects big-endian RGB565 pixels

  while (1) { // run forever (or until the user presses CTRL-C)
      bChange = 0; // flag indicating the user wants to change files
      if (gif.open(szFiles[iCurrentFile], NULL)) {
      w = gif.getCanvasWidth();
      h = gif.getCanvasHeight();
      //printf("Successfully opened GIF; Canvas size = %d x %d\n", w, h);
// The AnimatedGIF framebuffer is laid out as WxH 8-bit pixels (original)
// followed by the full color pixels translated through the palette
// In this case, RGB565 pixels which occupy 2 bytes each
      gif.setFrameBuf((uint8_t*)malloc(w*h*3));
      pStart = gif.getFrameBuf();
      pStart += w*h; // point to the RGB565 pixels
      gif.setDrawType(GIF_DRAW_COOKED); // request fully prepared pixels

      while (!bChange) { // loop over each file until the user chooses another
          while (gif.playFrame(false, &iDelay, NULL) && !bChange) {
	      lcd.setAddrWindow(0,0,w,h);
	      lcd.pushPixels((uint16_t *)pStart, w * h); // send the whole frame
              usleep(iDelay * 1000); // delay between frames
              // See if the user wants to change to a different animation
              u8 = digitalRead(UP_BUTTON);
              if (u8 == 0 && u8Old == 1) { // user just pressed it
                  bChange = 1;
                  iCurrentFile++;
                  if (iCurrentFile == NUM_FILES) {
                      iCurrentFile = 0; // wrap around to the start of the list
                  }
              }
              u8Old = u8; // old = new
          } // while decoding frames
	  gif.reset(); // reset the GIF animation to frame 0 to repeat it
      } // while (1)
      gif.close();
  } // GIF opened successfully
  } // outer loop
  return 0;
} /* main () */

