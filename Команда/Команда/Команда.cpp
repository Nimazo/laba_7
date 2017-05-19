#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Document
{
	vector<string> data;
public:
	void Insert(int line, const string & str)
	{
		if (line <= data.size())
			data.insert(data.begin() + line, str);
		else
			cout << "Ошибка" << endl;
	}

	void Remove(int line)
	{
		if (!(line>data.size()))
			data.erase(data.begin() + line);
		else
			cout << "Ошибка" << endl;
	}

	string & operator [] (int x)
	{
		return data[x];
	}

	void Show()
	{
		for (int i = 0; i<data.size(); ++i)
		{
			cout << i + 1 << ". " << data[i] << endl;
		}
	}
};

class Command
{
protected:
	Document * doc;
public:
	virtual void Execute() = 0;
	virtual void unExecute() = 0;

	void setDocument(Document * _doc)
	{
		doc = _doc;
	}
};

class InsertCommand : public Command
{
	int line;
	string str;
public:
	InsertCommand(int _line, const string & _str) : line(_line), str(_str) {}

	void Execute()
	{
		doc->Insert(line, str);
	}

	void unExecute()
	{
		doc->Remove(line);
	}
};

class Receiver
{
	vector<Command*> DoneCommands;
	Document doc;
	Command* command;
public:
	void Insert(int line, string str)
	{
		command = new InsertCommand(line, str);
		command->setDocument(&doc);
		command->Execute();
		DoneCommands.push_back(command);
	}

	void Undo()
	{
		if (DoneCommands.size() == 0)
		{
			cout << "Отменять нечего" << endl;
		}
		else
		{
			command = DoneCommands.back();
			DoneCommands.pop_back();
			command->unExecute();
			delete command;
		}
	}

	void Show()
	{
		doc.Show();
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	char s = '1';
	int line, line_b;
	string str;
	Receiver res;
	while (s != 'e')
	{
		cout << "Что сделать: \n1.Добавить строку\n2.Отменить последнюю команду" << endl;
		cin >> s;
		switch (s)
		{
		case '1':
			cout << "Какую строку добавить: ";
			cin >> line;
			--line;
			cout << "Что добавить? ";
			cin >> str;
			res.Insert(line, str);
			break;
		case '2':
			res.Undo();
			break;
		}
		cout << "" << endl;
		res.Show();
		cout << "" << endl;
	}
}
