// Author: Edward James Williams, Student Number: 170532613

#include <iostream>   //To enable screen input and output
#include <sstream>    //To convert string to int
#include <fstream>    //To enable file input and output
#include <stdexcept>  //To handle exceptions
#include <direct.h>   //To create directories
#include <ctime>      //To improve randomisation of numbers
#include <string>     //To enable the use of strings
#include <windows.h>  //To enable the use of Windows-specific types (e.g. DWORD)
#include <vector>     //To enable the (extensive) use of vectors
#include <io.h>       //To enable the use of the file access function
#include <chrono>	  //To enable the calculation of the duration of events
#include <iomanip>    //To set number of decimal places
#include <regex>	  //To replace characters in strings
#include <future>     //To enable multi-threading

using namespace std;

void fixInput(string x, int& s, int lower, int upper, string message) {
	istringstream iss(x);
	s = 0;
	iss >> s;
	while ((s < lower) || (s > upper)) {
		cout << message;
		cin >> x;
		istringstream iss(x);
		iss >> s;
	}
}

int GetNumOfFiles(string dir) {
	int i = 1;
	int highest = 0;
	string testFilename;
	while (i <= 999) {
		testFilename = dir + to_string(i) + ".obj";
		if (_access_s(testFilename.c_str(), 0) == 0) {
			highest = i;
		}
		i++;
	}
	return highest;
}

void writeIndividualFile() {
//	string item = "g 1499_Furn_Chair_Auditorium:LT3 Lecture Seat:";

//	string item = "g 1499_Furn_Chair_Meeting:Standard Meeting";

//	string item = "g System Panel:Glass Rainscreen Bronze:3084796";

//	string item = "g System Panel:Glazed";
	
//	string item = "g Rectangular Mullion:Cladding Joint 20mm";

//	string item = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:3";

//	string item = "g System Panel:Glass Rainscreen Bronze:3093964";

//	string item = "g SG Panel:SG Panel South East Facade:3091804";

//	string item = "g Rectangular Mullion:Schuco FW60+ Mullion Extended Cap:3835598";

//	string item = "g Basic Roof:40-45-45-175_Semi-intensive_Green_Roof_System:2894773";

//	string item = "g System Panel:Glass Rainscreen Bronze:3089685";

//	string item = "g Metal Rainscreen:Metal Panel Rainscreen:3086628";

//	string item = "g SG Panel:SG Panel 2450mm wide:";

//	string item = "g AWS114 SG Manual:AWS114 SG Manual:";

//	string item = "g System Panel:SG Panel Sloped:5523369";

//	string item = "g Rectangular Mullion:Schuco FW60+ Mullion Extended Cap:6069041";

//	string item = "g Basic Wall:RB-07b-25-85-45-150 ExtWall IWL 92mm Stud 2 boards + ins:11078769";

//	string item = "g NGB_Valve_OventropCoconQTZFlowControlValve-Male-Male:DN 15 (90-450):8360640";

//	string item = "g NGB_Valve_PipeworkTempSensor:NGB-Pipework Temp Sensor:";

//	string item = "g Glazed Internal Single Doors:";
//	string item = "g Glazed Internal Sliding Door:";
//	string item = "g HB_Door_Concept_Int_Dbl_Solid";
//	string item = "g HB_Door_Concept_Int_Sgl_Solid";
//	string item = "g Glazed Internal Double Doors:";
//	string item = "g HB_WC_Cubicle_FrontOnly:3888 Width 900 Door:";

	//string item = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486507";
//	string item = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8447898";
//	string item = "g 1499_Furn_CoffeeCart:1499_Furn_CoffeeCart:7432262";
//	string item = "g Basic Roof:HKB_Roof__Entrance Canopy:19043512";
//	string item = "g Sliding_Stacking_Panel_Partition:DT-17:8292025";

//	string item = "g External signage2:External signage:4747993";

	string item = "g Basic Roof:20-50-30-180_Reinforced_Bitumen_Membrane_Inverted_Roof_Covering_System (500 x 200mm  Paving):2324097:1";

	int length = (int)item.length();
	
	string objfile = "Z:\\USB Data\\OutsideUltra.obj";
	string datafile = "Z:\\USB Data\\OutsideDivided\\Missing1.obj";
//	string objfile = "Z:\\USB Data\\InsideCompleteRotatedTranslated2.obj";
//	string datafile = "Z:\\USB Data\\Inside\\Deleted Objects\\Sliding_Stacking_Panel_Partition.obj";
	
	ifstream obj(objfile);	
	ofstream data(datafile);

	string line;

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	int vertex = 0;
	int validVertex = 0;
	int texcoord = 0;
	int validTexcoord = 0;
	int normal = 0;
	int validNormal = 0;
	int triangle[9];
	string a = " ";
	getline(obj, line);
	string test = line.substr(0, 2);
	string sub;
	vector<string> lines;
	while (!obj.eof()) {
		vertex = 0;
		texcoord = 0;
		normal = 0;
		lines.clear();
		bool valid = false;
		sub = line.substr(0, length);
		if (sub == item) {
			lines.push_back(line);
			valid = true;			
		}

		if (valid) {
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test != "g ") {
					if (test == "v ") {
						vertex++;
					}
					if (test == "vt") {
						texcoord++;
					}
					if (test == "vn") {
						normal++;
					}
					lines.push_back(line);
				}
				else
				{
					break;
				}
			}

			for (auto i : lines) {
				string replace = i.substr(0, 1);
				if (replace == "f") {
					string line1 = regex_replace(i, std::regex(R"(\/)"), a);
					stringstream ss;
					ss << line1;
					string temp;
					int found;
					int i = 0;
					while (!ss.eof()) {
						ss >> temp;
						if (stringstream(temp) >> found) {
							if (i == 0 || i == 3 || i == 6) {
								triangle[i] = found - validVertex;
							}
							if (i == 1 || i == 4 || i == 7) {
								triangle[i] = found - validTexcoord;
							}
							if (i == 2 || i == 5 || i == 8) {
								triangle[i] = found - validNormal;
							}
							i++;
						}
						temp = "";
					}
					data << "f " << triangle[0] << '/' << triangle[1] << '/' << triangle[2] << ' '
						 << triangle[3] << '/' << triangle[4] << '/' << triangle[5] << ' '
						 << triangle[6] << '/' << triangle[7] << '/' << triangle[8] << endl;
				}
				else {
					data << i << endl;
				}
			}
		//	break; //Comment this out to create obj containing all instances of target object
		}
		else {
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test == "v ") {
					vertex++;
				}
				if (test == "vt") {
					texcoord++;
				}
				if (test == "g ") {				
					break;
				}
			}
			validVertex += vertex;
			validTexcoord += texcoord;
			validNormal += normal;
		}		
	}
	data.close();
	obj.close();
}

