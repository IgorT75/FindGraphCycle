#include <stdio.h>
#include <queue>
#include <utility>
#include <vector>
#include <map>
#include <stack>
#include <exception>

using namespace std;

void printVec(const vector<size_t>& v) {
  printf("%zu: ", v.size());
  for (size_t i : v)
    printf("%zu, ", i);
  printf("\n");
}

class CycleFinder {

	enum State { white = 0, gray = 1, black = 2 };

  vector<vector<size_t>> _graph;
  mutable vector<bool> _visited;
	mutable map<size_t, State> _state;

	bool dfs(size_t vertex) const {
		if (vertex >= _graph.size())
			throw bad_exception();

		_state[vertex] = gray;
		printf("Graying vertex: %zu\n", vertex);
		for (size_t adjVert : _graph[vertex])
		{
			if (_state[adjVert] == gray)
				return true;
			if (_state[adjVert] == white)
				if (dfs(adjVert))
					return true;
		}
		_state[vertex] = black;
		printf("Blackened vertex: %zu\n", vertex);
		return false;
	}

  public:
		explicit CycleFinder(vector<vector<size_t>> graph) : _graph(std::move(graph)) { }
		explicit CycleFinder(const vector<vector<size_t>>&& graph) : _graph(graph) { }

    bool findCycle() const {
      for (size_t i = 0, n = _graph.size(); i < n; ++i) {
				if (_state[i] == white)
					if (dfs(i))
						return true;
      }
			return false;
    }
};

int main() {
/* 0→→→→1←←←←←←←←←←←3
   ↑    ↓ ⬊      ⬈ ↓ ⬊
   ↑    ↓   ⬊  ⬈   ↓   ⬊
   ↑    ↓     2     ↓    4
   ↑    ↓  ⬋        ↓  ⬈
   ↑    ↓⬋          ↓⬈
   7→→→→6→→→→→→→→→→→5*/
	const vector<vector<size_t>> graph {
    { 1 },
    { 2, 6 },
    { 3, 6 },
    { 4, 5 },
    { 0 },
    { 4 },
    { 5 },
    { 0, 6 },
  };

  CycleFinder ts(graph);
	const bool isCycle = ts.findCycle();
	printf("Cycle present: %d\n", isCycle);

  return 0;
}