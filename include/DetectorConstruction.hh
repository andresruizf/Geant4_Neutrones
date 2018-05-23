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
// $Id: B3DetectorConstruction.hh 71079 2013-06-10 20:37:11Z ihrivnac $
//
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"
#include "globals.hh"

#include <vector>

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4VisAttributes;
class G4GenericMessenger;
class DetectorMessenger;

/// Detector construction class to define materials and geometry.
///
/// Crystals are positioned in Ring, with an appropriate rotation matrix. 
/// Several copies of Ring are placed in the full detector.

class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();
		virtual ~DetectorConstruction();
		virtual G4VPhysicalVolume* Construct();
		virtual void ConstructSDandField();
		//are created
		void SetSampleThickness(G4double );
		void SetSampleThicknessX(G4double ); //Función que cambia el ancho del Moderador 1 en X
		void SetSampleThicknessY(G4double ); //Función que cambia el ancho del Moderador 1 en Y
		void SetSampleThicknessZ(G4double ); //Función que cambia el ancho del Moderador 1 en Z
		void SetSampleThicknessX_2(G4double ); //Función que cambia el ancho del Moderador 2 en X
		void SetSampleThicknessY_2(G4double ); //Función que cambia el ancho del Moderador 2 en Y
		void SetSampleThicknessZ_2(G4double ); //Función que cambia el ancho del Moderador 2 en Z
		void SetSampleThicknessX_3(G4double ); //Función que cambia el ancho del Moderador 3 en X
		void SetSampleThicknessY_3(G4double ); //Función que cambia el ancho del Moderador 3 en Y
		void SetSampleThicknessZ_3(G4double ); //Función que cambia el ancho del Moderador 3 en Z
		void SetSampleThicknessX_Core(G4double ); //Función que cambia el ancho del Core en X
		void SetSampleThicknessY_Core(G4double ); //Función que cambia el ancho del Core en Y
		void SetSampleThicknessZ_Core(G4double ); //Función que cambia el ancho del Core en Z
		void SetSamplediam(G4double );
		void SetSamplediamCad(G4double ); // Funcion que cambia el radio de la lámina de cadmio
		void SetSamplediamAl(G4double ); // Funcion que cambia el radio de la lámina de Aluminio
		void SetSampleMaterialC1(G4String ); //Función que cambia el material moderador de la Primera Capa
		void SetSampleMaterialCad(G4String ); //Función que cambia el material la Capa de Cadmio
		void SetSampleMaterialAl(G4String ); //Función que cambia el material la Capa de Cadmio
		void SetSampleMaterialC2(G4String ); //Función que cambia el material moderador de la Segunda Capa
		void SetSampleMaterialC3(G4String ); //Función que cambia el material moderador de la Tercera Capa
		void SetSampleMaterialCore(G4String ); //Función que cambia el material moderador del Core
		void SetSampleDetMaterial(G4String ); //Funcion que cambia el material del detector
		void SetDefaults();
		G4Material* GetSampleMaterial() const {return SampleMaterialC1;};
		//~ G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
		G4double GetSampleThickness() const {return fSampleThickness;}; 			   
	private:
		void DefineMaterials();
		G4bool  fCheckOverlaps;
		G4Material* SampleDetMaterial; //Inicializa el material para el Detector
		G4Material* SampleMaterialCad;    // Inicializa el material Moderador de la Capa de Cadmio
		G4Material* SampleMaterialC1;    // Inicializa el material Moderador de la Primera Capa
		G4Material* SampleMaterialC2;    // Inicializa el material Moderador de la Segunda Capa
		G4Material* SampleMaterialC3;    // Inicializa el material Moderador de la Tercera Capa
		G4Material* SampleMaterialCore;    // Inicializa el material Moderador del Core
		G4Material* SampleMaterialAl;    // Inicializa el material Moderador del Core
		G4LogicalVolume*   fpWorldLogical;
		G4VPhysicalVolume* fpWorldPhysical;
		std::vector<G4VisAttributes*> fVisAttributes;
		G4double fSampleThickness;
		G4double fSampleThicknessX;//Cambia la geometria del moderador 1 en X
		G4double fSampleThicknessY;//Cambia la geometria del moderador 1 en Y
		G4double fSampleThicknessZ;//Cambia la geometria del moderador 1 en Z
		G4double fSampleThicknessX_2;//Cambia la geometria del moderador 2  en X
		G4double fSampleThicknessY_2;//Cambia la geometria del moderador  2 en Y
		G4double fSampleThicknessZ_2;//Cambia la geometria del moderador  2 en Z
		G4double fSampleThicknessX_3;//Cambia la geometria del moderador 3  en X
		G4double fSampleThicknessY_3;//Cambia la geometria del moderador  3 en Y
		G4double fSampleThicknessZ_3;//Cambia la geometria del moderador  3 en Z
		G4double fSampleThicknessX_Core;//Cambia la geometria del Core  en X
		G4double fSampleThicknessY_Core;//Cambia la geometria del Core en Y
		G4double fSampleThicknessZ_Core;//Cambia la geometria del Core en Z
		G4double fSampleRad;
		G4double fSampleRadCad; //cambia el diametro de la lamina de Cadmio
		G4double fSampleRadAl; //cambia el diametro de la lamina de Aluminio
		G4String pptoMaterial;
		DetectorMessenger* detectorMessenger;  //pointer to the Messenger
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

