#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <numeric>
#include <climits>
#include <cstring>
#include <list>
#include <queue>
#include <utility>
#include <functional>
#include <unordered_map>
#include <set>
#include <sstream>

using std::queue;
using std::pair;
using std::make_pair;
using std::priority_queue;
using std::list;
using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::greater;
using std::unordered_map;
using std::set;
using std::begin;
using std::end;
using std::find;
using std::swap;
using std::pow;
using std::log10;
using std::stringstream;
using std::fabs;

#define eps 0.00001

struct student {
    string SID;
    int CID;
    string name;
    int CHN_score, MATH_score, ENG_score, PRO_score;
    int total_score;
    double avg_score;
    int passed_count;
};

vector<student> students;

void welcomeMenu() {
    cout << "Welcome to Student Performance Management System (SPMS).\n" << endl;
    cout << "1 - Add" << endl;
    cout << "2 - Remove" << endl;
    cout << "3 - Query" << endl;
    cout << "4 - Show ranking" << endl;
    cout << "5 - Show Statistics" << endl;
    cout << "0 - Exit\n" << endl;
}

void add() {
    cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish." << endl;
    string sid;
    while (cin >> sid && sid != "0") {
        student stu;
        stu.SID = sid;
        cin >> stu.CID >> stu.name >> stu.CHN_score >> stu.MATH_score >> stu.ENG_score >> stu.PRO_score;
        stu.total_score = stu.CHN_score + stu.MATH_score + stu.ENG_score + stu.PRO_score;
        stu.avg_score = stu.total_score / 4.0;
        stu.passed_count = 0;
        if (stu.CHN_score >= 60) ++stu.passed_count;
        if (stu.MATH_score >= 60) ++stu.passed_count;
        if (stu.ENG_score >= 60) ++stu.passed_count;
        if (stu.PRO_score >= 60) ++stu.passed_count;
        bool duplicate = false;
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].SID == sid) {
                cout << "Duplicated SID." << endl;
                duplicate = true;
                break;
            }
        }
        if (!duplicate)
            students.push_back(stu);
        cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish." << endl;
    }
}

void remove() {
    cout << "Please enter SID or name. Enter 0 to finish." << endl;
    string remove_id;
    while (cin >> remove_id && remove_id != "0") {
        int count = 0;
        for (int i = 0; i < students.size();) {
            if (students[i].SID == remove_id || students[i].name == remove_id) {
                ++count;
                students.erase(students.begin() + i);
                continue;//如果erase则i不前进
            }
            ++i;
        }
        cout << count << " student(s) removed." << endl;
        cout << "Please enter SID or name. Enter 0 to finish." << endl;
    }

}

void query() {
    cout << "Please enter SID or name. Enter 0 to finish." << endl;
    string query_id;
    while (cin >> query_id && query_id != "0") {
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].SID == query_id || students[i].name == query_id) {
                int rank = 1;
                for (int j = 0; j < students.size(); ++j) {
                    if (students[j].total_score > students[i].total_score)
                        ++rank;
                }
                cout << rank << ' ' << students[i].SID << ' ' << students[i].CID << ' ' << students[i].name
                     << ' ' << students[i].CHN_score << ' ' << students[i].MATH_score << ' ' << students[i].ENG_score
                     << ' ' << students[i].PRO_score << ' ' << students[i].total_score << ' ' << std::fixed
                     << std::setprecision(2) << students[i].avg_score + eps << endl;
            }
        }
        cout << "Please enter SID or name. Enter 0 to finish." << endl;
    }

}

void showRank() {
    cout << "Showing the ranklist hurts students' self-esteem. Don't do that." << endl;
}

void showStatistic() {
    cout << "Please enter class ID, 0 for the whole statistics." << endl;
    int cid;
    cin >> cid;
    int stu_count = 0;
    int chn_score = 0;
    int math_score = 0;
    int eng_score = 0;
    int pro_score = 0;
    int passed_chn = 0;
    int passed_math = 0;
    int passed_eng = 0;
    int passed_pro = 0;
    int passed[5] = {0};
    for (int i = 0; i < students.size(); ++i) {
        if (cid == 0 || cid == students[i].CID) {
            ++stu_count;
            if (students[i].CHN_score >= 60) ++passed_chn;
            chn_score += students[i].CHN_score;
            if (students[i].MATH_score >= 60) ++passed_math;
            math_score += students[i].MATH_score;
            if (students[i].ENG_score >= 60) ++passed_eng;
            eng_score += students[i].ENG_score;
            if (students[i].PRO_score >= 60) ++passed_pro;
            pro_score += students[i].PRO_score;
            ++passed[students[i].passed_count];
        }
    }
    cout << "Chinese" << endl;
    cout << "Average Score: " << std::fixed << std::setprecision(2) << 1.0 * chn_score / stu_count + eps << endl;//一定要加fixed，定点十进制，而不是科学计数法，否则会WA
    cout << "Number of passed students: " << passed_chn << endl;
    cout << "Number of failed students: " << stu_count - passed_chn << endl << endl;

    cout << "Mathematics" << endl;
    cout << "Average Score: " << std::fixed << std::setprecision(2) << 1.0 * math_score / stu_count + eps << endl;
    cout << "Number of passed students: " << passed_math << endl;
    cout << "Number of failed students: " << stu_count - passed_math << endl << endl;

    cout << "English" << endl;
    cout << "Average Score: " << std::fixed << std::setprecision(2) << 1.0 * eng_score / stu_count + eps << endl;
    cout << "Number of passed students: " << passed_eng << endl;
    cout << "Number of failed students: " << stu_count - passed_eng << endl << endl;

    cout << "Programming" << endl;
    cout << "Average Score: " << std::fixed << std::setprecision(2) << 1.0 * pro_score / stu_count + eps << endl;
    cout << "Number of passed students: " << passed_pro << endl;
    cout << "Number of failed students: " << stu_count - passed_pro << endl << endl;

    cout << "Overall:" << endl;
    cout << "Number of students who passed all subjects: " << passed[4] << endl;
    cout << "Number of students who passed 3 or more subjects: " << passed[4] + passed[3] << endl;
    cout << "Number of students who passed 2 or more subjects: " << passed[4] + passed[3] + passed[2] << endl;
    cout << "Number of students who passed 1 or more subjects: " << passed[4] + passed[3] + passed[2] + passed[1]
         << endl;
    cout << "Number of students who failed all subjects: " << passed[0] << endl;
    cout << endl;
}

int main() {
    welcomeMenu();
    int oper;
    while (cin >> oper) {
        if (oper == 0)
            break;
        else if (oper == 1) {
            add();
            welcomeMenu();
        } else if (oper == 2) {
            remove();
            welcomeMenu();
        } else if (oper == 3) {
            query();
            welcomeMenu();
        } else if (oper == 4) {
            showRank();
            welcomeMenu();
        } else if (oper == 5) {
            showStatistic();
            welcomeMenu();
        }
    }
}
