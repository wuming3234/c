#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

struct Student {
	string name;
	int number;
	int chinese;
	int math;
	int english;
	int all;
};
int main() {
	vector<Student>rankList;
	int choice;

	do{

		cout << "=== 学生成绩管理系统 ===" << endl;
		cout << "1.学生信息录入" << endl;
		cout << "2.查看所有学生" << endl;
		cout << "3.计算排名" << endl;
		cout << "4.查询学生" << endl;
		cout << "5.统计信息" << endl;
		cout << "6.删除学生" << endl;
		cout << "7.退出" << endl;
		cout << "请选择" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			Student stu;
			string stuname;
			int stunumber;
			int stuchinese;
			int stumath;
			int stuenglish;
			cout << "开始录入学生信息" << endl;
			cout << "请输入学生姓名：" << endl;
			cin >> stuname;
			cout << "请输入学生学号：" << endl;
			cin >> stunumber;
			cout << "请输入学生的语文成绩：" << endl;
			cin >> stuchinese;
			cout << "请输入学生的数学成绩：" << endl;
			cin >> stumath;
			cout << "请输入学生的英语成绩：" << endl;
			cin >> stuenglish;
			stu.name = stuname;
			stu.number = stunumber;
			stu.chinese = stuchinese;
			stu.math = stumath;
			stu.english = stuenglish;
			stu.all = stuchinese + stumath + stuenglish;
			rankList.push_back(stu);
			break;

		}
		case 2:cout << "开始查看所有学生姓名学号：" << endl;
			cout << "学生姓名  学号  语文  数学  英语  总分" << endl;
			for (int i = 0; i < rankList.size(); i++)
			cout << rankList[i]. name<<"    " << rankList[i].number <<"    "<< rankList[i].chinese<<"    "
				<< rankList[i].math<< "    "<<rankList[i].english <<"    "<< rankList[i].all<<endl;
			break;
		case 3:cout << "开始计算排名：" << endl;
			cout << "学生排名  学生姓名  学生学号  学生总分数" << endl;
			sort(rankList.begin(), rankList.end(), [](const Student& a, const Student& b) {
				return a.all > b.all;
				});
			for (int i = 0; i < rankList.size(); i++)
			cout << " " << (i + 1) << "      " << rankList[i].name << "      "
				<< rankList[i].number << "       " << rankList[i].all << endl;
			break;
		case 4: {
			string searchname;
			cout << "开始查询学生，请输入学生姓名：" << endl;
			cin >> searchname;
			bool found = false;
			for (int i = 0; i < rankList.size(); i++) {
				if (rankList[i].name == searchname) {
					cout << "姓名: " << rankList[i].name << endl;
					cout << "学号: " << rankList[i].number << endl;
					cout << "语文: " << rankList[i].chinese << endl;
					cout << "数学: " << rankList[i].math << endl;
					cout << "英语: " << rankList[i].english << endl;
					cout << "总分: " << rankList[i].all << endl;
					found = true;
					break;
				}
			}
			if (!found) {
				cout << "抱歉没有查到该学生" << endl;
			}
			break;
		}
		case 5: {
			cout << "学生统计表：" << endl;
			if (rankList.size() == 0) {
				cout << "暂无数据" << endl;
				break;
			}

			int totalchinese = 0, totalmath = 0, totalenglish = 0;
			int maxchinese = rankList[0].chinese, minchinese = rankList[0].chinese;
			int maxmath = rankList[0].math, minmath = rankList[0].math;
			int maxenglish = rankList[0].english, minenglish = rankList[0].english;
			int n = rankList.size();

			for (int i = 0; i < rankList.size(); i++) {
				totalchinese += rankList[i].chinese;
				totalmath += rankList[i].math;
				totalenglish += rankList[i].english;

				if (rankList[i].chinese > maxchinese) maxchinese = rankList[i].chinese;
				if (rankList[i].chinese < minchinese) minchinese = rankList[i].chinese;
				if (rankList[i].math > maxmath) maxmath = rankList[i].math;
				if (rankList[i].math < minmath) minmath = rankList[i].math;
				if (rankList[i].english > maxenglish) maxenglish = rankList[i].english;
				if (rankList[i].english < minenglish) minenglish = rankList[i].english;
			}

			cout << "    平均分  最高分  最低分" << endl;
			cout << "语文  " << totalchinese / n << "    " << maxchinese << "    " << minchinese << endl;
			cout << "数学  " << totalmath / n << "    " << maxmath << "    " << minmath << endl;
			cout << "英语  " << totalenglish / n << "    " << maxenglish << "    " << minenglish << endl;
			break;
		}
		case 6: {
			string deletename;
			cout << "请输入要删除的学生" << endl;
				cin >> deletename;
				bool found = false;
				for (int i = 0; i < rankList.size(); i++) {
					if (rankList[i].name == deletename) {
						rankList.erase(rankList.begin() + i);
						cout << "删除成功！" << endl;
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "抱歉，没有找到该学生" << endl;
				}

			break;
		}
		case 7:cout << "感谢使用" << endl;
			break;
		}
	} while (choice!=7);
		return 0;
}