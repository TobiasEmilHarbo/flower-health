#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "LixieDigitPosition.h"
#include "LixieDigit.h"

LixieDigitPosition::LixieDigitPosition(int index, int digitWidth, int base, uint32_t color)
{
	Serial.begin(115200);

	_index = index;
	_color = color;
	_startPixel = index * digitWidth * base;
	
	for (int i = 0; i < base; ++i)
	{
		int digitIndex = (i * digitWidth) + _startPixel;
	 	_digits[i] = new LixieDigit(digitIndex, digitWidth);
	}
}

void LixieDigitPosition::setPixels(Adafruit_NeoPixel * pixels)
{
	_pixels = pixels;

	for (int i = 0; i < sizeof(_digits) / sizeof(_digits[0]); ++i)
	{
		if (_digits[i] != NULL)
		 	_digits[i]->setPixels(_pixels);
	}
}

void LixieDigitPosition::display(int number)
{
	_number = number;

	if (_digits[number] != NULL)
		_digits[number]->turnOn(_color);
}

void LixieDigitPosition::setColor(uint32_t color)
{
	_color = color;
	_digits[_number]->turnOn(color);
}

int LixieDigitPosition::pixelCount()
{
	int count = 0;

	for (int i = 0; i < sizeof(_digits) / sizeof(_digits[0]); ++i)
	{
		if (_digits[i] != NULL)
		 	count += _digits[i]->getWidth();
	}

	return count;
}