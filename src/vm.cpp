#include "fahangte/vm.hpp"
#include <iostream>

void VirtualMachine::exeHALT() { std::cout << "exeHALT" << std::endl; }
void VirtualMachine::exeNOP() { std::cout << "exeNOP" << std::endl; }
void VirtualMachine::exeSTDINR() { std::cout << "exeSTDINR" << std::endl; }
void VirtualMachine::exeSTDINM() { std::cout << "exeSTDINM" << std::endl; }
void VirtualMachine::exeSTDOUTR() { std::cout << "exeSTDOUTR" << std::endl; }
void VirtualMachine::exeSTDOUTM() { std::cout << "exeSTDOUTM" << std::endl; }
void VirtualMachine::exeSTDOUTI() { std::cout << "exeSTDOUTI" << std::endl; }
void VirtualMachine::exeJMPR() { std::cout << "exeJMPR" << std::endl; }
void VirtualMachine::exeJMPM() { std::cout << "exeJMPM" << std::endl; }
void VirtualMachine::exeJMPI() { std::cout << "exeJMPI" << std::endl; }
void VirtualMachine::exeJER() { std::cout << "exeJER" << std::endl; }
void VirtualMachine::exeJEM() { std::cout << "exeJEM" << std::endl; }
void VirtualMachine::exeJEI() { std::cout << "exeJEI" << std::endl; }
void VirtualMachine::exeJNER() { std::cout << "exeJNER" << std::endl; }
void VirtualMachine::exeJNEM() { std::cout << "exeJNEM" << std::endl; }
void VirtualMachine::exeJNEI() { std::cout << "exeJNEI" << std::endl; }
void VirtualMachine::exeJLTR() { std::cout << "exeJLTR" << std::endl; }
void VirtualMachine::exeJLTM() { std::cout << "exeJLTM" << std::endl; }
void VirtualMachine::exeJLTI() { std::cout << "exeJLTI" << std::endl; }
void VirtualMachine::exeJLER() { std::cout << "exeJLER" << std::endl; }
void VirtualMachine::exeJLEM() { std::cout << "exeJLEM" << std::endl; }
void VirtualMachine::exeJLEI() { std::cout << "exeJLEI" << std::endl; }
void VirtualMachine::exeJGTR() { std::cout << "exeJGTR" << std::endl; }
void VirtualMachine::exeJGTM() { std::cout << "exeJGTM" << std::endl; }
void VirtualMachine::exeJGTI() { std::cout << "exeJGTI" << std::endl; }
void VirtualMachine::exeJGER() { std::cout << "exeJGER" << std::endl; }
void VirtualMachine::exeJGEM() { std::cout << "exeJGEM" << std::endl; }
void VirtualMachine::exeJGEI() { std::cout << "exeJGEI" << std::endl; }

void VirtualMachine::exeMOVRR() { std::cout << "exeMOVRR" << std::endl; }
void VirtualMachine::exeMOVRM() { std::cout << "exeMOVRM" << std::endl; }
void VirtualMachine::exeMOVRI() { std::cout << "exeMOVRI" << std::endl; }
void VirtualMachine::exeMOVMR() { std::cout << "exeMOVMR" << std::endl; }
void VirtualMachine::exeMOVMI() { std::cout << "exeMOVMI" << std::endl; }

void VirtualMachine::exeADDRR() { std::cout << "exeADDRR" << std::endl; }
void VirtualMachine::exeADDRM() { std::cout << "exeADDRM" << std::endl; }
void VirtualMachine::exeADDRI() { std::cout << "exeADDRI" << std::endl; }
void VirtualMachine::exeADDMR() { std::cout << "exeADDMR" << std::endl; }
void VirtualMachine::exeADDMI() { std::cout << "exeADDMI" << std::endl; }

void VirtualMachine::exeSUBRR() { std::cout << "exeSUBRR" << std::endl; }
void VirtualMachine::exeSUBRM() { std::cout << "exeSUBRM" << std::endl; }
void VirtualMachine::exeSUBRI() { std::cout << "exeSUBRI" << std::endl; }
void VirtualMachine::exeSUBMR() { std::cout << "exeSUBMR" << std::endl; }
void VirtualMachine::exeSUBMI() { std::cout << "exeSUBMI" << std::endl; }

void VirtualMachine::exeMULRR() { std::cout << "exeMULRR" << std::endl; }
void VirtualMachine::exeMULRM() { std::cout << "exeMULRM" << std::endl; }
void VirtualMachine::exeMULRI() { std::cout << "exeMULRI" << std::endl; }
void VirtualMachine::exeMULMR() { std::cout << "exeMULMR" << std::endl; }
void VirtualMachine::exeMULMI() { std::cout << "exeMULMI" << std::endl; }

void VirtualMachine::exeDIVRR() { std::cout << "exeDIVRR" << std::endl; }
void VirtualMachine::exeDIVRM() { std::cout << "exeDIVRM" << std::endl; }
void VirtualMachine::exeDIVRI() { std::cout << "exeDIVRI" << std::endl; }
void VirtualMachine::exeDIVMR() { std::cout << "exeDIVMR" << std::endl; }
void VirtualMachine::exeDIVMI() { std::cout << "exeDIVMI" << std::endl; }

void VirtualMachine::exeMODRR() { std::cout << "exeMODRR" << std::endl; }
void VirtualMachine::exeMODRM() { std::cout << "exeMODRM" << std::endl; }
void VirtualMachine::exeMODRI() { std::cout << "exeMODRI" << std::endl; }
void VirtualMachine::exeMODMR() { std::cout << "exeMODMR" << std::endl; }
void VirtualMachine::exeMODMI() { std::cout << "exeMODMI" << std::endl; }

void VirtualMachine::exeCMPRR() { std::cout << "exeCMPRR" << std::endl; }
void VirtualMachine::exeCMPRM() { std::cout << "exeCMPRM" << std::endl; }
void VirtualMachine::exeCMPRI() { std::cout << "exeCMPRI" << std::endl; }
void VirtualMachine::exeCMPMR() { std::cout << "exeCMPMR" << std::endl; }
void VirtualMachine::exeCMPMI() { std::cout << "exeCMPMI" << std::endl; }