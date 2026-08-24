#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct Stats {
    int totalGames;      
    int totalTries;      
    int wins;            
};
struct Record {
    string name;
    string difficulty;
    int tries;
};
int main() {

    Stats stats{ 0,0,0 };
    vector<Record>rankList;
    int choice;
    char playagain;
    srand(time(0));

    do {
        cout << "=== 猜数字游戏 终极版 ===" << endl;
        cout << "1. 开始游戏" << endl;
        cout << "2. 查看统计" << endl;
        cout << "3. 查看排行榜" << endl;
        cout << "4. 退出" << endl;
        cout << "请选择: ";
        cin >> choice;

            switch (choice) { //菜单选择
            case 1: {
                string playername;
            game_start:

                cout << "游戏开始" << endl;
                cout << "=== 选择难度 ===" << endl;
                cout << "1. 简单（1-50，10次）" << endl;
                cout << "2. 普通（1-100，7次）" << endl;
                cout << "3. 困难（1-200，5次）" << endl;
                cout << "请选择: ";

                int difficult;
                int range, maxattempt;
                cin >> difficult;

                switch (difficult) {//难度选择
                case 1: range = 50; maxattempt = 10; break;
                case 2: range = 100; maxattempt = 7; break;
                case 3: range = 200; maxattempt = 5; break;
                default: range = 100; maxattempt = 7; break;
                }

                int a = rand() % range + 1;
                cout << "我已经想好了一个1到 " << range << " 之间的数字。你最多可以猜 " << maxattempt << " 次" << endl;

                cout << "请先输入你的名字：" << endl;
                cin >> playername;
                stats.totalGames++;
                int guess;
                int tries = 0;
                bool guessed = false;

                while (tries < maxattempt) {
                    cout << "第" << (tries + 1) << "次猜测: ";
                    cin >> guess;
                    tries++;
                    stats.totalTries++;

                    if (guess > a) {
                        cout << "太大了！" << endl;
                    }
                    else if (guess < a) {
                        cout << "太小了！" << endl;
                    }
                    else {
                        cout << "恭喜你猜中了！" << endl;
                        cout << "你一共猜了 " << tries << " 次" << endl;
                        guessed = true;
                        stats.wins++;
                        Record r;
                        r.name = playername;
                        if (difficult == 1) {
                            r.difficulty = "简单";
                        }
                        else if (difficult == 3) {
                            r.difficulty = "困难";
                        }
                        else {
                            r.difficulty = "普通";
                        }
                        r.tries = tries;
                        rankList.push_back(r);
                        break;
                    }
                }

                if (!guessed) {
                    cout << "机会用完了！答案是: " << a << endl;
                }
                cout << "想要再来一局吗？ (y/n): ";
                cin >> playagain;

                if (playagain == 'y' || playagain == 'Y') {
                    goto game_start;
                }
                else if (playagain == 'n' || playagain == 'N') {
                    break;
                }
                else {
                    cout << "无效选择，请重新输入" << endl;
                    break;
                }
                break;
            }
            case 2:
                cout << "=== 游戏统计 ===" << endl;
                cout << "总局数" << stats.totalGames << endl;
                cout << "总尝试次数" << stats.totalTries << endl;
                cout << "平均每局次数" << ((double)stats.totalTries / stats.totalGames)<< endl;
                cout << "胜场" << stats.wins << endl;
                cout << "胜率" << ((double)stats.wins / stats.totalGames)*100 << "%" << endl;
                break;
            case 3:
                cout << "=== 排行榜(top10) ===" << endl;
                cout << "排名  玩家名  难度  猜中次数" << endl;
                for (int z = 0; z < rankList.size(); z++) {
                    cout <<" " << (z + 1) << "    " << rankList[z].name << "    "
                        << rankList[z].difficulty << "     " << rankList[z].tries << endl;
                }
                break;
            case 4:
                cout << "感谢游玩！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入。" << endl;
                break;
            }
    } while (choice != 4);

    system("pause");
    return 0;
}