#include<iostream>
#include<iomanip>
#include<map>
#include<vector>
#include<fstream>
#include<ctime>
#include<string>
#include<Windows.h>
using namespace std;


typedef struct Book {
	int record_num;  //记录号
	int book_id;     //书号
	string book_name;    //书名
	int b_ptr;      //书名指针
	string author;  //作者
	int w_ptr;		//作者指针
	string press;   //出版社
	int p_ptr;		//出版社指针 
	int classfity;  //分类
	int collect;    //藏书量
	int borrow;     //借出数
}Book;

typedef struct Index {
	int lhead;	 //链头指针
	int length;  //长度
}Index;

typedef struct Reader {
	int reader_num;    //读者号
	string name;       //读者名
	int bn1;           //可借书数
	int bn2;           //已借书数
}Reader;

typedef struct Bbook {
	int reader_num;		//读者号
	int book_id;		//书号
	string borrow_date; //借书日期
	string return_date; //还书日期
}Bbook;

vector<Book> book;				//图书索引文件
map<int, int> bookid_index;		//书号索引文件
map<string, Index> name_index;	//书名索引文件
map<string, Index>author_index;	//作者索引文件
map<string, Index> press_index;	//出版社索引文件
vector<Reader> reader;	//读者文件
vector<Bbook> bbook;	//借还记录文件

//主菜单
int mainmenu();

//文件读盘
void readfile(string s1, string s2, string s3, string s4, string s5, string s6);

//打印当前记录号对应图书
void show_book(int index, int i);

//查询当前所有图书
void find_allbook();

//书号查询
vector<int> find_id(map<int, int> index, int bnum);

//书名查询
vector<int> find_name(map<string, Index> index, string name);

//作者查询
vector<int> find_author(map<string, Index> index, string author);

//出版社查询
vector<int> find_press(map<string, Index> index, string press);

//查询图书控制程序
void find_book();

//添加图书
void add_book();

//修改图书信息
void change_book();

//增加新读者
void add_reader();

//删除读者
void delete_reader();

//读者管理控制程序
void reader_manager();

//借书算法
void borrow_book(int index);

//还书算法
void return_book(vector<int> result, int index);

//借还系统查询函数
vector<int> find_book2();

//查询读者借的书
vector<int> find_borrow_book(int id);

//借还系统控制程序
void BRsystem();

//文件写盘
void outfile();

//main函数入口
int main()
{
	readfile("book_message.txt", "book_index.txt", "author_index.txt", "press_index.txt", "reader_message.txt", "bollow_message.txt");
	int k = 1;
	int n;
	while (k == 1) {
		n = mainmenu();
		switch (n)
		{
		case 1:
			find_book();
			system("pause");
			system("cls");
			break;
		case 2:
			add_book();
			system("cls");
			break;
		case 3:
			change_book();
			system("cls");
			break;
		case 4:
			reader_manager();
			system("cls");
			break;
		case 5:
			BRsystem();
			system("cls");
			break;
		case 0:
			k = 0;
			cout << "系统退出" << endl;
			outfile();
			break;
		}
	}

}

//主菜单
int mainmenu()
{
	int n = 0;
	string temp;
	cout << "-----图书管理系统----" << endl;
	cout << "-    1.图书查询  -" << endl;
	cout << "-    2.添加图书  -" << endl;
	cout << "-    3.修改图书  -" << endl;
	cout << "-    4.读者管理  -" << endl;
	cout << "-    5.借还系统  -" << endl;
	cout << "-    0.退出系统  -" << endl;
	cout << "---------------------" << endl;
	cout << "输入数字选择功能" << endl;
	while (true) {
		cin >> temp;

		if (temp != "1" && temp != "2" && temp != "3" && temp != "4" && temp != "5" && temp != "0")
		{
			cout << "输入不合法,重新输入！" << endl;
		}
		else
			break;
	}
	n = stoi(temp);
	return n;
}

//文件读盘
void readfile(string s1, string s2, string s3, string s4, string s5, string s6) {
	ifstream f1(s1);
	ifstream f2(s2);
	ifstream f3(s3);
	ifstream f4(s4);
	ifstream f5(s5);
	ifstream f6(s6);
	cout << "写入文件中..." << endl;
	while (f1.peek() != EOF) {
		Book temp;
		f1 >> temp.record_num;
		f1 >> temp.book_id;
		f1 >> temp.book_name;
		f1 >> temp.b_ptr;
		f1 >> temp.author;
		f1 >> temp.w_ptr;
		f1 >> temp.press;
		f1 >> temp.p_ptr;
		f1 >> temp.classfity;
		f1 >> temp.collect;
		f1 >> temp.borrow;
		bookid_index.insert(pair<int, int>(temp.book_id, temp.record_num));
		book.push_back(temp);
	}
	while (f2.peek() != EOF) {

		Index temp;
		string temp_s;
		f2 >> temp_s;
		f2 >> temp.lhead;
		f2 >> temp.length;
		name_index.insert(pair<string, Index>(temp_s, temp));
	}
	while (f3.peek() != EOF) {
		Index temp;
		string temp_s;
		f3 >> temp_s;
		f3 >> temp.lhead;
		f3 >> temp.length;
		author_index.insert(pair<string, Index>(temp_s, temp));
	}
	while (f4.peek() != EOF) {
		Index temp;
		string temp_s;
		f4 >> temp_s;
		f4 >> temp.lhead;
		f4 >> temp.length;
		press_index.insert(pair<string, Index>(temp_s, temp));
	}
	while (f5.peek() != EOF) {
		Reader temp;
		f5 >> temp.reader_num;
		f5 >> temp.name;
		f5 >> temp.bn1;
		f5 >> temp.bn2;
		reader.push_back(temp);
	}
	while (f6.peek() != EOF) {
		Bbook temp;
		f6 >> temp.reader_num;
		f6 >> temp.book_id;
		f6 >> temp.borrow_date;
		f6 >> temp.return_date;
		bbook.push_back(temp);
	}
	f1.close();
	f2.close();
	f3.close();
	f4.close();
	f5.close();
	f6.close();
	cout << "写入成功!" << endl;
	system("pause");
	system("cls");
}

//打印当前记录号对应图书
void show_book(int index, int i)
{
	cout << i
		<< setw(16) << book[index - 1].book_id
		<< setw(16) << book[index - 1].book_name
		<< setw(16) << book[index - 1].author
		<< setw(16) << book[index - 1].press
		<< setw(16) << book[index - 1].classfity
		<< setw(16) << book[index - 1].collect
		<< setw(16) << book[index - 1].borrow
		<< endl;
}

