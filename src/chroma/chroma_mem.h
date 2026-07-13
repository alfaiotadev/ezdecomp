#pragma once

void* Chroma_Alloc(unsigned int size);
void* Chroma_AllocAligned(unsigned int size, unsigned int alignment);
void Chroma_Free(void* ptr);
void Chroma_FreeAligned(void* ptr);
