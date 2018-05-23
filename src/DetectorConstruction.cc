//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B3DetectorConstruction.cc 101905 2016-12-07 11:34:39Z gunter $
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"


#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDChargedFilter.hh"
#include "G4SDParticleFilter.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VSolid.hh"
#include "G4Orb.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"

#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
//~ #include "G4VSDFilter.hh"
//~ #include "G4SDParticleFilter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fCheckOverlaps(true)
{
	DefineMaterials();
  	//defaults
	fSampleThickness=20.*cm;
	fSampleThicknessX=20.*cm; //Ancho del moderador en X
	fSampleThicknessY=20.*cm; //Ancho del moderador en Y
	fSampleThicknessZ=20.*cm;//Ancho del moderador en Z
	fSampleThicknessX_2=20.*cm; //Ancho del moderador 2 en X
	fSampleThicknessY_2=20.*cm; //Ancho del moderador 2 en Y
	fSampleThicknessZ_2=20.*cm;//Ancho del moderador 2 en Z
	fSampleThicknessX_3=20.*cm; //Ancho del moderador 3 en X
	fSampleThicknessY_3=20.*cm; //Ancho del moderador 3 en Y
	fSampleThicknessZ_3=20.*cm;//Ancho del moderador 3 en Z
	fSampleThicknessX_Core= 100.*mm; //Ancho del Core en X
	fSampleThicknessY_Core= 100.*mm; //Ancho del Core en Y
	fSampleThicknessZ_Core= 100.*mm;//Ancho del Core en Z 
	fSampleRad = 63.8*mm;
	fSampleRadCad = 1.1*mm;
	fSampleRadAl =  1.*mm;
	SetSampleMaterialCad("Cadmium");//primera capa de material de Cadmio
	SetSampleMaterialAl("Aluminium");//Capa de material de Aluminio
	SetSampleMaterialC1("Air");//primera capa de material moderador
	SetSampleMaterialC2("Air");//segunda capa capa de material moderador
	SetSampleMaterialC3("Air");//Tercera capa capa de material moderador
	SetSampleMaterialCore("Boron_Polyethylene_TS");

	SetSampleDetMaterial("He3Gas");
	detectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
	delete detectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
	G4NistManager* man = G4NistManager::Instance();
	G4String name, symbol;             
	G4double a, z, density, pressure;     
	G4int ncomponents, natoms, iz, n;
	G4double fractionmass;

	G4bool isotopes = false;
	

	//~ G4Element* He = man->FindOrBuildElement("He", isotopes); 
	G4Element*  O = man->FindOrBuildElement("O" , isotopes); 
	G4Element*  N = man->FindOrBuildElement("N" , isotopes);
	G4Element* Si = man->FindOrBuildElement("Si", isotopes);
	G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);
	G4Element* B  = man->FindOrBuildElement("B" , isotopes);  
	G4Element* F  = man->FindOrBuildElement("F" , isotopes);   
	 new G4Material("Cadmium", z=48. , a=112.411*g/mole, density=8.64*g/cm3);
	// Isotopos //
	
	G4Isotope* He3 = new G4Isotope(name="He3", iz=2, n=3, a=3.00*g/mole);
	G4Element* Helium3 = new G4Element(name="Helium3", symbol="3He", ncomponents=1);
	Helium3->AddIsotope(He3, 100.*perCent);
	
	// Material Helio 3 ///valores de densidad y presión al 'ojo'/// //
	G4Material* He3Gas = new G4Material(name="He3Gas", density=0.004*g/cm3 , ncomponents=1, kStateGas, STP_Temperature , pressure=20.265*bar );
		He3Gas->AddElement(Helium3, natoms=1);

	// Material BF3 ///valores de densidad y presión al 'ojo'/// //														// 10.1325 //
	G4Material* BF3Gas = new G4Material(name="BF3Gas", density=2.76*kg/m3 , ncomponents=2, kStateGas, STP_Temperature , pressure=10.1325*bar );
		BF3Gas->AddElement(B, natoms=1);
		BF3Gas->AddElement(F, natoms=3);
	
	man->FindOrBuildMaterial("G4_WATER");
	
	  // Define air
	G4Material* air = new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
		air->AddElement(N, fractionmass=0.7);
		air->AddElement(O, fractionmass=0.3);

	// Define vacuum
	G4Material* vacuum = new G4Material("Vacuum", density= 1.e-5*g/cm3, 
					  ncomponents=1, kStateGas, STP_Temperature, 
					  2.e-2*bar);
		vacuum->AddMaterial(air, fractionmass=1.);
  
	
	// Create elements and materials for thermal scattering 
	// Polyethylene
	G4Element* elTSH = new G4Element("TS_H_of_Polyethylene", "H_POLYETHYLENE", 1.0, 1.0079*g/mole);
	G4Element* elC   = new G4Element("Carbon", "C", 6.0, 12.01*g/mole);

	G4Material* matCH2_TS = new G4Material("Polyethylene_TS", density=0.94*g/cm3, ncomponents=2);
		matCH2_TS->AddElement(elTSH, natoms=2);
		matCH2_TS->AddElement(elC, natoms=1);
		
	// 5% Borated Polyethylene

	G4Element* elB = new G4Element("Boron", "B", 5.0, 10.01*g/mole);

	G4Material* matBORON_CH2_TS = new G4Material("Boron_Polyethylene_TS", density=0.94*g/cm3, ncomponents=3);
		matBORON_CH2_TS->AddElement(elTSH, fractionmass=0.63333);
		matBORON_CH2_TS->AddElement(elC, fractionmass=0.31666);
		matBORON_CH2_TS->AddElement(elB, fractionmass=0.05);
		

	G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
		LSO->AddElement(Lu, 2);
		LSO->AddElement(Si, 1);
		LSO->AddElement(O , 5);

	new G4Material("Helium", z=2, a=3.0*g/mole, density=1.0*g/cm3);
	new G4Material("Aluminium", z=13, a=26.984*g/mole, density=2.698*g/cm3);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{

	//// Limpiando la geometria (Logico, Fisico y Solido) del Mundo ////

	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();

	G4double LargoModerador_Z = (42.5)*.5*cm;
	
	////Dimensiones del Detector///
	
    G4double innerRaduis_Det = 0.*cm; 		//	radio interno 
	G4double outerRaduis_Det =fSampleRad; 	// 	radio externo
	G4double hz = fSampleThickness;  		// 	largo del detector
	
	//// Dimensiones de la capa de Aluminio  //
	
	G4double innerRaduis_Al = outerRaduis_Det; 				 //radio interno
	G4double outerRaduis_Al = innerRaduis_Al + fSampleRadAl; //radio externo
	G4double hz_Al = LargoModerador_Z; 						 // largo del detector
	
	////Dimensiones de la capa de Cadmio///
	
	G4double innerRaduis_Cad = outerRaduis_Al;
	G4double outerRaduis_Cad =  innerRaduis_Cad + fSampleRadCad ;
	G4double hz_Cad = LargoModerador_Z; 

	
	////Dimensiones del Core ///
	
	
	G4double box_x_C = fSampleThicknessX_Core; 
	G4double box_y_C = fSampleThicknessY_Core;
	G4double box_z_C = LargoModerador_Z;
	
	//Dimensiones del Primer Material moderador (Desde adentro hacia afuera) ////
	
	
	G4double box_x = box_x_C + fSampleThicknessX ;
	G4double box_y = box_y_C + fSampleThicknessY;
	G4double box_z = LargoModerador_Z;
	
	//Dimensiones del Segundo Material moderador (Desde adentro hacia afuera) ////
	
	G4double box_x_2 = box_x + fSampleThicknessX_2 ;
	G4double box_y_2 = box_y + fSampleThicknessY_2 ;
	G4double box_z_2 = LargoModerador_Z;
	
	//Dimensiones del Tercer Material moderador (Desde adentro hacia afuera) ////
	
	
	G4double box_x_3 = box_x_2 + fSampleThicknessX_3 ;
	G4double box_y_3 = box_y_2 + fSampleThicknessY_3;
	G4double box_z_3 = LargoModerador_Z;
	
	
	
	
	//~ G4NistManager* nist = G4NistManager::Instance();
	G4Material* air = G4Material::GetMaterial("Air");
	//~ G4Material* water = G4Material::GetMaterial("G4_WATER");
	//~ G4Material* vacuum = G4Material::GetMaterial("Vacuum");
	//~ G4Material* Aluminio = G4Material::GetMaterial("Aluminium");
	//~ G4Material* cadmium = G4Material::GetMaterial("Cadmium");
	//~ G4Material* He3Gas = G4Material::GetMaterial("He3Gas");
	//~ G4Material* BF3Gas = G4Material::GetMaterial("BF3Gas");
	//~ G4Material* He = G4Material::GetMaterial("Helium");
	//~ G4Material* matCH2_TS = G4Material::GetMaterial("Polyethylene_TS");
	//~ G4Material* matBORON_CH2_TS = G4Material::GetMaterial("Boron_Polyethylene_TS");
									//////////////////////////////////////////////////////////////////////////////////		
	//     
	// World
	//
	G4double world_sizeX = 500*cm;
	G4double world_sizeY = 500*cm;
	G4double world_sizeZ = 500*cm;

	G4Box* solidWorld =    
		new G4Box("WorldSolid",                       //its name
			world_sizeX, world_sizeY, world_sizeZ); //its size
      
	G4LogicalVolume* logicWorld =                         
		new G4LogicalVolume(solidWorld,      //its solid
                        air,				 //its material
                        "WorldLogic");            //its name
                                   
	G4VPhysicalVolume* physWorld = 
		new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "WorldPhys",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps 


////////////////////////////////////////////////////////////////////////
///////////////////////////CONO DE SOMBRA //////////////////////////////
////////////////////////////////////////////////////////////////////////
//***********************************************************************
// Las nuevas dimensiones del moderador son (para la geometria que 		*
// estamos dando en neutron.mac) : 										*	
// 26.04 cm x 26.04 cm x 37.5 cm ( X Y Z)								*
// Para parametrizar aumentamos en un centimetro el largo en X e Y 		*
// de la caja,por lo tanto la dimensiones de la caja que consideramos	*
// para parametrizar  es 27.04 cm x 27.04 cm x 37.5 cm (X Y Z) 			*
//***********************************************************************
////////////////////////////////////////////////////////////////////////

//~ //Grosores
	//~ G4double thickness_HDPE= 42.5*mm; //Grosor del HDPE negro
	//~ G4double thickness_HDPE_B5_H = 25*mm; // grosor del HDPE-B 5% mas grueso (HIGHER)
	//~ G4double thickness_HDPE_B5_L = 12.7*mm; // grosor del HDPE-B 5% mas delgado (LESS)
	//~ G4double thickness_cadmio= 1.1*mm;  // grosor lamina de Cadmio

															
//~ //Modulo 4 (rear-end) - (HDPE negro) 4.25 cm grosor
	
	//~ G4double d_cone_mod = 600*mm;  // distancia entre el centro rear-end del cono de sombra
								  //~ // y el centro del moderador-detector
	//~ G4double pos4_x = d_cone_mod + box_x_3; // posicion del centro del modulo 4 con 
											//~ //respecto al centro del detector, box_x_3 = 13.02
	
	//~ G4ThreeVector pos4 = G4ThreeVector(pos4_x, 0, 0); //x,y,z 73.02 = 13.02 + 60
	//~ G4Box* modulo4_solid = new G4Box("modulo4",2.125*cm ,6.15*cm,8.75*cm); //x,y,z
	//~ G4LogicalVolume* Modulo4Logical = new G4LogicalVolume(modulo4_solid,matCH2_TS,"modulo4Logical");
	//~ new G4PVPlacement(0,pos4,Modulo4Logical,"Modulo4Physical",logicWorld,
																//~ false,0,fCheckOverlaps);
															
//~ //Modulo 3  - HDPE-B 5% 2.5 cm grosor 
	
	//~ G4double pos3_x = pos4_x + thickness_HDPE_B5_H/2.0 +thickness_HDPE/2.0; // distancia entre el centro del modulo 3
																			//~ // y el centro del detector 
	
	
	//~ G4ThreeVector pos3 = G4ThreeVector(pos3_x, 0, 0); //x,y,z 76.9895 = 13.02 + 60 + 2.125 + 1.25
	//~ G4Box* modulo3_solid = new G4Box("modulo3",1.25*cm ,5.84*cm,8.31*cm); //x,y,z
	//~ G4LogicalVolume* Modulo3Logical = new G4LogicalVolume(modulo3_solid,matBORON_CH2_TS,"modulo3Logical");
		//~ new G4PVPlacement(0,pos3,Modulo3Logical,"Modulo3Physical",logicWorld,
																//~ false,0,fCheckOverlaps);															
//~ //Modulo 2  - HDPE-B 5% 1.27 cm grosor 
	
	//~ G4double pos2_x = pos3_x + thickness_HDPE_B5_H/2.0 +  thickness_HDPE_B5_L/2.0; // distancia entre el centro del modulo 2
																				   //~ // y el centro del detector 
	
	//~ G4ThreeVector pos2 = G4ThreeVector(pos2_x, 0, 0); //x,y,z 78.78 = 13.52 + 60 + 2.125 + 1.25 + 1.25 + 0.635
	//~ G4Box* modulo2_solid = new G4Box("modulo2",0.635*cm ,5.68*cm,8.09*cm); //x,y,z
	//~ G4LogicalVolume* Modulo2Logical = new G4LogicalVolume(modulo2_solid,matBORON_CH2_TS,"modulo2Logical");
		//~ new G4PVPlacement(0,pos2,Modulo2Logical,"Modulo2Physical",logicWorld,
																//~ false,0,fCheckOverlaps);
																
//~ //Modulo 1 (Front-end) - Cadmio 1.1 mm grosor 
	
	//~ G4double pos1_x = pos2_x + thickness_HDPE_B5_L/2.0 +  thickness_cadmio/2.0; // distancia entre el centro del modulo 1 
																				//~ //y el centro del detector 
	//~ G4ThreeVector pos1 = G4ThreeVector(pos1_x, 0, 0); //x,y,z 79.58 = 13.52 + 60 + 2.125 + 1.25 + 1.25
																	//~ // + 0.635 + 0.635 + 0.055
	//~ G4Box* modulo1_solid = new G4Box("modulo1",0.055*cm ,5.68*cm,8.09*cm); //x,y,z
	//~ G4LogicalVolume* Modulo1Logical = new G4LogicalVolume(modulo1_solid,cadmium,"modulo1Logical");
		//~ new G4PVPlacement(0,pos1,Modulo1Logical,"Modulo1Physical",logicWorld,
																//~ false,0,fCheckOverlaps);														
																
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////



// // Tercer Material Moderador


													
	G4Box* HDPEBox_3 = new G4Box("HDPE_Box_3", box_x_3, box_y_3, box_z_3);
	G4LogicalVolume* HDPEBoxLogical_3 = new G4LogicalVolume(HDPEBox_3, SampleMaterialC3, "HDPEBox_Logical_3");


	new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), HDPEBoxLogical_3, "HDPEBox_Physical_3", logicWorld, false, 0, fCheckOverlaps);


	// // Segundo Material Moderador 





	G4Box* HDPEBox_2 = new G4Box("HDPE_Box_2", box_x_2, box_y_2, box_z_2);
	G4LogicalVolume* HDPEBoxLogical_2 = new G4LogicalVolume(HDPEBox_2, SampleMaterialC2, "HDPEBox_Logical_2");


	new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), HDPEBoxLogical_2, "HDPEBox_Physical_2", HDPEBoxLogical_3, false, 0, fCheckOverlaps);



	// // Primer Material Moderador (desde adentro hacia afuera)



	//Cambié matBOR_CH2_TS por SampleMaterial

	//Cambié box_x por fSampleThickness




	G4Box* HDPEBox = new G4Box("HDPE_Box", box_x, box_y, box_z);
	G4LogicalVolume* HDPEBoxLogical = new G4LogicalVolume(HDPEBox, SampleMaterialC1, "HDPEBox_Logical");


	new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), HDPEBoxLogical, "HDPEBox_Physical", HDPEBoxLogical_2, false, 0, fCheckOverlaps);




	// // Core (desde adentro hacia afuera)



	//Cambié matBOR_CH2_TS por SampleMaterial

	//Cambié box_x por fSampleThickness




	G4Box* HDPEBox_C = new G4Box("HDPE_Box_C", box_x_C, box_y_C, box_z_C);
	G4LogicalVolume* HDPEBoxLogical_C = new G4LogicalVolume(HDPEBox_C, SampleMaterialCore, "HDPEBox_Logical_C");


	new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), HDPEBoxLogical_C, "HDPEBox_Physical_C", HDPEBoxLogical, false, 0, fCheckOverlaps);



	///////////////////////////////
	//Cilindro de Cadmio 

	
	
	G4double startAngle_Cad =0.*deg;
	G4double spanningAngle_Cad =360.*deg;           

	//Forma del cilindro de Cadmio 

	G4Tubs* CIL_Cad = new G4Tubs("Cilindro_Cad",innerRaduis_Cad,outerRaduis_Cad,hz_Cad,startAngle_Cad,spanningAngle_Cad);  


	//Volumen Logico
	G4LogicalVolume* LogCil_Cad = new G4LogicalVolume(CIL_Cad,SampleMaterialCad,"Cilindro_Cad_Vol");  
	
	//Lugar 

	G4ThreeVector posCil_Cad = G4ThreeVector(0., 0.*cm, 0.*cm);           


	new G4PVPlacement(0,posCil_Cad,LogCil_Cad,"Cilindro_Cad_Phys",HDPEBoxLogical_C,false,0,fCheckOverlaps);  




	///////////////////////////////
	//Cilindro de Aluminio 

	
	
	G4double startAngle_Al =0.*deg;
	G4double spanningAngle_Al =360.*deg;           

	//Forma del cilindro de Aluminio 

	G4Tubs* CIL_Al = new G4Tubs("Cilindro_Al",innerRaduis_Al,outerRaduis_Al,hz_Al,startAngle_Al,spanningAngle_Al);  


	//Volumen Logico
	G4LogicalVolume* LogCil_Al = new G4LogicalVolume(CIL_Al,SampleMaterialAl,"Cilindro_Al_Vol");  
	//Lugar 

	G4ThreeVector posCil_Al = G4ThreeVector(0., 0.*cm, 0.*cm);           


	new G4PVPlacement(0,posCil_Al,LogCil_Al,"Cilindro_Al_Phys",HDPEBoxLogical_C,false,0,fCheckOverlaps);  




	G4double startAngle =0.*deg;
	G4double spanningAngle =360.*deg;





	//Forma del detector 

	G4Tubs* CIL_He = new G4Tubs("Cilindro_He",innerRaduis_Det,outerRaduis_Det,hz,startAngle,spanningAngle);

	//Volumen Logico

	G4LogicalVolume* DetectorLogical = new G4LogicalVolume(CIL_He,SampleDetMaterial,"DetectorLV");

	//Lugar 

	G4ThreeVector posCil = G4ThreeVector(0.*cm, 0.*cm, 0.*cm);           

	//esto lo voy a ocupar despues para poder guardar mis datos  
	// fAbsorberPV = 

	new G4PVPlacement(0,posCil,DetectorLogical,"Cilindro_He_Phys",HDPEBoxLogical_C,false,0,fCheckOverlaps);


           
	// Visualization attributes
	//
	G4VisAttributes* sampleAttributes = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.5));
	sampleAttributes->SetVisibility(true);
	sampleAttributes->SetForceWireframe(true);
	sampleAttributes->SetForceSolid(true);
	HDPEBoxLogical_3->SetVisAttributes(sampleAttributes);

	G4VisAttributes* CadmiumAttributes = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
	CadmiumAttributes->SetVisibility(true);
	CadmiumAttributes->SetForceWireframe(true);
	CadmiumAttributes->SetForceAuxEdgeVisible(true);
	CadmiumAttributes->SetForceSolid(true);
	LogCil_Cad->SetVisAttributes(CadmiumAttributes);
	
	G4VisAttributes* AluminiumAttributes = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));
	AluminiumAttributes->SetVisibility(true);
	AluminiumAttributes->SetForceWireframe(true);
	AluminiumAttributes->SetForceAuxEdgeVisible(true);
	AluminiumAttributes->SetForceSolid(true);
	LogCil_Al->SetVisAttributes(AluminiumAttributes);
	
	G4VisAttributes* DetectorAttributes = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
	DetectorAttributes->SetVisibility(true);
	DetectorAttributes->SetForceWireframe(true);
	DetectorAttributes->SetForceAuxEdgeVisible(true);
	DetectorAttributes->SetForceSolid(true);
	DetectorLogical->SetVisAttributes(DetectorAttributes);
 

	// Print materials
	G4cout << *(G4Material::GetMaterialTable()) << G4endl; 

	//always return the physical World
	//
	return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Alto del Detector (hz) 