void ImproveEfficiency() {
//	string chair = "g System Panel:Glass Rainscreen Bronze";
	string window = "g System Panel:Glazed";
	string mcladding = "g Rectangular Mullion:Cladding Joint 20mm";
	string mainwindow = "g SG Panel:SG Panel South East Facade:";
	string bronzerainscreen = "g System Panel:Glass Rainscreen Bronze:";
	string metalrainscreen = "g Metal Rainscreen:Metal Panel Rainscreen";
	string greyrainscreen = "g System Panel:Glass Rainscreen Grey:";
	string mainwindow2 = "g SG Panel:SG Panel";
	string openwindow = "g AWS114 SG Manual:AWS114 SG Manual:";
	string slopedwindow = "g System Panel:SG Panel Sloped:";
	string windowframe = "g Rectangular Mullion:Schuco FW60+ Mullion Extended Cap:";

	int blength = (int)bronzerainscreen.length();
	int mrlength = (int)metalrainscreen.length();
	int glength = (int)greyrainscreen.length();
	int wlength = (int)window.length();
	int mlength = (int)mcladding.length();
	int mwlength = (int)mainwindow.length();
	int mw2length = (int)mainwindow2.length();
	int owlength = (int)openwindow.length();
	int swlength = (int)slopedwindow.length();
	int wflength = (int)windowframe.length();

	string x;
	string objfile;
	string line;

//	objfile = "Z:\\IFC Data\\Outside.obj";
	objfile = "Z:\\IFC Data\\Outside1\\7a.obj";
	string datafile = "Z:\\IFC Data\\Outside1\\Efficient2.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string panelsfile = "Z:\\IFC Data\\Output\\Outside\\BestPanels.txt";
	ofstream panels(panelsfile);

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	int vertex = 0;
	int validVertex = 0;
	float vertices[3];
	string a = " ";
	getline(obj, line);
	string test = line.substr(0, 2);
	string sub;
	string previousSub = " ";
	vector<string> lines;

	string temp0;
	string temp1;
	string temp2;

	int obCount = 0;
	int tcCount = 0;


	string testpanel = "";

	while (!obj.eof()) {
		vertex = 0;
		lines.clear();
		bool valid = false;
		bool mainwin = false;
		bool rainscr = false;
		bool altpanel1 = false;
		bool frame = false;
		sub = line.substr(0, blength);		
		if (sub == bronzerainscreen) {
			if (previousSub != sub) {
			//	lines.push_back(line);
			}
			testpanel = line;
			lines.push_back(line);
			valid = true;
			string altpanel = line.substr(39, 7);
			if (altpanel == "3089685" || altpanel == "5320407" || altpanel == "3093565" || altpanel == "3093566" || altpanel == "3093571" || altpanel == "3093572" || altpanel == "3093573" || altpanel == "3093574" 
				|| altpanel == "3093710" || altpanel == "3093681" || altpanel == "3093766" || altpanel == "3093767" || altpanel == "3093768" || altpanel == "3093769" || altpanel == "3093770"			
				|| altpanel == "3096782" || altpanel == "5468323") {
				rainscr = true;
			}		
		}
		sub = line.substr(0, mrlength);
		if (sub == metalrainscreen) {
			if (previousSub != sub) {
				lines.push_back(line);
			}
			valid = true;
		}
		sub = line.substr(0, glength);
		if (sub == greyrainscreen) {
			if (previousSub != sub) {
				lines.push_back(line);
			}
			valid = true;
		}
		sub = line.substr(0, wlength);
		if (sub == window) {
			if (previousSub != sub) {
				lines.push_back(line);
			}
			valid = true;
		}
		sub = line.substr(0, wflength);
		if (sub == windowframe) {
			if (previousSub != sub) {
			//	lines.push_back(line);
			}
			frame = true;
			lines.push_back(line);
			valid = true;
		}
		sub = line.substr(0, swlength);
		if (sub == slopedwindow) {
			if (previousSub != sub) {
				lines.push_back(line);
			}
			valid = true;
			string altpanel = line.substr(31, 7);
			if (altpanel == "5523369" || altpanel == "5523371" || altpanel == "5523373" || altpanel == "5523375" || altpanel == "5523363" || altpanel == "5523365" || altpanel == "5523367" || altpanel == "5536279"
				/*|| altpanel == "5523372" || altpanel == "5534676" || altpanel == "5523377" || altpanel == "5523359" || altpanel == "5523361" || altpanel == "5523356" || altpanel == "5523234" || altpanel == "5523232"
				|| altpanel == "5523230" || altpanel == "5523225" || altpanel == "5523223" || altpanel == "5523221" || altpanel == "5523220" || altpanel == "5523218" || altpanel == "5523217" || altpanel == "5523213" 
				|| altpanel == "5523211" || altpanel == "5523208" || altpanel == "3799727" || altpanel == "3799726" || altpanel == "5523353" || altpanel == "3799695" || altpanel == "3799694" || altpanel == "5691030"
				|| altpanel == "5523346" || altpanel == "5523345" || altpanel == "5523344" || altpanel == "5523378" || altpanel == "6777673" || altpanel == "6777674" || altpanel == "6828364" || altpanel == "3833315" 
				|| altpanel == "6777677" || altpanel == "3833317" || altpanel == "7064206" || altpanel == "7064207" || altpanel == "6777681" || altpanel == "7064138" || altpanel == "7064139" || altpanel == "6777684"*/) {
				altpanel1 = true;
			}
		}
		sub = line.substr(0, mlength);
		if (sub == mcladding) {
			if (previousSub != sub) {
				lines.push_back(line);
			}
			valid = true;
		}
		sub = line.substr(0, mwlength);
		if (sub == mainwindow) {
			if (previousSub != sub) {
				lines.push_back(line);
			}
			valid = true;
			mainwin = true;
		}
		sub = line.substr(0, mw2length);
		if (sub == mainwindow2) {
			if (previousSub != sub) {
				lines.push_back(line);
			}
			valid = true;
			mainwin = true;
		}

		int vnum = 0;
		int vtnum = 0;

		previousSub = sub;

		float v3 = 0.0f;
		bool alt = false;

		if (valid) {
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test != "g ") {
					if (test == "v ") {
						vnum++;
						if (rainscr) {
							if (vnum == 37 || vnum == 41 || vnum == 42 || vnum == 45 || vnum == 46 || vnum == 50 || vnum == 51 || vnum == 54) {
							/*	if (vnum == 54) {
									panels << testpanel << endl;
								}*/							
				/*				cout << vnum << " " <<  line << endl;
								system("pause");*/
								sub = line.substr(2);
								float found;
								int i = 0;
								stringstream ss;
								ss << sub;
								string temp;
								while (!ss.eof()) {
									ss >> temp;
									if (stringstream(temp) >> found) {
										vertices[i] = found;
										i++;
									}
									temp = "";
								}

								stringstream ss0;
								stringstream ss1;
								stringstream ss2;

								ss0 << fixed << setprecision(6) << vertices[0];
								ss1 << fixed << setprecision(6) << vertices[1];
								ss2 << fixed << setprecision(6) << vertices[2];

								ss0 >> temp0;
								ss1 >> temp1;
								ss2 >> temp2;

								line = "v " + temp0 + ' ' + temp1 + ' ' + temp2;
								lines.push_back(line);
							}
						}
						else {
							if (altpanel1) {
								if (vnum == 33 || vnum == 34 || vnum == 36 || vnum == 37 || vnum == 39 || vnum == 40 || vnum == 41 || vnum == 42 || vnum == 44 || vnum == 45 || vnum == 47 || vnum == 48) {
									sub = line.substr(2);
									float found;
									int i = 0;
									stringstream ss;
									ss << sub;
									string temp;
									while (!ss.eof()) {
										ss >> temp;
										if (stringstream(temp) >> found) {
											vertices[i] = found;
											i++;
										}
										temp = "";
									}

									stringstream ss0;
									stringstream ss1;
									stringstream ss2;

									ss0 << fixed << setprecision(6) << vertices[0];
									ss1 << fixed << setprecision(6) << vertices[1];
									ss2 << fixed << setprecision(6) << vertices[2];

									ss0 >> temp0;
									ss1 >> temp1;
									ss2 >> temp2;

									line = "v " + temp0 + ' ' + temp1 + ' ' + temp2;

									lines.push_back(line);
								}
							}
							else if (frame) {
							//	if (vnum <= 4 || (vnum >= 19 && vnum <= 22) || (vnum >= 37 && vnum <= 42) || (vnum >= 67 && vnum <= 78) || (vnum >= 93 && vnum <= 96) || (vnum >= 111 && vnum <= 122)) {
								if (vnum <= 2 || (vnum >= 27 && vnum <= 38) || (vnum >= 53 && vnum <= 56) || (vnum >= 71 && vnum <= 82) || (vnum >= 107 && vnum <= 112) || (vnum >= 127 && vnum <= 130) || (vnum >= 145 && vnum <= 148)) {
									sub = line.substr(2);
									float found;
									int i = 0;
									stringstream ss;
									ss << sub;
									string temp;
									while (!ss.eof()) {
										ss >> temp;
										if (stringstream(temp) >> found) {
											vertices[i] = found;
											i++;
										}
										temp = "";
									}

									stringstream ss0;
									stringstream ss1;
									stringstream ss2;

									ss0 << fixed << setprecision(6) << vertices[0];
									ss1 << fixed << setprecision(6) << vertices[1];
									ss2 << fixed << setprecision(6) << vertices[2];

									ss0 >> temp0;
									ss1 >> temp1;
									ss2 >> temp2;

									line = "v " + temp0 + ' ' + temp1 + ' ' + temp2;

									lines.push_back(line);
								}
							}						
							else {
								if ((vnum < 5) || (vnum > 6 && vnum < 11 && !alt) || ((vnum == 7 || vnum == 8 || vnum == 11 || vnum == 12) && alt) || (mainwin == true && (vnum < 5 || vnum == 7 || vnum == 8 || vnum == 11 || vnum == 12
									|| (vnum > 48 && vnum < 54) || vnum == 55 || vnum == 56 || vnum == 59 || vnum == 60 || vnum == 106 || vnum == 107 || vnum == 115 || vnum == 123))) {
									sub = line.substr(2);
									float found;
									int i = 0;
									stringstream ss;
									ss << sub;
									string temp;
									while (!ss.eof()) {
										ss >> temp;
										if (stringstream(temp) >> found) {
											vertices[i] = found;
											i++;
										}
										temp = "";
									}

									if (vnum == 1) {
										v3 = vertices[2];
									}

									if (vnum == 2) {
										if (v3 == vertices[2]) {
											alt = true;
										}
									}

									stringstream ss0;
									stringstream ss1;
									stringstream ss2;

									ss0 << fixed << setprecision(6) << vertices[0];
									ss1 << fixed << setprecision(6) << vertices[1];
									ss2 << fixed << setprecision(6) << vertices[2];

									ss0 >> temp0;
									ss1 >> temp1;
									ss2 >> temp2;

									line = "v " + temp0 + ' ' + temp1 + ' ' + temp2;
									lines.push_back(line);
								}
							}
						}
					}
					if (test == "vt" && rainscr) {
						vtnum++;
						if (vtnum == 37 || vtnum == 41 || vtnum == 42 || vtnum == 45) {
							/*cout << vnum << " " << line << endl;
							system("pause");*/
							lines.push_back(line);
						}
					}
					if (test == "vt" && altpanel1) {
						vtnum++;
						if (vtnum == 33 || vtnum == 34 || vtnum == 36 || vtnum == 37 || vtnum == 39 || vtnum == 40) {
							/*cout << vnum << " " << line << endl;
							system("pause");*/
							lines.push_back(line);
			/*				cout << line << endl;
							system("pause");*/
						}
					}
				}
				else
				{
					break;
				}
			}

			for (auto i : lines) {
				/*cout << i << endl;
				system("pause");*/
				data << i << endl;
			}

			if (rainscr) {
			//	data << "usemtl surface-style-4654430-white-pvc" << endl;
				data << "usemtl surface-style-3731-spandrelpanel_gold" << endl;
				data << "f " << to_string(1 + obCount) << "/" << to_string(1 + tcCount) << "/1 " << to_string(4 + obCount) << "/" << to_string(4 + tcCount) << "/1 " << to_string(3 + obCount) << "/" << to_string(3 + tcCount) << "/1" << endl;
				data << "f " << to_string(1 + obCount) << "/" << to_string(1 + tcCount) << "/1 " << to_string(3 + obCount) << "/" << to_string(3 + tcCount) << "/1 " << to_string(2 + obCount) << "/" << to_string(2 + tcCount) << "/1" << endl;
				data << "f " << to_string(7 + obCount) << "/" << to_string(3 + tcCount) << "/1 " << to_string(5 + obCount) << "/" << to_string(1 + tcCount) << "/1 " << to_string(6 + obCount) << "/" << to_string(2 + tcCount) << "/1" << endl;
				data << "f " << to_string(8 + obCount) << "/" << to_string(4 + tcCount) << "/1 " << to_string(5 + obCount) << "/" << to_string(1 + tcCount) << "/1 " << to_string(7 + obCount) << "/" << to_string(3 + tcCount) << "/1" << endl;
				obCount += 8;
				tcCount += 4;
			}
			else {
				if (altpanel1) {
					data << "usemtl surface-style-3731-spandrelpanel_gold" << endl;
					data << "f " << to_string(3 + obCount) << "/" << to_string(3 + tcCount) << "/1 " << to_string(2 + obCount) << "/" << to_string(2 + tcCount) << "/1 " << to_string(4 + obCount) << "/" << to_string(4 + tcCount) << "/1" << endl;
					data << "f " << to_string(2 + obCount) << "/" << to_string(2 + tcCount) << "/1 " << to_string(6 + obCount) << "/" << to_string(6 + tcCount) << "/1 " << to_string(4 + obCount) << "/" << to_string(4 + tcCount) << "/1" << endl;
					data << "f " << to_string(2 + obCount) << "/" << to_string(2 + tcCount) << "/1 " << to_string(1 + obCount) << "/" << to_string(1 + tcCount) << "/1 " << to_string(6 + obCount) << "/" << to_string(6 + tcCount) << "/1" << endl;
					data << "f " << to_string(2 + obCount) << "/" << to_string(2 + tcCount) << "/1 " << to_string(6 + obCount) << "/" << to_string(6 + tcCount) << "/1 " << to_string(5 + obCount) << "/" << to_string(5 + tcCount) << "/1" << endl;
					data << "f " << to_string(10 + obCount) << "/" << to_string(4 + tcCount) << "/1 " << to_string(8 + obCount) << "/" << to_string(2 + tcCount) << "/1 " << to_string(9 + obCount) << "/" << to_string(3 + tcCount) << "/1" << endl;
					data << "f " << to_string(10 + obCount) << "/" << to_string(4 + tcCount) << "/1 " << to_string(12 + obCount) << "/" << to_string(6 + tcCount) << "/1 " << to_string(8 + obCount) << "/" << to_string(2 + tcCount) << "/1" << endl;
					data << "f " << to_string(12 + obCount) << "/" << to_string(6 + tcCount) << "/1 " << to_string(7 + obCount) << "/" << to_string(1 + tcCount) << "/1 " << to_string(8 + obCount) << "/" << to_string(2 + tcCount) << "/1" << endl;
					data << "f " << to_string(11 + obCount) << "/" << to_string(5 + tcCount) << "/1 " << to_string(12 + obCount) << "/" << to_string(6 + tcCount) << "/1 " << to_string(8 + obCount) << "/" << to_string(2 + tcCount) << "/1" << endl;
					obCount += 12;
					tcCount += 6;
				}
				else if (frame) {
					data << "usemtl surface-style-3731-spandrelpanel_gold" << endl;
					data << "f " << to_string(2 + obCount) << "/1/1 " << to_string(1 + obCount) << "/1/1 " << to_string(31 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(31 + obCount) << "/1/1 " << to_string(32 + obCount) << "/1/1 " << to_string(2 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(4 + obCount) << "/1/1 " << to_string(3 + obCount) << "/1/1 " << to_string(5 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(6 + obCount) << "/1/1 " << to_string(4 + obCount) << "/1/1 " << to_string(5 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(8 + obCount) << "/1/1 " << to_string(7 + obCount) << "/1/1 " << to_string(9 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(10 + obCount) << "/1/1 " << to_string(8 + obCount) << "/1/1 " << to_string(9 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(12 + obCount) << "/1/1 " << to_string(11 + obCount) << "/1/1 " << to_string(13 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(14 + obCount) << "/1/1 " << to_string(12 + obCount) << "/1/1 " << to_string(13 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(13 + obCount) << "/1/1 " << to_string(14 + obCount) << "/1/1 " << to_string(16 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(13 + obCount) << "/1/1 " << to_string(16 + obCount) << "/1/1 " << to_string(15 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(16 + obCount) << "/1/1 " << to_string(15 + obCount) << "/1/1 " << to_string(17 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(18 + obCount) << "/1/1 " << to_string(16 + obCount) << "/1/1 " << to_string(17 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(18 + obCount) << "/1/1 " << to_string(17 + obCount) << "/1/1 " << to_string(20 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(17 + obCount) << "/1/1 " << to_string(19 + obCount) << "/1/1 " << to_string(20 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(20 + obCount) << "/1/1 " << to_string(19 + obCount) << "/1/1 " << to_string(21 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(22 + obCount) << "/1/1 " << to_string(20 + obCount) << "/1/1 " << to_string(21 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(24 + obCount) << "/1/1 " << to_string(23 + obCount) << "/1/1 " << to_string(25 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(26 + obCount) << "/1/1 " << to_string(24 + obCount) << "/1/1 " << to_string(25 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(28 + obCount) << "/1/1 " << to_string(27 + obCount) << "/1/1 " << to_string(29 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(30 + obCount) << "/1/1 " << to_string(28 + obCount) << "/1/1 " << to_string(29 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(34 + obCount) << "/1/1 " << to_string(33 + obCount) << "/1/1 " << to_string(35 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(36 + obCount) << "/1/1 " << to_string(34 + obCount) << "/1/1 " << to_string(35 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(38 + obCount) << "/1/1 " << to_string(37 + obCount) << "/1/1 " << to_string(39 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(40 + obCount) << "/1/1 " << to_string(38 + obCount) << "/1/1 " << to_string(39 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(42 + obCount) << "/1/1 " << to_string(41 + obCount) << "/1/1 " << to_string(43 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(44 + obCount) << "/1/1 " << to_string(42 + obCount) << "/1/1 " << to_string(43 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(40 + obCount) << "/1/1 " << to_string(39 + obCount) << "/1/1 " << to_string(41 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(40 + obCount) << "/1/1 " << to_string(41 + obCount) << "/1/1 " << to_string(42 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(37 + obCount) << "/1/1 " << to_string(38 + obCount) << "/1/1 " << to_string(35 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(38 + obCount) << "/1/1 " << to_string(36 + obCount) << "/1/1 " << to_string(35 + obCount) << "/" << "/1/1" << endl;
					obCount += 44;



					/*data << "f " << to_string(2 + obCount) << "/1/1 " << to_string(1 + obCount) << "/1/1 " << to_string(3 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(4 + obCount) << "/1/1 " << to_string(2 + obCount) << "/1/1 " << to_string(3 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(4 + obCount) << "/1/1 " << to_string(3 + obCount) << "/1/1 " << to_string(6 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(3 + obCount) << "/1/1 " << to_string(5 + obCount) << "/1/1 " << to_string(6 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(6 + obCount) << "/1/1 " << to_string(5 + obCount) << "/1/1 " << to_string(7 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(8 + obCount) << "/1/1 " << to_string(6 + obCount) << "/1/1 " << to_string(7 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(10 + obCount) << "/1/1 " << to_string(9 + obCount) << "/1/1 " << to_string(11 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(12 + obCount) << "/1/1 " << to_string(10 + obCount) << "/1/1 " << to_string(11 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(14 + obCount) << "/1/1 " << to_string(13 + obCount) << "/1/1 " << to_string(2 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(13 + obCount) << "/1/1 " << to_string(1 + obCount) << "/1/1 " << to_string(2 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(9 + obCount) << "/1/1 " << to_string(10 + obCount) << "/1/1 " << to_string(8 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(7 + obCount) << "/1/1 " << to_string(9 + obCount) << "/1/1 " << to_string(8 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(16 + obCount) << "/1/1 " << to_string(15 + obCount) << "/1/1 " << to_string(17 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(18 + obCount) << "/1/1 " << to_string(16 + obCount) << "/1/1 " << to_string(17 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(20 + obCount) << "/1/1 " << to_string(19 + obCount) << "/1/1 " << to_string(21 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(22 + obCount) << "/1/1 " << to_string(20 + obCount) << "/1/1 " << to_string(21 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(24 + obCount) << "/1/1 " << to_string(23 + obCount) << "/1/1 " << to_string(25 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(26 + obCount) << "/1/1 " << to_string(24 + obCount) << "/1/1 " << to_string(25 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(25 + obCount) << "/1/1 " << to_string(27 + obCount) << "/1/1 " << to_string(26 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(26 + obCount) << "/1/1 " << to_string(27 + obCount) << "/1/1 " << to_string(28 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(28 + obCount) << "/1/1 " << to_string(27 + obCount) << "/1/1 " << to_string(29 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(30 + obCount) << "/1/1 " << to_string(28 + obCount) << "/1/1 " << to_string(29 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(29 + obCount) << "/1/1 " << to_string(30 + obCount) << "/1/1 " << to_string(32 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(31 + obCount) << "/1/1 " << to_string(29 + obCount) << "/1/1 " << to_string(32 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(32 + obCount) << "/1/1 " << to_string(31 + obCount) << "/1/1 " << to_string(33 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(34 + obCount) << "/1/1 " << to_string(32 + obCount) << "/1/1 " << to_string(33 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(36 + obCount) << "/1/1 " << to_string(35 + obCount) << "/1/1 " << to_string(37 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(38 + obCount) << "/1/1 " << to_string(36 + obCount) << "/1/1 " << to_string(37 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(40 + obCount) << "/1/1 " << to_string(39 + obCount) << "/1/1 " << to_string(41 + obCount) << "/" << "/1/1" << endl;
					data << "f " << to_string(42 + obCount) << "/1/1 " << to_string(40 + obCount) << "/1/1 " << to_string(41 + obCount) << "/" << "/1/1" << endl;
					obCount += 42;*/
				}
				else {
					//	data << "vn 0 0 1 " << endl;
					//	data << "vn 0 0 -1 " << endl;
					data << "vt 0 1" << endl;
					data << "vt 0 0" << endl;
					data << "vt 1 0" << endl;
					data << "vt 1 1" << endl;
					data << "usemtl surface-style-3731-spandrelpanel_gold" << endl;

					if (mainwin == true) {
						data << "f " << to_string(2 + obCount) << "/4/1 " << to_string(5 + obCount) << "/2/1 " << to_string(3 + obCount) << "/1/1" << endl;
						data << "f " << to_string(2 + obCount) << "/4/1 " << to_string(7 + obCount) << "/3/1 " << to_string(5 + obCount) << "/2/1" << endl;
						//	data << "usemtl surface-style-4654430-white-pvc" << endl;
						data << "f " << to_string(4 + obCount) << "/1/2 " << to_string(6 + obCount) << "/2/2 " << to_string(1 + obCount) << "/4/2" << endl;
						data << "f " << to_string(6 + obCount) << "/1/2 " << to_string(8 + obCount) << "/2/2 " << to_string(1 + obCount) << "/3/2" << endl;

						data << "f " << to_string(19 + obCount) << "/1/2 " << to_string(21 + obCount) << "/3/2 " << to_string(18 + obCount) << "/4/2" << endl;
						data << "f " << to_string(19 + obCount) << "/1/2 " << to_string(20 + obCount) << "/2/2 " << to_string(21 + obCount) << "/3/2" << endl;

						data << "f " << to_string(10 + obCount) << "/1/1 " << to_string(11 + obCount) << "/1/1 " << to_string(12 + obCount) << "/1/1" << endl;
						data << "f " << to_string(10 + obCount) << "/1/1 " << to_string(12 + obCount) << "/1/1 " << to_string(9 + obCount) << "/1/1" << endl;
						data << "f " << to_string(12 + obCount) << "/1/1 " << to_string(13 + obCount) << "/1/1 " << to_string(14 + obCount) << "/1/1" << endl;
						data << "f " << to_string(12 + obCount) << "/1/1 " << to_string(14 + obCount) << "/1/1 " << to_string(15 + obCount) << "/1/1" << endl;
						data << "f " << to_string(14 + obCount) << "/1/1 " << to_string(16 + obCount) << "/1/1 " << to_string(17 + obCount) << "/1/1" << endl;
						data << "f " << to_string(14 + obCount) << "/1/1 " << to_string(17 + obCount) << "/1/1 " << to_string(15 + obCount) << "/1/1" << endl;
						data << "f " << to_string(16 + obCount) << "/1/1 " << to_string(17 + obCount) << "/1/1 " << to_string(16 + obCount) << "/1/1" << endl;
						data << "f " << to_string(16 + obCount) << "/1/1 " << to_string(17 + obCount) << "/1/1 " << to_string(17 + obCount) << "/1/1" << endl;
						obCount += 21;
					}
					else {
						if (alt) {
							data << "f " << to_string(3 + obCount) << "/3/1 " << to_string(1 + obCount) << "/2/1 " << to_string(5 + obCount) << "/1/1" << endl;
							data << "f " << to_string(1 + obCount) << "/4/1 " << to_string(7 + obCount) << "/3/1 " << to_string(5 + obCount) << "/1/1" << endl;
							//	data << "usemtl surface-style-4654430-white-pvc" << endl;
							data << "f " << to_string(6 + obCount) << "/4/2 " << to_string(2 + obCount) << "/1/2 " << to_string(4 + obCount) << "/2/2" << endl;
							data << "f " << to_string(6 + obCount) << "/3/2 " << to_string(8 + obCount) << "/4/2 " << to_string(2 + obCount) << "/2/2" << endl;
						}
						else {
							data << "f " << to_string(4 + obCount) << "/3/1 " << to_string(3 + obCount) << "/2/1 " << to_string(5 + obCount) << "/1/1" << endl;
							data << "f " << to_string(6 + obCount) << "/4/1 " << to_string(4 + obCount) << "/3/1 " << to_string(5 + obCount) << "/1/1" << endl;
							//	data << "usemtl surface-style-4654430-white-pvc" << endl;
							data << "f " << to_string(8 + obCount) << "/4/2 " << to_string(7 + obCount) << "/1/2 " << to_string(1 + obCount) << "/2/2" << endl;
							data << "f " << to_string(2 + obCount) << "/3/2 " << to_string(8 + obCount) << "/4/2 " << to_string(1 + obCount) << "/2/2" << endl;
						}
						obCount += 8;
					}
					tcCount += 4;
				}
			}		
		}
		else {
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test == "v ") {
					vertex++;
				}
				if (test == "g ") {
					break;
				}
			}
			validVertex += vertex;
		}
	}
	data.close();
	obj.close();
}

int div_ceil(int numerator, int denominator)
{
	std::div_t res = std::div(numerator, denominator);
	return res.rem ? (res.quot + 1) : res.quot;
}

void GetDimensions() {
	string objfile1 = "Z:\\IFC Data\\Pathways1Origin.obj";
	ifstream obj(objfile1);
	string line1;
	float minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
	float vert[3];
	int loopNum = 0;
	while (!obj.eof()) {
		
		getline(obj, line1);
		string test = line1.substr(0, 2);
		if (test == "v ") {
			loopNum++;
			string sub = line1.substr(2);
			stringstream ss(sub);
			ss >> vert[0] >> vert[1] >> vert[2];

			if (loopNum == 1) {
				minx = vert[0], maxx = vert[0], miny = vert[1], maxy = vert[1], minz = vert[2], maxz = vert[2];
			}
			else {
				if (vert[0] >= maxx) {
					maxx = vert[0];
				}
				if (vert[0] < minx) {
					minx = vert[0];
				}

				if (vert[1] >= maxy) {
					maxy = vert[1];
				}
				if (vert[1] < miny) {
					miny = vert[1];
				}

				if (vert[2] >= maxz) {
					maxz = vert[2];
				}
				if (vert[2] < minz) {
					minz = vert[2];
				}
			}			
		}
	}
	cout << "Min x = " << minx << endl;
	cout << "Max x = " << maxx << endl;
	cout << "Min y = " << miny << endl;
	cout << "Max y = " << maxy << endl;
	cout << "Min z = " << minz << endl;
	cout << "Max z = " << maxz << endl << endl;

	cout << "Coordinates of centre = (" << (maxx + minx) / 2.0f << ", " << (maxy + miny) / 2.0f << ", " << (maxz + minz) / 2.0f << ")" << endl;
	cout << "Size in x-direction = " << (maxx - minx) << endl;
	cout << "Size in y-direction = " << (maxy - miny) << endl;
	cout << "Size in z-direction = " << (maxz - minz) << endl;
	system("pause");
}

void CheckForErrors() {
	string objfile = "Z:\\USB Data\\InsideDivided\\Test\\1.obj";
	string outfile = "Z:\\USB Data\\InsideDivided\\Errors.txt";

	ifstream obj(objfile);
	ofstream out(outfile);

	string line;
	string test;
	string g;

	int vertex = 0;
	bool exit = false;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			g = line;
		}
		if (test == "v ") {
			vertex++;
		}
		if (test == "f ") {
			test = line.substr(2);
			string line1 = regex_replace(test, std::regex(R"(\/)"), " ");
			stringstream ss;
			ss << line1;
			string temp;
			int found;
			int i = 0;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					if (i == 0 || i == 3 || i == 6) {
						if (found > vertex) {
							out << g << endl;
							out << "Vertex index " + to_string(found) + " is larger than " + to_string(vertex) << endl << endl;						
							exit = true;
							break;
						}
					}
					i++;
				}
				temp = "";
			}
			if (exit)
				break;
		}

	}
	obj.close();
	out.close();
}

void DivideGeometry() {
	float x1 = -40.0f;   //Remember to negate x-coordinates!!!
	float x2 = 48.0f;

	float y1 = -1.0f;
	float y2 = 40.0f;

	float z1 = -40.0f;
	float z2 = 37.0f;

	//float xStepSize = 45.0f;
	//float yStepSize = 30.0f;
	//float zStepSize = 40.0f;

	float xStepSize = 22.0f;
	float yStepSize = 11.0f;
	float zStepSize = 20.0f;

	int xSteps = (int)ceil((x2 - x1) / xStepSize);
	int ySteps = (int)ceil((y2 - y1) / yStepSize);
	int zSteps = (int)ceil((z2 - z1) / zStepSize);

	/*cout << xSteps << endl;
	cout << ySteps << endl;
	cout << zSteps << endl;*/

	int fileNum = 0;

	float minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
	float vert[3];
	int loopNum = 0;
	int loopNumf = 0;

	string objfile = "Z:\\USB Data\\InsideUltra.obj";

	ifstream obj(objfile);

	int numBoxes = xSteps * ySteps * zSteps;

	vector<string> currentObject;
	vector<vector<string>> datafiles; 
	vector<int> vertNormUVIndex(3, 0);
	vector<vector<int>> vertNormUVIndices;

	for (int i = 0; i < numBoxes; i++) {
		datafiles.push_back(currentObject);
		vertNormUVIndices.push_back(vertNormUVIndex);
	}

	vector<int> correctBoxes;

	string line;
	string test = line.substr(0, 2);

	bool repeated = false;

	int vertex = 0;
	int validVertex = 0;
	int texcoord = 0;
	int validTexcoord = 0;
	int normal = 0;
	int validNormal = 0;
	int triangle[9];
	int vertexIndexMin = 0;
	int normalIndexMin = 0;
	int UVIndexMin = 0;

	vector<string> lines;

	while (!obj.eof()) {
		getline(obj, line);
		lines.push_back(line);
	}
	obj.close();

	float progress = 0.0f;
	float prevProgress = 0.0f;
	float invSize = 1.0f / lines.size();
	bool endObject = false;
	bool endFile = false;
	bool exit = false;
	int el = 2;

	do {		
		if (!endObject) {
			el++;
			line = lines[el];
			test = line.substr(0, 2);
			if (test == "v ") {
				vertex++;
				loopNum++;
				string sub = line.substr(2);
				stringstream ss(sub);
				ss >> vert[0] >> vert[1] >> vert[2];

				if (loopNum == 1) {
					minx = vert[0], maxx = vert[0], miny = vert[1], maxy = vert[1], minz = vert[2], maxz = vert[2];
				}
				else {
					if (vert[0] >= maxx) {
						maxx = vert[0];
					}
					if (vert[0] < minx) {
						minx = vert[0];
					}

					if (vert[1] >= maxy) {
						maxy = vert[1];
					}
					if (vert[1] < miny) {
						miny = vert[1];
					}

					if (vert[2] >= maxz) {
						maxz = vert[2];
					}
					if (vert[2] < minz) {
						minz = vert[2];
					}
				}
			}
			if (test == "vt") {
				texcoord++;
			}
			if (test == "vn") {
				normal++;
			}
			if (test == "f ") {
				test = line.substr(2);
				string line1 = regex_replace(test, std::regex(R"(\/)"), " ");
				stringstream ss;
				ss << line1;
				string temp;
				int found;
				int i = 0;
				while (!ss.eof()) {
					loopNumf++;
					ss >> temp;
					if (stringstream(temp) >> found) {
						if (i == 0 || i == 3 || i == 6) {
							if (loopNumf == 1) {
								vertexIndexMin = found;
							}
							else {
								if (found < vertexIndexMin) {
									vertexIndexMin = found;
								}
							}
						}
						if (i == 1 || i == 4 || i == 7) {
							if (loopNumf == 2) {
								UVIndexMin = found;
							}
							else {
								if (found < UVIndexMin) {
									UVIndexMin = found;
								}
							}
						}
						if (i == 2 || i == 5 || i == 8) {
							if (loopNumf == 3) {
								normalIndexMin = found;
							}
							else {
								if (found < normalIndexMin) {
									normalIndexMin = found;
								}
							}
						}
						i++;
					}
					temp = "";
				}
			}

			currentObject.push_back(line);
			
			if (el + 1 < lines.size()) {
				test = lines[el + 1].substr(0, 2);
				if (test == "g ") {
					endObject = true;
				}
			}
			else {
				endObject = true;
				endFile = true;
			}
		}
		else {
			for (int i = 0; i < xSteps; i++) {
				for (int j = 0; j < ySteps; j++) {
					for (int k = 0; k < zSteps; k++) {
						if (((maxx >= x1 + (i * xStepSize) && maxx < x1 + ((i + 1) * xStepSize)) || (minx >= x1 + (i * xStepSize) && minx < x1 + ((i + 1) * xStepSize)) || (minx < x1 + (i * xStepSize) && maxx >= x1 + ((i + 1) * xStepSize))) &&
							((maxy >= y1 + (j * yStepSize) && maxy < y1 + ((j + 1) * yStepSize)) || (miny >= y1 + (j * yStepSize) && miny < y1 + ((j + 1) * yStepSize)) || (miny < y1 + (j * yStepSize) && maxy >= y1 + ((j + 1) * yStepSize))) &&
							((maxz >= z1 + (k * zStepSize) && maxz < z1 + ((k + 1) * zStepSize)) || (minz >= z1 + (k * zStepSize) && minz < z1 + ((k + 1) * zStepSize)) || (minz < z1 + (k * zStepSize) && maxz >= z1 + ((k + 1) * zStepSize)))) {
							correctBoxes.push_back(k + j * zSteps + i * zSteps * ySteps);
						}
					}
				}
			}
			for (int j = 0; j < correctBoxes.size(); j++) {
				for (auto l : currentObject) {
					string linex = l;
					test = l.substr(0, 2);
					if (test == "f ") {
						test = linex.substr(2);
						string line1 = regex_replace(test, std::regex(R"(\/)"), " ");
						stringstream ss;
						ss << line1;
						string temp;
						int found;
						int i = 0;
						while (!ss.eof()) {
							ss >> temp;
							if (stringstream(temp) >> found) {
								if (i == 0 || i == 3 || i == 6) {
									triangle[i] = found + vertNormUVIndices[correctBoxes[j]][0] - vertexIndexMin + 1;
								}
								if (i == 1 || i == 4 || i == 7) {
									triangle[i] = found + vertNormUVIndices[correctBoxes[j]][1] - UVIndexMin + 1;
								}
								if (i == 2 || i == 5 || i == 8) {
									triangle[i] = found + vertNormUVIndices[correctBoxes[j]][2] - normalIndexMin + 1;
								}
								i++;
							}						
							temp = "";
						}
						linex = "f " + to_string(triangle[0]) + '/' + to_string(triangle[1]) + '/' + to_string(triangle[2]) + ' ' + to_string(triangle[3]) + '/' + to_string(triangle[4]) + '/' + to_string(triangle[5]) + ' '
							+ to_string(triangle[6]) + '/' + to_string(triangle[7]) + '/' + to_string(triangle[8]);

					}
					datafiles[correctBoxes[j]].push_back(linex);
				}
				vertNormUVIndices[correctBoxes[j]][0] += vertex;
				vertNormUVIndices[correctBoxes[j]][1] += texcoord;
				vertNormUVIndices[correctBoxes[j]][2] += normal;
			}
			currentObject.clear();
			correctBoxes.clear();
			vertex = 0;
			texcoord = 0;
			normal = 0;
			loopNum = 0;
			loopNumf = 0;
			endObject = false;
			progress = (float)el * invSize;
			if (progress >= prevProgress + 0.05f) {
				cout << "Progress processing file = " + to_string(progress * 100) + "%" << endl;
				prevProgress = progress;
			}			
			if (endFile)
				exit = true;
		}
	} while (!exit);
	
	string line1 = lines[0];
	string line2 = lines[1];

	lines.clear();
	vertNormUVIndices.clear();

	for (int j = 0; j < numBoxes; j++) {
		if (datafiles.size() != 0) {
			string datafile = "Z:\\USB Data\\InsideDivided64\\" + to_string(j + 1) + ".obj";
			ofstream data(datafile);
			data << line1 << endl;
			data << line2 << endl;
			for (auto i : datafiles[j]) {
				data << i << endl;
			}
			data.close();
		}
	}
	
	datafiles.clear(); //TODO Make sure all vectors are cleared at the end of all other functions!
}

void DivideGeometryOld() { //Uses far less RAM than new function, but slower

	float x1 = -40.0f;   //Remember to negate x-coordinates!!!
	float x2 = 48.0f;

	float y1 = -10.0f;
	float y2 = 50.0f;

	float z1 = -40.0f;
	float z2 = 37.0f;

	float xStepSize = 15.0f;
	float yStepSize = 15.0f;
	float zStepSize = 15.0f;

	int xSteps = (int)ceil((x2 - x1) / xStepSize);
	int ySteps = (int)ceil((y2 - y1) / yStepSize);
	int zSteps = (int)ceil((z2 - z1) / zStepSize);

	int fileNum = 0;

	float minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
	float vert[3];
	int loopNum = 0;
	int loopNumf = 0;

	string objfile = "Z:\\USB Data\\InsideUltra.obj";

	ifstream obj(objfile);

	int numBoxes = xSteps * ySteps * zSteps;

	vector<string> currentObject;
	vector<vector<string>> datafiles; // (numBoxes);
	vector<int> vertNormUVIndex(3, 0);
	vector<vector<int>> vertNormUVIndices;

	for (int i = 0; i < numBoxes; i++) {
		datafiles.push_back(currentObject);
		vertNormUVIndices.push_back(vertNormUVIndex);
	}

	vector<int> correctBoxes;

	string line;
	string test = line.substr(0, 2);
	
	bool repeated = false;

	int vertex = 0;
	int validVertex = 0;
	int texcoord = 0;
	int validTexcoord = 0;
	int normal = 0;
	int validNormal = 0;
	int triangle[9];
	int vertexIndexMin = 0;
	int normalIndexMin = 0;
	int UVIndexMin = 0;

	getline(obj, line);
	string xline1 = line;
	getline(obj, line);
	string xline2 = line;

	getline(obj, line);
	test = line.substr(0, 2);

	int g = 0;

	bool lastLine = false;

	while (!obj.eof() || lastLine) {
		if (g != 2) {
			if (test == "g ") {
				g++;
			}
			if (test == "v ") {
				vertex++;
				loopNum++;
				string sub = line.substr(2);
				stringstream ss(sub);
				ss >> vert[0] >> vert[1] >> vert[2];

				if (loopNum == 1) {
					minx = vert[0], maxx = vert[0], miny = vert[1], maxy = vert[1], minz = vert[2], maxz = vert[2];
				}
				else {
					if (vert[0] >= maxx) {
						maxx = vert[0];
					}
					if (vert[0] < minx) {
						minx = vert[0];
					}

					if (vert[1] >= maxy) {
						maxy = vert[1];
					}
					if (vert[1] < miny) {
						miny = vert[1];
					}

					if (vert[2] >= maxz) {
						maxz = vert[2];
					}
					if (vert[2] < minz) {
						minz = vert[2];
					}
				}
			}
			if (test == "vt") {
				texcoord++;
			}
			if (test == "vn") {
				normal++;
			}
			if (test == "f ") {			
				test = line.substr(2);
				string line1 = regex_replace(test, std::regex(R"(\/)"), " ");
				stringstream ss;
				ss << line1;
				string temp;
				int found;
				int i = 0;
				while (!ss.eof()) {
					loopNumf++;
					ss >> temp;
					if (stringstream(temp) >> found) {
						if (i == 0 || i == 3 || i == 6) {
							if (loopNumf == 1) {
								vertexIndexMin = found;
							}
							else {
								if (found < vertexIndexMin) {
									vertexIndexMin = found;
								}
							}			
						}
						if (i == 1 || i == 4 || i == 7) {
							if (loopNumf == 2) {
								UVIndexMin = found;								
							}
							else {
								if (found < UVIndexMin) {
									UVIndexMin = found;
								}
							}
						}
						if (i == 2 || i == 5 || i == 8) {
							if (loopNumf == 3) {
								normalIndexMin = found;
							}
							else {
								if (found < normalIndexMin) {
									normalIndexMin = found;
								}
							}
						}
						i++;
					}
					temp = "";
				}
			}

			currentObject.push_back(line);
			getline(obj, line);
			test = line.substr(0, 2);

			if (obj.eof() == true) {
				lastLine = true;
				g++;
			}

			if (test == "g ") {
				g++;
			}
		}
		else {
			lastLine = false;
			for (int i = 0; i < xSteps; i++) {
				for (int j = 0; j < ySteps; j++) {
					for (int k = 0; k < zSteps; k++) {
						if (((maxx >= x1 + (i * xStepSize) && maxx < x1 + ((i + 1) * xStepSize)) || (minx >= x1 + (i * xStepSize) && minx < x1 + ((i + 1) * xStepSize)) || (minx < x1 + (i * xStepSize) && maxx >= x1 + ((i + 1) * xStepSize))) &&   
							((maxy >= y1 + (j * yStepSize) && maxy < y1 + ((j + 1) * yStepSize)) || (miny >= y1 + (j * yStepSize) && miny < y1 + ((j + 1) * yStepSize)) || (miny < y1 + (j * yStepSize) && maxy >= y1 + ((j + 1) * yStepSize))) &&
							((maxz >= z1 + (k * zStepSize) && maxz < z1 + ((k + 1) * zStepSize)) || (minz >= z1 + (k * zStepSize) && minz < z1 + ((k + 1) * zStepSize)) || (minz < z1 + (k * zStepSize) && maxz >= z1 + ((k + 1) * zStepSize)))) {
							correctBoxes.push_back(k + j * zSteps + i * zSteps * ySteps);
						}
					}
				}
			}
			
			for (int j = 0; j < correctBoxes.size(); j++) {
				for (auto l : currentObject) {
					string linex = l;
					test = l.substr(0, 2);
					if (test == "f ") {
						test = linex.substr(2);
						string line1 = regex_replace(test, std::regex(R"(\/)"), " ");
						stringstream ss;
						ss << line1;
						string temp;
						int found;
						int i = 0;
						while (!ss.eof()) {
							ss >> temp;
							if (stringstream(temp) >> found) {
								if (i == 0 || i == 3 || i == 6) {
									triangle[i] = found + vertNormUVIndices[correctBoxes[j]][0] - vertexIndexMin + 1;
								}
								if (i == 1 || i == 4 || i == 7) {
									triangle[i] = found + vertNormUVIndices[correctBoxes[j]][1] - UVIndexMin + 1;
								}
								if (i == 2 || i == 5 || i == 8) {
									triangle[i] = found + vertNormUVIndices[correctBoxes[j]][2] - normalIndexMin + 1;
								}
								i++;
							}
							temp = "";
						}
						linex = "f " + to_string(triangle[0]) + '/' + to_string(triangle[1]) + '/' + to_string(triangle[2]) + ' ' + to_string(triangle[3]) + '/' + to_string(triangle[4]) + '/' + to_string(triangle[5]) + ' '
							+ to_string(triangle[6]) + '/' + to_string(triangle[7]) + '/' + to_string(triangle[8]);						
					}
					datafiles[correctBoxes[j]].push_back(linex);
				}				
				vertNormUVIndices[correctBoxes[j]][0] += vertex;
				vertNormUVIndices[correctBoxes[j]][1] += texcoord;
				vertNormUVIndices[correctBoxes[j]][2] += normal;
			}
			currentObject.clear();
			correctBoxes.clear();		
			vertex = 0;			
			texcoord = 0;
			normal = 0;		
			loopNum = 0;
			loopNumf = 0;
			g = 0;
		}
	}
	obj.close();

	for (int j = 0; j < numBoxes; j++) {
		if (datafiles.size() != 0) {
			string datafile = "Z:\\USB Data\\InsideDivided\\" + to_string(j + 1) + ".obj";
			ofstream data(datafile);
			data << xline1 << endl;
			data << xline2 << endl;
			for (auto i : datafiles[j]) {
				data << i << endl;
			}
			data.close();
		}
	}
	datafiles.clear(); //TODO Make sure all vectors are cleared at the end of all other functions!
	vertNormUVIndices.clear();
}

void PlaceAtOrigin() {
	/*string objfile = "Z:\\IFC Data\\InsideBest1.obj";
	string datafile = "Z:\\IFC Data\\InsideBest1AtOriginn.obj";*/

	/*string objfile = "Z:\\IFC Data\\Pathways.obj";
	string datafile = "Z:\\IFC Data\\PathwaysOrigin.obj";*/

	string objfile = "Z:\\USB Data\\InsideCompleteRotated.obj";
	string datafile = "Z:\\USB Data\\InsideCompleteRotatedOrigin.obj";
	string transformFile = "Z:\\USB Data\\InsideCompleteRotatedOrigin.txt";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;

	int vertex = 0;
	int validVertex = 0;
	float triangle[3];
	string a = " ";
	string test = line.substr(0, 2);
	string sub;
	vector<string> lines;

	float x1 = 0.0f;
	float x2 = 0.0f;

	float y1 = 0.0f;
	float y2 = 0.0f;

	float z1 = 0.0f;
	float z2 = 0.0f;

	bool first = true;

	while (!obj.eof()) {
		getline(obj, line);
		lines.push_back(line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					triangle[i] = found;
					i++;
				}
				temp = "";
			}
			if (first) {
				x1 = triangle[0];
				x2 = triangle[0];

				y1 = triangle[1];
				y2 = triangle[1];

				z1 = triangle[2];
				z2 = triangle[2];
				first = false;
			}
			else {
				if (triangle[0] < x1) {
					x1 = triangle[0];
				}
				if (triangle[0] > x2) {
					x2 = triangle[0];
				}

				if (triangle[1] < y1) {
					y1 = triangle[1];
				}
				if (triangle[1] > y2) {
					y2 = triangle[1];
				}

				if (triangle[2] < z1) {
					z1 = triangle[2];
				}
				if (triangle[2] > z2) {
					z2 = triangle[2];
				}
			}
		}
	}
		
	float midx = (x1 + x2) / 2.0f;
	float midy = (y1 + y2) / 2.0f;
	float midz = (z1 + z2) / 2.0f;

	for (auto i : lines) {
		string replace = i.substr(0, 2);
		if (replace == "v ") {
			sub = i.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					triangle[i] = found;
					i++;
				}
				temp = "";
			}
			sub = "v " + to_string(triangle[0] - midx) + " " + to_string(triangle[1] - midy) + " " + to_string(triangle[2] - midz);
			data << sub << endl;		
		}
		else {
			data << i << endl;
		}
	}

	ofstream tran(transformFile);
	tran << to_string(midx) << endl;
	tran << to_string(midy) << endl;
	tran << to_string(midz) << endl;

	tran.close();
	data.close();
	obj.close();
}

void CommaDelim() {
	string x;
	string objfile;
	string line;

	objfile = "Z:\\IFC Data\\Output\\Outside\\Window.obj";
	string datafile = "Z:\\IFC Data\\Output\\Outside\\Window.txt";

	ifstream obj(objfile);
	ofstream data(datafile);

	/*while (!obj.eof()) {
		getline(obj, line);
		string test = line.substr(0, 1);
		std::size_t found = line.find("<");
		if (found > line.length())
		{
			cout << line << endl;
			system("pause");
		}
	}

	data << line << endl;
	getline(obj, line);
	data << line << endl;*/

	int vertex = 0;
	int validVertex = 0;
	float triangle[3];
	string a = " ";
	getline(obj, line);
	string test = line.substr(0, 2);
	string sub;
	vector<string> lines;

	float x1 = 0.0f;
	float x2 = 0.0f;

	float y1 = 0.0f;
	float y2 = 0.0f;

	float z1 = 0.0f;
	float z2 = 0.0f;

	bool first = true;

	while (!obj.eof()) {
		getline(obj, line);
		lines.push_back(line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					triangle[i] = found;
					i++;
				}
				temp = "";
			}
			if (first) {
				x1 = triangle[0];
				x2 = triangle[0];

				y1 = triangle[1];
				y2 = triangle[1];

				z1 = triangle[2];
				z2 = triangle[2];
				first = false;
			}
			else {
				if (triangle[0] < x1) {
					x1 = triangle[0];
				}
				if (triangle[0] > x2) {
					x2 = triangle[0];
				}

				if (triangle[1] < y1) {
					y1 = triangle[1];
				}
				if (triangle[1] > y2) {
					y2 = triangle[1];
				}

				if (triangle[2] < z1) {
					z1 = triangle[2];
				}
				if (triangle[2] > z2) {
					z2 = triangle[2];
				}
			}
		}
	}

	float midx = (x1 + x2) / 2.0f;
	float midy = (y1 + y2) / 2.0f;
	float midz = (z1 + z2) / 2.0f;
	int vert = 0;
	for (auto i : lines) {
		string replace = i.substr(0, 2);
		if (replace == "v ") {
			vert++;
			sub = i.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					triangle[i] = found;
					i++;
				}
				temp = "";
			}
			sub = to_string(vert) + "," + to_string(triangle[0] - midx) + "," + to_string(triangle[1] - midy) + "," + to_string(triangle[2] - midz);
			data << sub << endl;
		}

	}


	data.close();
	obj.close();
}

void Removeg() {
	string objfile = "Z:\\USB Data\\InsideDivided\\1.obj";
	string datafile = "Z:\\USB Data\\InsideDivided\\1Nog.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);

	bool first = true;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test != "g ") {
			data << line << endl;
		}
		else {
			if (first) {
				data << line << endl;
				first = false;
			}
		}
	}
}

void RemovegBatchProcess() {
	string objdir = "Z:\\USB Data\\InsideDivided27\\";

	string line;
	string test;

	bool first = true;

	int numFiles = GetNumOfFiles(objdir);

	for (int i = 1; i <= numFiles; i++) {
		string objfile = objdir + to_string(i) + ".obj";
		string outfile = objdir + to_string(i) + "Nog.obj";
		if (_access_s(objfile.c_str(), 0) == 0) { //True if file exists
			ifstream obj(objfile);
			ofstream out(outfile);
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test != "g ") {
					out << line << endl;
				}
				else {
					if (first) {
						out << line << endl;
						first = false;
					}
				}
			}
		}
	}
}

void Removemtl() {
	string objfile = "Z:\\USB Data\\CombinedTest.obj";
	string datafile = "Z:\\USB Data\\CombinedTestNoMTL.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);

	bool first = true;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test != "us") {
			data << line << endl;
		}
		else {
			if (first) {
				data << line << endl;
				first = false;
			}
		}
	}
}

void FindParticularObject() {
	string x;
	string objfile;
	string line;

	objfile = "Z:\\IFC Data\\Inside.obj";
	string datafile = "Z:\\IFC Data\\ListOfDefaultObjects.txt";

	ifstream obj(objfile);
	ofstream data(datafile);

	string test = line.substr(0, 2);

	bool first = true;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			if (line.length() <= 2) {
				data << line << endl;
			}		
		}
	}
}

void Removen() {
	string objfile = "Z:\\USB Data\\Inside\\InsideOrderedNog.obj";
	string datafile = "Z:\\USB Data\\Inside\\InsideOrderedNogNoNormals.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test != "vn") {
			data << line << endl;
		}
	}
}

void Removetc() {
	string objfile = "Z:\\USB Data\\Inside\\InsideOrderedNogNoNormals.obj";
	string datafile = "Z:\\USB Data\\Inside\\InsideOrderedNogNoNormalsNoTCs.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test != "vt") {
			data << line << endl;
		}
	}
}

void Replacegwitho() {
	string x;
	string objfile;
	string line;

	objfile = "Z:\\IFC Data\\Structure.obj";
	string datafile = "Z:\\IFC Data\\StructureChild.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string test = line.substr(0, 2);

	bool first = true;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test != "g ") {
			data << line << endl;
		}
		else {
			if (first) {
				data << line << endl;
				first = false;
			}
			else {
				line = "o " + line.substr(2);
				data << line << endl;
			}
		}
	}
}

