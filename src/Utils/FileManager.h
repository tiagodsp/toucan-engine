#pragma once
#include "Toucan.h"

namespace Toucan
{

class FileHandle
{
  public:
    virtual ~FileHandle() {}

    /**
     * Return the current write or read position.
     * @return	    Current write or read position.
     **/
    virtual int64 Tell() = 0;

    /**
     * Set the current write or read position.
     * @param NewPosition   New seek postion.
     * @return	            true if successfuly changed to the new write or read position.
     **/
    virtual bool Seek(int64 NewPosition) = 0;

    /**
     * Set the current write or read position relative to the end of file.
     * @param NewPositionRelativeToEnd  New seek position relative to the end of the file.
     * @return	                        true is successfully changed to the new write or read position.
     **/
    virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd) = 0;

    /**
     * Read bytes from the file.
     * @param Destination   Buffer to holds the result, should be at least BytesToRead in size.
     * @param BytesToRead   Number of bytes to read into the destination.
     * @return	            Read bytes (may be less than BytesToRead if end of file is reached).
     **/
    virtual uint64 Read(uint8 *Destination, uint64 BytesToRead) = 0;

    /**
     * Write bytes to the file.
     * @param Source        Buffer to writen, should be at least BytesToWrite in size.
     * @param BytesToRead   Number of bytes to read into the destination.
     * @return	            true if the operation completed successfully.
     **/
    virtual bool Write(const uint8 *Source, int64 BytesToWrite) = 0;

    /**
     * Flushes the file handle to disk.
     * @return  true if the operation completed successfully.
     **/
    virtual bool Flush() = 0;
};

class FileManager
{
  public:
    static Ref<FileManager> Get();

    ~FileManager() {}

    /**
     * @brief Check if a file exists.
     * @param Filename  Filename to check.
     * @return true if the file exists.
     * @return false if the file does not exist.
     */
    virtual bool FileExists(const String &Filename) = 0;

    /**
     * @brief Get the size of a file.
     * @param Filename  Filename to check.
     * @return The size of the file.
     */
    virtual uint64 FileSize(const String &Filename) = 0;

    /**
     * @brief Delete a file.
     * @param Filename Filename to delete.
     * @return true if the file was deleted.
     */
    virtual bool DeleteFile(const String &Filename) = 0;

    /**
     * @brief Check if a file is read only.
     * @param Filename Filename to check.
     * @return true if the file is read only.
     */
    virtual bool IsReadOnly(const String &Filename) = 0;

    /**
     * @brief Move a file to a new location.
     * @param From Filename to move.
     * @param To  Filename to move to.
     * @return true if the file was moved.
     */
    virtual bool MoveFile(const String &From, const String &To) = 0;

    /**
     * @brief Set file as read only.
     * @param Filename Filename to set.
     * @param NewReadOnlyValue New read only value.
     * @return true if the file was set.
     */
    virtual bool SetReadOnly(const String &Filename, bool NewReadOnlyValue) = 0;

    /**
     * @brief Get the absolute path of a file in the filesystem.
     * @param Filename Filename to get the absolute path of.
     * @return The absolute path of the file.
     */
    virtual String GetFilenameOnDisk(const String &Filename) = 0;

    /**
     * @brief Open a file for reading.
     * @param Filename Filename to open.
     * @param AllowWrite If true, the file will be opened for writing.
     * @return FileHandle* Pointer to the file handle.
     */
    virtual FileHandle *OpenRead(const String &Filename, bool AllowWrite = false) = 0;

    /**
     * @brief Open a file for writing.
     * @param Filename Filename to open.
     * @param AllowRead If true, the file will be opened for reading.
     * @return FileHandle* Pointer to the file handle.
     */
    virtual FileHandle *OpenWrite(const String &Filename, bool Append = false, bool AllowRead = false) = 0;

    /**
     * @brief Check if directory exists.
     * @param Directory Directory to check.
     * @return true if the directory exists.
     */
    virtual bool DirectoryExists(const String &Directory) = 0;

    /**
     * @brief Create a directory.
     * @param Directory Directory to create.
     * @return true if the directory was created.
     */
    virtual bool CreateDirectory(const String &Directory) = 0;

    /**
     * @brief Delete a directory.
     * @param Directory Directory to delete.
     * @return true if the directory was deleted.
     */
    virtual bool DeleteDirectory(const String &Directory) = 0;

    /**
     * @brief Find all files in a directory from a given extension. If extension is empty, all files will be returned.
     * @param FoundFiles List of found files.
     * @param Directory Directory to search.
     * @param FileExtension File extension to search for. If empty, all files will be returned.
     */
    virtual void FindFiles(std::vector<String> &FoundFiles, const String &Directory, const String &FileExtension) = 0;

    /**
     * @brief Find all files in a directory from a given extension recursively. If extension is empty, all files will be
     * returned.
     * @param FoundFiles List of found files.
     * @param Directory Directory to search.
     * @param FileExtension File extension to search for. If empty, all files will be returned.
     */
    virtual void FindFilesRecursively(
        std::vector<String> &FoundFiles, const String &Directory, const String &FileExtension) = 0;

    /**
     * @brief Delete all files in a directory.
     * @param Directory Directory to delete.
     * @return true if the directory was deleted.
     */
    virtual bool DeleteDirectoryRecursively(const String &Directory) = 0;

    /**
     * @brief Create a Directory Tree from a given path.
     * @param Directory Directory to create.
     * @return true if the directory was created.
     */
    virtual bool CreateDirectoryTree(const String &Directory) = 0;

    /**
     * @brief Copy a file from one location to another.
     * @param From Filename to copy from.
     * @param To Filename to copy to.
     * @return true if the file was copied.
     */
    virtual bool CopyFile(const String &From, const String &To) = 0;

    /**
     * @brief Copy a entire directory from one location to another.
     * @param DestinationDirectory Destination directory to copy to.
     * @param Source Directory to copy from.
     * @param OverwriteAllExisting If true, all existing files will be overwritten. If false, existing files will rise
     * an error.
     * @return true if the directory was copied.
     */
    virtual bool CopyDirectoryTree(
        const String &DestinationDirectory, const String &Source, bool OverwriteAllExisting) = 0;
};
} // namespace Toucan
