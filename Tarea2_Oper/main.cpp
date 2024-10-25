#include "VirtualMemoryManager.hpp"


int main() {
   VirtualMemoryManager object;
   vector<int32_t> logicalAddresses = {1, 256, 32768, 32769, 128, 65534, 33153};
   vector<int> getPageOffset;
   for(size_t i = 0; i < logicalAddresses.size(); ++i) {
        getPageOffset = object.CalcPageOffset(logicalAddresses[i]);
        cout << "Direccion logica: " << logicalAddresses[i] << " Numero de pagina: " << getPageOffset[0] << " Offset: " << getPageOffset[1] << endl;
   }
   // Esta función era solo para probar si se guardan valores bien en las páginas.
   cout << "numero en page Table: " << object.getPageValue(250);

   
   return 0;
}