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

  show("Swim");

  return 0;
}

void show(const std::string &swim) {
  std::vector<std::string> vector;
  vector.push_back("2023-09-11");
  vector.push_back("2023-09-12");
  vector.push_back("2023-09-14");
  vector.push_back("2023-09-18");
  vector.push_back("2023-09-19");
  vector.push_back("2023-09-20");
  vector.push_back("2023-09-22");
  vector.push_back("2023-09-25");
  vector.push_back("2023-09-26");
  vector.push_back("2023-09-27");
  vector.push_back("2023-10-08");
  vector.push_back("2023-10-10");
  vector.push_back("2023-10-11");
  vector.push_back("2023-10-12");
  vector.push_back("2023-10-13");
  vector.push_back("2023-10-18");
  vector.push_back("2023-10-19");
  vector.push_back("2023-10-24");
  vector.push_back("2023-10-25");
  vector.push_back("2023-10-26");
  vector.push_back("2023-10-30");
  vector.push_back("2023-10-31");
  vector.push_back("2023-11-03");
  vector.push_back("2023-11-09");

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Swimming times: " << vector.size() << std::endl;
  std::cout << "the usage: " << vector.size() * 1.0f / 59 * 100 << '%' << '\n';
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