void SplitFiles() {
	string objfile = "Z:\\USB Data\\PipeworkCompleteRotatedTranslated.obj";

	ifstream obj(objfile);

	vector<vector<string>> datafiles(1000);

	int gtype = 0;

	string line;
	string test = line.substr(0, 2);
	vector<string> preGs;
	bool repeated = false;

	int vertex = 0;
	int validVertex = 0;
	int texcoord = 0;
	int validTexcoord = 0;
	int normal = 0;
	int validNormal = 0;
	string a = " ";
	int triangle[9];

	getline(obj, line);
	string xline1 = line;
	getline(obj, line);
	string xline2 = line;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test != "g ") {
			if (test == "v ") {
				vertex++;
			}
			if (test == "vt") {
				texcoord++;
			}
			if (test == "vn") {
				normal++;
			}
			if (test == "f ") {
				test = line.substr(2);
				string line1 = regex_replace(test, std::regex(R"(\/)"), a);
				stringstream ss;
				ss << line1;
				string temp;
				int found;
				int i = 0;
				while (!ss.eof()) {
					ss >> temp;
					if (stringstream(temp) >> found) {
						if (i == 0 || i == 3 || i == 6) {
							triangle[i] = found - validVertex;
						}
						if (i == 1 || i == 4 || i == 7) {
							triangle[i] = found - validTexcoord;
						}
						if (i == 2 || i == 5 || i == 8) {
							triangle[i] = found - validNormal;
						}
						i++;
					}
					temp = "";
				}
				line = "f " + to_string(triangle[0]) + '/' + to_string(triangle[1]) + '/' + to_string(triangle[2]) + ' ' + to_string(triangle[3]) + '/' + to_string(triangle[4]) + '/' + to_string(triangle[5]) + ' '
					        + to_string(triangle[6]) + '/' + to_string(triangle[7]) + '/' + to_string(triangle[8]);
			}
			datafiles[gtype].push_back(line);		
		}
		else {
			validVertex += vertex;
			vertex = 0;
			validTexcoord += texcoord;		
			texcoord = 0;
			validNormal += normal;
			normal = 0;
			gtype = 0;
			test = line.substr(0, 20);
			for (auto i : preGs) {			
				if (test == i) {
					repeated = true;
					break;
				}	
				gtype++;
			}
			if (!repeated) {
				datafiles[gtype].push_back(line);
				preGs.push_back(test);
			}
			else {
				datafiles[gtype].push_back(line);  //To add back g for every object
				repeated = false;
			}			
		}
	}

	for (int j = 0; j < datafiles.size(); j++) {
		if (datafiles[j].size() != 0) {
			string datafile = "Z:\\USB Data\\Pipework\\" + to_string(j + 1) + ".obj";
			ofstream data(datafile);
			vertex = 0;
			validVertex = 0;
			texcoord = 0;
			validTexcoord = 0;
			normal = 0;
			validNormal = 0;
			data << xline1 << endl;
			data << xline2 << endl;
			for (auto i : datafiles[j]) {
				test = i.substr(0, 2);
				if (test != "s ") {
					if (test == "v ") {
						vertex++;
					}
					if (test == "vt") {
						texcoord++;
					}
					if (test == "vn") {
						normal++;
					}
					if (test == "f ") {
						test = i.substr(2);
						string line1 = regex_replace(test, std::regex(R"(\/)"), a);
						stringstream ss;
						ss << line1;
						string temp;
						int found;
						int i = 0;
						while (!ss.eof()) {
							ss >> temp;
							if (stringstream(temp) >> found) {
								if (i == 0 || i == 3 || i == 6) {
									triangle[i] = found + validVertex;
								}
								if (i == 1 || i == 4 || i == 7) {
									triangle[i] = found + validTexcoord;
								}
								if (i == 2 || i == 5 || i == 8) {
									triangle[i] = found + validNormal;
								}
								i++;
							}
							temp = "";
						}
						line = "f " + to_string(triangle[0]) + '/' + to_string(triangle[1]) + '/' + to_string(triangle[2]) + ' ' + to_string(triangle[3]) + '/' + to_string(triangle[4]) + '/' + to_string(triangle[5]) + ' '
							+ to_string(triangle[6]) + '/' + to_string(triangle[7]) + '/' + to_string(triangle[8]);
						data << line << endl;
					}
					else {
						data << i << endl;
					}
				}
				else {
					validVertex += vertex;
					vertex = 0;
					validTexcoord += texcoord;
					texcoord = 0;
					validNormal += normal;
					normal = 0;
					data << i << endl;
				}				
			}
		}		
	}
}

