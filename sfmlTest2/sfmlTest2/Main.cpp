#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ranges>
#include <algorithm>
#include <chrono>
#include <thread>

int width = 800; // global var
int height = 600;
double speed_; // how fast the rectangles move

void printVec(const std::vector<int>& vec) {
	for (auto num : vec) {
		std::cout.width(6);
		std::cout << num << " || ";
	}
	std::cout << std::endl;
}

void changeRectHeight(int index, int new_value, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	// used for merge sort only
	// similiar to swapRect func, but will change heights of rectangles, instead of moving them
	// first rect's height is set  equal to 2nd rect's height
	//sf::Clock clock;
	int delay = 3000 / rectangles.size();
	rectangles.at(index).setFillColor(sf::Color(0, 250, 0));
	//rectangles.at(second).setFillColor(sf::Color(200, 0, 0));

	auto rect_width = rectangles.at(index).getSize().x;
	auto new_rect_height = new_value * 5; //rectangles.at(second).getSize().y;
	//auto old_xPos = rectangles.at(index).getPosition().x;
	//auto new_yPos = rectangles.at(second).getPosition().y;
	rectangles.at(index).setSize(sf::Vector2f(rect_width, new_rect_height)); // only change y val
	rectangles.at(index).setOrigin(0, new_rect_height); // by default, origin is at top left, but i want it bottom left
	//rectangles.at(index).setPosition(old_xPos, new_yPos); // change y pos so rectangle is at bottom

	while (true) {
		//auto elapsedTime = clock.getElapsedTime();

		window.draw(bg); // draw background
		for (auto rect : rectangles) { // iterates and draws each rectangle
			window.draw(rect);
		}
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // add delay
		break;
	}

	rectangles.at(index).setFillColor(sf::Color(255, 255, 255));
	//rectangles.at(second).setFillColor(sf::Color(0, 30, 190));


}

void swapRectangles(int first, int second, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	auto FirstPosX = rectangles.at(first).getPosition().x; // holds old x position of rect
	auto SecondPosX = rectangles.at(second).getPosition().x;

	rectangles.at(first).setFillColor(sf::Color(0, 250, 0));
	rectangles.at(second).setFillColor(sf::Color(200, 0, 0));

	while (true) {
		window.draw(bg); // draw background
		if (rectangles.at(first).getPosition().x <= SecondPosX) {
			//or rectangles.at(second).getPosition().x >= FirstPosX) { // move first rect

			rectangles.at(second).move(sf::Vector2f(-1 * speed_, 0));
			rectangles.at(first).move(sf::Vector2f(speed_, 0));

			for (auto rect : rectangles) { // iterates and draws each rectangle
				window.draw(rect);
			}
			window.display();
			continue;
		}
		//if (rectangles.at(j).getPosition().x >= FirstPosX) { // move second rect
		//	rectangles.at(j).move(sf::Vector2f(-0.2, 0));
		//	for (auto rect : rectangles) { // iterates and draws each rectangle
		//		window.draw(rect);
		//	}
		//	window.display();
		//	continue;
		//}
		break;
	}

	//rectangles.at(first).setFillColor(sf::Color(0, 30, 190));
	//rectangles.at(second).setFillColor(sf::Color(0, 30, 190));

	std::swap(rectangles.at(first), rectangles.at(second));
	// set all rect to same color at the end
}

void insertionSort(std::vector<int>& nums, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	auto& insertionSortList = nums; // change this to copy later
	for (int i = 1; i < (int)insertionSortList.size(); i++) {
		int j = i; // j is position of last sorted element
		//std::cout << "in for loop" << std::endl; // debugging
		while (j > 0 and (insertionSortList.at(j) < insertionSortList.at(j - 1))) {
			//std::cout << "swapping " << insertionSortList.at(j) << " and " << insertionSortList.at(j - 1) << std::endl;
		
			swapRectangles(j-1, j, rectangles, bg, window);
			rectangles.at(j).setFillColor(sf::Color(255, 255, 255));
			rectangles.at(j-1).setFillColor(sf::Color(255, 255, 255));

			std::swap(insertionSortList.at(j), insertionSortList.at(j - 1)); // if elem is smaller than previous, swap them


			j--; // go backwards thru list and swap appropriate elements
		}
	}
	//printVec(insertionSortList);
	for (auto& rect : rectangles) {
		rect.setFillColor(sf::Color(0, 30, 190));
	}
	std::cout << "count: list has been sorted(insertion)" << std::endl;
}

