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
};
#endif // WXCHELPER_H
