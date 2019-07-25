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
#include <map>		  //To map new indices to old
#include <future>     //To enable multi-threading

using namespace std;

void createFolder(string dir) {
	DWORD x = GetFileAttributesA(dir.c_str());
	if (x == INVALID_FILE_ATTRIBUTES) { //Determines whether folder already exists
		_mkdir(dir.c_str());
	}
}

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
	//	string item = "g Glazed Internal Double Timber Doors:DT-22:";
	//	string item = "g Glazed Internal Double Sliding Door:";
	//	string item = "g Glazed Internal Single Doors:";
	//  string item = "g Glazed Internal Double Doors:";
	//	string item = "g HB_WC_Cubicle_FrontOnly:";

	//	string item = "g External signage2:External signage:4747993";

	//	string item = "g Basic Roof:20-50-30-180_Reinforced_Bitumen_Membrane_Inverted_Roof_Covering_System (500 x 200mm  Paving):2324097:1";

	string item = "g HB_Door_Concept_Int_Sgl_Solid_VP - DT-03:1010x2110mm RB DT 03c:9941156";


	int length = (int)item.length();
	/*
	string objfile = "Z:\\IFC Data\\Inside\\InsideOrdered.obj";
	string datafile = "Z:\\IFC Data\\Inside\\Doors\\gHB_WC_Cubicle_FrontOnly.obj";*/
	string objfile = "Z:\\IFC Data\\Inside\\Doors\\gHB_Door_Concept_Int_Dbl_Solid.obj";
	string datafile = "Z:\\IFC Data\\Inside\\Doors\\DiningDoor.obj";

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
	data.close();
	obj.close();
}

