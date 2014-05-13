#ifndef WXCHELPER_H
#define WXCHELPER_H

#include <vector>
#include <wx/filename.h>
#include <cbproject.h>

class cbProject;
struct StrToFileNameVecFunctor {
    std::vector<wxFileName>& m_outoutVec;
    
    StrToFileNameVecFunctor(std::vector<wxFileName>& outputVec) : m_outoutVec( outputVec) {}
    void operator()(const wxString &str) {
        m_outoutVec.push_back( wxFileName(str) );
    }
};

typedef std::vector<wxFileName> wxFileNameVec_t;

class wxcHelper 
{
public:
    /**
     * @brief create an empty file. Prompt the user incase of an error
     */
    static bool CreateEmptyFile( const wxFileName& fn );
    
    /**
     * @brief add files to project
     */
    static void AddFilesToProject(cbProject* proj, const std::vector<wxFileName>& files, bool compile);
    
    /**
     * @brief add file to project
     */
    static void AddFileToProject(cbProject* proj, const wxFileName& file, bool compile);
    
    /**
     * @brief find a project by name
     */
    static cbProject* GetProject( const wxString &name );
    
    /**
     * @brief return all workspace files
     * @param files [output]
     */
    static void GetAllFiles( FilesList &files, const wxString &filterExt = wxEmptyString );
    
    /**
     * @brief extract a file from Zip archive
     * @param zipPath zip file path
     * @param filename the file that we want to extract
     * @param targetDir destination folder for the extracted file
     * @param targetFileName [output]
     */
    static bool ExtractFileFromZip(const wxString& zipPath, const wxString& filename, const wxString& targetDir, wxString &targetFileName);
    
    /**
     * @brief read a file content
     */
    static bool ReadFileContent( const wxString& filepath, wxString &content );
    /**
     * @brief write file content (replacing any existing content)
     */
    static bool WriteFileContent( const wxString& filepath, const wxString &content );
};
#endif // WXCHELPER_H
