#include <FastLED.h>
#define redPin 5
#define grnPin 6
#define bluPin 9

CRGB LED;
void flicker();

void setup() {
	// Configure the pins for each LED channel
	pinMode(redPin, OUTPUT);
	pinMode(grnPin, OUTPUT);
	pinMode(bluPin, OUTPUT);

}

void loop()
{
	flicker();
}

// Call repeatedly for a flame-like effect
void flicker() {
	const int min_brightness = 150;
	const int max_brightness = 200;
	const int min_hue = 23;
	const int max_hue = 28;

	int peak = random(0, max_brightness - min_brightness);

	int flicker_speed = random(3, 4);
	int solid_time = random(200, 1000); // Time between flickers in ms

	// Stay at max brightness for some time before flickering
	LED = CHSV(max_hue, 255, max_brightness);
	updateLED();
	delay(solid_time);

	// Start of the flicker. Ramp down brightness to the random peak value
	for (int i = max_brightness; i > max_brightness - peak; i--)
	{
		int hue = map(i, min_brightness, max_brightness, max_hue, min_hue);
		LED = CHSV(hue, 255, i);
		updateLED();
		delay(flicker_speed);

	}

	// Second half of the flicker, ramp back up to max brightness
	for (int i = max_brightness - peak; i < max_brightness; i++)
	{
		int hue = map(i, min_brightness, max_brightness, max_hue, min_hue);
		LED = CHSV(hue, 255, i);
		updateLED();
		delay(flicker_speed);

	}



}

// Use analogWrite to generate PWM signals for each color channel. Color values come from global LED object
void updateLED(void)
{
	analogWrite(redPin, LED.r);
	analogWrite(grnPin, LED.g);
	analogWrite(bluPin, LED.b);
}

