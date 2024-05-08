// Cpractice.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student{
    long id = 0;   //학번
    string name;  //이름
    int midScore = 0;  //중간고사 점수
    int finalScore = 0;   //기말 점수

    float totalScore() const {   //최종성적 계산 함수
        return (midScore + finalScore) / 2.0;
    }


    friend ostream& operator << (ostream& os, const Student& student) {  //내용을 바꾸지 않겠다는 const 추가
        os << "[ id : " << student.id << ", name : " << student.name << ", total score : " << student.totalScore() << "]";
        return os;
    }
};


void printList(const vector<Student>& students) {  //학생 리스트 출력함수
    for (const auto& student : students) {  //student에 students를 하나씩 계속 집어넣기(레퍼런스를)
        cout << student;
    }
}


int main(){
    vector <Student> students = {};
    int opCode = 0;
    bool terminated = false;
    while (!terminated) {

        printList(students);  //현재 학생 리스트 출력
        cout << endl;

        cout << "Enter Operation Code: ";
        cin >> opCode;
        switch (opCode)
        {
        case 1: {   //학생의 id, name, midScore, finalScore 입력받아 배열에 추가
            Student st;
            cout << ">>>ID?: ";
            cin >> st.id;
            cout << ">>>name? : ";
            cin >> st.name;
            cout << ">>>midScore? : ";
            cin >> st.midScore;
            cout << ">>>finalScore? : ";
            cin >> st.finalScore;

            bool exit = false;

            for (const auto& student : students) {
                if (student.id == st.id) {   //입력받은 id가 이미 존재하는 id라면
                    cout << "The student already exists." << endl;
                    exit = true;
                    break;
                }
            }

            if (!exit) {  //존재하지 않았다면,
                students.push_back(st);
            }  //students 에 학생 st 추가

        } break;
          
        case 2: {   //학번을 입력받아 해당 학생이 존재하면 배열에서 삭제, 없으면 X
            long id;
            cout << ">>>> ID?: ";
            cin >> id;

            auto it = find_if(students.begin(), students.end(),
                [id](const Student& s) { return s.id == id;}
            );   //remove_if()를 이용해 입력받은 id가 이미 존재하면 해당 id를 배열에서 삭제
            if (it == students.end()) {  //배열 내에서 동일한 id를 찾지 못했다면
                cout << "No such student." << endl;
            }
            else {   //동일한 아이디가 있다면,
                students.erase(it);
            }

        } break;


        case 3: { //학번과 중간고사 점수를 입력받아 중간고사 점수를 수정
            long id;
            int midScore;

            cout << ">>> ID? :  ";
            cin >> id;
            cout << ">>> Please enter the revised mid score : ";
            cin >> midScore;
            auto it = find_if(students.begin(), students.end(),
                [id](const Student& s) { return s.id == id; }
            );   //find_if()를 이용해 입력받은 id가 이미 존재하는지 체크
            if (it == students.end()) {  //배열 내에서 동일한 id를 찾지 못했다면
                cout << "No such student." << endl;
            }
            else {   //동일한 id를 찾았다면
                it->midScore = midScore;   //입력받은 midScore값을 it.midScore에 넣는다.
            }
        }   break;

        case 4: {   //학번과 기말고사 점수를 입력받아 기말고사 점수를 수정
            long id;
            int finalScore;

            cout << ">>> ID? :  ";
            cin >> id;
            cout << ">>> Please enter the revised final score : ";
            cin >> finalScore;
            auto it = find_if(students.begin(), students.end(),
                [id](const Student& s) { return s.id == id; }
            );   //find_if()를 이용해 입력받은 id가 이미 존재하는지 체크
            if (it == students.end()) {  //배열 내에서 동일한 id를 찾지 못했다면
                cout << "No such student." << endl;
            }
            else {   //동일한 id를 찾았다면
                it->finalScore = finalScore;   //입력받은 midScore값을 it.midScore에 넣는다.
            }
        }   break;


        case 5: {  //학생들의 학번 순(오름차순)으로 정렬
            //Comparator cmp;
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.id < b.id;
                });
        } break;

        case 6: {  //학생들의 최종 성적 순(내림차순)으로 정렬
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.totalScore() > b.totalScore();
                });
        } break;

        case 7: { //입력된 이름을 가진 학생의 학번을 출력
            string name;

            cout << "Enter the name : ";
            cin >> name;

            bool found = false; // 일치하는 학생을 찾았는지를 저장하는 변수

            for (const auto& student : students) {  //students 전체를 돌면서  //동일한 이름을 가진 여러 학생이 있다면 모두 출력가능
                if (student.name == name) { // 찾으려는 이름과 일치하는 학생을 찾으면
                    cout << student.id << " "; // 해당 학생의 학번 출력
                    found = true; // 일치하는 학생을 찾았다는 상태로 변경
                }
            }
            if (!found) { // 일치하는 학생이 없었으면
                cout << "No such student." << endl;
            }
            else {
                cout << endl;
            }
        } break;

        case 8: {  //반복 종료, 프로그램 종료
            cout << "Exit the program." << endl;
            terminated = true;
        }break;

        default: {
            cout << "Wrong Code\n";
            continue;
        }
        }


    }



}

