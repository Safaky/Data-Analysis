#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analysis::Loop()
{


   if (fChain == 0) return;

    
        TFile *outputFile = new TFile("output.root","RECREATE");
        
        
        TH1F * h_eventnumber = new TH1F("h_eventnumber","NumberofEvents",5,0,5);
        h_eventnumber->GetYaxis()->SetTitle("Events");
        
        
        TH1F * h_electronmultiplicity = new TH1F("h_electronmultiplicity", "Electron Multiplicity",20,0,20);
        h_electronmultiplicity->GetXaxis()->SetTitle("electron multiplicity");
        h_electronmultiplicity->GetYaxis()->SetTitle("Events");
        TH1F * h_electroncharge = new TH1F("h_electroncharge","Charge Distribution of Electrons",100,-3,3);
        h_electroncharge->GetXaxis()->SetTitle("electron charge");
        h_electroncharge->GetYaxis()->SetTitle("Events");
        TH1F * h_electronpt = new TH1F("h_electronpt","Pt Distribution of Electrons",200,0,200);
        //h_electroneta->GetXaxis()->SetTitle("PT");
        //h_electroneta->GetYaxis()->SetTitle("Events");
        TH1F * h_electroneta = new TH1F("h_electroneta","Eta Distribution of Electrons",24,-2.4,2.4);
        h_electroneta->GetXaxis()->SetTitle("ETA");
        h_electroneta->GetYaxis()->SetTitle("Events");
        TH1F * h_electronphi = new TH1F("h_electronphi","Phi Distribution of Electrons",20,0,20);
        h_electronphi->GetXaxis()->SetTitle("PHI");
        h_electronphi->GetYaxis()->SetTitle("Events");
        
        TH1F * hZtoEeMass= new TH1F("hZtoEeMass","Reconstructed Mass of ZtoEe",100,0,200);
        hZtoEeMass->GetXaxis()->SetTitle("m_{Z}^{#e#e} (GeV)");
        hZtoEeMass->GetYaxis()->SetTitle("Events/2Gev");
        hZtoEeMass->GetYaxis()->SetTitleOffset(1.20);
                
        TH1F * hZtoEeMass2= new TH1F("hZtoEeMass2","Reconstructed Mass of ZtoEe",100,0,200);
        hZtoEeMass2->GetXaxis()->SetTitle("m_{Z}^{#e#e} (GeV)");
        hZtoEeMass2->GetYaxis()->SetTitle("Events/2Gev");
        hZtoEeMass2->GetYaxis()->SetTitleOffset(1.20);

    //DeltaR
        TH1F *heEDR = new TH1F("h_eEDR","",100,0,10);
        heEDR->GetXaxis()->SetTitle("electron #DeltaR");
        
        //See cut
        TH1F * hCutEfficiency = new TH1F("hCutEfficiency","Cut Efficiency",10,0,10);
        
        int eventnumber=0;
        Long64_t nentries = fChain->GetEntriesFast();

       Long64_t nbytes = 0, nb = 0;
       for (Long64_t jentry=0; jentry<nentries;jentry++) {
          Long64_t ientry = LoadTree(jentry);
          if (ientry < 0) break;
          nb = fChain->GetEntry(jentry);   nbytes += nb;
          // if (Cut(ientry) < 0) continue;
           eventnumber++;
           h_eventnumber->Fill(1);
           hCutEfficiency->Fill(0);
           
           TLorentzVector zLep1,zLep2;
           
           int nElectrons = Electron_size;
           int countM=0;
           bool ZfromM = false;
           float Ee=0;
           
           for (int i =0; i < nElectrons; i++) {
               countM++;
               h_electronpt->Fill(Electron_PT[i]);
               h_electroneta->Fill(Electron_Eta[i]);
               h_electronphi->Fill(Electron_Phi[i]);
               h_electroncharge->Fill(Electron_Charge[i]);
               for(int j=0; j < i; j++)  {
                              if((Electron_Charge[i]*Electron_Charge[j]) < 0){
                                  hCutEfficiency->Fill(1);
                                  zLep1.SetPtEtaPhiM(Electron_PT[i], Electron_Eta[i], Electron_Phi[i],0.511);
                                  zLep2.SetPtEtaPhiM(Electron_PT[j], Electron_Eta[j], Electron_Phi[j],0.511);
                                  double ZeEmass=(zLep1+zLep2).M();
                                  ZfromM = true;
                                  hZtoEeMass->Fill(ZeEmass);
                                  if((fabs(ZeEmass-91))<20){
                                      hCutEfficiency->Fill(2);
                                      hZtoEeMass2->Fill(ZeEmass);
                                  }
                                  //deltaR//
                                 //EEdR = DeltaR(Electron_Eta[i], Electron_Phi[i], Electron_Eta[j], Electron_Phi[j]);
                                   //heEDR->Fill(EEdR);
                              }
                          }
                       h_electronmultiplicity->Fill(countM);
                       }//end of electron loop
                   }
                   outputFile->cd();
                   h_eventnumber->Write();
                   h_electronmultiplicity->Write();
                   h_electroncharge->Write();
                   h_electronpt->Write();
                   h_electroneta->Write();
                   h_electronphi->Write();
                   heEDR->Write();
                   hZtoEeMass->Write();
                   hZtoEeMass2->Write();
                   hCutEfficiency->Write();
                   
               }
