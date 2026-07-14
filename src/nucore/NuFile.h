#pragma once

struct NuFileSortKey;

enum nufilemode_e {};

class NuFile {
public:
    enum TYPE {};

    virtual ~NuFile();
    virtual void Init();
    virtual void Closedown();
    virtual void SetFilename(const char*);
    virtual void GetPos();
    virtual void GetSize();
    virtual void GetOpenFileNames(TYPE, char*, int, char**, int);
    virtual void GetSortKey(NuFileSortKey&);
};

void NuFileGetSortKey(NuFile* const& file, NuFileSortKey& key);
