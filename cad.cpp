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

// 函数用于打印std::vector<std::array<NekDouble, 3>>到屏幕
void printVector(const std::vector<std::array<Nektar::NekDouble, 3>>& vec) {
    for (const auto& arr : vec) {
        std::cout << "(" << arr[0] << ", " << arr[1] << ", " << arr[2] << ")\n";
    }
}

int main(int argc, char *argv[])
{
    // create a logger
    auto logOutput = std::make_shared<StreamOutput>(std::cout);
    Logger m_log(logOutput, INFO);


    MeshSharedPtr mesh = std::shared_ptr<Mesh>(new Mesh());
    ModuleSharedPtr module;
     ////**** CAD ****////
    module = GetModuleFactory().CreateInstance(
        ModuleKey(eProcessModule, "loadcad"), mesh);
    module->SetLogger(m_log);
    module->RegisterConfig("filename", "t106a.geo");
    module->RegisterConfig("voidpoints", "");
    module->RegisterConfig("2D", "");


    module->SetDefaults();
    try{
        module->Process();
    }
    catch (NekMeshError &e)
    {
        return 1;
    }
    // 打印数据
    cout << "surf: "<< mesh->m_cad->GetNumSurf() << endl;

    //octree
    module = GetModuleFactory().CreateInstance(
        ModuleKey(eProcessModule, "loadoctree"), mesh);
    module->SetLogger(m_log);
    module->RegisterConfig("mindel", "0.002");
    module->RegisterConfig("maxdel", "0.035");
    module->RegisterConfig("eps", "0.00005");

    set<string> refinement;
    refinement.insert("-0.0712157,0.1,0.0,-0.0712157,-0.15,0.0,0.15,0.025");
    string m_refinement = "-0.0712157,0.1,0.0,-0.0712157,-0.15,0.0,0.15,0.025";
    

    module->RegisterConfig("refinement", m_refinement);
    

    module->SetDefaults();
    module->Process();

    bool m_2D = true;
    ////**** LINEAR MESHING ****////
    if (m_2D)
    {
        ////**** 2DGenerator ****////
        mesh->m_expDim   = 2;
        mesh->m_spaceDim = 2;
        module             = GetModuleFactory().CreateInstance(
            ModuleKey(eProcessModule, "2dgenerator"), mesh);

        module->SetLogger(m_log);
        bool m_makeBL=true;
        if (m_makeBL)
        {
            module->RegisterConfig("blcurves", "9-12");
            module->RegisterConfig("blthick", "0.012");
        }


        try
        {
            module->SetDefaults();
            module->Process();
        }
        catch (runtime_error &e)
        {
            m_log(WARNING) << "2D linear mesh generator failed with message:"
                           << endl;
            m_log(WARNING) << e.what() << endl;
            m_log(FATAL) << "No mesh file has been created." << endl;
        }
    }
    
    cout << mesh->GetNumElements() << endl;
    if (!mesh->m_edgeSet.empty()) {
        // Get the first element
        for (const auto& edgeSharedPtr : mesh->m_edgeSet) {
            // Dereference the shared pointer to call GetNodeCount()
            std::cout << "Edge pair: id=  " << edgeSharedPtr->m_n1->m_id << "," << edgeSharedPtr->m_n1->m_x << ", " << edgeSharedPtr->m_n1->m_y << ", " << edgeSharedPtr->m_n1->m_z<< std::endl;
            std::cout << "Edge pair: id=  " << edgeSharedPtr->m_n2->m_id << "," << edgeSharedPtr->m_n2->m_x << ", " << edgeSharedPtr->m_n2->m_y << ", " << edgeSharedPtr->m_n2->m_z<< std::endl;
        }
        // auto firstEdge = *mesh->m_edgeSet.begin(); // need to derenference

        // // Dereference the shared pointer to call GetNodeCount()
        // std::cout << "First edge node : " << firstEdge->m_n1->m_x << "," << firstEdge->m_n1->m_y << ", " << firstEdge->m_n1->m_z << std::endl;
    } else {
        std::cout << "EdgeSet is empty." << std::endl;
    }

    return 0;
}


