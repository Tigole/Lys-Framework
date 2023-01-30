#ifndef _FILE_MANAGEMENT_HPP
#define _FILE_MANAGEMENT_HPP 1

#include <vector>
#include <utility>
#include <string>

#include "Lys/LysConfig.hpp"

namespace lys
{

class LYS_API File
{
public:
    File();
    File(const std::string& full_path);
    File(const std::string& path, const std::string& name, const std::string& ext);

    uint32_t mt_Get_Last_Modification_Date(void) const;

    std::string mt_Get_Path_Name(void) const;
    std::string mt_Get_Path_Name_Ext(void) const;
    const std::string& mt_Get_Name(void) const {return m_Name;}
    const std::string& mt_Get_Extension(void) const {return m_Extension;}
    const std::string& mt_Get_Path(void) const {return m_Path;}
    std::string mt_Get_Parent_Path(void) const;

    bool mt_Create_Path_To_File(void) const;

private:

    std::string m_Path;
    std::string m_Name;
    std::string m_Extension;

    std::vector<std::string> mt_Get_Sub_Sequence_Path(void) const;

    static bool smt_Cut_Path(const std::string& full_path, std::string& path, std::string& name, std::string& ext);
    static bool smt_Cut_Path(const std::string& full_path, File& file);
};

LYS_API bool fn_Is_File(const std::string& path);

LYS_API std::vector<File> fn_Get_Files(const std::string& path, int depth = -1);
LYS_API std::vector<std::string> fn_Get_Directories(const std::string& path, int depth = -1);

LYS_API bool fn_Create_Directory(const std::string& path);

LYS_API bool fn_File_Exists(const std::string& file_name);

LYS_API std::string fn_Get_Relative_Path(const std::string& absolute_root_directory, const std::string& absolute_path);

}

#endif // _FILE_MANAGEMENT_HPP
