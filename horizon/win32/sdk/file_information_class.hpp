#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum FILE_INFORMATION_CLASS
{
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation = 2,
	FileBothDirectoryInformation = 3,
	FileBasicInformation = 4,
	FileStandardInformation = 5,

	FileIdBothDirectoryInformation = 37,
};
// sizeof( FILE_INFORMATION_CLASS ) = 0x0004

} // namespace horizon::win32