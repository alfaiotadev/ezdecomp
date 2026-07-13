#pragma once

struct CHROMA;
struct HUFFMAN;

void VideoDecode_FillBlock(CHROMA* chroma, unsigned int x, unsigned int y, unsigned char r, unsigned char g,
                           unsigned char b);
void VideoDecode_CopyBlock(CHROMA* chroma, unsigned int x, unsigned int y, short mvX, short mvY);
HUFFMAN* VideoDecode_GetHuffmanTable(CHROMA* chroma, int tableType, int tableIndex);
// unsigned char VideoDecodeGet8(IMAGE*)
void VideoDecode_SetupMovieHeader(CHROMA* chroma);
void VideoDecode_BuildDequantisationTables(CHROMA* chroma);
void VideoDecode_YCbCrToRGBRow(unsigned char* y, unsigned char* cb, unsigned char* cr, unsigned char* rgb,
                               int pixelCount);
void VideoDecode_DecodeFrame(CHROMA* chroma, const unsigned char* frameData, int frameDataSize,
                             unsigned char* outputBuffer, bool decodeAudio);
void VideoDecode_ColourTablesInit();
void VideoDecode_ColourTablesExit();