void CombineOBJs() {
	string objfile1 = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated1.obj";
	string objfile2 = "Z:\\USB Data\\InsideSupportsCompleteRotatedTranslated1.obj";
	string outfile = "Z:\\USB Data\\CombinedTest.obj";

	ifstream obj1(objfile1);
	ifstream obj2(objfile2);
	ofstream out(outfile);

	string line;
	string test;
	
	int vertex = 0;
	int texcoord = 0;
	int normal = 0;

	int triangle[9];

	while (!obj1.eof()) {
		getline(obj1, line);
		test = line.substr(0, 2);
		if (test == "mt") {
			line = "mtllib USB.mtl";
		}
		if (test == "v ") {
			vertex++;
		}
		if (test == "vt") {
			texcoord++;
		}
		if (test == "vn") {
			normal++;
		}
		if (line != "") {
			out << line << endl;
		}	
	}
	obj1.close();

	getline(obj2, line);
	getline(obj2, line);

	while (!obj2.eof()) {
		getline(obj2, line);
		test = line.substr(0, 2);
		
		if (test == "f ") {
			test = line.substr(2);
			string line1 = regex_replace(test, std::regex(R"(\/)"), " ");
			stringstream ss;
			ss << line1;
			string temp;
			int found;
			int i = 0;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					if (i == 0 || i == 3 || i == 6) {
						triangle[i] = found + vertex;
					}
					if (i == 1 || i == 4 || i == 7) {
						triangle[i] = found + normal;
					}
					if (i == 2 || i == 5 || i == 8) {
						triangle[i] = found + texcoord;
					}
					i++;
				}
				temp = "";
			}
			line = "f " + to_string(triangle[0]) + '/' + to_string(triangle[1]) + '/' + to_string(triangle[2]) + ' ' + to_string(triangle[3]) + '/' + to_string(triangle[4]) + '/' + to_string(triangle[5]) + ' '
				+ to_string(triangle[6]) + '/' + to_string(triangle[7]) + '/' + to_string(triangle[8]);
		}
		if (line != "") {
			out << line << endl;
		}
	}
	out.close();	
	obj2.close();
}

