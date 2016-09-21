
using namespace std;

class Bag {
public:
    Bag(vector<Item*> nItems, short maxSize);
    short getSize() { return size; }
    short getMaxSize() { return maxSize; }
    vector<Item*> getItems() { return items; }
    void setMaxSize(int n) { maxSize = n; }
    void sort(Item* item);

    Item* addItem(Item* item);
    Item* removeItem(Item* item);
    Item* itemAt(int n);
private:
    short size;
    short maxSize;
    vector<Item*> items;
};

Bag::Bag(vector<Item*> nItems = {}, short nMaxSize = 10)
    : size(0), maxSize(nMaxSize)  {
    for(auto item : nItems) {
        addItem(item);
    }
}

Item* Bag::addItem(Item* item) {
//	if(item == nullptr) return item;

    items.push_back(item);
	size++;
    return item;
}
Item* Bag::removeItem(Item* item) {
	if(find(items.begin(), items.end(), item) == items.end())
		return item;
	items.erase(find(items.begin(), items.end(), item));
    size--;
    return item;
}
Item* Bag::itemAt(int n) {
	return getItems().at(n);
}
void Bag::sort(Item* item) {
	// rotates bag to have the item being used to fight be set in front (used to calculate the next turn's defending weapon weight)
	  vector<Item*>::iterator it = find(items.begin(), items.end(), item);
	  rotate(items.begin(), it, items.end());
}
