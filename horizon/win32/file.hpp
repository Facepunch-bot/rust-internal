#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "sdk/handle.hpp"
#include "sdk/file_information_class.hpp"
#include "sdk/file_standard_information.hpp"
#include "sdk/file_directory_information.hpp"

namespace horizon::win32
{

class NtFile
{
public:
	NtFile();

public:
	~NtFile();

public:
	bool IsOpen() const;
	bool IsDirectory() const;

	void Close();

protected:
	bool OpenInternal( const std::wstring& path, bool create_if_not_existing, std::uint32_t desired_access, std::uint32_t create_options );

protected:
	HANDLE m_object = nullptr;
};

class Directory : public NtFile
{
public:
	Directory( const std::wstring& path, bool create_if_not_existing = false, std::uint32_t desired_access = FILE_READ_DATA );

public:
	bool Open( const std::wstring& path, bool create_if_not_existing = false, std::uint32_t desired_access = FILE_READ_DATA );
	bool Query( FILE_DIRECTORY_INFORMATION* information, bool restart = false );
};

class File : public NtFile
{
public:
	File( const std::wstring& path, bool create_if_not_existing = false, std::uint32_t desired_access = FILE_READ_DATA );

public:
	bool Open( const std::wstring& path, bool create_if_not_existing = false, std::uint32_t desired_access = FILE_READ_DATA );

	bool Read( void* data, std::size_t size_to_read, std::size_t* size_read = nullptr );
	bool Write( const void* const data, std::size_t size_to_write, std::size_t* size_written = nullptr );

	std::size_t GetSize() const;
};

} // namespace horizon::win32