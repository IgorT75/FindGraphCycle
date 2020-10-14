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
	stack<size_t> _stack;
	vector<size_t> _path;
	map<size_t, State> _state;

	void buildCycle(size_t vertex) {
		_path.clear();
		while (!_stack.empty() && _stack.top() != vertex) {
			_path.push_back(_stack.top());
			_stack.pop();
		}

		_path.push_back(vertex);
		std::reverse(_path.begin(), _path.end());

		while (!_stack.empty())
			_stack.pop();
	}

	bool dfs(size_t vertex) {
		if (vertex >= _graph.size())
			throw bad_exception();

		_state[vertex] = gray;
		_stack.push(vertex);
		//printf("Graying vertex: %zu\n", vertex);
		for (size_t adjVert : _graph[vertex])
		{
			if (_state[adjVert] == gray) {
				buildCycle(adjVert);
				return true;
			}
			if (_state[adjVert] == white)
				if (dfs(adjVert))
					return true;
		}
		_stack.pop();
		_state[vertex] = black;
		//printf("Blackened vertex: %zu\n", vertex);
		return false;
	}

  public:
		explicit CycleFinder(vector<vector<size_t>> graph) : _graph(std::move(graph)) { }
		explicit CycleFinder(const vector<vector<size_t>>&& graph) : _graph(graph) { }

    vector<size_t> findCycle() {
			_path.clear(); _state.clear();
      for (size_t i = 0, n = _graph.size(); i < n; ++i) {
				if (_state[i] == white)
					if (dfs(i))
						break;
      }

			return _path;
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
    { 1, 4, 5 },
    {  },
    { 4 },
    { 5 },
    { 0, 6 },
  };

  CycleFinder ts(graph);
	const auto cyclePath = ts.findCycle();
	printVec(cyclePath);

  return 0;
}
