void Sadasd(std::string filename)
{
	double bins[210];
	//~ Int_t  binnum = sizeof(bins)/sizeof(Float_t) - 1; // or just = 9 // cantidad de bines
	double binnum = 209;

	double n = 0;
	for (int i = 0; i <= 11; i++){
		n = double(i - 12);
		bins[i] = pow(10,n);
	}

	for (int i = 2; i <= 200; i++){
		bins[ i + 10 ] = 0.1*i;
	}

	TH1F* hist = new TH1F("fres","Funcion Respuesta", binnum, bins);	// histograma

	TFile * ifile = TFile::Open(filename.c_str());

	if( !ifile ){
		std::cout << filename << " not found" << std::endl;
		return -1;
	}

	TTree * Detectados = (TTree*)ifile->Get("Detectados");
	//~ TTree * Detectados = (TTree*)ifile->Get("Neutrones");
	TTreeReader aReader( Detectados );
	TString Eraser = "Detectados	::	";
	TString Title = Detectados->GetTitle();
	TTreeReaderValue <double>	neutron  (aReader, "Neutron_Energy");
	//~ TTreeReaderValue <double>	neutron  (aReader, "Kinect_MeV");

	Title.ReplaceAll(Eraser, "");
	TString FileName = Title;

	FileName.Resize(6);
	FileName.ReplaceAll("key", "G");
	FileName.ReplaceAll(" ", "");

		
	std::cout << "--number of entries: " << (Long64_t) aReader.GetEntries(kFALSE) << std::endl;
	while( aReader.Next() ){
		hist->Fill(*neutron);		
	}

	
	double C = 0;
	for (int i = 0; i < 210; i++){
		C = hist->GetBinContent( i );
		hist->SetBinContent(i, C);
	}
	
	ifile->Close();
	TCanvas * c1 = new TCanvas("c1", "Funcion Respuesta", 800, 600);

Title = FileName;

	hist->SetTitle(Title);
	hist->Draw();

	c1->SetLogx();
	c1->SetLogy();
	c1->Update();
    
    TFile * ofile = new TFile("Funcion_Respuesta.root","recreate");
    hist->Write();

    c1->SaveAs(FileName+".pdf");

    TAxis* X = hist->GetXaxis();
    TAxis* Y = hist->GetYaxis();
	X->SetRangeUser(0.1,	10);
	Y->SetRangeUser(1,	5e04);

	c1->Update();
	c1->SaveAs(FileName+"_Zoom.pdf");

    ofile->Close();

    return hist->Integral(0,210);  

}
