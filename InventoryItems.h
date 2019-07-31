#ifndef INVENTORY_ITEMS_H
#define INVENTORY_ITEMS_H

#include <string>
using namespace std;

class InventoryItems {

private:
	string description;
	int units;
	double cost;

public: 
	InventoryItems() {
		description = "";
		units = 0;
		cost = 0.0;
	}

	InventoryItems(string desc)
	{
		description = desc;
		cost = 0.0;
		units = 0;
	}

	InventoryItems(string d, double c, int u) {
		description = d;
		units = u;
		cost = c;
	}

	void setDescription(string d) {
		description = d;
	}
	void setCost(double u) {
		cost = u;
	}
	void setUnits(int u) {
		units = u;
	}

	string getDescription()const {
		return description;
	}
	double getCost() const{
		return cost;
	}
	int getUnits() const {
		return units;
	}

};

#endif // !INVENTORY_ITEMS_H
#pragma once
