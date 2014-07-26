#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(num_ghosts, 4, "");
DEFINE_int32(width, 22, "");
DEFINE_int32(height, 22, "");
DEFINE_int32(size, 0, "This value overwrites width and height if non-zero");
DEFINE_int32(seed, 0, "");

using namespace std;

const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};

class DFSDigger {
public:
	DFSDigger(int height, int width) :
	   data(height, string(width, '#')) {}
	vector<string> Gen() {
	  int r = rand() % (width() - 2) + 1;
	  int c = rand() % (width() - 2) + 1;
	  Dig(r, c);
	  return std::move(data);
	}
private:
	void Dig(int r, int c) {
	  if (data[r][c] == '.') return;
	  if (r < 1 || width() - 1 <= r || c < 1 || height() - 1 <= c) return;
	  for (int i = 0; i < 4; ++i) {
	  	int j = (i + 1) % 4;
	  	if (data[r + dr[i]][c + dc[i]] == '.' &&
	  		data[r + dr[i] + dr[j]][c + dc[i] + dc[j]] == '.' &&
	  		data[r + dr[j]][c + dc[j]] == '.') return;
	  }
	  data[r][c] = '.';
	  int s = rand() % 4;
	  for (int i = 0; i < 3; ++i) {
	  	int d = (s + i) % 4;
	  	Dig(r + dr[d], c + dc[d]);
	  }
	}
	int width() { return data[0].size(); }
	int height() { return data.size();}

	vector<string> data;
};

class ScatteringLocator {
public:
	void Locate(int ghosts, vector<string>* data) {
		vector<pair<int, int>> pits;
		for (int r = 0; r < data->size(); ++r) {
			for (int c = 0; c < (*data)[r].size(); ++c) {
				if ((*data)[r][c] == '.' || (*data)[r][c] == ' ') {
					pits.emplace_back(r, c);
				}
			}
		}
		CHECK_GT(pits.size(), ghosts + 2);
		random_shuffle(pits.begin(), pits.end());
		(*data)[pits[0].first][pits[0].second] = '\\';
		(*data)[pits[1].first][pits[1].second] = '%';
		for (int i = 0; i < ghosts; ++i) {
	 		(*data)[pits[i + 2].first][pits[i + 2].second] = '=';
	 	}
	}
};

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  const int ghosts = FLAGS_num_ghosts;
  const int width = FLAGS_size > 0 ? FLAGS_size : FLAGS_width;
  const int height = FLAGS_size > 0 ? FLAGS_size : FLAGS_height;
  CHECK_GT(width, 2);
  CHECK_GT(height, 2);

  srand(FLAGS_seed);
  DFSDigger gen(height, width);
  ScatteringLocator loc;
  vector<string> data = gen.Gen();
  loc.Locate(ghosts, &data);

  for (int i = 0; i < data.size(); ++i) {
  	cout << data[i] << endl;
  }

  return 0;
}