#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<set>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <ctime> 

using namespace std;

class Character {
private:
	string name;
	int level;
	int maxhp;
	int hp;
	int attackPower;
	int defense;
public:
	Character(string name, int level, int maxhp, int hp, int attackPower, int defense);
	string getname() const;
	int getlevel() const;
	int gethp() const;
	int getmaxhp() const;
	int getattack() const;
	int getdefense() const;
	void sethp(int newhp);
	void setmaxhp(int newmaxhp);
	void setattack(int newattack);
	void setdefense(int newdefense);

	bool isAlive() const;
	void takeDamage(int damage);
	virtual void attack(Character& target) = 0;
	virtual void display() = 0;
	virtual void displayBrief() = 0;
	virtual ~Character() = default;
};

Character::Character(string name, int level, int maxhp, int hp, int attackPower, int defense)
	: name(name), level(level), maxhp(maxhp), hp(hp), attackPower(attackPower), defense(defense) {}

string Character::getname() const { return name; }
int Character::getlevel() const { return level; }
int Character::gethp() const { return hp; }
int Character::getmaxhp() const { return maxhp; }
int Character::getattack() const { return attackPower; }
int Character::getdefense() const { return defense; }
void Character::sethp(int newhp) { hp = newhp; }
void Character::setmaxhp(int newmaxhp) { maxhp = newmaxhp; }
void Character::setattack(int newattack) { attackPower = newattack; }
void Character::setdefense(int newdefense) { defense = newdefense; }

void Character::takeDamage(int damage) {
	hp -= damage;
	if (hp < 0) hp = 0;
}
bool Character::isAlive() const {
	return hp > 0;
}

class Warrior : public Character {
private:
	int rage;
public:
	Warrior(string name, int level) :Character(name, level, 120, 120, 15, 8), rage(0) {};

	int getrage() const { return rage; }
	void attack(Character& target) {
		int damage = getattack();
		rage += 20;

		if (rage >= 100) {
			damage *= 2;
			rage = 0;
			cout << "【暴击】" << endl;
		}
		target.takeDamage(damage);
		cout << getname() << "劈砍造成" << damage << "点伤害（怒气值：" << rage << "）" << endl;
	}
	void display() override {
		cout << "战士" << getname() << "Lv." << getlevel() << endl;
		cout << "HP" << gethp() << "/" << getmaxhp() << endl;
		cout << "攻击：" << getattack() << endl;
		cout << "防御：" << getdefense() << endl;
		cout << "怒气：" << rage << endl;
	}
	void displayBrief() override {
		cout << "战士 | " << getname() << " | Lv." << getlevel() << endl;
	}

};
class Mage : public Character {
private:
	int mana;
public:
	Mage(string name, int level) :Character(name, level, 80, 80, 25, 5), mana(100) {};

	int getmana() const { return mana; }
	void attack(Character& target) {
		if (mana < 10) {
			cout << "魔法不足，无法攻击" << endl;
			return;
		}
		int damage = (int)(getattack() * 1.5);
		mana -= 10;
		target.takeDamage(damage);
		cout << getname() << "释放火球造成" << damage << "点伤害（法力值：" << mana << "）" << endl;
	}
	void display() override {
		cout << "法师" << getname() << "Lv." << getlevel() << endl;
		cout << "HP" << gethp() << "/" << getmaxhp() << endl;
		cout << "攻击：" << getattack() << endl;
		cout << "防御：" << getdefense() << endl;
		cout << "法力值：" << mana << endl;
	}
	void displayBrief() override {
		cout << "法师 | " << getname() << " | Lv." << getlevel() << endl;
	}
};
class Archer : public Character {
private:
	int arrows;
public:
	Archer(string name, int level) :Character(name, level, 90, 90, 18, 6), arrows(20) {};

	int getarrows() const { return arrows; }
	void attack(Character& target) {
		if (arrows < 1) {
			cout << "箭矢不足，无法攻击" << endl;
			return;
		}
		int damage = getattack() + 5;
		arrows -= 1;
		target.takeDamage(damage);
		cout << getname() << "释放箭矢造成" << damage << "点伤害（剩余箭矢：" << arrows << "）" << endl;
	}
	void display() override {
		cout << "弓箭手" << getname() << "Lv." << getlevel() << endl;
		cout << "HP" << gethp() << "/" << getmaxhp() << endl;
		cout << "攻击：" << getattack() << endl;
		cout << "防御：" << getdefense() << endl;
		cout << "箭矢：" << arrows << endl;
	}
	void displayBrief() override {
		cout << "弓箭手 | " << getname() << " | Lv." << getlevel() << endl;
	}
};


