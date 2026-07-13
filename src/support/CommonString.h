#pragma once

#include <cstdint>

int NuStrCmp(const char* s1, const char* s2);
int NuStrICmp(const char* s1, const char* s2);
char NuToUpper(unsigned char c);
char NuToLower(unsigned char c);
int NuFileExistQuiet(const char* path);
void NuFileSetCurrentDirectory(const char* path);

// todo add missing methods
class CommonString {
public:
    CommonString();
    virtual ~CommonString();

    char* AsChar() const;
    unsigned short Length() const;
    unsigned short GetLength() const;
    void SetLength(int length);

    char operator[](int index) const;
    bool operator==(const CommonString& other) const;
    bool operator==(const char* other) const;
    bool operator!=(const CommonString& other) const;
    bool operator!=(const char* other) const;

    bool Contains(const char* substring) const;
    bool StartsWith(const char* prefix) const;
    bool EndsWith(const char* suffix) const;
    int IndexOf(const char* substring) const;
    int RIndexOf(const char* substring) const;

    bool ContainsI(const char* substring) const;
    bool StartsWithI(const char* prefix) const;
    bool EndsWithI(const char* suffix) const;
    int IndexOfI(const char* substring) const;
    int RIndexOfI(const char* substring) const;

    int Count(const char* substring) const;
    int AToI(bool* ok = nullptr);

    void ToUpper();
    void ToLower();

    bool FileExists() const;
    void SetCurrentDir() const;

    static void SetCaseSensitiveCompare(bool sensitive);
    static bool GetCaseSensitiveCompare();

private:
    char* m_data;
    static bool m_CaseSensitiveCompare;
    uint16_t* length;
};
