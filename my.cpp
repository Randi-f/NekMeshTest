/*
 * @Author: shihan
 * @Date: 2024-04-18 14:13:30
 * @version: 1.0
 * @description: 
 */
#include <LibUtilities/BasicConst/GitRevision.h>
#include <LibUtilities/BasicUtils/Timer.h>
#include <boost/algorithm/string.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <string>

#include <NekMesh/Module/Module.h>

using namespace std;
using namespace Nektar::NekMesh;

int main(int argc, char *argv[])
{
    // create a logger
    Logger log;

    MeshSharedPtr mesh = std::shared_ptr<Mesh>(new Mesh());
    mesh->m_metadata["NekMeshCommandLine"] = "ADR_mesh.msh ADR_mesh.xml";

    vector<ModuleSharedPtr> modules;
    vector<string> modcmds;


    ModuleKey in_module;
    // ModuleType t = eInputModule;
    in_module.first=eInputModule;
    in_module.second="msh";
    ModuleKey out_module;
    // ModuleType t2 = eOutputModule;
    out_module.first=eOutputModule;
    out_module.second="xml";

    // Create module.
    ModuleSharedPtr mod = GetModuleFactory().CreateInstance(in_module, mesh);
    mod->SetLogger(log);
    mod->RegisterConfig("infile", "ADR_mesh.msh");
    // Ensure configuration options have been set.
    mod->SetDefaults();
    modules.push_back(mod);
    

    ModuleSharedPtr mod1 = GetModuleFactory().CreateInstance(out_module, mesh);
    mod1->SetLogger(log);
    modules.push_back(mod1);
    mod1->RegisterConfig("outfile", "ADR_mesh.xml");
    // Ensure configuration options have been set.
    mod1->SetDefaults();


    // Run mesh process.
    for (int i = 0; i < modules.size(); ++i)
    {
        Nektar::LibUtilities::Timer t;
        t.Start();
        try
        {
            cout << "try process for " << modules[i]->GetModuleName() << endl;
            modules[i]->Process();
        }
        catch (NekMeshError &e)
        {
            return 1;
        }
        t.Stop();

        log.SetPrefix(modules[i]->GetModuleName());

    }


    return 0;
}
