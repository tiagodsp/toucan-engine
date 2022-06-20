#pragma once
#include "Toucan.h"
#include "Utils/FileManager.h"

namespace Toucan
{

class DarwinFileHandle : public FileHandle
{
    HANDLE m_NativeFileHandle;

  public:
    DarwinFileHandle(HANDLE fileHandle);
    virtual ~DarwinFileHandle() override;
    virtual int64 Tell() override;
    virtual bool Seek(int64 NewPosition) override;
    virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd) override;
    virtual uint64 Read(uint8 *Destination, uint64 BytesToRead) override;
    virtual bool Write(const uint8 *Source, int64 BytesToWrite) override;
    virtual bool Flush() override;
};

class DarwinFileManager : public FileManager
{
  public:
    ~DarwinFileManager() {}

    virtual bool FileExists(const String &Filename) override;
    virtual uint64 FileSize(const String &Filename) override;
    virtual bool DeleteFile(const String &Filename) override;
    virtual bool IsReadOnly(const String &Filename) override;
    virtual bool MoveFile(const String &From, const String &To) override;
    virtual bool SetReadOnly(const String &Filename, bool NewReadOnlyValue) override;
    virtual String GetFilenameOnDisk(const String &Filename) override;

    virtual FileHandle *OpenRead(const String &Filename, bool AllowWrite = false) override;
    virtual FileHandle *OpenWrite(const String &Filename, bool Append = false, bool AllowRead = false) override;

    virtual bool DirectoryExists(const String &Directory) override;
    virtual bool CreateDirectory(const String &Directory) override;
    virtual bool DeleteDirectory(const String &Directory) override;

    virtual void FindFiles(
        std::vector<String> &FoundFiles, const String &Directory, const String &FileExtension) override;
    virtual void FindFilesRecursively(
        std::vector<String> &FoundFiles, const String &Directory, const String &FileExtension) override;
    virtual bool DeleteDirectoryRecursively(const String &Directory) override;
    virtual bool CreateDirectoryTree(const String &Directory) override;

    virtual bool CopyFile(const String &To, const String &From) override;
    virtual bool CopyDirectoryTree(
        const String &DestinationDirectory, const String &Source, bool OverwriteAllExisting) override;
};
} // namespace Toucan
