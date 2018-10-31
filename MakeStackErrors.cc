#include "TROOT.h"

TH1F* MakeStackErrors(THStack* TheStack)
{
  TH1F* DenominatorHistos = new TH1F("DenominatorHistos","DenominatorHistos",
				     ((TH1F*) TheStack->GetHists()->At(0))->GetNbinsX(),
				     ((TH1F*) TheStack->GetHists()->At(0))->GetXaxis()->GetXmin(),
				     ((TH1F*) TheStack->GetHists()->At(0))->GetXaxis()->GetXmax());
  TList * ListOfStackHistograms = TheStack->GetHists();
  for(int i = 0; i < TheStack->GetNhists(); i++)
    {
      DenominatorHistos->Add((TH1F*) TheStack->GetHists()->At(i));
    }
  
  TH1F* TheErrorHisto = new TH1F("TheErrorHisto","",
				 DenominatorHistos->GetNbinsX(),
				 DenominatorHistos->GetXaxis()->GetXmin(),
				 DenominatorHistos->GetXaxis()->GetXmax());

  for(int i=1; i <= DenominatorHistos->GetNbinsX(); ++i)
    {
      TheErrorHisto->SetBinContent(i, DenominatorHistos->GetBinContent(i));
      TheErrorHisto->SetBinError(i, DenominatorHistos->GetBinError(i));
    }  
  TheErrorHisto->SetLineColor(0);
  TheErrorHisto->SetLineWidth(0);
  TheErrorHisto->SetMarkerSize(0);
  TheErrorHisto->SetFillStyle(3001);
  TheErrorHisto->SetFillColor(15);
  return TheErrorHisto;
}
