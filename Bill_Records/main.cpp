#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#define MONTH_SALARY 3600
#define APARTMENT_AID = 600
#define MEAL_AID = 20

void show(std::map<std::string, double>);
/*
From 08-31

Mapping

Meal:
Drink:
Vehicle:
Football:
Snooker:
Shopping:
Movie:
Apartment_bill:
Transport:
Network:
Sum:
*/

int main() {

  std::map<std::string, double> map;
  std::cout << "the bill from 2023-08-31: " << std::endl;
  map["Transport"] += (46.5 * 2);
  map["Sum"] += (46.5 * 2);
  map["Meal"] += 7.5 + 21.58;
  map["Sum"] += 7.5 + 21.58;

  // 9-1
  map["Drink"] += 11;
  map["Sum"] += 11;
  map["Meal"] += 6.8;
  map["Sum"] += 6.8;

  show(map);

  return 0;
}

void show(std::map<std::string, double> map) {
  for (auto it : map) {
    std::cout << it.first << ": " << it.second << std::endl;
  }
}