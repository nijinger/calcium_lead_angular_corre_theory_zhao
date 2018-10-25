G4double GetCarbon12Range(G4double energy) //MeV
{
  if(energy<=0.) return 0.;
  return 4.94609+0.230177*energy+0.0133917*energy*energy-0.00000761914*energy*energy*energy;
}

G4double GetCarbon12Energy(G4double range)
{
  
}
G4double GetCrbonEnergyLoss(G4double energy, G4double dr,G4double thick)
{
  
}
