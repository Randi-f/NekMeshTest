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

#include <map>

using namespace std;
using namespace Nektar::NekMesh;



MeshSharedPtr mesh = std::shared_ptr<Mesh>(new Mesh());
vector<ModuleSharedPtr> modules;


void addInputModule(Logger log, string inputFile){
    ModuleKey in_module;
    in_module.first=eInputModule;
    // 找到最后一个点的位置
    size_t pos = inputFile.find_last_of(".");
    if (pos != std::string::npos) {
        // 返回点之后的所有字符
        in_module.second=inputFile.substr(pos + 1);
    } else {
        // 如果没有找到点，返回空字符串
        return ;
    }
    // Create module.
    ModuleSharedPtr mod = GetModuleFactory().CreateInstance(in_module, mesh);
    mod->SetLogger(log);
    mod->RegisterConfig("infile", inputFile);
    // Ensure configuration options have been set.
    mod->SetDefaults();
    modules.push_back(mod);
}

void addOutputFile(Logger log, string filePath){
    ModuleKey out_module;
    out_module.first=eOutputModule;
    out_module.second="xml";
    ModuleSharedPtr mod1 = GetModuleFactory().CreateInstance(out_module, mesh);
    mod1->SetLogger(log);
    modules.push_back(mod1);
    mod1->RegisterConfig("outfile", "/Users/shihan/Desktop/ADR_mesh.xml");
    // Ensure configuration options have been set.
    mod1->SetDefaults();
}

void addProcessModule(Logger log, map<string, string>values){
    ModuleKey process_module;
    process_module.first=eProcessModule;
    process_module.second="peralign";
    ModuleSharedPtr modp = GetModuleFactory().CreateInstance(process_module, mesh);
    modp->SetLogger(log);
    modules.push_back(modp);
    modp->RegisterConfig("surf1", values["surf1"]);
    modp->RegisterConfig("surf2", values["surf2"]);
    modp->RegisterConfig("dir", values["dir"]);
    // Ensure configuration options have been set.
    modp->SetDefaults();
}

int main(int argc, char *argv[])
{
    // create a logger
    auto logOutput = std::make_shared<StreamOutput>(std::cout);
    Logger log(logOutput, INFO);
    mesh->m_metadata["NekMeshCommandLine"] = "ADR_mesh.msh ADR_mesh.xml";
    addInputModule(log,"ADR_mesh.msh");
    // map<string, string>values;
    // values["surf1"]="200";
    // values["surf2"]="400";
    // values["dir"]="x";
    // addProcessModule(log, values);
    addOutputFile(log,"");

    

    log.SetPrefixLen(11);
    // Run mesh process.
    for (int i = 0; i < modules.size(); ++i)
    {
        Nektar::LibUtilities::Timer t;
        t.Start();
        try
        {
            modules[i]->GetLogger().SetPrefixLen(11);
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

    cout << mesh->m_edgeSet.begin() << endl;


    return 0;
}


