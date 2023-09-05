#include <algorithm>
#include <cmath>
#include <iomanip>
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
*/

int main() {

  std::map<std::string, double> map;
  std::cout << "the bill from 2023-08-31: " << std::endl;
  map["Transport"] += (46.5 * 2);
  map["Meal"] += 7.5 + 21.58;

  // 9-1
  map["Drink"] += 11;
  map["Meal"] += 6.8;
  map["Meal"] += 15;
  map["Shopping"] += 16.8;
  map["Shopping"] += 76.55;
  map["Vehicle"] += 9.51 + 0.98;

  // 9-2
  map["Vehicle"] += 2 + 3.5 + 11;
  map["Meal"] += 30.5;
  map["Movie"] += 90.7;

  // 9-3
  map["Vehicle"] += 11.32, map["Meal"] += 22.9, map["Shopping"] += 12;

  // 9-4
  map["Meal"] += 7.5;
  map["Meal"] += 17.27;

  // 9-5
  map["Meal"] += 6.8;

  show(map);

  return 0;
}

void show(std::map<std::string, double> map) {
  std::cout << std::endl;
  double sum = 0;
  for (auto it : map) {
    sum += it.second;
  }
  std::cout << "-------------------------------------" << std::endl;
  for (auto it : map) {
    std::cout << std::left << std::setw(10) << it.first << ": " << std::fixed
              << std::setw(10) << std::setprecision(2) << it.second << ", "
              << std::setprecision(2)
              << (it.second / sum * 100) << "%" << std::endl;
  }
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "From 08-31 the bills : " << std::fixed << std::setprecision(2)
            << sum << std::endl;
  std::cout << std::endl;
}