void DeleteObject2() {
	string line;

	string objfile = "Z:\\IFC Data\\Insideno\\59.obj";
	string datafile = "Z:\\IFC Data\\Insideno\\Test.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	vector<string> lines;

	while (!obj.eof()) {
		getline(obj, line);
		lines.push_back(line);
	}

	string extraneousPart = "usemtl IfcOpeningElement";
	int length = (int)extraneousPart.length();

	int lineNum = 0;

	for (auto it = lines.begin(); it != lines.end(); )
	{
		if ((*it) == extraneousPart && lineNum < 5) {
			lineNum++;
			it = lines.erase(it, it + 13);
		}		
		else
			++it;
	}

	for (auto i : lines) {
		data << i << endl;
	}

	data.close();
	obj.close();
}

void Reconciliation() {
	string line;
	string test;

//	string objdir = "Z:\IFC Data\\Objects\\";
//	string objdir = "Z:\IFC Data\\Insideno\\";
//	string datafile = "Z:\\IFC Data\\Objects\\Reconcile1.obj";
//	string datafile = "Z:\\IFC Data\\Insideno\\Reconcile.obj";

//	string objdir = "Z:\\IFC Data\\Pathways\\";
//	string datafile = "Z:\\IFC Data\\Pathways\\Pathways.obj";

	//string objdir = "Z:\\USB Data\\Inside\\";
	//string datafile = "Z:\\USB Data\\Inside\\InsideOrdered.obj";

	//string objdir = "Z:\\USB Data\\Pipework\\Useful\\";
	//string datafile = "Z:\\USB Data\\Pipework\\Useful\\PipeworkOrdered.obj";

	string objdir = "Z:\\USB Data\\Outside\\";
	string datafile = "Z:\\USB Data\\Outside\\OutsideOrderedLogo.obj";

	ofstream data(datafile);

	int numFiles = GetNumOfFiles(objdir);
	bool first = true;
	int triangle[9];
	string a = " ";
	int vertex = 0;
	int validVertex = 0;
	int texcoord = 0;
	int validTexcoord = 0;
	int normal = 0;
	int validNormal = 0;
	
	for (int i = 1; i <= numFiles; i++) { 
		vertex = 0;
		texcoord = 0;
		normal = 0;
		string objfile = objdir + to_string(i) + ".obj";
		if (_access_s(objfile.c_str(), 0) == 0) { //True if file exists
			ifstream obj(objfile);
			if (first) {
				getline(obj, line);
				data << line << endl;
				getline(obj, line);
				data << line << endl;
				first = false;
			}
			else {
				getline(obj, line);
				getline(obj, line);
			}
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test == "v ") {
					vertex++;
				}
				if (test == "vt") {
					texcoord++;
				}
				if (test == "vn") {
					normal++;
				}
				if (test == "f ") {
					string replace = line.substr(1);
					string line1 = regex_replace(replace, std::regex(R"(\/)"), a);
					stringstream ss;
					ss << line1;
					string temp;
					int found;
					int i = 0;
					while (!ss.eof()) {
						ss >> temp;
						if (stringstream(temp) >> found) {
							if (i == 0 || i == 3 || i == 6) {
								triangle[i] = found + validVertex;
							}
							if (i == 1 || i == 4 || i == 7) {
								triangle[i] = found + validTexcoord;
							}
							if (i == 2 || i == 5 || i == 8) {
								triangle[i] = found + validNormal;
							}
							i++;
						}
						temp = "";
					}
					data << "f " << triangle[0] << '/' << triangle[1] << '/' << triangle[2] << ' '
						<< triangle[3] << '/' << triangle[4] << '/' << triangle[5] << ' '
						<< triangle[6] << '/' << triangle[7] << '/' << triangle[8] << endl;
				}
				else {
					data << line << endl;
				}
			}
			validVertex += vertex;
			validTexcoord += texcoord;
			validNormal += normal;
		}
	}
}

