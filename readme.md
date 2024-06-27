<!--
 * @Author: shihan
 * @Date: 2024-06-07 11:52:10
 * @version: 1.0
 * @description: 
-->
export CMAKE_PREFIX_PATH=/Users/shihan/D/IC/Individual_project/codes/nektar++/build/dist/lib/nektar++/cmake

CMAKE_MODULE_PREFIX_PATH=/homes/sf23/Desktop/nektar++/build/dist/lib64/nektar++/cmake/ cmake ..

NekMesh ADR_mesh.msh ADR_mesh.xml

Nekmesh  -v  t106a.mcf  t106a.xml
Nekmesh  -m  peralign:surf1=1:surf2=7:dir=y  -m  peralign:surf1=2:surf2=6:dir=y  -m peralign:surf1=3:surf2=5:dir=y   t106a.xml t106a_aligned.xml

Convert the .xml file into a .xml file with periodic edges aligned
NekMesh -m peralign:surf1=200:surf2=400:dir=x ADR_mesh.xml ADR_mesh_aligned.xml