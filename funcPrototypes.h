#include <graphics.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <math.h>
#define WIDTH 1000
#define HEIGHT 600
#define WINDOW_SIZE 512
#define MAX_AMPLITUDE 32767
#include <windows.h>

extern int SampleNumber;
extern float timeLength;
extern int Fs;

typedef struct header {
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
} header;

typedef struct header* headerP;
void borderRadius();
void theFrameOfTheSoundWave();
void theFrameOfTheCurrentSoundWave();
void theFrameOfTheAutoCorr();
void theFrameOfFrequencyVariation();

void drawWaveForm(int16_t *data, int num_samples, int color, int startX, int startY, int widthOfWindow, int firstSignal);
void drawWavesInTheCurrentWindow(int16_t *data, int num_samples, int color, int startX, int startY, int start);
void calculateAndDrawAutocorrelation(int16_t *data, float autoCorr, int start, int color, int startX, int startY);
void showMaxMinAutoCorr(float maxAutoCorr, float minAutoCorr);
void clearTheWindowFrame(int left, int top, int right, int bottom);
void drawAndClearCurrentWindow (int16_t *data, int num_samples, int color, int startX, int startY);
void moveTwoCursors(int16_t *data);