void ReconciliationGroupg() {
	string line;
	string test;

	string objdir = "Z:\\USB Data\\Inside\\";
	string datafile = "Z:\\USB Data\\Inside\\InsideOrderedGroupedg.obj";

	ofstream data(datafile);

	int numFiles = GetNumOfFiles(objdir);
	bool first = true;
	bool firstg = true;
	int triangle[9];
	string a = " ";
	int vertex = 0;
	int validVertex = 0;
	int texcoord = 0;
	int validTexcoord = 0;
	int normal = 0;
	int validNormal = 0;

	for (int i = 1; i <= numFiles; i++) {
		vertex = 0;
		texcoord = 0;
		normal = 0;
		firstg = true;
		string objfile = objdir + to_string(i) + ".obj";
		if (_access_s(objfile.c_str(), 0) == 0) { //True if file exists
			ifstream obj(objfile);
			if (first) {
				getline(obj, line);
				data << line << endl;
				getline(obj, line);
				data << line << endl;
				first = false;
			}
			else {
				getline(obj, line);
				getline(obj, line);
			}
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test == "g ") {
					if (firstg) {
						firstg = false;
					}
					else {
						continue;
					}
				}
				if (test == "v ") {
					vertex++;
				}
				if (test == "vt") {
					texcoord++;
				}
				if (test == "vn") {
					normal++;
				}
				if (test == "f ") {
					string replace = line.substr(1);
					string line1 = regex_replace(replace, std::regex(R"(\/)"), a);
					stringstream ss;
					ss << line1;
					string temp;
					int found;
					int i = 0;
					while (!ss.eof()) {
						ss >> temp;
						if (stringstream(temp) >> found) {
							if (i == 0 || i == 3 || i == 6) {
								triangle[i] = found + validVertex;
							}
							if (i == 1 || i == 4 || i == 7) {
								triangle[i] = found + validTexcoord;
							}
							if (i == 2 || i == 5 || i == 8) {
								triangle[i] = found + validNormal;
							}
							i++;
						}
						temp = "";
					}
					data << "f " << triangle[0] << '/' << triangle[1] << '/' << triangle[2] << ' '
						<< triangle[3] << '/' << triangle[4] << '/' << triangle[5] << ' '
						<< triangle[6] << '/' << triangle[7] << '/' << triangle[8] << endl;
				}
				else {
					data << line << endl;
				}
			}
			validVertex += vertex;
			validTexcoord += texcoord;
			validNormal += normal;
		}
	}
}

void Rotate90() {
	//string objfile = "Z:\\IFC Data\\PathwaysOrigin.obj";
	//string datafile = "Z:\\IFC Data\\PathwaysOriginRotate.obj";

	string objfile = "Z:\\IFC Data\\Lighting.obj";
	string datafile = "Z:\\USB Data\\LightingRotated.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);
	string sub;

	float vert[3];
	float normal[3];

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					vert[i] = found;
					i++;
				}
				temp = "";
			}
			sub = "v " + to_string(vert[0]) + " " + to_string(vert[2]) + " " + to_string(-vert[1]);
			data << sub << endl;
		}
		else if (test == "vn") {
			sub = line.substr(3);
			float found;
			int i = 0;
			stringstream ss;
			ss << fixed << setprecision(3) << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					if (abs(found) < 0.000001f) {
						found = abs(found);
					}
					normal[i] = found;
					i++;
				}
				temp = "";
			}
			if (abs(normal[1]) < 0.000001f) {
				sub = "vn " + to_string(normal[0]) + " " + to_string(normal[2]) + " " + to_string(normal[1]);
			}
			else {
				sub = "vn " + to_string(normal[0]) + " " + to_string(normal[2]) + " " + to_string(-normal[1]);
			}			
			data << sub << endl;
		}
		else {
			data << line << endl;
		}
	}
}

void ScaleTranslate() {
	string x;
	string objfile;
	string line;

	objfile = "Z:\\IFC Data\\InsideSupportsRotatedTranslated1.obj";
	string datafile = "Z:\\IFC Data\\InsideSupportsRotatedTranslated2.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string test = line.substr(0, 2);
	string sub;

	float vert[3];

	float Scale[3] = { 1.0f, 1.0f, 1.0f };
	float Translate[3] = { 0.0f, -0.07f, 0.0f };

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					vert[i] = found;
					i++;
				}
				temp = "";
			}
			sub = "v " + to_string(Scale[0] * (vert[0] - Translate[0])) + " " + to_string(Scale[1] * (vert[1] + Translate[1])) + " " + to_string(Scale[2] * (vert[2] + Translate[2]));
			data << sub << endl;
		}
		else {
			data << line << endl;
		}
	}
}

void Translate() {
	//string objfile = "Z:\\IFC Data\\InsideSupportsRotatedTranslated1.obj";
	//string datafile = "Z:\\IFC Data\\InsideSupportsRotatedTranslated2.obj";

	//string objfile = "Z:\\IFC Data\\PathwaysUltra3.obj";
	//string datafile = "Z:\\IFC Data\\PathwaysUltra4.obj";

	/*string objfile = "Z:\\IFC Data\\OutsideUltra2.obj";
	string datafile = "Z:\\IFC Data\\OutsideUltra3.obj";*/

	//string objfile = "Z:\\USB Data\\LightingRotated.obj";
	//string datafile = "Z:\\USB Data\\LightingRotatedTranslated.obj";

	//string objfile = "Z:\\USB Data\\OutsideCompleteRotatedOrigin.obj";
	//string datafile = "Z:\\USB Data\\OutsideCompleteRotatedTranslated1.obj";

	string objfile = "Z:\\USB Data\\PathwaysCompleteRotatedOrigin.obj";
	string datafile = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated1.obj";

	//string objfile = "Z:\\USB Data\\InsideSupportsCompleteRotatedOrigin.obj";
	//string datafile = "Z:\\USB Data\\InsideSupportsCompleteRotatedTranslated1.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);
	string sub;

	float vert[3];

//	float Translate[3] = { 0.0f, 15.5f, 0.509811f }; //Outside
//	float Translate[3] = { -0.227f, 10.02f, -0.883f }; //InsideSupports
//	float Translate[3] = { -0.38f, 17.74f, 0.519f }; //Outside
	float Translate[3] = { 2.255f, 10.516f, -33.755f }; //Pathways
//	float Translate[3] = { 30.35f / 1.1f, 29.39f / 1.1f, 30.433f / 1.1f }; //Pipework
//	float Translate[3] = {197.07f / 1.1f, 17.12f / 1.1f, 192.459f / 1.1f }; //Lighting

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					vert[i] = found;
					i++;
				}
				temp = "";
			}
			sub = "v " + to_string(vert[0] - Translate[0]) + " " + to_string(vert[1] + Translate[1]) + " " + to_string(vert[2] + Translate[2]);
			data << sub << endl;
		}
		else {
			data << line << endl;
		}
	}
}

void TranslateObject() {
	string object = "g WAR_NewcastleLitterBin:WAR_NewcastleLitterBin:798431";

	string objfile = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated5.obj";
	string datafile = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated6.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);
	string sub;

	float vert[3];

	float Translate[3] = { 0.0f, -0.704f, 0.0f };

	bool match = false;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			if (line == object) {
				match = true;
			}
			else {
				match = false;
			}
		}
		if (test == "v " && match) {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					vert[i] = found;
					i++;
				}
				temp = "";
			}
			sub = "v " + to_string(vert[0] - Translate[0]) + " " + to_string(vert[1] + Translate[1]) + " " + to_string(vert[2] + Translate[2]);
			data << sub << endl;
		}
		else {
			data << line << endl;
		}
	}
}

