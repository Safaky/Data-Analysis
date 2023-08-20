#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void analysis::Loop()
{
//   In a ROOT session, you can do:
//      root> .L analysis.C
//      root> analysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//



//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
    //outputfile
    TFile*outputFile= new TFile("Zboson.root","RECREATE");
    //Histogram Yarat
  TH1F * h_eventnumber = new TH1F("h_eventnumber", "Number of Events",8,0,8);
  TH1F *eeta, *ephi, *ePT, *eMass;
  TH1F *Eeta, *Ephi, *EPT, *EMass;
  TH1F *Zeta, *Zphi, *ZPT, *ZMass;
    TH1F *fit;
  
  
  //Histogram tanımla
  
eeta= new TH1F("eeta","electron #eta", 50,-5,5);
   eeta->GetXaxis()->SetTitle("#eta");
   eeta->GetYaxis()->SetTitle("events");
ephi= new TH1F("ephi", "electron #phi", 50,-5,5);
   ephi->GetXaxis()->SetTitle("phi");
   ephi->GetYaxis()->SetTitle("events");
ePT= new TH1F("ePT", "electron p_{T}", 300,0,300);
   ePT->GetXaxis()->SetTitle("PT");
   ePT->GetYaxis()->SetTitle("events");
eMass= new TH1F("eMass","electron", 100,-0.01,0.01);
   eMass->GetXaxis()->SetTitle("mass(GeV)");
   eMass->GetYaxis()->SetTitle("events");
    

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Eeta= new TH1F("Eeta", "positron #eta", 50,-5,5);
   Eeta->GetXaxis()->SetTitle("eta");
   Eeta->GetYaxis()->SetTitle("events");
Ephi= new TH1F("Ephi","electron #phi",50,-5,5);
   Ephi->GetXaxis()->SetTitle("phi");
   Ephi->GetYaxis()->SetTitle("events");
EPT= new TH1F("EPT", "positron p_{T}",300,0,300);
   EPT->GetXaxis()->SetTitle("PT");
   EPT->GetYaxis()->SetTitle("events");
EMass= new TH1F("EMass","positron", 100,-0.01,0.01);
   EMass->GetXaxis()->SetTitle("mass(GeV");
   EMass->GetYaxis()->SetTitle("events");
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ZMass= new TH1F("ZMass","Z boson", 100,0,200);
        ZMass->GetXaxis()->SetTitle("mass(GeV)");
        ZMass->GetYaxis()->SetTitle("events");

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    int eventnumber=0;
   
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        //İf (Cut(ientry)<0) continue;
        eventnumber++;
        h_eventnumber->Fill(1);

        //Değişken tanımladık-elektron,pozitron,Zboson
        TLorentzVector e1;
        TLorentzVector e2;
        TLorentzVector Z;
            
        e1.SetPtEtaPhiM (Particle_PT[2], Particle_Eta[2], Particle_Phi[2], Particle_M[2]);
        e2.SetPtEtaPhiM (Particle_PT[3], Particle_Eta[3], Particle_Phi[3], Particle_M[3]);
        
        Z=e1+e2;
        ZMass->Fill(Z.M());
        
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            
              
              //Histogramları burda doldurduk
               eMass->Fill(e1.M());
               ePT->Fill(e1.Pt());
               eeta->Fill(e1.Eta());
               ephi->Fill(e1.Phi());
               EMass->Fill(e2.M());
               EPT->Fill(e2.Pt());
               Eeta->Fill(e2.Eta());
               Ephi->Fill(e2.Phi());
               
               
    }
    
            
    // Histogramlar burda yazıldı.Ekrana düşmesi. Bir daha paranteze gerek yok!
    
    outputFile->cd();
    h_eventnumber->Write();
    ePT->Write();
    eeta->Write();
    ephi->Write();
    eMass->Write();
    Eeta->Write();
    Ephi->Write();
    EPT->Write();
    EMass->Write();
    ZMass->Write();
   
   
}
