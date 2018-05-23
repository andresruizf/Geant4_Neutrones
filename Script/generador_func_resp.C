#include <string>
#include <vector>
#include "TTreeReader.h"

void Generador_Funciones_Respuestas(int inicio, int fin)
{
	double bins[210];
	double bininicio = 209;

	double n = 0;
	for (int i = 0; i <= 11; i++){
		n = double(i - 12);
		bins[i] = pow(10,n);
	}

	for (int i = 2; i <= 200; i++){
		bins[ i + 10 ] = 0.1*i;
	}

	TH1D** histoarray = new TH1D*[9];		// array of histograms //
	for (int i=0;i<9;i++) { histoarray[i] = new TH1D(Form("fr%d",i),"test",bininicio,bins); }

	
	TCanvas * c1 = new TCanvas("c1", "Funcion Respuesta",1920, 1080 );
	c1->Divide(3,3);


	std::string OutName;
	std::string Path;
	std::string From;
	std::string To;
	std::string file;
	std::string filename ;
	Path = "/data_G";
	inicio = inicio - 1;

	while (true){
		From = std::to_string(inicio+1);
		for (int i = 0; i < 9; i++){
			inicio++;
			if (inicio > fin) {inicio = inicio -1; break;}
			file = std::to_string(inicio);
			filename = file + Path + file + ".root";
				
			TFile * ifile = TFile::Open(filename.c_str());
			if( !ifile ){
				std::cout << filename << " not found" << std::endl;
				continue;
			}

			TTree * Detectados = (TTree*)ifile->Get("Detectados");
			TTreeReader aReader( Detectados );
			TString Eraser = "Detectados	::	";
			TString Title = Detectados->GetTitle();
			TTreeReaderValue <double>	neutron  (aReader, "Neutron_Energy");

			Title.ReplaceAll(Eraser, "");
			TString FileName = Title;

			FileName.Resize(6);
			FileName.ReplaceAll("key", "G");
			FileName.ReplaceAll(" ", "");

			int entries = aReader.GetEntries(kFALSE);
			std::cout << "Geometry -> " << inicio << "	 ::   number of entries: " << (Long64_t) aReader.GetEntries(kFALSE) << std::endl;
			while( aReader.Next() ){
				histoarray[i]->Fill(*neutron);		
			}
			
			ifile->Close();
			Title = FileName;

			histoarray[i]->SetTitle(Title);
			c1->cd(i+1);
			histoarray[i]->Draw();
			gPad->Update();	// Update para asegurar la creacion del pave stats //
			TPaveStats *st1 = (TPaveStats*)histoarray[i]->FindObject("stats");	// encontrar la instancia de pave stats //
			// Cambiando las coordenas '1' //
			st1->SetY1NDC(0.1);
			st1->SetX1NDC(0.7);
			// Cambiando las coordenadas '2' //
			st1->SetY2NDC(0.2);
			st1->SetX2NDC(0.9);
		}
		To = std::to_string(inicio);


			
		for (int j = 1; j < 10; j++){
			c1->cd(j)->SetLogx();
			c1->cd(j)->SetLogy();
			c1->cd(j)->Update();
		}

		OutName = From + "-" + To + ".pdf";
		c1->SaveAs(OutName.c_str());
		c1->Clear();
		c1->Divide(3,3);
		if (inicio == fin) break;

	}
	c1->Destructor();

    return 42;  

}