void RotateScaleTranslate() {
	/*string objfile = "Z:\\IFC Data\\InsideSupportsAtOrigin.obj";
	string datafile = "Z:\\IFC Data\\InsideSupportsRotatedTranslated.obj";*/

	string objfile = "Z:\\IFC Data\\PipeworkComplete.obj";
	string datafile = "Z:\\USB Data\\PipeworkCompleteRotatedTranslated.obj";

	ofstream data(datafile);

	string line;
	string test;
	string sub;

	ifstream obj(objfile);

	float vert[3];
	float normal[3];

	/*float Scale[3] = { 100.0f, 100.0f, 100.0f };
	float Translate[3] = { 134.6f, 12.3f, -1.5f };*/

//	float Scale[3] = { 100.0f, 100.0f, 100.0f };

	float Scale[3] = { 1.0f, 1.0f, 1.0f };

	float Translate[3] = { 30.35f / 1.1f, 29.39f / 1.1f, 30.433f / 1.1f }; //Pipework
//	float Translate[3] = { 0.0f, 16.6f, 0.0f }; //Inside
//	float Translate[3] = { -0.227f, -5.42f + 16.6f, -1.392f }; //InsideSupports
//	float Translate[3] = { -0.24f, 2.25f + 16.6f, -0.02f }; //Outside
//	float Translate[3] = { 2.2f, -13.75f + 16.6f, -34.29f }; //Pathways

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << fixed << setprecision(6) << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					vert[i] = found;
					i++;
				}
				temp = "";
			}
			sub = "v " + to_string(vert[0] - Translate[0]) + " " + to_string(vert[2] + Translate[1]) + " " + to_string(-vert[1] + Translate[2]);
	//		sub = "v " + to_string(Scale[0] * (vert[0] - midx) + midx - Translate[0]) + " " + to_string(Scale[1] * (vert[2] - midy) + midy + Translate[1]) + " " + to_string(Scale[2] * (-vert[1] - midz) + midz + Translate[2]);
			data << sub << endl;
		}
		else if (test == "vn") {
			sub = line.substr(3);
			float found;
			int i = 0;
			stringstream ss;
			ss << fixed << setprecision(3) << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					if (abs(found) < 0.000001f) {
						found = abs(found);
					}
					normal[i] = found;
					i++;
				}
				temp = "";
			}
			sub = "vn " + to_string(normal[0]) + " " + to_string(normal[2]) + " " + to_string(-normal[1]);
			data << sub << endl;
		}
		else {
			data << line << endl;
		}
	}
}

void TestNormals() {
	string x;
	string objfile;
	string line;

	objfile = "Z:\\IFC Data\\Outside\\Reconcile.obj";
	string datafile = "Z:\\IFC Data\\Outside\\OutsideFixedTexCoords.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string test = line.substr(0, 2);
	string sub;

	float normal[3];

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "vn") {
			sub = line.substr(3);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					normal[i] = found;
					i++;
				}
				temp = "";
			}
			if (normal[0] > 0.0f && normal[0] < 0.01f) {
				cout << normal[0] << endl;
			}
			if (normal[1] > 0.0f && normal[1] < 0.01f) {
				cout << normal[1] << endl;
			}
			if (normal[2] > 0.0f && normal[2] < 0.01f) {
				cout << normal[2] << endl;
			}
			if (normal[0] > 100.0f) {
				cout << normal[0] << endl;
			}
			if (normal[1] > 100.0f) {
				cout << normal[1] << endl;
			}
			if (normal[2] > 100.0f) {
				cout << normal[2] << endl;
			}

		}
	}
}

void FixTexCoords() {
	string objfile = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated1.obj";
	string datafile = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated1UV.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test;
	string sub;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "vt") {
			sub = line.substr(3);
			string space = " ";
			size_t pos = sub.find(space);
			string tca = sub.substr(0, pos);
			string tcb = sub.substr(pos + 1);

			stringstream linea;
			stringstream lineb;

			double dlinea = ::atof(tca.c_str());
			double dlineb = ::atof(tcb.c_str());

			if (dlinea > 1000.0f) {
				dlinea = dlinea - 424120.0f;
			}

			if (dlineb > 1000.0f) {
				dlineb = dlineb - 564404.0f;
			}

			linea << fixed << setprecision(4) << dlinea;
			linea >> tca;

			lineb << fixed << setprecision(4) << dlineb;
			lineb >> tcb;

			line = "vt " + tca + " " + tcb;

		}
		data << line << endl;
	}
	data.close();
	obj.close();
}

void DeleteObjectsHelperFunction(bool valid, ifstream& obj, ofstream& data, string& line, int& validVertex, int& validTexcoord, int& validNormal, vector<string>& lines) {
	int vertex = 0;
	int texcoord = 0;
	int normal = 0;
	string test;
	if (valid) {
		while (!obj.eof()) {
			getline(obj, line);
			test = line.substr(0, 2);
			if (test != "g ") {
				lines.push_back(line);
			}
			else
			{
				break;
			}
		}
		string a = " ";
		int triangle[9];
		for (auto i : lines) {
			string replace = i.substr(0, 1);
			if (replace == "f") {
				string line1 = regex_replace(i, std::regex(R"(\/)"), a);
				stringstream ss;
				ss << line1;
				string temp;
				int found;
				int i = 0;
				while (!ss.eof()) {
					ss >> temp;
					if (stringstream(temp) >> found) {
						if (i == 0 || i == 3 || i == 6) {
							triangle[i] = found - validVertex;
						}
						if (i == 1 || i == 4 || i == 7) {
							triangle[i] = found - validTexcoord;
						}
						if (i == 2 || i == 5 || i == 8) {
							triangle[i] = found - validNormal;
						}
						i++;
					}
					temp = "";
				}
				data << "f " << triangle[0] << '/' << triangle[1] << '/' << triangle[2] << ' '
					<< triangle[3] << '/' << triangle[4] << '/' << triangle[5] << ' '
					<< triangle[6] << '/' << triangle[7] << '/' << triangle[8] << endl;
			}
			else {
				data << i << endl;
			}
		}
	}
	else {
		while (!obj.eof()) {
			getline(obj, line);
			test = line.substr(0, 2);
			if (test == "v ") {
				vertex++;
			}
			if (test == "vt") {
				texcoord++;
			}
			if (test == "vn") {
				normal++;
			}
			if (test == "g ") {
				break;
			}
		}
		validVertex += vertex;
		validTexcoord += texcoord;
		validNormal += normal;
	}
}

void DeleteSingleObject() {
	string deleteThis = "g ";
	int length = (int)deleteThis.length();

	string objfile = "Z:\\IFC Data\\PathwaysRotatedTranslated1.obj";
	string datafile = "Z:\\IFC Data\\PathwaysRotatedTranslated2.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	getline(obj, line);

	string sub1;
	vector<string> lines;

	int validVertex = 0;
	int validTexcoord = 0;
	int validNormal = 0;

	while (!obj.eof()) {
		lines.clear();
		bool valid = false;
		sub1 = line.substr(0, length);
		if (line.length() > 2 && sub1 == "g ") {
			lines.push_back(line);
			valid = true;
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);
	}
	data.close();
	obj.close();
}

void DeleteObjectsInside() {
	string deleteThis1 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9698101";
	string deleteThis2 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9697663";
	string deleteThis3 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9697501";
	string deleteThis4 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9681236";
	string deleteThis5 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9695929";
	string deleteThis6 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9695813";
	string deleteThis7 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9715905";
	string deleteThis8 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9695700";
	string deleteThis9 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9695516";
	string deleteThis10 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9708359";
	string deleteThis11 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:5543180";
	string deleteThis12 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9697211";
	string deleteThis13 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9696285";
	string deleteThis14 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9710479";
	string deleteThis15 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9694880";
	string deleteThis16 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9694323";
	string deleteThis17 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:5157456";
	string deleteThis18 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9735082";
	string deleteThis19 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9736349";
	string deleteThis20 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9711195";
	string deleteThis21 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9711138";
	string deleteThis22 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9711034";
	string deleteThis23 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9697857";
	string deleteThis24 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11442180";
	string deleteThis25 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11427691";
	string deleteThis26 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11031864";
	string deleteThis27 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11032146";
	string deleteThis28 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11032118";
	string deleteThis29 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11032974";

	string deleteThis30 = "g Basic Wall:A 25-15-35 M ExtWall 166:9650395";
	string deleteThis31 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11035132";
	string deleteThis32 = "g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:11078769";

	string deleteThis33 = "g Floor:RB_Floor Build up_01_90mm Heated screed-210mm total:12358600:";

	string deleteThis34 = "g Floor:RB_Floor Build Up_07a - RAF medium duty:12259692:3";
	string deleteThis35 = "g 25-50-20-135 Fire Curtain:Fireguard_SC120:12086224";
	string deleteThis36 = "g 25-50-20-135 Fire Curtain:Fireguard_SC120:12086224:1";
	string deleteThis37 = "g Floor:Trench Heater - 112mm:12598978:11";
	string deleteThis38 = "g Sliding_Stacking_Panel_Partition:DT-17:8292025";
	string deleteThis39 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8447898";
	string deleteThis40 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8447929";
	string deleteThis41 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8759571";
	string deleteThis42 = "g 1499_Furn_CoffeeCart:1499_Furn_CoffeeCart:7432262";
	string deleteThis43 = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:22";
	string deleteThis44 = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:23";
	string deleteThis45 = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:15";
	string deleteThis46 = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:17";
	string deleteThis47 = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:18";
	string deleteThis48 = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:4";
	string deleteThis49 = "g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:6";
	string deleteThis50 = "g Floor:RB_Floor Build up_05_110mm Screed-260mm total:18996928";
	string deleteThis51 = "g Basic Wall:RB-3d-sts-122thk-twin-50dB-60FR-4600mh-Sev-50_ins:11008079";
	string deleteThis52 = "g NBS_ProfabAccessLtd_AccessPanels_Profab4000-SingleDoor:IAP-01 500x2000mm:16739564";

	int length = (int)deleteThis33.length();

	string objfile = "Z:\\IFC Data\\InsideBest2RotatedTranslated.obj";
	string datafile = "Z:\\IFC Data\\InsideBest3RotatedTranslated.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	getline(obj, line);

	string sub1;
	vector<string> lines;

	int validVertex = 0;
	int validTexcoord = 0;
	int validNormal = 0;

	while (!obj.eof()) {
		lines.clear();
		bool valid = false;
		sub1 = line.substr(0, length);
		if (line != deleteThis1 && line != deleteThis2 && line != deleteThis3 && line != deleteThis4 && line != deleteThis5 && line != deleteThis6 && line != deleteThis7 && line != deleteThis8 && line != deleteThis9 &&
			line != deleteThis10 && line != deleteThis11 && line != deleteThis12 && line != deleteThis13 && line != deleteThis14 && line != deleteThis15 && line != deleteThis16 && line != deleteThis17 && line != deleteThis18 &&
			line != deleteThis19 && line != deleteThis20 && line != deleteThis21 && line != deleteThis22 && line != deleteThis23 && line != deleteThis24 && line != deleteThis25 && line != deleteThis26 && line != deleteThis27 &&
			line != deleteThis28 && line != deleteThis29 && line != deleteThis30 && line != deleteThis31 && line != deleteThis32 && sub1 != deleteThis33 &&
			line != deleteThis34 && line != deleteThis35 && line != deleteThis36 && line != deleteThis37 && line != deleteThis38 && line != deleteThis39 && line != deleteThis40 && line != deleteThis41 &&
			line != deleteThis42 && line != deleteThis43 && line != deleteThis44 && line != deleteThis45 && line != deleteThis46 && line != deleteThis47 && line != deleteThis48 &&
			line != deleteThis49 && line != deleteThis50 && line != deleteThis51 && line != deleteThis52) {
			lines.push_back(line);
			valid = true;
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);		
	}
	data.close();
	obj.close();
}

void DeleteObjectsInsideSupports() {
	string deleteThis1 = "g Floor:300 Thick RC slab:719528:2";
	string deleteThis2 = "g Floor:300 Thick RC slab:719948:2";
	string deleteThis3 = "g Floor:300 Thick Post Tension Slab:716762:2";
	string deleteThis4 = "g RC Pile:";

	int length = (int)deleteThis4.length();

	string objfile = "Z:\\IFC Data\\InsideSupportsRotatedTranslated.obj";
	string datafile = "Z:\\IFC Data\\InsideSupportsRotatedTranslated1.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	getline(obj, line);

	string sub1;
	vector<string> lines;

	int validVertex = 0;
	int validTexcoord = 0;
	int validNormal = 0;

	while (!obj.eof()) {
		lines.clear();
		bool valid = false;
		sub1 = line.substr(0, length);

		if (line != deleteThis1 && line != deleteThis2 && line != deleteThis3 && sub1 != deleteThis4) {
			lines.push_back(line);
			valid = true;
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);
	}
	data.close();
	obj.close();
}

