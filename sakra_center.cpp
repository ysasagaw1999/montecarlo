{
    double length_start = 35.036;
    double each_length = 6.399375;
    double angle_start = -1 * M_PI / 6;
    double each_angle = M_PI / 24;
    
    // Calculate center coordinates and store them in arrays
    const int nPoints = 16 * 8; // Total number of points
    double x[nPoints];
    double y[nPoints];
    int pointIndex = 0;
    for (int f_ch = 0; f_ch < 16; f_ch++) {
        double center_r = length_start + (f_ch + 0.5) * each_length;
        for (int r_ch = 0; r_ch < 8; r_ch++) {
            double center_th = angle_start + (r_ch + 0.5) * each_angle;
            x[pointIndex] = center_r * cos(center_th); // X coordinate
            y[pointIndex] = center_r * sin(center_th); // Y coordinate
            pointIndex++;
        }
    }

    // Create a canvas
    TCanvas* c1 = new TCanvas("c1", "Center Plot", 800, 600);

    // Create a graph
    TGraph* graph = new TGraph(nPoints, x, y);
    graph->SetMarkerStyle(20); // Set marker style to circle

    // Draw the graph
    graph->Draw("AP"); // "AP" option draws the graph with markers

    // Set axis titles
    graph->GetXaxis()->SetTitle("X");
    graph->GetYaxis()->SetTitle("Y");

    // Draw the canvas
    c1->Draw();

    return 0;
}
