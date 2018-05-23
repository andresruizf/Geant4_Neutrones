{ 
//this is a ROOT macros. to run it you must have ROOT toolkit installed. In a terminal > root -l matrix_creator.cpp. A "matriz_datos.dat" output file is created.
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream> 


string sumanombre;
sumanombre= "matriz_datos.dat"; //output file name
ofstream archivosalida(sumanombre.c_str());

vector<string> gases_mat = {"He3Gas", "BF3Gas"}; //neutron detectors materials as called in Geant
vector<string> moderadores_mat = {"Air", "Polyethylene_TS", "Boron_Polyethylene_TS", "Cadmium"}; //moderator materials as called in Geant
vector<double> radio_det={63.8,50.6}; //neutron detectors radii respectively acording to gases_mat vector
vector<double> length_det={375,295}; //neutron detectors length respectively acording to gases_mat vector
vector<double> espesor_Cadmium = {0,1.1}; // cadmium sheet width. Zero value is inclueded just in this case and means no presence of Cd in a layer
vector<double> espesor_Polyethylene_TS ={42.5};// HDPE widths must be defined as vector components
vector<double> espesor_Boron_Polyethylene_TS = {25, 12.7}; //Boron HDPE 5% widths must be defined here as vector components
vector <string> lineadummy; //dummy vector to store temporally string components: names and numbers converted in string.

double tamano_capa1= 10; //this is the core total width. In our sketch is CAPA 1

for(int i=0; i<gases_mat.size();i++){
          
     lineadummy.push_back(gases_mat[i]);
if (i==0) { std::ostringstream strs; strs << radio_det[i]; std::string str = strs.str();lineadummy.push_back(str);
    std::ostringstream strs1; strs1 << length_det[i]; std::string str1 = strs1.str();lineadummy.push_back(str1);
} 
else {std::ostringstream strs; strs << radio_det[i]; std::string str = strs.str();lineadummy.push_back(str);
	std::ostringstream strs1; strs1 << length_det[i]; std::string str1 = strs1.str();lineadummy.push_back(str1);
	}

lineadummy.push_back("Aluminum");lineadummy.push_back("1.0");
lineadummy.push_back("Cadmium");
    
for (int i1=0;i1<espesor_Cadmium.size();i1++){
    std::ostringstream strs; strs << espesor_Cadmium[i1]; std::string str = strs.str();lineadummy.push_back(str);
    for(int i2=0; i2<moderadores_mat.size();i2++){//capa1
       if(moderadores_mat[i2] != "Cadmium"){
           lineadummy.push_back(moderadores_mat[i2]);
           std::ostringstream strs; strs << tamano_capa1; std::string str = strs.str();lineadummy.push_back(str);
       
           
           
           for(int i3=0; i3<moderadores_mat.size();i3++){//capa2
           if(moderadores_mat[i3]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i3]);
              for (int i31=0;i31<espesor_Boron_Polyethylene_TS.size();i31++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i31]; std::string str = strs.str();lineadummy.push_back(str);
                for(int i4=0; i4<moderadores_mat.size();i4++){//capa2
                    if(moderadores_mat[i4]=="Boron_Polyethylene_TS"){
                        lineadummy.push_back(moderadores_mat[i4]);
                            for (int i41=0;i41<espesor_Boron_Polyethylene_TS.size();i41++){
                                    std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i41]; std::string str = strs.str();lineadummy.push_back(str);
                                        for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
                                                                if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                                                                        lineadummy.push_back(moderadores_mat[i5]);
                                                                            for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
                                                                                    std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
                                                                                    for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " ";  archivosalida<<lineadummy[k]<<" ";}
                                                                                        cout<< endl;archivosalida<<endl;
                                                                                            lineadummy.pop_back();
                                                                                                                                            }
                                                                                                                        lineadummy.pop_back();
                                                                                                                }
                                                                else if(moderadores_mat[i5]=="Polyethylene_TS"){
                                                                        lineadummy.push_back(moderadores_mat[i5]);
                                                                                for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
                                                                                        std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
                                                                                            for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                                                                                              cout<< endl;archivosalida<<endl;
                                                                                                        lineadummy.pop_back();
                                                                                                                                        }
                                                                                            lineadummy.pop_back();
                                                                                                                }
                                                                else if(moderadores_mat[i5]=="Cadmium"){
                                                                    lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i4]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Polyethylene_TS.size();i41++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i41]; std::string str = strs.str();lineadummy.push_back(str);
               for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
     
          
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i4]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Cadmium.size();i41++){
              std::ostringstream strs; strs << espesor_Cadmium[i41]; std::string str = strs.str();lineadummy.push_back(str);
              for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
     
    
          
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           }
              
              
              
              
              
              lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i3]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i3]);
              for (int i31=0;i31<espesor_Polyethylene_TS.size();i31++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i31]; std::string str = strs.str();lineadummy.push_back(str);
                for(int i4=0; i4<moderadores_mat.size();i4++){//capa2
     
      
          
           if(moderadores_mat[i4]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Boron_Polyethylene_TS.size();i41++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i41]; std::string str = strs.str();lineadummy.push_back(str);
               for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
 
          
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i4]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Polyethylene_TS.size();i41++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i41]; std::string str = strs.str();lineadummy.push_back(str);
              for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
     
           //archivosalida<<moderadores_mat[i3]<<" " <<tamano_capa1<<" ";
          
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i4]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Cadmium.size();i41++){
              std::ostringstream strs; strs << espesor_Cadmium[i41]; std::string str = strs.str();lineadummy.push_back(str);
               for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
     
      
          
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           }
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i3]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i3]);
              for (int i31=0;i31<espesor_Cadmium.size();i31++){
              std::ostringstream strs; strs << espesor_Cadmium[i31]; std::string str = strs.str();lineadummy.push_back(str);
                for(int i4=0; i4<moderadores_mat.size();i4++){//capa2
   
          
           if(moderadores_mat[i4]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Boron_Polyethylene_TS.size();i41++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i41]; std::string str = strs.str();lineadummy.push_back(str);
               for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
     
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i4]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Polyethylene_TS.size();i41++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i41]; std::string str = strs.str();lineadummy.push_back(str);
              for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
     
           //archivosalida<<moderadores_mat[i3]<<" " <<tamano_capa1<<" ";
          
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i4]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i4]);
              for (int i41=0;i41<espesor_Cadmium.size();i41++){
              std::ostringstream strs; strs << espesor_Cadmium[i41]; std::string str = strs.str();lineadummy.push_back(str);
               for(int i5=0; i5<moderadores_mat.size();i5++){//capa2
     
          
          
           if(moderadores_mat[i5]=="Boron_Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Boron_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Boron_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
            else if(moderadores_mat[i5]=="Polyethylene_TS"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Polyethylene_TS.size();i51++){
              std::ostringstream strs; strs << espesor_Polyethylene_TS[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
           else if(moderadores_mat[i5]=="Cadmium"){
                lineadummy.push_back(moderadores_mat[i5]);
              for (int i51=0;i51<espesor_Cadmium.size();i51++){
              std::ostringstream strs; strs << espesor_Cadmium[i51]; std::string str = strs.str();lineadummy.push_back(str);
               for(int k=0;k<lineadummy.size();k++){cout<<lineadummy[k]<< " "; archivosalida<<lineadummy[k]<<" ";}
                 cout<< endl;archivosalida<<endl;
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           } 
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           }
               lineadummy.pop_back();
            }
               lineadummy.pop_back();
        }
     //hasta aqui     
           }
  
             lineadummy.pop_back();lineadummy.pop_back();

    }

    
    
    }//for capa1

lineadummy.pop_back();




    
}//for cadmium
lineadummy.pop_back();lineadummy.pop_back();lineadummy.pop_back();lineadummy.pop_back();lineadummy.pop_back();lineadummy.pop_back();
//archivosalida<< endl;
} //for de gases
//for capa
archivosalida.close();
}
