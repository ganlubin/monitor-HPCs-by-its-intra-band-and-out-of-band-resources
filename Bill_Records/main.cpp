#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#define MONTH_SALARY 3600
#define APARTMENT_AID = 600
#define MEAL_AID = 20

void show(std::map<std::string, double>&);
void show(const std::string&);
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
Trip:
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
  map["Meal"] += 13.4;

  // 9-6
  map["Shopping"] += 9.9;
  map["Meal"] += 6;
  map["Meal"] += 23;
  map["Meal"] += 20.6;
  map["Football"] += 16.88;
  map["Apartment_bill"] += 61.5;

  // 9-7
  map["Shopping"] += 28.9;
  map["Meal"] += 4.5;
  map["Meal"] += 8;
  map["Meal"] += 20;
  map["Drink"] += 8;
  map["Snooker"] += 300;

  // 9-8 ~ 9-10
  map["Transport"] += 8;
  map["Trip"] += 10;
  map["Drink"] += 9.9;
  map["Meal"] += 33.9;
  map["Movie"] += 92;
  map["Meal"] += 14;
  map["Transport"] += 7;
  map["Meal"] += 69.3;
  map["Transport"] += 12;

  // 9.11
  map["Vehicle"] += 13.27 + 3.99;
  map["Shopping"] += 6.18 + 10.5;
  map["Meal"] += 12;
  map["Apartment_bill"] += 22.5;

  show(map);
  show("Swim");

  return 0;
}

void show(const std::string &swim) {
  std::vector<std::string> vector;
  vector.push_back("2023-09-11");



  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Swimming times: " << vector.size() << std::endl;
  std::cout << "-------------------------------------" << std::endl;
}

void show(std::map<std::string, double> &map) {
  std::cout << std::endl;
  double sum = 0;
  for (auto it : map) {
    sum += it.second;
  }
  std::cout << "-------------------------------------" << std::endl;
  for (auto it : map) {
    std::cout << std::left << std::setw(15) << it.first << ": " << std::fixed
              << std::setw(15) << std::setprecision(2) << it.second << ", "
              << std::setprecision(2) << (it.second / sum * 100) << "%"
              << std::endl;
  }
  std::cout << "From 08-31 the bills : " << std::fixed << std::setprecision(2)
            << sum << std::endl;
  std::cout << "-------------------------------------" << std::endl;
}
