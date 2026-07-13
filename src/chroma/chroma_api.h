#pragma once

struct FMVHandle;
struct TRACKINFO;
struct TRACKCHANNELMAP;

unsigned int Chroma_ReadFrameChunk(FMVHandle* fmvHandle, int* chunkSize);
unsigned char* Chroma_ReadFrame(FMVHandle* fmvHandle);
void fnaDebug(...);
void Chroma_DecodeVideoFrame(FMVHandle* fmvHandle, bool decodeAudio);
void Chroma_DecodeAudioFrame(FMVHandle* fmvHandle);
void Chroma_DecodeFrame(FMVHandle* fmvHandle, bool decodeAudio);
FMVHandle* Chroma_OpenVideo(const char* filename, bool decodeAudio, void (*videoCallback)(void* chroma),
                            void (*audioCallback)(void* chroma, void* audioData, unsigned int audioDataSize),
                            void* userData, TRACKCHANNELMAP const* trackChannelMap,
                            unsigned int trackChannelMapCount);
unsigned int Chroma_GetTrackList(const char* filename, TRACKINFO* trackInfoList,
                                 unsigned int trackInfoListSize);
void Chroma_CloseVideo(FMVHandle* fmvHandle);
void Chroma_SetFileCallbacks(void* (*openCallback)(const char* filename, bool read),
                             unsigned int (*readCallback)(void* fileHandle, void* buffer, unsigned int size),
                             void (*seekCallback)(void* fileHandle, long offset, int origin),
                             void (*closeCallback)(void* fileHandle));
void Chroma_SetMemory(void* (*mallocCallback)(unsigned int size),
                      void* (*reallocCallback)(unsigned int newSize, unsigned int oldSize),
                      void (*freeCallback)(void* ptr), void (*exitCallback)(void* ptr));
