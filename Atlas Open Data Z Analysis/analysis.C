#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void analysis::Loop()
{
    TFile * outputFile = new TFile ("ATLASOD.root", "RECREATE");
    //I wrote the my outputfile name, firstly
    TH1F * h_par_type = new TH1F ("h_par_type", "Particle Type", 10, 15, 15);
    h_par_type->GetXaxis()->SetTitle("particle PID");
    h_par_type->GetYaxis()->SetTitle("particle count");
    //this time I made that code because I want to select which I eliminated particle
    
    TH1F *h_passgrl = new TH1F("h_passgrl", "number of grl events", 5, 0, 5);
    h_passgrl->GetXaxis()->SetTitle("status of events grl");
    h_passgrl->GetYaxis()->SetTitle("event count");
    //I am gonna explain this step!!!!
    
    //TH1F * h_goodvertex = new TH1F("number of good vertex events", 2, 0, 2);
        
   // h_goodvertex->GetXaxis()->SetTitle("good vertex statuss");
                                      //0 is false and 1 is true lik
    //h_goodvertex->GetYaxis()->SetTitle("event count");
    
    TH1F * h_multiplicity = new TH1F("h_multiplicity", "electron multiplicity",10, 0, 10);
    h_multiplicity->GetXaxis()->SetTitle("electron count");
    h_multiplicity->GetYaxis()->SetTitle("event count");
    
    TH1F * h_electroncharge = new TH1F("h_electroncharge", "charge distribution for electrons", 100, -3, 3);
    h_electroncharge->GetXaxis()->SetTitle("charge of particle");
    h_electroncharge->GetYaxis()->SetTitle("particle count");
    //this step means define the charge of particle
    
    TH1F * h_electronpt = new TH1F("h_electronpt", "p_{t} dist. of electrons", 200, 0, 200);
    h_electronpt->GetXaxis()->SetTitle("particle p_{t}");
    h_electroncharge->GetYaxis()->SetTitle("particle count");
    //I wrote a code for particles's PT values
    
    TH1F * h_electrone = new TH1F("h_electrone", "energy dist. of electrons",200, 0, 500);
    h_electrone->GetXaxis()->SetTitle("particle energy");
    h_electrone->GetYaxis()->SetTitle("particle count");
    //I wrote a code for particles's energy values
    
    TH1F * h_electroneta = new TH1F("h_electroneta", "eta dist. of electrons", 24, -4, 4);
    h_electroneta->GetXaxis()->SetTitle("particle eta");
    h_electroneta->GetYaxis()->SetTitle("particle count");
    
    TH1F * h_electronphi = new TH1F("h_electronphi", "phi dist. of electrons", 24, -4, 4);
    h_electronphi->GetXaxis()->SetTitle("electron phi");
    h_electronphi->GetYaxis()->SetTitle("particle count");
    //That is the end of the electrons definition components!
    
    TH1F * h_positronpt = new TH1F("h_positronpt","p_{t} dist.of positron", 200, 0, 200);
    h_positronpt->GetXaxis()->SetTitle("particle p_{t}");
    h_positronpt->GetYaxis()->SetTitle("particle count");
    //now I made for positron's PT
    
    TH1F * h_positrone = new TH1F("h_positrone", "energy dist. of positron", 200, 0, 500);
    h_positrone->GetXaxis()->SetTitle("particle energy");
    h_positrone->GetYaxis()->SetTitle("particle count");
    //energy of positron
    
    TH1F * h_positroneta = new TH1F("h_positroneta", "eta dist. of positrons", 24, -4, 4);
    h_positroneta->GetXaxis()->SetTitle("particle eta");
    h_positroneta->GetYaxis()->SetTitle("particle count");
    //now I wrote the fucking eta of positron!!
    
    TH1F * h_positronphi = new TH1F("h_positronphi", "phi dist.of positrons", 24, -4, 4);
    h_positronphi->GetXaxis()->SetTitle("particle phi");
    h_positronphi->GetYaxis()->SetTitle("particle count");
    //phi for positron!!!!!! och
    
    TH1F * hZtoeeMassM = new TH1F("hZtoeeMassM", "Recons. mass od Z", 100, 0, 200);
    hZtoeeMassM->GetXaxis()->SetTitle("m_Z^e.....GeV");
    hZtoeeMassM->GetYaxis()->SetTitle("event count");
    //I didnt understand ask Aytül teacher!
    TH1F * hZtoeeMassE = new TH1F("hZtoeeMassE", "Recons. mass od Z", 100, 0, 200);
    hZtoeeMassM->GetXaxis()->SetTitle("m_Z^e.....GeV");
    hZtoeeMassM->GetYaxis()->SetTitle("event count");
    //I didnt understand ask Aytül teacher!
    
    TH1F * hCutEfficiency = new TH1F("hCutEfficiency", "Cut Efficiency", 5, 0, 5);
    TH1F * h_eventnumber = new TH1F("h_eventnumber", "Number of events", 3, 0, 3);
    
    //Finally I finished this shit
    
    //I am going to define a lorentz vector
    TLorentzVector zLep1, zLep2;
    int eventnumber = 0;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        eventnumber++;
        h_eventnumber->Fill(1);
        if (jentry % 100000 == 0) {
            cout << "Left:" << nentries - jentry << endl;
            }
        h_passgrl->Fill(passGRL);
       // h_goodvertex->Fill(hasGoodVertex);
        int CountM = 0;
        for (int i=0; i < lep_n; i++) {
            h_par_type->Fill(lep_type[i]);
            if (lep_type[i] == 11) {
                CountM++;
                h_electroncharge->Fill(lep_charge[i]);
                hCutEfficiency->Fill(0);
                if (lep_pt[i] > 25000) {
                    hCutEfficiency->Fill(1);
                    
                    if (abs(lep_eta[i]) < 2.0) {
                        hCutEfficiency->Fill(2);
                        if(lep_charge[i] < 0) {
                            h_electronpt->Fill(lep_pt[i] / 1000);
                            h_electrone->Fill(lep_E[i] / 1000);
                            h_electronphi->Fill(lep_phi[i]);
                            h_electroneta->Fill(lep_eta[i]);
                        } else if (lep_charge[i] > 0) {
                            h_positronpt->Fill(lep_pt[i] / 1000);
                            h_positrone->Fill(lep_E[i] / 1000);
                            h_positronphi->Fill(lep_phi[i]);
                            h_positroneta->Fill(lep_eta[i]);
                        }
                        if (lep_n == 2) {
                            for (int j=0; j < i; j++) {
                                if((lep_charge[i] * lep_charge[j]) < 0) {
                                    zLep1.SetPtEtaPhiM(lep_pt[i] / 1000, lep_eta[i], lep_phi[i], 0.000511);
                                    zLep2.SetPtEtaPhiM(lep_pt[j] / 1000, lep_eta[j], lep_phi[i], 0.000511);
                                    double ZeeMass=(zLep1+zLep2).M();
                                    hZtoeeMassM-> Fill(ZeeMass);
                                    zLep1.SetPtEtaPhiE(lep_pt[i] / 1000, lep_eta[i], lep_phi[i], lep_E[i] / 1000);
                                    zLep2.SetPtEtaPhiE(lep_pt[j] / 1000, lep_eta[j], lep_phi[j], lep_E[j] / 1000);
                                    ZeeMass=(zLep1+zLep2).M();
                                    hZtoeeMassE->Fill(ZeeMass);
                                }
                            }
                        }
                    
                    }
                }
            }
        }
        h_multiplicity->Fill(CountM);
    }
    //This area means all I wrote the codes output
    outputFile->cd();
    h_par_type->Write();
    h_passgrl->Write();
    //h_goodvertex->Write();
    h_multiplicity->Write();
    h_electroncharge->Write();
    h_electronpt->Write();
    h_electrone->Write();
    h_electroneta->Write();
    h_positronphi->Write();
    h_positronpt->Write();
    h_positroneta->Write();
    h_positrone->Write();
    hZtoeeMassE->Write();
    hZtoeeMassM->Write();
    hCutEfficiency->Write();
    h_eventnumber->Write();
    //outputfile->Close();
    
}
