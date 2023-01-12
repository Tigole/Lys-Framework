#include "Lys/Core/FileManagement.hpp"

#include <unistd.h>
#if (PLATFORM == PLATFORM_WINDOWS)
    #include <dir.h>
    #include <windows.h>
#endif
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>


#include "Lys/Core/Log.hpp"

namespace lys
{

File::File()
 :  m_Path(), m_Name(), m_Extension()
{}

File::File(const std::string& full_path)
 :  m_Path(), m_Name(), m_Extension()
{
    smt_Cut_Path(full_path, *this);
}

File::File(const std::string& path, const std::string& name, const std::string& ext)
 :  m_Path(path), m_Name(name), m_Extension(ext)
{}

uint32_t File::mt_Get_Last_Modification_Date(void) const
{
    struct stat l_Stat;
    uint32_t l_Ret = 0;

    if (stat(mt_Get_Path_Name_Ext().c_str(), &l_Stat) == 0)
    {
        l_Ret = l_Stat.st_mtime;
    }

    return l_Ret;
}

std::string File::mt_Get_Path_Name(void) const
{
    return m_Path + m_Name;
}

std::string File::mt_Get_Path_Name_Ext(void) const
{
    return m_Path + m_Name + '.' + m_Extension;
}

std::string File::mt_Get_Parent_Path(void) const
{
    std::string l_Parent_Path;

    LYS_LOG_CORE_DEBUG("m_Path: '%s'", m_Path.c_str());
    l_Parent_Path = m_Path.substr(0, m_Path.find_last_of('/'));
    LYS_LOG_CORE_DEBUG("l_Parent_Path: '%s'", l_Parent_Path.c_str());
    l_Parent_Path = l_Parent_Path.substr(0, l_Parent_Path.find_last_of('/') + 1);
    LYS_LOG_CORE_DEBUG("l_Parent_Path: '%s'", l_Parent_Path.c_str());

    return l_Parent_Path;
}

bool File::mt_Create_Path_To_File(void) const
{
    std::vector<std::string> l_Sub_Seq;
    bool l_b_Ret = true;

    l_Sub_Seq = mt_Get_Sub_Sequence_Path();

    LYS_LOG_CORE_DEBUG("subseq directories: %d", l_Sub_Seq.size());

    for (std::size_t ii = 0; (ii < l_Sub_Seq.size()) && (l_b_Ret == true); ii++)
    {
        l_b_Ret = fn_Create_Directory(l_Sub_Seq[ii]);
    }

    return l_b_Ret;
}

std::vector<std::string> File::mt_Get_Sub_Sequence_Path(void) const
{
    std::vector<std::string> l_Ret;
    std::string l_Current_Path(m_Path);

    l_Current_Path.resize(0);

    LYS_LOG_CORE_TRACE("Sub sequence for path: '%s'", m_Path.c_str());
    for (std::size_t ii = 0; ii < m_Path.size(); ii++)
    {
        l_Current_Path += m_Path[ii];
        if (m_Path[ii] == '/' || m_Path[ii] == '\\')
        {
            l_Ret.push_back(l_Current_Path);

            LYS_LOG_CORE_TRACE("'%s'", l_Current_Path.c_str());
        }
    }

    l_Ret.push_back(l_Current_Path);

    return l_Ret;
}

bool File::smt_Cut_Path(const std::string& full_path, std::string& path, std::string& name, std::string& ext)
{
    bool l_b_Ret = true;
    std::size_t l_Dot_Pos = full_path.rfind('.');
    std::size_t l_Slash_Pos = full_path.rfind('/');
    std::size_t l_Back_Slash_Pos = full_path.rfind('\\');
    std::size_t l_Last_Separator = std::string::npos;

    l_b_Ret = true;

    if (    (l_Slash_Pos == std::string::npos)
        &&  (l_Back_Slash_Pos == std::string::npos))
    {
        l_Last_Separator = 0;
    }
    else
    {
        if (l_Slash_Pos != std::string::npos)
        {
            l_Last_Separator = l_Slash_Pos;
        }
        else if (l_Back_Slash_Pos != std::string::npos)
        {
            l_Last_Separator = l_Back_Slash_Pos;
        }
        else
        {
            l_Last_Separator = std::min(l_Slash_Pos, l_Back_Slash_Pos);
        }

        l_Last_Separator++;
    }

    if (l_Dot_Pos != std::string::npos)
    {
        l_b_Ret = true;

        path = full_path.substr(0, l_Last_Separator);
        name = full_path.substr(l_Last_Separator, l_Dot_Pos - l_Last_Separator);
        ext = full_path.substr(l_Dot_Pos + 1);

        LYS_LOG_CORE_TRACE("\nfull path: '%s'\npath: '%s'\nname: '%s'\next: '%s'", full_path.c_str(), path.c_str(), name.c_str(), ext.c_str());
    }
    else
    {
        l_b_Ret = false;
    }

    return l_b_Ret;
}

bool File::smt_Cut_Path(const std::string& full_path, File& file)
{
    return smt_Cut_Path(full_path, file.m_Path, file.m_Name, file.m_Extension);
}



bool fn_Is_File(const std::string& path)
{
#if (PLATFORM == PLATFORM_WINDOWS)
	std::ifstream l_Stream;
	l_Stream.open(path);
	return l_Stream.is_open();
#else
    struct stat l_Stat;
    if (stat(path.c_str(), &l_Stat) == 0)
    {
        return S_ISREG(l_Stat.st_mode) != 0;
    }
    return false;
#endif
}




std::vector<File> fn_Get_Files(const std::string& path, int depth)
{
    std::vector<File> l_Ret;
    DIR *dir;
    struct dirent *ent;
    std::string l_str;
    std::string l_File_Name;
    std::string l_File_Ext;
    std::string l_File_Path;

    if ((dir = opendir(path.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            l_str = ent->d_name;
            if ((l_str != ".") && (l_str != ".."))
            {
                if (fn_Is_File(path + l_str) == true)
                {
                    l_File_Name = l_str.substr(0, l_str.find_last_of('.'));
                    l_File_Ext = l_str.substr(l_str.find_last_of('.') + 1);
                    l_File_Path = path;
                    l_Ret.push_back(File(l_File_Path, l_File_Name, l_File_Ext));
                }
                else if (depth != 0)
                {
                    std::vector<File> l_Sub;

                    l_Sub = fn_Get_Files(path + l_str + '/', depth - 1);

                    for (std::size_t ii = 0; ii < l_Sub.size(); ii++)
                    {
                        l_Ret.push_back(l_Sub[ii]);
                    }
                }
            }
        }
        closedir (dir);
    }

    return l_Ret;
}

std::vector<std::string> fn_Get_Directories(const std::string& path, int depth)
{
    std::vector<std::string> l_Ret;
    DIR *dir;
    struct dirent *ent;
    std::string l_str;

    if ((dir = opendir(path.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            l_str = ent->d_name;
            if ((l_str != ".") && (l_str != ".."))
            {
                if (fn_Is_File(path + l_str) == false)
                {
                    l_Ret.push_back(path + l_str + '/');

                    if (depth != 0)
                    {
                        std::vector<std::string> l_Sub;

                        l_Sub = fn_Get_Directories(path + l_str + '/', depth - 1);

                        for (std::size_t ii = 0; ii < l_Sub.size(); ii++)
                        {
                            l_Ret.push_back(l_Sub[ii]);
                        }
                    }
                }
            }
        }
        closedir (dir);
    }

    return l_Ret;
}

bool fn_Create_Directory(const std::string& path)
{
#if (PLATFORM == PLATFORM_WINDOWS)
    bool l_Creation_Succeded = CreateDirectory(path.c_str(), nullptr);

    if (l_Creation_Succeded == true)
    {
        LYS_LOG_CORE_DEBUG("Directory created: '%s'", path.c_str());
    }
    else
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            LYS_LOG_CORE_TRACE("Directory already exists: '%s'", path.c_str());
            l_Creation_Succeded = true;
        }
        else
        {
            LYS_LOG_CORE_ERROR("Can't create directory: \"%s\"", path.c_str());
        }
    }
    return l_Creation_Succeded;
#else
    struct stat st = {0};
    if (stat(path.c_str(), &st) == -1)
    {
        return mkdir(path.c_str(), 0700) == 0;
    }
    return true;
#endif
}

bool fn_File_Exists(const std::string& file_name)
{
    std::ifstream l_File;

    l_File.open(file_name);

    return l_File.is_open();
}

}
