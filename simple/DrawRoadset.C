#include "UtilTrigger.h"
using namespace std;
void DrawOne(const int rs_id, const vector<int>* list_road, const string label, const string name);

/**
 * ROOT macro to draw all enabled roads in the given roadset.
 * It is an example of using UtilTrigger etc.
 */
void DrawRoadset(const int rs_id)
{
  cout << "Roadset " << rs_id << endl;
  auto list_road_pos_top = UtilTrigger::ReadRoadList(rs_id, "plus" , "top"   );
  auto list_road_pos_bot = UtilTrigger::ReadRoadList(rs_id, "plus" , "bottom");
  auto list_road_neg_top = UtilTrigger::ReadRoadList(rs_id, "minus", "top"   );
  auto list_road_neg_bot = UtilTrigger::ReadRoadList(rs_id, "minus", "bottom");
  DrawOne(rs_id, &list_road_pos_top, "Positive Top"   , "pos_top");
  DrawOne(rs_id, &list_road_pos_bot, "Positive Bottom", "pos_bot");
  DrawOne(rs_id, &list_road_neg_top, "Negative Top"   , "neg_top");
  DrawOne(rs_id, &list_road_neg_bot, "Negative Bottom", "neg_bot");
  exit(0);
}

void DrawOne(const int rs_id, const vector<int>* list_road, const string label, const string name)
{
  gStyle->SetOptStat(0);
  TCanvas* c1 = new TCanvas("c1", "", 1600, 800);
  c1->SetMargin(0.02, 0.02, 0.02, 0.02); // (l, r, b, t)
  TH1* frame = new TH2D("frame", "", 1, 0.5, 4.5, 1, -9, 9);
  frame->Draw("A");
  
  TLine line;
  line.SetLineColor(kBlue);
  for (auto it = list_road->begin(); it != list_road->end(); it++) {
    int h1, h2, h3, h4, tb;
    UtilTrigger::Road2Hodo(*it, h1, h2, h3, h4, tb);
    line.DrawLine(1, (h1-12)*0.5, 2, (h2-8.5));
    line.DrawLine(2, (h2-8.5)   , 3, (h3-8.5));
    line.DrawLine(3, (h3-8.5)   , 4, (h4-8.5));
  }

  TGraph* gr = new TGraph();
  gr->SetMarkerColor(kRed);
  gr->SetMarkerStyle(8);
  for (int ii = 1; ii <= 23; ii++) gr->SetPoint(gr->GetN(), 1, (ii-12)*0.5);
  for (int ii = 1; ii <= 16; ii++) gr->SetPoint(gr->GetN(), 2, (ii-8.5));
  for (int ii = 1; ii <= 16; ii++) gr->SetPoint(gr->GetN(), 3, (ii-8.5));
  for (int ii = 1; ii <= 16; ii++) gr->SetPoint(gr->GetN(), 4, (ii-8.5));
  gr->Draw("P");

  TText text;
  text.SetNDC(true);
  text.DrawText(0.04, 0.92, Form("Roadset %i", rs_id) );
  text.DrawText(0.04, 0.86, label.c_str());
  text.DrawText(0.08, 0.06, Form("%zu roads", list_road->size()) );
  
  gSystem->mkdir("result", true);  
  c1->SaveAs( Form("result/rs%i_%s.pdf", rs_id, name.c_str()) );

  delete gr;
  delete frame;
  delete c1;
}