void merge(std::vector<int>& mergeList, int start, int mid, int end, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	//std::cout << "merge" << std::endl;

	int subOne = mid - start + 1;
	int subTwo = end - mid;

	std::vector<int> A, B;
	for (int i = 0; i < subOne; i++) { // A contains first half of mergeList
		//std::cout << "A: append " << mergeList.at(start + i) << std::endl;
		A.push_back(mergeList.at(start + i));
		//rectangles.at(start + i).setFillColor(sf::Color(100, 0, 100));
	}
	for (int j = 0; j < subTwo; j++) { // B contains second half of mergeList
		//std::cout << "B: append " << mergeList.at(mid + 1 + j) << std::endl;
		B.push_back(mergeList.at(mid + 1 + j));
		//rectangles.at(mid + 1 + j).setFillColor(sf::Color(250, 170, 40));
	}


	int indexSubOne = 0, indexSubTwo = 0, indexMergedArray = start;

	while ((indexSubOne < subOne) and (indexSubTwo < subTwo)) {
		if (A.at(indexSubOne) <= B.at(indexSubTwo)) {
			mergeList.at(indexMergedArray) = A.at(indexSubOne);
			changeRectHeight(indexMergedArray, A.at(indexSubOne), rectangles, bg, window);
			indexSubOne++;
		}
		else {
			mergeList.at(indexMergedArray) = B.at(indexSubTwo);
			changeRectHeight(indexMergedArray, B.at(indexSubTwo), rectangles, bg, window);
			indexSubTwo++;
		}
		indexMergedArray++;
	}

	while (indexSubOne < subOne) {
		mergeList.at(indexMergedArray) = A.at(indexSubOne);
		changeRectHeight(indexMergedArray, A.at(indexSubOne), rectangles, bg, window);
		indexSubOne++;
		indexMergedArray++;
	}
	while (indexSubTwo < subTwo) {
		mergeList.at(indexMergedArray) = B.at(indexSubTwo);
		changeRectHeight(indexMergedArray, B.at(indexSubTwo), rectangles, bg, window);
		indexSubTwo++;
		indexMergedArray++;
	}
	//printVec(mergeList);

}

void mergeSort(std::vector<int>& nums, int start, int end, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	//std::cout << "merge Sort" << std::endl;
	auto& mergeList = nums;
	int j = 0;
	if (start < end) {
		j = start + (end - start) / 2; // midpt
		//std::cout << "start, j, end " << start << ", " << j << ", " << end << std::endl;
		mergeSort(mergeList, start, j, rectangles, bg, window);
		mergeSort(mergeList, j + 1, end, rectangles, bg, window);
		merge(mergeList, start, j, end, rectangles, bg, window);
	}
	//printVec(mergeList);
	//std::cout << std::endl;

}

void selectionSort(std::vector<int>& nums, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	//std::cout << "sel Sort" << std::endl;
	auto selectionList = nums; // create copy of array
	for (int i = 0; i < selectionList.size(); i++) {
		int min_index = i;
		for (int j = i + 1; j < selectionList.size(); j++) { // find smallest elem and put it in front
			if (selectionList.at(j) < selectionList.at(min_index)) {
				min_index = j;
			}
		}
		std::swap(selectionList.at(i), selectionList.at(min_index)); // smallest will now be 1st elem
		if (min_index != i) { // only change rect pos if a swap is required
			swapRectangles(i, min_index, rectangles, bg, window);
			rectangles.at(i).setFillColor(sf::Color(0, 30, 190));
			rectangles.at(min_index).setFillColor(sf::Color(255, 255, 255));
		}

		rectangles.at(i).setFillColor(sf::Color(0, 30, 190));
	}
	//printVec(selectionList);
}


int partition(std::vector<int>& A, int low, int hi, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	//std::cout << "partition" << std::endl;
	int i = low - 1;
	//int j = hi;
	int pivot = A.at(hi);
	rectangles.at(hi).setFillColor(sf::Color(200, 200, 200));
	//std::cout << "pivot: " << pivot << std::endl;

	for (int j = low; j < hi; j++) {
		if (A.at(j) < pivot) {
			i++;
			std::swap(A.at(i), A.at(j));
			if (i != j) { // only swap rects if i isnt equal to j
				swapRectangles(i, j, rectangles, bg, window);
				rectangles.at(i).setFillColor(sf::Color(255, 255, 255));
				rectangles.at(j).setFillColor(sf::Color(255, 255, 255));
			}
		}
	}
	std::swap(A.at(i + 1), A.at(hi));
	rectangles.at(hi).setFillColor(sf::Color(0, 30, 190));
	if ((i + 1) != hi) { // only swap rects if i + 1 != hi
		swapRectangles((i + 1), hi, rectangles, bg, window);
		rectangles.at(i + 1).setFillColor(sf::Color(255, 255, 255));
		rectangles.at(hi).setFillColor(sf::Color(255, 255, 255));
	}

	
	return (i + 1);
}

void quickSort(std::vector<int>& nums, int low, int hi, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	//std::cout << "Quick Sort" << std::endl;
	auto& quickList = nums;
	if (low < hi) {
		int j = partition(quickList, low, hi, rectangles, bg, window);
		//rectangles.at(j).setFillColor(sf::Color(50, 0, 50));
		quickSort(quickList, low, j - 1, rectangles, bg, window);
		quickSort(quickList, j + 1, hi, rectangles, bg, window);
		//rectangles.at(j).setFillColor(sf::Color(255, 255, 255));
	}
	//printVec(quickList);
}

