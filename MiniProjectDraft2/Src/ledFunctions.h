

struct color{
	char green;
	char red;
	char blue;
};

void ledStripWrite(struct color* data, int numBytes);

void setWhite (struct color* colors, int quantity, int percent);

void setBlack (struct color* colors, int quantity, int percent);

void setBlue (struct color* colors, int quantity, int percent);

void setRed (struct color* colors, int quantity, int percent);