void DeleteObjectsPathways() {
	//string deleteThis1 = "g Floor:Pr_25_93_60_58_M_Type_6-Limestone-Carlow-Blue:725349";
	//string deleteThis2 = "g Floor:Pr_25_93_60_58_M_Type_5-Limestone-Carlow-Blue:725179";
	//string deleteThis3 = "g Floor:Pr_25_93_60_58_M_Type_5-Limestone-Carlow-Blue:725919";
	//string deleteThis4 = "g Floor:Pr_25_93_60_58_M_Type_5-Limestone-Carlow-Blue:726116";
	//string deleteThis5 = "g Floor:Pr_25_93_60_58_M_Type_6-Limestone-Carlow-Blue:726271";
	string deleteThis6 = "g AR_Plant_Tree1:WAR_LiquidambarStyraciflua:731878";
	string deleteThis7 = "g AR_Plant_Tree1:WAR_LiquidambarStyraciflua:732616";
	string deleteThis8 = "g AR_Plant_Tree1:WAR_LiquidambarStyraciflua:732627";
	string deleteThis9 = "g Floor:Floor-Existing_Planting-425_Grvl-450_Soil-100_Mlch:728267";
	string deleteThis10 = "g Floor:Floor-Existing_Planting-425_Grvl-450_Soil-100_Mlch:728237";
	string deleteThis11 = "g Floor:Floor-Existing_Planting-425_Grvl-450_Soil-100_Mlch:728795";

//	int length = (int)deleteThis.length();

	string objfile = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated1.obj";
	string datafile = "Z:\\USB Data\\PathwaysCompleteRotatedTranslated2.obj";
	
	ifstream obj(objfile);
	ofstream data(datafile);

	string line;

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	getline(obj, line);
	
	string sub1;
	vector<string> lines;

	int validVertex = 0;
	int validTexcoord = 0;
	int validNormal = 0;

	while (!obj.eof()) {
		lines.clear();
		bool valid = false;
	//	sub1 = line.substr(0, length);

		if ( line != deleteThis6 && line != deleteThis7 && line != deleteThis8 && line != deleteThis9
			&& line != deleteThis10 && line != deleteThis11) {
			lines.push_back(line);
			valid = true;
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);
	}
	data.close();
	obj.close();
}

void DeleteObjectsOutside() {
	string deleteThis1 = "g Gutter Upstand North:Gutter Upstand North:11249608:1";

//	int length = (int)deleteThis.length();

	string objfile = "Z:\\USB Data\\OutsideCompleteRotatedTranslated1.obj";
	string datafile = "Z:\\USB Data\\OutsideUltra.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	getline(obj, line);

	string sub1;
	vector<string> lines;

	int validVertex = 0;
	int validTexcoord = 0;
	int validNormal = 0;

	while (!obj.eof()) {
		lines.clear();
		bool valid = false;
//		sub1 = line.substr(0, length);

		if (line != deleteThis1) {
			lines.push_back(line);
			valid = true;
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);
	}
	data.close();
	obj.close();
}

void DeleteObjectsInsideExtra() {
	//string deleteThis1 = "g Basic Wall:RB-07e- IWL double board-117mm thk-no ins-6000 max ht:11088817";
	//string deleteThis2 = "g Floor:Trench Heater - 112mm:12598978:12";
	//string deleteThis3 = "g Floor:Trench Heater - 112mm:12598978:13";
	//string deleteThis4 = "g Basic Wall:A 25-15-35 M ExtWall 62:9704080";
	//string deleteThis5 = "g Basic Wall:A 25-15-35 M ExtWall 216:9744301";
	//string deleteThis6 = "g Basic Wall:A 25-15-35 M ExtWall 216:9730346";
	//string deleteThis7 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486507";
	//string deleteThis8 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486818";
	//string deleteThis9 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486761";
	//string deleteThis10 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486708";
	//string deleteThis11 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486599";
	//string deleteThis12 = "g Basic Wall:RB-07b-25-85-45-150 ExtWall IWL 92mm Stud 2 boards + ins:11078769";

	//string deleteThis1 = "g Glazed Internal Single Doors:";
	//string deleteThis2 = "g Glazed Internal Sliding Door:";
	//string deleteThis3 = "g HB_Door_Concept_Int_Dbl_Solid";
	//string deleteThis4 = "g HB_Door_Concept_Int_Sgl_Solid";
	//string deleteThis5 = "g Glazed Internal Double Doors:";
	//string deleteThis6 = "g HB_WC_Cubicle_FrontOnly:3888 Width 900 Door:";

	string deleteThis1 = "g 25-50-20-135 Fire Curtain:Fireguard_SC120:12086224";
	string deleteThis2 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8447898";
	string deleteThis3 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8447929";
	string deleteThis4 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8759571";
	string deleteThis5 = "g 1499_Furn_CoffeeCart:1499_Furn_CoffeeCart:7432262";
	string deleteThis6 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486507";
	string deleteThis7 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486818";
	string deleteThis8 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486761";
	string deleteThis9 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486708";
	string deleteThis10 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486599";
	string deleteThis11 = "g Basic Roof:HKB_Roof__Entrance Canopy:19043512";
	string deleteThis12 = "g Sliding_Stacking_Panel_Partition:DT-17:8292025";

	int length1 = (int)deleteThis1.length();
	int length2 = (int)deleteThis2.length();
	int length3 = (int)deleteThis3.length();
	int length4 = (int)deleteThis4.length();
	int length5 = (int)deleteThis5.length();
	int length6 = (int)deleteThis6.length();

	string objfile = "Z:\\USB Data\\InsideCompleteRotatedTranslated2.obj";
	string datafile = "Z:\\USB Data\\InsideUltra.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	getline(obj, line);

	string sub1;
	string sub2;
	string sub3;
	string sub4;
	string sub5;
	string sub6;
	vector<string> lines;

	int validVertex = 0;
	int validTexcoord = 0;
	int validNormal = 0;

	while (!obj.eof()) {
		lines.clear();
		bool valid = false;
		sub1 = line.substr(0, length1);
		sub2 = line.substr(0, length2);
		sub3 = line.substr(0, length3);
		sub4 = line.substr(0, length4);
		sub5 = line.substr(0, length5);
		sub6 = line.substr(0, length6);
//		if (sub1 != deleteThis1 && sub2 != deleteThis2 && sub3 != deleteThis3 && sub4 != deleteThis4 && sub5 != deleteThis5 && sub6 != deleteThis6) {
		if (line != deleteThis1 && line != deleteThis2 && line != deleteThis3 && line != deleteThis4 && line != deleteThis5 && line != deleteThis6 &&
			line != deleteThis7 && line != deleteThis8 && line != deleteThis9 && line != deleteThis10 && line != deleteThis11 && line != deleteThis12) {
			lines.push_back(line);
			valid = true;
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);
	}
	data.close();
	obj.close();
}

void Listg() {
	string objfile = "Z:\\USB Data\\InsideCompleteRotatedTranslated1.obj";
	string datafile = "Z:\\USB Data\\InsideCompleteObjects.txt";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			data << line << endl;
		}
	}
}

void Materialscount() {
	string mtlfile = "Z:\\IFC Data\\PathwaysComplete.mtl";

	ifstream mtl(mtlfile);

	string line;
	string test;

	int mtlnum = 0;

	while (!mtl.eof()) {
		getline(mtl, line);
		test = line.substr(0, 6);
		if (test == "newmtl") {
			mtlnum++;
		}
	}
	cout << "Number of materials: " << mtlnum << endl;
}

void Objectscount() {
	string objfile = "Z:\\IFC Data\\OutsideComplete.obj";

	ifstream obj(objfile);

	string line;
	string test;

	int objnum = 0;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			objnum++;
		}
	}
	cout << "Number of objects: " << objnum << endl;
}

int main() {
	string x;
	int s;
	do {
		cout << "                                                 OBJ Editor\n";
		cout << "********************************************************************************************************************\n";
		cout << "Please select an option:\n";
		cout << "====================================================================================================================\n";
		cout << "1. Divide geometry\n";
		cout << "2. Place at origin\n";
		cout << "3. Write individual file\n";
		cout << "4. Improve efficiency\n";
		cout << "5. Output comma-delimited vertices\n";
		cout << "6. Remove g\n";
		cout << "7. Delete objects from Inside\n";
		cout << "8. Rotate 90 degrees\n";
		cout << "9. Scale and translate\n";
		cout << "10. Rotate, scale and translate\n";
		cout << "11. Reconciliation\n";		
		cout << "12. Fix texture coordinates\n";
		cout << "13. Test normals\n";
		cout << "14. Replace g with o\n";
		cout << "15. Remove normals\n";
		cout << "16. Remove texture coordinates\n";
		cout << "17. Get dimensions\n";
		cout << "18. Find all g with default\n";
		cout << "19. Delete single object\n";
		cout << "20. Delete objects from InsideSupports\n";
		cout << "21. Delete objects from Pathways\n";
		cout << "22. Delete objects from Outside\n";
		cout << "23. Delete extra objects from Inside\n";
		cout << "24. Translate everything in file\n";
		cout << "25. List g\n";
		cout << "26. Split files\n";
		cout << "27. Reconciliation with grouped g\n";
		cout << "28. Translate single object in file\n";
		cout << "29. Remove MTL\n";
		cout << "30. Combine OBJ's\n";
		cout << "31. Check for errors\n";
		cout << "32. Remove g with batch process\n";
		cout << "33. Count materials\n";
		cout << "34. Count objects\n";
		cout << "35. Terminate the program\n";
		cout << "********************************************************************************************************************\n";
		cin >> x;
		fixInput(x, s, 1, 35, "Invalid input! Please enter an integer from the above menu: ");

		switch (s)
		{
		case 1:
			system("cls");
			DivideGeometry();
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			try {
				PlaceAtOrigin();
			}
			catch (const invalid_argument& iae) {
				cout << "Unable to read data. " << iae.what() << "\n";
			}
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			try {
				writeIndividualFile();
			}
			catch (const invalid_argument& iae) {
				cout << "Unable to read data. " << iae.what() << "\n";
			}
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			try {
				ImproveEfficiency();
			}
			catch (const invalid_argument& iae) {
				cout << "Unable to read data. " << iae.what() << "\n";
			}
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
			CommaDelim();
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");
			Removeg();
			system("pause");
			system("cls");
			break;
		case 7:
			system("cls");
			DeleteObjectsInside();
			system("pause");
			system("cls");
			break;
		case 8:
			system("cls");
			Rotate90();
			system("pause");
			system("cls");
			break;
		case 9:
			system("cls");
			ScaleTranslate();
			system("pause");
			system("cls");
			break;
		case 10:
			system("cls");
			RotateScaleTranslate();
			system("pause");
			system("cls");
			break;
		case 11:
			system("cls");
			Reconciliation();
			system("pause");
			system("cls");
			break;
		case 12:
			system("cls");
			FixTexCoords();
			system("pause");
			system("cls");
			break;
		case 13:
			system("cls");
			TestNormals();
			system("pause");
			system("cls");
			break;
		case 14:
			system("cls");
			Replacegwitho();
			system("pause");
			system("cls");
			break;
		case 15:
			system("cls");
			Removen();
			system("pause");
			system("cls");
			break;	
		case 16:
			system("cls");
			Removetc();
			system("pause");
			system("cls");
			break;
		case 17:
			system("cls");
			GetDimensions();
			system("pause");
			system("cls");
			break;
		case 18:
			system("cls");
			FindParticularObject();
			system("pause");
			system("cls");
			break;	
		case 19:
			system("cls");
			DeleteSingleObject();
			system("pause");
			system("cls");
			break;
		case 20:
			system("cls");
			DeleteObjectsInsideSupports();
			system("pause");
			system("cls");
			break;
		case 21:
			system("cls");
			DeleteObjectsPathways();
			system("pause");
			system("cls");
			break;	
		case 22:
			system("cls");
			DeleteObjectsOutside();
			system("pause");
			system("cls");
			break;
		case 23:
			system("cls");
			DeleteObjectsInsideExtra();
			system("pause");
			system("cls");
			break;			
		case 24:
			system("cls");
			Translate();
			system("pause");
			system("cls");
			break;	
		case 25:
			system("cls");
			Listg();
			system("pause");
			system("cls");
			break;
		case 26:
			system("cls");
			SplitFiles();
			system("pause");
			system("cls");
			break;
		case 27:
			system("cls");
			ReconciliationGroupg();
			system("pause");
			system("cls");
			break;
		case 28:
			system("cls");
			TranslateObject();
			system("pause");
			system("cls");
			break;
		case 29:
			system("cls");
			Removemtl();
			system("pause");
			system("cls");
			break;
		case 30:
			system("cls");
			CombineOBJs();
			system("pause");
			system("cls");
			break;
		case 31:
			system("cls");		
			CheckForErrors();
			system("pause");
			system("cls");
			break;
		case 32:
			system("cls");
			RemovegBatchProcess();
			system("pause");
			system("cls");
			break;	
		case 33:
			system("cls");
			Materialscount();
			system("pause");
			system("cls");
			break;
		case 34:
			system("cls");
			Objectscount();
			system("pause");
			system("cls");
			break;
		case 35:
			break;
		}  //No default case is required due to the above fixInput function
	} while (s != 35);
	return 0;
}