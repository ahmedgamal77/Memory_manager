

#include "pch.h"
#include <iostream>
#include <string>
#include<vector>
#include <algorithm>
using namespace std;

struct segment {
	string name;//name of the segment
	string parent;//the name of the process that the segment Belongs to
	bool hole; // true if this segment is a hole (free space)
	int address;
	int size;

	segment(int ad, int s) {
		//constructor to use at adding a new hole
		address = ad;
		size = s;
		hole = true;
		
	}
	segment(string n, string p, int ad, int s) {
		//constructor to use at adding new data segmant 
		name = n;
		parent = p;
		address = ad;
		size = s;
		hole = false;
	}



};
void add_holes(vector<segment>&v,vector<int> adress, vector<int> size, int total);
bool first_fit_alloc(vector<segment>&v, vector<string>names, vector<int>size, string parent);
bool best_fit_alloc(vector<segment>&v, vector<string>names, vector<int>size, string parent);
void de_alloc(vector<segment>&v, string proc);
vector<segment> seg_table(vector<segment>&v, string proc);




int main()
{	
	
	vector<segment> v;
	v.push_back(segment(0, 10));//to add hole (adress , size )
	v.push_back(segment("segment1", "parent1", 1, 25));//to add data segment (the name of the seg , its parent , adress , size )
	

	
	
}
void add_holes(vector<segment>&v, vector<int> adress, vector<int> size, int total) {
	/*function that takes two vectors to put the holes in the memory vector
	one contatins the starting addresses of each hole
	the second contating the size of each hole
	the memory vector is the first parameter
	it has to update the memory vector with the holes
	and add data segments to the places already taken*/
	int temp;
	int holes_no = (adress.size());
	//sorting holes according to the adress
	for (int i = 0; i < holes_no; i++) {
		for (int j = i + 1; j < holes_no; j++) {
			if (adress[j] < adress[i]) {
				temp = adress[i];
				adress[i] = adress[j];
				adress[j] = temp;
				temp = size[i];
				size[i] = size[j];
				size[j] = temp;
			}
		}
	}
	//check if the start is data
	if (adress[0] != 0)
	{

		v.push_back(segment("segment0", "parent0", 0, adress[0]));
		v.push_back(segment(adress[0], size[0]));
		for (int i = 1; i < holes_no; i++) {
			v.push_back(segment("segment0", "parent0", adress[i - 1] + size[i - 1], adress[i] - adress[i - 1] - size[i - 1]));
			v.push_back(segment(adress[i], size[i]));


		}
		//add data at the end if last hole doesn't end at the end of the memory
		if ((adress[holes_no - 1] + size[holes_no - 1]) < total) {

			v.push_back(segment("segment0", "parent0", adress[holes_no - 1] + size[holes_no - 1], total - adress[holes_no - 1] - size[holes_no - 1]));

		}

	}
	//check if the start is hole
	else {

		v.push_back(segment(adress[0], size[0]));
		for (int i = 1; i < holes_no; i++) {
			v.push_back(segment("segment0", "parent0", adress[i - 1] + size[i - 1], adress[i] - adress[i - 1] - size[i - 1]));
			v.push_back(segment(adress[i], size[i]));
		}
		//add data at the end if last hole doesn't end at the end of the memory
		if ((adress[holes_no - 1] + size[holes_no - 1]) < total) {

			v.push_back(segment("segment0", "parent0", adress[holes_no - 1] + size[holes_no - 1], total - adress[holes_no - 1] - size[holes_no - 1]));

		}

	}

}
bool first_fit_alloc(vector<segment>&v, vector<string>names, vector<int>size, string parent){
	/*function that takes the process name (parent) and two vectors 
	first vector contains the names of the segments that belongs to that process
	the second contains their sizes 
	the memory vector is the first parameter
	it has to search at the memory vector for the first place to fit them 
	the function updates the memory vector return true if it find places to all segments
	the function return false if there is a segment does't fit in the memory and don't update the memory vector*/
	return true;
}
bool best_fit_alloc(vector<segment>&v, vector<string>names, vector<int>size, string parent){
	/*function that takes the process name (parent) and two vectors
	first vector contains the names of the segments that belongs to that process
	the second contains their sizes
	the memory vector is the first parameter
	it has to search at the memory vector for the best place to fit them (a hole with size same or near to the size of the segmen)
	the function updates the memory vector return true if it find places to all segments
	the function return false if there is a segment doesn't fit in the memory and don't update the memory vector*/
	return true;

}
void de_alloc(vector<segment>&v, string proc) {
	/*function that takes a process name then find all the segments for that process and remove them from the memory
	then check if there is a hole before or after it then it should increase the hole size
	if not then it add a new hole to the memory vector
	the memory vector is the first parameter*/
	for (int i = 0; i < v.size(); i++) {
		if (v[i].hole)
			continue;
		if (v[i].parent == proc) {
			if (v[i - 1].hole) {
				v[i - 1].size += v[i].size;
				v.erase(v.begin() + i);
				i--;
			}
			else if (v[i + 1].hole) {
				v[i + 1].size += v[i].size;
				v[i + 1].address = v[i].address;
				v.erase(v.begin() + i);
				i--;
			}
			else {
				v[i].hole = true;
				v[i].parent = "";
				v[i].name = "";
			}

		}
	}
	for (int i = 0; i < v.size(); i++) {
		if (!v[i].hole)
			continue;
		if (v[i].hole) {
			if (i + 1 != v.size()) {
				if (v[i + 1].hole) {
					v[i].size += v[i + 1].size;
					v.erase(v.begin() + i + 1);
					i--;
				}
			}
		}
	}
}
vector<segment> seg_table(vector<segment>&v, string proc) {

	/*function that takes a process name then find all the segments for that process and add them to a vector of segments and return that vector
	the memory vector is the first parameter*/

	vector<segment> seg(v.size());

	copy_if(v.begin(), v.end(), seg.begin(), [proc](const segment &s)
	{
		return s.parent == proc;

	});

	return seg;

}