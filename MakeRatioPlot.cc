//simple macro to make ratio plots
// takes the canvas you were planning to draw to, the stack of predictions, and a histogram with observations
// it hands back the TPad that the stack and data are to be drawn on 
// 
#include "TROOT.h"
#include <string>

TPad* MakeRatioPlot(TCanvas *TheCanvas, THStack * TheStack, TH1F* TheData)
{
  TPad* PlotPad = new TPad("pad1", "plot", 0., 0.20, 1., 1.);
  PlotPad->Draw();
  TPad* RatioPad = new TPad("pad2", "ratio", 0., 0., 1., 0.20);
  RatioPad->Draw();
  
  PlotPad->cd();

  RatioPad->SetTopMargin(0.0);
  RatioPad->SetBottomMargin(0.3);
  PlotPad->SetBottomMargin(0.08);
  RatioPad->SetGridy();

  TH1F* RatioHist = new TH1F("Ratio", "",
			     TheData->GetSize()-2,
			     TheData->GetXaxis()->GetXmin(),
			     TheData->GetXaxis()->GetXmax());

  RatioHist->Sumw2();
  RatioHist->Add(TheData);

  TH1F* DenominatorHistos = new TH1F("DenominatorHistos","DenominatorHistos",
				     TheData->GetSize()-2,
				     TheData->GetXaxis()->GetXmin(),
				     TheData->GetXaxis()->GetXmax());
  
  TList * ListOfStackHistograms = TheStack->GetHists();
  for(int i = 0; i < TheStack->GetNhists(); i++)
    {
      DenominatorHistos->Add((TH1F*) TheStack->GetHists()->At(i));
    }

  RatioHist->Divide(DenominatorHistos);
  RatioHist->SetMarkerStyle(20);
  
  RatioHist->GetYaxis()->SetTitle("Data/Predicted");    
  RatioHist->GetYaxis()->SetTitleSize(0.11);
  RatioHist->GetYaxis()->SetTitleOffset(.18);
  RatioHist->GetYaxis()->SetLabelSize(0.10);
  RatioHist->GetYaxis()->SetNdivisions(6,0,0);
  
  //RatioHist->GetXaxis()->SetTitleSize(0.10);
  RatioHist->GetXaxis()->SetLabelSize(0.10);
  
  RatioPad->cd();
  RatioHist->Draw("ex0");
  
  PlotPad->cd();

  return PlotPad;
}

//this one will take the canvas and two histograms as input, as well as an X axis label
//it will again hand back the Pad that the histograms are to be drawn on
TPad* MakeRatioPlot(TCanvas *TheCanvas, TH1F* HistoOne, TH1F *HistoTwo, std::string XAxisLabel)
{
  TPad* PlotPad = new TPad("pad1","plot", 0., 0.20, 1., 1.);
  PlotPad->Draw();
  TPad* RatioPad = new TPad("pad2", "ratio", 0., 0., 1., 0.20);
  RatioPad->Draw();

  PlotPad->cd();

  RatioPad->SetTopMargin(0.0);
  RatioPad->SetBottomMargin(0.3);
  PlotPad->SetBottomMargin(0.08);
  RatioPad->SetGridy();

  TH1F* RatioHist = new TH1F("Ratio", "",
			     HistoOne->GetSize()-2,
			     HistoOne->GetXaxis()->GetXmin(),
			     HistoOne->GetXaxis()->GetXmax());

  RatioHist->Sumw2();
  RatioHist->Add(HistoOne);

  RatioHist->Divide(HistoTwo);
  RatioHist->SetMarkerStyle(20);

  RatioHist->GetYaxis()->SetLabelSize(0.10);
  RatioHist->GetYaxis()->SetNdivisions(6,0,0);

  RatioHist->GetXaxis()->SetTitle(XAxisLabel.c_str());  
  RatioHist->GetXaxis()->SetTitleSize(0.10);
  RatioHist->GetXaxis()->SetLabelSize(0.10);
  
  RatioPad->cd();
  RatioHist->Draw("ex0");
  
  PlotPad->cd();

  return PlotPad;
}
