#include "wxcHelper.h"
#include <wx/msgdlg.h>
#include <wx/ffile.h>
#include <cbproject.h>
#include <manager.h>
#include <projectmanager.h>
#include <globals.h>
#include <wx/filefn.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>

bool wxcHelper::ExtractFileFromZip(const wxString& zipPath, const wxString& filename, const wxString& targetDir, wxString &targetFileName)
{
    wxZipEntry *       entry(NULL);
    wxFFileInputStream in(zipPath);
    wxZipInputStream   zip(in);

    // Make sure the target directory exists...
    wxFileName::Mkdir(targetDir, 0777, wxPATH_MKDIR_FULL);

    entry = zip.GetNextEntry();
    while ( entry ) {
        
        wxString name = entry->GetName();
        if (name == filename) {
            targetFileName = wxFileName(targetDir, filename).GetFullPath();
            wxFFileOutputStream out( targetFileName );
            zip.Read(out);
            out.Close();
            delete entry;
            return true;
        }

        wxDELETE(entry);
        entry = zip.GetNextEntry();
        
    }
    return false;
}

bool wxcHelper::CreateEmptyFile( const wxFileName& fn )
{
    if ( fn.FileExists() ) {
        if ( ::cbMessageBox(_("A file with this name already exists, would you like to replace it?"), wxT("wxCrafter"), wxYES_NO|wxCENTER|wxICON_QUESTION) != wxID_YES ) {
            return false;
        }
        // Remove the current file
        if ( !::wxRemoveFile( fn.GetFullPath() ) ) {
            return false;
        }
    }

    // Create an empty file
    wxFFile fp(fn.GetFullPath(), wxT("w+b"));
    if( !fp.IsOpened() ) {
        wxString errmsg;
        errmsg << _("Failed to create file '") << fn.GetFullPath() << wxT("'");
        ::wxMessageBox(errmsg, wxT("wxCrafter"), wxICON_ERROR|wxCENTER|wxOK);
        return false;
    }
    return true;
}

void wxcHelper::AddFileToProject(cbProject* proj, const wxFileName& file, bool compile)
{
    std::vector<wxFileName> files;
    files.push_back( file );
    AddFilesToProject(proj, files, compile);
}

void wxcHelper::AddFilesToProject(cbProject* proj, const std::vector<wxFileName>& files, bool compile)
{
    wxFileName folderPath(proj->GetFilename());
    proj->BeginAddFiles();

    for(size_t i=0; i<files.size(); ++i) {
        wxFileName fn = files.at(i);
        fn.MakeRelativeTo( folderPath.GetPath() );
        ProjectFile* pf(NULL);
        for(int targetIndex=0; targetIndex<proj->GetBuildTargetsCount(); ++targetIndex) {
            pf = proj->AddFile( targetIndex, fn.GetFullPath(), compile, compile );
        }

        if ( pf ) {
            // This is the only sane way I found to add the file all build targets:
            // clear the array and then iterate them one by one and add them
            pf->buildTargets.Clear();
            for(int targetIndex=0; targetIndex<proj->GetBuildTargetsCount(); ++targetIndex) {
                pf->buildTargets.Add( proj->GetBuildTarget(targetIndex)->GetTitle() );
            }
        }
    }
    proj->EndAddFiles();

    // Save and rebuild the project tree
    Manager::Get()->GetProjectManager()->SaveAllProjects();
    Manager::Get()->GetProjectManager()->GetUI().RebuildTree();
}

cbProject* wxcHelper::GetProject(const wxString& name)
{
    cbProject *selectedProject ( NULL );
    ProjectsArray* projects = Manager::Get()->GetProjectManager()->GetProjects();
    for ( size_t i=0; i<projects->GetCount(); ++i ) {
        if ( projects->Item(i)->GetTitle() == name ) {
            selectedProject = projects->Item(i);
            break;
        }
    }
    return selectedProject;
}

void wxcHelper::GetAllFiles(FilesList& files, const wxString& filterExt)
{
    wxString filterExtLowerCase = filterExt;
    filterExtLowerCase.MakeLower();

    ProjectsArray* projects = Manager::Get()->GetProjectManager()->GetProjects();
    for ( size_t i=0; i<projects->GetCount(); ++i ) {
        cbProject* pProj = projects->Item(i);
        const FilesList& fileList = pProj->GetFilesList();
        FilesList::const_iterator iter = fileList.begin();
        for( ; iter != fileList.end(); ++iter ) {
            if( filterExtLowerCase.IsEmpty() || filterExtLowerCase == (*iter)->file.GetExt().MakeLower() ) {
                files.insert( (*iter) );
            }
        }
    }
}

bool wxcHelper::ReadFileContent(const wxString& filepath, wxString& content)
{
    wxFFile fp(filepath, wxT("r+b"));
    if ( fp.IsOpened() ) {
        fp.ReadAll(&content, wxConvUTF8);
        fp.Close();
        return true;
    }
    return false;
}

bool wxcHelper::WriteFileContent(const wxString& filepath, const wxString& content)
{
    wxFFile fp(filepath, wxT("w+b"));
    if ( fp.IsOpened() ) {
        fp.Write( content );
        fp.Close();
        return true;
    }
    return false;
}
