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
//
// $Id: SteppingAction.cc,v 1.1 2010-11-12 19:16:31 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// User's Classes //

#include "Analysis.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

//#include "DirManagement.hh"

// G4's Classes //

#include "G4ParticleDefinition.hh" 
#include "G4Event.hh" 
#include "G4Neutron.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0),
  NeutronEnergy(0),
  Aux(0),
  Evt(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{		
	///////////////////////////////////////////////////////////////////////////////////
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	G4Track* track = step->GetTrack();
	const G4String VolName = track->GetTouchable()->GetVolume(0)->GetName();
	//~ G4double Edep = step->GetTotalEnergyDeposit();
	G4String PartName = track->GetDefinition()->GetParticleName();
	G4int TrckID = track->GetTrackID();
	G4int nofEvent = fEventAction->GetNofEvent();
	if (TrckID == 1){
		NeutronEnergy = track->GetVertexKineticEnergy();
		
	}


	//~ if (PartName == "neutron" || PartName == "proton" || PartName == "triton"){
	//~ if (TrckID != Aux || VolName == "DetectorPhysical"){
	if (TrckID != Aux || Evt != nofEvent){
		Aux = TrckID;
		Evt = nofEvent;

		/// Se debe descomentar lo siguiente para que el Tree id=2 funcione correctamente ///
		
		//~ G4int PrntID = track->GetParentID();
		//~ G4double VertexEnergy = track->GetVertexKineticEnergy();
		//~ G4double KinectEnergy = step->GetPreStepPoint()->GetKineticEnergy();
		//~ G4double TotalEnergy = track->GetTotalEnergy();
		const G4String OriVolName = track->GetOriginTouchable()->GetVolume()->GetName();
		//~ G4cout << PartName << G4endl;
		//~ G4String Process;
		//~ if (TrckID != 1){
			//~ Process = track->GetCreatorProcess()->GetProcessName();
		//~ }
		//~ else {Process = "Gun/Beam";}	// GetCreatorProcess lanza un seg fault si la particula sale del beam/gun

		if ((PartName == "triton" || PartName == "Li7") && OriVolName == "Cilindro_He_Phys"){		/// neutrones detectados en detector de He3 o BF3

			analysisManager->FillNtupleIColumn(1, 0, nofEvent);
			analysisManager->FillNtupleDColumn(1, 1, NeutronEnergy);
			analysisManager->AddNtupleRow(1);
		}
		
		/// Tree para ver las particulas generadas en la simulacion ///

		//~ analysisManager->FillNtupleIColumn(2, 0, nofEvent);
		//~ analysisManager->FillNtupleSColumn(2, 1, PartName);
		//~ analysisManager->FillNtupleSColumn(2, 2, Process);
		//~ analysisManager->FillNtupleSColumn(2, 3, OriVolName);
		//~ analysisManager->FillNtupleDColumn(2, 4, VertexEnergy);
		//~ analysisManager->FillNtupleDColumn(2, 5, KinectEnergy);
		//~ analysisManager->FillNtupleDColumn(2, 6, TotalEnergy);
		//~ analysisManager->FillNtupleIColumn(2, 7, TrckID);
		//~ analysisManager->FillNtupleIColumn(2, 8, PrntID);
		//~ analysisManager->FillNtupleIColumn(2, 9, detect);
		//~ analysisManager->AddNtupleRow(2);
		//~ detect = 0;
	}

}