void DetectorConstruction::SetSampleThickness(G4double d_mtl) {
	this->fSampleThickness=d_mtl*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Radio Del Detector

void DetectorConstruction::SetSamplediam(G4double diam) {
	this->fSampleRad=diam*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Radio De la lamina de Aluminio

void DetectorConstruction::SetSamplediamAl(G4double diamAl) {
	this->fSampleRadAl=diamAl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}



//Radio Del lamina de Cadmio

void DetectorConstruction::SetSamplediamCad(G4double diamCad) {
	this->fSampleRadCad=diamCad;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}


//Ancho en X de la Capa 1

void DetectorConstruction::SetSampleThicknessX(G4double d_mtlx) {
	this->fSampleThicknessX=d_mtlx;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Ancho en Y de la Capa 1

void DetectorConstruction::SetSampleThicknessY(G4double d_mtly) {
	this->fSampleThicknessY=d_mtly;
	G4RunManager::GetRunManager()->ReinitializeGeometry();

}

//Ancho en Z de la Capa 1

void DetectorConstruction::SetSampleThicknessZ(G4double d_mtlz) {
	this->fSampleThicknessZ=d_mtlz*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Ancho en X de la Capa 2

void DetectorConstruction::SetSampleThicknessX_2(G4double d_mtlx_2) {
		this->fSampleThicknessX_2=d_mtlx_2;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Ancho en Y de la Capa 2

void DetectorConstruction::SetSampleThicknessY_2(G4double d_mtly_2) {
	this->fSampleThicknessY_2=d_mtly_2;
	G4RunManager::GetRunManager()->ReinitializeGeometry();

}

//Ancho en Z de la Capa 2

void DetectorConstruction::SetSampleThicknessZ_2(G4double d_mtlz_2) {
	this->fSampleThicknessZ_2=d_mtlz_2*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}


	//Ancho en X de la Capa 3

void DetectorConstruction::SetSampleThicknessX_3(G4double d_mtlx_3) {
	this->fSampleThicknessX_3=d_mtlx_3;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Ancho en Y de la Capa 3

void DetectorConstruction::SetSampleThicknessY_3(G4double d_mtly_3) {
	this->fSampleThicknessY_3=d_mtly_3;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Ancho en Z de la Capa 3

void DetectorConstruction::SetSampleThicknessZ_3(G4double d_mtlz_3) {
	this->fSampleThicknessZ_3=d_mtlz_3*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}


//Ancho en X del Core

void DetectorConstruction::SetSampleThicknessX_Core(G4double d_mtlx_Core) {
	this->fSampleThicknessX_Core=d_mtlx_Core*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Ancho en Y del Core

void DetectorConstruction::SetSampleThicknessY_Core(G4double d_mtly_Core) {
	this->fSampleThicknessY_Core=d_mtly_Core*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Ancho en Z del Core

void DetectorConstruction::SetSampleThicknessZ_Core(G4double d_mtlz_Core) {
	this->fSampleThicknessZ_Core=d_mtlz_Core*.5;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}





// Material DE la Capa de Cadmio o Aire
void DetectorConstruction::SetSampleMaterialCad(G4String materialChoice) {
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) SampleMaterialCad = pttoMaterial;
	G4cout 
		<< G4endl 
		<< "----> The target is made of " << materialChoice << G4endl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

// Material DE la Capa de Aluminio
void DetectorConstruction::SetSampleMaterialAl(G4String materialChoice) {
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) SampleMaterialAl = pttoMaterial;
	G4cout 
		<< G4endl 
		<< "----> The target is made of " << materialChoice << G4endl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}


	

// Material DE la Primera Capa
void DetectorConstruction::SetSampleMaterialC1(G4String materialChoice) {
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) SampleMaterialC1 = pttoMaterial;
	G4cout 
		<< G4endl 
		<< "----> The target is made of " << materialChoice << G4endl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//Material de la Segunda Capa
void DetectorConstruction::SetSampleMaterialC2(G4String materialChoice) {
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) SampleMaterialC2 = pttoMaterial;
	G4cout 
		<< G4endl 
		<< "----> The target is made of " << materialChoice << G4endl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}


//Material de la Tercera Capa
void DetectorConstruction::SetSampleMaterialC3(G4String materialChoice) {
G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) SampleMaterialC3 = pttoMaterial;
	G4cout 
		<< G4endl 
		<< "----> The target is made of " << materialChoice << G4endl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

   //Material del Core
void DetectorConstruction::SetSampleMaterialCore(G4String materialChoice) {
G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) SampleMaterialCore = pttoMaterial;
	G4cout 
		<< G4endl 
		<< "----> The target is made of " << materialChoice << G4endl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}



//Material Del Detector

void DetectorConstruction::SetSampleDetMaterial(G4String materialChoice) {
G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) SampleDetMaterial = pttoMaterial;
 G4cout 
	  << G4endl 
	  << "----> The target is made of " << materialChoice << G4endl;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}
	
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDefaults() {

	//Resets to default values
	fSampleThickness=20.*cm;
	fSampleThicknessX=20.*cm;
	fSampleThicknessY=20.*cm;
	fSampleThicknessZ=20.*cm;
	fSampleThicknessX_2=20.*cm;
	fSampleThicknessY_2=20.*cm;
	fSampleThicknessZ_2=20.*cm;
	fSampleThicknessX_3=20.*cm;
	fSampleThicknessY_3=20.*cm;
	fSampleThicknessZ_3=20.*cm;
	fSampleThicknessX_Core=20.*cm; 
	fSampleThicknessY_Core=20.*cm; 
	fSampleThicknessZ_Core=20.*cm;
	fSampleRad = 63.8*mm;
	fSampleRadCad = 1.1*mm;
	SetSampleMaterialC3("Air");
	fSampleRadAl =  1.*mm;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
	G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
	
	// declare the MultiFunctionalDetector scorer //
	
	G4MultiFunctionalDetector* He3C = new G4MultiFunctionalDetector("Detector_charg");
	G4MultiFunctionalDetector* He3P = new G4MultiFunctionalDetector("Detector_proto");
	G4MultiFunctionalDetector* He3T = new G4MultiFunctionalDetector("Detector_trito");
	G4MultiFunctionalDetector* He3A = new G4MultiFunctionalDetector("Detector_alpha");
	G4MultiFunctionalDetector* He3g = new G4MultiFunctionalDetector("Detector_gamma");
	G4MultiFunctionalDetector* He3e = new G4MultiFunctionalDetector("Detector_elect");
	G4MultiFunctionalDetector* He3H = new G4MultiFunctionalDetector("Detector_heli3");
	G4MultiFunctionalDetector* He3D = new G4MultiFunctionalDetector("Detector_deute");
	
	// add the detectors //
	
	G4SDManager::GetSDMpointer()->AddNewDetector(He3C);
	G4SDManager::GetSDMpointer()->AddNewDetector(He3P);
	G4SDManager::GetSDMpointer()->AddNewDetector(He3T);
	G4SDManager::GetSDMpointer()->AddNewDetector(He3A);
	G4SDManager::GetSDMpointer()->AddNewDetector(He3g);
	G4SDManager::GetSDMpointer()->AddNewDetector(He3e);
	G4SDManager::GetSDMpointer()->AddNewDetector(He3H);
	G4SDManager::GetSDMpointer()->AddNewDetector(He3D);
	
	// set the type of detector //
	
	G4VPrimitiveScorer* primitiv0 = new G4PSEnergyDeposit("edep_c");
	G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep_p");
	G4VPrimitiveScorer* primitiv2 = new G4PSEnergyDeposit("edep_t");
	G4VPrimitiveScorer* primitiv3 = new G4PSEnergyDeposit("edep_a");
	G4VPrimitiveScorer* primitiv4 = new G4PSEnergyDeposit("edep_g");
	G4VPrimitiveScorer* primitiv5 = new G4PSEnergyDeposit("edep_e");
	G4VPrimitiveScorer* primitiv6 = new G4PSEnergyDeposit("edep_h");
	G4VPrimitiveScorer* primitiv7 = new G4PSEnergyDeposit("edep_d");
	
	// Create Filters //

	//~ primitiv1 = new G4PSTrackLength("TrackLength");
	auto charge = new G4SDChargedFilter("ChargeFilter");
	auto proto = new G4SDParticleFilter("ProtonFilter",		"proton");
	auto trito = new G4SDParticleFilter("TritioFilter",		"triton");
	auto alpha = new G4SDParticleFilter("AlphaFilter",		"alpha");
	auto gammF = new G4SDParticleFilter("gammaFilter",		"gamma");
	auto elect = new G4SDParticleFilter("electronFilter",	"e-");
	auto heli3 = new G4SDParticleFilter("Helio3Filter",		"He3");
	auto deute = new G4SDParticleFilter("Deuteron3Filter",	"deuteron");
	
	// Set Filters //
	
	primitiv0->SetFilter(charge);
	primitiv1->SetFilter(proto);
	primitiv2->SetFilter(trito);
	primitiv3->SetFilter(alpha);
	primitiv4->SetFilter(gammF);
	primitiv5->SetFilter(elect);
	primitiv6->SetFilter(heli3);
	primitiv7->SetFilter(deute);
	
	// Register Scorer //
	
	He3C->RegisterPrimitive(primitiv0);
	He3P->RegisterPrimitive(primitiv1);
	He3T->RegisterPrimitive(primitiv2);
	He3A->RegisterPrimitive(primitiv3);
	He3g->RegisterPrimitive(primitiv4);
	He3e->RegisterPrimitive(primitiv5);
	He3H->RegisterPrimitive(primitiv6);
	He3D->RegisterPrimitive(primitiv7);
	SetSensitiveDetector("DetectorLV",He3C);
	SetSensitiveDetector("DetectorLV",He3P);
	SetSensitiveDetector("DetectorLV",He3T);
	SetSensitiveDetector("DetectorLV",He3A);
	SetSensitiveDetector("DetectorLV",He3g);
	SetSensitiveDetector("DetectorLV",He3e);
	SetSensitiveDetector("DetectorLV",He3H);
	SetSensitiveDetector("DetectorLV",He3D);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