//查询当前所有图书
void find_allbook()
{
	int index = 1;
	if (book.size() == 0)
	{
		cout << "当前库中没有图书" << endl;
		return;
	}
	else
	{
		cout << " " << setw(16) << "书号" << setw(16) << "书名" << setw(16) << "作者" << setw(16) << "出版社" << setw(16) << "分类" << setw(16) << "藏书量" << setw(16) << "借出数" << endl;
		for (unsigned int i = 1; i <= book.size(); i++) {
			show_book(i, index++);
		}
	}

}

//根据书号查询图书
vector<int> find_id(map<int, int> index, int bnum)
{
	vector<int> result;
	// find 返回迭代器指向当前查找元素的位置，若查找不到则返回map::end()位置
	auto iter = index.find(bnum);
	int index2 = 1;
	if (iter != index.end())
	{
		cout << " " << setw(16) << "书号" << setw(16) << "书名" << setw(16) << "作者" << setw(16) << "出版社" << setw(16) << "分类" << setw(16) << "藏书量" << setw(16) << "借出数" << endl;
		show_book(iter->second, index2++);	//
		result.push_back(iter->second);
	}
	else
		cout << "Do not Find" << endl;

	return result;

}

//根据书名查询图书
vector<int> find_name(map<string, Index> index, string name) {
	Index result;	//对应键值(头指针和长度)
	vector<int> result2;	//保存查找到的图书记录号
	auto iter = index.find(name);
	if (iter != index.end()) {
		result = iter->second;
		int index = result.lhead;	//记录号
		cout << " " << setw(16) << "书号" << setw(16) << "书名" << setw(16) << "作者" << setw(16) << "出版社" << setw(16) << "分类" << setw(16) << "藏书量" << setw(16) << "借出数" << endl;
		for (int i = 0; i < result.length; i++) {
			show_book(index, i + 1);
			result2.push_back(index);
			index = book[index - 1].b_ptr;	//根据指针更新记录号
		}
	}
	else {
		cout << "Do not Find" << endl;
	}
	return result2;
}

//根据作者查询图书
vector<int> find_author(map<string, Index> index, string author)
{
	vector<int> result2;
	Index result;
	auto iter = index.find(author);
	if (iter != index.end()) {
		result = iter->second;
		int index = result.lhead;
		cout << " " << setw(16) << "书号" << setw(16) << "书名" << setw(16) << "作者" << setw(16) << "出版社" << setw(16) << "分类" << setw(16) << "藏书量" << setw(16) << "借出数" << endl;
		for (int i = 0; i < result.length; i++) {
			show_book(index, i + 1);
			result2.push_back(index);
			index = book[index - 1].w_ptr;
		}
	}
	else {
		cout << "Do not Find" << endl;
	}
	return result2;
}

//根据出版社查询图书
vector<int> find_press(map<string, Index> index, string press)
{
	vector<int> result2;
	Index result;
	auto iter = index.find(press);
	if (iter != index.end()) {
		result = iter->second;
		int index = result.lhead;
		cout << " " << setw(16) << "书号" << setw(16) << "书名" << setw(16) << "作者" << setw(16) << "出版社" << setw(16) << "分类" << setw(16) << "藏书量" << setw(16) << "借出数" << endl;
		for (int i = 0; i < result.length; i++) {
			show_book(index, i + 1);
			result2.push_back(index);
			index = book[index - 1].p_ptr;
		}
	}
	else {
		cout << "Do not Find" << endl;
	}
	return result2;
}

//查询图书控制程序
void find_book()
{
	string temp;
	int a;
	int bno;
	int flag = 1;
	string bname, bauthor, bpress;
	while (flag == 1) {
		cout << "\n1、通过书号查询，2、通过书名查询，3、通过作者查询，4、通过出版社查询，5、查询当前所有图书，0、退出查询" << endl;
		while (true) {
			cin >> temp;

			if (temp != "1" && temp != "2" && temp != "3" && temp != "4" && temp != "5" && temp != "0")
			{
				cout << "输入不合法,重新输入！" << endl;
			}
			else
				break;
		}
		a = stoi(temp);
		switch (a)
		{

		case 1:
			cout << "输入书号：";
			cin >> bno;
			find_id(bookid_index, bno);
			break;
		case 2:
			cout << "输入书名：";
			cin >> bname;
			find_name(name_index, bname);
			break;
		case 3:
			cout << "输入作者：";
			cin >> bauthor;
			find_author(author_index, bauthor);
			break;
		case 4:
			cout << "输入出版社：";
			cin >> bpress;
			find_press(press_index, bpress);
			break;
		case 5:
			find_allbook();
			break;
		case 0:
			cout << "退出查询！" << endl;
			flag = 0;
			break;
		}
	}
}

