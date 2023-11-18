#include "stdafx.h"
#include "Set.h"

// private methods:
void Set::makeRandomNumbers(int size)
{	
	this->unsortedSet.clear();

	for (int i = 0; i < size; i++)
		this->unsortedSet.push_back(i + 1);

	srand(static_cast<unsigned>(time(0)));

	for (auto i = 0; i < this->unsortedSet.size(); i++)
	{
		int a = rand() % this->unsortedSet.size();
		int b = rand() % this->unsortedSet.size();
		std::swap(this->unsortedSet[a], this->unsortedSet[b]);
	}
}

void Set::makeRectanglesUnsorted()
{
	this->rectangles.clear();

	sf::RectangleShape temp;
	temp.setFillColor(this->rectColor);
	
	for (auto i = 0; i < this->unsortedSet.size(); i++)
	{
		temp.setOrigin(0.f, this->unsortedSet[i] * this->rectMinHeight);
		temp.setSize(
			sf::Vector2f(
				this->rectWidth, 
				this->unsortedSet[i] * this->rectMinHeight
			)
		);
		temp.setPosition(
			sf::Vector2f(
				i * this->rectWidth + (static_cast<float>(this->windowSize.x) - static_cast<float>(this->windowSize.y)) / 2.f,
				static_cast<float>(this->windowSize.y)
			)
		);

		this->rectangles.push_back(temp);
	}
}

void Set::makePresort()
{
	this->swaps.clear();
	this->colored.clear();

	if (this->sortType == "BUBBLE")
		this->makeBubblePresort();

	else if (this->sortType == "SELECTION")
		this->makeSelectionPresort();

	else if (this->sortType == "HEAP")
		this->makeHeapPresort();

	else if (this->sortType == "QUICK")
	{
		std::vector<unsigned short> temp{ this->unsortedSet };
		this->makeQuickPresort(0, this->unsortedSet.size() - 1, temp);
	}
}

// presort methods:
void Set::makeBubblePresort()
{
	std::vector<unsigned short> temp{ this->unsortedSet };

	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 1; j < temp.size() - i; j++)
		{
			this->swaps.push_back(std::make_pair(-1, -1));
			
			if (temp[j - 1] > temp[j])
			{
				this->swaps[this->swaps.size() - 1] = std::make_pair(j - 1, j);
				std::swap(temp[j - 1], temp[j]);
			}

			this->colored.push_back(std::make_pair(j - 1, j));
		}
	}
}

void Set::makeSelectionPresort()
{
	std::vector<unsigned short> temp{ this->unsortedSet };

	for (int i = 0; i < temp.size(); i++)
	{
		int m = i;

		for (int j = i + 1; j < temp.size(); j++)
		{
			this->swaps.push_back(std::make_pair(-1, -1));
			
			if (temp[j] < temp[m])
				m = j;
			
			this->colored.push_back(std::make_pair(m, j));
		}

		std::swap(temp[m], temp[i]);
		this->swaps.push_back(std::make_pair(m, i));
		this->colored.push_back(std::make_pair(m, i));
	}
}

void Set::makeHeapPresort()
{
	std::vector<unsigned short> temp{ this->unsortedSet };

	for (int i = temp.size() / 2 - 1; i >= 0; i--)
		heapify(temp.size(), i, temp);

	for (int i = temp.size() - 1; i >= 0; i--)
	{
		std::swap(temp[0], temp[i]);
		this->swaps.push_back(std::make_pair(0, i));
		this->colored.push_back(std::make_pair(0, i));
		
		heapify(i, 0, temp);
	}
}

void Set::heapify(int n, int i, std::vector<unsigned short>& v)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && v[left] > v[largest])
		largest = left;

	if (right < n && v[right] > v[largest])
		largest = right;

	if (largest != i) 
	{
		std::swap(v[i], v[largest]);
		this->swaps.push_back(std::make_pair(i, largest));
		this->colored.push_back(std::make_pair(i, largest));
		heapify(n, largest, v);
	}
}

void Set::makeQuickPresort(int start, int end, std::vector<unsigned short>& v)
{
	if (start < end)
	{
		int index = partition(start, end, v);
		makeQuickPresort(start, index - 1, v);
		makeQuickPresort(index + 1, end, v);
	}
}

int Set::partition(int start, int end, std::vector<unsigned short>& v)
{
	int pivotIndex = start;
	unsigned short pivotValue = v[end];

	for (int i = start; i < end; i++)
	{
		if (v[i] < pivotValue)
		{
			if (i != pivotIndex)
			{
				std::swap(v[i], v[pivotIndex]);
				this->swaps.push_back(std::make_pair(i, pivotIndex));
				this->colored.push_back(std::make_pair(i, pivotIndex));
			}

			pivotIndex++;
		}
	}

	if (pivotIndex != end)
	{
		std::swap(v[pivotIndex], v[end]);
		this->swaps.push_back(std::make_pair(pivotIndex, end));
		this->colored.push_back(std::make_pair(pivotIndex, end));
	}

	return pivotIndex;
}

// constructor:
Set::Set(unsigned short size, sf::Vector2u windowSize, sf::Color rectColor)
{
	this->sorted = false;
	this->sortType = "HEAP";
	this->step = 0;
	this->rectWidth = static_cast<float>(windowSize.y) / size;
	this->rectMinHeight = static_cast<float>(windowSize.y) / size;
	this->rectColor = rectColor;
	this->windowSize = windowSize;	
	this->makeRandomNumbers(size);
	this->makeRectanglesUnsorted();
	this->makePresort();
}

// accessors:

const std::string& Set::getSortType() const
{
	return this->sortType;
}

int Set::getStep() const
{
	return this->step;
}

// predicates:
bool Set::isSorted() const
{
	return this->sorted;
}

// modifiers:
void Set::setSortType(const std::string& sortType)
{
	this->sortType = sortType;
	this->makePresort();
	this->restart();
}

// other methods:
void Set::restart()
{
	this->step = 0;
	this->sorted = false;
	this->makeRectanglesUnsorted();
}

void Set::update()
{
	if (this->step != this->swaps.size())
	{
		if (this->swaps[step].first != -1)
		{
			sf::RectangleShape temp;
			temp.setSize(this->rectangles[this->swaps[step].first].getSize());
			temp.setOrigin(this->rectangles[this->swaps[step].first].getOrigin());
			
			this->rectangles[this->swaps[step].first].setSize(this->rectangles[this->swaps[step].second].getSize());
			this->rectangles[this->swaps[step].first].setOrigin(this->rectangles[this->swaps[step].second].getOrigin());

			this->rectangles[this->swaps[step].second].setSize(temp.getSize());
			this->rectangles[this->swaps[step].second].setOrigin(temp.getOrigin());
		}

		if (step > 0)
		{
			this->rectangles[this->colored[step - 1].first].setFillColor(this->rectColor);
			this->rectangles[this->colored[step - 1].second].setFillColor(this->rectColor);
		}

		this->rectangles[this->colored[step].first].setFillColor(sf::Color::Red);
		this->rectangles[this->colored[step].second].setFillColor(sf::Color::Red);

		this->step++;

		if (this->step == this->swaps.size())
		{
			this->sorted = true;

			this->rectangles[this->colored[this->colored.size() - 1].first].setFillColor(this->rectColor);
			this->rectangles[this->colored[this->colored.size() - 1].second].setFillColor(this->rectColor);
		}
	}
}

void Set::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->rectangles.size(); ++i)
		target.draw(this->rectangles[i]);
}
