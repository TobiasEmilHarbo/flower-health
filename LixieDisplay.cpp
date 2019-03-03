#include "Arduino.h"
#include "LixieDisplay.h"
#include "LixieDigitPosition.h"

#include "Adafruit_NeoPixel.h"

LixieDisplay::LixieDisplay(int digits)
{
	Serial.begin(115200);

	_numOfDigits = digits;
	
	uint32_t defaultColor = _pixels->Color(244,212,66);

	for (int i = 0; i < _numOfDigits; ++i)
	{
		_digitPositions[i] = new LixieDigitPosition(i, 2, 10, defaultColor); 
	}
}

void LixieDisplay::setup(Adafruit_NeoPixel * pixels)
{
	_pixels = pixels;

	_pixels->begin();

	for (int i = 0; i < _numOfDigits; ++i)
	{
		if (_digitPositions[i] != NULL)
	 		_digitPositions[i]->setPixels(_pixels);
	}

	_pixels->setBrightness(50);
	_pixels->show(); // Initialize all pixels to 'off'
}

void LixieDisplay::setColor(uint32_t color)
{
	for (int i = 0; i < _numOfDigits; ++i)
	{
		if (_digitPositions[i] != NULL)
	 		_digitPositions[i]->setColor(color);
	}

	_pixels->show();
}

void LixieDisplay::setColors(uint32_t colors[])
{
	for (int i = 0; i < _numOfDigits; ++i)
	{
		if(colors[i] == NULL) return;
		if(_digitPositions[i] == NULL) return;

		_digitPositions[i]->setColor(colors[i]);

		Serial.print("color[");
		Serial.print(i);
		Serial.print("] is not NULL: ");
		Serial.println((colors[i] != NULL));
		Serial.println(colors[i]);
		
		Serial.print("_digitPositions[");
		Serial.print(i);
		Serial.print("] is not NULL: ");
		Serial.println((_digitPositions[i] != NULL));
	}

	_pixels->show();
}

void LixieDisplay::display(String number)
{
	
	this->turnOff();

	int digitCount = number.length();
	char digits[digitCount];

	int diff = _numOfDigits - digitCount;
	int padding = (diff > 0) ? diff : 0;

	number.toCharArray(digits, digitCount+1);

	for (int i = 0; i < digitCount; ++i)
	{
		int digit = digits[i] - '0'; // convert char to int

		if (_digitPositions[padding+i] != NULL)
	 		_digitPositions[padding+i]->display(digit);
	}

	_pixels->show();
}

int LixieDisplay::pixelCount()
{
	int count = 0;

	for (int i = 0; i < _numOfDigits; ++i)
	{
		if (_digitPositions[i] != NULL)
	 		count += _digitPositions[i]->pixelCount();
	}

	return count;
}

void LixieDisplay::turnOff()
{
	for (int i = 0; i < this->pixelCount(); ++i)
	{
		_pixels->setPixelColor(i, 0);
	}
}
