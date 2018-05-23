#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;

class DetectorMessenger: public G4UImessenger
{
	public:

		DetectorMessenger(DetectorConstruction*);
		virtual ~DetectorMessenger();
		virtual void SetNewValue(G4UIcommand*, G4String);
 
	private:

		DetectorConstruction*        Detector;
		G4UIdirectory*               fDetectorDir;
		G4UIdirectory*               fVolumesDir;
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmd;
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdX;//Largo del moderador 1 en X
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdY;//Largo del moderador 1 en Y
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdZ;//Largo del moderador 1 en Z
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdX_2;//Largo del moderador 2 en X
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdY_2;//Largo del moderador 2 en Y
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdZ_2;//Largo del moderador 2 en Z
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdX_3;//Largo del moderador 3 en X
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdY_3;//Largo del moderador 3 en Y
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdZ_3;//Largo del moderador 3 en Z
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdX_Core;//Largo del Core en X
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdY_Core;//Largo del Core en Y
		G4UIcmdWithADoubleAndUnit*   fSampleThicknessCmdZ_Core;//Largo del Core en Z
		G4UIcmdWithADoubleAndUnit*   fdiamCmd;  
		G4UIcmdWithADoubleAndUnit*   fdiamCmdCad;  //cambia el radio de la lámina de Cadmio
		G4UIcmdWithADoubleAndUnit*   fdiamCmdAl;  //cambia el radio de la lámina de Aluminio
		G4UIcmdWithAString*        	 SampleDetMaterCmd; //Cambia el material del detector
		G4UIcmdWithAString*        	 SampleMaterCmdC1; //Cambia el material Moderador de la Primera Capa     
		G4UIcmdWithAString*        	 SampleMaterCmdCad; //Cambia el material Moderador de la Capa de Cadmio 
		G4UIcmdWithAString*        	 SampleMaterCmdAl; //Cambia el material del Aluminio
		G4UIcmdWithAString*        	 SampleMaterCmdC2; //Cambia el material Moderador de la Segunda Capa
		G4UIcmdWithAString*        	 SampleMaterCmdC3; //Cambia el material Moderador de la Tercera Capa
		G4UIcmdWithAString*        	 SampleMaterCmdCore; //Cambia el material Moderador del Core
		G4UIcommand*                 fDefaultsCmd;
};

#endif