void MoveObjectToIndividualOBJ() {
	bool allInstances = false;
	string item = "g _Timber:";

	int length = (int)item.length();

	string objfile = "Z:\\IFC Data\\InsideSupports\\InsideSupportsOrderedOld.obj";
	string outfile1 = "Z:\\IFC Data\\InsideSupports\\InsideSupportsOrderedOldNew.obj";
	string outfile2 = "Z:\\IFC Data\\InsideSupports\\Timber.obj";

	ifstream obj(objfile);
	ofstream out1(outfile1);
	ofstream out2(outfile2);

	string line;

	getline(obj, line);
	out1 << line << endl;
	out2 << line << endl;
	getline(obj, line);
	out1 << line << endl;
	out2 << line << endl;

	int vertex = 0;
	int validVertex = 0;
	int texcoord = 0;
	int validTexcoord = 0;
	int normal = 0;
	int validNormal = 0;

	int validVertexSource = 0;
	int validTexcoordSource = 0;
	int validNormalSource = 0;

	int triangle[9];
	string a = " ";
	getline(obj, line);
	string test;
	string sub;
	vector<string> lines;
	bool finished = false;

	while (!obj.eof()) {
		vertex = 0;
		texcoord = 0;
		normal = 0;
		lines.clear();
		lines.push_back(line);
		bool valid = false;
		sub = line.substr(0, length);
		if (sub == item) {
			valid = true;
		}

		if (valid && !finished) {
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
			validVertexSource += vertex;
			validTexcoordSource += texcoord;
			validNormalSource += normal;

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
					out2 << "f " << triangle[0] << '/' << triangle[1] << '/' << triangle[2] << ' '
						<< triangle[3] << '/' << triangle[4] << '/' << triangle[5] << ' '
						<< triangle[6] << '/' << triangle[7] << '/' << triangle[8] << endl;
				}
				else {
					if (i != "") {
						out2 << i << endl;
					}
				}
			}
			if (!allInstances) {
				finished = true;
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
				lines.push_back(line);
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
								triangle[i] = found - validVertexSource;
							}
							if (i == 1 || i == 4 || i == 7) {
								triangle[i] = found - validTexcoordSource;
							}
							if (i == 2 || i == 5 || i == 8) {
								triangle[i] = found - validNormalSource;
							}
							i++;
						}
						temp = "";
					}
					out1 << "f " << triangle[0] << '/' << triangle[1] << '/' << triangle[2] << ' '
						<< triangle[3] << '/' << triangle[4] << '/' << triangle[5] << ' '
						<< triangle[6] << '/' << triangle[7] << '/' << triangle[8] << endl;
				}
				else {
					if (i != "") {
						out1 << i << endl;
					}
				}
			}
			validVertex += vertex;
			validTexcoord += texcoord;
			validNormal += normal;
		}
	}
	out1.close();
	out2.close();
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
	string objfile1 = "Z:\\IFC Data\\Inside\\Doors\\DiningDoorOrigin.obj";
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
	bool writeNotInBoxOBJ = true;
	string objfile = "Z:\\IFC Data\\Inside\\Separated\\RoomContents.obj";

	ifstream obj(objfile);

	vector<float> box;
	vector<vector<float>> boxes;

	box = { 16.77f, 37.23f, -1.05f, 7.18f, -31.05f, -7.86f };
	boxes.push_back(box);

	box = { 16.77f, 37.23f, 7.20f, 10.83f, -31.05f, -7.86f };
	boxes.push_back(box);

	box = { 16.77f, 37.23f, 11.3f, 14.85f, -31.05f, -7.86f };
	boxes.push_back(box);

	box = { 16.77f, 37.23f, 15.3f, 18.86f, -31.05f, -7.86f };
	boxes.push_back(box);

	box = { 16.77f, 37.23f, 19.3f, 22.86f, -31.05f, -7.86f };
	boxes.push_back(box);

	box = { 16.77f, 37.23f, 23.3f, 26.86f, -31.05f, -7.86f };
	boxes.push_back(box);

	box = { 16.77f, 37.23f, 27.3f, 30.86f, -31.05f, -7.86f };
	boxes.push_back(box);



	box = { -7.86f, 15.5f, -1.05f, 7.18f, -33.18f, -15.36f };
	boxes.push_back(box);

	box = { -7.86f, 15.5f, 7.20f, 10.83f, -33.18f, -15.36f };
	boxes.push_back(box);

	box = { -7.86f, 15.5f, 11.3f, 14.85f, -33.18f, -15.36f };
	boxes.push_back(box);

	box = { -7.86f, 15.5f, 15.3f, 18.86f, -33.18f, -15.36f };
	boxes.push_back(box);

	box = { -7.86f, 15.5f, 19.3f, 22.86f, -33.18f, -15.36f };
	boxes.push_back(box);

	box = { -7.86f, 15.5f, 23.3f, 26.86f, -33.18f, -15.36f };
	boxes.push_back(box);

	box = { -7.86f, 15.5f, 27.3f, 30.86f, -33.18f, -15.36f };
	boxes.push_back(box);



	box = { -34.32f, -14.95f, -1.05f, 7.18f, -34.36f, -1.09f };
	boxes.push_back(box);

	box = { -34.32f, -14.95f, 7.20f, 10.83f, -34.36f, -1.09f };
	boxes.push_back(box);

	box = { -34.32f, -14.95f, 11.3f, 14.85f, -34.36f, -1.09f };
	boxes.push_back(box);

	box = { -34.32f, -14.95f, 15.3f, 18.86f, -34.36f, -1.09f };
	boxes.push_back(box);

	box = { -34.32f, -14.95f, 19.3f, 22.86f, -34.36f, -1.09f };
	boxes.push_back(box);

	box = { -33.59f, -7.9f, 23.3f, 26.86f, -35.2f, -17.37f };
	boxes.push_back(box);

	box = { -33.59f, -7.9f, 27.3f, 30.86f, -35.2f, -17.37f };
	boxes.push_back(box);



	box = { -37.45f, -16.36f, -1.05f, 7.18f, -0.64f, 32.73f };
	boxes.push_back(box);

	box = { -37.45f, -16.36f, 7.20f, 10.83f, -0.64f, 32.73f };
	boxes.push_back(box);

	box = { -37.45f, -16.36f, 11.3f, 14.85f, -0.64f, 32.73f };
	boxes.push_back(box);

	box = { -37.45f, -16.36f, 15.3f, 18.86f, -0.64f, 32.73f };
	boxes.push_back(box);

	box = { -37.45f, -16.36f, 19.3f, 22.86f, -0.64f, 32.73f };
	boxes.push_back(box);



	//box = { -40.0f, 0.0f, -1.0f, 20.0f, 0.0f, 37.0f };
	//boxes.push_back(box);

	//box = { -40.0f, 0.0f, 20.0f, 40.0f, -40.0f, 0.0f };
	//boxes.push_back(box);

	//box = { -40.0f, 0.0f, 20.0f, 40.0f, 0.0f, 37.0f };
	//boxes.push_back(box);

	//box = { 0.0f, 48.0f, -1.0f, 20.0f, -40.0f, 0.0f };
	//boxes.push_back(box);

	//box = { 0.0f, 48.0f, -1.0f, 20.0f, 0.0f, 37.0f };
	//boxes.push_back(box);

	//box = { 0.0f, 48.0f, 20.0f, 40.0f, -40.0f, 0.0f };
	//boxes.push_back(box);

	//box = { 0.0f, 48.0f, 20.0f, 40.0f, 0.0f, 37.0f };
	//boxes.push_back(box);


	float minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
	float vert[3];
	int loopNum = 0;
	int loopNumf = 0;

	int numBoxes = (int)boxes.size();

	if (writeNotInBoxOBJ) {
		numBoxes++;
	}

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
	string test;

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
			int boxNum = 0;
			bool inBox = false;
			for (auto l : boxes) {
				if (((maxx >= l[0] && maxx < l[1]) || (minx >= l[0] && minx < l[1]) || (minx < l[0] && maxx >= l[1])) &&
					((maxy >= l[2] && maxy < l[3]) || (miny >= l[2] && miny < l[3]) || (miny < l[2] && maxy >= l[3])) &&
					((maxz >= l[4] && maxz < l[5]) || (minz >= l[4] && minz < l[5]) || (minz < l[4] && maxz >= l[5]))) {
					correctBoxes.push_back(boxNum);
					inBox = true;
				}
				boxNum++;
			}
			if (writeNotInBoxOBJ && !inBox) {
				correctBoxes.push_back(numBoxes - 1);
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
			string datafile = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\";;
			if (j != numBoxes - 1 || !writeNotInBoxOBJ) {
				datafile += to_string(j + 1) + ".obj";
			}
			else {
				datafile += "NotInBox.obj";
			}
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

void DivideGeometrySteps() {
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

	float xMin, xMax, yMin, yMax, zMin, zMax;

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
						xMin = x1 + (i * xStepSize);
						xMax = x1 + ((i + 1) * xStepSize);

						yMin = y1 + (j * yStepSize);
						yMax = y1 + ((j + 1) * yStepSize);

						zMin = z1 + (k * zStepSize);
						zMax = z1 + ((k + 1) * zStepSize);

						if (((maxx >= xMin && maxx < xMax) || (minx >= xMin && minx < xMax) || (minx < xMin && maxx >= xMax)) &&
							((maxy >= yMin && maxy < yMax) || (miny >= yMin && miny < yMax) || (miny < yMin && maxy >= yMax)) &&
							((maxz >= zMin && maxz < zMax) || (minz >= zMin && minz < zMax) || (minz < zMin && maxz >= zMax))) {
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
	string objfile = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\NotInBox.obj";
	string datafile = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\NotInBoxNog.obj";

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
	string objdir = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\";

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
	string objfile = "Z:\\IFC Data\\Inside\\InsideOrderedNogNoNormalsNoTCs.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideOrderedNogNoNormalsNoTCsNoMTL.obj";

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

void Replacemtl() {
	string objfile = "Z:\\IFC Data\\InsideSupports\\InsideSupportsOrdered.obj";
	string datafile = "Z:\\IFC Data\\InsideSupports\\InsideSupportsOrderedBest.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);

	while (!obj.eof()) {
		getline(obj, line);
		if (line != "usemtl surface-style-8092-concrete---cast-in-place-concrete-post-tensioned") {
			data << line << endl;
		}
		else {
			data << "usemtl surface-style-423-concrete---cast-in-place-concrete" << endl;
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
	string objfile = "Z:\\IFC Data\\Inside\\CashMachineBestEverNoTCs.obj";
	string datafile = "Z:\\IFC Data\\Inside\\CashMachineBestEverNoTCsNoNormals.obj";

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
	string objfile = "Z:\\IFC Data\\Inside\\CashMachineBestEver.obj";
	string datafile = "Z:\\IFC Data\\Inside\\CashMachineBestEverNoTCs.obj";

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
	string objfile = "Z:\\IFC Data\\Inside\\InsideOrderedReducedMaterialsNoDoorsNoGlitches.obj";

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
			string datafile = "Z:\\IFC Data\\Inside\\Separated\\" + to_string(j + 1) + ".obj";
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

void SplitIntoOneOBJPerObject() {
	string objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\28\\gGlazedInternalSlidingDoor.obj";

	ifstream obj(objfile);

	vector<vector<string>> datafiles(2000);

	int gtype = -1;

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
			gtype++;
			datafiles[gtype].push_back(line);
		}
	}

	for (int j = 0; j < datafiles.size(); j++) {
		if (datafiles[j].size() != 0) {
			string datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\28\\" + to_string(j + 1) + ".obj";
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
	string objfile1 = "Z:\\IFC Data\\Inside\\InsideBest6.obj";
	string objfile2 = "Z:\\IFC Data\\Inside\\Frames.obj";
	string outfile = "Z:\\IFC Data\\Inside\\InsideBest7.obj";

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

	string objdir = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\Frames\\";
	string datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\Frames\\Frames.obj";

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

	string objdir = "Z:\\IFC Data\\Inside\\Separated\\WallsFloors\\";
	string datafile = "Z:\\IFC Data\\Inside\\Separated\\WallsFloors\\OccludersGroupedg.obj";

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

void BatchProcessSingleFileGroupg() {
	string line;
	string test;
	string previous;

	string indir = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\";
	string outdir = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\Groupedg\\";

	int numFiles = GetNumOfFiles(indir);

	for (int i = 1; i <= numFiles; i++) {
		previous = "";
		string infile = indir + to_string(i) + ".obj";
		if (_access_s(infile.c_str(), 0) == 0) { //True if file exists
			ifstream in(infile);
			ofstream out(outdir + to_string(i) + ".obj");
			getline(in, line);
			out << line << endl;
			getline(in, line);
			out << line << endl;

			while (!in.eof()) {
				getline(in, line);
				test = line.substr(0, 2);
				if (test == "g ") {
					test = line.substr(0, 20);
					if (test != previous) {
						out << line << endl;
						previous = test;
					}
				}
				else {
					out << line << endl;
				}
			}
			in.close();
			out.close();
		}
	}
}

void FindObjectinOBJList() {
	string target = "g Cash_Register_10234:Cash_Register_10234:17224173";

	string indir = "Z:\\IFC Data\\Inside\\Separated\\";

	string line;

	bool found = false;

	int numFiles = GetNumOfFiles(indir);

	for (int i = 1; i <= numFiles; i++) {
		string infile = indir + to_string(i) + ".obj";
		if (_access_s(infile.c_str(), 0) == 0) { //True if file exists
			ifstream in(infile);
			while (!in.eof()) {
				getline(in, line);
				if (line == target) {
					cout << "File number is " << i << endl;
					found = true;
					break;
				}
			}
			in.close();
		}
		if (found)
			break;
	}
	if (!found)
		cout << "Object not found!" << endl;
}

void SingleFileGroupg() {
	string line;
	string test;
	string previous;

	string objfile = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\NotInBox.obj";
	string datafile = "Z:\\IFC Data\\Inside\\Separated\\Rooms\\Groupedg\\NotInBoxGroupedg.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	getline(obj, line);
	data << line << endl;
	getline(obj, line);
	data << line << endl;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			test = line.substr(0, 20);
			if (test != previous) {
				data << line << endl;
				previous = test;
			}
		}
		else {
			data << line << endl;
		}
	}
	data.close();
	obj.close();
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
	//	string object = "g WAR_NewcastleLitterBin:WAR_NewcastleLitterBin:798431";
	//	string object = "g WAR_NewcastleLitterBin:WAR_NewcastleLitterBin:798581";
	//	string object = "g WAR_NewcastleLitterBin:WAR_NewcastleLitterBin:798523";
	//  string object = "g WAR_NewcastleLitterBin:WAR_NewcastleLitterBin:798611";
	string object = "g HB_Door_Concept_Int_Sgl_Solid_VP - DT-03:1010x2110mm RB DT 03c:9941156";

	string objfile = "Z:\\IFC Data\\Inside\\Doors\\DiningDoorOrigin.obj";
	string datafile = "Z:\\IFC Data\\Inside\\Doors\\DiningDoorOriginTranslated1.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test = line.substr(0, 2);
	string sub;

	float vert[3];

	//	float Translate[3] = { 0.0f, -0.748f, 0.0f };
	//	float Translate[3] = { 0.0f, -0.3278f, 0.0f };
	//	float Translate[3] = { 0.0f, -0.2035f, 0.0f };
	//  float Translate[3] = { 0.0f, -0.099f, 0.0f };
	float Translate[3] = { -0.554424f, 0.0f, 0.0f };

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

void TranslateObjectsNew() {
	/*string objfile = "Z:\\IFC Data\\Inside\\InsideBest.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideBest1.obj";*/

	//string objfile = "Z:\\IFC Data\\Pathways\\PathwaysOrdered.obj";
	//string datafile = "Z:\\IFC Data\\Pathways\\PathwaysOrdered1.obj";

	string objfile = "Z:\\IFC Data\\Inside\\InsideBest5.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideBest6.obj";

	vector<string> object;
	vector<float> translate;
	vector<vector<float>> translates;

	//object.push_back("g Compound Ceiling:CLG-03:17651448");
	//translate = { 0.0f, 0.001f, 0.0f };
	//translates.push_back(translate);

	//object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 900mm Bench Height:6413199");
	//translate = { 0.001f, 0.0f, 0.0f };
	//translates.push_back(translate);


	/*object.push_back("g AR_Plant_Tree1:WAR_LiquidambarStyraciflua:731878");
	translate = { 0.0f, 0.385f, 0.0f };
	translates.push_back(translate);*/


	//object.push_back("g Floor:475 Thick Post Tension Slab:716246");
	//translate = { 0.001f, 0.0f, 0.0f };
	//translates.push_back(translate);

	//object.push_back("g Basic Wall:300 THICK:829989");
	//translate = { 0.0f, 0.001f, 0.0f };
	//translates.push_back(translate);


	object.push_back("g Basic Wall:HKB_InternalWall_Plaster (IWS08) + Host 200:15208446");
	translate = { 0.001f, 0.0f, 0.0f };
	translates.push_back(translate);


	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test;
	string sub;

	float vert[3];

	bool match = false;

	int loopNum;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			match = false;
			loopNum = 0;
			for (auto l : object) {
				if (line == l) {
					match = true;
					break;
				}
				else {
					loopNum++;
				}
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
			sub = "v " + to_string(vert[0] - translates[loopNum][0]) + " " + to_string(vert[1] + translates[loopNum][1]) + " " + to_string(vert[2] + translates[loopNum][2]);
			data << sub << endl;
		}
		else {
			data << line << endl;
		}
	}
}

void TranslateObjects() {
	string objfile = "Z:\\IFC Data\\Inside\\InsideOrderedReducedMaterialsNoDoors.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideOrderedReducedMaterialsNoDoorsNoGlitches.obj";

	vector<string> object;
	vector<float> translate;
	vector<vector<float>> translates;

	object.push_back("g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495");
	translate = { 0.0f, -0.00012f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-09_LimestonePaving:5880942");
	translate = { 0.0f, -0.00017f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-01_Timber:2136040");
	translate = { 0.0f, -0.0001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_Floor Build up_05_110mm Screed-260mm total:18996914");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_BaseUnit_BlankingPanel_Side:18x500x882mm:6428178");
	translate = { 0.0001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door_and_Drawer:1000mm Wide for 850 / 900mm Bench Height:6427853");
	translate = { 0.0f, -0.00001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door_and_Drawer:1000mm_Wide for 850 / 900mm Bench Height:6427800");
	translate = { 0.0f, -0.00001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door_and_Drawer:1000mm_Wide for 850 / 900mm Bench Height:6427749");
	translate = { 0.0f, -0.00001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-2f-NBS_H+H_140mm_ConcreteBlock_2_no_42mm_Linings of duraline on gypliner:1672134");
	translate = { 0.0f, -0.00003f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3f-sts-149thk-twin-54dB-60FR-5800mh-Sev-no_ins:4628567");
	translate = { 0.0f, 0.0f, -0.0001f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:17651448");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:7348280");
	translate = { 0.0f, 0.00002f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:7348077");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Rectangular Mullion:240 x 100mm _Timber:11811679");
	translate = { -0.00001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Rectangular Mullion:120 x 100mm _Timber:11811681");
	translate = { -0.00001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Rectangular Mullion:120 x 100mm _Timber:11811683");
	translate = { -0.00001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Single_Door:500mm Wide for 850 / 900mm Bench Height:12188757");
	translate = { 0.0f, 0.0f, 0.00005f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:150 WIDE CONTINUOUS RC UPSTAND:13284683");
	translate = { 0.0f, -0.00001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:150 WIDE CONTINUOUS RC UPSTAND:13286207");
	translate = { 0.0f, -0.00001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3d-sts-122thk-twin-50dB-60FR-4600mh-Sev-50_ins:8485227");
	translate = { 0.0f, -0.001f, -0.0001f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-9c-above glazed screens-142thk-twin-50dB-60FR-Sev-no_ins:17059215");
	translate = { 0.0f, -0.0001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-07a- DryLining single board on gypliner 62.5mm no ins:5548762");
	translate = { 0.0f, 0.0f, -0.00001f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 850 / 900mm Bench Height:12186996");
	translate = { 0.0f, 0.0f, 0.0005f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Single_Door:500mm Wide for 850 / 900mm Bench Height:12186990");
	translate = { 0.0f, 0.0f, 0.0005f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3c-sts-127thk-twin-45dB-60FR-4600mh-Sev-no_ins:1640405");
	translate = { 0.0f, -0.001f, -0.00005f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:17636049");
	translate = { 0.0f, -0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:17638435");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:11145113");
	translate = { 0.0f, 0.00002f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:17643632");
	translate = { 0.0f, 0.00001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_Floor Build Up_07a - RAF medium duty:19015549");
	translate = { 0.0f, -0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Balustrade Capping GL 3:Balustrade Capping GL 3:12267550");
	translate = { 0.0f, 0.00001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:Trench Heater - 112mm:12598978:9");
	translate = { 0.0f, -0.00007f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826382");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826308");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826334");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826358");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826406");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826430");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826454");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826477");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826500");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826523");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-08_Carpet:16826556");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:HKB_InternalWall_Plaster (IWS08) + 47.5 + 15 + Host 200:9989232");
	translate = { 0.0f, 0.0f, -0.00005f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:HKB_InternalWall_Plaster (IWS08) + 47.5 + 15 + Host 200:15240752");
	translate = { 0.0f, 0.0f, -0.00005f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 850 / 900mm Bench Height:7453376");
	translate = { -0.001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 850 / 900mm Bench Height:7453227");
	translate = { 0.0f, 0.0f, -0.001f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 850 / 900mm Bench Height:10074681");
	translate = { 0.0f, 0.0f, -0.001f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 850 / 900mm Bench Height:10074680");
	translate = { 0.0f, 0.0f, -0.001f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 850 / 900mm Bench Height:10074903");
	translate = { 0.0f, 0.0f, -0.001f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 850 / 900mm Bench Height:6352949");
	translate = { -0.0001f, 0.0f, -0.00005f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Single_Door:300mm Wide for 850 / 900mm Bench Height:6352951");
	translate = { -0.0001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9726941");
	translate = { 0.0f, 0.0f, 0.0001f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-07c-25-85-45-150 ExtWall IWL 70mm Stud 2 boards + ins:9718767");
	translate = { 0.0f, 0.0f, 0.0001f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-08-plasterboard on thin gypliner 25mm:5601505");
	translate = { -0.0001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_Floor Build Up_07a - RAF medium duty:19025216");
	translate = { 0.0f, -0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Balustrade Sweep 05-06:Balustrade Sweep 05-06:12560179");
	translate = { 0.00001f, 0.0001f, 0.00005f };
	translates.push_back(translate);

	object.push_back("g Balustrade Sweep:Balustrade Sweep:12512239");
	translate = { 0.0015f, 0.005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Floor:RB_FloorFinish_FL-03b_Carpet:11669076");
	translate = { 0.0f, 0.00004f, 0.0f };
	translates.push_back(translate);

	object.push_back("g 1499_Furn_Sofa_WorkPod_op2:Work Pod (4 Seater) 2630Wx1620Dx1360H:5933223");
	translate = { 0.0f, -0.198f, 0.0f };
	translates.push_back(translate);

	object.push_back("g HKB_1499_CoatStand:HKB_1499_CoatStand:8397895");
	translate = { 0.0f, -0.198f, 0.0f };
	translates.push_back(translate);

	object.push_back("g HKB_1499_CoatStand:HKB_1499_CoatStand:8397894");
	translate = { 0.0f, -0.198f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:HKB_InternalWall_Plaster (IWS08) + 47.5 + 15 + Host 200:10246628");
	translate = { 0.0f, 0.0f, -0.0007f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:12098149");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:17638449");
	translate = { 0.0f, 0.00005f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-02:11884800");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-02:7347925");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:17643581");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3c-sts-127thk-twin-45dB-60FR-4600mh-Sev-no_ins:1672807");
	translate = { 0.0f, 0.0f, 0.00002f };
	translates.push_back(translate);

	object.push_back("g 1499_Furn_Board_AVScreen:42\":8641171");
	translate = { 0.0f, 0.176f, 0.0f };
	translates.push_back(translate);

	object.push_back("g 1499_Furn_Board_AVScreen:42\":8639562");
	translate = { 0.0f, 0.176f, 0.0f };
	translates.push_back(translate);

	object.push_back("g 1499_Furn_Board_AVScreen:42\":8639609");
	translate = { 0.0f, 0.176f, 0.0f };
	translates.push_back(translate);

	object.push_back("g 1499_Furn_Board_AVScreen:42\":8641026");
	translate = { 0.0f, 0.176f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3e-sts-122thk-twin-57dB-120FR-4700mh-Sev-25_ins:1635229");
	translate = { 0.0f, -0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3e-sts-122thk-twin-57dB-120FR-4700mh-Sev-25_ins:1634775");
	translate = { 0.0f, -0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3c-sts-127thk-twin-45dB-60FR-4600mh-Sev-no_ins:1736305");
	translate = { 0.0f, -0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3c-sts-127thk-twin-45dB-60FR-4600mh-Sev-no_ins:1736523");
	translate = { 0.0f, -0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:RB-3c-sts-127thk-twin-45dB-60FR-4600mh-Sev-no_ins:2290208");
	translate = { 0.0f, 0.0f, 0.001f };
	translates.push_back(translate);

	object.push_back("g Furn_Fixed_Base_Unit_Dbl_Door:1000mm Wide for 900mm Bench Height:16248745");
	translate = { 0.001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Compound Ceiling:CLG-03:17507319");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Living Stair Balustrade Detail:Living Stair Balustrade Detail:12551245");
	translate = { 0.001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:HKB_InternalWall_Plaster (IWS08) + 62.5 +  Host 300:9975654");
	translate = { -0.001f, 0.0f, 0.0f };
	translates.push_back(translate);

	object.push_back("g RYD_Furn_CSReceptionDesk:RYD_Furn_CSReceptionDesk:7813338");
	translate = { 0.0f, 0.0f, 0.001f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:Topakustik Lining:12558593");
	translate = { 0.0f, 0.001f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:Topakustik Lining:12548638");
	translate = { 0.0f, 0.0165f, 0.0f };
	translates.push_back(translate);

	object.push_back("g Basic Wall:Topakustik Lining:12474366");
	translate = { 0.0f, 0.0099f, 0.0f };
	translates.push_back(translate);

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test;
	string sub;

	float vert[3];

	bool match = false;

	int loopNum;

	while (!obj.eof()) {		
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			match = false;
			loopNum = 0;
			for (auto l : object) {
				if (line == l) {
					match = true;
					break;
				}
				else {
					loopNum++;
				}				
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
			sub = "v " + to_string(vert[0] - translates[loopNum][0]) + " " + to_string(vert[1] + translates[loopNum][1]) + " " + to_string(vert[2] + translates[loopNum][2]);
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

	string objfile = "Z:\\IFC Data\\InsideUnfurnishedUncentred.obj";
	string datafile = "Z:\\IFC Data\\InsideUnfurnishedURT.obj";

	ofstream data(datafile);

	string line;
	string test;
	string sub;

	ifstream obj(objfile);

	double vert[3];
	float normal[3];

	/*float Scale[3] = { 100.0f, 100.0f, 100.0f };
	float Translate[3] = { 134.6f, 12.3f, -1.5f };*/

	//	float Scale[3] = { 100.0f, 100.0f, 100.0f };

	float Scale[3] = { 1.0f, 1.0f, 1.0f };

	//	float Translate[3] = { 30.35f / 1.1f, 29.39f / 1.1f, 30.433f / 1.1f }; //Pipework
	//	float Translate[3] = { 0.0f, 16.6f, 0.0f }; //Inside
	//	float Translate[3] = { -0.227f, -5.42f + 16.6f, -1.392f }; //InsideSupports
	//	float Translate[3] = { -0.24f, 2.25f + 16.6f, -0.02f }; //Outside
	//	float Translate[3] = { 2.2f, -13.75f + 16.6f, -34.29f }; //Pathways

	//	double Translate[3] = { 0.0f, 16.6f, 0.0f }; //Inside

	double Translate[3] = { 424088.812500f, -63.66635f, 564390.500000f }; //Everything else

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			double found;
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
	string objfile = "Z:\\IFC Data\\InsideUnfurnishedURT.obj";
	string datafile = "Z:\\IFC Data\\InsideUnfurnishedURTUV.obj";

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
	string deleteThis = "g Cash_Register_10234:Cash_Register_10234:17224173";
//	int length = (int)deleteThis.length();

	string objfile = "Z:\\IFC Data\\Inside\\InsideOrderedReducedMaterialsNoDoorsNoGlitches.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideOrderedReducedMaterialsNoDoorsNoGlitchesNoCash.obj";

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
		if (line != deleteThis) {
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

	string objfile = "Z:\\IFC Data\\InsideSupportsURTUV.obj";
	string datafile = "Z:\\IFC Data\\InsideSupportsUltra.obj";

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
	//string deleteThis6 = "g AR_Plant_Tree1:WAR_LiquidambarStyraciflua:731878";
	//string deleteThis7 = "g AR_Plant_Tree1:WAR_LiquidambarStyraciflua:732616";
	//string deleteThis8 = "g AR_Plant_Tree1:WAR_LiquidambarStyraciflua:732627";
	string deleteThis9 = "g Floor:Floor-Existing_Planting-425_Grvl-450_Soil-100_Mlch:728267";
	string deleteThis10 = "g Floor:Floor-Existing_Planting-425_Grvl-450_Soil-100_Mlch:728237";
	string deleteThis11 = "g Floor:Floor-Existing_Planting-425_Grvl-450_Soil-100_Mlch:728795";

	//	int length = (int)deleteThis.length();

	string objfile = "Z:\\IFC Data\\PathwaysURTUV.obj";
	string datafile = "Z:\\IFC Data\\PathwaysUltra.obj";

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

		if (line != deleteThis9 && line != deleteThis10 && line != deleteThis11) {
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

	string objfile = "Z:\\IFC Data\\OutsideURTUV.obj";
	string datafile = "Z:\\IFC Data\\OutsideUltra.obj";

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
	string objfile = "Z:\\IFC Data\\Inside\\InsideBest3.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideBest4.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	vector<string> toDelete;

	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:2");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:3");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:4");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:5");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:6");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:7");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:8");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:10");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:11");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:12");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:13");
	//toDelete.push_back("g Floor:Trench Heater - 112mm:12598978:14");
	//toDelete.push_back("g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:2");
	//toDelete.push_back("g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:3");
	//toDelete.push_back("g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:4");
	//toDelete.push_back("g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:5");
	//toDelete.push_back("g Floor:RB_FloorFinish_FL-09_LimestonePaving:11850495:6");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12751795");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12752630");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12751948");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12752250");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12752799");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12751795");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12752630");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12751264");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12752349");
	//toDelete.push_back("g VWE-Event Space Grille:VWE-Event Space Grille:12752127");
	//toDelete.push_back("g Floor:RB_Floor Build up_05_110mm Screed-260mm total:18996844");
	//toDelete.push_back("g Floor:RB_Floor Build up_05_110mm Screed-260mm total:18996928");
	//toDelete.push_back("g Floor:RB_Floor Build up_05_110mm Screed-260mm total:18996858");
	//toDelete.push_back("g Floor:RB_Floor Build up_05_110mm Screed-260mm total:11737316");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:3677855 Stringer 1");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:3677855 Stringer 2");
	//toDelete.push_back("g Square Hollow Sections-Column:SHS140x140x5:11870104");
	//toDelete.push_back("g Basic Wall:HKB_Wall_Structural_225mm:9937258");
	//toDelete.push_back("g Floor:RB_Floor Build Up_07a - RAF medium duty:19011957");
	//toDelete.push_back("g Floor:RB_FloorFinish_FL-02c_Rubber:17538658");
	//toDelete.push_back("g Basic Wall:150 WIDE CONTINUOUS RC UPSTAND:13292395");
	//toDelete.push_back("g Basic Wall:Topakustik Lining:11376217");
	//toDelete.push_back("g Basic Wall:200 Wide continuous RC upstand:11218255");
	//toDelete.push_back("g Basic Wall:200 Wide continuous RC upstand:11217594");
	//toDelete.push_back("g Basic Wall:150 WIDE CONTINUOUS RC UPSTAND:11217674");
	//toDelete.push_back("g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486327");
	//toDelete.push_back("g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486414");
	//toDelete.push_back("g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486276");
	//toDelete.push_back("g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486187");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 1");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 2");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 3");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 4");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 5");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 6");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 9");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:12360584 Stringer 10");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:2086486 Stringer 3");
	//toDelete.push_back("g Cast-In-Place Stair:Stair:2086486 Stringer 4");
	//toDelete.push_back("g Floor:RB_Floor Build Up_07a - RAF medium duty:19024639");
	//toDelete.push_back("g Basic Roof:40-45-45-175_Semi-intensive_Green_Roof_System:19040789");
	//toDelete.push_back("g Floor:RB_FloorFinish_FL-03b_Carpet:11669076");
	//toDelete.push_back("g Floor:RB_Floor Build up_07c RAF antistatic bonded vinyl:7613301");
	//toDelete.push_back("g Floor:RB_Floor Build Up_07a - RAF medium duty:18999082");
	//toDelete.push_back("g Floor:RB_Floor Build up_08_180mm with 80 screed:18998373");
	//toDelete.push_back("g Bunn_BrewWISE_Coffee_Maker_11661:Bunn_BrewWISE_Coffee_Maker_11661:14278969");
	//toDelete.push_back("g Bunn_BrewWISE_Coffee_Maker_11661:Bunn_BrewWISE_Coffee_Maker_11661:14279402");

	toDelete.push_back("g Cash_Register_10234:Cash_Register_10234:17224173");


	string deleteThis1 = "g Glazed Internal Double Timber Doors:DT-22:";
	string deleteThis2 = "g Glazed Internal Double Sliding Door:";
	string deleteThis3 = "g Glazed Internal Single Doors:";
	string deleteThis4 = "g Glazed Internal Double Doors:";
	string deleteThis5 = "g HB_WC_Cubicle_FrontOnly:";

	int length1 = (int)deleteThis1.length();
	int length2 = (int)deleteThis2.length();
	int length3 = (int)deleteThis3.length();
	int length4 = (int)deleteThis4.length();
	int length5 = (int)deleteThis5.length();

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
		if (sub1 != deleteThis1 && sub2 != deleteThis2 && sub3 != deleteThis3 && sub4 != deleteThis4 && sub5 != deleteThis5) {
			valid = true;
			for (auto l : toDelete) {
				if (line == l) {
					valid = false;
					break;
				}
			}
			if (valid) {
				lines.push_back(line);
			}
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);
	}
	data.close();
	obj.close();

	toDelete.clear();
}

void DeleteObjectsInsideExtraOld() {
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

	//string deleteThis1 = "g 25-50-20-135 Fire Curtain:Fireguard_SC120:12086224";
	//string deleteThis2 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8447898";
	//string deleteThis3 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8447929";
	//string deleteThis4 = "g 1499_Furn_Bench_AtriumCanopy_Placeholder:Circle Bench 1000dia x 2000H:8759571";
	//string deleteThis5 = "g 1499_Furn_CoffeeCart:1499_Furn_CoffeeCart:7432262";
	//string deleteThis6 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486507";
	//string deleteThis7 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486818";
	//string deleteThis8 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486761";
	//string deleteThis9 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486708";
	//string deleteThis10 = "g Site_Bollard_Steel:150_Diameter-1000mm_Height:8486599";
	//string deleteThis11 = "g Basic Roof:HKB_Roof__Entrance Canopy:19043512";
	//string deleteThis12 = "g Sliding_Stacking_Panel_Partition:DT-17:8292025";


	string deleteThis1 = "g Glazed Internal Double Timber Doors:DT-22:";
	string deleteThis2 = "g Glazed Internal Double Sliding Door:";
	string deleteThis3 = "g Glazed Internal Single Doors:";
	string deleteThis4 = "g Glazed Internal Double Doors:";
	string deleteThis5 = "g HB_WC_Cubicle_FrontOnly:";

	int length1 = (int)deleteThis1.length();
	int length2 = (int)deleteThis2.length();
	int length3 = (int)deleteThis3.length();
	int length4 = (int)deleteThis4.length();
	int length5 = (int)deleteThis5.length();

	string objfile = "Z:\\IFC Data\\Inside\\InsideOrdered.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideOrderedNoDoors.obj";

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
		//		sub6 = line.substr(0, length6);
		if (sub1 != deleteThis1 && sub2 != deleteThis2 && sub3 != deleteThis3 && sub4 != deleteThis4 && sub5 != deleteThis5) {
			/*if (line != deleteThis1 && line != deleteThis2 && line != deleteThis3 && line != deleteThis4 && line != deleteThis5 && line != deleteThis6 &&
				line != deleteThis7 && line != deleteThis8 && line != deleteThis9 && line != deleteThis10 && line != deleteThis11 && line != deleteThis12) {*/
			lines.push_back(line);
			valid = true;
		}
		DeleteObjectsHelperFunction(valid, obj, data, line, validVertex, validTexcoord, validNormal, lines);
	}
	data.close();
	obj.close();
}

void Listg() {
	string objfile = "Z:\\IFC Data\\Inside\\Doors\\gHB_Door_Concept_Int_Dbl_Solid.obj";
	string datafile = "Z:\\IFC Data\\Inside\\Doors\\DoorObjects.txt";

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
	data.close();
	obj.close();
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
	mtl.close();
}

void ListMaterials() {
	string mtlfile = "Z:\\IFC Data\\Inside\\InsideOrderedNoDoorsTotallyOrderedMTL.obj";
	string datafile = "Z:\\IFC Data\\Inside\\InsideOrderedNoDoorsTotallyOrderedMTL.txt";

	ifstream mtl(mtlfile);
	ofstream out(datafile);

	string line;
	string test;

	int count = 0;

	string previous;

	while (!mtl.eof()) {
		getline(mtl, line);
		test = line.substr(0, 6);
		if (test == "usemtl") {
			if (previous != line) {
				count++;
				previous = line;
			}
			out << "mat.push_back(\"" + line.substr(7) + "\");" << endl;
		}
	}
	cout << count << endl;
	mtl.close();
	out.close();
}

void FillMat1Vector(vector<string>& mat) {
	mat.push_back("IfcBeam");
	mat.push_back("IfcBuildingElementProxy");
	mat.push_back("IfcCovering");
	mat.push_back("IfcFlowTerminal");
	mat.push_back("IfcFurnishingElement");
	mat.push_back("IfcPlate");
	mat.push_back("IfcTransportElement");
	mat.push_back("surface-style-1054000-aluminium-dorma-metal-anodized-silver");
	mat.push_back("surface-style-108753-screed");
	mat.push_back("surface-style-109933-hkb_floor_lino");
	mat.push_back("surface-style-1130044-orangebox_aluminium_ral-9006");
	mat.push_back("surface-style-1330249-concrete-masonry,-floor-block");
	mat.push_back("surface-style-1367305-_wilkhahn-white-varnish");
	mat.push_back("surface-style-154260-concrete,-cast-in-place-gray");
	mat.push_back("surface-style-154410-concrete,-precast");
	mat.push_back("surface-style-1960184-glass-splashback");
	mat.push_back("surface-style-2153869-dorma---brushed-stainless-steel");
	mat.push_back("surface-style-2263442-concrete---cast-in-place-concrete");
	mat.push_back("surface-style-2294322-fermacell_gypsum_fibre_board");
	mat.push_back("surface-style-2294775-concrete,-cast-in-situ");
	mat.push_back("surface-style-260120-furniture---helmsman-ice");
	mat.push_back("surface-style-2611090-chrome---polished-black");
	mat.push_back("surface-style-27026-metal---steel-galvanised");
	mat.push_back("surface-style-278030-metal---chrome");
	mat.push_back("surface-style-2804151-amwell-mercury");
	mat.push_back("surface-style-3068807-silicon-nitride---polished");
	mat.push_back("surface-style-523-gypsum-plasterboard---15mm-gyproc-duraline");
	mat.push_back("surface-style-5539043-chair---chrome");
	mat.push_back("surface-style-5571425-polished");
	mat.push_back("surface-style-5589331-stainless-steel-brushed");
	mat.push_back("surface-style-585793-casework---carcass-finish");
	mat.push_back("surface-style-6186396-white-plastic");
	mat.push_back("surface-style-6187127-white-pvc");
	mat.push_back("surface-style-624444-furniture---metal-racking");
	mat.push_back("surface-style-6456067-pc-monitor-color-accent");
	mat.push_back("surface-style-6627-pc---silver");
	mat.push_back("surface-style-6989062-stainless-steel-baluster");
	mat.push_back("surface-style-477585-mirror");
}

void FillMat2Vector(vector<string>& mat) {
	mat.push_back("surface-style-111619-dulux-ral9010");
	mat.push_back("IfcRailing");
	mat.push_back("surface-style-1082063-bedding");
	mat.push_back("surface-style-1082080-hkb_floor_paving_limestone");
	mat.push_back("surface-style-1130398-orangebox_plastic_grey");
	mat.push_back("surface-style-1318490-steel,-paint-finish,-dark-gray,-matte");
	mat.push_back("surface-style-1338935-orangebox_wood_walnut");
	mat.push_back("surface-style-1894178-corian-anthracite");
	mat.push_back("surface-style-2145779-horizontal-lines");
	mat.push_back("surface-style-2168052-ryderbp-mdf");
	mat.push_back("surface-style-2330430-stainless-steel");
	mat.push_back("surface-style-260108-default");
	mat.push_back("surface-style-2804169-amwell-solid-surface-hurricane");
	mat.push_back("surface-style-3036151-ceramic-sink");
	mat.push_back("surface-style-3068825-chrome");
	mat.push_back("surface-style-3080611-amwell-stainless-steel");
	mat.push_back("surface-style-42673-abet-1810-sei-laminate");
	mat.push_back("surface-style-4678673-red-(1)");
	mat.push_back("surface-style-5167355-rigid-insulation-for-screed");
	mat.push_back("surface-style-5459834-topakustik-finish");
	mat.push_back("surface-style-5571407-powder-coated-aluminium-grey-lj");
	mat.push_back("surface-style-5589695-ceramic");
	mat.push_back("surface-style-564165-plastic---gray");
	mat.push_back("surface-style-5642854-metal---paint-finish---dark-gray,-matte");
	mat.push_back("surface-style-566764-plastic---gray,-dark");
	mat.push_back("surface-style-6229015-_chs_default_grey");
	mat.push_back("surface-style-6355752-stainless-steel-polished");
	mat.push_back("surface-style-6422922-airflake-wall");
	mat.push_back("surface-style-6798052-render-material-harmaa-128-128-128");
	mat.push_back("surface-style-6952124-asphalt,-bitumen");
	mat.push_back("surface-style-6953474-nbs_sikasarnafil_polymericroofingmembranes_sarnafiltcs");
	mat.push_back("surface-style-6957571-default-roof");
	mat.push_back("surface-style-6960788-stainless-steel,-brushed");
	mat.push_back("surface-style-780453-generic");
	mat.push_back("surface-style-886424-furniture---chrome");
	mat.push_back("surface-style-586616-default-wall");
}

void FillMat3Vector(vector<string>& mat) {
	mat.push_back("surface-style-197828-european-oak");
	mat.push_back("surface-style-603-nbs_h+huk_autoclavedaeratedconcreteblocks_standardgrade_celconblock");
	mat.push_back("IfcSlab");
	mat.push_back("surface-style-1069685-abet-1830-grigio-etna");
	mat.push_back("surface-style-108480-hkb_floor_carpet");
	mat.push_back("surface-style-108736-insulation-/-support-frame");
	mat.push_back("surface-style-110646-concrete-cladding_painted-black-finish");
	mat.push_back("surface-style-110886-metal---stud-layer");
	mat.push_back("surface-style-1130218-orangebox_fabric-3_grey");
	mat.push_back("surface-style-2147767-abet-1830-etna");
	mat.push_back("surface-style-2846719-amwell-charcoal");
	mat.push_back("surface-style-3475765-ash_armitageshanks_grabbars_contour21_charcoalrn_render");
	mat.push_back("surface-style-469785-plastik");
	mat.push_back("surface-style-5512872-_2-ral---7011-iron-grey");
	mat.push_back("surface-style-5551090-ral7002");
	mat.push_back("surface-style-5589343-duco-coated");
	mat.push_back("surface-style-5621373-noraplan-ultra-grip-6015");
	mat.push_back("surface-style-5702812-grey-plastic");
	mat.push_back("surface-style-6220697-_chs_mildsteel");
	mat.push_back("surface-style-6456056-default-3");
	mat.push_back("surface-style-6456078-default-2");
	mat.push_back("surface-style-831040-slate-grey");
	mat.push_back("surface-style-846327-external-sheathing-board");
}

void FillMat4Vector(vector<string>& mat) {
	mat.push_back("surface-style-1614280-fabric-material-1");
	mat.push_back("surface-style-6543051-site-specified");
}

void FillMat5Vector(vector<string>& mat) {
	mat.push_back("surface-style-1161443-wood---birch");
	mat.push_back("surface-style-2166947-wood---timber");
	mat.push_back("surface-style-227510-metal---powder-coated-orange");
	mat.push_back("surface-style-469635-sittepute");
	mat.push_back("surface-style-5209893-door---frame/mullion");
	mat.push_back("surface-style-5209902-door---panel");
}

void FillMat6Vector(vector<string>& mat) {
	mat.push_back("surface-style-205659-mesh");
	mat.push_back("surface-style-2285-glazing_internal");
}

void FillMat7Vector(vector<string>& mat) {
	mat.push_back("surface-style-57879-rubber");
	mat.push_back("surface-style-2460-ral-7016-paint");
	mat.push_back("surface-style-298458-hkb_paint_black");
	mat.push_back("surface-style-547245-trim");
	mat.push_back("surface-style-609027-pc---black");
	mat.push_back("surface-style-615134-chair---dark-grey");
	mat.push_back("surface-style-615182-chair---black");
}

void FillMat8Vector(vector<string>& mat) {
	mat.push_back("surface-style-24662-hkb_floor_timber_03");
	mat.push_back("surface-style-2846731-amwell-hessian");
	mat.push_back("surface-style-6364330-lucia-aruba");
}

void FillMat9Vector(vector<string>& mat) {
	mat.push_back("surface-style-1130464-orangebox_wood_maple");
	mat.push_back("surface-style-26946-hkb_floor_timber");
	mat.push_back("surface-style-57909-wood---maple");
	mat.push_back("surface-style-782021-hkb_frame_timber");
	mat.push_back("surface-style-6367549-reef-yb085");
}

void FillMat10Vector(vector<string>& mat) {
	mat.push_back("IfcWall");
	mat.push_back("IfcWallStandardCase");
	mat.push_back("surface-style-107878-concrete---white");
	mat.push_back("surface-style-1092406-nbl_conceptsolid");
	mat.push_back("surface-style-110137-air");
	mat.push_back("surface-style-110864-ceilings---plasterboard-(perforated)(rigitone)");
	mat.push_back("surface-style-111078-concrete_ancillary");
	mat.push_back("surface-style-1246088-material-metal-polished");
	mat.push_back("surface-style-1246099-material-metal-brushed");
	mat.push_back("surface-style-1314600-hkb_paint_white");
	mat.push_back("surface-style-1330880-_1---ral---9010-pure-white");
	mat.push_back("surface-style-1367323-_wilkhahn-bright-chromed-alloy");
	mat.push_back("surface-style-1405678-whitegoods");
	mat.push_back("surface-style-1887331-ceilings---plasterboard-(solid)(services_raft)");
	mat.push_back("surface-style-1933663-ice-white");
	mat.push_back("surface-style-1941113-ceiling-tile-600-x-600");
	mat.push_back("surface-style-205858-aluminium");
	mat.push_back("surface-style-2084299-metal---white-powder-coated");
	mat.push_back("surface-style-2155994-furniture---coat-hooks");
	mat.push_back("surface-style-2194164-metal---stainless-steel");
	mat.push_back("surface-style-2316927-nbs_concept");
	mat.push_back("surface-style-24812-metal---steel");
	mat.push_back("surface-style-2518887-pvc---white");
	mat.push_back("surface-style-2591647-vc");
	mat.push_back("surface-style-260096-metal---chrome-polished");
	mat.push_back("surface-style-260132-furniture---white-paint");
	mat.push_back("surface-style-277994-metal---paint-finish---ivory,-glossy");
	mat.push_back("surface-style-281743-metal---aluminium");
	mat.push_back("surface-style-2829336-ash_armitageshanks-_sanitaryware_white5_render");
	mat.push_back("surface-style-2829739-ash_armitageshanks-_plastic_white1_render");
	mat.push_back("surface-style-284035-gypsum-plasterboard---15mm-gyproc-wallboard");
	mat.push_back("surface-style-2968454-fine-fireclay");
	mat.push_back("surface-style-3080627-amwell-linen");
	mat.push_back("surface-style-3475744-ash_armitageshanks_ancillaries_contour21_white_bump");
	mat.push_back("surface-style-3475776-ash_armitageshanks_grabbars_contour21_whiteac_render");
	mat.push_back("surface-style-35235-gypsum-plasterboard---6mm-gyproc-multiboard");
	mat.push_back("surface-style-4306133-disabled-white");
	mat.push_back("surface-style-4306151-paint---white-disabled");
	mat.push_back("surface-style-469743-metall");
	mat.push_back("surface-style-5108425-metal---steel-50-355");
	mat.push_back("surface-style-5108666-metal---steel-43-275");
	mat.push_back("surface-style-5421372-nbl_conceptwhite");
	mat.push_back("surface-style-5537040-concept---white");
	mat.push_back("surface-style-5571395-chrome---polished");
	mat.push_back("surface-style-5658917-cabinets");
	mat.push_back("surface-style-5697654-plasterboard-improved-fire-resistance");
	mat.push_back("surface-style-5782770-metal---stainless-steel,-polished-plain");
	mat.push_back("surface-style-57921-table---frame-finish");
	mat.push_back("surface-style-5793920-ryder_intent_steelwork");
	mat.push_back("surface-style-585745-casework---cupboard-handle");
	mat.push_back("surface-style-585757-casework---door-/-drawer-front");
	mat.push_back("surface-style-620830-plasterboard-monolithic");
	mat.push_back("surface-style-6218669-_chs_default_white");
	mat.push_back("surface-style-6571971-void");
	mat.push_back("surface-style-6954175-paving-450mm-sq");
	mat.push_back("surface-style-787429-cubicle-finish-1");
	mat.push_back("surface-style-787438-finishes_paint_sen");
	mat.push_back("surface-style-974-gypsum-plasterboard---12.5mm-gyproc-wallboard");
	mat.push_back("surface-style-534738-porcelain");
}

void FillMat11Vector(vector<string>& mat) {
	mat.push_back("surface-style-1130416-orangebox_plastic_black");
	mat.push_back("surface-style-1367251-_wilkhahn-black-plastic");
	mat.push_back("surface-style-280643-internal-door---architrave");
	mat.push_back("surface-style-469695-dekk");
	mat.push_back("surface-style-564177-plastic---black");
	mat.push_back("surface-style-6229003-_chs_default_black");
	mat.push_back("surface-style-6456094-pc-monitor-color");
}

void FillMat12Vector(vector<string>& mat) {
	mat.push_back("surface-style-6539946");
	mat.push_back("surface-style-6798004");
	mat.push_back("surface-style-6798028");
}

void FillMat13Vector(vector<string>& mat) {
	mat.push_back("surface-style-6456045-pc-monitor-glass");
	mat.push_back("surface-style-886442-chair---blue");
}

void FillMat14Vector(vector<string>& mat) {
	mat.push_back("surface-style-112875-");
	mat.push_back("surface-style-2167195");
	mat.push_back("surface-style-6367417");
}

void ReplaceMaterials() {
	string infile = "Z:\\IFC Data\\Inside\\InsideOrdered.obj";
	string outfile = "Z:\\IFC Data\\Inside\\InsideOrderedReducedMaterials.obj";

	ifstream in(infile);
	ofstream out(outfile);

	string line;
	string test;

	vector<string> mat1;
	vector<string> mat2;
	vector<string> mat3;
	vector<string> mat4;
	vector<string> mat5;
	vector<string> mat6;
	vector<string> mat7;
	vector<string> mat8;
	vector<string> mat9;
	vector<string> mat10;
	vector<string> mat11;
	vector<string> mat12;
	vector<string> mat13;
	vector<string> mat14;

	FillMat1Vector(mat1);
	FillMat2Vector(mat2);
	FillMat3Vector(mat3);
	FillMat4Vector(mat4);
	FillMat5Vector(mat5);
	FillMat6Vector(mat6);
	FillMat7Vector(mat7);
	FillMat8Vector(mat8);
	FillMat9Vector(mat9);
	FillMat10Vector(mat10);
	FillMat11Vector(mat11);
	FillMat12Vector(mat12);
	FillMat13Vector(mat13);
	FillMat14Vector(mat14);

	bool match;

	while (!in.eof()) {
		match = false;
		getline(in, line);
		test = line.substr(0, 6);
		if (test == "usemtl") {
			if (line == "usemtl IfcDoor" || line == "usemtl surface-style-1130206-orangebox_fabric-2_red" || line == "usemtl surface-style-197643-cafe-couch-material" ||
				line == "usemtl surface-style-2451-door---glazing" || line == "usemtl surface-style-3305054-amwell-heather" ||
				line == "usemtl surface-style-469833-håndtak" || line == "usemtl surface-style-5537028-event-space-luminaire" || line == "usemtl surface-style-5782782-paint---red" ||
				line == "usemtl surface-style-5783130-plastic---orange" || line == "usemtl surface-style-615170-chair---fabric---red" || line == "usemtl surface-style-7116102-glass,-clear-glazing" ||
				line == "usemtl surface-style-778770-arcat---fabric---heavy-duty-exterior-grade" || line == "usemtl surface-style-109430-gypsum-plasterboard---19mm-gyproc-coreboard" ||
				line == "usemtl surface-style-13775-mastic---clear" || line == "usemtl surface-style-34257-glass" || line == "usemtl surface-style-13775-mastic---clear" ||
				line == "usemtl surface-style-281761-plastic---white" || line == "usemtl surface-style-217-gypsum-plasterboard---12.5mm-gyproc-soundbloc" ||
				line == "usemtl surface-style-2264790-vapour-control-layer" || line == "surface-style-197819-analytical-floor-surface") {
				out << line << endl;
				match = true;
			}
			if (!match) {
				for (auto lines : mat1) {
					if (lines == line.substr(7)) {
						out << "usemtl IfcBeam" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat2) {
					if (lines == line.substr(7)) {
						out << "usemtl IfcRailing" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat3) {
					if (lines == line.substr(7)) {
						out << "usemtl IfcSlab" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat4) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-1614280-fabric-material-1" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat5) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-227510-metal---powder-coated-orange" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat6) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-2285-glazing_internal" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat7) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-2460-ral-7016-paint" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat8) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-24662-hkb_floor_timber_03" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat9) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-26946-hkb_floor_timber" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat10) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-35235-gypsum-plasterboard---6mm-gyproc-multiboard" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat11) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-469695-dekk" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat12) {
					if (lines == line.substr(7, 21)) {
						out << "usemtl surface-style-6539946-machine_green" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat13) {
					if (lines == line.substr(7)) {
						out << "usemtl surface-style-886442-chair---blue" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				for (auto lines : mat14) {
					if (lines == line.substr(7, 21)) {
						out << "usemtl surface-style-2167195-hkb_topakustik_14-2" << endl;
						match = true;
						break;
					}
				}
			}
			if (!match) {
				out << line << endl;
			}
		}
		else {
			out << line << endl;
		}
	}
	in.close();
	out.close();
}

void Objectscount() {
	string objfile = "Z:\\IFC Data\\Inside\\CashMachineBestEver.obj";

	ifstream obj(objfile);

	string line;
	string test;

	int objnum = 0;
	int vertex = 0;
	int texcoord = 0;
	int normal = 0;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "g ") {
			objnum++;
		}
		if (test == "v ") {
			vertex++;
		}
		if (test == "vn") {
			normal++;
		}
		if (test == "vt") {
			texcoord++;
		}
	}
	cout << "Number of objects: " << objnum << endl;
	cout << "Number of vertices: " << vertex << endl;
	cout << "Number of texture coordinates: " << texcoord << endl;
	cout << "Number of normals: " << normal << endl;
}

void DivideMaterials1() {
	int loopNum = 0;
	int loopNumf = 0;

	string objfile = "Z:\\IFC Data\\Inside\\InsideOrderedNoDoorsReducedMaterials.obj";

	ifstream obj(objfile);

	vector<string> currentObject;
	vector<vector<string>> datafiles;
	vector<int> vertNormUVIndex(3, 0);
	vector<vector<int>> vertNormUVIndices;

	int mtype = 0;
	vector<string> preMats;
	bool repeated = false;

	string line;
	string test;
	string material;

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
		test = line.substr(0, 2);
		if (test == "us") {
			for (auto i : preMats) {
				if (line == i) {
					repeated = true;
					break;
				}
			}
			if (!repeated) {
				preMats.push_back(line);
			}
			else {
				repeated = false;
			}
		}
	}
	obj.close();

	for (int i = 0; i < preMats.size(); i++) {
		datafiles.push_back(currentObject);
		vertNormUVIndices.push_back(vertNormUVIndex);
	}

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
			if (test == "us") {
				material = line;
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
			mtype = 0;
			for (auto i : preMats) {
				if (material == i) {
					break;
				}
				mtype++;
			}

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
								triangle[i] = found + vertNormUVIndices[mtype][0] - vertexIndexMin + 1;
							}
							if (i == 1 || i == 4 || i == 7) {
								triangle[i] = found + vertNormUVIndices[mtype][1] - UVIndexMin + 1;
							}
							if (i == 2 || i == 5 || i == 8) {
								triangle[i] = found + vertNormUVIndices[mtype][2] - normalIndexMin + 1;
							}
							i++;
						}
						temp = "";
					}
					linex = "f " + to_string(triangle[0]) + '/' + to_string(triangle[1]) + '/' + to_string(triangle[2]) + ' ' + to_string(triangle[3]) + '/' + to_string(triangle[4]) + '/' + to_string(triangle[5]) + ' '
						+ to_string(triangle[6]) + '/' + to_string(triangle[7]) + '/' + to_string(triangle[8]);
				}
				datafiles[mtype].push_back(linex);
			}
			vertNormUVIndices[mtype][0] += vertex;
			vertNormUVIndices[mtype][1] += texcoord;
			vertNormUVIndices[mtype][2] += normal;

			currentObject.clear();
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
			if (endFile) {
				exit = true;
			}
		}
	} while (!exit);

	string line1 = lines[0];
	string line2 = lines[1];

	lines.clear();
	vertNormUVIndices.clear();

	cout << datafiles.size() << endl;

	for (int j = 0; j < datafiles.size(); j++) {
		string datafile = "Z:\\IFC Data\\Inside\\SplitByMaterial\\" + to_string(j + 1) + ".obj";
		ofstream data(datafile);
		data << line1 << endl;
		data << line2 << endl;
		for (auto i : datafiles[j]) {
			data << i << endl;
		}
		data.close();
	}

	datafiles.clear(); //TODO Make sure all vectors are cleared at the end of all other functions!
}

void DivideMaterials() {
	string infile = "Z:\\IFC Data\\Inside\\SplitByMaterial\\InsideOrderedTextures.obj";
	string outfile = "Z:\\IFC Data\\Inside\\SplitByMaterial\\InsideTotallyOrderedReducedMTLGroupedG.obj";

	ifstream in(infile);
	ofstream out(outfile);

	vector<string> currentObject;
	vector<vector<string>> datafiles;

	int mtype = 0;
	vector<string> preMats;
	bool repeated = false;
	bool first = true;

	string line;
	string test;
	string previous;

	vector<string> lines;

	while (!in.eof()) {
		getline(in, line);
		lines.push_back(line);
		test = line.substr(0, 2);
		if (test == "us") {
			for (auto i : preMats) {
				if (line == i) {
					repeated = true;
					break;
				}
			}
			if (!repeated) {
				preMats.push_back(line);
			}
			else {
				repeated = false;
			}
		}
	}
	in.close();

	for (int i = 0; i < preMats.size(); i++) {
		datafiles.push_back(currentObject);
	}

	for (auto j : lines) {
		test = j.substr(0, 2);
		if (test == "us" || test == "f ") {
			if (test == "us") {
				mtype = 0;
				for (auto i : preMats) {
					if (j == i) {
						break;
					}
					mtype++;
				}
				if (j != previous) {
					datafiles[mtype].push_back(j);
					previous = j;
				}
			}
			else {
				datafiles[mtype].push_back(j);
			}
		}
		else {
			if (test != "g ") {
				if (test != "") {
					out << j << endl;
				}
			}
			else {
				if (first) {
					out << j << endl;
					first = false;
				}
			}
		}
	}

	for (int j = 0; j < datafiles.size(); j++) {
		first = true;
		for (auto i : datafiles[j]) {
			if (i.substr(0, 2) != "us") {
				if (i != "") {
					out << i << endl;
				}
			}
			else {
				if (first) {
					if (i != "") {
						out << "g " + to_string(j) << endl;
						out << i << endl;
						first = false;
					}
				}
			}
		}
	}

	out.close();
	datafiles.clear();
}

void FixCoffeeMachineGlitch() {
	string objfile = "Z:\\IFC Data\\Inside\\CoffeeMachines.obj";
	string datafile = "Z:\\IFC Data\\Inside\\CoffeeMachinesFixed.obj";

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test;
	string sub;

	float vert[3];

	float Translate[3] = { 0.001f, 0.0f, 0.001f };

	bool match = false;

	int vertex = 0;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test == "v ") {
			vertex++;
			if (vertex >= 7713 && vertex <= 7868 || vertex >= 50835 && vertex <= 50990) {
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
		else {
			data << line << endl;
		}
	}
}

void SplitMesh(int fileNum = 0, int folderNum = 0) {
	string objfile;

	string out1file;
	string out2file;
	/*if (folderNum == 0) {
		if (fileNum == 0) {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\1.obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Frame1.obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1.obj";
		}
		else {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\" + to_string(fileNum) + ".obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Frame" + to_string(fileNum) + ".obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + ".obj";
		}
	}
	else {
		if (fileNum == 0) {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\1.obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Frame1.obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1.obj";
		}
		else {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\" + to_string(fileNum) + ".obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Frame" + to_string(fileNum) + ".obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + ".obj";
		}
	}*/

	if (folderNum == 0) {
		if (fileNum == 0) {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\1.obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\DoorFrame1.obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\DoorFrame2.obj";
		}
		else {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + ".obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "a.obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "b.obj";
		}
	}
	else {
		if (fileNum == 0) {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1.obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1a.obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1b.obj";
		}
		else {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\" + to_string(fileNum) + ".obj";
			out1file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "a.obj";
			out2file = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "b.obj";
		}
	}

	if (_access_s(objfile.c_str(), 0) != 0) { //True if file does not exist
		return;
	}
	
	ifstream obj(objfile);
	ofstream out1(out1file);
	ofstream out2(out2file);

	vector<int> vert;

	//vert.push_back(121); // 1, 2
	//vert.push_back(167);

	//vert.push_back(289);
	//vert.push_back(383);


	//vert.push_back(1); // 3, 8 and 11
	//vert.push_back(48);
	//
	//vert.push_back(169);
	//vert.push_back(262);


	//vert.push_back(1); // 4
	//vert.push_back(48);

	//vert.push_back(73);
	//vert.push_back(168);

	//vert.push_back(169);
	//vert.push_back(262);


	//vert.push_back(25); // 5
	//vert.push_back(72);

	//vert.push_back(97);
	//vert.push_back(192);


	//vert.push_back(121); // 6, 7
	//vert.push_back(168);

	//vert.push_back(289);
	//vert.push_back(384);


	//vert.push_back(1); // 9
	//vert.push_back(48);

	//vert.push_back(73);
	//vert.push_back(168);

	//vert.push_back(1); // 10
	//vert.push_back(144);

	//vert.push_back(1); // DoorA
	//vert.push_back(120);

	//vert.push_back(1); // 13
	//vert.push_back(24);

	//vert.push_back(1); // 17, 18
	//vert.push_back(120);

	//vert.push_back(241);
	//vert.push_back(264);

	//vert.push_back(1); // 22
	//vert.push_back(24);

	vert.push_back(1); // 23, 24, 25 - 27
	vert.push_back(24);

	vert.push_back(49);
	vert.push_back(96);


	//vert.push_back(289); // DoorFrame1
	//vert.push_back(384);

	int firstVertexIndex = 0;
	int firstUVIndex = 0;
	int firstNormalIndex = 0;
	int loopNum = 0;

	bool firstVertex = true;
	bool firstUV = true;
	bool firstNormal = true;

	int triangle[9];

	string line;
	string test;

	vector<string> data;
	vector<string> doorData;
	vector<string> frameData;

	vector<int> doorVertexIndices;
	vector<int> doorUVIndices;
	vector<int> doorNormalIndices;
	vector<int> frameVertexIndices;
	vector<int> frameUVIndices;
	vector<int> frameNormalIndices;

	map<int, int> doorVertexIndicesMap;
	map<int, int> doorUVIndicesMap;
	map<int, int> doorNormalIndicesMap;
	map<int, int> frameVertexIndicesMap;
	map<int, int> frameUVIndicesMap;
	map<int, int> frameNormalIndicesMap;

	bool frame;

	while (!obj.eof()) {
		getline(obj, line);
		test = line.substr(0, 2);
		if (test != "  ") {
			if (test == "v " || test == "vt" || test == "vn") {
				data.push_back(line);
				if (test == "v " && firstVertex) {
					firstVertexIndex = loopNum;
					firstVertex = false;
				}
				if (test == "vt" && firstUV) {
					firstUVIndex = loopNum;
					firstUV = false;
				}
				if (test == "vn" && firstNormal) {
					firstNormalIndex = loopNum;
					firstNormal = false;
				}
				loopNum++;
			}
			else {
				if (test == "# " || test == "mt" || test == "g " || test == "s ") {
					if (test == "g ") {
						out1 << line + " frame" << endl;
						out2 << line + " door" << endl;
					}
					else {
						out1 << line << endl;
						out2 << line << endl;
					}
				}
				if (test == "f ") {
					test = line.substr(2);
					string line1 = regex_replace(test, std::regex(R"(\/)"), " ");
					stringstream ss;
					ss << line1;
					string temp;
					int found;
					int j = 0;
					frame = false;
					while (!ss.eof()) {
						ss >> temp;
						if (stringstream(temp) >> found) {
							for (int i = 0; i < vert.size(); ) {
								if (found >= vert[i] && found <= vert[i + 1]) {
									frame = true;
									break;
								}
								i += 2;
							}
							triangle[j] = found;
						}
						temp = "";
						j++;
					}
					
					if (frame) {
						frameData.push_back(line);
						for (int l = 0; l < 9; l++) {
							if (l == 0 || l == 3 || l == 6) {
								frameVertexIndices.push_back(triangle[l]);
							}
							if (l == 1 || l == 4 || l == 7) {
								frameUVIndices.push_back(triangle[l]);
							}
							if (l == 2 || l == 5 || l == 8) {
								frameNormalIndices.push_back(triangle[l]);
							}
						}
					}
					else {
						doorData.push_back(line);
						for (int k = 0; k < 9; k++) {
							if (k == 0 || k == 3 || k == 6) {
								doorVertexIndices.push_back(triangle[k]);
							}
							if (k == 1 || k == 4 || k == 7) {
								doorUVIndices.push_back(triangle[k]);
							}
							if (k == 2 || k == 5 || k == 8) {
								doorNormalIndices.push_back(triangle[k]);
							}
						}		
					}
				}
				if (test == "us") {
					frameData.push_back(line);
					doorData.push_back(line);
				}
			}
		}
	}

	sort(frameVertexIndices.begin(), frameVertexIndices.end());
	frameVertexIndices.erase(unique(frameVertexIndices.begin(), frameVertexIndices.end()), frameVertexIndices.end());
	loopNum = 0;
	for (auto i : frameVertexIndices) {
		loopNum++;
		frameVertexIndicesMap[i] = loopNum;
		out1 << data[i + firstVertexIndex - 1] << endl;
	}

	sort(frameUVIndices.begin(), frameUVIndices.end());
	frameUVIndices.erase(unique(frameUVIndices.begin(), frameUVIndices.end()), frameUVIndices.end());
	loopNum = 0;
	for (auto i : frameUVIndices) {
		loopNum++;
		frameUVIndicesMap[i] = loopNum;
		out1 << data[i + firstUVIndex - 1] << endl;
	}

	sort(frameNormalIndices.begin(), frameNormalIndices.end());
	frameNormalIndices.erase(unique(frameNormalIndices.begin(), frameNormalIndices.end()), frameNormalIndices.end());
	loopNum = 0;
	for (auto i : frameNormalIndices) {
		loopNum++;
		frameNormalIndicesMap[i] = loopNum;
		out1 << data[i + firstNormalIndex - 1] << endl;
	}

	sort(doorVertexIndices.begin(), doorVertexIndices.end());
	doorVertexIndices.erase(unique(doorVertexIndices.begin(), doorVertexIndices.end()), doorVertexIndices.end());
	loopNum = 0;
	for (auto i : doorVertexIndices) {
		loopNum++;
		doorVertexIndicesMap[i] = loopNum;
		out2 << data[i + firstVertexIndex - 1] << endl;
	}

	sort(doorUVIndices.begin(), doorUVIndices.end());
	doorUVIndices.erase(unique(doorUVIndices.begin(), doorUVIndices.end()), doorUVIndices.end());
	loopNum = 0;
	for (auto i : doorUVIndices) {
		loopNum++;
		doorUVIndicesMap[i] = loopNum;
		out2 << data[i + firstUVIndex - 1] << endl;
	}

	sort(doorNormalIndices.begin(), doorNormalIndices.end());
	doorNormalIndices.erase(unique(doorNormalIndices.begin(), doorNormalIndices.end()), doorNormalIndices.end());
	loopNum = 0;
	for (auto i : doorNormalIndices) {
		loopNum++;
		doorNormalIndicesMap[i] = loopNum;
		out2 << data[i + firstNormalIndex - 1] << endl;
	}

	for (int i = 0; i < frameData.size(); i++) {
		test = frameData[i].substr(0, 2);
		if (test == "us") {
			if (i + 1 < frameData.size()) {
				if (frameData[i + 1].substr(0, 2) != "us") {
					out1 << frameData[i] << endl;
				}
			}	
		}
		if (test == "f ") {
			test = frameData[i].substr(2);
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
						triangle[i] = found;
					}
					if (i == 1 || i == 4 || i == 7) {
						triangle[i] = found;
					}
					if (i == 2 || i == 5 || i == 8) {
						triangle[i] = found;
					}
					i++;
				}
				temp = "";
			}
			line = "f " + to_string(frameVertexIndicesMap[triangle[0]]) + '/' + to_string(frameUVIndicesMap[triangle[1]]) + '/' + to_string(frameNormalIndicesMap[triangle[2]]) + ' '
						+ to_string(frameVertexIndicesMap[triangle[3]]) + '/' + to_string(frameUVIndicesMap[triangle[4]]) + '/' + to_string(frameNormalIndicesMap[triangle[5]]) + ' '
						+ to_string(frameVertexIndicesMap[triangle[6]]) + '/' + to_string(frameUVIndicesMap[triangle[7]]) + '/' + to_string(frameNormalIndicesMap[triangle[8]]);
			out1 << line << endl;
		}
	}

	for (int i = 0; i < doorData.size(); i++) {
		test = doorData[i].substr(0, 2);
		if (test == "us") {
			if (i + 1 < doorData.size()) {
				if (doorData[i + 1].substr(0, 2) != "us") {
					out2 << doorData[i] << endl;
				}
			}
		}
		if (test == "f ") {
			test = doorData[i].substr(2);
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
						triangle[i] = found;
					}
					if (i == 1 || i == 4 || i == 7) {
						triangle[i] = found;
					}
					if (i == 2 || i == 5 || i == 8) {
						triangle[i] = found;
					}
					i++;
				}
				temp = "";
			}
			line = "f " + to_string(doorVertexIndicesMap[triangle[0]]) + '/' + to_string(doorUVIndicesMap[triangle[1]]) + '/' + to_string(doorNormalIndicesMap[triangle[2]]) + ' '
				+ to_string(doorVertexIndicesMap[triangle[3]]) + '/' + to_string(doorUVIndicesMap[triangle[4]]) + '/' + to_string(doorNormalIndicesMap[triangle[5]]) + ' '
				+ to_string(doorVertexIndicesMap[triangle[6]]) + '/' + to_string(doorUVIndicesMap[triangle[7]]) + '/' + to_string(doorNormalIndicesMap[triangle[8]]);
			out2 << line << endl;
		}
	}

	data.clear();
	doorData.clear();
	frameData.clear();

	doorVertexIndices.clear();
	doorUVIndices.clear();
	doorNormalIndices.clear();
	frameVertexIndices.clear();
	frameUVIndices.clear();
	frameNormalIndices.clear();

	doorVertexIndicesMap.clear();
	doorUVIndicesMap.clear();
	doorNormalIndicesMap.clear();
	frameVertexIndicesMap.clear();
	frameUVIndicesMap.clear();
	frameNormalIndicesMap.clear();

	obj.close();
	out1.close();
	out2.close();
}

void BatchSplitMesh() {
	int numFiles = 200;
	int numFolders = 26;

	for (int j = 26; j <= numFolders; j++) {
		for (int i = 1; i <= numFiles; i++) {
			SplitMesh(i, j);
		}
	}
}

void GroupFilesIntoFolders() {
	string objdir = "Z:\\IFC Data\\Inside\\Doors\\Split\\";

	createFolder(objdir + "Groups");

	string line;
	string test;
	string objfile;
	string outfile;
	string typefile = objdir + "Groups\\Types.txt";

	ofstream type(typefile);

	vector<string> data;
	vector<string> preGs;

	bool repeated = false;
	bool first = true;

	int gtype;
	int numFiles = GetNumOfFiles(objdir);
	int numFilesNewDir;

	for (int i = 1; i <= numFiles; i++) {
		objfile = objdir + to_string(i) + ".obj";
		if (_access_s(objfile.c_str(), 0) == 0) { //True if file exists
			ifstream obj(objfile);
			while (!obj.eof()) {
				getline(obj, line);
				data.push_back(line);
				test = line.substr(0, 2);
				if (test == "g ") {
					string object(line.begin(), find(line.begin(), line.end(), ':'));
					gtype = 1;
					if (first) {
						repeated = false;
						first = false;
					}
					else {
						for (auto i : preGs) {
							if (object == i) {
								repeated = true;
								break;
							}
							gtype++;
						}
					}					
					if (!repeated) {
						preGs.push_back(object);
						type << gtype << ' ' << object << endl;
						createFolder(objdir + "Groups\\" + to_string(gtype));
						outfile = objdir + "Groups\\" + to_string(gtype) + "\\1.obj";
					}
					else {
						numFilesNewDir = GetNumOfFiles(objdir + "Groups\\" + to_string(gtype) + "\\") + 1;
						outfile = objdir + "Groups\\" + to_string(gtype) + "\\" + to_string(numFilesNewDir) + ".obj";
						repeated = false;
					}
				}
			}
			ofstream out(outfile);
			for (auto j : data) {
				out << j << endl;
			}
			data.clear();
			out.close();
			obj.close();
		}
	}
	type.close();
}

float GetxExtent(const vector<vector<float>>& vertices) {
	float minx = 0, maxx = 0;
	int loopNum = 0;
	for (auto i : vertices) {
		loopNum++;
		if (loopNum == 1) {
			minx = i[0], maxx = i[0];
		}
		else {
			if (i[0] > maxx) {
				maxx = i[0];
			}
			if (i[0] < minx) {
				minx = i[0];
			}
		}
	}
	return maxx - minx;
}

void PlaceAtOrigin(int fileNum = 0, int folderNum = 0, bool doorA = true, bool singleDoor = false) {
	string objfile;
	string datafile;
	string transformFile;

	if (!singleDoor) {
		if (doorA) {
			if (folderNum == 0) {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1a.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1aOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1aTransform.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "a.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "aOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "aTransform.txt";
				}
			}
			else {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1a.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1aOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1aTransform.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "a.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "aOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "aTransform.txt";
				}
			}
		}
		else {
			if (folderNum == 0) {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1b.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1bOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1bTransform.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "b.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "bOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "bTransform.txt";
				}
			}
			else {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1b.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1bOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1bTransform.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "b.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "bOrigin.obj";
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "bTransform.txt";
				}
			}
		}
	}
	else {
		if (folderNum == 0) {
			if (fileNum == 0) {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1.obj";
				datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1Origin.obj";
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1Transform.txt";
			}
			else {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + ".obj";
				datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "Origin.obj";
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "Transform.txt";
			}
		}
		else {
			if (fileNum == 0) {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1.obj";
				datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1Origin.obj";
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1Transform.txt";
			}
			else {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + ".obj";
				datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "Origin.obj";
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "Transform.txt";
			}
		}
	}
	

	if (_access_s(objfile.c_str(), 0) != 0) { //True if file does not exist
		return;
	}

	ifstream obj(objfile);
	ofstream data(datafile);
	ofstream tran(transformFile);

	string line;

	int vertex = 0;
	int validVertex = 0;
	double triangle[3];
	string a = " ";
	string test = line.substr(0, 2);
	string sub;
	vector<string> lines;

	double x1 = 0.0f;
	double x2 = 0.0f;

	double y1 = 0.0f;
	double y2 = 0.0f;

	double z1 = 0.0f;
	double z2 = 0.0f;

	bool first = true;

	while (!obj.eof()) {
		getline(obj, line);
		lines.push_back(line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			double found;
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

	double midx = (x1 + x2) / 2.0f;
	double midy = (y1 + y2) / 2.0f;
	double midz = (z1 + z2) / 2.0f;

	for (auto i : lines) {
		string replace = i.substr(0, 2);
		if (replace == "v ") {
			sub = i.substr(2);
			double found;
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

	tran << to_string(midx * -1.1f) << endl;
	tran << to_string(midy * 1.1f) << endl;
	tran << to_string(midz * 1.1f) << endl;

	tran.close();
	data.close();
	obj.close();
}

void FindTransformAngle(int fileNum = 0, int folderNum = 0, bool doorA = true, bool singleDoor = false) {
	string objfile;
	string datafile;
	string transformFile1;
	string transformFile2;

	if (!singleDoor) {
		if (doorA) {
			if (folderNum == 0) {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1aOrigin.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1aTransformed.obj";
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1aTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1aTransform1.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "aOrigin.obj";
					if (fileNum == 1) {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor" + to_string(fileNum) + "aTransformed.obj";
					}
					else {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "aTransformed.obj";
					}
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "aTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "aTransform1.txt";
				}
			}
			else {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1aOrigin.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1aTransformed.obj";
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1aTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1aTransform1.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "aOrigin.obj";
					if (fileNum == 1) {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor" + to_string(fileNum) + "aTransformed.obj";
					}
					else {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "aTransformed.obj";
					}
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "aTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "aTransform1.txt";
				}
			}
		}
		else {
			if (folderNum == 0) {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1bOrigin.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1bTransformed.obj";
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1bTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1bTransform1.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "bOrigin.obj";
					if (fileNum == 1) {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor" + to_string(fileNum) + "bTransformed.obj";
					}
					else {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "bTransformed.obj";
					}
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "bTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "bTransform1.txt";
				}
			}
			else {
				if (fileNum == 0) {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1bOrigin.obj";
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1bTransformed.obj";
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1bTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1bTransform1.txt";
				}
				else {
					objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "bOrigin.obj";
					if (fileNum == 1) {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor" + to_string(fileNum) + "bTransformed.obj";
					}
					else {
						datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "bTransformed.obj";
					}
					transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "bTransform.txt";
					transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "bTransform1.txt";
				}
			}
		}
	}
	else{
		if (folderNum == 0) {
			if (fileNum == 0) {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1Origin.obj";
				datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1Transformed.obj";
				transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1Transform.txt";
				transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door1Transform1.txt";
			}
			else {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "Origin.obj";
				if (fileNum == 1) {
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor" + to_string(fileNum) + "Transformed.obj";
				}
				else {
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "Transformed.obj";
				}
				transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "Transform.txt";
				transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "Transform1.txt";
			}
		}
		else {
			if (fileNum == 0) {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1Origin.obj";
				datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1Transformed.obj";
				transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1Transform.txt";
				transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door1Transform1.txt";
			}
			else {
				objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "Origin.obj";
				if (fileNum == 1) {
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor" + to_string(fileNum) + "Transformed.obj";
				}
				else {
					datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "Transformed.obj";
				}
				transformFile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "Transform.txt";
				transformFile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "Transform1.txt";
			}
		}
	}
	
	if (_access_s(objfile.c_str(), 0) != 0 || _access_s(transformFile1.c_str(), 0) != 0) { //True if file does not exist
		return;
	}

	ifstream transin(transformFile1);

	string transform[3];
	string line;

	int loopNum = 0;
	do {
		getline(transin, line);
		transform[loopNum] = line;
		loopNum++;
	} while (loopNum < 3);

	transin.close();

	ifstream obj(objfile);
	ofstream data(datafile);
	ofstream transout(transformFile2);

	vector<string> lines;
	vector<float> vertex;
	vector<float> rotVertex;
	vector<float> normal;
	vector<vector<float>> vertices;
	vector<vector<float>> rotVertices;
	vector<vector<float>> normals;
		
	string test;
	string sub;

	float theta;
	float bestTheta;
	float bestTheta2;
	float xExtent;
	float minxExtent = 9999999.9f;

	bool match = false;

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
					vertex.push_back(found);	
					rotVertex.push_back(found);
				}
				temp = "";
			}
			vertices.push_back(vertex);
			rotVertices.push_back(rotVertex);
			vertex.clear();
			rotVertex.clear();
		}
		if (test == "vn") {
			sub = line.substr(2);
			float found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					normal.push_back(found);
				}
				temp = "";
			}
			normals.push_back(normal);
			normal.clear();
		}
	}

	for (int a = 0; a <= 180; a++) {
		int j = 0;
		theta = a * 0.017453292f;
		for (auto i : vertices) {
			rotVertices[j][0] = cos(theta) * i[0] + sin(theta) * i[2];
			rotVertices[j][2] = -sin(theta) * i[0] + cos(theta) * i[2];
			j++;
		}
		xExtent = GetxExtent(rotVertices);

		if (xExtent < minxExtent) {
			minxExtent = xExtent;
			bestTheta = theta;
		}
	}

	for (int a = 0; a <= 2000; a++) {
		int j = 0;
		theta = bestTheta + (a - 1000) * 0.0000017453292f;
		for (auto i : vertices) {
			rotVertices[j][0] = cos(theta) * i[0] + sin(theta) * i[2];			
			rotVertices[j][2] = -sin(theta) * i[0] + cos(theta) * i[2];
			j++;
		}
		xExtent = GetxExtent(rotVertices);

		if (xExtent < minxExtent) {
			minxExtent = xExtent;
			bestTheta2 = theta;
		}
	}

	for (auto i : transform) {
		transout << i << endl;
	}
	transout << to_string(bestTheta2 * 57.2957795f) << endl;

	float x, z;
	for (auto& i : vertices) {
		x = cos(bestTheta2) * i[0] + sin(bestTheta2) * i[2];		
		z = -sin(bestTheta2) * i[0] + cos(bestTheta2) * i[2];
		i[0] = x;
		i[2] = z;
	}
	for (auto& i : normals) {
		x = cos(bestTheta2) * i[0] + sin(bestTheta2) * i[2];
		z = -sin(bestTheta2) * i[0] + cos(bestTheta2) * i[2];
		i[0] = x;
		i[2] = z;
	}

	int j = 0;
	int k = 0;
	for (auto i : lines) {
		test = i.substr(0, 2);
		if (test == "v ") {
			line = "v " + to_string(vertices[j][0]) + ' ' + to_string(vertices[j][1]) + ' ' + to_string(vertices[j][2]);
			data << line << endl;
			j++;
		}
		else if (test == "vn") {
			line = "vn " + to_string(normals[k][0]) + ' ' + to_string(normals[k][1]) + ' ' + to_string(normals[k][2]);
			data << line << endl;
			k++;
		}
		else {
			data << i << endl;
		}
	}

	lines.clear();
	vertex.clear();
	rotVertex.clear();
	normal.clear();
	vertices.clear();
	rotVertices.clear();
	normals.clear();

	transout.close();
	obj.close();
	data.close();
}

void MakePrefabs(int fileNum = 0, int folderNum = 0, bool doorA = true, bool singleDoor = false) {
	string infile1;
	string infile2;
	string outfile;

	if (!singleDoor) {
		if (doorA) {
			if (folderNum == 0) {
				createFolder("Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs");
				if (fileNum == 0) {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1aTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door2aTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs\\Door2aTransformed1.PREFAB";
				}
				else {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1aTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "aTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs\\Door" + to_string(fileNum) + "aTransformed1.PREFAB";
				}
			}
			else {
				createFolder("Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs");
				if (fileNum == 0) {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1aTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door2aTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs\\Door2aTransformed1.PREFAB";
				}
				else {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1aTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "aTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs\\Door" + to_string(fileNum) + "aTransformed1.PREFAB";
				}
			}
		}
		else {
			if (folderNum == 0) {
				createFolder("Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs");
				if (fileNum == 0) {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1bTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door2bTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs\\Door2bTransformed1.PREFAB";
				}
				else {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1bTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "bTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs\\Door" + to_string(fileNum) + "bTransformed1.PREFAB";
				}
			}
			else {
				createFolder("Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs");
				if (fileNum == 0) {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1bTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door2bTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs\\Door2bTransformed1.PREFAB";
				}
				else {
					infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1bTransformed1.PREFAB";
					infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "bTransform2.txt";
					outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs\\Door" + to_string(fileNum) + "bTransformed1.PREFAB";
				}
			}
		}
	}
	else {
		if (folderNum == 0) {
			createFolder("Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs");
			if (fileNum == 0) {
				infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1Transformed1.PREFAB";
				infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door2Transform2.txt";
				outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs\\Door2Transformed1.PREFAB";
			}
			else {
				infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\MainDoor1Transformed1.PREFAB";
				infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Door" + to_string(fileNum) + "Transform2.txt";
				outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\1\\Prefabs\\Door" + to_string(fileNum) + "Transformed1.PREFAB";
			}
		}
		else {
			createFolder("Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs");
			if (fileNum == 0) {
				infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1Transformed1.PREFAB";
				infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door2Transform2.txt";
				outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs\\Door2Transformed1.PREFAB";
			}
			else {
				infile1 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1Transformed1.PREFAB";
				infile2 = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(fileNum) + "Transform2.txt";
				outfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Prefabs\\Door" + to_string(fileNum) + "Transformed1.PREFAB";
			}
		}
	}

	if (_access_s(infile1.c_str(), 0) != 0 || _access_s(infile2.c_str(), 0) != 0) { //True if file does not exist
		return;
	}

	ifstream in2(infile2);
	ofstream out(outfile);

	string line;
	string test;

	string transform[4];

	int loopNum = 0;
	do {
		getline(in2, line);
		transform[loopNum] = line;
		loopNum++;
	} while (loopNum < 4);

	float angle;
	stringstream(transform[3]) >> angle;
	float halfangle = 0.00872665f * angle;
	in2.close();

	ifstream in1(infile1);

	bool first = true;
	while (!in1.eof()) {
		getline(in1, line);
		test = line.substr(0, 15);
		if (test == "  m_LocalRotati" && first) {
			out << "  m_LocalRotation: {x: 0, y: " + to_string(sin(halfangle)) + ", z: 0, w: " + to_string(cos(halfangle)) + "}" << endl;
		}
		else if (test == "  m_LocalPositi" && first) {
			out << "  m_LocalPosition: {x: " + transform[0] + ", y: " + transform[1] + ", z: " + transform[2] + "}" << endl;
		}
		else if (test == "  m_LocalScale:" && first) {
			out << "  m_LocalScale: {x: 110, y: 110, z: 110}" << endl;
			first = false;
		}
		else {
			out << line << endl;
		}
	}

	in1.close();
	out.close();
}

void ListginFileList() {
	string line;
	string test;

	string objdir = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\28\\";
	string datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\28\\Listg.txt";

	ofstream data(datafile);

	int numFiles = GetNumOfFiles(objdir);	

	int objNum = 0;

	for (int i = 1; i <= numFiles; i++) {
		string objfile = objdir + to_string(i) + ".obj";
		if (_access_s(objfile.c_str(), 0) == 0) { //True if file exists
			ifstream obj(objfile);
			while (!obj.eof()) {
				getline(obj, line);
				test = line.substr(0, 2);
				if (test == "g ") {
					objNum++;
					data << objNum << ", " << line << endl;
					break;
				}			
			}
			obj.close();
		}
	}
	data.close();
}

void BatchFindTransform(int folderNum = 28, bool doorA = 0, bool singleDoor = 1) {
	int numFiles = 200;
	int numFolders = folderNum;

	for (int j = folderNum; j <= numFolders; j++) {
		for (int i = 1; i <= numFiles; i++) {
			PlaceAtOrigin(i, j, doorA, singleDoor);
			FindTransformAngle(i, j, doorA, singleDoor);
		}
	}
}

void BatchMakePrefabs(int folderNum = 28, bool doorA = 0, bool singleDoor = 1) {
	int numFiles = 200;
	int numFolders = folderNum;

	for (int j = folderNum; j <= numFolders; j++) {
		for (int i = 1; i <= numFiles; i++) {
			MakePrefabs(i, j, doorA, singleDoor);
		}
	}
}

void FixDoorHinges(int folderNum = 28, bool doorA = 0, bool alt = 0, bool singleDoor = 1) {
	int fileNum = 150;
	string objfile;
	string datafile;
	string transformFile;

	if (!singleDoor) {
		if (doorA) {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1aTransformed.obj";
			datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1aTransformed1.obj";
		}
		else {
			objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1bTransformed.obj";
			datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1bTransformed1.obj";
		}
	}
	else {
		objfile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1Transformed.obj";
		datafile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\MainDoor1Transformed1.obj";
	}

	if (_access_s(objfile.c_str(), 0) != 0) { //True if file does not exist
		return;
	}

	ifstream obj(objfile);
	ofstream data(datafile);

	string line;
	string test;
	string sub;

	double vertex[3];
	double vertexZ = 0.0f;;
	double maxZ = 0.0f;
	vector<string> lines;

	while (!obj.eof()) {
		getline(obj, line);
		lines.push_back(line);
		test = line.substr(0, 2);
		if (test == "v ") {
			sub = line.substr(2);
			double found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					if (i == 2) {
						vertexZ = found;
					}
					i++;
				}
				temp = "";
			}
			if (vertexZ > maxZ) {
				maxZ = vertexZ;
			}
		}
	}

	for (auto i : lines) {
		string replace = i.substr(0, 2);
		if (replace == "v ") {
			sub = i.substr(2);
			double found;
			int i = 0;
			stringstream ss;
			ss << sub;
			string temp;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					vertex[i] = found;
					i++;
				}
				temp = "";
			}
			if (!alt) {
				if (!singleDoor) {
					if (doorA) {
						sub = "v " + to_string(vertex[0]) + " " + to_string(vertex[1]) + " " + to_string(vertex[2] - maxZ);
					}
					else {
						sub = "v " + to_string(vertex[0]) + " " + to_string(vertex[1]) + " " + to_string(vertex[2] + maxZ);
					}
				}
				else {
					sub = "v " + to_string(vertex[0]) + " " + to_string(vertex[1]) + " " + to_string(vertex[2] - maxZ);
				}			
			}
			else {
				if (!singleDoor) {
					if (doorA) {
						sub = "v " + to_string(vertex[0]) + " " + to_string(vertex[1]) + " " + to_string(vertex[2] + maxZ);
					}
					else {
						sub = "v " + to_string(vertex[0]) + " " + to_string(vertex[1]) + " " + to_string(vertex[2] - maxZ);
					}
				}
				else {
					sub = "v " + to_string(vertex[0]) + " " + to_string(vertex[1]) + " " + to_string(vertex[2] + maxZ);
				}
			}			
			data << sub << endl;
		}
		else {
			data << i << endl;
		}
	}

	lines.clear();

	data.close();
	obj.close();

	string transform[4];

	for (int i = 1; i < fileNum; i++) {
		if (!singleDoor) {
			if (doorA) {
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "aTransform1.txt";
			}
			else {
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "bTransform1.txt";
			}
		}
		else {
			transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "Transform1.txt";
		}
		
		if (_access_s(transformFile.c_str(), 0) != 0) { //True if file does not exist
			continue;
		}
		ifstream tran(transformFile);
		for (auto& j : transform) {
			getline(tran, line);
			j = line;
		}
		tran.close();

		double fixedX;
		double fixedZ;
		float angle;
		stringstream(transform[0]) >> fixedX;
		stringstream(transform[2]) >> fixedZ;
		stringstream(transform[3]) >> angle;

		if (!alt) {
			if (!singleDoor) {
				if (doorA) {
					fixedX += maxZ * 1.1f * sin(angle * 0.017453292f);
					fixedZ += maxZ * 1.1f * cos(angle * 0.017453292f);
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "aTransform2.txt";
				}
				else {
					fixedX -= maxZ * 1.1f * sin(angle * 0.017453292f);
					fixedZ -= maxZ * 1.1f * cos(angle * 0.017453292f);
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "bTransform2.txt";
				}
			}
			else {
				fixedX += maxZ * 1.1f * sin(angle * 0.017453292f);
				fixedZ += maxZ * 1.1f * cos(angle * 0.017453292f);
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "Transform2.txt";
			}			
		}
		else {
			if (!singleDoor) {
				if (doorA) {
					fixedX -= maxZ * 1.1f * sin(angle * 0.017453292f);
					fixedZ -= maxZ * 1.1f * cos(angle * 0.017453292f);
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "aTransform2.txt";
				}
				else {
					fixedX += maxZ * 1.1f * sin(angle * 0.017453292f);
					fixedZ += maxZ * 1.1f * cos(angle * 0.017453292f);
					transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "bTransform2.txt";
				}
			}
			else {
				fixedX -= maxZ * 1.1f * sin(angle * 0.017453292f);
				fixedZ -= maxZ * 1.1f * cos(angle * 0.017453292f);
				transformFile = "Z:\\IFC Data\\Inside\\Doors\\Split\\Groups\\" + to_string(folderNum) + "\\Door" + to_string(i) + "Transform2.txt";
			}			
		}

		ofstream fixedtran(transformFile);
		fixedtran << to_string(fixedX) << endl;
		fixedtran << transform[1] << endl;
		fixedtran << to_string(fixedZ) << endl;
		fixedtran << transform[3] << endl;
		fixedtran.close();
	}
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
		cout << "35. Single file group g \n";
		cout << "36. Split all objects into individual OBJ's\n";
		cout << "37. Replace material\n";
		cout << "38. List materials\n";
		cout << "39. Replace materials\n";
		cout << "40. Divide materials\n";
		cout << "41. Move object to individual OBJ\n";
		cout << "42. Translate objects\n";
		cout << "43. Fix coffee machine glitch\n";
		cout << "44. Group g with batch process\n";
		cout << "45. Find object in list of OBJ files\n";
		cout << "46. Split mesh into separate obj files\n";
		cout << "47. Batch process splitting mesh into separate obj files\n";
		cout << "48. Group files into folders\n";
		cout << "49. Find transform angle\n";
		cout << "50. Batch process finding transform\n";
		cout << "51. Make prefabs\n";
		cout << "52. Batch process making prefabs\n";
		cout << "53. Fix hinges\n";
		cout << "54. List g in list of files\n";
		cout << "55. Terminate the program\n";
		cout << "********************************************************************************************************************\n";
		cin >> x;
		fixInput(x, s, 1, 55, "Invalid input! Please enter an integer from the above menu: ");

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
			system("cls");
			SingleFileGroupg();
			system("pause");
			system("cls");
			break;
		case 36:
			system("cls");
			SplitIntoOneOBJPerObject();
			system("pause");
			system("cls");
			break;
		case 37:
			system("cls");
			Replacemtl();
			system("pause");
			system("cls");
			break;
		case 38:
			system("cls");
			ListMaterials();
			system("pause");
			system("cls");
			break;
		case 39:
			system("cls");
			ReplaceMaterials();
			system("pause");
			system("cls");
			break;
		case 40:
			system("cls");
			DivideMaterials();
			system("pause");
			system("cls");
			break;
		case 41:
			system("cls");
			MoveObjectToIndividualOBJ();
			system("pause");
			system("cls");
			break;
		case 42:
			system("cls");
			TranslateObjectsNew();
			system("pause");
			system("cls");
			break;
		case 43:
			system("cls");
			FixCoffeeMachineGlitch();
			system("pause");
			system("cls");
			break;
		case 44:
			system("cls");
			BatchProcessSingleFileGroupg();
			system("pause");
			system("cls");
			break;		
		case 45:
			system("cls");
			FindObjectinOBJList();
			system("pause");
			system("cls");
			break;	
		case 46:
			system("cls");
			SplitMesh();
			system("pause");
			system("cls");
			break;	
		case 47:
			system("cls");
			BatchSplitMesh();
			system("pause");
			system("cls");
			break;
		case 48:
			system("cls");
			GroupFilesIntoFolders();
			system("pause");
			system("cls");
			break;		
		case 49:
			system("cls");
			FindTransformAngle();
			system("pause");
			system("cls");
			break;	
		case 50:
			system("cls");
			BatchFindTransform();
			system("pause");
			system("cls");
			break;	
		case 51:
			system("cls");
			MakePrefabs();
			system("pause");
			system("cls");
			break;	
		case 52:
			system("cls");
			BatchMakePrefabs();
			system("pause");
			system("cls");
			break;	
		case 53:
			system("cls");
			FixDoorHinges();
			system("pause");
			system("cls");
			break;		
		case 54:
			system("cls");
			ListginFileList();
			system("pause");
			system("cls");
			break;			
		case 55:
			break;
		}  //No default case is required due to the above fixInput function
	} while (s != 55);
	return 0;
}