//添加图书
void add_book()
{
	srand((unsigned)time(NULL));    // 初始化随机数种子
	int flag = 1;
	while (flag == 1)
	{
		int record_num1, book_id1, b_ptr1, w_ptr1, p_ptr1, classify1, collect1;
		int borrow1;
		string book_name1, author1, press1;
		int d;
		d = book.size();
		cout << "请输入书号：";
		cin >> book_id1;
		cout << "请输入存进去的数目：";
		cin >> collect1;
		for (int j = 0; j < d; j++)		//遍历书号
		{
			if (book[j].book_id == book_id1)	//有相同书号，对应库存增加
			{
				book[j].collect += collect1;
				break;
			}
			if (book[j].book_id != book_id1 && j == d - 1)	//遍历结束，没有相同书号，判断剩余变量
			{
				record_num1 = book[d - 1].record_num + 1;		//书号不同是新书，增加一个记录号
				borrow1 = 0;		//新书刚存进去，借出数为0
				cout << "请输入书名：";
				cin >> book_name1;
				for (unsigned int k = 0; k < book.size(); k++)		//遍历书名
				{
					if (book[k].book_name == book_name1)	//有重复名字，归为同一个分类
					{
						classify1 = book[k].classfity;
						break;
					}
					if (book[k].book_name != book_name1 && k == book.size() - 1)//遍历结束无相同名字，随机生成一个新的分类
					{
						classify1 = rand() % 100 + 1;	//1到100之间随机生成分类
						int b = 1;
						while (b == 1)		//循环产生，防止出现不同名字重复分类
						{
							for (unsigned int k1 = 0; k1 < book.size(); k1++)	//遍历分类
							{
								if (book[k1].classfity == classify1)
								{
									classify1 = rand() % 100 + 1;
									break;
								}
								if (k1 == book.size() - 1)
									b = 0;
							}
						}
					}
				}
				cout << "请输入作者：";
				cin >> author1;
				cout << "请输入出版社：";
				cin >> press1;
				for (int i = book.size() - 1; i >= 0; i--)	//从大到小遍历书名
				{
					if (book[i].book_name == book_name1)	//有相同书名则更新
					{
						b_ptr1 = i + 1;		//更新书名指针
						auto iter = name_index.find(book_name1);	//找到书名索引对应书名的迭代器位置
						Index b;
						string c;
						c = book_name1;
						b.lhead = record_num1;		//更新链头指针
						b.length = iter->second.length + 1;	//更新长度
						name_index.erase(iter);		//删除书名位置的迭代器
						name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
						break;
					}
					if (book[i].book_name != book_name1 && i == 0)		//遍历结束无相同书名
					{
						b_ptr1 = 0;		//书名指针置为0
						Index b;
						string c;
						c = book_name1;
						b.lhead = record_num1;
						b.length = 1;	//书名索引长度置为1
						name_index.insert(pair<string, Index>(c, b));	//插入新的书名索引
					}
				}
				for (int i = book.size() - 1; i >= 0; i--)	//从大到小遍历作者
				{
					if (book[i].author == author1)	//有相同作者则更新
					{
						w_ptr1 = i + 1;		//更新作者指针
						auto iter = author_index.find(author1);	//找到作者索引对应作者的迭代器位置
						Index b;
						string c;
						c = author1;
						b.lhead = record_num1;		//更新链头指针
						b.length = iter->second.length + 1;	//更新长度
						author_index.erase(iter);	//删除作者位置的迭代器
						author_index.insert(pair<string, Index>(c, b));	//插入刚保存的作者索引
						break;
					}
					if (book[i].author != author1 && i == 0)	//遍历结束无相同作者
					{
						w_ptr1 = 0;		//作者指针置为0
						Index b;
						string c;
						c = author1;
						b.lhead = record_num1;
						b.length = 1;	//作者索引长度置为1
						author_index.insert(pair<string, Index>(c, b));	//插入新的作者索引
					}
				}
				for (int i = book.size() - 1; i >= 0; i--)	//从大到小遍历出版社
				{
					if (book[i].press == press1)	//有相同出版社则更新
					{
						p_ptr1 = i + 1;		//更新出版社指针
						auto iter = press_index.find(press1);	//找到出版社索引对应出版社的迭代器位置
						Index b;
						string c;
						c = press1;
						b.lhead = record_num1;		//更新链头指针
						b.length = iter->second.length + 1;	//更新长度
						press_index.erase(iter);	//删除出版社位置的迭代器
						press_index.insert(pair<string, Index>(c, b));	//插入刚保存的出版社索引
						break;
					}
					if (book[i].press != press1 && i == 0)	//遍历结束无相同出版社
					{
						p_ptr1 = 0;		//出版社指针置为0
						Index b;
						string c;
						c = press1;
						b.lhead = record_num1;
						b.length = 1;		//出版社索引长度置为1
						press_index.insert(pair<string, Index>(c, b));	//插入新的出版社索引
					}
				}
				Book a;
				a.record_num = record_num1;
				a.book_id = book_id1;
				a.book_name = book_name1;
				a.b_ptr = b_ptr1;
				a.author = author1;
				a.w_ptr = w_ptr1;
				a.press = press1;
				a.p_ptr = p_ptr1;
				a.classfity = classify1;
				a.collect = collect1;
				a.borrow = borrow1;
				book.push_back(a);	//往容器内插入新的图书信息
				bookid_index.insert(pair<int, int>(book_id1, record_num1));		//更新书号索引
			}
		}
		int Cflag;
		int flag1 = 1;
		cout << "是否继续添加图书" << endl;
		cout << "1、是   2、否" << endl;
		while (flag1 == 1)
		{
			cin >> Cflag;
			if (Cflag == 1)
			{
				flag = 1;
				flag1 = 0;
			}
			if (Cflag == 2)
			{
				flag = 0;
				flag1 = 0;
			}
			if (Cflag != 1 && Cflag != 2)
			{
				cout << "输入不合法，请重新输入" << endl;
				flag1 = 1;
			}
		}
	}
}

