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
// $Id: B3aRunAction.hh 99559 2016-09-27 07:02:21Z gcosmo $
//
/// \file RunAction.hh
/// \brief Definition of the RunAction class

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

/// Run action class

class RunAction : public G4UserRunAction
{
	public:
		RunAction();
		virtual ~RunAction();

		virtual void BeginOfRunAction(const G4Run*);
		virtual void   EndOfRunAction(const G4Run*);

		void SumEnerDep(G4double edep) { fSumEnerDep += edep; };
		void SumEnerPrt(G4double edep) { fSumEnerPrt += edep; };
		void SumEnerTrt(G4double edep) { fSumEnerTrt += edep; };
		
		void SetTolNumEvt(G4int TnEvt) { TotalnofEvent = TnEvt; };
		G4int GetTolNumEvt() {return TotalnofEvent; };
		

	private:
		G4Accumulable<G4double> fSumEnerDep, fSumEnerPrt, fSumEnerTrt;  
		G4int TotalnofEvent;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

