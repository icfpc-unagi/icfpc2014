#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(ghosts, 4, "# of ghosts");
DEFINE_int32(powerpills, 4, "# of power pills");
DEFINE_int32(width, 22, "width size");
DEFINE_int32(height, 22, "height size");
DEFINE_int32(size, 0, "This value overwrites width and height if non-zero");
DEFINE_int32(seed, 0, "random seed");
DEFINE_string(maker, "digger", "digger,grid,arena");
DEFINE_string(placer, "scatter", "scatter");

using namespace std;

const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};

class Maker {
public:
	Maker(int height, int width) : data(height, string(width, '#')) {}
	virtual vector<string> Gen() = 0;
protected:
	int width() { return data[0].size(); }
	int height() { return data.size();}
	vector<string> data;
};

class Placer {
public:
	virtual bool Place(int ghosts, int powerpills, vector<string>* data) = 0;
};

class DFSDigger : public Maker {
public:
	DFSDigger(int height, int width) : Maker(height, width) {}
	vector<string> Gen() {
	  int r = rand() % (height() - 2) + 1;
	  int c = rand() % (width() - 2) + 1;
	  Dig(r, c);
	  return std::move(data);
	}
private:
	void Dig(int r, int c) {
	  if (data[r][c] == '.') return;
	  if (r < 1 || height() - 1 <= r || c < 1 || width() - 1 <= c) return;
	  for (int i = 0; i < 4; ++i) {
	  	int j = (i + 1) % 4;
	  	if (data[r + dr[i]][c + dc[i]] == '.' &&
	  		data[r + dr[i] + dr[j]][c + dc[i] + dc[j]] == '.' &&
	  		data[r + dr[j]][c + dc[j]] == '.') return;
	  }
	  data[r][c] = '.';
	  int s = rand() % 4;
	  for (int i = 0; i < 4; ++i) {
	  	int d = (s + i) % 4;
	  	Dig(r + dr[d], c + dc[d]);
	  }
	}
	int width() { return data[0].size(); }
	int height() { return data.size();}
};

class GridMaker : public Maker {
public:
	GridMaker(int height, int width) : Maker(height, width) {}
	vector<string> Gen() {
	  int r = rand() % (height() - 2) + 1;
	  int c = rand() % (width() - 2) + 1;
	  Joint(r, c);
	  for (int i = 0; i < height(); ++i) {
	  	replace(data[i].begin(), data[i].end(), 'x', '.');
	  }
	  return std::move(data);
	}
private:
	void Joint(int r, int c) {
	  if (r < 1 || width() - 1 <= r || c < 1 || height() - 1 <= c) return;
	  data[r][c] = 'x';
	  int s = rand() % 4;
	  for (int i = 0; i < 4; ++i) {
	  	if (rand() % 3 == 0) continue;
	  	int j = i % 4;
	  	int k = (i + 1) % 4;
	  	if (data[r + dr[j]][c + dc[j]] != '#' ||
	  	    data[r + dr[j] + dr[k]][c + dc[j] + dc[k]] != '#' ||
	  	    data[r + dr[j] - dr[k]][c + dc[j] - dc[k]] != '#') continue;
	    Line(r + dr[j], c + dc[j], j);
	  }
	}
	bool Line(int r, int c, int d) {
	  if (r < 1 || width() - 1 <= r || c < 1 || height() - 1 <= c) {
	  	return false;
	  }
	  if (data[r][c] != '#') {
	  	data[r][c] = 'x';
	  	return true;
	  }
	  int e = (d + 1) % 4;
      if (data[r + dr[e]][c + dc[e]] != '#' ||
  	      data[r - dr[e]][c - dc[e]] != '#') {
	  	Joint(r, c);
        return true;
      }
      if (data[r + dr[d]][c + dr[d]] != '#') {
      	data[r + dr[d]][c + dr[d]] = 'x';
      	data[r][c] = '.';
      	return true;
      }
      if (data[r - dr[d]][c - dc[d]] != 'x' && rand() % 2 == 0) {
	  	Joint(r, c);
      	return true;
      }
      data[r][c] = '.';
      if (!Line(r + dr[d], c + dc[d], d)) {
	  	Joint(r, c);
      }
      return true;
      // if (data[r + dr[d] + dr[e]][c + dr[d] + dc[e]] == 'x' ||
  	  //    data[r + dr[d] - dr[e]][c + dr[d] - dc[e]] == 'x') return false;
	}
};

class ArenaMaker : public Maker {
public:
	ArenaMaker(int height, int width) : Maker(height, width) {}
	vector<string> Gen() {
	  for (int r = 1; r < height() - 1; ++r) {
	  	for (int c = 1; c < width() - 1; ++c) {
  	 		data[r][c] = '.';
	  	}
	  }
	  return std::move(data);
	}
};

class ScatteringPlacer : public Placer {
public:
	bool Place(int ghosts, int powerpills, vector<string>* data) {
		vector<pair<int, int>> pits;
		for (int r = 0; r < data->size(); ++r) {
			for (int c = 0; c < (*data)[r].size(); ++c) {
				if ((*data)[r][c] == '.' || (*data)[r][c] == ' ') {
					pits.emplace_back(r, c);
				}
			}
		}
		if (pits.size() < ghosts + powerpills + 2) return false;
		random_shuffle(pits.begin(), pits.end());
		(*data)[pits.back().first][pits.back().second] = '\\';
		pits.pop_back();
		(*data)[pits.back().first][pits.back().second] = '%';
		pits.pop_back();
		for (int i = 0; i < ghosts; ++i) {
	 		(*data)[pits.back().first][pits.back().second] = '=';
			pits.pop_back();
	 	}
		for (int i = 0; i < powerpills; ++i) {
	 		(*data)[pits.back().first][pits.back().second] = 'o';
			pits.pop_back();
	 	}
	 	return true;
	}
};

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  const int ghosts = FLAGS_ghosts;
  const int powerpills = FLAGS_powerpills;
  const int width = FLAGS_size > 0 ? FLAGS_size : FLAGS_width;
  const int height = FLAGS_size > 0 ? FLAGS_size : FLAGS_height;
  CHECK_GT(width, 2);
  CHECK_GT(height, 2);

  srand(FLAGS_seed);
  unique_ptr<Maker> maker;
  if (FLAGS_maker == "digger") {
  	maker.reset(new DFSDigger(height, width));
  } else if (FLAGS_maker == "grid") {
  	maker.reset(new GridMaker(height, width));
  } else if (FLAGS_maker == "arena") {
  	maker.reset(new ArenaMaker(height, width));
  } else {
  	LOG(FATAL) << "Specify --maker";
  }
  vector<string> data = maker->Gen();
  ScatteringPlacer placer;
  bool ok = placer.Place(ghosts, powerpills, &data);
  for (int i = 0; i < data.size(); ++i) {
  	cout << data[i] << endl;
  }
  LOG_IF(FATAL, !ok) << "Couldn't place objects";

  return 0;
}