void bubbleSort(std::vector<int>& nums, std::vector<sf::RectangleShape>& rectangles, sf::Sprite bg, sf::RenderWindow& window) {
	auto bubbleList = nums;
	
	for (int i = 1; i < bubbleList.size(); i++) {
		for (int j = 0; j < bubbleList.size() - 1; j++) {
			if (bubbleList.at(j) > bubbleList.at(j + 1)) {
				swapRectangles(j, j + 1, rectangles, bg, window);
				rectangles.at(j + 1).setFillColor(sf::Color(255, 255, 255));
				rectangles.at(j).setFillColor(sf::Color(255, 255, 255));
				std::swap(bubbleList.at(j), bubbleList.at(j + 1));
			}
		}
		rectangles.at(bubbleList.size() - i).setFillColor(sf::Color(0, 30, 190));
	}
	rectangles.at(0).setFillColor(sf::Color(0, 30, 190));
	printVec(bubbleList);
}

int main() {

	// allow user to choose size of list, speed, and which sort to use

	std::random_device rd;
	std::uniform_int_distribution<> d(1, 99);
	std::vector<int> nums;
	int size_ = 100;
	//int speed_input;

	//std::cout << "Enter how many numbers do you want to be sorted: " << std::endl;
	//std::cin >> size_;
	//std::cout << "Enter how fast do you want the sort (input 1 - 5): " << std::endl;
	//std::cin >> speed_input;
	speed_ = size_ / 60.0;
	//std::cout << "Choose sort - (i)nsertion, (s)election, (q)uick, or (m)erge" << std::endl;

	for (int i = 0; i < size_; i++) { // creates random vec of numbers
		nums.push_back(d(rd));
	}

	// insertion Sort
	//auto insertionSortList = nums;
	printVec(nums);


	// Actual program start

	sf::Image image;
	image.create(width, height);
	for (int i = 0; i < width; i++) {
		// itr thru each pixel of the image and set the color
		for (int j = 0; j < height; j++) {
			image.setPixel(i, j, sf::Color(0, 255, 255));
		}
	}
	sf::Texture texture;
	texture.loadFromImage(image); // load texture w/ blank image
	sf::Sprite sprite;
	sprite.setTexture(texture); // load sprite with the texture


	std::vector<sf::RectangleShape> rectangles; // holds rectangles that are used to represent nums in list
	double x_pos = 0;
	int y_pos = height;
	// This loop creates the rectangles that represent the list of nums
	for (auto num : nums) { // itr over list to be sorted
		double rect_width = width / nums.size();
		double rect_height = num * 5;
		sf::RectangleShape rectangle;
		sf::Vector2f sizeVec(rect_width, rect_height);
		rectangle.setSize(sizeVec); // width is 10, height should be changed to be relative to the num it's supposed to represent
		// rectangle for 10 should be shorter than rectangle for 100
		rectangle.setFillColor(sf::Color(255, 255, 255)); // sets rect color
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color(0, 0, 0));
		rectangle.setOrigin(0, num * 5); // by default, origin is at top left, but i want it bottom left
		rectangle.setPosition(x_pos, y_pos);
		// might need to setOrigin or setScale
		rectangles.push_back(rectangle);
		x_pos += rect_width; // add the width to x_pos so rectangles don't overlap
	}


	sf::RenderWindow window(sf::VideoMode(width, height), "Title"); // init window 800x600 pixels

	sf::Event event; // init event

	while (window.isOpen()) { // while window is open (you haven't clicked x yet)


		while (window.pollEvent(event)) { // while loop looking for events (like interrupts)

			if (event.type == sf::Event::Closed) { // if you exit (click X) window, close the window
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) { // check if 'i' key is pressed
					insertionSort(nums, rectangles, sprite, window);
					// exit afterward
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) { // 'm' for mergeSort
					mergeSort(nums, 0, nums.size() - 1, rectangles, sprite, window);
					for (auto& rect : rectangles) {
						rect.setFillColor(sf::Color(0, 30, 190));
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // 's' for selctionSort
					selectionSort(nums, rectangles, sprite, window);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { // 'q' for quick sort
					quickSort(nums, 0, nums.size() - 1, rectangles, sprite, window);
					for (auto& rect : rectangles) {
						rect.setFillColor(sf::Color(0, 30, 190));
					}
					printVec(nums);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) { // 'b' for bubble sort
					bubbleSort(nums, rectangles, sprite, window);
				}
			}



		}

		window.draw(sprite); // draw sprite (background) to screen

		for (auto rect : rectangles) { // iterates and draws each rectangle
			window.draw(rect);
		}
		
		window.display(); // display window

		window.clear(); // clear screen every frame i think

	}

	std::cout << "Ahoy world!" << std::endl;



	return 0;
}