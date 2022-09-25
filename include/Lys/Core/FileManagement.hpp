#ifndef _FILE_MANAGEMENT_HPP
#define _FILE_MANAGEMENT_HPP 1

#include <vector>
#include <utility>
#include <string>

#include "Lys/LysConfig.hpp"

namespace lys
{

struct LYS_API File
{
    File();
    File(const std::string& full_path);
    File(const std::string& path, const std::string& name, const std::string& ext);

    std::string m_Path;
    std::string m_Name;
    std::string m_Extension;
    uint32_t mt_Get_Last_Modification_Date(void) const;

    std::string mt_Get_Path_Name(void) const;
    std::string mt_Get_Path_Name_Ext(void) const;
    std::string mt_Get_Name(void) const {return m_Name;}
    std::string mt_Get_Extension(void) const {return m_Extension;}
    std::string mt_Get_Path(void) const {return m_Path;}

    bool mt_Create_Path_To_File(void) const;

    std::vector<std::string> mt_Get_Sub_Sequence_Path(void) const;

    static bool smt_Cut_Path(const std::string& full_path, std::string& path, std::string& name, std::string& ext);
    static bool smt_Cut_Path(const std::string& full_path, File& file);
};


LYS_API std::vector<File> fn_Get_Files(const std::string& path, int depth = -1);
LYS_API std::vector<std::string> fn_Get_Directories(const std::string& path, int depth = -1);

LYS_API bool fn_Create_Directory(const std::string& path);

LYS_API bool fn_File_Exists(const std::string& file_name);

}

#endif // _FILE_MANAGEMENT_HPP
