#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4Scintillation.hh"
#include "G4UIcmdWithAString.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* sample)
 : Detector(sample)
{
	//Setup a command directory for detector controls with guidance
	fDetectorDir = new G4UIdirectory("/shield/sample/");
	fDetectorDir->SetGuidance("Geometry control of the sample");

	fVolumesDir = new G4UIdirectory("/shield/sample/volumes/");
	fVolumesDir->SetGuidance("Enable/disable volumes");

	//Various commands for modifying detector geometry
	fSampleThicknessCmd = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThickness",this);
	fSampleThicknessCmd->SetGuidance("Set the thickness of the sample.");
	fSampleThicknessCmd->SetParameterName("d_mtl",false);
	fSampleThicknessCmd->SetDefaultUnit("mm");
	fSampleThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	//Cambia el ancho del moderador 1 en X
	fSampleThicknessCmdX = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessX",this);
	fSampleThicknessCmdX->SetGuidance("Setea el moderador en X.");
	fSampleThicknessCmdX->SetParameterName("d_mtlx",false);
	fSampleThicknessCmdX->SetDefaultUnit("mm");
	fSampleThicknessCmdX->AvailableForStates(G4State_PreInit,G4State_Idle);  

	//Cambia el ancho del moderador 1 en Y
	fSampleThicknessCmdY = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessY",this);
	fSampleThicknessCmdY->SetGuidance("Setea el moderador en Y.");
	fSampleThicknessCmdY->SetParameterName("d_mtly",false);
	fSampleThicknessCmdY->SetDefaultUnit("mm");
	fSampleThicknessCmdY->AvailableForStates(G4State_PreInit,G4State_Idle);  

	  //Cambia el ancho del moderador 1 en Z
	fSampleThicknessCmdZ = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessZ",this);
	fSampleThicknessCmdZ->SetGuidance("Setea el moderador en Z.");
	fSampleThicknessCmdZ->SetParameterName("d_mtlz",false);
	fSampleThicknessCmdZ->SetDefaultUnit("mm");
	fSampleThicknessCmdZ->AvailableForStates(G4State_PreInit,G4State_Idle);  

	//Cambia el ancho del moderador 2 en X
	fSampleThicknessCmdX_2 = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessX_2",this);
	fSampleThicknessCmdX_2->SetGuidance("Setea el moderador 2 en X.");
	fSampleThicknessCmdX_2->SetParameterName("d_mtlx_2",false);
	fSampleThicknessCmdX_2->SetDefaultUnit("mm");
	fSampleThicknessCmdX_2->AvailableForStates(G4State_PreInit,G4State_Idle);  

	//Cambia el ancho del moderador 2 en Y
	fSampleThicknessCmdY_2 = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessY_2",this);
	fSampleThicknessCmdY_2->SetGuidance("Setea el moderador 2 en Y.");
	fSampleThicknessCmdY_2->SetParameterName("d_mtly_2",false);
	fSampleThicknessCmdY_2->SetDefaultUnit("mm");
	fSampleThicknessCmdY_2->AvailableForStates(G4State_PreInit,G4State_Idle);  

	  //Cambia el ancho del moderador 2  en Z
	fSampleThicknessCmdZ_2 = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessZ_2",this);
	fSampleThicknessCmdZ_2->SetGuidance("Setea el moderador 2 en Z.");
	fSampleThicknessCmdZ_2->SetParameterName("d_mtlz_2",false);
	fSampleThicknessCmdZ_2->SetDefaultUnit("mm");
	fSampleThicknessCmdZ_2->AvailableForStates(G4State_PreInit,G4State_Idle);  

	  //Cambia el ancho del moderador 3 en X
	fSampleThicknessCmdX_3 = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessX_3",this);
	fSampleThicknessCmdX_3->SetGuidance("Setea el moderador 3 en X.");
	fSampleThicknessCmdX_3->SetParameterName("d_mtlx_3",false);
	fSampleThicknessCmdX_3->SetDefaultUnit("mm");
	fSampleThicknessCmdX_3->AvailableForStates(G4State_PreInit,G4State_Idle);  

	//Cambia el ancho del moderador 3 en Y
	fSampleThicknessCmdY_3 = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessY_3",this);
	fSampleThicknessCmdY_3->SetGuidance("Setea el moderador 3 en Y.");
	fSampleThicknessCmdY_3->SetParameterName("d_mtly_3",false);
	fSampleThicknessCmdY_3->SetDefaultUnit("mm");
	fSampleThicknessCmdY_3->AvailableForStates(G4State_PreInit,G4State_Idle);  

	  //Cambia el ancho del moderador 3  en Z
	fSampleThicknessCmdZ_3 = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessZ_3",this);
	fSampleThicknessCmdZ_3->SetGuidance("Setea el moderador 3 en Z.");
	fSampleThicknessCmdZ_3->SetParameterName("d_mtlz_3",false);
	fSampleThicknessCmdZ_3->SetDefaultUnit("mm");
	fSampleThicknessCmdZ_3->AvailableForStates(G4State_PreInit,G4State_Idle);  
	
		  //Cambia el ancho del Core
	fSampleThicknessCmdX_Core = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessX_Core",this);
	fSampleThicknessCmdX_Core->SetGuidance("Setea el Core en X.");
	fSampleThicknessCmdX_Core->SetParameterName("d_mtlx_Core",false);
	fSampleThicknessCmdX_Core->SetDefaultUnit("mm");
	fSampleThicknessCmdX_Core->AvailableForStates(G4State_PreInit,G4State_Idle);  

	//Cambia el ancho del Core en Y
	fSampleThicknessCmdY_Core = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessY_Core",this);
	fSampleThicknessCmdY_Core->SetGuidance("Setea el Core en Y.");
	fSampleThicknessCmdY_Core->SetParameterName("d_mtly_Core",false);
	fSampleThicknessCmdY_Core->SetDefaultUnit("mm");
	fSampleThicknessCmdY_Core->AvailableForStates(G4State_PreInit,G4State_Idle);  

	  //Cambia el ancho del Core
	fSampleThicknessCmdZ_Core = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/sampleThicknessZ_Core",this);
	fSampleThicknessCmdZ_Core->SetGuidance("Setea el Core en Z.");
	fSampleThicknessCmdZ_Core->SetParameterName("d_mtlz_Core",false);
	fSampleThicknessCmdZ_Core->SetDefaultUnit("mm");
	fSampleThicknessCmdZ_Core->AvailableForStates(G4State_PreInit,G4State_Idle);  
	
	
	//cambia el diametro de la lámina de Cadmio
		fdiamCmdCad = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/Diametro_Cad",this);
	fdiamCmdCad->SetGuidance("Set the diam of sample.");
	fdiamCmdCad->SetParameterName("diamCad",false);
	fdiamCmdCad->SetDefaultUnit("mm");
	fdiamCmdCad->AvailableForStates(G4State_PreInit,G4State_Idle);
	
	//cambia el diametro de la lámina de Aluminio
		fdiamCmdAl = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/Diametro_Al",this);
	fdiamCmdAl->SetGuidance("Set the diam of sample.");
	fdiamCmdAl->SetParameterName("diamAl",false);
	fdiamCmdAl->SetDefaultUnit("mm");
	fdiamCmdAl->AvailableForStates(G4State_PreInit,G4State_Idle);



	//  fSampleThicknessCmd->SetToBeBroadcasted(false);

	fdiamCmd = new G4UIcmdWithADoubleAndUnit
	("/shield/sample/Diametro_Det",this);
	fdiamCmd->SetGuidance("Set the diam of sample.");
	fdiamCmd->SetParameterName("diam",false);
	fdiamCmd->SetDefaultUnit("mm");
	fdiamCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	//  fdiamCmd->SetToBeBroadcasted(false);

	fDefaultsCmd = new G4UIcommand("/shield/sample/defaults",this);
	fDefaultsCmd->SetGuidance("Set all detector geometry values to defaults.");
	fDefaultsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	//  fDefaultsCmd->SetToBeBroadcasted(false);
	
	// Cambia el Material Moderador De la Capa de Cadmio
	SampleMaterCmdCad = new G4UIcmdWithAString("/shield/sample/setSampleMatCad",this);
	SampleMaterCmdCad->SetGuidance("Select Material of the Sample.");
	SampleMaterCmdCad->SetParameterName("choice",false);
	SampleMaterCmdCad->AvailableForStates(G4State_PreInit,G4State_Idle);

	// Cambia el Material Moderador De la Primera Capa
	SampleMaterCmdC1 = new G4UIcmdWithAString("/shield/sample/setSampleMatC1",this);
	SampleMaterCmdC1->SetGuidance("Select Material of the Sample.");
	SampleMaterCmdC1->SetParameterName("choice",false);
	SampleMaterCmdC1->AvailableForStates(G4State_PreInit,G4State_Idle);

	// Cambia el Material Moderador De la Segunda Capa
	SampleMaterCmdC2 = new G4UIcmdWithAString("/shield/sample/setSampleMatC2",this);
	SampleMaterCmdC2->SetGuidance("Select Material of the Sample.");
	SampleMaterCmdC2->SetParameterName("choice",false);
	SampleMaterCmdC2->AvailableForStates(G4State_PreInit,G4State_Idle);

	// Cambia el Material Moderador De la Tercera Capa
	SampleMaterCmdC3 = new G4UIcmdWithAString("/shield/sample/setSampleMatC3",this);
	SampleMaterCmdC3->SetGuidance("Select Material of the Sample.");
	SampleMaterCmdC3->SetParameterName("choice",false);

	SampleMaterCmdC3->SetDefaultValue("Air");
	SampleMaterCmdC3->AvailableForStates(G4State_PreInit,G4State_Idle);
	

	 // Cambia el Material Moderador Del Core
	SampleMaterCmdCore = new G4UIcmdWithAString("/shield/sample/setSampleMatCore",this);
	SampleMaterCmdCore->SetGuidance("Select Material of the Sample.");
	SampleMaterCmdCore->SetParameterName("choice",false);
	SampleMaterCmdCore->AvailableForStates(G4State_PreInit,G4State_Idle);
	
		 // Cambia el Material del Aluminio
	SampleMaterCmdAl = new G4UIcmdWithAString("/shield/sample/setSampleMatAl",this);
	SampleMaterCmdAl->SetGuidance("Select Material of the Sample.");
	SampleMaterCmdAl->SetParameterName("choice",false);
	SampleMaterCmdAl->AvailableForStates(G4State_PreInit,G4State_Idle);


	// Cambia el Material del Detector 
	SampleDetMaterCmd = new G4UIcmdWithAString("/shield/sample/setSampleDetMat",this);
	SampleDetMaterCmd->SetGuidance("Select Material of the Detector.");
	SampleDetMaterCmd->SetParameterName("choiceDet",false);
	SampleDetMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
	//~ delete fSampleThicknessCmd;
	//~ delete fSampleThicknessCmdX;
	//~ delete fSampleThicknessCmdY;
	//~ delete fSampleThicknessCmdZ;
	//~ delete fSampleThicknessCmdX_2;
	//~ delete fSampleThicknessCmdY_2;
	//~ delete fSampleThicknessCmdZ_2;
	//~ delete fSampleThicknessCmdX_3;
	//~ delete fSampleThicknessCmdY_3;
	//~ delete fSampleThicknessCmdZ_3;
	//~ delete fdiamCmd;
	//~ delete fDetectorDir;
	//~ delete fVolumesDir;
	//~ delete fDefaultsCmd;
	//~ delete SampleMaterCmdC3;
	//~ delete SampleMaterCmdC1;
	//~ delete SampleMaterCmdC1;
	//~ delete SampleMaterCmdCore;
	//~ delete SampleDetMaterCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == fSampleThicknessCmd){
	Detector->SetSampleThickness(fSampleThicknessCmd
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del moderador 1 en X
	else if (command == fSampleThicknessCmdX){
		Detector->SetSampleThicknessX(fSampleThicknessCmdX
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del moderador 1 en Y
	else if (command == fSampleThicknessCmdY){
		Detector->SetSampleThicknessY(fSampleThicknessCmdY
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del moderador 1 en Z
	else if (command == fSampleThicknessCmdZ){
		Detector->SetSampleThicknessZ(fSampleThicknessCmdZ
									 ->GetNewDoubleValue(newValue));
	}

	//funcion que cambia el ancho del moderador 2 en X
	else if (command == fSampleThicknessCmdX_2){
		Detector->SetSampleThicknessX_2(fSampleThicknessCmdX_2
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del moderador 2 en Y
	else if (command == fSampleThicknessCmdY_2){
		Detector->SetSampleThicknessY_2(fSampleThicknessCmdY_2
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del moderador 2 en Z
	else if (command == fSampleThicknessCmdZ_2){
		Detector->SetSampleThicknessZ_2(fSampleThicknessCmdZ_2
									 ->GetNewDoubleValue(newValue));
	}

	  //funcion que cambia el ancho del moderador 3 en X
	else if (command == fSampleThicknessCmdX_3){
		Detector->SetSampleThicknessX_3(fSampleThicknessCmdX_3
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del moderador 3 en Y
	else if (command == fSampleThicknessCmdY_3){
		Detector->SetSampleThicknessY_3(fSampleThicknessCmdY_3
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del moderador 3 en Z
	else if (command == fSampleThicknessCmdZ_3){
		Detector->SetSampleThicknessZ_3(fSampleThicknessCmdZ_3
									 ->GetNewDoubleValue(newValue));
	}

	  //funcion que cambia el ancho del Core en X
	else if (command == fSampleThicknessCmdX_Core){
		Detector->SetSampleThicknessX_Core(fSampleThicknessCmdX_Core
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del Core en Y
	else if (command == fSampleThicknessCmdY_Core){
		Detector->SetSampleThicknessY_Core(fSampleThicknessCmdY_Core
									 ->GetNewDoubleValue(newValue));
	}
	//funcion que cambia el ancho del Core en Z
	else if (command == fSampleThicknessCmdZ_Core){
		Detector->SetSampleThicknessZ_Core(fSampleThicknessCmdZ_Core
									 ->GetNewDoubleValue(newValue));
	}





	//funcion que cambia el diametro del detector


	else if (command == fdiamCmd){
		Detector->SetSamplediam(fdiamCmd->GetNewDoubleValue(newValue));
	}
		//funcion que cambia el diametro de la lámina de Aluminio


	else if (command == fdiamCmdAl){
		Detector->SetSamplediamAl(fdiamCmdAl->GetNewDoubleValue(newValue));
	}
	
	
	//funcion que cambia el diametro de la Lamina de Cadmio


	else if (command == fdiamCmdCad){
		Detector->SetSamplediamCad(fdiamCmdCad->GetNewDoubleValue(newValue));
	}

	// Cambia el material del detector
	else if (command == SampleDetMaterCmd) {
		Detector->SetSampleDetMaterial(newValue);
	}
	
		// Cambia el material del Aluminio
	else if (command == SampleMaterCmdAl) {
		Detector->SetSampleMaterialAl(newValue);
	}
	
	//Cambia el material Moderador de la Primera Capa
	else if (command == SampleMaterCmdC1) {
		Detector->SetSampleMaterialC1(newValue);
	}
	
		//Cambia el material de Cadmio
	else if (command == SampleMaterCmdCad) {
		Detector->SetSampleMaterialCad(newValue);
	}

	//Cambia el material Moderador de la Segunda Capa
	else if (command == SampleMaterCmdC2) {
		Detector->SetSampleMaterialC2(newValue);
	}

	//Cambia el Material Moderador de la Tercera Capa
	else if (command == SampleMaterCmdC3) {
		Detector->SetSampleMaterialC3(newValue);
	}

	//Cambia el Material Moderador del Core
	else if (command == SampleMaterCmdCore) {
		Detector->SetSampleMaterialCore(newValue);
	}

	else if (command == fDefaultsCmd){
		Detector->SetDefaults();
	}

}
