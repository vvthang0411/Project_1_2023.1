#include "funcPrototypes.h"
#include <vector>
int SampleNumber;
float timeLength;
int Fs;

int main(int argc, char *argv[]) {

	//Định dạng kích thước cho cửa sổ đồ họa
	int width = WIDTH+9;
    int height = HEIGHT+13;
    initwindow(width, height, "Funda_Wave");
    setcolor(LIGHTGRAY);
    setbkcolor(LIGHTGRAY);
    
	//Open and read file
	FILE* infile;
	OPENFILENAME ofn;
    char szFile[260];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "WAV Files (*.wav)\0*.wav\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        // Mở tập tin đã chọn
        infile = fopen(ofn.lpstrFile, "rb");
        if (infile == NULL) {
        	perror("Error opening file");
        	exit(1);
        }
    }
    else {
        // Người dùng đã hủy hộp thoại chọn tập tin
        printf("Nguoi dung da huy.\n");
        exit(1);
    }
    
    headerP meta;
    meta = (headerP)malloc(sizeof(header));
    // Read the first 36 bytes
	fread(meta, 1, 36, infile);
	
    // Read the remaining portion of Subchunk 1, if its size exceeds 16 bytes.
    if (meta->subchunk1_size > 16) {
        fseek(infile, meta->subchunk1_size - 16, SEEK_CUR);
    }

    // Read Subchunk2ID and Subchunk2Size
    fread(&meta->subchunk2_id, 1, 4, infile);
    fread(&meta->subchunk2_size, 1, 4, infile);
    
    // Read the header
	// do bits_per_sample = 16 (2 byte)
	SampleNumber = meta -> subchunk2_size/2;
	
	Fs = meta -> sample_rate;
	float Ts = 1.0/(float)Fs;
    
    int16_t* inbuff16;
    inbuff16 = (int16_t*)malloc(2 * sizeof(int16_t) * SampleNumber);
    fread(inbuff16, 2, SampleNumber, infile);
    
 	// file length
	timeLength = static_cast<float>(SampleNumber)/Fs;
	borderRadius();
	drawWaveForm(inbuff16, SampleNumber, LIGHTGREEN, 50, 100, 900, 0);
	drawAndClearCurrentWindow (inbuff16, SampleNumber, LIGHTGREEN, 200, 300);
	
	moveTwoCursors(inbuff16);

	free(meta);
	fclose(infile);    
    return 0;
}
