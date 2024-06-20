#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <iostream>

using namespace std;

struct info {
    int num = 0; //�ڽ� ������ ���� Ƚ��
    vector<string> list; //�ڽ� ���� ����Ʈ
};

//���� �����
void combination(string& str, map<int, info>& table, map<string, int>& table_2, bool is_course[], string temp, int start, int size, int& max_size) {

    if (is_course[size]) {

        //cout << "size : " << size << " �ϼ��� ���ڿ� :" << temp << '\n';
        //�ڽ� ���ڿ� �´� ���� �ϳ� �ϼ�
        table_2[temp]++;
        if (table[size].num < table_2[temp]) {

            table[size].num = table_2[temp];
            if (table[size].list.size() >= 1) table[size].list.clear();
            table[size].list.push_back(temp);
        }
        else if (table[size].num == table_2[temp]) {
            table[size].list.push_back(temp);
        }


        if (size == max_size) {
            //cout << "max_size :" << max_size << '\n';
            return;
        }
    }

    for (int i = start; i < str.length(); i++) {
        temp += str[i];
        combination(str, table, table_2, is_course, temp, i + 1, size + 1, max_size);
        temp.pop_back();
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {

    //��ī�ǰ� �߰��ϰ� �;��ϴ� �ڽ��丮 ���
    map<int, info> table;
    //���� Ƚ��
    map<string, int> table_2;

    int max_size = 0;
    bool is_course[11];
    memset(is_course, 0, sizeof(bool) * 11);
    for (int i = 0; i < course.size(); i++) {
        is_course[course[i]] = true;
        max_size = max(max_size, course[i]);
    }


    //���ڿ� ����
    for (int i = 0; i < orders.size(); i++) {
        sort(orders[i].begin(), orders[i].end());
    }

    for (int i = 0; i < orders.size(); i++) {
        string target = orders[i];
        for (int j = i + 1; j < orders.size(); j++) {
            string compare = orders[j];
            string str = "";

            //�ߺ��Ǵ� ���ڿ� ���
            for (int k = 0; k < target.size(); k++) {
                for (int x = 0; x < compare.size(); x++) {
                    if (target[k] == compare[x]) {
                        str += target[k];
                    }
                }
            }

            //cout << "�ߺ��Ǵ� ���ڿ� : " << str << '\n';
             //���� ���� ������ ã��
            combination(str, table, table_2, is_course, "", 0, 0, max_size);
        }
    }


    vector<string> answer;
    for (auto p : table) {
        for (int i = 0; i < p.second.list.size(); i++) answer.push_back(p.second.list[i]);
    }
    sort(answer.begin(), answer.end());




    return answer;
}