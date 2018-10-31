//simple macro to make ratio plots
// takes the canvas you were planning to draw to, the stack of predictions, and a histogram with observations
// it hands back the TPad that the stack and data are to be drawn on 
// 
#include "TROOT.h"
#include <string>

TPad* MakeRatioPlot(TCanvas *TheCanvas, THStack * TheStack, TH1F* TheData, string XAxisLabel)
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
  //okay, apparently CMS wants ratio histogram errors reported in the least convenient way possible,
  //with marker errors denoting actualy statistical uncertaiinty on the data, and then a sepreate 
  //opaque bar denoting... something?
  TH1F* FinalRatioHist = new TH1F("FinalRatio","",
				  RatioHist->GetNbinsX(),
				  RatioHist->GetXaxis()->GetXmin(),
				  RatioHist->GetXaxis()->GetXmax());

  for(int i = 1; i <= FinalRatioHist->GetNbinsX(); ++i)
    {
      FinalRatioHist->SetBinContent(i,RatioHist->GetBinContent(i));
      FinalRatioHist->SetBinError(i, (TheData->GetBinError(i)/TheData->GetBinContent(i))*RatioHist->GetBinContent(i));
    }

  FinalRatioHist->SetMarkerStyle(20);
  
  FinalRatioHist->GetYaxis()->SetTitle("Data/Predicted");    
  FinalRatioHist->GetYaxis()->SetTitleSize(0.1);
  FinalRatioHist->GetYaxis()->SetTitleOffset(0.32);  
  FinalRatioHist->GetYaxis()->CenterTitle();
  FinalRatioHist->GetYaxis()->SetLabelSize(0.10);
  FinalRatioHist->GetYaxis()->SetNdivisions(5,0,0);
  
  FinalRatioHist->GetXaxis()->SetLabelSize(0.10);

  FinalRatioHist->GetXaxis()->SetTitle(XAxisLabel.c_str());
  FinalRatioHist->GetXaxis()->SetTitleSize(0.14);

  //okay, now we need to create the weird bar histogram that represents the actual error on the ratio.
  TH1F* MCErrors = new TH1F("MCErrors","MCErrors",
			    RatioHist->GetNbinsX(),
			    RatioHist->GetXaxis()->GetXmin(),
			    RatioHist->GetXaxis()->GetXmax());
    
  for(int i = 1; i<= MCErrors->GetNbinsX(); ++i)
    {
      MCErrors->SetBinContent(i,1.0);
      MCErrors->SetBinError(i,DenominatorHistos->GetBinError(i)/DenominatorHistos->GetBinContent(i));            
    }  
  
  MCErrors->SetFillStyle(3001);
  MCErrors->SetFillColor(15);  

  RatioPad->cd();
  FinalRatioHist->Draw("ex0");
  MCErrors->Draw("SAME e2");
  FinalRatioHist->Draw("SAME ex0");
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

  //RatioHist->GetYaxis()->SetRangeUser(0.8,1.2);
  RatioHist->GetYaxis()->SetLabelSize(0.10);
  RatioHist->GetYaxis()->SetNdivisions(5,0,0);

  RatioHist->GetXaxis()->SetTitle(XAxisLabel.c_str());  
  RatioHist->GetXaxis()->SetTitleSize(0.10);
  RatioHist->GetXaxis()->SetLabelSize(0.10);

  RatioPad->cd();
  RatioHist->Draw("ex0");
  
  PlotPad->cd();

  return PlotPad;
}
