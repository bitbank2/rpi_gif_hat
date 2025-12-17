# C++ LCD HAT GIF player by Larry Bank
<br>
This project is a simple example of my bb_spi_lcd and AnimatedGIF libraries
which uses C++ to display GIF animations on RPI LCD HATs. This specific example
was written to run on the Waveshare 1.3" LCD HAT (ST7789 240x240 LCD). The
up arrow on the joystick is used to switch to the next GIF in the list.
The code comes with 4 GIF files that are in a fixed list within the code.
These can be changed to any number of type of GIF file as needed.

## Requirements
Raspberry Pi 1/2/3/4/5 with a SPI LCD HAT

## Setup
Type the following into a Linux terminal to install the requirements:<br>
sudo apt install libgpiod-dev<br>
<br>
cd ~<br>
mkdir Projects<br>
cd Projects<br>
git clone https://github.com/bitbank2/AnimatedGIF<br>
git clone https://github.com/bitbank2/bb_spi_lcd<br>
<br>
cd bb_spi_lcd/linux<br>
make<br>
cd ../../AnimatedGIF/linux<br>
make<br>
<br>
Now you're ready to run make in the project directory and run the program<br>


