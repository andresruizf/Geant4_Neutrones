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
// $Id$
//
/// \file  EventAction.cc
/// \brief Implementation of the  EventAction class

// User's Classes //

#include "EventAction.hh"
#include "RunAction.hh"
#include "Analysis.hh"

// G4's Clasess //

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 EventAction:: EventAction(RunAction* runAction)
 : G4UserEventAction(),
   fRunAction(runAction),
   nofEvent(0),
   TolnofEvent(0),
   fCollID_He3C(-1),
   fCollID_He3P(-1),
   fCollID_He3T(-1),
   fCollID_He3A(-1),
   fCollID_He3g(-1),
   fCollID_He3e(-1),
   fCollID_He3H(-1),
   fCollID_He3D(-1)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 EventAction::~ EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void  EventAction::BeginOfEventAction(const G4Event* evt)
{
	nofEvent = evt->GetEventID();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void  EventAction::EndOfEventAction(const G4Event* evt )
{
	//Hits collections
	//  
	G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
	if(!HCE) return;
	
	if (TolnofEvent == 0){
		TolnofEvent = fRunAction->GetTolNumEvt();
	}
	
	
	//Analysis Manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
			   
	// Get hits collections IDs
	if (fCollID_He3C < 0) {
		G4SDManager* SDMan = G4SDManager::GetSDMpointer();  
		fCollID_He3C = SDMan->GetCollectionID("Detector_charg/edep_c");
		fCollID_He3P = SDMan->GetCollectionID("Detector_proto/edep_p");
		fCollID_He3T = SDMan->GetCollectionID("Detector_trito/edep_t");
		fCollID_He3A = SDMan->GetCollectionID("Detector_alpha/edep_a");
		fCollID_He3g = SDMan->GetCollectionID("Detector_gamma/edep_g");
		fCollID_He3e = SDMan->GetCollectionID("Detector_elect/edep_e");
		fCollID_He3H = SDMan->GetCollectionID("Detector_heli3/edep_h");
		fCollID_He3D = SDMan->GetCollectionID("Detector_deute/edep_d");
	}
	
	nofEvent = evt->GetEventID();

	G4THitsMap<G4double>* evtMapCharge = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3C));
	G4THitsMap<G4double>* evtMapProto  = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3P));
	G4THitsMap<G4double>* evtMapTrito  = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3T));
	G4THitsMap<G4double>* evtMapAlpha  = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3A));
	G4THitsMap<G4double>* evtMapgamma  = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3g));
	G4THitsMap<G4double>* evtMapelect  = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3e));
	G4THitsMap<G4double>* evtMapHeli3  = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3H));
	G4THitsMap<G4double>* evtMapDeute  = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_He3D));
	
	std::map<G4int,G4double*>::iterator itr = evtMapCharge->GetMap()->begin();
	G4double edep_charge = 0;
	for (; itr != evtMapCharge->GetMap()->end(); itr++) {
		G4double edep = *(itr->second);
		edep_charge = *(itr->second);		// parece que es redundante //
		fRunAction->SumEnerDep(edep);
	}
	
	itr = evtMapProto->GetMap()->begin();
	G4double edep_proto = 0;
	for (; itr != evtMapProto->GetMap()->end(); itr++) {
		G4double edep = *(itr->second);
		edep_proto = *(itr->second);
		fRunAction->SumEnerPrt(edep);
	}
	
	G4double edep_trito = 0;
	itr = evtMapTrito->GetMap()->begin();
	for (; itr != evtMapTrito->GetMap()->end(); itr++) {
		G4double edep = *(itr->second);
		edep_trito = *(itr->second);
		fRunAction->SumEnerTrt(edep);
	}
	
	G4double edep_alpha = 0;
	itr = evtMapAlpha->GetMap()->begin();
	for (; itr != evtMapAlpha->GetMap()->end(); itr++) {
		edep_alpha = *(itr->second);
	}
	
	G4double edep_gamma = 0;
	itr = evtMapgamma->GetMap()->begin();
	for (; itr != evtMapgamma->GetMap()->end(); itr++) {
		edep_gamma = *(itr->second);
	}
	
	G4double edep_elect = 0;
	itr = evtMapelect->GetMap()->begin();
	for (; itr != evtMapelect->GetMap()->end(); itr++) {
		edep_elect = *(itr->second);
	}
	
	G4double edep_heli3 = 0;
	itr = evtMapHeli3->GetMap()->begin();
	for (; itr != evtMapHeli3->GetMap()->end(); itr++) {
		edep_heli3 = *(itr->second);
	}
			   
	G4double edep_deute = 0;
	itr = evtMapDeute->GetMap()->begin();
	for (; itr != evtMapDeute->GetMap()->end(); itr++) {
		edep_deute = *(itr->second);
	}


	/// muestra el porcentaje en pantalla ///		  
	//~ if (nofEvent%100000 == 0){
		//~ std::cout << int(double(nofEvent)/double(TolnofEvent)*100) << "%" << "\r" << std::flush;
	//~ }


	edep_charge = edep_charge/keV;
	edep_proto = edep_proto/keV;
	edep_trito = edep_trito/keV;
	edep_alpha = edep_alpha/keV;
	edep_gamma = edep_gamma/keV;
	edep_elect = edep_elect/keV;
	edep_heli3 = edep_heli3/keV;
	edep_deute = edep_deute/keV;
	// fill ntuple
	//
	analysisManager->FillNtupleIColumn(0, 0, nofEvent);
	analysisManager->FillNtupleDColumn(0, 1, edep_charge);
	analysisManager->FillNtupleDColumn(0, 2, edep_proto);
	analysisManager->FillNtupleDColumn(0, 3, edep_trito);
	analysisManager->FillNtupleDColumn(0, 4, edep_alpha);
	analysisManager->FillNtupleDColumn(0, 5, edep_gamma);
	analysisManager->FillNtupleDColumn(0, 6, edep_elect);
	analysisManager->FillNtupleDColumn(0, 7, edep_heli3);
	analysisManager->FillNtupleDColumn(0, 8, edep_deute);
	analysisManager->AddNtupleRow(0);  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
