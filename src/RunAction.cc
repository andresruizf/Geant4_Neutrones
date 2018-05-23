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
// $Id: B3aRunAction.cc 99559 2016-09-27 07:02:21Z gcosmo $
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

// User's Classes //

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Analysis.hh"

// G4's Classes //

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

// C++ Clasess //

//~ #include <iostream>
//~ #include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction(),
   fSumEnerDep(0.),  
   fSumEnerPrt(0.),  
   fSumEnerTrt(0.),
   TotalnofEvent(0)
{  
    
	//add new units for dose
	// 
	const G4double milligray = 1.e-3*gray;
	const G4double microgray = 1.e-6*gray;
	const G4double nanogray  = 1.e-9*gray;  
	const G4double picogray  = 1.e-12*gray;

	new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
	new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
	new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
	new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

	// Register accumulable to the accumulable manager
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->RegisterAccumulable(fSumEnerDep); 
	accumulableManager->RegisterAccumulable(fSumEnerPrt); 
	accumulableManager->RegisterAccumulable(fSumEnerTrt); 
	
	
	//~ G4String fileName = "shield";
	//~ G4int ENBins = 1000;
	//~ std::vector<G4double> EnXSecs(ENBins+1); //= new G4double [ENBins+1];
	//~ G4double dumEnfullLast = 2.E7;
	//~ G4double dumEnfullFirst = 1.E-5;
	//~ for (G4int i=0; i < ENBins + 1; i++){ 
	//~ EnXSecs[i]= exp (i*(log (dumEnfullLast/dumEnfullFirst))/ENBins +
	//~ log( dumEnfullFirst) );
	//~ }

	// Analysis Manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << " analysis manager" << G4endl;
	analysisManager->SetVerboseLevel(0);
	analysisManager->SetFirstHistoId(1);



	G4cout << "---------------------Preparando Trees...------------------------" << G4endl;

	std::ifstream ficheroEntrada;
	G4String parametros;
	G4String titulo;

	G4cout << "---------------------Leyendo Archivo...------------------------" << G4endl;

	
	ficheroEntrada.open ("dummy.txt");
	std::getline(ficheroEntrada, parametros);

	G4cout << "	::::::	" << parametros << "	::::::	" << G4endl; 

	G4cout << "---------------------Archivo Leido------------------------" << G4endl;


	
	// Creating ntuple

	/// Tree que guarda la energía depositada en el detector ///
	titulo = "Energia por evt	::	" + parametros;
	
	// Create 1st ntuple (id = 0)
	analysisManager->CreateNtuple("Energia", titulo);
	analysisManager->CreateNtupleIColumn("Event_ID");	// column Id = 0 
	analysisManager->CreateNtupleDColumn("Edep_Charge");	// column Id = 1
	analysisManager->CreateNtupleDColumn("Edep_Proton");	// column Id = 2
	analysisManager->CreateNtupleDColumn("Edep_Trito");		// column Id = 3
	analysisManager->CreateNtupleDColumn("Edep_Alpha");		// column Id = 4
	analysisManager->CreateNtupleDColumn("Edep_Gamma");		// column Id = 5
	analysisManager->CreateNtupleDColumn("Edep_Electron");	// column Id = 6
	analysisManager->CreateNtupleDColumn("Edep_Helio3");	// column Id = 7
	analysisManager->CreateNtupleDColumn("Edep_Deuterio");	// column Id = 8
	analysisManager->FinishNtuple();


	/// Tree que guarda los neutrones detectados en el detector ///
	titulo = "Detectados	::	" + parametros;
	
	// Create 2nd ntuple (id = 1)
	analysisManager->CreateNtuple("Detectados", titulo);
	analysisManager->CreateNtupleIColumn("Event_ID");		// column Id = 0
	analysisManager->CreateNtupleDColumn("Neutron_Energy");		// column Id = 1
	//~ analysisManager->CreateNtupleSColumn("Particle");		// column Id = 2
	//~ analysisManager->CreateNtupleSColumn("Born_Volume");	// column Id = 3
	//~ analysisManager->CreateNtupleSColumn("Process_Type");	// column Id = 4
	//~ analysisManager->CreateNtupleDColumn("Energy_Deposit");	// column Id = 5
	//~ analysisManager->CreateNtupleIColumn("Track_ID");		// column Id = 6
	//~ analysisManager->CreateNtupleIColumn("Parent_ID");		// column Id = 7
	analysisManager->FinishNtuple();


	/// Tree para guardar todas las particulas que se crean en la simulacion ///
	//~ titulo = "Particulas	::	" + parametros;
	
	// Create 3th ntuple (id = 2)
	//~ analysisManager->CreateNtuple("Particulas", titulo);
	//~ analysisManager->CreateNtupleIColumn("Event_ID");		// column Id = 0
	//~ analysisManager->CreateNtupleSColumn("Particle");		// column Id = 1
	//~ analysisManager->CreateNtupleSColumn("Process_Type");	// column Id = 2
	//~ analysisManager->CreateNtupleSColumn("Born_Volume");	// column Id = 3
	//~ analysisManager->CreateNtupleDColumn("Energy_MeV");		// column Id = 4
	//~ analysisManager->CreateNtupleDColumn("Kinect_MeV");		// column Id = 5
	//~ analysisManager->CreateNtupleDColumn("Total_MeV");		// column Id = 6
	//~ analysisManager->CreateNtupleIColumn("Track_ID");		// column Id = 7
	//~ analysisManager->CreateNtupleIColumn("Parent_ID");		// column Id = 8
	//~ analysisManager->FinishNtuple();

	G4cout << "---------------------Trees Creados------------------------" << G4endl;
	ficheroEntrada.close();

	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{ 
	delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{ 
	G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

	// reset accumulables to their initial values
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Reset();

	//inform the runManager to save random number seed
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);

	//inform the runManager to save random number seed
	G4RunManager::GetRunManager()->SetRandomNumberStore(true);
	
	G4int nofEvents = run->GetNumberOfEventToBeProcessed();
	SetTolNumEvt(nofEvents);

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->OpenFile("data.root");		// Nombre de los Archivos //
	G4cout << "FILE OPENED" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;
	
	
	// Merge accumulables 
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Merge();

	// Run conditions
	//  note: There is no primary generator action object for "master"
	//        run manager for multi-threaded mode.
	const PrimaryGeneratorAction* generatorAction
	= static_cast<const PrimaryGeneratorAction*>(
		G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
	G4String partName;
	if (generatorAction) 
	{
	G4ParticleDefinition* particle 
		= generatorAction->GetParticleGun()->GetParticleDefinition();
	partName = particle->GetParticleName();
	} 
	
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
          
  // Print results
  //
	if (IsMaster())
	{
		G4cout
			<< G4endl
			<< "--------------------End of Global Run-----------------------"
			<< G4endl;
	}
	else
	{
		G4cout
			<< G4endl
			<< "--------------------End of Local Run------------------------"
			<< G4endl
			<< "	The run was " << nofEvents << " "<< partName << G4endl;
	}      
		G4cout
			<< " Total energy by charged particle in detector : " << G4BestUnit(fSumEnerDep.GetValue(),"Energy") 
			<< G4endl 
			<< " Total energy by proton in detector : " << G4BestUnit(fSumEnerPrt.GetValue(),"Energy") 
			<< G4endl 
			<< " Total energy by Triton in detector : " << G4BestUnit(fSumEnerTrt.GetValue(),"Energy") 
			<< G4endl 
			<< "------------------------------------------------------------" << G4endl 
			<< G4endl;
			
	analysisManager->Write();
	G4cout << "WRITING FILE" << G4endl;
	analysisManager->CloseFile();
	G4cout << "FILE CLOSED" << G4endl;
	
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
