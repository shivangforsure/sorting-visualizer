#pragma once

class Set
{
private:
	bool sorted;
	std::string sortType;

	sf::Vector2u windowSize;

	std::vector<unsigned short> unsortedSet;

	std::vector<std::pair<short, short> > swaps;

	std::vector<std::pair<short, short> > colored;


	unsigned step; 


	std::vector<sf::RectangleShape> rectangles;


	float rectWidth;
	float rectMinHeight;

	sf::Color rectColor;

	// private methods:
	void makeRandomNumbers(int size);
	void makeRectanglesUnsorted();
	void makePresort();

	// presort methods:
	void makeBubblePresort();

	void makeSelectionPresort();

	void makeHeapPresort();
	void heapify(int n, int i, std::vector<unsigned short>& v);

	void makeQuickPresort(int start, int end, std::vector<unsigned short>& v);
	int partition(int start, int end, std::vector<unsigned short>& v);

public:
	// constructor:
	Set(unsigned short size, sf::Vector2u windowSize, sf::Color rectColor);

	// accessors:
	const std::string& getSortType() const; 
	int getStep() const; 

	// predicates:
	bool isSorted() const;

	// modifiers:
	void setSortType(const std::string& sortType); 
	// other methods:
	void restart(); 
	void update();
	void render(sf::RenderTarget& target);
};
