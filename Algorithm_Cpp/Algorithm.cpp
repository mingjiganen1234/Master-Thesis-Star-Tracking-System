#include "Algorithm.h"

StarPattern getStarPattern(std::vector<Star> &starList,int FOV) {
	StarPattern starPattern;

	//Calculate the star distance to starRef
	Star starRef = starList.front();
	std::pop_heap(starList.begin(), starList.end(), [](const Star &a, const Star &b) {return a.starDistance2Centre > b.starDistance2Centre; });
	starList.pop_back();

	for (int i = 0; i < starList.size(); ++i) {
		starList[i].starDistance2StarRef = sqrt((starRef.X - starList[i].X)*(starRef.X - starList[i].X) + (starRef.Y - starList[i].Y)*(starRef.Y - starList[i].Y));
	}
	std::make_heap(starList.begin(), starList.end(), [](const Star &a, const Star &b) {return a.starDistance2StarRef > b.starDistance2StarRef; });

	//Traverse through the sorted list to get star pattern
	int count = 0;
	float distance[3] = { 0,0,0 };

	while (!starList.empty()) {
		if (starList.front().starDistance2StarRef > FOV / 2) break;
		if (count < 3) distance[count] = starList.front().starDistance2StarRef;

		std::pop_heap(starList.begin(), starList.end(), [](const Star &a, const Star &b) {return a.starDistance2StarRef > b.starDistance2StarRef; });
		starList.pop_back();
		++count;
	}
		
	//Update Starpattern
	starPattern.N = count;
	starPattern.d1 = distance[0];
	starPattern.d2 = distance[1];
	starPattern.d3 = distance[2];

	return starPattern;
}

