#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class BinaryTree
{
private:
	vector<int> _tree;
public:
	void add(int value);
	void orderTree(int i);
	void del();
	int get() const { return _tree[0]; }
	void show() const;
};

vector<string> &split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

int main(int argc, char* argv[])
{
	BinaryTree tree;
	string command;
	vector<string> commands;
	int N;
	int i = 0;
	int size;
	cout << "N = ";
	cin >> N;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (i < N && i >= 0)
	{
		cout << i + 1 << ">>";
		getline(cin, command);
		commands = split(command, ' ');
		size = commands.size();
		if (size == 0)
		{
			cout << "Incorrect command. Try again.\n";
			i--;
		}
		else if (size == 2)
		{
			if (commands[0] == "add")
				tree.add(stoi(commands[1]));
			else
			{
				cout << "Incorrect command. Try again.\n";
				i--;
			}
		}
		else if (size == 1)
		{
			try
			{
				if (commands[0] == "del")
					tree.del();
				else if (commands[0] == "get")
					cout << tree.get() << endl;
				else if (commands[0] == "show")
				{
					tree.show();
					cout << endl;
				}
				else
				{
					cout << "Incorrect command. Try again.\n";
					i--;
				}
			}
			catch (char* message)
			{
				cout << message << endl;
			}
		}
		else
		{
			cout << "Incorrect command. Try again.\n";
			i--;
		}
		i++;
	}
	system("pause");
	return 0;
}

void BinaryTree::add(int value)
{
	_tree.push_back(value);
	int i = _tree.size() - 1;
	int parent = (i - 1) / 2;

	while (i > 0 && _tree[parent] > _tree[i])
	{
		int temp = _tree[i];
		_tree[i] = _tree[parent];
		_tree[parent] = temp;
		i = parent;
		parent = (i - 1) / 2;
	}
}

void BinaryTree::orderTree(int i)
{
	int leftChild;
	int rightChild;
	int leastChild;

	while (true)
	{
		leftChild = 2 * i + 1;
		rightChild = 2 * i + 2;
		leastChild = i;

		if (leftChild < _tree.size() && _tree[leftChild] < _tree[leastChild])
			leastChild = leftChild;

		if (rightChild < _tree.size() && _tree[rightChild] < _tree[leastChild])
			leastChild = rightChild;

		if (leastChild == i)
			break;

		int temp = _tree[i];
		_tree[i] = _tree[leastChild];
		_tree[leastChild] = temp;
		i = leastChild;
	}
}

void BinaryTree::del()
{
	if (_tree.size() == 0)
		throw "Tree is empty";

	int result = _tree[0];
	_tree[0] = _tree[_tree.size() - 1];
	_tree.erase(_tree.begin() + _tree.size() - 1);

	for (int i = _tree.size() / 2; i >= 0; i--)
		orderTree(i);
}

void BinaryTree::show() const
{
	for (int i = 0; i < _tree.size(); i++)
		cout << _tree[i] << "  ";
}