int main() {
	map<string, Character*> characters;
	int chioce;
	srand((unsigned)time(0));
	do {
		cout << "=== RPG游戏人物初始化菜单 ===" << endl;
		cout << "1.创建角色" << endl;
		cout << "2.查看所有角色" << endl;
		cout << "3.查看单人角色" << endl;
		cout << "4.删除角色" << endl;
		cout << "5.角色战斗模拟" << endl;
		cout << "6.按攻击力排序" << endl;
		cout << "7.保存数据" << endl;
		cout << "8.加载数据" << endl;
		cout << "9.退出" << endl;
		cin >> chioce;

		switch (chioce) {
		case 1: {
			while (true) {
				string name;
				int classchioce;
				cout << "请创建玩家昵称：" << endl;
				cin >> name;
				if (characters.find(name) != characters.end()) {
					cout << "该昵称已被注册" << endl;
					break;
				}
				cout << "请选择角色职业" << endl;
				cout << "1.战士" << endl;
				cout << "2.法师" << endl;
				cout << "3.弓箭手" << endl;
				cin >> classchioce;
				if (!(cin >> classchioce)) { cin.clear(); cin.ignore(); cout << "请输入数字" << endl; continue; }
				Character* newChar = nullptr;
				switch (classchioce) {
				case 1:
					newChar = new Warrior(name, 1);
					cout << "正在创建" << endl;
					break;
				case 2:
					newChar = new Mage(name, 1);
					cout << "正在创建" << endl;
					break;
				case 3:
					newChar = new Archer(name, 1);
					cout << "正在创建" << endl;
					break;
				default:
					cout << "无效职业，请重新选择" << endl;
					break;
				}
				if (newChar != nullptr) {
					characters[name] = newChar;
					cout << "创建成功" << endl;
					newChar->display();
				}
				else {
					cout << "创建失败" << endl;
				}

				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
				// 否则继续循环（回到本功能开头）
			}
			break;
		}
		case 2: {
			while (true) {
				if (characters.empty()) {
					cout << "暂无角色" << endl;
				}
				else {
					for (auto& pair : characters) {
						pair.second->display();
					}
				}
				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
			}
			break;
		}
		case 3: {
			while (true) {
				string name;
				cout << "请输入角色昵称" << endl;
				cin >> name;
				auto it = characters.find(name);
				if (it != characters.end()) {
					it->second->display();
				}
				else {
					cout << "未找到该角色" << endl;
				}
				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
			}
			break;
		}
		case 4: {
			while (true) {
				string name;
				int delchioce;
				cout << "请输入要删除的角色昵称" << endl;
				cin >> name;
				auto it = characters.find(name);
				if (it != characters.end()) {
					cout << "已找到该角色，是否确认删除" << endl;
					cout << "1.是  2.否" << endl;
					cin >> delchioce;
					if (!(cin >> delchioce)) { cin.clear(); cin.ignore(); cout << "请输入数字" << endl; continue; }
					if (delchioce == 1) {
						delete it->second;
						characters.erase(it);
						cout << "已删除该角色" << endl;
					}
					else if (delchioce == 2) {
						cout << "已取消删除" << endl;
					}
					else {
						cout << "无效选择" << endl;
					}
				}
				else {
					cout << "未找到该角色" << endl;
				}
				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
			}
			break;
		}
		case 5: {
			while (true) {
				int atkchioce;
				string player1;
				string player2;
				int plychioce;
				cout << "正在进入角色战斗模拟，请选择对战角色或者随机选择角色" << endl;
				cout << "1.选择角色  2.随机角色" << endl;

				cin >> atkchioce;
				if (!(cin >> atkchioce)) { cin.clear(); cin.ignore(); cout << "请输入数字" << endl; continue; }
				if (atkchioce == 1) {
					while (true) {
						if (characters.empty()) {
							cout << "暂无角色" << endl;
							break;
						}
						for (auto& pair : characters) {
							pair.second->displayBrief();
						}
						cout << "请选择角色1" << endl;
						cin >> player1;
						if (characters.find(player1) == characters.end()) {
							cout << "未找到该角色" << endl;
							break;
						}
						cout << "请选择角色2" << endl;
						cin >> player2;
						if (characters.find(player2) == characters.end()) {
							cout << "未找到该角色" << endl;
							break;
						}
						if (player1 == player2) {
							cout << "无法选择相同角色" << endl;
							break;
						}
						Character* p1 = characters[player1];
						Character* p2 = characters[player2];
						cout << "1.开始战斗   2.重新选择" << endl;
						cin >> plychioce;
						if (!(cin >> plychioce)) { cin.clear(); cin.ignore(); cout << "请输入数字" << endl; continue; }
						if (plychioce == 1) {
							cout << "=====战斗开始=====" << endl;
							cout << p1->getname() << "VS" << p2->getname() << endl;
							cout << "==================" << endl;

							int round = 1;
							while (p1->isAlive() && p2->isAlive()) {
								cout << "第" << round << "局" << endl;
								int attacker = rand() % 2;
								if (attacker == 0) {
									p1->attack(*p2);
									if (!p2->isAlive()) {
										cout << p2->getname() << "已经死亡，战斗结束" << endl;
										break;
									}
								}
								else {
									p2->attack(*p1);
									if (!p1->isAlive()) {
										cout << p1->getname() << "已经死亡，战斗结束" << endl;
										break;
									}
								}
								round++;
							}
							break;
						}
						else if (plychioce == 2) {
							cout << "重新开始选择角色" << endl;
							continue;
						}
						else {
							cout << "无效选项" << endl;
						}
						break;
					}
				}
				else if (atkchioce == 2) {
					while (true) {
						cout << "开始随机选择角色对战" << endl;
						if (characters.empty()) {
							cout << "暂无角色" << endl;
							break;
						}
						if (characters.size() < 2) {
							cout << "至少需要 2 个角色才能战斗" << endl;
							break;
						}
						vector<Character*> charList;
						for (auto& pair : characters) {
							charList.push_back(pair.second);
						}
						int index1 = rand() % charList.size();
						int index2;
						do {
							index2 = rand() % charList.size();
						} while (index2 == index1);
						Character* p1 = charList[index1];
						Character* p2 = charList[index2];

						cout << "随机选择的角色分别为：" << endl;
						p1->displayBrief();
						p2->displayBrief();
						cout << "1.开始战斗   2.重新选择" << endl;
						cin >> plychioce;
						if (!(cin >> plychioce)) { cin.clear(); cin.ignore(); cout << "请输入数字" << endl; continue; }
						if (plychioce == 1) {
							cout << "=====战斗开始=====" << endl;
							cout << p1->getname() << "VS" << p2->getname() << endl;
							cout << "==================" << endl;

							int round = 1;
							while (p1->isAlive() && p2->isAlive()) {
								cout << "第" << round << "局" << endl;
								int attacker = rand() % 2;
								if (attacker == 0) {
									p1->attack(*p2);
									if (!p2->isAlive()) {
										cout << p2->getname() << "已经死亡，战斗结束" << endl;
										break;
									}
								}
								else {
									p2->attack(*p1);
									if (!p1->isAlive()) {
										cout << p1->getname() << "已经死亡，战斗结束" << endl;
										break;
									}
								}
								round++;
							}
							break;
						}
						else if (plychioce == 2) {
							cout << "重新开始选择角色" << endl;
							continue;
						}
						else {
							cout << "无效选项" << endl;
						}
						break;
					}
				}
				else {
					cout << "无效选择" << endl;
				}
				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
			}
			break;
		}
		case 6: {
			while (true) {
				if (characters.empty()) {
					cout << "暂无角色" << endl;
				}
				else {
					vector<Character*> charList;
					for (auto& pair : characters) {
						charList.push_back(pair.second);
					}
					sort(charList.begin(), charList.end(), [](Character* a, Character* b)
						{return a->getattack() > b->getattack(); });
					cout << "=====攻击力从高到低=====" << endl;
					for (auto& p : charList) {
						p->displayBrief();
					}
				}
				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
			}
			break;
		}
		case 7: {
			while (true) {
				ofstream file("characters.txt");
				if (!file.is_open()) {
					cout << "无法打开文件进行保存" << endl;
				}
				else {
					for (auto& pair : characters) {
						Character* c = pair.second;
						int classType;
						int special;
						if (dynamic_cast<Warrior*>(c)) {
							classType = 1;
							special = static_cast<Warrior*>(c)->getrage();
						}
						else if (dynamic_cast<Mage*>(c)) {
							classType = 2;
							special = static_cast<Mage*>(c)->getmana();
						}
						else if (dynamic_cast<Archer*>(c)) {
							classType = 3;
							special = static_cast<Archer*>(c)->getarrows();
						}
						file << c->getname() << " "
							<< c->getlevel() << " "
							<< c->gethp() << " "
							<< c->getmaxhp() << " "
							<< c->getattack() << " "
							<< c->getdefense() << " "
							<< classType << " "
							<< special << endl;
					}
					file.close();
					cout << "数据保存成功！共保存 " << characters.size() << " 个角色" << endl;
				}
				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
			}
			break;
		}
		case 8: {
			while (true) {
				ifstream file("characters.txt");
				if (!file.is_open()) {
					cout << "没有找到存档文件" << endl;
				}
				else {
					string name;
					int level, hp, maxhp, atk, def, classType, special;
					int count = 0;

					while (file >> name >> level >> hp >> maxhp >> atk >> def >> classType >> special) {
						if (characters.find(name) != characters.end()) {
							cout << "角色 " << name << " 已存在，跳过加载" << endl;
							continue;
						}

						Character* newChar = nullptr;
						switch (classType) {
						case 1: newChar = new Warrior(name, level); break;
						case 2: newChar = new Mage(name, level); break;
						case 3: newChar = new Archer(name, level); break;
						default: cout << "未知职业类型: " << classType << endl; continue;
						}

						newChar->setmaxhp(maxhp);
						newChar->sethp(hp);
						newChar->setattack(atk);
						newChar->setdefense(def);

						characters[name] = newChar;
						count++;
					}

					file.close();
					cout << "数据加载成功！共加载 " << count << " 个角色" << endl;
				}
				char back;
				cout << "是否回到主菜单？(y/n): ";
				cin >> back;
				if (back == 'y' || back == 'Y') break;
			}
			break;
		}
		case 9:
			cout << "感谢游玩！" << endl;
			break;
		default:
			cout << "无效选择" << endl;
			break;
		}
	} while (chioce != 9);
	return 0;
}