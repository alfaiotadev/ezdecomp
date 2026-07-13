#pragma once

struct HUFFMAN;
struct CHROMA;
struct AUDIOTRACK;

void IDCT_Block(unsigned char* output, int outputStride, short* input, float* dequantisationTable);
void AudioDecode_DecodeAdpcm(AUDIOTRACK* audioTrack, unsigned char* inputData, unsigned int* outputData,
                             unsigned int outputDataSize);
void Huffman_BuildTable(HUFFMAN* huffman, int* codeLengths);
void Huffman_GrowBitBuffer(CHROMA* chroma, int& bitBuffer);
void Huffman_DecodeBlock(CHROMA* chroma, short* output, HUFFMAN* huffmanY, HUFFMAN* huffmanCbCr,
                         int blockType);
// int HuffmanDecodeValue(CHROMA*, HUFFMAN*, int&)
// int HuffmanGetCoefficient(CHROMA*, int, int&)
void Huffman_GetYCbCrFill(CHROMA* chroma, unsigned char* r, unsigned char* g, unsigned char* b);
// int HuffmanGetBits(CHROMA*, int, int&)
void Huffman_GetMotionVector(CHROMA* chroma, short* mvX, short* mvY);
