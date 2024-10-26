#include "VirtualMemoryManager.hpp"


int main() {
   VirtualMemoryManager object;
   vector<int32_t> logicalAddresses = {1, 256, 32768, 32769, 128, 65534, 33153};
   vector<int> getPageOffset;
   for(size_t i = 0; i < logicalAddresses.size(); ++i) {
      // El primer elemento es el número de página y el segundo el offset.
      getPageOffset = object.CalcPageOffset(logicalAddresses[i]);
      cout << endl;
      object.verifyPage(getPageOffset[0]);
      int32_t physicalAddress = object.calcPhysicalAddress(getPageOffset[0], getPageOffset[1]);
      cout << "Direccion logica: " << logicalAddresses[i] << " Numero de pagina: " << getPageOffset[0] << " Offset: " << getPageOffset[1] << " Direccion en memoria fisica: " << physicalAddress << " Valor en direccion en memoria fisica: " << static_cast<int>(static_cast<unsigned char>(object.getPhysicalAddressValue(physicalAddress))) << endl;
   }
   cout << endl;

   // Se deben imprimir las estadísticas, de porcentaje de fallos de páginas que hubo.
   int faultPercentage = (object.getFaultPages()*100)/object.getTotalPages();
   cout << "El porcentaje de fallos de paginas es: %" << faultPercentage;

   // Esta función era solo para probar si se guardan valores bien en las páginas.
   //cout << "numero en page Table: " << object.getPageValue(250);

   // Esta era para ver los valores copiados en la memoria física.
   // object.readPhysicalMemory(5);

   
   
   return 0;
}