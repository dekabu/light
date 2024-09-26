#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PREFIX         "/sys/class/backlight/amdgpu_bl0/"

#define BRIGHTNESS     PREFIX "brightness" 
#define MAX_BRIGHTNESS PREFIX "max_brightness"

int   brightness;
char  brightness_str[8];
FILE *brightness_fp;

int   max_brightness;
char  max_brightness_str[8];
FILE *max_brightness_fp;

int new_brightness;

int normalize(int);

int main(int argc, char* argv[])
{
	brightness_fp     = fopen(BRIGHTNESS, "w+");
	max_brightness_fp = fopen(MAX_BRIGHTNESS, "r");

	brightness = atoi(fgets(brightness_str, 8, brightness_fp));
	max_brightness = atoi(fgets(max_brightness_str, 8, max_brightness_fp));

	if (argc > 1) {
		char *arg = argv[1];
		if (arg[strlen(arg) - 1] == '%') {
			int    percent = brightness * 100 / max_brightness;
			arg[strlen(arg) - 1] = 0;
			if (arg[0] == '+')
				percent += atoi(++arg);
			else if (arg[0] == '-')
				percent -= atoi(++arg);
			else
				percent = atoi(arg);
			new_brightness = ceil((float) percent * 255 / 100);
		}
		else {
			if (arg[0] == '+')
				new_brightness = brightness + atoi(++arg);
			else if (arg[0] == '-')
				new_brightness = brightness - atoi(++arg);
			else
				new_brightness = atoi(arg);
		}
	}
	else
		new_brightness = brightness;

	new_brightness = normalize(new_brightness);

	if (new_brightness != brightness) {
		sprintf(brightness_str, "%i", new_brightness);
		fputs(brightness_str, brightness_fp);
	}

	printf("%i/%i (%i%%)\n", new_brightness, max_brightness, new_brightness * 100 / max_brightness);

	return 0;
}

int normalize(int brightness)
{
	if (brightness < 0)
		return 0;
	else if (brightness > max_brightness)
		return max_brightness;
	else
		return brightness;
}
