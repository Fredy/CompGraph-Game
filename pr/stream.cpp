#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string line = "UNO DOS TRES CUATRO CINCO    SEIS 909";
  istringstream stringstrm(line);
  vector<std::string> results((istream_iterator<string>(stringstrm)),
                              istream_iterator<string>());

  for (int i = 0 ; i < results.size(); i++) {
    cout << results[i] << endl;
  }

}