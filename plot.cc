{

std::ifstream infile1("onSakra.dat");
std::vector<double> x1, y1;
double x_val1, y_val1;
while (infile1 >> x_val1 >> y_val1) {
    y1.push_back(y_val1);
    x1.push_back(x_val1);
}
infile1.close();

std::ifstream infile2("outSakra.dat");
std::vector<double> x2, y2;
while (infile2 >> x_val2 >> y_val2) {
    y2.push_back(y_val2);
    x2.push_back(x_val2);
}
infile2.close();

int n1 = x1.size();
TGraph *g1 = new TGraph(n1,x1.data(),y1.data());
g1->SetLineColor(kBlue); 
g1->SetLineWidth(2); 

int n2 = x2.size();
TGraph *g2 = new TGraph(n2,x2.data(),y2.data());
g2->SetMarkerStyle(20); 
g2->SetMarkerSize(1.5); 
g2->SetMarkerColor(kRed); 

TCanvas *c1 = new TCanvas("c1", "", 0, 0, 1000, 700);
c1 -> SetGrid(1);  

g1->Draw("AP");
g1->GetXaxis()->SetRangeUser(-100., 100.);
g1->GetYaxis()->SetRangeUser(-100., 100.);
g2->Draw("P same");

c1 -> Update();
c1 -> Print("temp.pdf"); 
return 0;

}