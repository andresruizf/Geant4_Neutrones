#ifndef PHYSICSLISTNEUTRON_HH
#define PHYSICSLISTNEUTRON_HH 1
 
#include "G4VPhysicsConstructor.hh"

class PhysicsListNeutrons : public G4VPhysicsConstructor {

public:
PhysicsListNeutrons(const G4String& name="neutron");
  virtual ~PhysicsListNeutrons();
 
 
   void ConstructParticle() { };
    void ConstructProcess();
 
 };
 
#endif