//修改图书信息
void change_book()
{
	int flag = 1;
	while (flag == 1)
	{
		cout << "是否需要查询图书" << endl;
		cout << "1、是      2否" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			find_book2();
		}
		if (a == 2)
		{
			flag = 0;
		}
	}
	int flag2 = 1;
	while (flag2 == 1)
	{
		cout << "选择想要修改信息的图书（写书号）:" << endl;
		int s;
		cin >> s;
		int flag1 = 1;
		auto iter = bookid_index.find(s);	//找到
		while (flag1 == 1)
		{
			int b;
			cout << "选择要修改的信息(输入0结束修改)：" << endl;
			cout << "1、书号 2、书名 3、作者 4、出版社 5、库存量" << endl;
			cin >> b;
			if (b == 1)
			{
				cout << "请输入新的书号：";
				int book_id1;
				cin >> book_id1;
				for (unsigned int i = 0; i < book.size(); i++)
				{
					if (book[i].book_id == book_id1 && i != iter->second - 1)	//有相同书号，对应库存增加
					{
						auto iter1 = name_index.find(book[iter->second - 1].book_name);		//找到书名对应索引
						if (iter1->second.lhead == book[iter->second - 1].record_num)	//链头指针等于删除的记录号
						{
							Index b;
							string c;
							c = iter1->first;
							b.lhead = book[iter->second - 1].b_ptr;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							name_index.erase(iter1);		//删除书名位置的迭代器
							if (b.length > 0)
								name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
						}
						else
						{
							Index b;
							string c;
							c = iter1->first;
							b.lhead = iter1->second.lhead - 1;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							name_index.erase(iter1);		//删除书名位置的迭代器
							name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
						}

						auto iter2 = author_index.find(book[iter->second - 1].author);		//找到作者对应索引
						if (iter2->second.lhead == book[iter->second - 1].record_num)	//链头指针等于删除的记录号
						{
							Index b;
							string c;
							c = iter2->first;
							b.lhead = book[iter->second - 1].w_ptr;		//更新链头指针
							b.length = iter2->second.length - 1;	//更新长度
							author_index.erase(iter2);		//删除作者位置的迭代器
							if (b.length > 0)
								author_index.insert(pair<string, Index>(c, b));	//插入刚保存的作者索引
						}
						else
						{
							Index b;
							string c;
							c = iter2->first;
							b.lhead = iter2->second.lhead - 1;		//更新链头指针
							b.length = iter2->second.length - 1;	//更新长度
							author_index.erase(iter2);		//删除作者位置的迭代器
							author_index.insert(pair<string, Index>(c, b));	//插入刚保存的作者索引
						}

						auto iter3 = press_index.find(book[iter->second - 1].press);		//找到出版社对应索引
						if (iter3->second.lhead == book[iter->second - 1].record_num)	//链头指针等于删除的记录号
						{
							Index b;
							string c;
							c = iter3->first;
							b.lhead = book[iter->second - 1].p_ptr;		//更新链头指针
							b.length = iter3->second.length - 1;	//更新长度
							press_index.erase(iter3);		//删除出版社位置的迭代器
							if (b.length > 0)
								press_index.insert(pair<string, Index>(c, b));	//插入刚保存的出版社索引
						}
						else
						{
							Index b;
							string c;
							c = iter3->first;
							b.lhead = iter3->second.lhead - 1;		//更新链头指针
							b.length = iter3->second.length - 1;	//更新长度
							press_index.erase(iter3);		//删除出版社位置的迭代器
							press_index.insert(pair<string, Index>(c, b));	//插入刚保存的出版社索引
						}

						book[i].collect += book[iter->second - 1].collect;
						for (unsigned int j = iter->second; j < book.size(); j++)	//相同合并，修改其他项指针指向
						{
							book[j].record_num--;
							auto iter1 = bookid_index.find(book[j].book_id);
							bookid_index.erase(iter1);
							bookid_index.insert(pair<int, int>(book[j].book_id, book[j].record_num));		//更新书号索引
							//更新每个项对应的指针
							if (book[j].b_ptr > iter->second)
							{
								book[j].b_ptr--;
							}
							if (book[j].b_ptr == iter->second)
							{
								book[j].b_ptr = book[iter->second - 1].b_ptr;
							}
							if (book[j].w_ptr > iter->second)
							{
								book[j].w_ptr--;
							}
							if (book[j].w_ptr == iter->second)
							{
								book[j].w_ptr = book[iter->second - 1].w_ptr;
							}
							if (book[j].p_ptr > iter->second)
							{
								book[j].p_ptr--;
							}
							if (book[j].p_ptr == iter->second)
							{
								book[j].p_ptr = book[iter->second - 1].p_ptr;
							}
						}
						auto it = book.begin() + (iter->second - 1);
						book.erase(it);
						bookid_index.erase(iter);	//删除图书记录，删除书号索引
						break;
					}
					if (book[i].book_id != book_id1 && i == book.size() - 1)		//不相同，直接改成新书号，更新书号索引
					{
						book[iter->second - 1].book_id = book_id1;
						int c = iter->second;
						bookid_index.erase(iter);
						bookid_index.insert(pair<int, int>(book_id1, c));
						iter = bookid_index.find(book_id1);  //书号修改，更新查找位置
					}
				}

			}

			if (b == 2)
			{
				cout << "请输入新的书名：";
				string book_name1;
				cin >> book_name1;
				auto iter1 = name_index.find(book[iter->second - 1].book_name);		//查找旧书名在书名索引中的迭代器位置
				if (iter1->second.length > 1)	//旧书名长度大于1，不会被去除掉索引
				{
					for (int i = book.size() - 1; i >= 0; i--)	//从后往前遍历书库
					{
						if (book[i].book_name == book[iter->second - 1].book_name && i > iter->second - 1)
						{	//有相同书名且在修改的书的后面，则索引表就长度减1
							Index b;
							string c;
							c = book[i].book_name;
							b.lhead = iter1->second.lhead;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							name_index.erase(iter1);		//删除书名位置的迭代器
							name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
						if (book[i].book_name == book[iter->second - 1].book_name && i < iter->second - 1)
						{	//有相同书名但在修改的书的前面，索引链头指针更改和长度减1
							Index b;
							string c;
							c = book[i].book_name;
							b.lhead = book[i].record_num;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							name_index.erase(iter1);		//删除书名位置的迭代器
							name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
					}
					for (unsigned int i = iter->second; i < book.size(); i++)
					{	//找旧书名往后的同书名，修改其指针指向前一本书
						if (book[i].book_name == book[iter->second - 1].book_name)
						{
							book[i].b_ptr = book[iter->second - 1].b_ptr;
							break;
						}
					}
				}
				else
					name_index.erase(iter1);	//直接删除该书名索引
				book[iter->second - 1].book_name = book_name1;		//旧的修改完，更新书名
				for (int i = iter->second - 2; i >= 0; i--)		//遍历修改位置往前的书名
				{
					if (book[i].book_name == book_name1)	//有相同书名，更改修改位置指针指向该记录号
					{
						book[iter->second - 1].b_ptr = book[i].record_num;
						break;
					}
					if (book[i].book_name != book_name1 && i == 0)	//遍历结束无相同书名，指针置为0
					{
						book[iter->second - 1].b_ptr = 0;
					}
				}
				for (unsigned int i = iter->second; i < book.size(); i++)	//遍历修改位置往后的书名
				{
					if (book[i].book_name == book_name1)	//有相同书名，把该位置指针指向修改位置的记录号
					{
						book[i].b_ptr = book[iter->second - 1].record_num;
						break;
					}
				}
				auto iter2 = name_index.find(book_name1);
				if (iter2 != name_index.end())	//新书名在书名索引中存在
				{
					for (int i = book.size() - 1; i >= 0; i--)
					{
						if (book[i].book_name == book_name1 && i > iter->second - 1)
						{	//有相同书名，在修改位后面，链头指针不用修改
							book[iter->second - 1].classfity = book[i].classfity;	//修改位置分类置为同一类
							Index b;
							string c;
							c = book_name1;
							b.lhead = iter2->second.lhead;		//更新链头指针
							b.length = iter2->second.length + 1;	//更新长度
							name_index.erase(iter2);		//删除书名位置的迭代器
							name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
						if (book[i].book_name == book_name1 && i < iter->second - 1)
						{	//有相同书名，在修改位前面，链头指针改为修改位置记录号
							book[iter->second - 1].classfity = book[i].classfity;	//修改位置分类置为同一类
							Index b;
							string c;
							c = book_name1;
							b.lhead = book[iter->second - 1].record_num;		//更新链头指针
							b.length = iter2->second.length + 1;	//更新长度
							name_index.erase(iter2);		//删除书名位置的迭代器
							name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
					}
				}
				else
				{	//无相同书名，属于一本新书，产生新分类
					int classify1 = rand() % 100 + 1;	//1到100之间随机生成分类
					int a1 = 1;
					while (a1 == 1)		//循环产生，防止出现不同名字重复分类
					{
						for (unsigned int k1 = 0; k1 < book.size(); k1++)	//遍历分类
						{
							if (book[k1].classfity == classify1)
							{
								classify1 = rand() % 100 + 1;
								break;
							}
							if (k1 == book.size() - 1)
								a1 = 0;
						}
					}
					book[iter->second - 1].classfity = classify1;
					Index b;
					string c;
					c = book_name1;
					b.lhead = book[iter->second - 1].record_num;		//更新链头指针
					b.length = 1;	//更新长度
					name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
				}
			}

			if (b == 3)
			{
				cout << "请输入新的作者：";
				string author1;
				cin >> author1;
				auto iter1 = author_index.find(book[iter->second - 1].author);	//查找旧作者在作者索引中的迭代器位置
				if (iter1->second.length > 1)
				{
					for (int i = book.size() - 1; i >= 0; i--)
					{
						if (book[i].author == book[iter->second - 1].author && i > iter->second - 1)
						{
							Index b;
							string c;
							c = book[i].author;
							b.lhead = iter1->second.lhead;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							author_index.erase(iter1);		//删除书名位置的迭代器
							author_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
						if (book[i].author == book[iter->second - 1].author && i < iter->second - 1)
						{
							Index b;
							string c;
							c = book[i].author;
							b.lhead = book[i].record_num;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							author_index.erase(iter1);		//删除书名位置的迭代器
							author_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
					}
					for (unsigned int i = iter->second + 1; i < book.size(); i++)
					{
						if (book[i].author == book[iter->second - 1].author)
						{
							book[i].w_ptr = book[iter->second - 1].w_ptr;
							break;
						}
					}
				}
				else
					author_index.erase(iter1);
				book[iter->second - 1].author = author1;
				for (int i = iter->second - 2; i >= 0; i--)
				{
					if (book[i].author == author1)
					{
						book[iter->second - 1].w_ptr = book[i].record_num;
						break;
					}
					if (book[i].author != author1 && i == 0)
					{
						book[iter->second - 1].w_ptr = 0;
					}
				}
				for (unsigned int i = iter->second; i < book.size(); i++)
				{
					if (book[i].author == author1)
					{
						book[i].w_ptr = book[iter->second - 1].record_num;
						break;
					}
				}
				auto iter2 = author_index.find(author1);
				if (iter2 != author_index.end())
				{
					for (int i = book.size() - 1; i >= 0; i--)
					{
						if (book[i].author == author1 && i > iter->second - 1)
						{
							Index b;
							string c;
							c = author1;
							b.lhead = iter2->second.lhead;		//更新链头指针
							b.length = iter2->second.length + 1;	//更新长度
							author_index.erase(iter2);		//删除书名位置的迭代器
							author_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
						if (book[i].author == author1 && i < iter->second - 1)
						{
							Index b;
							string c;
							c = author1;
							b.lhead = book[iter->second - 1].record_num;		//更新链头指针
							b.length = iter2->second.length + 1;	//更新长度
							author_index.erase(iter2);		//删除书名位置的迭代器
							author_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
					}
				}
				else
				{
					Index b;
					string c;
					c = author1;
					b.lhead = book[iter->second - 1].record_num;		//更新链头指针
					b.length = 1;	//更新长度
					author_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
				}
			}

			if (b == 4)
			{
				cout << "请输入新的出版社：";
				string press1;
				cin >> press1;
				auto iter1 = press_index.find(book[iter->second - 1].press);
				if (iter1->second.length > 1)
				{
					for (int i = book.size() - 1; i >= 0; i--)
					{
						if (book[i].press == book[iter->second - 1].press && i > iter->second - 1)
						{
							Index b;
							string c;
							c = book[i].press;
							b.lhead = iter1->second.lhead;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							press_index.erase(iter1);		//删除书名位置的迭代器
							press_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
						if (book[i].press == book[iter->second - 1].press && i < iter->second - 1)
						{
							Index b;
							string c;
							c = book[i].press;
							b.lhead = book[i].record_num;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							press_index.erase(iter1);		//删除书名位置的迭代器
							press_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
					}
					for (unsigned int i = iter->second + 1; i < book.size(); i++)
					{
						if (book[i].press == book[iter->second - 1].press)
						{
							book[i].p_ptr = book[iter->second - 1].p_ptr;
							break;
						}
					}
				}
				else
					press_index.erase(iter1);
				book[iter->second - 1].press = press1;
				for (int i = iter->second - 2; i >= 0; i--)
				{
					if (book[i].press == press1)
					{
						book[iter->second - 1].p_ptr = book[i].record_num;
						break;
					}
					if (book[i].press != press1 && i == 0)
					{
						book[iter->second - 1].p_ptr = 0;
					}
				}
				for (unsigned int i = iter->second; i < book.size(); i++)
				{
					if (book[i].press == press1)
					{
						book[i].p_ptr = book[iter->second - 1].record_num;
						break;
					}
				}
				auto iter2 = press_index.find(press1);
				if (iter2 != press_index.end())
				{
					for (int i = book.size() - 1; i >= 0; i--)
					{
						if (book[i].press == press1 && i > iter->second - 1)
						{
							Index b;
							string c;
							c = press1;
							b.lhead = iter2->second.lhead;		//更新链头指针
							b.length = iter2->second.length + 1;	//更新长度
							press_index.erase(iter2);		//删除书名位置的迭代器
							press_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
						if (book[i].press == press1 && i < iter->second - 1)
						{
							Index b;
							string c;
							c = press1;
							b.lhead = book[iter->second - 1].record_num;		//更新链头指针
							b.length = iter2->second.length + 1;	//更新长度
							press_index.erase(iter2);		//删除书名位置的迭代器
							press_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
							break;
						}
					}
				}
				else
				{
					Index b;
					string c;
					c = press1;
					b.lhead = book[iter->second - 1].record_num;		//更新链头指针
					b.length = 1;	//更新长度
					press_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
				}
			}

			if (b == 5)
			{
				cout << "请输入新的库存量：";
				int collect1;
				cin >> collect1;
				if (collect1 != 0)
					book[iter->second - 1].collect = collect1;
				if (collect1 == 0 && book[iter->second - 1].borrow > 0)
					book[iter->second - 1].collect = collect1;
				if (collect1 == 0 && book[iter->second - 1].borrow == 0)
				{
					for (unsigned int i = 0; i < book.size(); i++)
					{
						auto iter1 = name_index.find(book[iter->second - 1].book_name);		//找到书名对应索引
						if (iter1->second.lhead == book[iter->second - 1].record_num)	//链头指针等于删除的记录号
						{
							Index b;
							string c;
							c = iter1->first;
							b.lhead = book[iter->second - 1].b_ptr;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							name_index.erase(iter1);		//删除书名位置的迭代器
							if (b.length > 0)
								name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
						}
						else
						{
							Index b;
							string c;
							c = iter1->first;
							b.lhead = iter1->second.lhead - 1;		//更新链头指针
							b.length = iter1->second.length - 1;	//更新长度
							name_index.erase(iter1);		//删除书名位置的迭代器
							name_index.insert(pair<string, Index>(c, b));	//插入刚保存的书名索引
						}

						auto iter2 = author_index.find(book[iter->second - 1].author);		//找到作者对应索引
						if (iter2->second.lhead == book[iter->second - 1].record_num)	//链头指针等于删除的记录号
						{
							Index b;
							string c;
							c = iter2->first;
							b.lhead = book[iter->second - 1].w_ptr;		//更新链头指针
							b.length = iter2->second.length - 1;	//更新长度
							author_index.erase(iter2);		//删除作者位置的迭代器
							if (b.length > 0)
								author_index.insert(pair<string, Index>(c, b));	//插入刚保存的作者索引
						}
						else
						{
							Index b;
							string c;
							c = iter2->first;
							b.lhead = iter2->second.lhead - 1;		//更新链头指针
							b.length = iter2->second.length - 1;	//更新长度
							author_index.erase(iter2);		//删除作者位置的迭代器
							author_index.insert(pair<string, Index>(c, b));	//插入刚保存的作者索引
						}

						auto iter3 = press_index.find(book[iter->second - 1].press);		//找到出版社对应索引
						if (iter3->second.lhead == book[iter->second - 1].record_num)	//链头指针等于删除的记录号
						{
							Index b;
							string c;
							c = iter3->first;
							b.lhead = book[iter->second - 1].p_ptr;		//更新链头指针
							b.length = iter3->second.length - 1;	//更新长度
							press_index.erase(iter3);		//删除出版社位置的迭代器
							if (b.length > 0)
								press_index.insert(pair<string, Index>(c, b));	//插入刚保存的出版社索引
						}
						else
						{
							Index b;
							string c;
							c = iter3->first;
							b.lhead = iter3->second.lhead - 1;		//更新链头指针
							b.length = iter3->second.length - 1;	//更新长度
							press_index.erase(iter3);		//删除出版社位置的迭代器
							press_index.insert(pair<string, Index>(c, b));	//插入刚保存的出版社索引
						}

						for (unsigned int j = iter->second; j < book.size(); j++)	//修改指针指向
						{
							book[j].record_num--;
							auto iter1 = bookid_index.find(book[j].book_id);
							bookid_index.erase(iter1);
							bookid_index.insert(pair<int, int>(book[j].book_id, book[j].record_num));		//更新书号索引
							if (book[j].b_ptr > iter->second)
							{
								book[j].b_ptr--;
							}
							if (book[j].b_ptr == iter->second)
							{
								book[j].b_ptr = book[iter->second - 1].b_ptr;
							}
							if (book[j].w_ptr > iter->second)
							{
								book[j].w_ptr--;
							}
							if (book[j].w_ptr == iter->second)
							{
								book[j].w_ptr = book[iter->second - 1].w_ptr;
							}
							if (book[j].p_ptr > iter->second)
							{
								book[j].p_ptr--;
							}
							if (book[j].p_ptr == iter->second)
							{
								book[j].p_ptr = book[iter->second - 1].p_ptr;
							}
						}
						auto it = book.begin() + (iter->second - 1);
						book.erase(it);
						bookid_index.erase(iter);
						break;
					}
				}
			}

			if (b == 0)
			{
				flag1 = 0;
				int flag3 = 1;
				while (flag3 == 1)
				{
					cout << "是否继续修改别的图书信息" << endl;
					cout << "1、是      2、否" << endl;
					int b1;
					cin >> b1;
					if (b1 == 1)
					{
						flag2 = 1;
						flag3 = 0;
					}
					if (b1 == 2)
					{
						flag2 = 0;
						flag3 = 0;
					}
					if (b1 != 1 && b1 != 2)
					{
						cout << "输入不合法，请重新输入" << endl;
						flag3 = 1;
					}
				}
			}
		}
	}
}

//读者录入
void add_reader()
{
	string rna;     //读者名
	int rno, rb1;     //读者号，可借书数
	int k = 1;        //标志位
	//注册读者信息(与已有读者读者号不冲突)
	while (k == 1)
	{
		cout << "读者号	读者名	可借书数" << endl;
		cin >> rno >> rna >> rb1;

		//当前没有读者
		if (reader.size() == 0)
		{
			k = 0;
		}
		else
		{
			//遍历查看读者号是否重复
			for (unsigned int i = 0; i < reader.size(); i++)
			{
				if (reader[i].reader_num == rno)       
				{
					cout << "与库中读者号重复，重新输入!" << endl;
					k = 1;
					break;
				}
				//遍历完全无重复,退出输入
				if (i == reader.size() - 1)
					k = 0;
			}
		}
	}
	if (k == 0) {
		cout << "读者录入中" << endl;
		Reader r;            //初始化读者
		r.reader_num = rno;
		r.name = rna;
		r.bn1 = rb1;
		r.bn2 = 0;
		reader.push_back(r);   //增加读者
	}
	system("pause");

}

//删除读者
void delete_reader()
{ 
	int k = 1;
	if (reader.size() == 0)       //读者数为0
	{
		cout << "当前读者库中无读者,请前往注册" << endl;
		system("pause");
		return;
	}
	cout << "以下为读者库中的读者" << endl;
	cout << "读者号" << setw(16) << "读者名" << setw(16) << "可借书数" << setw(16) << "已借书数" << endl;
	for (unsigned int i = 0; i < reader.size(); i++)    //遍历输出读者
	{
		cout << reader[i].reader_num << setw(16) << reader[i].name << setw(16) << reader[i].bn1 << setw(16) << reader[i].bn2 << endl;
	}
	while (k == 1) {
		int a;
		if (reader.size() == 0)
		{
			return;
		}
		cout << "请选择要删除的读者(输入对应读者号),输入(-1)退出删除" << endl;
		cin >> a;
		if (a == -1)
			k = 0;
		else {
			//遍历reader找出要删除的读者
			for (unsigned int i = 0; i < reader.size(); i++)
			{
				//找到对应读者
				if (reader[i].reader_num == a)
				{
					//还有未还书数，不可删除
					if (reader[i].bn2 != 0)
					{
						cout << "该读者还有书未还，请先前往还书系统还书" << endl;
						break;
					}
					//删除相应读者
					else
					{
						vector<Reader>::iterator  it = reader.begin() + i;
						reader.erase(it);
						cout << "删除成功" << endl;
						break;
					}
				}
				if (i == reader.size() - 1)
					cout << "没有找到该读者" << endl;
			}
		}

	}
	system("pause");
}

//读者管理控制程序
void reader_manager()
{
	int a;
	int flag = 1;
	string temp;
	cout << "读者管理系统:" << endl;
	while (flag == 1) {
		cout << "选择功能：1：读者注册	2：读者注销  0:退出" << endl;
		while (true) {
			cin >> temp;

			if (temp != "1" && temp != "2" && temp != "0")       //保证输出合法
			{
				cout << "输入不合法,重新输入！" << endl;
			}
			else
				break;
		}
		a = stoi(temp);   //string字符转int
		switch (a)
		{
		case 1:
			add_reader();        //增加读者
			break;
		case 2:
			delete_reader();     //删除读者
			break;
		case 0:
			cout << "退出系统!" << endl;
			flag = 0;
			system("pause");
			break;
		}
	}

}

//借书算法
void borrow_book(int index)
{
	SYSTEMTIME sys;		//读取系统时间
	if (reader[index].bn1 <= 0)
	{
		cout << "你当前可借书数不大于0，不可借书" << endl;
		return;
	} 
	string s;               //记录输入字符串
	vector<int> result;		//要借的书对应序号
	vector<int> book_list;		//图书对应记录号
	while (true) {
		cout << "查询想要借的书：" << endl;
		book_list = find_book2();      //返回记录号序列
		if (book_list.size() == 0) {	//没有查到相应图书
			return;
		}
		cout << "选择想要借的书:" << endl;
		cin >> s;
		int m = 0;
		//切割字符串
		for (unsigned int i = 0; i < s.size(); i++) {
			string temp;
			if (s[i] == ',') {
				temp = s.substr(m, i - m);
				result.push_back(stoi(temp) - 1);
				m = i + 1;
			}
			if (i == s.size() - 1) {
				temp = s.substr(m);
				result.push_back(stoi(temp) - 1);
			}
		}
		if (reader[index].bn1 < result.size())
		{
			cout << "你当前可借书数小于要借数量，请重新选择" << endl;
			book_list.clear();
			result.clear();
		}
		else
			break;
	}
	for (unsigned int i = 0; i < result.size(); i++) {
		int temp = result[i];
		int temp2 = book_list[temp] - 1;	//记录号减一为对应图书下标
		book[temp2].borrow += 1;     //更新藏书量和借出数
		book[temp2].collect -= 1;

		Bbook b;
		GetLocalTime(&sys);	//获取当前借书时间
		unsigned short year = sys.wYear;
		unsigned short month = sys.wMonth;
		unsigned short day = sys.wDay;
		unsigned short time = sys.wHour;
		unsigned short min = sys.wMinute;
		string date = to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日" + to_string(time) + "时" + to_string(min) + "分";
		//初始化借书记录
		b.book_id = book[temp2].book_id;
		b.reader_num = reader[index].reader_num;
		b.borrow_date = date;
		b.return_date = "未还";
		bbook.push_back(b);
	}
	reader[index].bn1 -= result.size();       //更新读者信息
	reader[index].bn2 += result.size();

	cout << "借书成功" << endl;
}

//还书算法
void return_book(vector<int> result, int index)
{
	//result:未还书书号		//index:读者下标
	string s;
	vector<int> book_list;	//未还图书对应记录号
	SYSTEMTIME sys;	//系统时间
	for (unsigned int i = 0; i < result.size(); i++) {
		auto iter = bookid_index.find(result[i]);
		if (iter != bookid_index.end())
		{
			book_list.push_back(iter->second);
		}
	}
	if (book_list.size() == 0)
	{
		cout << "你没有已借的书" << endl;
		return;
	}
	else {
		cout << "已借的书：" << endl;
		cout << " " << setw(16) << "书号" << setw(16) << "书名" << setw(16) << "作者" << setw(16) << "出版社" << setw(16)
			<< "分类" << setw(16) << "藏书量" << setw(16) << "借出数" << endl;
		int index2 = 1;		//序号
		for (unsigned int i = 0; i < book_list.size(); i++)
			show_book(book_list[i], index2++);      //打印未还的图书
	}
	cout << "选择要归还的书(-1退出选择）：";
	cin >> s;
	if (s == "-1") {
		return;
	}
	int m = 0;
	vector<int> result2;     //读者的选择
	//切割字符串
	for (unsigned int i = 0; i < s.size(); i++) {
		string temp;
		if (s[i] == ',') {
			temp = s.substr(m, i - m);
			result2.push_back(stoi(temp) - 1);
			m = i + 1;
		}
		if (i == s.size() - 1) {
			temp = s.substr(m);        
			result2.push_back(stoi(temp) - 1);
		}
	}
	for (unsigned int i = 0; i < result2.size(); i++) {   
		int temp = result2[i];       
		int temp2 = book_list[temp] - 1;    //选择映射到图书记录号
		book[temp2].borrow -= 1;     //更新藏书量和借出数
		book[temp2].collect += 1;

		for (unsigned int j = 0; j < bbook.size(); j++) {   //遍历借书记录
			if (book[temp2].book_id == bbook[j].book_id && bbook[j].return_date == "未还") {     
				GetLocalTime(&sys);
				unsigned short year = sys.wYear;
				unsigned short month = sys.wMonth;
				unsigned short day = sys.wDay;
				unsigned short time = sys.wHour;
				unsigned short min = sys.wMinute;
				string date = to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日" + to_string(time) + "时" + to_string(min) + "分";

				bbook[j].return_date = date;    //还书日期
			}
		}
	}
	reader[index].bn1 += result2.size();       //更新读者信息
	reader[index].bn2 -= result2.size();

	cout << "还书成功" << endl;
}

//借还系统查询函数
vector<int> find_book2()
{
	string temp;
	int a;
	int bno;
	string bname, bauthor, bpress;
	vector<int> result;
	cout << "\n1、通过书号查询，2、通过书名查询，3、通过作者查询，4、通过出版社查询，输入0退出查询" << endl;
	while (true) {
		cin >> temp;

		if (temp != "1" && temp != "2" && temp != "3" && temp != "4" && temp != "0")
		{
			cout << "输入不合法,重新输入！" << endl;
		}
		else
			break;
	}
	a = stoi(temp);
	switch (a)
	{

	case 1:
		cout << "输入书号：";
		cin >> bno;
		result = find_id(bookid_index, bno);
		break;
	case 2:
		cout << "输入书名：";
		cin >> bname;
		result = find_name(name_index, bname);
		break;
	case 3:
		cout << "输入作者：";
		cin >> bauthor;
		result = find_author(author_index, bauthor);
		break;
	case 4:
		cout << "输入出版社：";
		cin >> bpress;
		result = find_press(press_index, bpress);
		break;
	case 0:
		cout << "退出查询！" << endl;
		break;
	}
	return result;
}

//查询读者未还的书
vector<int> find_borrow_book(int id)
{
	vector<int> result;
	for (unsigned int i = 0; i < bbook.size(); i++) {
		if (bbook[i].reader_num == id && bbook[i].return_date == "未还") {
			result.push_back(bbook[i].book_id);
		}
	}
	return result;	//返回对应书号
}

//借还系统控制程序
void BRsystem()
{
	int a;
	int id;		//读者号
	int index;	//读者在vector中对应下标
	int flag = 0;
	while (true) {
		flag = 0;
		cout << "输入你的读者号(如没有注册，需要先注册),输入0退出:" << endl;
		cin >> id;
		if (id == 0) {
			break;
		}
		for (unsigned int i = 0; i < reader.size(); i++) {
			if (reader[i].reader_num == id) {
				index = i;		//更新下标
				flag = 1;
			}
		}
		if (flag == 0) {
			cout << "没有找到该读者信息！" << endl;
			system("pause");
			continue;
		}
		int flag2 = 0;
		while (flag2 == 0) {
			cout << "选择要进行的操作：1、借书， 2、还书，  0、退出" << endl;
			cin >> a;
			switch (a)
			{
			case 1:
			{
				int flag = 1;
				while (flag == 1)
				{
					string s;
					borrow_book(index);	//对应下标读者借书
					cout << "是否继续借书？1、是，2、否" << endl;
					while (true) {
						cin >> s;
						if (s != "1" && s != "2") {
							cout << "输入不合法，请继续输入!" << endl;
						}
						else {
							break;
						}
					}
					int a = stoi(s);
					if (a == 2) {
						flag = 0;
					}
				}
				break;
			}
			case 2:
			{
				int flag = 1;
				while (flag == 1)
				{
					string s;
					//int id = reader[index].reader_num;	
					vector<int> result = find_borrow_book(id);	//读者未还书目对应书号
					return_book(result, index);    //对应下标读者还书
					if (result.size() == 0) {
						break;
					}
					cout << "是否继续还书？1、是，2、否" << endl;
					while (true) {
						cin >> s;
						if (s != "1" && s != "2") {
							cout << "输入不合法，请继续输入!" << endl;
						}
						else {
							break;
						}
					}
					int a = stoi(s);
					if (a == 2) {
						flag = 0;
					}
				}
				break;
			}

			case 0:
				flag2 = 1;
				break;
			}
		}

	}

}

//文件写盘
void outfile()
{
	ofstream out("book_message.txt");  //初始化一个out对象
	if (!out) {             //是否正常打开
		cout << "error";
	}
	else {
		for (unsigned int i = 0; i < book.size(); i++)	//遍历容器把内容写到文件中
		{
			out << book[i].record_num << " " << book[i].book_id << " " << book[i].book_name << " " << book[i].b_ptr
				<< " " << book[i].author << " " << book[i].w_ptr << " " << book[i].press << " " << book[i].p_ptr << " "
				<< book[i].classfity << " " << book[i].collect << " " << book[i].borrow;  //写入数据
			if (i != book.size() - 1)
				out << endl;
		}
	}
	out.close();         //关闭

	ofstream out1("book_index.txt");  //初始化一个out1对象
	if (!out1) {             //是否正常打开
		cout << "error";
	}
	else {
		map<string, Index>::reverse_iterator iter;
		for (iter = name_index.rbegin(); iter != name_index.rend(); iter++)		//遍历容器把内容写到文件中
		{
			if (iter == name_index.rbegin())
				out1 << iter->first << " " << iter->second.lhead << " " << iter->second.length;
			else
			{
				out1 << endl;
				out1 << iter->first << " " << iter->second.lhead << " " << iter->second.length;
			}
		}
	}
	out1.close();         //关闭

	ofstream out2("author_index.txt");  //初始化一个out2对象
	if (!out2) {             //是否正常打开
		cout << "error";
	}
	else {
		map<string, Index>::reverse_iterator iter;
		for (iter = author_index.rbegin(); iter != author_index.rend(); iter++)		//遍历容器把内容写到文件中
		{
			if (iter == author_index.rbegin())
				out2 << iter->first << " " << iter->second.lhead << " " << iter->second.length;
			else
			{
				out2 << endl;
				out2 << iter->first << " " << iter->second.lhead << " " << iter->second.length;
			}
		}
	}
	out2.close();         //关闭

	ofstream out3("press_index.txt");  //初始化一个out3对象
	if (!out3) {             //是否正常打开
		cout << "error";
	}
	else {
		map<string, Index>::reverse_iterator iter;
		for (iter = press_index.rbegin(); iter != press_index.rend(); iter++)	//遍历容器把内容写到文件中
		{
			if (iter == press_index.rbegin())
				out3 << iter->first << " " << iter->second.lhead << " " << iter->second.length;
			else
			{
				out3 << endl;
				out3 << iter->first << " " << iter->second.lhead << " " << iter->second.length;
			}
		}
	}
	out3.close();         //关闭

	ofstream out4("reader_message.txt");
	if (!out4) {             //是否正常打开
		cout << "error";
	}
	else {
		for (unsigned int i = 0; i < reader.size(); i++)
		{
			out4 << reader[i].reader_num << " "
				<< reader[i].name << " "
				<< reader[i].bn1 << " "
				<< reader[i].bn2;
			if (i != reader.size() - 1)
				out4 << endl;
		}
	}
	out4.close();         //关闭 

	ofstream out5("bollow_message.txt");
	if (!out5) {             //是否正常打开
		cout << "error";
	}
	else {
		for (unsigned int i = 0; i < bbook.size(); i++)
		{
			out5 << bbook[i].reader_num << " "
				<< bbook[i].book_id << " "
				<< bbook[i].borrow_date << " "
				<< bbook[i].return_date;
			if (i != bbook.size() - 1)
				out5 << endl;
		}
	}
	out5.close();         //关闭 
}
