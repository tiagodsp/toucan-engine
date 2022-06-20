#include "DarwinFileManager.h"
#include "Log.h"
#include "Utils/FileManager.h"
#include <filesystem>
#include <fstream>
#include <ios>

namespace fs = std::filesystem;

namespace Toucan
{

DarwinFileHandle::DarwinFileHandle(HANDLE fileHandle) : m_NativeFileHandle(fileHandle) {}

DarwinFileHandle::~DarwinFileHandle()
{
    auto handle = (std::fstream *)m_NativeFileHandle;
    handle->close();
    delete handle;
}

int64 DarwinFileHandle::Tell()
{
    auto handle = (std::fstream *)m_NativeFileHandle;
    return handle->tellg();
}

bool DarwinFileHandle::Seek(int64 NewPosition)
{
    auto handle = (std::fstream *)m_NativeFileHandle;
    handle->seekg(NewPosition);
}

bool DarwinFileHandle::SeekFromEnd(int64 NewPositionRelativeToEnd)
{
    auto handle = (std::fstream *)m_NativeFileHandle;
    handle->seekg(NewPositionRelativeToEnd, std::ios_base::end);
}

uint64 DarwinFileHandle::Read(uint8 *Destination, uint64 BytesToRead)
{
    auto handle = (std::fstream *)m_NativeFileHandle;
    handle->read((char *)Destination, BytesToRead);
    return handle->gcount();
}

bool DarwinFileHandle::Write(const uint8 *Source, int64 BytesToWrite)
{
    auto handle = (std::fstream *)m_NativeFileHandle;
    handle->write((char *)Source, BytesToWrite);
    if (handle->fail())
    {
        CORE_LOGE("Failed to write to file.");
        return false;
    }
    return handle->good();
}

bool DarwinFileHandle::Flush()
{
    auto handle = (std::fstream *)m_NativeFileHandle;
    handle->flush();
    return handle->good();
}

// DarwinFileManager definitions -------------------------------------------------

bool DarwinFileManager::FileExists(const String &Filename) { return fs::exists(Filename); }

int64 DarwinFileManager::FileSize(const String &Filename) { return fs::file_size(Filename); }

bool DarwinFileManager::DeleteFile(const String &Filename) { return fs::remove(Filename); }

bool DarwinFileManager::IsReadOnly(const String &Filename)
{
    return (fs::status(Filename).permissions() & fs::perms::owner_read) != fs::perms::none;
}

bool DarwinFileManager::MoveFile(const String &From, const String &To) { fs::rename(From, To); }

bool DarwinFileManager::SetReadOnly(const String &Filename, bool NewReadOnlyValue)
{
    fs::permissions(Filename, fs::perms::owner_read | (NewReadOnlyValue ? fs::perms::none : fs::perms::owner_write));
}

String DarwinFileManager::GetFilenameOnDisk(const String &Filename) { return fs::absolute(Filename).string(); }

FileHandle *DarwinFileManager::OpenRead(const String &Filename, bool AllowWrite)
{
    std::ios::openmode mode = std::ios::in;
    mode |= AllowWrite ? std::ios::out : std::ios::in;
    HANDLE fileHandle = new std::fstream(Filename, mode);
    if (fileHandle == nullptr)
    {
        CORE_LOGE("Failed to open file '%s'.", Filename.c_str());
        return nullptr;
    }
    return new DarwinFileHandle(fileHandle);
}

FileHandle *DarwinFileManager::OpenWrite(const String &Filename, bool Append, bool AllowRead)
{
    std::ios::openmode mode = std::ios::out;
    mode |= Append ? std::ios::app : std::ios::trunc;
    mode |= AllowRead ? std::ios::in : std::ios::out;
    HANDLE fileHandle = new std::fstream(Filename, mode);
    if (fileHandle == nullptr)
    {
        CORE_LOGE("Failed to open file '%s'.", Filename.c_str());
        return nullptr;
    }
    return new DarwinFileHandle(fileHandle);
}

bool DarwinFileManager::DirectoryExists(const String &Directory) { return fs::is_directory(Directory); }

bool DarwinFileManager::CreateDirectory(const String &Directory) { fs::create_directory(Directory); }

bool DarwinFileManager::DeleteDirectory(const String &Directory) { fs::remove_all(Directory); }

void DarwinFileManager::FindFiles(std::vector<String> &FoundFiles, const String &Directory, const String &FileExtension)
{
    for (const auto &entry : fs::directory_iterator(Directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == FileExtension)
        {
            FoundFiles.push_back(entry.path().string());
        }
    }
}

void DarwinFileManager::FindFilesRecursively(
    std::vector<String> &FoundFiles, const String &Directory, const String &FileExtension)
{
    for (const auto &entry : fs::recursive_directory_iterator(Directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == FileExtension)
        {
            FoundFiles.push_back(entry.path().string());
        }
    }
}

bool DarwinFileManager::DeleteDirectoryRecursively(const String &Directory)
{
    for (const auto &entry : fs::recursive_directory_iterator(Directory))
    {
        if (entry.is_regular_file())
        {
            fs::remove(entry.path());
        }
        else if (entry.is_directory())
        {
            fs::remove_all(entry.path());
        }
    }
    return fs::remove(Directory);
}

bool DarwinFileManager::CreateDirectoryTree(const String &Directory)
{
    std::vector<String> directories;
    String currentDirectory = Directory;
    while (currentDirectory.length() > 0)
    {
        directories.push_back(currentDirectory);
        currentDirectory = currentDirectory.substr(0, currentDirectory.find_last_of('/'));
    }
    for (auto it = directories.rbegin(); it != directories.rend(); ++it)
    {
        if (!fs::exists(*it))
        {
            if (!fs::create_directory(*it))
            {
                CORE_LOGE("Failed to create directory '%s' trying to create directory tree '%s'.", *it, Directory);
                return false;
            }
        }
    }
    return true;
}

bool DarwinFileManager::CopyFile(const String &From, const String &To)
{
    FileHandle *from = OpenRead(From);
    FileHandle *to = OpenWrite(To);
    if (from || to)
    {
        uint8 buffer[1024];
        uint64 readBytes = 0;
        while (readBytes = from->Read(buffer, 1024))
        {
            to->Write(buffer, readBytes);
        }
        to->Flush();
        delete from;
        delete to;
        return true;
    }
    CORE_LOGE("Failed to copy file '%s' to '%s'.", From, To);
    return false;
}

bool DarwinFileManager::CopyDirectoryTree(
    const String &DestinationDirectory, const String &Source, bool OverwriteAllExisting)
{
    if (!CreateDirectoryTree(DestinationDirectory))
    {
        CORE_LOGE("Failed to create directory tree '%s'.", DestinationDirectory);
        return false;
    }
    for (const auto &entry : fs::recursive_directory_iterator(Source))
    {
        if (entry.is_regular_file())
        {
            String destination = DestinationDirectory + entry.path().string().substr(Source.length());
            if (OverwriteAllExisting || !fs::exists(destination))
            {
                if (!CopyFile(entry.path().string(), destination))
                {
                    CORE_LOGE("Failed to copy directory tree '%s' to '%s'.", Source, DestinationDirectory);
                    return false;
                }
            }
            else
            {
                CORE_LOGE(
                    "Failed to copy directory tree '%s' to '%s' because file '%s' already exists.",
                    Source,
                    DestinationDirectory,
                    destination);
                return false;
            }
        }
    }
    return true;
}
} // namespace Toucan