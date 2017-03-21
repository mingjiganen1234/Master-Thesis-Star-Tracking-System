#ifndef DATABASE_H_
#define DATABASE_H_

#include <vector>
#include <memory>
#include <algorithm>
#include "StarPatternDatabase.h"

/***************************************** SEARCH 1 **************************************************/

int searchLin(int database[DATABASESIZE][5], int tor, int N, int D1, int D2, int D3) {
	int error = 999;
	int cid = -1;
	for (int i = 0; i < DATABASESIZE; ++i) {
		if (database[i][0] >= N - tor && database[i][0] <= N + tor &&
			database[i][1] >= D1 - tor && database[i][1] <= D1 + tor &&
			database[i][2] >= D2 - tor && database[i][2] <= D2 + tor &&
			database[i][3] >= D3 - tor && database[i][3] <= D3 + tor)
		{
			int temp = (N - database[i][0]) * (N - database[i][0]) + (D1 - database[i][1]) * (D1 - database[i][1]) + (D2 - database[i][2]) * (D2 - database[i][2]) + (D3 - database[i][3]) * (D3 - database[i][3]);
			if (error > temp) {
				error = temp;
				cid = database[i][4];
			}
		}
	}
	return cid;
}

/******************************************* SEARCH 2 ************************************************/
class Node;
typedef std::shared_ptr<Node> NodePtr;
class Node {
public:
	int key_;
	NodePtr parent_;
	std::vector<NodePtr> children_;

	struct CompareKey {
		CompareKey(const int &val) : val_(val) {}
		bool operator()(const NodePtr &element) const {
			return val_ == element->key_;
		}
	private:
		int val_;
	};

public:
	Node(const int &key) : key_(key), parent_(nullptr) {}
	Node(const int &key, const NodePtr &parent) : key_(key), parent_(parent) {
		if (parent_ == nullptr) return;
		parent_->children_.push_back((NodePtr)this);
	}

	size_t insert(const int &data, const NodePtr &parentNode) {
		auto it = std::find_if(parentNode->children_.begin(), parentNode->children_.end(), CompareKey(data));
		if (it == parentNode->children_.end()) {
			new Node(data, parentNode);
			return parentNode->children_.size() - 1;
		}
		return it - parentNode->children_.begin();
	}

	NodePtr moveToChild(const NodePtr &pt, size_t it) const {
		return pt->children_[it];
	}

	friend int searchPattern(const NodePtr &root, int N, int d1, int d2, int d3) {
		NodePtr ptr = root;

		//N
		auto it = std::find_if(ptr->children_.begin(), ptr->children_.end(), CompareKey(N));
		if (it == ptr->children_.end())
			return -1;

		//d1
		ptr = root->moveToChild(ptr, it - ptr->children_.begin());
		it = std::find_if(ptr->children_.begin(), ptr->children_.end(), CompareKey(d1));
		if (it == ptr->children_.end())
			return -1;

		//d2
		ptr = root->moveToChild(ptr, it - ptr->children_.begin());
		it = std::find_if(ptr->children_.begin(), ptr->children_.end(), CompareKey(d2));
		if (it == ptr->children_.end())
			return -1;

		//d3
		ptr = root->moveToChild(ptr, it - ptr->children_.begin());
		it = std::find_if(ptr->children_.begin(), ptr->children_.end(), CompareKey(d3));
		if (it == ptr->children_.end())
			return -1;

		//return id
		ptr = root->moveToChild(ptr, it - ptr->children_.begin());
		return ptr->children_.back()->key_;
	}

	friend int searchTolerance(const NodePtr &root, int tor, int N, int D1, int D2, int D3) {
		std::vector<dataStruct> resid;
		for (int n = N - tor; n <= N + tor; ++n)
			for (int d1 = D1 - tor; d1 <= D1 + tor; ++d1)
				for (int d2 = D2 - tor; d2 <= D2 + tor; ++d2)
					for (int d3 = D3 - tor; d3 <= D3 + tor; ++d3) {
						int res = searchPattern(root, n, d1, d2, d3);
						if (res != -1)
							resid.push_back({ n,d1,d2,d3,res });
					}
		if (resid.size() == 0)
			return -1;

		int error = 999;
		int cid = resid[0].id;
		for (int i = 0; i < (int)resid.size(); ++i) {
			int temp = (N - resid[i].N) * (N - resid[i].N) + (D1 - resid[i].d1) * (D1 - resid[i].d1) + (D2 - resid[i].d2) * (D2 - resid[i].d2) + (D3 - resid[i].d3) * (D3 - resid[i].d3);
			if (error > temp) {
				error = temp;
				cid = resid[i].id;
			}
		}
		return cid;
	}
};

NodePtr buildTree(int database[DATABASESIZE][5]) {
	//Init tree
	NodePtr root(new Node(0));

	for(int i = 0; i < DATABASESIZE; ++i) {
		NodePtr ptr = root;

		//Insert N
		size_t it = root->insert(database[i][0], ptr);
		ptr = root->moveToChild(ptr, it);

		//Insert d1
		it = root->insert(database[i][1], ptr);
		ptr = root->moveToChild(ptr, it);

		//Insert d2
		it = root->insert(database[i][2], ptr);
		ptr = root->moveToChild(ptr, it);

		//Insert d3
		it = root->insert(database[i][3], ptr);
		ptr = root->moveToChild(ptr, it);

		//Insert id
		it = root->insert(database[i][4], ptr);
	}
	return root;
}


#endif