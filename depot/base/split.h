// Author: Kentaro Imajo (@imos)

#ifndef BASE_SPLIT_H_
#define BASE_SPLIT_H_

#include <string>
#include <vector>

vector<string> Split(const string& input, const string& delimiter, int limit);

vector<string> Split(const string& input, const string& delimiter);

vector<string> ReverseSplit(
    const string& self, const string& delimiter, int limit);

#endif  // BASE_SPLIT_H_
