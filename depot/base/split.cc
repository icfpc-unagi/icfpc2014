// Author: Kentaro Imajo (@imos)

#include "base/split.h"

#include <algorithm>
#include <string>
#include <vector>

vector<string> Split(const string& input, const string& delimiter, int limit) {
  vector<string> result;
  size_t current_position = 0;
  while (current_position < input.size() &&
         (limit == 0 || result.size() < limit - 1)) {
    size_t next_position = input.find(delimiter, current_position);
    if (next_position == string::npos) break;
    result.push_back(input.substr(
        current_position, next_position - current_position));
    current_position = next_position + delimiter.size();
  }
  result.push_back(input.substr(current_position));
  return result;
}

vector<string> Split(const string& input, const string& delimiter) {
  return Split(input, delimiter, 0);
}

vector<string> ReverseSplit(
    const string& self, const string& delimiter, int limit) {
  vector<string> result;
  size_t current_position = self.size();
  while (delimiter.size() <= current_position &&
         (limit == 0 || result.size() < limit - 1)) {
    size_t next_position =
        self.rfind(delimiter, current_position - delimiter.size());
    if (next_position == string::npos) break;
    result.push_back(self.substr(
        next_position + delimiter.size(),
        current_position - next_position - delimiter.size()));
    current_position = next_position;
  }
  result.push_back(self.substr(0, current_position));
  std::reverse(result.begin(), result.end());
  return result;
}
