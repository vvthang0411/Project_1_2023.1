#include "funcPrototypes.h"

void zoomTheSelectedWave(int16_t *data,int xRedCursor,int xBlueCursor) {
	//drawWaveForm(int16_t *data, int num_samples, int color, int startX, int startY, int widthOfWindow, int firstSignal);
	float sample_spacing = (float)(900)/SampleNumber;
	int redCursorIndex, blueCursorIndex;
	redCursorIndex = static_cast<float>(xRedCursor - 50)/sample_spacing;
	blueCursorIndex = static_cast<float>(xBlueCursor - 50)/sample_spacing;
	int num_samples = blueCursorIndex - redCursorIndex;
	drawWaveForm(data, num_samples, LIGHTGREEN, 50, 300, 420, redCursorIndex);
}

void drawWaveForm2(int16_t *data, int num_samples, int color, int startX, int startY, int widthOfWindow, int firstSignal) {
	float sample_spacing = (float)(widthOfWindow)/num_samples;    //Draw a wave graph
    for ( int i = 0; i < num_samples ; i++) {
        int x1 = startX + i * sample_spacing;
        int y1 = startY - (data[i+firstSignal] * 80 / MAX_AMPLITUDE);
        int x2 = startX + (i + 1) * sample_spacing;
        int y2 = startY - (data[i + firstSignal+1] * 80 / MAX_AMPLITUDE); 

        setcolor(color);
        line(x1, y1, x2, y2);
    }
}

void moveTwoCursors(int16_t *data){
	char ch;
	int xRedCursor = 100, yRedCursor = 100;
    int xBlueCursor = 200, yBlueCursor = 100;
	int *bufferWave = (int*)malloc(imagesize(20, 20, 950, 180));
	getimage(50, 20, 950, 180, bufferWave);
    while (1) {
    	//neu con nhap ky tu thi thuc hien cac thao tac
        if (kbhit()) {
            ch = getch();
            
            if ((ch == 'T') && (xBlueCursor > xRedCursor)) {
                xBlueCursor -= 1;
            }
			else if ((ch == 't') && (xRedCursor>50)) {
            	xRedCursor -= 1;
			}
			else if ((ch == 'P')&& (xBlueCursor<950)) {
				 xBlueCursor += 1;
			}
			else if ((ch == 'p') && (xBlueCursor > xRedCursor)) {
				 xRedCursor	+= 1;			
		 	}
			//Reset 2 duong line
			putimage(50,20,bufferWave, COPY_PUT);
			//Ve 2 duong line moi
			setcolor(RED);
			line(xRedCursor, 180, xRedCursor,20);
			setcolor(BLUE);
			line(xBlueCursor, 180, xBlueCursor,20);
			//Zoom
			if(ch == 'i') {
				clearTheWindowFrame(50, 220, 471, 379);
				theFrameOfTheCurrentSoundWave();
				zoomTheSelectedWave(data, xRedCursor, xBlueCursor);
				
			}
			
		}
	}
}