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
    mesh->m_metadata["NekMeshCommandLine"] = "naca.mcf naca.xml";

    vector<ModuleSharedPtr> modules;
    vector<string> modcmds;


    ModuleKey in_module;
    in_module.first=eInputModule;
    in_module.second="mcf";
    ModuleKey out_module;
    in_module.first=eOutputModule;
    in_module.second="xml";

    // Create module.
    ModuleSharedPtr mod = GetModuleFactory().CreateInstance(in_module, mesh);
    mod->SetLogger(log);
    mod->RegisterConfig("infile", "naca.mcf");
    modules.push_back(mod);
    

    // ModuleSharedPtr mod1 = GetModuleFactory().CreateInstance(out_module, mesh);
    // mod1->SetLogger(log);
    // modules.push_back(mod1);
    // mod1->RegisterConfig("outfile", "naca.xml");


    // Run mesh process.
    // for (int i = 0; i < modules.size(); ++i)
    // {
    //     Nektar::LibUtilities::Timer t;
    //     t.Start();
    //     try
    //     {
    //         modules[i]->Process();
    //     }
    //     catch (NekMeshError &e)
    //     {
    //         return 1;
    //     }
    //     t.Stop();

    //     log.SetPrefix(modules[i]->GetModuleName());

    // }


    return 0;
}
